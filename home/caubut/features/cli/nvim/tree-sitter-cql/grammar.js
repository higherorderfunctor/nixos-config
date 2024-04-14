const createCaseInsensitiveRegex = (word) =>
  new RegExp(
    word
      .split("")
      .map((letter) => `[${letter.toLowerCase()}${letter.toUpperCase()}]`)
      .join(""),
  );

const kw = (keyword) => {
  if (keyword.toUpperCase() !== keyword) {
    throw new Error(`Expected upper case keyword got ${keyword}`);
  }
  const words = keyword.split(" ");
  const regExps = words.map(createCaseInsensitiveRegex);

  if (regExps.length === 1) {
    return alias(regExps[0], keyword);
  }
  return alias(seq(...regExps), keyword.replace(/ /g, "_"));
};

const sep1 = (rule, separator) => seq(rule, repeat(seq(separator, rule)));

const commaSep1 = (rule) => sep1(rule, ",");
const PREC = {
  primary: 7,
  unary: 6,
  multiplicative: 5,
  additive: 4,
  comparative: 3,
  and: 2,
  or: 1,
  composite_literal: -1,
};
const dot = ".";
const star = "*";
const comparative_operators = choice("<", "<=", "<>", "=", ">", ">=");
const plus_or_minus = /[+-]/;

const if_not_exists = seq(kw("IF"), kw("NOT"), kw("EXISTS"));
const if_exists = seq(kw("IF"), kw("EXISTS"));
const primary_key = seq(kw("PRIMARY"), kw("KEY"));
const or_replace = seq(kw("OR"), kw("REPLACE"));
const order_direction = choice(kw("ASC"), kw("DESC"));
const uuid_str =
  /[0-9a-fA-F]{8}-[0-9a-fA-F]{4}\-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{12}/;
const hex_digit = /[0-9a-fA-F]/;
const decimal_digits = /[0-9]+/;
const hex_str = choice(
  seq("0X", repeat1(hex_digit)),
  seq("0x", repeat1(hex_digit)),
);
const decimal_str = seq(optional("-"), decimal_digits);
const float_str = choice(
  seq(optional("-"), decimal_digits, dot, decimal_digits),
  /'-'?[0-9]+('.'[0-9]*)?([eE][+-]?[0-9+])?/,
);
const code = /\$\$(\$?[^$]+)+\$\$/;
const identifier = /[a-zA-Z][A-Za-z0-9_$]*/;
const quoted_identifier = /\"[a-zA-Z]([A-Za-z0-9_$]|(\"\"))*\"/;
const timestamp = seq(kw("TIMESTAMP"), alias(token(decimal_str), "time"));
const ttl = seq(kw("TTL"), alias(token(decimal_str), "ttl"));

// https://docs.datastax.com/en/cql-oss/3.3/cql/cql_reference/ref-lexical-valid-chars.html
const underscore = "_";
const alpha = /[a-zA-Z]/;
const digit = /[0-9]/;
const digits = repeat1(digit);
const alphanum = choice(alpha, digit);

const dotted_name = (rule1, rule2, name) =>
  choice(
    seq(alias(rule1, "keyspace"), ".", alias(rule2, name)),
    alias(rule2, name),
  );

module.exports = grammar({
  name: "cql",

  conflicts: (_, original) => original.concat([]),

  rules: {
    source_file: ($) => repeat($._statement),

    // worked ////////////////////////////////////////////////////////////////////////////////////////////////////////

    comma_sep: () => ",",
    dot_sep: () => ".",
    semi_sep: () => ";",

    single_quote: () => "'",
    escaped_single_quote: ($) => seq(field("escape_char", $.single_quote), "'"),

    double_quote: () => '"',
    escaped_double_quote: ($) => seq(field("escape_char", $.double_quote), '"'),

    double_dollar: () => "$$",

    /**
     * https://cassandra.apache.org/doc/5.0/cassandra/developing/cql/definitions.html#identifiers
     */

    // unquoted_identifier::= re('[a-zA-Z][link:[a-zA-Z0-9]]*')
    // NOTE: no idea what "link:" is and the section above the
    // documentation includes underscore in the identifier
    unquoted_identifier: () => seq(alpha, repeat(choice(underscore, alphanum))),
    // quoted_identifier::= '"' (any character where " can appear if doubled)+ '"'
    quoted_identifier: ($) =>
      seq(
        field("left_quote", $.double_quote),
        field("content", repeat1(choice(/[^"]/, $.escaped_double_quote))),
        field("right_quote", $.double_quote),
      ),
    // identifier::= unquoted_identifier | quoted_identifier
    identifier: ($) => choice($.unquoted_identifier, $.quoted_identifier),

    /**
     * https://cassandra.apache.org/doc/stable/cassandra/cql/definitions.html#constants
     */

    // string::= ''' (any character where ' can appear if doubled)+ ''' : '$$' (any character other than '$$') '$$'
    string_literal: ($) =>
      choice(
        seq(
          field("left_quote", $.single_quote),
          field("content", repeat1(choice(/[^']/, $.escaped_single_quote))),
          field("right_quote", $.single_quote),
        ),
        seq(
          field("left_quote", $.double_dollar),
          field("content", /([$][^$]|[^$])+/), // TODO: test this
          field("right_quote", $.double_dollar),
        ),
      ),

    // integer::= re('-?[0-9]+')
    // negative_integer: ($) => prec.right(seq("-", $.term)),
    integer: () => prec(PREC.unary, prec.right(seq(optional("-"), digits))),

    // float::= re('-?[0-9]+(.[0-9]*)?([eE][+-]?[0-9+])?') | NAN | INFINITY
    nan: () => "NAN",
    infinity: () => "INFINITY",
    decimal_fraction: ($) => seq($.dot_sep, digits),
    standard_decimal_notation: ($) => seq($.integer, $.decimal_fraction),
    scientific_notation_exponent: () => /[eE]/,
    scientific_notation: ($) =>
      seq(
        $.integer,
        optional($.decimal_fraction),
        $.scientific_notation_exponent,
        optional(plus_or_minus),
        digits,
      ),
    float_literal: ($) =>
      choice(
        $.scientific_notation,
        $.standard_decimal_notation,
        $.nan,
        $.infinity,
      ),

    // boolean::= TRUE | FALSE
    true_literal: () => "TRUE",
    false_literal: () => "FALSE",
    boolean_literal: ($) => choice($.true_literal, $.false_literal),

    // uuid::= hex\{8}-hex\{4}-hex\{4}-hex\{4}-hex\{12}
    uuid_literal: () =>
      /[0-9a-fA-f]{8}-[0-9a-fA-f]{4}-[0-9a-fA-f]{4}-[0-9a-fA-f]{4}-[0-9a-fA-f]{12}/,

    // hex::= re("[0-9a-fA-F]")

    // blob::= '0' ('x' | 'X') hex+
    blob_literal: () => /0[xX][0-9a-fA-F]+/,

    // constant::= string | integer | float | boolean | uuid | blob | NULL
    null_literal: () => "NULL",
    constant: ($) =>
      choice(
        $.string_literal,
        $.integer,
        $.float_literal,
        $.boolean_literal,
        $.uuid_literal,
        $.blob_literal,
        $.null_literal,
      ),

    /**
     * https://cassandra.apache.org/doc/stable/cassandra/cql/definitions.html#terms
     */

    // term::= constant | literal | function_call | arithmetic_operation | type_hint | bind_marker
    term: ($) =>
      choice(
        $.constant,
        $.function_call,
        $.arithmetic_operation,
        $.bind_marker,
      ),

    // literal::= collection_literal | vector_literal | udt_literal | tuple_literal

    // function_call::= identifier '(' [ term (',' term)* ] ')'
    // function_name: ($) => dotted_name($.object_name, $.object_name, "function"),
    function_name: ($) => $.identifier,
    // function_args: ($) =>
    //   commaSep1(choice($.constant, $.object_name, $.function_call)),
    function_args: ($) => seq($.term, repeat(seq($.comma_sep, $.term))),
    function_call: ($) =>
      seq(
        field("name", $.function_name),
        field("open_parenthesis", "("),
        field("args", $.function_args),
        field("close_parenthesis", ")"),
      ),

    // function_call: ($) =>
    //   seq(
    //     alias($.object_name, "function_name"),
    //     "(",
    //     choice(star, $.function_args),
    //     ")",
    //   ),

    // arithmetic_operation::= '-' term | term ('+' | '-' | '*' | '/' | '%') term
    arithmetic_operator: () => /[-+*/%]/,
    //     const PREC = {
    //   primary: 7,
    //   unary: 6,
    //   multiplicative: 5,
    //   additive: 4,
    //   comparative: 3,
    //   and: 2,
    //   or: 1,
    //   composite_literal: -1,
    // };

    arithmetic_operation: ($) =>
      choice(
        // prec(PREC.unary, prec.right(seq("-", $.term))), FIXME:
        prec(PREC.multiplicative, prec.left(seq($.term, /[*/]/, $.term))),
        prec(PREC.additive, prec.left(seq($.term, /[+-]/, $.term))),
      ),

    // type_hint::= '(' cql_type ')' term

    // bind_marker::= '?' | ':' identifier
    bind_marker: ($) => choice("?", seq(":", $.identifier)),

    /**
     * https://cassandra.apache.org/doc/4.1/cassandra/cql/types.html
     */

    // cql_type::= native_type| collection_type| user_defined_type | tuple_type | custom_type
    cql_type: ($) => choice($.native_type, $.collection_type),

    // https://cassandra.apache.org/doc/4.1/cassandra/cql/types.html#native-types

    // native_type::= ASCII | BIGINT | BLOB | BOOLEAN | COUNTER | DATE
    // | DECIMAL | DOUBLE | DURATION | FLOAT | INET | INT |
    // SMALLINT | TEXT | TIME | TIMESTAMP | TIMEUUID | TINYINT |
    // UUID | VARCHAR | VARINT
    ascii_type: () => "ASCII",
    bigint_type: () => "BIGINT",
    blob_type: () => "BLOB",
    boolean_type: () => "BOOLEAN",
    counter_type: () => "COUNTER",
    date_type: () => "DATE",
    decimal_type: () => "DECIMAL",
    double_type: () => "DOUBLE",
    duration_type: () => "DURATION",
    float_type: () => "FLOAT",
    inet_type: () => "INET",
    int_type: () => "INT",
    smallint_type: () => "SMALLINT",
    text_type: () => "TEXT",
    time_type: () => "TIME",
    timestamp_type: () => "TIMESTAMP",
    timeuuid_type: () => "TIMEUUID",
    tinyint_type: () => "TINYINT",
    uuid_type: () => "UUID",
    varchar_type: () => "VARCHAR",
    varint_type: () => "VARINT",
    native_type: ($) =>
      choice(
        $.ascii_type,
        $.bigint_type,
        $.blob_type,
        $.boolean_type,
        $.counter_type,
        $.date_type,
        $.decimal_type,
        $.double_type,
        $.duration_type,
        $.float_type,
        $.inet_type,
        $.int_type,
        $.smallint_type,
        $.text_type,
        $.time_type,
        $.timestamp_type,
        $.timeuuid_type,
        $.tinyint_type,
        $.uuid_type,
        $.varchar_type,
        $.varint_type,
      ),

    /**
     * https://cassandra.apache.org/doc/4.1/cassandra/cql/types.html#collections
     * FIXME: neither bind_marker nor NULL are supported inside collection literals.
     * FIXME: term cohesivness
     */

    // collection_type::= MAP '<' cql_type',' cql_type'>'
    // | SET '<' cql_type '>'
    // | LIST '<' cql_type'>'
    collection_type: ($) => choice($.map_type, $.set_type, $.list_type),
    map_type: ($) => seq("MAP", "<", $.cql_type, $.comma_sep, ">"),
    set_type: ($) => seq("SET", "<", $.cql_type, ">"),
    list_type: ($) => seq("LIST", "<", $.cql_type, ">"),

    // collection_literal::= map_literal | set_literal | list_literal
    collection_literal: ($) =>
      choice($.map_literal, $.set_literal, $.list_literal),
    // map_literal::= '\{' [ term ':' term (',' term : term)* ] '}'
    map_key: ($) => $.term,
    map_value: ($) => $.term,
    map_entry: ($) => seq($.map_key, ":", $.map_value),
    map_literal: ($) =>
      seq(
        field("open_curly_brace", "{"),
        field("content", seq($.map_entry, seq($.comma_sep, $.map_entry))), // FIXME: filter types
        field("close_curly_brace", "}"),
      ),
    // assignment_map: ($) =>
    //  seq("{", commaSep1(seq($.constant, ":", $._value_marker)), "}"),
    // set_literal::= '\{' [ term (',' term)* ] '}'
    set_literal: ($) =>
      seq(
        field("open_curly_brace", "{"),
        field("content", seq($.term, seq($.comma_sep, $.term))), // FIXME: filter types
        field("close_curly_brace", "}"),
      ),
    //     assignment_set: ($) => seq("{", optional(commaSep1($._value_marker)), "}"),
    // list_literal::= '[' [ term (',' term)* ] ']'
    list_literal: ($) =>
      seq(
        field("open_square_braket", "["),
        field("content", seq($.term, seq($.comma_sep, $.term))), // FIXME: filter types
        field("close_square_bracket", "]"),
      ),
    // assignment_list: ($) => seq("[", commaSep1($._value_marker), "]"),

    /**
     * https://cassandra.apache.org/doc/4.1/cassandra/cql/types.html#udts
     * TODO:
     */

    /**
     * https://cassandra.apache.org/doc/4.1/cassandra/cql/types.html#tuples
     * TODO:
     */

    // tuple_type::= TUPLE '<' cql_type( ',' cql_type)* '>'
    tuple_type: ($) => ...,
    // tuple_literal::= '(' term( ',' term )* ')'
    tuple_literal: ($) =>
      seq(
        field("open_parenthesis", "("),
        field("content", seq($.term, seq($.comma_sep, $.term))), // FIXME: filter types
        field("close_parenthesis", ")"),
      ),

    assignment_tuple: ($) => seq("(", $.expression_list, ")"),

    /**
     * https://cassandra.apache.org/doc/4.1/cassandra/cql/types.html#custom-types
     * TODO:
     */

    /// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // constant: ($) =>
    //   choice(
    //     $._integer,
    //     $.float_literal,
    //     token(hex_str),
    //     $.boolean_literal,
    //     $._code_block,
    //     kw("NULL"),
    //     $.string_literal,
    //     token(uuid_str),
    //   ),
    // _value_marker: ($) => choice($.constant, $.bind_marker),
    // _code_block: ($) => token(code),
    keyspace_name: () => unquoted_identifier,

    table_name: () => seq(alphanum, repeat(choice(underscore, alphanum))),
    table_expression: ($) =>
      choice(seq($.keyspace_name, $.dot_sep, $.table_name), $.table_name),

    column_name: ($) => $.identifier,

    column_glob: () => "*",
    /// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

    from_spec: ($) => seq(kw("FROM"), $.table_expression),
    //
    // -- This is a comment
    // This is a comment too
    /* This is
   a multi-line comment */

    // column_alias: () =>

    // https://docs.datastax.com/en/cql-oss/3.3/cql/cql_reference/cqlSelect.html
    // select_expression
    // *
    //
    //
    // SELECT * | select_expression | DISTINCT partition
    // FROM [keyspace_name.] table_name
    // [WHERE partition_value
    //    [AND clustering_filters
    //    [AND static_filters]]]
    // [ORDER BY PK_column_name ASC|DESC]
    // [LIMIT N]
    // [ALLOW FILTERING]

    select_element: ($) =>
      // seq(
      $.column_name, // FIXME: $.function_call
    // optional(seq(kw("AS"), alias($.object_name, "alias"))),
    // ),

    select_expression: (
      $, // FIXME:
    ) =>
      choice(
        $.column_glob, // NOTE:
        seq($.select_element, repeat(seq($.comma_sep, $.select_element))),
      ),

    select_statement: ($) =>
      seq(
        kw("SELECT"),
        optional(kw("DISTINCT")),
        optional(kw("JSON")),
        $.select_expression,
        $.from_spec,
        optional($.where_spec),
        optional($.order_spec),
        optional($.limit_spec),
        optional(seq(kw("ALLOW"), kw("FILTERING"))),
        $.semi_sep,
      ),

    _statement: ($) =>
      seq(
        choice(
          $.alter_keyspace,
          $.alter_materialized_view,
          $.alter_role,
          $.alter_table,
          $.alter_type,
          $.alter_user,
          $.apply_batch,
          $.create_aggregate,
          $.create_function,
          $.create_index,
          $.create_keyspace,
          $.create_materialized_view,
          $.create_role,
          $.create_table,
          $.create_trigger,
          $.create_type,
          $.create_user,
          $.delete_statement,
          $.drop_aggregate,
          $.drop_function,
          $.drop_index,
          $.drop_keyspace,
          $.drop_materialized_view,
          $.drop_role,
          $.drop_table,
          $.drop_trigger,
          $.drop_type,
          $.drop_user,
          $.grant,
          $.insert_statement,
          $.list_permissions,
          $.list_roles,
          $.revoke,
          $.select_statement,
          $.truncate,
          $.update,
          $.use,
        ),
        optional(";"),
      ),

    limit_spec: ($) => seq(kw("LIMIT"), alias($.integer, "limit_value")),
    // constant: ($) =>
    //   choice(
    //     $._integer,
    //     $.float_literal,
    //     token(hex_str),
    //     $.boolean_literal,
    //     $._code_block,
    //     kw("NULL"),
    //     $.string_literal,
    //     token(uuid_str),
    //   ),
    bind_marker: ($) => choice("?", seq(":", $.object_name)),
    _value_marker: ($) => choice($.constant, $.bind_marker),
    _code_block: ($) => token(code),
    where_spec: ($) => seq(kw("WHERE"), $.relation_elements),
    relation_elements: ($) =>
      prec.left(PREC.and, sep1($.relation_element, kw("AND"))),
    relation_element: ($) =>
      choice(
        seq(
          alias($.object_name, "column"),
          comparative_operators,
          $._value_marker,
        ),
        seq($.function_call, comparative_operators, $._value_marker),
        seq($.function_call, comparative_operators, $.function_call),
        seq(
          alias($.object_name, "column"),
          kw("IN"),
          "(",
          $.function_args,
          ")",
        ),
        seq(
          "(",
          commaSep1(alias($.object_name, "column")),
          ")",
          kw("IN"),
          "(",
          commaSep1($.assignment_tuple),
          ")",
        ),
        seq(
          "(",
          commaSep1(alias($.object_name, "column")),
          ")",
          comparative_operators,
          commaSep1($.assignment_tuple),
        ),
        $.relation_contains_key,
        $.relation_contains,
      ),
    relation_contains_key: ($) =>
      seq(
        alias($.object_name, "column"),
        kw("CONTAINS"),
        kw("KEY"),
        $.constant,
      ),
    relation_contains: ($) =>
      seq(alias($.object_name, "column"), kw("CONTAINS"), $.constant),
    order_spec: ($) =>
      seq(kw("ORDER"), kw("BY"), $.object_name, optional(order_direction)),
    delete_statement: ($) =>
      seq(
        optional($.begin_batch),
        kw("DELETE"),
        optional($.delete_column_list),
        $.from_spec,
        optional($.using_timestamp_spec),
        $.where_spec,
        optional(choice(if_exists, $.if_spec)),
      ),
    begin_batch: ($) =>
      seq(
        kw("BEGIN"),
        optional(choice(kw("LOGGED"), kw("UNLOGGED"), kw("COUNTER"))),
        kw("BATCH"),
        optional($.using_timestamp_spec),
      ),
    delete_column_list: ($) =>
      seq($.delete_column_item, repeat(seq(",", $.delete_column_item))),
    delete_column_item: ($) =>
      seq(
        alias($.object_name, "column"),
        optional(
          seq("[", alias(choice($.string_literal, $.integer), "index"), "]"),
        ),
      ),
    using_timestamp_spec: ($) => seq(kw("USING"), timestamp),
    if_exist: ($) => token(if_exists),
    if_spec: ($) => seq(kw("IF"), $.relation_elements),
    insert_statement: ($) =>
      seq(
        optional($.begin_batch),
        kw("INSERT"),
        kw("INTO"),
        $.table_name,
        $.insert_column_spec,
        $.insert_values_spec,
        optional(if_not_exists),
        optional($.using_ttl_timestamp),
      ),
    insert_column_spec: ($) => seq("(", $.column_list, ")"),
    column_list: ($) => commaSep1(alias($.object_name, "column")),
    insert_values_spec: ($) =>
      choice(
        seq(kw("VALUES"), "(", $.expression_list, ")"),
        seq(kw("JSON"), $.constant),
      ),
    expression_list: ($) => commaSep1($.expression),
    expression: ($) =>
      choice(
        $.constant,
        $.bind_marker,
        $.map_literal,
        $.set_literal,
        $.list_literal,
        $.assignment_tuple,
      ),
    using_ttl_timestamp: ($) =>
      seq(
        kw("USING"),
        choice(
          seq(ttl, optional(seq(kw("AND"), timestamp))),
          seq(timestamp, optional(seq(kw("AND"), ttl))),
        ),
      ),
    // ttl : $ => seq( kw("TTL"), $._integer),
    truncate: ($) => seq(kw("TRUNCATE"), optional(kw("TABLE")), $.table_name),
    create_index: ($) =>
      seq(
        kw("CREATE"),
        kw("INDEX"),
        optional(if_not_exists),
        optional($.short_index_name),
        kw("ON"),
        $.table_name,
        "(",
        $.index_column_spec,
        ")",
      ),
    index_column_spec: ($) =>
      choice(
        alias($.object_name, "column"),
        $.index_keys_spec,
        $.index_entries_s_spec,
        $.index_full_spec,
      ),
    index_keys_spec: ($) =>
      seq(kw("KEYS"), "(", alias($.object_name, "key"), ")"),
    index_entries_s_spec: ($) =>
      seq(kw("ENTRIES"), "(", alias($.object_name, "entry"), ")"),
    index_full_spec: ($) =>
      seq(kw("FULL"), "(", alias($.object_name, "full"), ")"),
    drop_index: ($) =>
      seq(kw("DROP"), kw("INDEX"), optional(if_exists), $.index_name),
    update: ($) =>
      seq(
        optional($.begin_batch),
        kw("UPDATE"),
        $.table_name,
        optional($.using_ttl_timestamp),
        $.update_assignments,
        $.where_spec,
        optional(choice(if_exists, $.if_spec)),
      ),
    update_assignments: ($) => seq(kw("SET"), commaSep1($.assignment_element)),
    assignment_element: ($) =>
      choice(
        seq(
          $.object_name,
          "=",
          choice($.constant, $.map_literal, $.set_literal, $.list_literal),
        ),
        seq(
          $.object_name,
          "=",
          $.object_name,
          plus_or_minus,
          alias($.integer, "assignment_operand"),
        ),
        seq($.object_name, "=", $.object_name, plus_or_minus, $.set_literal),
        seq(
          $.object_name,
          "=",
          $.set_literal,
          plus_or_minus,
          alias($.object_name, "assignment_operand"),
        ),
        seq($.object_name, "=", $.object_name, plus_or_minus, $.map_literal),
        seq(
          $.object_name,
          "=",
          $.map_literal,
          plus_or_minus,
          alias($.object_name, "assignment_operand"),
        ),
        seq($.object_name, "=", $.object_name, plus_or_minus, $.list_literal),
        seq(
          $.object_name,
          "=",
          $.list_literal,
          plus_or_minus,
          alias($.object_name, "assignment_operand"),
        ),
        seq($.indexed_column, "=", $.constant),
      ),
    indexed_column: ($) =>
      seq($.object_name, "[", alias($.integer, "index"), "]"),

    use: ($) => seq(kw("USE"), alias($.object_name, "keyspace")),
    grant: ($) =>
      seq(
        seq(kw("GRANT"), $.privilege),
        seq(kw("ON"), $.resource),
        seq(kw("TO"), alias($.object_name, "role")),
      ),
    revoke: ($) =>
      seq(
        seq(kw("REVOKE"), $.privilege),
        seq(kw("ON"), $.resource),
        seq(kw("FROM"), alias($.object_name, "role")),
      ),
    privilege: ($) =>
      choice(
        seq(kw("ALL"), optional(kw("PERMISSIONS"))),
        kw("ALTER"),
        kw("AUTHORIZE"),
        kw("DESCRIBE"),
        kw("EXECUTE"),
        kw("CREATE"),
        kw("DROP"),
        kw("MODIFY"),
        kw("SELECT"),
      ),
    resource: ($) =>
      choice(
        seq(
          kw("ALL"),
          choice(
            seq(
              kw("FUNCTIONS"),
              optional(
                seq(kw("IN"), kw("KEYSPACE"), alias($.object_name, "keyspace")),
              ),
            ),
            kw("KEYSPACES"),
            kw("ROLES"),
          ),
        ),
        seq(
          kw("FUNCTION"),
          dotted_name($.object_name, $.object_name, "function"),
        ),
        seq(kw("KEYSPACE"), alias($.object_name, "keyspace")),
        seq(kw("ROLE"), alias($.object_name, "role")),
        seq(
          optional(kw("TABLE")),
          dotted_name($.object_name, $.object_name, "table"),
        ),
      ),
    list_roles: ($) =>
      seq(
        kw("LIST"),
        kw("ROLES"),
        optional(seq(kw("OF"), alias($.object_name, "role"))),
        optional(kw("NORECURSIVE")),
      ),
    list_permissions: ($) =>
      seq(
        kw("LIST"),
        $.privilege,
        optional(seq(kw("ON"), $.resource)),
        optional(seq(kw("OF"), alias($.object_name, "role"))),
      ),
    drop_aggregate: ($) =>
      seq(kw("DROP"), kw("AGGREGATE"), optional(if_exists), $.aggregate_name),
    drop_materialized_view: ($) =>
      seq(
        kw("DROP"),
        kw("MATERIALIZED"),
        kw("VIEW"),
        optional(if_exists),
        $.materialized_view_name,
      ),
    drop_function: ($) =>
      seq(kw("DROP"), kw("FUNCTION"), optional(if_exists), $.function_name),
    drop_keyspace: ($) =>
      seq(kw("DROP"), kw("KEYSPACE"), optional(if_exists), $.keyspace_name),
    drop_role: ($) =>
      seq(kw("DROP"), kw("ROLE"), optional(if_exists), $.role_name),
    drop_table: ($) =>
      seq(kw("DROP"), kw("TABLE"), optional(if_exists), $.table_name),
    drop_trigger: ($) =>
      seq(
        kw("DROP"),
        kw("TRIGGER"),
        optional(if_exists),
        $.trigger_name,
        kw("ON"),
        $.table_name,
      ),

    drop_type: ($) =>
      seq(kw("DROP"), kw("TYPE"), optional(if_exists), $.type_name),
    drop_user: ($) =>
      seq(kw("DROP"), kw("USER"), optional(if_exists), $.user_name),
    create_aggregate: ($) =>
      seq(
        kw("CREATE"),
        optional(or_replace),
        kw("AGGREGATE"),
        optional(if_not_exists),
        $.aggregate_name,
        "(",
        $.data_type,
        ")",
        kw("SFUNC"),
        alias($.function_name, "sfunc"),
        kw("STYPE"),
        $.data_type,
        kw("FINALFUNC"),
        alias($.function_name, "finalfunc"),
        kw("INITCOND"),
        $.init_cond_definition,
      ),
    init_cond_definition: ($) =>
      choice(
        $.constant,
        $.init_cond_list,
        $.init_cond_nested_list,
        $.init_cond_hash,
      ),
    init_cond_list: ($) => seq("(", commaSep1($.constant), ")"),
    init_cond_nested_list: ($) =>
      seq(
        "(",
        $.init_cond_list,
        repeat(seq(",", choice($.constant, $.init_cond_list))),
        ")",
      ),
    init_cond_hash: ($) => seq("(", commaSep1($.init_cond_hash_item), ")"),
    init_cond_hash_item: ($) =>
      seq(alias($.object_name, "hash_key"), ":", $.init_cond_definition),
    create_materialized_view: ($) =>
      seq(
        kw("CREATE"),
        kw("MATERIALIZED"),
        kw("VIEW"),
        optional(if_not_exists),
        $.materialized_view_name,
        kw("AS"),
        kw("SELECT"),
        $.column_list,
        kw("FROM"),
        $.table_name,
        $.materialized_view_where,
        $.primary_key_element,
        optional($.with_element),
      ),
    materialized_view_columns: ($) => $.column_list,
    materialized_view_where: ($) =>
      seq(
        kw("WHERE"),
        $.column_not_null,
        optional(repeat(seq(kw("AND"), $.column_not_null))),
        optional(repeat(seq(kw("AND"), $.relation_element))),
      ),
    column_not_null_list: ($) => prec.left(sep1($.column_not_null, kw("AND"))),
    column_not_null: ($) => seq($.object_name, kw("IS"), kw("NOT"), kw("NULL")),
    create_function: ($) =>
      seq(
        kw("CREATE"),
        optional(or_replace),
        kw("FUNCTION"),
        optional(if_not_exists),
        $.function_name,
        "(",
        optional(commaSep1($.typed_name)),
        ")",
        $.return_mode,
        kw("RETURNS"),
        $.data_type,
        kw("LANGUAGE"),
        alias($.object_name, "language"),
        kw("AS"),
        alias($._code_block, "code_block"),
      ),
    data_type: ($) => seq($.data_type_name, optional($.data_type_definition)),
    data_type_name: ($) =>
      choice(
        $.object_name,
        kw("TIMESTAMP"),
        kw("SET"),
        kw("ASCII"),
        kw("BIGINT"),
        kw("BLOB"),
        kw("BOOLEAN"),
        kw("COUNTER"),
        kw("DATE"),
        kw("DECIMAL"),
        kw("DOUBLE"),
        kw("FLOAT"),
        kw("FROZEN"),
        kw("INET"),
        kw("INT"),
        kw("LIST"),
        kw("MAP"),
        kw("SMALLINT"),
        kw("TEXT"),
        kw("TIME"),
        kw("TIMEUUID"),
        kw("TINYINT"),
        kw("TUPLE"),
        kw("VARCHAR"),
        kw("VARINT"),
        kw("UUID"),
      ),
    data_type_definition: ($) => seq("<", commaSep1($.data_type_name), ">"),
    return_mode: ($) =>
      seq(
        choice(kw("CALLED"), seq(kw("RETURNS"), kw("NULL"))),
        kw("ON"),
        kw("NULL"),
        kw("INPUT"),
      ),
    create_keyspace: ($) =>
      seq(
        kw("CREATE"),
        kw("KEYSPACE"),
        optional(if_not_exists),
        $.keyspace_name,
        kw("WITH"),
        kw("REPLICATION"),
        "=",
        $.replication_list,
        optional(seq(kw("AND"), $.durable_writes)),
      ),
    replication_list_item: ($) =>
      choice(
        seq(
          alias($.string_literal, "key"),
          ":",
          alias($.string_literal, "value"),
        ),
        seq(alias($.string_literal, "key"), ":", alias($.integer, "value")),
      ),
    durable_writes: ($) =>
      seq(kw("DURABLE_WRITES"), "=", alias($.boolean_literal, "value")),
    create_role: ($) =>
      seq(
        kw("CREATE"),
        kw("ROLE"),
        optional(if_not_exists),
        $.role_name,
        optional($.role_with),
      ),
    role_with: ($) => seq(kw("WITH"), sep1($.role_with_option, kw("AND"))),
    role_with_option: ($) =>
      choice(
        seq(kw("PASSWORD"), "=", alias($.string_literal, "password")),
        seq(kw("LOGIN"), "=", alias($.boolean_literal, "login")),
        seq(kw("SUPERUSER"), "=", alias($.boolean_literal, "user")),
        seq(kw("OPTIONS"), "=", $.option_hash),
      ),
    option_hash: ($) => seq("{", commaSep1($.option_hash_item), "}"),
    option_hash_item: ($) =>
      seq(
        alias($.string_literal, "key"),
        ":",
        alias(choice($.string_literal, $.float_literal), "value"),
      ),
    create_table: ($) =>
      seq(
        kw("CREATE"),
        kw("TABLE"),
        optional(if_not_exists),
        $.table_name,
        "(",
        $.column_definition_list,
        ")",
        optional($.with_element),
      ),
    column_definition_list: ($) =>
      seq(
        commaSep1($.column_definition),
        optional(seq(",", $.primary_key_element)),
      ),
    column_definition: ($) =>
      seq(
        alias($.object_name, "column"),
        $.data_type,
        optional($.primary_key_column),
      ),
    primary_key_column: ($) => primary_key,
    primary_key_element: ($) =>
      seq(primary_key, "(", $.primary_key_definition, ")"),
    primary_key_definition: ($) =>
      choice(
        alias($.object_name, "primary_key"),
        $.compound_key,
        $.composite_key,
      ),
    compound_key: ($) =>
      seq(alias($.object_name, "partition_key"), ",", $.clustering_key_list),
    clustering_key_list: ($) => commaSep1($.object_name),
    composite_key: ($) =>
      seq("(", $.partition_key_list, ")", ",", $.clustering_key_list),
    partition_key_list: ($) => commaSep1($.object_name),
    with_element: ($) => seq(kw("WITH"), $.table_options),
    table_options: ($) =>
      prec.left(
        PREC.and,
        sep1(
          choice($.clustering_order, $.compact_storage, $.table_option_item),
          kw("AND"),
        ),
      ),
    table_option_item: ($) =>
      choice(
        seq($.table_option_name, "=", $.table_option_value),
        seq($.table_option_name, "=", $.option_hash),
      ),
    table_option_name: ($) => $.object_name,
    table_option_value: ($) => choice($.string_literal, $.float_literal),
    compact_storage: ($) => seq(kw("COMPACT"), kw("STORAGE")),
    clustering_order: ($) =>
      seq(
        kw("CLUSTERING"),
        kw("ORDER"),
        kw("BY"),
        "(",
        alias($.object_name, "column"),
        optional(order_direction),
        ")",
      ),
    create_trigger: ($) =>
      seq(
        kw("CREATE"),
        kw("TRIGGER"),
        optional(if_not_exists),
        $.trigger_name,
        kw("USING"),
        $.trigger_class,
      ),
    trigger_class: ($) => $.string_literal,
    create_type: ($) =>
      seq(
        kw("CREATE"),
        kw("TYPE"),
        optional(if_not_exists),
        $.type_name,
        "(",
        commaSep1($.typed_name),
        ")",
      ),
    typed_name: ($) => seq(alias($.object_name, "column"), $.data_type),
    create_user: ($) =>
      seq(
        kw("CREATE"),
        kw("USER"),
        optional(if_not_exists),
        $.user_name,
        $.user_with,
      ),
    user_with: ($) =>
      seq(kw("WITH"), $.user_password, optional($.user_super_user)),
    user_password: ($) =>
      seq(kw("PASSWORD"), alias($.string_literal, "password")),
    user_super_user: ($) => choice(kw("SUPERUSER"), kw("NOSUPERUSER")),

    alter_materialized_view: ($) =>
      seq(
        kw("ALTER"),
        kw("MATERIALIZED"),
        kw("VIEW"),
        $.materialized_view_name,
        optional($.with_element),
      ),
    alter_keyspace: ($) =>
      seq(
        kw("ALTER"),
        kw("KEYSPACE"),
        $.keyspace_name,
        kw("WITH"),
        kw("REPLICATION"),
        "=",
        $.replication_list,
        optional(seq(kw("AND"), $.durable_writes)),
      ),
    replication_list: ($) => seq("{", commaSep1($.replication_list_item), "}"),
    alter_role: ($) =>
      seq(kw("ALTER"), kw("ROLE"), $.role_name, optional($.role_with)),
    alter_table: ($) =>
      seq(kw("ALTER"), kw("TABLE"), $.table_name, $.alter_table_operation),
    alter_table_operation: ($) =>
      choice(
        $.alter_table_add,
        $.alter_table_drop_columns,
        $.alter_table_drop_compact_storage,
        $.alter_table_rename,
        $.with_element,
      ),
    alter_table_add: ($) => seq(kw("ADD"), commaSep1($.typed_name)),
    alter_table_drop_columns: ($) => seq(kw("DROP"), commaSep1($.object_name)),
    alter_table_drop_compact_storage: ($) =>
      seq(kw("DROP"), kw("COMPACT"), kw("STORAGE")),
    alter_table_rename: ($) =>
      seq(
        kw("RENAME"),
        alias($.object_name, "column"),
        kw("TO"),
        alias($.object_name, "column"),
      ),
    alter_type: ($) =>
      seq(kw("ALTER"), kw("TYPE"), $.type_name, $.alter_type_operation),
    alter_type_operation: ($) =>
      choice($.alter_type_alter_type, $.alter_type_add, $.alter_type_rename),
    alter_type_alter_type: ($) =>
      seq(kw("ALTER"), alias($.object_name, "column"), kw("TYPE"), $.data_type),
    alter_type_add: ($) => seq(kw("ADD"), commaSep1($.typed_name)),
    alter_type_rename: ($) =>
      seq(kw("RENAME"), sep1($.alter_type_rename_item, kw("AND"))),
    alter_type_rename_item: ($) =>
      seq(
        alias($.object_name, "column"),
        kw("TO"),
        alias($.object_name, "column"),
      ),
    alter_user: ($) => seq(kw("ALTER"), kw("USER"), $.user_name, $.user_with),
    apply_batch: ($) => seq(kw("APPLY"), kw("BATCH")),

    object_name: ($) => token(choice(identifier, quoted_identifier)),

    // names
    aggregate_name: ($) =>
      dotted_name($.object_name, $.object_name, "aggregate"),
    short_index_name: ($) =>
      alias(choice($.object_name, $.string_literal), "index"),
    index_name: ($) => dotted_name($.object_name, $.object_name, "index"),
    keyspace_name: ($) => alias($.object_name, "keyspace"),
    materialized_view_name: ($) =>
      dotted_name($.object_name, $.object_name, "materialized_view"),
    role_name: ($) => alias($.object_name, "role"),
    trigger_name: ($) => dotted_name($.object_name, $.object_name, "trigger"),
    type_name: ($) => dotted_name($.object_name, $.object_name, "type"),
    user_name: ($) => alias($.object_name, "user"),
  },
});
