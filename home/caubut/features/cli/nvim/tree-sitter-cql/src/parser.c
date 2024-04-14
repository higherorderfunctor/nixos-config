#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#ifdef _MSC_VER
#pragma optimize("", off)
#elif defined(__clang__)
#pragma clang optimize off
#elif defined(__GNUC__)
#pragma GCC optimize ("O0")
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 1013
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 348
#define ALIAS_COUNT 26
#define TOKEN_COUNT 160
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 12
#define MAX_ALIAS_SEQUENCE_LENGTH 19
#define PRODUCTION_ID_COUNT 65

enum ts_symbol_identifiers {
  anon_sym_COMMA = 1,
  anon_sym_DOT = 2,
  anon_sym_SEMI = 3,
  anon_sym_SQUOTE = 4,
  anon_sym_DQUOTE = 5,
  sym_double_dollar = 6,
  aux_sym_unquoted_identifier_token1 = 7,
  anon_sym__ = 8,
  aux_sym_unquoted_identifier_token2 = 9,
  aux_sym_quoted_identifier_token1 = 10,
  aux_sym_string_literal_token1 = 11,
  aux_sym_string_literal_token2 = 12,
  anon_sym_DASH = 13,
  sym_nan = 14,
  sym_infinity = 15,
  sym_scientific_notation_exponent = 16,
  aux_sym_scientific_notation_token1 = 17,
  sym_true_literal = 18,
  sym_false_literal = 19,
  sym_uuid_literal = 20,
  sym_blob_literal = 21,
  sym_null_literal = 22,
  anon_sym_LPAREN = 23,
  anon_sym_RPAREN = 24,
  sym_arithmetic_operator = 25,
  aux_sym_arithmetic_operation_token1 = 26,
  anon_sym_QMARK = 27,
  anon_sym_COLON = 28,
  anon_sym_LT = 29,
  anon_sym_GT = 30,
  anon_sym_LBRACE = 31,
  anon_sym_RBRACE = 32,
  anon_sym_LBRACK = 33,
  anon_sym_RBRACK = 34,
  sym_column_glob = 35,
  aux_sym_from_spec_token1 = 36,
  aux_sym_select_statement_token1 = 37,
  aux_sym_select_statement_token2 = 38,
  aux_sym_select_statement_token3 = 39,
  aux_sym_select_statement_token4 = 40,
  aux_sym_select_statement_token5 = 41,
  aux_sym_limit_spec_token1 = 42,
  sym__code_block = 43,
  aux_sym_where_spec_token1 = 44,
  aux_sym_relation_elements_token1 = 45,
  anon_sym_LT_EQ = 46,
  anon_sym_LT_GT = 47,
  anon_sym_EQ = 48,
  anon_sym_GT_EQ = 49,
  aux_sym_relation_element_token1 = 50,
  aux_sym_relation_contains_key_token1 = 51,
  aux_sym_relation_contains_key_token2 = 52,
  aux_sym_order_spec_token1 = 53,
  aux_sym_order_spec_token2 = 54,
  aux_sym_order_spec_token3 = 55,
  aux_sym_order_spec_token4 = 56,
  aux_sym_delete_statement_token1 = 57,
  aux_sym_delete_statement_token2 = 58,
  aux_sym_delete_statement_token3 = 59,
  aux_sym_begin_batch_token1 = 60,
  aux_sym_begin_batch_token2 = 61,
  aux_sym_begin_batch_token3 = 62,
  aux_sym_begin_batch_token4 = 63,
  aux_sym_begin_batch_token5 = 64,
  aux_sym_using_timestamp_spec_token1 = 65,
  aux_sym_using_timestamp_spec_token2 = 66,
  aux_sym_using_timestamp_spec_token3 = 67,
  aux_sym_insert_statement_token1 = 68,
  aux_sym_insert_statement_token2 = 69,
  aux_sym_insert_statement_token3 = 70,
  aux_sym_insert_values_spec_token1 = 71,
  aux_sym_using_ttl_timestamp_token1 = 72,
  aux_sym_truncate_token1 = 73,
  aux_sym_truncate_token2 = 74,
  aux_sym_create_index_token1 = 75,
  aux_sym_create_index_token2 = 76,
  aux_sym_create_index_token3 = 77,
  aux_sym_index_keys_spec_token1 = 78,
  aux_sym_index_entries_s_spec_token1 = 79,
  aux_sym_index_full_spec_token1 = 80,
  aux_sym_drop_index_token1 = 81,
  aux_sym_update_token1 = 82,
  aux_sym_update_assignments_token1 = 83,
  aux_sym_use_token1 = 84,
  aux_sym_grant_token1 = 85,
  aux_sym_grant_token2 = 86,
  aux_sym_revoke_token1 = 87,
  aux_sym_privilege_token1 = 88,
  aux_sym_privilege_token2 = 89,
  aux_sym_privilege_token3 = 90,
  aux_sym_privilege_token4 = 91,
  aux_sym_privilege_token5 = 92,
  aux_sym_privilege_token6 = 93,
  aux_sym_privilege_token7 = 94,
  aux_sym_resource_token1 = 95,
  aux_sym_resource_token2 = 96,
  aux_sym_resource_token3 = 97,
  aux_sym_resource_token4 = 98,
  aux_sym_resource_token5 = 99,
  aux_sym_resource_token6 = 100,
  aux_sym_list_roles_token1 = 101,
  aux_sym_list_roles_token2 = 102,
  aux_sym_list_roles_token3 = 103,
  aux_sym_drop_aggregate_token1 = 104,
  aux_sym_drop_materialized_view_token1 = 105,
  aux_sym_drop_materialized_view_token2 = 106,
  aux_sym_drop_trigger_token1 = 107,
  aux_sym_drop_type_token1 = 108,
  aux_sym_drop_user_token1 = 109,
  aux_sym_create_aggregate_token1 = 110,
  aux_sym_create_aggregate_token2 = 111,
  aux_sym_create_aggregate_token3 = 112,
  aux_sym_create_aggregate_token4 = 113,
  aux_sym_create_aggregate_token5 = 114,
  aux_sym_create_aggregate_token6 = 115,
  aux_sym_create_materialized_view_token1 = 116,
  aux_sym_column_not_null_token1 = 117,
  aux_sym_column_not_null_token2 = 118,
  aux_sym_create_function_token1 = 119,
  aux_sym_create_function_token2 = 120,
  aux_sym_data_type_name_token1 = 121,
  aux_sym_data_type_name_token2 = 122,
  aux_sym_data_type_name_token3 = 123,
  aux_sym_data_type_name_token4 = 124,
  aux_sym_data_type_name_token5 = 125,
  aux_sym_data_type_name_token6 = 126,
  aux_sym_data_type_name_token7 = 127,
  aux_sym_data_type_name_token8 = 128,
  aux_sym_data_type_name_token9 = 129,
  aux_sym_data_type_name_token10 = 130,
  aux_sym_data_type_name_token11 = 131,
  aux_sym_data_type_name_token12 = 132,
  aux_sym_data_type_name_token13 = 133,
  aux_sym_data_type_name_token14 = 134,
  aux_sym_data_type_name_token15 = 135,
  aux_sym_data_type_name_token16 = 136,
  aux_sym_data_type_name_token17 = 137,
  aux_sym_data_type_name_token18 = 138,
  aux_sym_data_type_name_token19 = 139,
  aux_sym_data_type_name_token20 = 140,
  aux_sym_data_type_name_token21 = 141,
  aux_sym_return_mode_token1 = 142,
  aux_sym_return_mode_token2 = 143,
  aux_sym_create_keyspace_token1 = 144,
  aux_sym_create_keyspace_token2 = 145,
  aux_sym_durable_writes_token1 = 146,
  aux_sym_role_with_option_token1 = 147,
  aux_sym_role_with_option_token2 = 148,
  aux_sym_role_with_option_token3 = 149,
  aux_sym_role_with_option_token4 = 150,
  aux_sym_primary_key_column_token1 = 151,
  aux_sym_compact_storage_token1 = 152,
  aux_sym_compact_storage_token2 = 153,
  aux_sym_clustering_order_token1 = 154,
  aux_sym_user_super_user_token1 = 155,
  aux_sym_alter_table_add_token1 = 156,
  aux_sym_alter_table_rename_token1 = 157,
  aux_sym_apply_batch_token1 = 158,
  sym_object_name = 159,
  sym_source_file = 160,
  sym_comma_sep = 161,
  sym_dot_sep = 162,
  sym_semi_sep = 163,
  sym_single_quote = 164,
  sym_escaped_single_quote = 165,
  sym_double_quote = 166,
  sym_escaped_double_quote = 167,
  sym_unquoted_identifier = 168,
  sym_quoted_identifier = 169,
  sym_identifier = 170,
  sym_string_literal = 171,
  sym_integer = 172,
  sym_decimal_fraction = 173,
  sym_standard_decimal_notation = 174,
  sym_scientific_notation = 175,
  sym_float_literal = 176,
  sym_boolean_literal = 177,
  sym_constant = 178,
  sym_term = 179,
  sym_function_name = 180,
  sym_function_args = 181,
  sym_function_call = 182,
  sym_arithmetic_operation = 183,
  sym_bind_marker = 184,
  sym_map_key = 185,
  sym_map_value = 186,
  sym_map_entry = 187,
  sym_map_literal = 188,
  sym_set_literal = 189,
  sym_list_literal = 190,
  sym_assignment_tuple = 191,
  sym_keyspace_name = 192,
  sym_table_name = 193,
  sym_table_expression = 194,
  sym_column_name = 195,
  sym_from_spec = 196,
  sym_select_element = 197,
  sym_select_expression = 198,
  sym_select_statement = 199,
  sym__statement = 200,
  sym_limit_spec = 201,
  sym__value_marker = 202,
  sym_where_spec = 203,
  sym_relation_elements = 204,
  sym_relation_element = 205,
  sym_relation_contains_key = 206,
  sym_relation_contains = 207,
  sym_order_spec = 208,
  sym_delete_statement = 209,
  sym_begin_batch = 210,
  sym_delete_column_list = 211,
  sym_delete_column_item = 212,
  sym_using_timestamp_spec = 213,
  sym_if_spec = 214,
  sym_insert_statement = 215,
  sym_insert_column_spec = 216,
  sym_column_list = 217,
  sym_insert_values_spec = 218,
  sym_expression_list = 219,
  sym_expression = 220,
  sym_using_ttl_timestamp = 221,
  sym_truncate = 222,
  sym_create_index = 223,
  sym_index_column_spec = 224,
  sym_index_keys_spec = 225,
  sym_index_entries_s_spec = 226,
  sym_index_full_spec = 227,
  sym_drop_index = 228,
  sym_update = 229,
  sym_update_assignments = 230,
  sym_assignment_element = 231,
  sym_indexed_column = 232,
  sym_use = 233,
  sym_grant = 234,
  sym_revoke = 235,
  sym_privilege = 236,
  sym_resource = 237,
  sym_list_roles = 238,
  sym_list_permissions = 239,
  sym_drop_aggregate = 240,
  sym_drop_materialized_view = 241,
  sym_drop_function = 242,
  sym_drop_keyspace = 243,
  sym_drop_role = 244,
  sym_drop_table = 245,
  sym_drop_trigger = 246,
  sym_drop_type = 247,
  sym_drop_user = 248,
  sym_create_aggregate = 249,
  sym_init_cond_definition = 250,
  sym_init_cond_list = 251,
  sym_init_cond_nested_list = 252,
  sym_init_cond_hash = 253,
  sym_init_cond_hash_item = 254,
  sym_create_materialized_view = 255,
  sym_materialized_view_where = 256,
  sym_column_not_null = 257,
  sym_create_function = 258,
  sym_data_type = 259,
  sym_data_type_name = 260,
  sym_data_type_definition = 261,
  sym_return_mode = 262,
  sym_create_keyspace = 263,
  sym_replication_list_item = 264,
  sym_durable_writes = 265,
  sym_create_role = 266,
  sym_role_with = 267,
  sym_role_with_option = 268,
  sym_option_hash = 269,
  sym_option_hash_item = 270,
  sym_create_table = 271,
  sym_column_definition_list = 272,
  sym_column_definition = 273,
  sym_primary_key_column = 274,
  sym_primary_key_element = 275,
  sym_primary_key_definition = 276,
  sym_compound_key = 277,
  sym_clustering_key_list = 278,
  sym_composite_key = 279,
  sym_partition_key_list = 280,
  sym_with_element = 281,
  sym_table_options = 282,
  sym_table_option_item = 283,
  sym_table_option_name = 284,
  sym_table_option_value = 285,
  sym_compact_storage = 286,
  sym_clustering_order = 287,
  sym_create_trigger = 288,
  sym_trigger_class = 289,
  sym_create_type = 290,
  sym_typed_name = 291,
  sym_create_user = 292,
  sym_user_with = 293,
  sym_user_password = 294,
  sym_user_super_user = 295,
  sym_alter_materialized_view = 296,
  sym_alter_keyspace = 297,
  sym_replication_list = 298,
  sym_alter_role = 299,
  sym_alter_table = 300,
  sym_alter_table_operation = 301,
  sym_alter_table_add = 302,
  sym_alter_table_drop_columns = 303,
  sym_alter_table_drop_compact_storage = 304,
  sym_alter_table_rename = 305,
  sym_alter_type = 306,
  sym_alter_type_operation = 307,
  sym_alter_type_alter_type = 308,
  sym_alter_type_add = 309,
  sym_alter_type_rename = 310,
  sym_alter_type_rename_item = 311,
  sym_alter_user = 312,
  sym_apply_batch = 313,
  sym_aggregate_name = 314,
  sym_short_index_name = 315,
  sym_index_name = 316,
  sym_materialized_view_name = 317,
  sym_role_name = 318,
  sym_trigger_name = 319,
  sym_type_name = 320,
  sym_user_name = 321,
  aux_sym_source_file_repeat1 = 322,
  aux_sym_unquoted_identifier_repeat1 = 323,
  aux_sym_quoted_identifier_repeat1 = 324,
  aux_sym_string_literal_repeat1 = 325,
  aux_sym_integer_repeat1 = 326,
  aux_sym_function_args_repeat1 = 327,
  aux_sym_select_expression_repeat1 = 328,
  aux_sym_relation_elements_repeat1 = 329,
  aux_sym_relation_element_repeat1 = 330,
  aux_sym_relation_element_repeat2 = 331,
  aux_sym_delete_column_list_repeat1 = 332,
  aux_sym_expression_list_repeat1 = 333,
  aux_sym_update_assignments_repeat1 = 334,
  aux_sym_init_cond_list_repeat1 = 335,
  aux_sym_init_cond_nested_list_repeat1 = 336,
  aux_sym_init_cond_hash_repeat1 = 337,
  aux_sym_materialized_view_where_repeat1 = 338,
  aux_sym_create_function_repeat1 = 339,
  aux_sym_data_type_definition_repeat1 = 340,
  aux_sym_role_with_repeat1 = 341,
  aux_sym_option_hash_repeat1 = 342,
  aux_sym_column_definition_list_repeat1 = 343,
  aux_sym_clustering_key_list_repeat1 = 344,
  aux_sym_table_options_repeat1 = 345,
  aux_sym_replication_list_repeat1 = 346,
  aux_sym_alter_type_rename_repeat1 = 347,
  anon_alias_sym_aggregate = 348,
  anon_alias_sym_assignment_operand = 349,
  anon_alias_sym_column = 350,
  anon_alias_sym_entry = 351,
  anon_alias_sym_finalfunc = 352,
  anon_alias_sym_full = 353,
  anon_alias_sym_function = 354,
  anon_alias_sym_hash_key = 355,
  anon_alias_sym_index = 356,
  anon_alias_sym_key = 357,
  anon_alias_sym_keyspace = 358,
  anon_alias_sym_language = 359,
  anon_alias_sym_limit_value = 360,
  anon_alias_sym_login = 361,
  anon_alias_sym_materialized_view = 362,
  anon_alias_sym_partition_key = 363,
  anon_alias_sym_password = 364,
  anon_alias_sym_primary_key = 365,
  anon_alias_sym_role = 366,
  anon_alias_sym_sfunc = 367,
  anon_alias_sym_table = 368,
  anon_alias_sym_trigger = 369,
  anon_alias_sym_ttl = 370,
  anon_alias_sym_type = 371,
  anon_alias_sym_user = 372,
  anon_alias_sym_value = 373,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [anon_sym_COMMA] = ",",
  [anon_sym_DOT] = ".",
  [anon_sym_SEMI] = ";",
  [anon_sym_SQUOTE] = "'",
  [anon_sym_DQUOTE] = "\"",
  [sym_double_dollar] = "double_dollar",
  [aux_sym_unquoted_identifier_token1] = "unquoted_identifier_token1",
  [anon_sym__] = "_",
  [aux_sym_unquoted_identifier_token2] = "unquoted_identifier_token2",
  [aux_sym_quoted_identifier_token1] = "quoted_identifier_token1",
  [aux_sym_string_literal_token1] = "string_literal_token1",
  [aux_sym_string_literal_token2] = "string_literal_token2",
  [anon_sym_DASH] = "-",
  [sym_nan] = "nan",
  [sym_infinity] = "infinity",
  [sym_scientific_notation_exponent] = "scientific_notation_exponent",
  [aux_sym_scientific_notation_token1] = "scientific_notation_token1",
  [sym_true_literal] = "true_literal",
  [sym_false_literal] = "false_literal",
  [sym_uuid_literal] = "uuid_literal",
  [sym_blob_literal] = "blob_literal",
  [sym_null_literal] = "null_literal",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
  [sym_arithmetic_operator] = "arithmetic_operator",
  [aux_sym_arithmetic_operation_token1] = "arithmetic_operation_token1",
  [anon_sym_QMARK] = "\?",
  [anon_sym_COLON] = ":",
  [anon_sym_LT] = "<",
  [anon_sym_GT] = ">",
  [anon_sym_LBRACE] = "{",
  [anon_sym_RBRACE] = "}",
  [anon_sym_LBRACK] = "[",
  [anon_sym_RBRACK] = "]",
  [sym_column_glob] = "column_glob",
  [aux_sym_from_spec_token1] = "FROM",
  [aux_sym_select_statement_token1] = "SELECT",
  [aux_sym_select_statement_token2] = "DISTINCT",
  [aux_sym_select_statement_token3] = "JSON",
  [aux_sym_select_statement_token4] = "ALLOW",
  [aux_sym_select_statement_token5] = "FILTERING",
  [aux_sym_limit_spec_token1] = "LIMIT",
  [sym__code_block] = "code_block",
  [aux_sym_where_spec_token1] = "WHERE",
  [aux_sym_relation_elements_token1] = "AND",
  [anon_sym_LT_EQ] = "<=",
  [anon_sym_LT_GT] = "<>",
  [anon_sym_EQ] = "=",
  [anon_sym_GT_EQ] = ">=",
  [aux_sym_relation_element_token1] = "IN",
  [aux_sym_relation_contains_key_token1] = "CONTAINS",
  [aux_sym_relation_contains_key_token2] = "KEY",
  [aux_sym_order_spec_token1] = "ORDER",
  [aux_sym_order_spec_token2] = "BY",
  [aux_sym_order_spec_token3] = "ASC",
  [aux_sym_order_spec_token4] = "DESC",
  [aux_sym_delete_statement_token1] = "DELETE",
  [aux_sym_delete_statement_token2] = "IF",
  [aux_sym_delete_statement_token3] = "EXISTS",
  [aux_sym_begin_batch_token1] = "BEGIN",
  [aux_sym_begin_batch_token2] = "LOGGED",
  [aux_sym_begin_batch_token3] = "UNLOGGED",
  [aux_sym_begin_batch_token4] = "COUNTER",
  [aux_sym_begin_batch_token5] = "BATCH",
  [aux_sym_using_timestamp_spec_token1] = "USING",
  [aux_sym_using_timestamp_spec_token2] = "TIMESTAMP",
  [aux_sym_using_timestamp_spec_token3] = "time",
  [aux_sym_insert_statement_token1] = "INSERT",
  [aux_sym_insert_statement_token2] = "INTO",
  [aux_sym_insert_statement_token3] = "NOT",
  [aux_sym_insert_values_spec_token1] = "VALUES",
  [aux_sym_using_ttl_timestamp_token1] = "TTL",
  [aux_sym_truncate_token1] = "TRUNCATE",
  [aux_sym_truncate_token2] = "TABLE",
  [aux_sym_create_index_token1] = "CREATE",
  [aux_sym_create_index_token2] = "INDEX",
  [aux_sym_create_index_token3] = "ON",
  [aux_sym_index_keys_spec_token1] = "KEYS",
  [aux_sym_index_entries_s_spec_token1] = "ENTRIES",
  [aux_sym_index_full_spec_token1] = "FULL",
  [aux_sym_drop_index_token1] = "DROP",
  [aux_sym_update_token1] = "UPDATE",
  [aux_sym_update_assignments_token1] = "SET",
  [aux_sym_use_token1] = "USE",
  [aux_sym_grant_token1] = "GRANT",
  [aux_sym_grant_token2] = "TO",
  [aux_sym_revoke_token1] = "REVOKE",
  [aux_sym_privilege_token1] = "ALL",
  [aux_sym_privilege_token2] = "PERMISSIONS",
  [aux_sym_privilege_token3] = "ALTER",
  [aux_sym_privilege_token4] = "AUTHORIZE",
  [aux_sym_privilege_token5] = "DESCRIBE",
  [aux_sym_privilege_token6] = "EXECUTE",
  [aux_sym_privilege_token7] = "MODIFY",
  [aux_sym_resource_token1] = "FUNCTIONS",
  [aux_sym_resource_token2] = "KEYSPACE",
  [aux_sym_resource_token3] = "KEYSPACES",
  [aux_sym_resource_token4] = "ROLES",
  [aux_sym_resource_token5] = "FUNCTION",
  [aux_sym_resource_token6] = "ROLE",
  [aux_sym_list_roles_token1] = "LIST",
  [aux_sym_list_roles_token2] = "OF",
  [aux_sym_list_roles_token3] = "NORECURSIVE",
  [aux_sym_drop_aggregate_token1] = "AGGREGATE",
  [aux_sym_drop_materialized_view_token1] = "MATERIALIZED",
  [aux_sym_drop_materialized_view_token2] = "VIEW",
  [aux_sym_drop_trigger_token1] = "TRIGGER",
  [aux_sym_drop_type_token1] = "TYPE",
  [aux_sym_drop_user_token1] = "USER",
  [aux_sym_create_aggregate_token1] = "OR",
  [aux_sym_create_aggregate_token2] = "REPLACE",
  [aux_sym_create_aggregate_token3] = "SFUNC",
  [aux_sym_create_aggregate_token4] = "STYPE",
  [aux_sym_create_aggregate_token5] = "FINALFUNC",
  [aux_sym_create_aggregate_token6] = "INITCOND",
  [aux_sym_create_materialized_view_token1] = "AS",
  [aux_sym_column_not_null_token1] = "IS",
  [aux_sym_column_not_null_token2] = "NULL",
  [aux_sym_create_function_token1] = "RETURNS",
  [aux_sym_create_function_token2] = "LANGUAGE",
  [aux_sym_data_type_name_token1] = "ASCII",
  [aux_sym_data_type_name_token2] = "BIGINT",
  [aux_sym_data_type_name_token3] = "BLOB",
  [aux_sym_data_type_name_token4] = "BOOLEAN",
  [aux_sym_data_type_name_token5] = "DATE",
  [aux_sym_data_type_name_token6] = "DECIMAL",
  [aux_sym_data_type_name_token7] = "DOUBLE",
  [aux_sym_data_type_name_token8] = "FLOAT",
  [aux_sym_data_type_name_token9] = "FROZEN",
  [aux_sym_data_type_name_token10] = "INET",
  [aux_sym_data_type_name_token11] = "INT",
  [aux_sym_data_type_name_token12] = "MAP",
  [aux_sym_data_type_name_token13] = "SMALLINT",
  [aux_sym_data_type_name_token14] = "TEXT",
  [aux_sym_data_type_name_token15] = "TIME",
  [aux_sym_data_type_name_token16] = "TIMEUUID",
  [aux_sym_data_type_name_token17] = "TINYINT",
  [aux_sym_data_type_name_token18] = "TUPLE",
  [aux_sym_data_type_name_token19] = "VARCHAR",
  [aux_sym_data_type_name_token20] = "VARINT",
  [aux_sym_data_type_name_token21] = "UUID",
  [aux_sym_return_mode_token1] = "CALLED",
  [aux_sym_return_mode_token2] = "INPUT",
  [aux_sym_create_keyspace_token1] = "WITH",
  [aux_sym_create_keyspace_token2] = "REPLICATION",
  [aux_sym_durable_writes_token1] = "DURABLE_WRITES",
  [aux_sym_role_with_option_token1] = "PASSWORD",
  [aux_sym_role_with_option_token2] = "LOGIN",
  [aux_sym_role_with_option_token3] = "SUPERUSER",
  [aux_sym_role_with_option_token4] = "OPTIONS",
  [aux_sym_primary_key_column_token1] = "PRIMARY",
  [aux_sym_compact_storage_token1] = "COMPACT",
  [aux_sym_compact_storage_token2] = "STORAGE",
  [aux_sym_clustering_order_token1] = "CLUSTERING",
  [aux_sym_user_super_user_token1] = "NOSUPERUSER",
  [aux_sym_alter_table_add_token1] = "ADD",
  [aux_sym_alter_table_rename_token1] = "RENAME",
  [aux_sym_apply_batch_token1] = "APPLY",
  [sym_object_name] = "object_name",
  [sym_source_file] = "source_file",
  [sym_comma_sep] = "comma_sep",
  [sym_dot_sep] = "dot_sep",
  [sym_semi_sep] = "semi_sep",
  [sym_single_quote] = "single_quote",
  [sym_escaped_single_quote] = "escaped_single_quote",
  [sym_double_quote] = "double_quote",
  [sym_escaped_double_quote] = "escaped_double_quote",
  [sym_unquoted_identifier] = "unquoted_identifier",
  [sym_quoted_identifier] = "quoted_identifier",
  [sym_identifier] = "identifier",
  [sym_string_literal] = "string_literal",
  [sym_integer] = "integer",
  [sym_decimal_fraction] = "decimal_fraction",
  [sym_standard_decimal_notation] = "standard_decimal_notation",
  [sym_scientific_notation] = "scientific_notation",
  [sym_float_literal] = "float_literal",
  [sym_boolean_literal] = "boolean_literal",
  [sym_constant] = "constant",
  [sym_term] = "term",
  [sym_function_name] = "function_name",
  [sym_function_args] = "function_args",
  [sym_function_call] = "function_call",
  [sym_arithmetic_operation] = "arithmetic_operation",
  [sym_bind_marker] = "bind_marker",
  [sym_map_key] = "map_key",
  [sym_map_value] = "map_value",
  [sym_map_entry] = "map_entry",
  [sym_map_literal] = "map_literal",
  [sym_set_literal] = "set_literal",
  [sym_list_literal] = "list_literal",
  [sym_assignment_tuple] = "assignment_tuple",
  [sym_keyspace_name] = "keyspace_name",
  [sym_table_name] = "table_name",
  [sym_table_expression] = "table_expression",
  [sym_column_name] = "column_name",
  [sym_from_spec] = "from_spec",
  [sym_select_element] = "select_element",
  [sym_select_expression] = "select_expression",
  [sym_select_statement] = "select_statement",
  [sym__statement] = "_statement",
  [sym_limit_spec] = "limit_spec",
  [sym__value_marker] = "_value_marker",
  [sym_where_spec] = "where_spec",
  [sym_relation_elements] = "relation_elements",
  [sym_relation_element] = "relation_element",
  [sym_relation_contains_key] = "relation_contains_key",
  [sym_relation_contains] = "relation_contains",
  [sym_order_spec] = "order_spec",
  [sym_delete_statement] = "delete_statement",
  [sym_begin_batch] = "begin_batch",
  [sym_delete_column_list] = "delete_column_list",
  [sym_delete_column_item] = "delete_column_item",
  [sym_using_timestamp_spec] = "using_timestamp_spec",
  [sym_if_spec] = "if_spec",
  [sym_insert_statement] = "insert_statement",
  [sym_insert_column_spec] = "insert_column_spec",
  [sym_column_list] = "column_list",
  [sym_insert_values_spec] = "insert_values_spec",
  [sym_expression_list] = "expression_list",
  [sym_expression] = "expression",
  [sym_using_ttl_timestamp] = "using_ttl_timestamp",
  [sym_truncate] = "truncate",
  [sym_create_index] = "create_index",
  [sym_index_column_spec] = "index_column_spec",
  [sym_index_keys_spec] = "index_keys_spec",
  [sym_index_entries_s_spec] = "index_entries_s_spec",
  [sym_index_full_spec] = "index_full_spec",
  [sym_drop_index] = "drop_index",
  [sym_update] = "update",
  [sym_update_assignments] = "update_assignments",
  [sym_assignment_element] = "assignment_element",
  [sym_indexed_column] = "indexed_column",
  [sym_use] = "use",
  [sym_grant] = "grant",
  [sym_revoke] = "revoke",
  [sym_privilege] = "privilege",
  [sym_resource] = "resource",
  [sym_list_roles] = "list_roles",
  [sym_list_permissions] = "list_permissions",
  [sym_drop_aggregate] = "drop_aggregate",
  [sym_drop_materialized_view] = "drop_materialized_view",
  [sym_drop_function] = "drop_function",
  [sym_drop_keyspace] = "drop_keyspace",
  [sym_drop_role] = "drop_role",
  [sym_drop_table] = "drop_table",
  [sym_drop_trigger] = "drop_trigger",
  [sym_drop_type] = "drop_type",
  [sym_drop_user] = "drop_user",
  [sym_create_aggregate] = "create_aggregate",
  [sym_init_cond_definition] = "init_cond_definition",
  [sym_init_cond_list] = "init_cond_list",
  [sym_init_cond_nested_list] = "init_cond_nested_list",
  [sym_init_cond_hash] = "init_cond_hash",
  [sym_init_cond_hash_item] = "init_cond_hash_item",
  [sym_create_materialized_view] = "create_materialized_view",
  [sym_materialized_view_where] = "materialized_view_where",
  [sym_column_not_null] = "column_not_null",
  [sym_create_function] = "create_function",
  [sym_data_type] = "data_type",
  [sym_data_type_name] = "data_type_name",
  [sym_data_type_definition] = "data_type_definition",
  [sym_return_mode] = "return_mode",
  [sym_create_keyspace] = "create_keyspace",
  [sym_replication_list_item] = "replication_list_item",
  [sym_durable_writes] = "durable_writes",
  [sym_create_role] = "create_role",
  [sym_role_with] = "role_with",
  [sym_role_with_option] = "role_with_option",
  [sym_option_hash] = "option_hash",
  [sym_option_hash_item] = "option_hash_item",
  [sym_create_table] = "create_table",
  [sym_column_definition_list] = "column_definition_list",
  [sym_column_definition] = "column_definition",
  [sym_primary_key_column] = "primary_key_column",
  [sym_primary_key_element] = "primary_key_element",
  [sym_primary_key_definition] = "primary_key_definition",
  [sym_compound_key] = "compound_key",
  [sym_clustering_key_list] = "clustering_key_list",
  [sym_composite_key] = "composite_key",
  [sym_partition_key_list] = "partition_key_list",
  [sym_with_element] = "with_element",
  [sym_table_options] = "table_options",
  [sym_table_option_item] = "table_option_item",
  [sym_table_option_name] = "table_option_name",
  [sym_table_option_value] = "table_option_value",
  [sym_compact_storage] = "compact_storage",
  [sym_clustering_order] = "clustering_order",
  [sym_create_trigger] = "create_trigger",
  [sym_trigger_class] = "trigger_class",
  [sym_create_type] = "create_type",
  [sym_typed_name] = "typed_name",
  [sym_create_user] = "create_user",
  [sym_user_with] = "user_with",
  [sym_user_password] = "user_password",
  [sym_user_super_user] = "user_super_user",
  [sym_alter_materialized_view] = "alter_materialized_view",
  [sym_alter_keyspace] = "alter_keyspace",
  [sym_replication_list] = "replication_list",
  [sym_alter_role] = "alter_role",
  [sym_alter_table] = "alter_table",
  [sym_alter_table_operation] = "alter_table_operation",
  [sym_alter_table_add] = "alter_table_add",
  [sym_alter_table_drop_columns] = "alter_table_drop_columns",
  [sym_alter_table_drop_compact_storage] = "alter_table_drop_compact_storage",
  [sym_alter_table_rename] = "alter_table_rename",
  [sym_alter_type] = "alter_type",
  [sym_alter_type_operation] = "alter_type_operation",
  [sym_alter_type_alter_type] = "alter_type_alter_type",
  [sym_alter_type_add] = "alter_type_add",
  [sym_alter_type_rename] = "alter_type_rename",
  [sym_alter_type_rename_item] = "alter_type_rename_item",
  [sym_alter_user] = "alter_user",
  [sym_apply_batch] = "apply_batch",
  [sym_aggregate_name] = "aggregate_name",
  [sym_short_index_name] = "short_index_name",
  [sym_index_name] = "index_name",
  [sym_materialized_view_name] = "materialized_view_name",
  [sym_role_name] = "role_name",
  [sym_trigger_name] = "trigger_name",
  [sym_type_name] = "type_name",
  [sym_user_name] = "user_name",
  [aux_sym_source_file_repeat1] = "source_file_repeat1",
  [aux_sym_unquoted_identifier_repeat1] = "unquoted_identifier_repeat1",
  [aux_sym_quoted_identifier_repeat1] = "quoted_identifier_repeat1",
  [aux_sym_string_literal_repeat1] = "string_literal_repeat1",
  [aux_sym_integer_repeat1] = "integer_repeat1",
  [aux_sym_function_args_repeat1] = "function_args_repeat1",
  [aux_sym_select_expression_repeat1] = "select_expression_repeat1",
  [aux_sym_relation_elements_repeat1] = "relation_elements_repeat1",
  [aux_sym_relation_element_repeat1] = "relation_element_repeat1",
  [aux_sym_relation_element_repeat2] = "relation_element_repeat2",
  [aux_sym_delete_column_list_repeat1] = "delete_column_list_repeat1",
  [aux_sym_expression_list_repeat1] = "expression_list_repeat1",
  [aux_sym_update_assignments_repeat1] = "update_assignments_repeat1",
  [aux_sym_init_cond_list_repeat1] = "init_cond_list_repeat1",
  [aux_sym_init_cond_nested_list_repeat1] = "init_cond_nested_list_repeat1",
  [aux_sym_init_cond_hash_repeat1] = "init_cond_hash_repeat1",
  [aux_sym_materialized_view_where_repeat1] = "materialized_view_where_repeat1",
  [aux_sym_create_function_repeat1] = "create_function_repeat1",
  [aux_sym_data_type_definition_repeat1] = "data_type_definition_repeat1",
  [aux_sym_role_with_repeat1] = "role_with_repeat1",
  [aux_sym_option_hash_repeat1] = "option_hash_repeat1",
  [aux_sym_column_definition_list_repeat1] = "column_definition_list_repeat1",
  [aux_sym_clustering_key_list_repeat1] = "clustering_key_list_repeat1",
  [aux_sym_table_options_repeat1] = "table_options_repeat1",
  [aux_sym_replication_list_repeat1] = "replication_list_repeat1",
  [aux_sym_alter_type_rename_repeat1] = "alter_type_rename_repeat1",
  [anon_alias_sym_aggregate] = "aggregate",
  [anon_alias_sym_assignment_operand] = "assignment_operand",
  [anon_alias_sym_column] = "column",
  [anon_alias_sym_entry] = "entry",
  [anon_alias_sym_finalfunc] = "finalfunc",
  [anon_alias_sym_full] = "full",
  [anon_alias_sym_function] = "function",
  [anon_alias_sym_hash_key] = "hash_key",
  [anon_alias_sym_index] = "index",
  [anon_alias_sym_key] = "key",
  [anon_alias_sym_keyspace] = "keyspace",
  [anon_alias_sym_language] = "language",
  [anon_alias_sym_limit_value] = "limit_value",
  [anon_alias_sym_login] = "login",
  [anon_alias_sym_materialized_view] = "materialized_view",
  [anon_alias_sym_partition_key] = "partition_key",
  [anon_alias_sym_password] = "password",
  [anon_alias_sym_primary_key] = "primary_key",
  [anon_alias_sym_role] = "role",
  [anon_alias_sym_sfunc] = "sfunc",
  [anon_alias_sym_table] = "table",
  [anon_alias_sym_trigger] = "trigger",
  [anon_alias_sym_ttl] = "ttl",
  [anon_alias_sym_type] = "type",
  [anon_alias_sym_user] = "user",
  [anon_alias_sym_value] = "value",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [anon_sym_COMMA] = anon_sym_COMMA,
  [anon_sym_DOT] = anon_sym_DOT,
  [anon_sym_SEMI] = anon_sym_SEMI,
  [anon_sym_SQUOTE] = anon_sym_SQUOTE,
  [anon_sym_DQUOTE] = anon_sym_DQUOTE,
  [sym_double_dollar] = sym_double_dollar,
  [aux_sym_unquoted_identifier_token1] = aux_sym_unquoted_identifier_token1,
  [anon_sym__] = anon_sym__,
  [aux_sym_unquoted_identifier_token2] = aux_sym_unquoted_identifier_token2,
  [aux_sym_quoted_identifier_token1] = aux_sym_quoted_identifier_token1,
  [aux_sym_string_literal_token1] = aux_sym_string_literal_token1,
  [aux_sym_string_literal_token2] = aux_sym_string_literal_token2,
  [anon_sym_DASH] = anon_sym_DASH,
  [sym_nan] = sym_nan,
  [sym_infinity] = sym_infinity,
  [sym_scientific_notation_exponent] = sym_scientific_notation_exponent,
  [aux_sym_scientific_notation_token1] = aux_sym_scientific_notation_token1,
  [sym_true_literal] = sym_true_literal,
  [sym_false_literal] = sym_false_literal,
  [sym_uuid_literal] = sym_uuid_literal,
  [sym_blob_literal] = sym_blob_literal,
  [sym_null_literal] = sym_null_literal,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [sym_arithmetic_operator] = sym_arithmetic_operator,
  [aux_sym_arithmetic_operation_token1] = aux_sym_arithmetic_operation_token1,
  [anon_sym_QMARK] = anon_sym_QMARK,
  [anon_sym_COLON] = anon_sym_COLON,
  [anon_sym_LT] = anon_sym_LT,
  [anon_sym_GT] = anon_sym_GT,
  [anon_sym_LBRACE] = anon_sym_LBRACE,
  [anon_sym_RBRACE] = anon_sym_RBRACE,
  [anon_sym_LBRACK] = anon_sym_LBRACK,
  [anon_sym_RBRACK] = anon_sym_RBRACK,
  [sym_column_glob] = sym_column_glob,
  [aux_sym_from_spec_token1] = aux_sym_from_spec_token1,
  [aux_sym_select_statement_token1] = aux_sym_select_statement_token1,
  [aux_sym_select_statement_token2] = aux_sym_select_statement_token2,
  [aux_sym_select_statement_token3] = aux_sym_select_statement_token3,
  [aux_sym_select_statement_token4] = aux_sym_select_statement_token4,
  [aux_sym_select_statement_token5] = aux_sym_select_statement_token5,
  [aux_sym_limit_spec_token1] = aux_sym_limit_spec_token1,
  [sym__code_block] = sym__code_block,
  [aux_sym_where_spec_token1] = aux_sym_where_spec_token1,
  [aux_sym_relation_elements_token1] = aux_sym_relation_elements_token1,
  [anon_sym_LT_EQ] = anon_sym_LT_EQ,
  [anon_sym_LT_GT] = anon_sym_LT_GT,
  [anon_sym_EQ] = anon_sym_EQ,
  [anon_sym_GT_EQ] = anon_sym_GT_EQ,
  [aux_sym_relation_element_token1] = aux_sym_relation_element_token1,
  [aux_sym_relation_contains_key_token1] = aux_sym_relation_contains_key_token1,
  [aux_sym_relation_contains_key_token2] = aux_sym_relation_contains_key_token2,
  [aux_sym_order_spec_token1] = aux_sym_order_spec_token1,
  [aux_sym_order_spec_token2] = aux_sym_order_spec_token2,
  [aux_sym_order_spec_token3] = aux_sym_order_spec_token3,
  [aux_sym_order_spec_token4] = aux_sym_order_spec_token4,
  [aux_sym_delete_statement_token1] = aux_sym_delete_statement_token1,
  [aux_sym_delete_statement_token2] = aux_sym_delete_statement_token2,
  [aux_sym_delete_statement_token3] = aux_sym_delete_statement_token3,
  [aux_sym_begin_batch_token1] = aux_sym_begin_batch_token1,
  [aux_sym_begin_batch_token2] = aux_sym_begin_batch_token2,
  [aux_sym_begin_batch_token3] = aux_sym_begin_batch_token3,
  [aux_sym_begin_batch_token4] = aux_sym_begin_batch_token4,
  [aux_sym_begin_batch_token5] = aux_sym_begin_batch_token5,
  [aux_sym_using_timestamp_spec_token1] = aux_sym_using_timestamp_spec_token1,
  [aux_sym_using_timestamp_spec_token2] = aux_sym_using_timestamp_spec_token2,
  [aux_sym_using_timestamp_spec_token3] = aux_sym_using_timestamp_spec_token3,
  [aux_sym_insert_statement_token1] = aux_sym_insert_statement_token1,
  [aux_sym_insert_statement_token2] = aux_sym_insert_statement_token2,
  [aux_sym_insert_statement_token3] = aux_sym_insert_statement_token3,
  [aux_sym_insert_values_spec_token1] = aux_sym_insert_values_spec_token1,
  [aux_sym_using_ttl_timestamp_token1] = aux_sym_using_ttl_timestamp_token1,
  [aux_sym_truncate_token1] = aux_sym_truncate_token1,
  [aux_sym_truncate_token2] = aux_sym_truncate_token2,
  [aux_sym_create_index_token1] = aux_sym_create_index_token1,
  [aux_sym_create_index_token2] = aux_sym_create_index_token2,
  [aux_sym_create_index_token3] = aux_sym_create_index_token3,
  [aux_sym_index_keys_spec_token1] = aux_sym_index_keys_spec_token1,
  [aux_sym_index_entries_s_spec_token1] = aux_sym_index_entries_s_spec_token1,
  [aux_sym_index_full_spec_token1] = aux_sym_index_full_spec_token1,
  [aux_sym_drop_index_token1] = aux_sym_drop_index_token1,
  [aux_sym_update_token1] = aux_sym_update_token1,
  [aux_sym_update_assignments_token1] = aux_sym_update_assignments_token1,
  [aux_sym_use_token1] = aux_sym_use_token1,
  [aux_sym_grant_token1] = aux_sym_grant_token1,
  [aux_sym_grant_token2] = aux_sym_grant_token2,
  [aux_sym_revoke_token1] = aux_sym_revoke_token1,
  [aux_sym_privilege_token1] = aux_sym_privilege_token1,
  [aux_sym_privilege_token2] = aux_sym_privilege_token2,
  [aux_sym_privilege_token3] = aux_sym_privilege_token3,
  [aux_sym_privilege_token4] = aux_sym_privilege_token4,
  [aux_sym_privilege_token5] = aux_sym_privilege_token5,
  [aux_sym_privilege_token6] = aux_sym_privilege_token6,
  [aux_sym_privilege_token7] = aux_sym_privilege_token7,
  [aux_sym_resource_token1] = aux_sym_resource_token1,
  [aux_sym_resource_token2] = aux_sym_resource_token2,
  [aux_sym_resource_token3] = aux_sym_resource_token3,
  [aux_sym_resource_token4] = aux_sym_resource_token4,
  [aux_sym_resource_token5] = aux_sym_resource_token5,
  [aux_sym_resource_token6] = aux_sym_resource_token6,
  [aux_sym_list_roles_token1] = aux_sym_list_roles_token1,
  [aux_sym_list_roles_token2] = aux_sym_list_roles_token2,
  [aux_sym_list_roles_token3] = aux_sym_list_roles_token3,
  [aux_sym_drop_aggregate_token1] = aux_sym_drop_aggregate_token1,
  [aux_sym_drop_materialized_view_token1] = aux_sym_drop_materialized_view_token1,
  [aux_sym_drop_materialized_view_token2] = aux_sym_drop_materialized_view_token2,
  [aux_sym_drop_trigger_token1] = aux_sym_drop_trigger_token1,
  [aux_sym_drop_type_token1] = aux_sym_drop_type_token1,
  [aux_sym_drop_user_token1] = aux_sym_drop_user_token1,
  [aux_sym_create_aggregate_token1] = aux_sym_create_aggregate_token1,
  [aux_sym_create_aggregate_token2] = aux_sym_create_aggregate_token2,
  [aux_sym_create_aggregate_token3] = aux_sym_create_aggregate_token3,
  [aux_sym_create_aggregate_token4] = aux_sym_create_aggregate_token4,
  [aux_sym_create_aggregate_token5] = aux_sym_create_aggregate_token5,
  [aux_sym_create_aggregate_token6] = aux_sym_create_aggregate_token6,
  [aux_sym_create_materialized_view_token1] = aux_sym_create_materialized_view_token1,
  [aux_sym_column_not_null_token1] = aux_sym_column_not_null_token1,
  [aux_sym_column_not_null_token2] = aux_sym_column_not_null_token2,
  [aux_sym_create_function_token1] = aux_sym_create_function_token1,
  [aux_sym_create_function_token2] = aux_sym_create_function_token2,
  [aux_sym_data_type_name_token1] = aux_sym_data_type_name_token1,
  [aux_sym_data_type_name_token2] = aux_sym_data_type_name_token2,
  [aux_sym_data_type_name_token3] = aux_sym_data_type_name_token3,
  [aux_sym_data_type_name_token4] = aux_sym_data_type_name_token4,
  [aux_sym_data_type_name_token5] = aux_sym_data_type_name_token5,
  [aux_sym_data_type_name_token6] = aux_sym_data_type_name_token6,
  [aux_sym_data_type_name_token7] = aux_sym_data_type_name_token7,
  [aux_sym_data_type_name_token8] = aux_sym_data_type_name_token8,
  [aux_sym_data_type_name_token9] = aux_sym_data_type_name_token9,
  [aux_sym_data_type_name_token10] = aux_sym_data_type_name_token10,
  [aux_sym_data_type_name_token11] = aux_sym_data_type_name_token11,
  [aux_sym_data_type_name_token12] = aux_sym_data_type_name_token12,
  [aux_sym_data_type_name_token13] = aux_sym_data_type_name_token13,
  [aux_sym_data_type_name_token14] = aux_sym_data_type_name_token14,
  [aux_sym_data_type_name_token15] = aux_sym_data_type_name_token15,
  [aux_sym_data_type_name_token16] = aux_sym_data_type_name_token16,
  [aux_sym_data_type_name_token17] = aux_sym_data_type_name_token17,
  [aux_sym_data_type_name_token18] = aux_sym_data_type_name_token18,
  [aux_sym_data_type_name_token19] = aux_sym_data_type_name_token19,
  [aux_sym_data_type_name_token20] = aux_sym_data_type_name_token20,
  [aux_sym_data_type_name_token21] = aux_sym_data_type_name_token21,
  [aux_sym_return_mode_token1] = aux_sym_return_mode_token1,
  [aux_sym_return_mode_token2] = aux_sym_return_mode_token2,
  [aux_sym_create_keyspace_token1] = aux_sym_create_keyspace_token1,
  [aux_sym_create_keyspace_token2] = aux_sym_create_keyspace_token2,
  [aux_sym_durable_writes_token1] = aux_sym_durable_writes_token1,
  [aux_sym_role_with_option_token1] = aux_sym_role_with_option_token1,
  [aux_sym_role_with_option_token2] = aux_sym_role_with_option_token2,
  [aux_sym_role_with_option_token3] = aux_sym_role_with_option_token3,
  [aux_sym_role_with_option_token4] = aux_sym_role_with_option_token4,
  [aux_sym_primary_key_column_token1] = aux_sym_primary_key_column_token1,
  [aux_sym_compact_storage_token1] = aux_sym_compact_storage_token1,
  [aux_sym_compact_storage_token2] = aux_sym_compact_storage_token2,
  [aux_sym_clustering_order_token1] = aux_sym_clustering_order_token1,
  [aux_sym_user_super_user_token1] = aux_sym_user_super_user_token1,
  [aux_sym_alter_table_add_token1] = aux_sym_alter_table_add_token1,
  [aux_sym_alter_table_rename_token1] = aux_sym_alter_table_rename_token1,
  [aux_sym_apply_batch_token1] = aux_sym_apply_batch_token1,
  [sym_object_name] = sym_object_name,
  [sym_source_file] = sym_source_file,
  [sym_comma_sep] = sym_comma_sep,
  [sym_dot_sep] = sym_dot_sep,
  [sym_semi_sep] = sym_semi_sep,
  [sym_single_quote] = sym_single_quote,
  [sym_escaped_single_quote] = sym_escaped_single_quote,
  [sym_double_quote] = sym_double_quote,
  [sym_escaped_double_quote] = sym_escaped_double_quote,
  [sym_unquoted_identifier] = sym_unquoted_identifier,
  [sym_quoted_identifier] = sym_quoted_identifier,
  [sym_identifier] = sym_identifier,
  [sym_string_literal] = sym_string_literal,
  [sym_integer] = sym_integer,
  [sym_decimal_fraction] = sym_decimal_fraction,
  [sym_standard_decimal_notation] = sym_standard_decimal_notation,
  [sym_scientific_notation] = sym_scientific_notation,
  [sym_float_literal] = sym_float_literal,
  [sym_boolean_literal] = sym_boolean_literal,
  [sym_constant] = sym_constant,
  [sym_term] = sym_term,
  [sym_function_name] = sym_function_name,
  [sym_function_args] = sym_function_args,
  [sym_function_call] = sym_function_call,
  [sym_arithmetic_operation] = sym_arithmetic_operation,
  [sym_bind_marker] = sym_bind_marker,
  [sym_map_key] = sym_map_key,
  [sym_map_value] = sym_map_value,
  [sym_map_entry] = sym_map_entry,
  [sym_map_literal] = sym_map_literal,
  [sym_set_literal] = sym_set_literal,
  [sym_list_literal] = sym_list_literal,
  [sym_assignment_tuple] = sym_assignment_tuple,
  [sym_keyspace_name] = sym_keyspace_name,
  [sym_table_name] = sym_table_name,
  [sym_table_expression] = sym_table_expression,
  [sym_column_name] = sym_column_name,
  [sym_from_spec] = sym_from_spec,
  [sym_select_element] = sym_select_element,
  [sym_select_expression] = sym_select_expression,
  [sym_select_statement] = sym_select_statement,
  [sym__statement] = sym__statement,
  [sym_limit_spec] = sym_limit_spec,
  [sym__value_marker] = sym__value_marker,
  [sym_where_spec] = sym_where_spec,
  [sym_relation_elements] = sym_relation_elements,
  [sym_relation_element] = sym_relation_element,
  [sym_relation_contains_key] = sym_relation_contains_key,
  [sym_relation_contains] = sym_relation_contains,
  [sym_order_spec] = sym_order_spec,
  [sym_delete_statement] = sym_delete_statement,
  [sym_begin_batch] = sym_begin_batch,
  [sym_delete_column_list] = sym_delete_column_list,
  [sym_delete_column_item] = sym_delete_column_item,
  [sym_using_timestamp_spec] = sym_using_timestamp_spec,
  [sym_if_spec] = sym_if_spec,
  [sym_insert_statement] = sym_insert_statement,
  [sym_insert_column_spec] = sym_insert_column_spec,
  [sym_column_list] = sym_column_list,
  [sym_insert_values_spec] = sym_insert_values_spec,
  [sym_expression_list] = sym_expression_list,
  [sym_expression] = sym_expression,
  [sym_using_ttl_timestamp] = sym_using_ttl_timestamp,
  [sym_truncate] = sym_truncate,
  [sym_create_index] = sym_create_index,
  [sym_index_column_spec] = sym_index_column_spec,
  [sym_index_keys_spec] = sym_index_keys_spec,
  [sym_index_entries_s_spec] = sym_index_entries_s_spec,
  [sym_index_full_spec] = sym_index_full_spec,
  [sym_drop_index] = sym_drop_index,
  [sym_update] = sym_update,
  [sym_update_assignments] = sym_update_assignments,
  [sym_assignment_element] = sym_assignment_element,
  [sym_indexed_column] = sym_indexed_column,
  [sym_use] = sym_use,
  [sym_grant] = sym_grant,
  [sym_revoke] = sym_revoke,
  [sym_privilege] = sym_privilege,
  [sym_resource] = sym_resource,
  [sym_list_roles] = sym_list_roles,
  [sym_list_permissions] = sym_list_permissions,
  [sym_drop_aggregate] = sym_drop_aggregate,
  [sym_drop_materialized_view] = sym_drop_materialized_view,
  [sym_drop_function] = sym_drop_function,
  [sym_drop_keyspace] = sym_drop_keyspace,
  [sym_drop_role] = sym_drop_role,
  [sym_drop_table] = sym_drop_table,
  [sym_drop_trigger] = sym_drop_trigger,
  [sym_drop_type] = sym_drop_type,
  [sym_drop_user] = sym_drop_user,
  [sym_create_aggregate] = sym_create_aggregate,
  [sym_init_cond_definition] = sym_init_cond_definition,
  [sym_init_cond_list] = sym_init_cond_list,
  [sym_init_cond_nested_list] = sym_init_cond_nested_list,
  [sym_init_cond_hash] = sym_init_cond_hash,
  [sym_init_cond_hash_item] = sym_init_cond_hash_item,
  [sym_create_materialized_view] = sym_create_materialized_view,
  [sym_materialized_view_where] = sym_materialized_view_where,
  [sym_column_not_null] = sym_column_not_null,
  [sym_create_function] = sym_create_function,
  [sym_data_type] = sym_data_type,
  [sym_data_type_name] = sym_data_type_name,
  [sym_data_type_definition] = sym_data_type_definition,
  [sym_return_mode] = sym_return_mode,
  [sym_create_keyspace] = sym_create_keyspace,
  [sym_replication_list_item] = sym_replication_list_item,
  [sym_durable_writes] = sym_durable_writes,
  [sym_create_role] = sym_create_role,
  [sym_role_with] = sym_role_with,
  [sym_role_with_option] = sym_role_with_option,
  [sym_option_hash] = sym_option_hash,
  [sym_option_hash_item] = sym_option_hash_item,
  [sym_create_table] = sym_create_table,
  [sym_column_definition_list] = sym_column_definition_list,
  [sym_column_definition] = sym_column_definition,
  [sym_primary_key_column] = sym_primary_key_column,
  [sym_primary_key_element] = sym_primary_key_element,
  [sym_primary_key_definition] = sym_primary_key_definition,
  [sym_compound_key] = sym_compound_key,
  [sym_clustering_key_list] = sym_clustering_key_list,
  [sym_composite_key] = sym_composite_key,
  [sym_partition_key_list] = sym_partition_key_list,
  [sym_with_element] = sym_with_element,
  [sym_table_options] = sym_table_options,
  [sym_table_option_item] = sym_table_option_item,
  [sym_table_option_name] = sym_table_option_name,
  [sym_table_option_value] = sym_table_option_value,
  [sym_compact_storage] = sym_compact_storage,
  [sym_clustering_order] = sym_clustering_order,
  [sym_create_trigger] = sym_create_trigger,
  [sym_trigger_class] = sym_trigger_class,
  [sym_create_type] = sym_create_type,
  [sym_typed_name] = sym_typed_name,
  [sym_create_user] = sym_create_user,
  [sym_user_with] = sym_user_with,
  [sym_user_password] = sym_user_password,
  [sym_user_super_user] = sym_user_super_user,
  [sym_alter_materialized_view] = sym_alter_materialized_view,
  [sym_alter_keyspace] = sym_alter_keyspace,
  [sym_replication_list] = sym_replication_list,
  [sym_alter_role] = sym_alter_role,
  [sym_alter_table] = sym_alter_table,
  [sym_alter_table_operation] = sym_alter_table_operation,
  [sym_alter_table_add] = sym_alter_table_add,
  [sym_alter_table_drop_columns] = sym_alter_table_drop_columns,
  [sym_alter_table_drop_compact_storage] = sym_alter_table_drop_compact_storage,
  [sym_alter_table_rename] = sym_alter_table_rename,
  [sym_alter_type] = sym_alter_type,
  [sym_alter_type_operation] = sym_alter_type_operation,
  [sym_alter_type_alter_type] = sym_alter_type_alter_type,
  [sym_alter_type_add] = sym_alter_type_add,
  [sym_alter_type_rename] = sym_alter_type_rename,
  [sym_alter_type_rename_item] = sym_alter_type_rename_item,
  [sym_alter_user] = sym_alter_user,
  [sym_apply_batch] = sym_apply_batch,
  [sym_aggregate_name] = sym_aggregate_name,
  [sym_short_index_name] = sym_short_index_name,
  [sym_index_name] = sym_index_name,
  [sym_materialized_view_name] = sym_materialized_view_name,
  [sym_role_name] = sym_role_name,
  [sym_trigger_name] = sym_trigger_name,
  [sym_type_name] = sym_type_name,
  [sym_user_name] = sym_user_name,
  [aux_sym_source_file_repeat1] = aux_sym_source_file_repeat1,
  [aux_sym_unquoted_identifier_repeat1] = aux_sym_unquoted_identifier_repeat1,
  [aux_sym_quoted_identifier_repeat1] = aux_sym_quoted_identifier_repeat1,
  [aux_sym_string_literal_repeat1] = aux_sym_string_literal_repeat1,
  [aux_sym_integer_repeat1] = aux_sym_integer_repeat1,
  [aux_sym_function_args_repeat1] = aux_sym_function_args_repeat1,
  [aux_sym_select_expression_repeat1] = aux_sym_select_expression_repeat1,
  [aux_sym_relation_elements_repeat1] = aux_sym_relation_elements_repeat1,
  [aux_sym_relation_element_repeat1] = aux_sym_relation_element_repeat1,
  [aux_sym_relation_element_repeat2] = aux_sym_relation_element_repeat2,
  [aux_sym_delete_column_list_repeat1] = aux_sym_delete_column_list_repeat1,
  [aux_sym_expression_list_repeat1] = aux_sym_expression_list_repeat1,
  [aux_sym_update_assignments_repeat1] = aux_sym_update_assignments_repeat1,
  [aux_sym_init_cond_list_repeat1] = aux_sym_init_cond_list_repeat1,
  [aux_sym_init_cond_nested_list_repeat1] = aux_sym_init_cond_nested_list_repeat1,
  [aux_sym_init_cond_hash_repeat1] = aux_sym_init_cond_hash_repeat1,
  [aux_sym_materialized_view_where_repeat1] = aux_sym_materialized_view_where_repeat1,
  [aux_sym_create_function_repeat1] = aux_sym_create_function_repeat1,
  [aux_sym_data_type_definition_repeat1] = aux_sym_data_type_definition_repeat1,
  [aux_sym_role_with_repeat1] = aux_sym_role_with_repeat1,
  [aux_sym_option_hash_repeat1] = aux_sym_option_hash_repeat1,
  [aux_sym_column_definition_list_repeat1] = aux_sym_column_definition_list_repeat1,
  [aux_sym_clustering_key_list_repeat1] = aux_sym_clustering_key_list_repeat1,
  [aux_sym_table_options_repeat1] = aux_sym_table_options_repeat1,
  [aux_sym_replication_list_repeat1] = aux_sym_replication_list_repeat1,
  [aux_sym_alter_type_rename_repeat1] = aux_sym_alter_type_rename_repeat1,
  [anon_alias_sym_aggregate] = anon_alias_sym_aggregate,
  [anon_alias_sym_assignment_operand] = anon_alias_sym_assignment_operand,
  [anon_alias_sym_column] = anon_alias_sym_column,
  [anon_alias_sym_entry] = anon_alias_sym_entry,
  [anon_alias_sym_finalfunc] = anon_alias_sym_finalfunc,
  [anon_alias_sym_full] = anon_alias_sym_full,
  [anon_alias_sym_function] = anon_alias_sym_function,
  [anon_alias_sym_hash_key] = anon_alias_sym_hash_key,
  [anon_alias_sym_index] = anon_alias_sym_index,
  [anon_alias_sym_key] = anon_alias_sym_key,
  [anon_alias_sym_keyspace] = anon_alias_sym_keyspace,
  [anon_alias_sym_language] = anon_alias_sym_language,
  [anon_alias_sym_limit_value] = anon_alias_sym_limit_value,
  [anon_alias_sym_login] = anon_alias_sym_login,
  [anon_alias_sym_materialized_view] = anon_alias_sym_materialized_view,
  [anon_alias_sym_partition_key] = anon_alias_sym_partition_key,
  [anon_alias_sym_password] = anon_alias_sym_password,
  [anon_alias_sym_primary_key] = anon_alias_sym_primary_key,
  [anon_alias_sym_role] = anon_alias_sym_role,
  [anon_alias_sym_sfunc] = anon_alias_sym_sfunc,
  [anon_alias_sym_table] = anon_alias_sym_table,
  [anon_alias_sym_trigger] = anon_alias_sym_trigger,
  [anon_alias_sym_ttl] = anon_alias_sym_ttl,
  [anon_alias_sym_type] = anon_alias_sym_type,
  [anon_alias_sym_user] = anon_alias_sym_user,
  [anon_alias_sym_value] = anon_alias_sym_value,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [anon_sym_COMMA] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DOT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SEMI] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SQUOTE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DQUOTE] = {
    .visible = true,
    .named = false,
  },
  [sym_double_dollar] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_unquoted_identifier_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym__] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_unquoted_identifier_token2] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_quoted_identifier_token1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_string_literal_token1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_string_literal_token2] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_DASH] = {
    .visible = true,
    .named = false,
  },
  [sym_nan] = {
    .visible = true,
    .named = true,
  },
  [sym_infinity] = {
    .visible = true,
    .named = true,
  },
  [sym_scientific_notation_exponent] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_scientific_notation_token1] = {
    .visible = false,
    .named = false,
  },
  [sym_true_literal] = {
    .visible = true,
    .named = true,
  },
  [sym_false_literal] = {
    .visible = true,
    .named = true,
  },
  [sym_uuid_literal] = {
    .visible = true,
    .named = true,
  },
  [sym_blob_literal] = {
    .visible = true,
    .named = true,
  },
  [sym_null_literal] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_LPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RPAREN] = {
    .visible = true,
    .named = false,
  },
  [sym_arithmetic_operator] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_arithmetic_operation_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_QMARK] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COLON] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_GT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LBRACK] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RBRACK] = {
    .visible = true,
    .named = false,
  },
  [sym_column_glob] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_from_spec_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_select_statement_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_select_statement_token2] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_select_statement_token3] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_select_statement_token4] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_select_statement_token5] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_limit_spec_token1] = {
    .visible = true,
    .named = false,
  },
  [sym__code_block] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_where_spec_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_relation_elements_token1] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LT_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LT_GT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_GT_EQ] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_relation_element_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_relation_contains_key_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_relation_contains_key_token2] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_order_spec_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_order_spec_token2] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_order_spec_token3] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_order_spec_token4] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_delete_statement_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_delete_statement_token2] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_delete_statement_token3] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_begin_batch_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_begin_batch_token2] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_begin_batch_token3] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_begin_batch_token4] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_begin_batch_token5] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_using_timestamp_spec_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_using_timestamp_spec_token2] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_using_timestamp_spec_token3] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_insert_statement_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_insert_statement_token2] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_insert_statement_token3] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_insert_values_spec_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_using_ttl_timestamp_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_truncate_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_truncate_token2] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_create_index_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_create_index_token2] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_create_index_token3] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_index_keys_spec_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_index_entries_s_spec_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_index_full_spec_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_drop_index_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_update_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_update_assignments_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_use_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_grant_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_grant_token2] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_revoke_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_privilege_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_privilege_token2] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_privilege_token3] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_privilege_token4] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_privilege_token5] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_privilege_token6] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_privilege_token7] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_resource_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_resource_token2] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_resource_token3] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_resource_token4] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_resource_token5] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_resource_token6] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_list_roles_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_list_roles_token2] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_list_roles_token3] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_drop_aggregate_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_drop_materialized_view_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_drop_materialized_view_token2] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_drop_trigger_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_drop_type_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_drop_user_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_create_aggregate_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_create_aggregate_token2] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_create_aggregate_token3] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_create_aggregate_token4] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_create_aggregate_token5] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_create_aggregate_token6] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_create_materialized_view_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_column_not_null_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_column_not_null_token2] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_create_function_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_create_function_token2] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_data_type_name_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_data_type_name_token2] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_data_type_name_token3] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_data_type_name_token4] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_data_type_name_token5] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_data_type_name_token6] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_data_type_name_token7] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_data_type_name_token8] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_data_type_name_token9] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_data_type_name_token10] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_data_type_name_token11] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_data_type_name_token12] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_data_type_name_token13] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_data_type_name_token14] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_data_type_name_token15] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_data_type_name_token16] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_data_type_name_token17] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_data_type_name_token18] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_data_type_name_token19] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_data_type_name_token20] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_data_type_name_token21] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_return_mode_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_return_mode_token2] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_create_keyspace_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_create_keyspace_token2] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_durable_writes_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_role_with_option_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_role_with_option_token2] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_role_with_option_token3] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_role_with_option_token4] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_primary_key_column_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_compact_storage_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_compact_storage_token2] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_clustering_order_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_user_super_user_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_alter_table_add_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_alter_table_rename_token1] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_apply_batch_token1] = {
    .visible = true,
    .named = false,
  },
  [sym_object_name] = {
    .visible = true,
    .named = true,
  },
  [sym_source_file] = {
    .visible = true,
    .named = true,
  },
  [sym_comma_sep] = {
    .visible = true,
    .named = true,
  },
  [sym_dot_sep] = {
    .visible = true,
    .named = true,
  },
  [sym_semi_sep] = {
    .visible = true,
    .named = true,
  },
  [sym_single_quote] = {
    .visible = true,
    .named = true,
  },
  [sym_escaped_single_quote] = {
    .visible = true,
    .named = true,
  },
  [sym_double_quote] = {
    .visible = true,
    .named = true,
  },
  [sym_escaped_double_quote] = {
    .visible = true,
    .named = true,
  },
  [sym_unquoted_identifier] = {
    .visible = true,
    .named = true,
  },
  [sym_quoted_identifier] = {
    .visible = true,
    .named = true,
  },
  [sym_identifier] = {
    .visible = true,
    .named = true,
  },
  [sym_string_literal] = {
    .visible = true,
    .named = true,
  },
  [sym_integer] = {
    .visible = true,
    .named = true,
  },
  [sym_decimal_fraction] = {
    .visible = true,
    .named = true,
  },
  [sym_standard_decimal_notation] = {
    .visible = true,
    .named = true,
  },
  [sym_scientific_notation] = {
    .visible = true,
    .named = true,
  },
  [sym_float_literal] = {
    .visible = true,
    .named = true,
  },
  [sym_boolean_literal] = {
    .visible = true,
    .named = true,
  },
  [sym_constant] = {
    .visible = true,
    .named = true,
  },
  [sym_term] = {
    .visible = true,
    .named = true,
  },
  [sym_function_name] = {
    .visible = true,
    .named = true,
  },
  [sym_function_args] = {
    .visible = true,
    .named = true,
  },
  [sym_function_call] = {
    .visible = true,
    .named = true,
  },
  [sym_arithmetic_operation] = {
    .visible = true,
    .named = true,
  },
  [sym_bind_marker] = {
    .visible = true,
    .named = true,
  },
  [sym_map_key] = {
    .visible = true,
    .named = true,
  },
  [sym_map_value] = {
    .visible = true,
    .named = true,
  },
  [sym_map_entry] = {
    .visible = true,
    .named = true,
  },
  [sym_map_literal] = {
    .visible = true,
    .named = true,
  },
  [sym_set_literal] = {
    .visible = true,
    .named = true,
  },
  [sym_list_literal] = {
    .visible = true,
    .named = true,
  },
  [sym_assignment_tuple] = {
    .visible = true,
    .named = true,
  },
  [sym_keyspace_name] = {
    .visible = true,
    .named = true,
  },
  [sym_table_name] = {
    .visible = true,
    .named = true,
  },
  [sym_table_expression] = {
    .visible = true,
    .named = true,
  },
  [sym_column_name] = {
    .visible = true,
    .named = true,
  },
  [sym_from_spec] = {
    .visible = true,
    .named = true,
  },
  [sym_select_element] = {
    .visible = true,
    .named = true,
  },
  [sym_select_expression] = {
    .visible = true,
    .named = true,
  },
  [sym_select_statement] = {
    .visible = true,
    .named = true,
  },
  [sym__statement] = {
    .visible = false,
    .named = true,
  },
  [sym_limit_spec] = {
    .visible = true,
    .named = true,
  },
  [sym__value_marker] = {
    .visible = false,
    .named = true,
  },
  [sym_where_spec] = {
    .visible = true,
    .named = true,
  },
  [sym_relation_elements] = {
    .visible = true,
    .named = true,
  },
  [sym_relation_element] = {
    .visible = true,
    .named = true,
  },
  [sym_relation_contains_key] = {
    .visible = true,
    .named = true,
  },
  [sym_relation_contains] = {
    .visible = true,
    .named = true,
  },
  [sym_order_spec] = {
    .visible = true,
    .named = true,
  },
  [sym_delete_statement] = {
    .visible = true,
    .named = true,
  },
  [sym_begin_batch] = {
    .visible = true,
    .named = true,
  },
  [sym_delete_column_list] = {
    .visible = true,
    .named = true,
  },
  [sym_delete_column_item] = {
    .visible = true,
    .named = true,
  },
  [sym_using_timestamp_spec] = {
    .visible = true,
    .named = true,
  },
  [sym_if_spec] = {
    .visible = true,
    .named = true,
  },
  [sym_insert_statement] = {
    .visible = true,
    .named = true,
  },
  [sym_insert_column_spec] = {
    .visible = true,
    .named = true,
  },
  [sym_column_list] = {
    .visible = true,
    .named = true,
  },
  [sym_insert_values_spec] = {
    .visible = true,
    .named = true,
  },
  [sym_expression_list] = {
    .visible = true,
    .named = true,
  },
  [sym_expression] = {
    .visible = true,
    .named = true,
  },
  [sym_using_ttl_timestamp] = {
    .visible = true,
    .named = true,
  },
  [sym_truncate] = {
    .visible = true,
    .named = true,
  },
  [sym_create_index] = {
    .visible = true,
    .named = true,
  },
  [sym_index_column_spec] = {
    .visible = true,
    .named = true,
  },
  [sym_index_keys_spec] = {
    .visible = true,
    .named = true,
  },
  [sym_index_entries_s_spec] = {
    .visible = true,
    .named = true,
  },
  [sym_index_full_spec] = {
    .visible = true,
    .named = true,
  },
  [sym_drop_index] = {
    .visible = true,
    .named = true,
  },
  [sym_update] = {
    .visible = true,
    .named = true,
  },
  [sym_update_assignments] = {
    .visible = true,
    .named = true,
  },
  [sym_assignment_element] = {
    .visible = true,
    .named = true,
  },
  [sym_indexed_column] = {
    .visible = true,
    .named = true,
  },
  [sym_use] = {
    .visible = true,
    .named = true,
  },
  [sym_grant] = {
    .visible = true,
    .named = true,
  },
  [sym_revoke] = {
    .visible = true,
    .named = true,
  },
  [sym_privilege] = {
    .visible = true,
    .named = true,
  },
  [sym_resource] = {
    .visible = true,
    .named = true,
  },
  [sym_list_roles] = {
    .visible = true,
    .named = true,
  },
  [sym_list_permissions] = {
    .visible = true,
    .named = true,
  },
  [sym_drop_aggregate] = {
    .visible = true,
    .named = true,
  },
  [sym_drop_materialized_view] = {
    .visible = true,
    .named = true,
  },
  [sym_drop_function] = {
    .visible = true,
    .named = true,
  },
  [sym_drop_keyspace] = {
    .visible = true,
    .named = true,
  },
  [sym_drop_role] = {
    .visible = true,
    .named = true,
  },
  [sym_drop_table] = {
    .visible = true,
    .named = true,
  },
  [sym_drop_trigger] = {
    .visible = true,
    .named = true,
  },
  [sym_drop_type] = {
    .visible = true,
    .named = true,
  },
  [sym_drop_user] = {
    .visible = true,
    .named = true,
  },
  [sym_create_aggregate] = {
    .visible = true,
    .named = true,
  },
  [sym_init_cond_definition] = {
    .visible = true,
    .named = true,
  },
  [sym_init_cond_list] = {
    .visible = true,
    .named = true,
  },
  [sym_init_cond_nested_list] = {
    .visible = true,
    .named = true,
  },
  [sym_init_cond_hash] = {
    .visible = true,
    .named = true,
  },
  [sym_init_cond_hash_item] = {
    .visible = true,
    .named = true,
  },
  [sym_create_materialized_view] = {
    .visible = true,
    .named = true,
  },
  [sym_materialized_view_where] = {
    .visible = true,
    .named = true,
  },
  [sym_column_not_null] = {
    .visible = true,
    .named = true,
  },
  [sym_create_function] = {
    .visible = true,
    .named = true,
  },
  [sym_data_type] = {
    .visible = true,
    .named = true,
  },
  [sym_data_type_name] = {
    .visible = true,
    .named = true,
  },
  [sym_data_type_definition] = {
    .visible = true,
    .named = true,
  },
  [sym_return_mode] = {
    .visible = true,
    .named = true,
  },
  [sym_create_keyspace] = {
    .visible = true,
    .named = true,
  },
  [sym_replication_list_item] = {
    .visible = true,
    .named = true,
  },
  [sym_durable_writes] = {
    .visible = true,
    .named = true,
  },
  [sym_create_role] = {
    .visible = true,
    .named = true,
  },
  [sym_role_with] = {
    .visible = true,
    .named = true,
  },
  [sym_role_with_option] = {
    .visible = true,
    .named = true,
  },
  [sym_option_hash] = {
    .visible = true,
    .named = true,
  },
  [sym_option_hash_item] = {
    .visible = true,
    .named = true,
  },
  [sym_create_table] = {
    .visible = true,
    .named = true,
  },
  [sym_column_definition_list] = {
    .visible = true,
    .named = true,
  },
  [sym_column_definition] = {
    .visible = true,
    .named = true,
  },
  [sym_primary_key_column] = {
    .visible = true,
    .named = true,
  },
  [sym_primary_key_element] = {
    .visible = true,
    .named = true,
  },
  [sym_primary_key_definition] = {
    .visible = true,
    .named = true,
  },
  [sym_compound_key] = {
    .visible = true,
    .named = true,
  },
  [sym_clustering_key_list] = {
    .visible = true,
    .named = true,
  },
  [sym_composite_key] = {
    .visible = true,
    .named = true,
  },
  [sym_partition_key_list] = {
    .visible = true,
    .named = true,
  },
  [sym_with_element] = {
    .visible = true,
    .named = true,
  },
  [sym_table_options] = {
    .visible = true,
    .named = true,
  },
  [sym_table_option_item] = {
    .visible = true,
    .named = true,
  },
  [sym_table_option_name] = {
    .visible = true,
    .named = true,
  },
  [sym_table_option_value] = {
    .visible = true,
    .named = true,
  },
  [sym_compact_storage] = {
    .visible = true,
    .named = true,
  },
  [sym_clustering_order] = {
    .visible = true,
    .named = true,
  },
  [sym_create_trigger] = {
    .visible = true,
    .named = true,
  },
  [sym_trigger_class] = {
    .visible = true,
    .named = true,
  },
  [sym_create_type] = {
    .visible = true,
    .named = true,
  },
  [sym_typed_name] = {
    .visible = true,
    .named = true,
  },
  [sym_create_user] = {
    .visible = true,
    .named = true,
  },
  [sym_user_with] = {
    .visible = true,
    .named = true,
  },
  [sym_user_password] = {
    .visible = true,
    .named = true,
  },
  [sym_user_super_user] = {
    .visible = true,
    .named = true,
  },
  [sym_alter_materialized_view] = {
    .visible = true,
    .named = true,
  },
  [sym_alter_keyspace] = {
    .visible = true,
    .named = true,
  },
  [sym_replication_list] = {
    .visible = true,
    .named = true,
  },
  [sym_alter_role] = {
    .visible = true,
    .named = true,
  },
  [sym_alter_table] = {
    .visible = true,
    .named = true,
  },
  [sym_alter_table_operation] = {
    .visible = true,
    .named = true,
  },
  [sym_alter_table_add] = {
    .visible = true,
    .named = true,
  },
  [sym_alter_table_drop_columns] = {
    .visible = true,
    .named = true,
  },
  [sym_alter_table_drop_compact_storage] = {
    .visible = true,
    .named = true,
  },
  [sym_alter_table_rename] = {
    .visible = true,
    .named = true,
  },
  [sym_alter_type] = {
    .visible = true,
    .named = true,
  },
  [sym_alter_type_operation] = {
    .visible = true,
    .named = true,
  },
  [sym_alter_type_alter_type] = {
    .visible = true,
    .named = true,
  },
  [sym_alter_type_add] = {
    .visible = true,
    .named = true,
  },
  [sym_alter_type_rename] = {
    .visible = true,
    .named = true,
  },
  [sym_alter_type_rename_item] = {
    .visible = true,
    .named = true,
  },
  [sym_alter_user] = {
    .visible = true,
    .named = true,
  },
  [sym_apply_batch] = {
    .visible = true,
    .named = true,
  },
  [sym_aggregate_name] = {
    .visible = true,
    .named = true,
  },
  [sym_short_index_name] = {
    .visible = true,
    .named = true,
  },
  [sym_index_name] = {
    .visible = true,
    .named = true,
  },
  [sym_materialized_view_name] = {
    .visible = true,
    .named = true,
  },
  [sym_role_name] = {
    .visible = true,
    .named = true,
  },
  [sym_trigger_name] = {
    .visible = true,
    .named = true,
  },
  [sym_type_name] = {
    .visible = true,
    .named = true,
  },
  [sym_user_name] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_source_file_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_unquoted_identifier_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_quoted_identifier_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_string_literal_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_integer_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_function_args_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_select_expression_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_relation_elements_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_relation_element_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_relation_element_repeat2] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_delete_column_list_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_expression_list_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_update_assignments_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_init_cond_list_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_init_cond_nested_list_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_init_cond_hash_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_materialized_view_where_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_create_function_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_data_type_definition_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_role_with_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_option_hash_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_column_definition_list_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_clustering_key_list_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_table_options_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_replication_list_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_alter_type_rename_repeat1] = {
    .visible = false,
    .named = false,
  },
  [anon_alias_sym_aggregate] = {
    .visible = true,
    .named = false,
  },
  [anon_alias_sym_assignment_operand] = {
    .visible = true,
    .named = false,
  },
  [anon_alias_sym_column] = {
    .visible = true,
    .named = false,
  },
  [anon_alias_sym_entry] = {
    .visible = true,
    .named = false,
  },
  [anon_alias_sym_finalfunc] = {
    .visible = true,
    .named = false,
  },
  [anon_alias_sym_full] = {
    .visible = true,
    .named = false,
  },
  [anon_alias_sym_function] = {
    .visible = true,
    .named = false,
  },
  [anon_alias_sym_hash_key] = {
    .visible = true,
    .named = false,
  },
  [anon_alias_sym_index] = {
    .visible = true,
    .named = false,
  },
  [anon_alias_sym_key] = {
    .visible = true,
    .named = false,
  },
  [anon_alias_sym_keyspace] = {
    .visible = true,
    .named = false,
  },
  [anon_alias_sym_language] = {
    .visible = true,
    .named = false,
  },
  [anon_alias_sym_limit_value] = {
    .visible = true,
    .named = false,
  },
  [anon_alias_sym_login] = {
    .visible = true,
    .named = false,
  },
  [anon_alias_sym_materialized_view] = {
    .visible = true,
    .named = false,
  },
  [anon_alias_sym_partition_key] = {
    .visible = true,
    .named = false,
  },
  [anon_alias_sym_password] = {
    .visible = true,
    .named = false,
  },
  [anon_alias_sym_primary_key] = {
    .visible = true,
    .named = false,
  },
  [anon_alias_sym_role] = {
    .visible = true,
    .named = false,
  },
  [anon_alias_sym_sfunc] = {
    .visible = true,
    .named = false,
  },
  [anon_alias_sym_table] = {
    .visible = true,
    .named = false,
  },
  [anon_alias_sym_trigger] = {
    .visible = true,
    .named = false,
  },
  [anon_alias_sym_ttl] = {
    .visible = true,
    .named = false,
  },
  [anon_alias_sym_type] = {
    .visible = true,
    .named = false,
  },
  [anon_alias_sym_user] = {
    .visible = true,
    .named = false,
  },
  [anon_alias_sym_value] = {
    .visible = true,
    .named = false,
  },
};

enum ts_field_identifiers {
  field_args = 1,
  field_close_curly_brace = 2,
  field_close_parenthesis = 3,
  field_close_square_bracket = 4,
  field_content = 5,
  field_escape_char = 6,
  field_left_quote = 7,
  field_name = 8,
  field_open_curly_brace = 9,
  field_open_parenthesis = 10,
  field_open_square_braket = 11,
  field_right_quote = 12,
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_args] = "args",
  [field_close_curly_brace] = "close_curly_brace",
  [field_close_parenthesis] = "close_parenthesis",
  [field_close_square_bracket] = "close_square_bracket",
  [field_content] = "content",
  [field_escape_char] = "escape_char",
  [field_left_quote] = "left_quote",
  [field_name] = "name",
  [field_open_curly_brace] = "open_curly_brace",
  [field_open_parenthesis] = "open_parenthesis",
  [field_open_square_braket] = "open_square_braket",
  [field_right_quote] = "right_quote",
};

static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {
  [10] = {.index = 0, .length = 1},
  [11] = {.index = 1, .length = 3},
  [30] = {.index = 4, .length = 4},
  [47] = {.index = 8, .length = 5},
  [48] = {.index = 13, .length = 5},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_escape_char, 0},
  [1] =
    {field_content, 1},
    {field_left_quote, 0},
    {field_right_quote, 2},
  [4] =
    {field_args, 2},
    {field_close_parenthesis, 3},
    {field_name, 0},
    {field_open_parenthesis, 1},
  [8] =
    {field_close_curly_brace, 4},
    {field_content, 1},
    {field_content, 2},
    {field_content, 3},
    {field_open_curly_brace, 0},
  [13] =
    {field_close_square_bracket, 4},
    {field_content, 1},
    {field_content, 2},
    {field_content, 3},
    {field_open_square_braket, 0},
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
  [1] = {
    [0] = anon_alias_sym_column,
  },
  [2] = {
    [1] = anon_alias_sym_keyspace,
  },
  [3] = {
    [0] = anon_alias_sym_keyspace,
  },
  [4] = {
    [0] = anon_alias_sym_index,
  },
  [5] = {
    [0] = anon_alias_sym_role,
  },
  [6] = {
    [0] = anon_alias_sym_aggregate,
  },
  [7] = {
    [0] = anon_alias_sym_trigger,
  },
  [8] = {
    [0] = anon_alias_sym_type,
  },
  [9] = {
    [0] = anon_alias_sym_user,
  },
  [12] = {
    [0] = anon_alias_sym_materialized_view,
  },
  [13] = {
    [0] = anon_alias_sym_table,
  },
  [14] = {
    [3] = anon_alias_sym_role,
  },
  [15] = {
    [1] = anon_alias_sym_limit_value,
  },
  [16] = {
    [0] = anon_alias_sym_column,
    [2] = anon_alias_sym_index,
  },
  [17] = {
    [0] = anon_alias_sym_keyspace,
    [2] = anon_alias_sym_aggregate,
  },
  [18] = {
    [0] = anon_alias_sym_keyspace,
    [2] = anon_alias_sym_trigger,
  },
  [19] = {
    [0] = anon_alias_sym_keyspace,
    [2] = anon_alias_sym_type,
  },
  [20] = {
    [0] = anon_alias_sym_keyspace,
    [2] = anon_alias_sym_index,
  },
  [21] = {
    [2] = anon_alias_sym_ttl,
  },
  [22] = {
    [1] = anon_alias_sym_table,
  },
  [23] = {
    [1] = anon_alias_sym_function,
  },
  [24] = {
    [1] = anon_alias_sym_role,
  },
  [25] = {
    [0] = anon_alias_sym_keyspace,
    [2] = anon_alias_sym_materialized_view,
  },
  [26] = {
    [1] = anon_alias_sym_password,
  },
  [27] = {
    [0] = anon_alias_sym_keyspace,
    [2] = anon_alias_sym_table,
  },
  [28] = {
    [5] = anon_alias_sym_role,
  },
  [29] = {
    [1] = anon_alias_sym_column,
  },
  [31] = {
    [2] = anon_alias_sym_password,
  },
  [32] = {
    [2] = anon_alias_sym_login,
  },
  [33] = {
    [2] = anon_alias_sym_user,
  },
  [34] = {
    [2] = anon_alias_sym_index,
  },
  [35] = {
    [1] = anon_alias_sym_keyspace,
    [3] = anon_alias_sym_table,
  },
  [36] = {
    [1] = anon_alias_sym_keyspace,
    [3] = anon_alias_sym_function,
  },
  [37] = {
    [1] = anon_alias_sym_column,
    [3] = anon_alias_sym_column,
  },
  [38] = {
    [0] = anon_alias_sym_column,
    [2] = anon_alias_sym_column,
  },
  [39] = {
    [5] = anon_alias_sym_ttl,
  },
  [40] = {
    [4] = anon_alias_sym_assignment_operand,
  },
  [41] = {
    [4] = anon_alias_sym_keyspace,
  },
  [42] = {
    [2] = anon_alias_sym_key,
  },
  [43] = {
    [2] = anon_alias_sym_entry,
  },
  [44] = {
    [2] = anon_alias_sym_full,
  },
  [45] = {
    [0] = anon_alias_sym_primary_key,
  },
  [46] = {
    [0] = anon_alias_sym_key,
    [2] = anon_alias_sym_value,
  },
  [49] = {
    [4] = anon_alias_sym_column,
  },
  [50] = {
    [2] = anon_alias_sym_value,
  },
  [51] = {
    [0] = anon_alias_sym_partition_key,
  },
  [52] = {
    [9] = anon_alias_sym_language,
  },
  [53] = {
    [10] = anon_alias_sym_language,
  },
  [54] = {
    [11] = anon_alias_sym_language,
  },
  [55] = {
    [7] = anon_alias_sym_sfunc,
    [11] = anon_alias_sym_finalfunc,
  },
  [56] = {
    [12] = anon_alias_sym_language,
  },
  [57] = {
    [13] = anon_alias_sym_language,
  },
  [58] = {
    [9] = anon_alias_sym_sfunc,
    [13] = anon_alias_sym_finalfunc,
  },
  [59] = {
    [14] = anon_alias_sym_language,
  },
  [60] = {
    [10] = anon_alias_sym_sfunc,
    [14] = anon_alias_sym_finalfunc,
  },
  [61] = {
    [0] = anon_alias_sym_hash_key,
  },
  [62] = {
    [15] = anon_alias_sym_language,
  },
  [63] = {
    [16] = anon_alias_sym_language,
  },
  [64] = {
    [12] = anon_alias_sym_sfunc,
    [16] = anon_alias_sym_finalfunc,
  },
};

static const uint16_t ts_non_terminal_alias_map[] = {
  sym_string_literal, 5,
    sym_string_literal,
    anon_alias_sym_index,
    anon_alias_sym_key,
    anon_alias_sym_password,
    anon_alias_sym_value,
  sym_integer, 5,
    sym_integer,
    anon_alias_sym_assignment_operand,
    anon_alias_sym_index,
    anon_alias_sym_limit_value,
    anon_alias_sym_value,
  sym_float_literal, 2,
    sym_float_literal,
    anon_alias_sym_value,
  sym_boolean_literal, 4,
    sym_boolean_literal,
    anon_alias_sym_login,
    anon_alias_sym_user,
    anon_alias_sym_value,
  sym_function_name, 3,
    sym_function_name,
    anon_alias_sym_finalfunc,
    anon_alias_sym_sfunc,
  0,
};

static const TSStateId ts_primary_state_ids[STATE_COUNT] = {
  [0] = 0,
  [1] = 1,
  [2] = 2,
  [3] = 3,
  [4] = 4,
  [5] = 5,
  [6] = 6,
  [7] = 7,
  [8] = 8,
  [9] = 9,
  [10] = 10,
  [11] = 11,
  [12] = 12,
  [13] = 13,
  [14] = 14,
  [15] = 15,
  [16] = 16,
  [17] = 17,
  [18] = 18,
  [19] = 19,
  [20] = 20,
  [21] = 21,
  [22] = 22,
  [23] = 23,
  [24] = 24,
  [25] = 25,
  [26] = 26,
  [27] = 27,
  [28] = 28,
  [29] = 29,
  [30] = 30,
  [31] = 31,
  [32] = 32,
  [33] = 33,
  [34] = 34,
  [35] = 35,
  [36] = 36,
  [37] = 37,
  [38] = 38,
  [39] = 39,
  [40] = 40,
  [41] = 41,
  [42] = 42,
  [43] = 43,
  [44] = 44,
  [45] = 45,
  [46] = 46,
  [47] = 47,
  [48] = 48,
  [49] = 49,
  [50] = 50,
  [51] = 51,
  [52] = 52,
  [53] = 53,
  [54] = 54,
  [55] = 55,
  [56] = 56,
  [57] = 57,
  [58] = 58,
  [59] = 59,
  [60] = 60,
  [61] = 61,
  [62] = 62,
  [63] = 63,
  [64] = 64,
  [65] = 65,
  [66] = 66,
  [67] = 67,
  [68] = 68,
  [69] = 69,
  [70] = 70,
  [71] = 71,
  [72] = 72,
  [73] = 73,
  [74] = 74,
  [75] = 75,
  [76] = 76,
  [77] = 77,
  [78] = 78,
  [79] = 79,
  [80] = 80,
  [81] = 81,
  [82] = 82,
  [83] = 83,
  [84] = 84,
  [85] = 85,
  [86] = 86,
  [87] = 87,
  [88] = 88,
  [89] = 89,
  [90] = 90,
  [91] = 91,
  [92] = 92,
  [93] = 93,
  [94] = 94,
  [95] = 95,
  [96] = 96,
  [97] = 97,
  [98] = 98,
  [99] = 99,
  [100] = 100,
  [101] = 101,
  [102] = 102,
  [103] = 103,
  [104] = 104,
  [105] = 105,
  [106] = 106,
  [107] = 107,
  [108] = 108,
  [109] = 109,
  [110] = 110,
  [111] = 111,
  [112] = 112,
  [113] = 113,
  [114] = 114,
  [115] = 115,
  [116] = 116,
  [117] = 117,
  [118] = 118,
  [119] = 119,
  [120] = 120,
  [121] = 121,
  [122] = 122,
  [123] = 123,
  [124] = 124,
  [125] = 125,
  [126] = 126,
  [127] = 127,
  [128] = 128,
  [129] = 129,
  [130] = 130,
  [131] = 131,
  [132] = 132,
  [133] = 133,
  [134] = 134,
  [135] = 135,
  [136] = 136,
  [137] = 137,
  [138] = 138,
  [139] = 139,
  [140] = 140,
  [141] = 141,
  [142] = 142,
  [143] = 143,
  [144] = 144,
  [145] = 145,
  [146] = 146,
  [147] = 147,
  [148] = 148,
  [149] = 149,
  [150] = 150,
  [151] = 151,
  [152] = 152,
  [153] = 153,
  [154] = 154,
  [155] = 155,
  [156] = 156,
  [157] = 157,
  [158] = 158,
  [159] = 159,
  [160] = 160,
  [161] = 161,
  [162] = 162,
  [163] = 163,
  [164] = 164,
  [165] = 165,
  [166] = 166,
  [167] = 167,
  [168] = 168,
  [169] = 169,
  [170] = 170,
  [171] = 171,
  [172] = 172,
  [173] = 173,
  [174] = 174,
  [175] = 175,
  [176] = 176,
  [177] = 177,
  [178] = 178,
  [179] = 179,
  [180] = 180,
  [181] = 181,
  [182] = 182,
  [183] = 183,
  [184] = 184,
  [185] = 185,
  [186] = 186,
  [187] = 187,
  [188] = 188,
  [189] = 189,
  [190] = 190,
  [191] = 191,
  [192] = 192,
  [193] = 193,
  [194] = 194,
  [195] = 195,
  [196] = 196,
  [197] = 197,
  [198] = 198,
  [199] = 199,
  [200] = 200,
  [201] = 201,
  [202] = 202,
  [203] = 203,
  [204] = 204,
  [205] = 205,
  [206] = 206,
  [207] = 207,
  [208] = 208,
  [209] = 209,
  [210] = 210,
  [211] = 211,
  [212] = 212,
  [213] = 213,
  [214] = 214,
  [215] = 215,
  [216] = 216,
  [217] = 217,
  [218] = 218,
  [219] = 219,
  [220] = 220,
  [221] = 221,
  [222] = 222,
  [223] = 223,
  [224] = 224,
  [225] = 225,
  [226] = 226,
  [227] = 227,
  [228] = 228,
  [229] = 229,
  [230] = 230,
  [231] = 231,
  [232] = 232,
  [233] = 233,
  [234] = 234,
  [235] = 235,
  [236] = 236,
  [237] = 237,
  [238] = 238,
  [239] = 239,
  [240] = 240,
  [241] = 241,
  [242] = 242,
  [243] = 243,
  [244] = 244,
  [245] = 245,
  [246] = 246,
  [247] = 247,
  [248] = 248,
  [249] = 249,
  [250] = 250,
  [251] = 251,
  [252] = 252,
  [253] = 253,
  [254] = 254,
  [255] = 255,
  [256] = 256,
  [257] = 257,
  [258] = 258,
  [259] = 259,
  [260] = 260,
  [261] = 261,
  [262] = 262,
  [263] = 263,
  [264] = 264,
  [265] = 265,
  [266] = 266,
  [267] = 267,
  [268] = 268,
  [269] = 269,
  [270] = 270,
  [271] = 271,
  [272] = 272,
  [273] = 273,
  [274] = 274,
  [275] = 275,
  [276] = 276,
  [277] = 277,
  [278] = 278,
  [279] = 279,
  [280] = 280,
  [281] = 281,
  [282] = 282,
  [283] = 283,
  [284] = 284,
  [285] = 285,
  [286] = 286,
  [287] = 287,
  [288] = 288,
  [289] = 289,
  [290] = 290,
  [291] = 291,
  [292] = 292,
  [293] = 293,
  [294] = 294,
  [295] = 295,
  [296] = 296,
  [297] = 297,
  [298] = 298,
  [299] = 299,
  [300] = 300,
  [301] = 301,
  [302] = 302,
  [303] = 303,
  [304] = 304,
  [305] = 305,
  [306] = 306,
  [307] = 307,
  [308] = 308,
  [309] = 309,
  [310] = 310,
  [311] = 311,
  [312] = 312,
  [313] = 313,
  [314] = 314,
  [315] = 315,
  [316] = 316,
  [317] = 317,
  [318] = 318,
  [319] = 319,
  [320] = 320,
  [321] = 321,
  [322] = 322,
  [323] = 323,
  [324] = 324,
  [325] = 325,
  [326] = 326,
  [327] = 327,
  [328] = 328,
  [329] = 329,
  [330] = 330,
  [331] = 331,
  [332] = 332,
  [333] = 333,
  [334] = 334,
  [335] = 335,
  [336] = 336,
  [337] = 337,
  [338] = 107,
  [339] = 339,
  [340] = 340,
  [341] = 96,
  [342] = 342,
  [343] = 343,
  [344] = 100,
  [345] = 345,
  [346] = 346,
  [347] = 347,
  [348] = 348,
  [349] = 107,
  [350] = 350,
  [351] = 351,
  [352] = 352,
  [353] = 353,
  [354] = 354,
  [355] = 355,
  [356] = 356,
  [357] = 357,
  [358] = 100,
  [359] = 96,
  [360] = 360,
  [361] = 361,
  [362] = 362,
  [363] = 363,
  [364] = 364,
  [365] = 365,
  [366] = 366,
  [367] = 367,
  [368] = 368,
  [369] = 369,
  [370] = 370,
  [371] = 371,
  [372] = 372,
  [373] = 373,
  [374] = 374,
  [375] = 375,
  [376] = 376,
  [377] = 377,
  [378] = 378,
  [379] = 379,
  [380] = 380,
  [381] = 381,
  [382] = 382,
  [383] = 383,
  [384] = 384,
  [385] = 385,
  [386] = 386,
  [387] = 387,
  [388] = 388,
  [389] = 389,
  [390] = 98,
  [391] = 391,
  [392] = 100,
  [393] = 393,
  [394] = 394,
  [395] = 107,
  [396] = 393,
  [397] = 96,
  [398] = 398,
  [399] = 100,
  [400] = 100,
  [401] = 107,
  [402] = 110,
  [403] = 96,
  [404] = 100,
  [405] = 405,
  [406] = 98,
  [407] = 407,
  [408] = 110,
  [409] = 98,
  [410] = 410,
  [411] = 411,
  [412] = 412,
  [413] = 110,
  [414] = 414,
  [415] = 107,
  [416] = 416,
  [417] = 417,
  [418] = 110,
  [419] = 419,
  [420] = 96,
  [421] = 98,
  [422] = 422,
  [423] = 423,
  [424] = 100,
  [425] = 425,
  [426] = 100,
  [427] = 100,
  [428] = 428,
  [429] = 429,
  [430] = 430,
  [431] = 431,
  [432] = 432,
  [433] = 433,
  [434] = 434,
  [435] = 96,
  [436] = 436,
  [437] = 437,
  [438] = 107,
  [439] = 439,
  [440] = 440,
  [441] = 441,
  [442] = 442,
  [443] = 443,
  [444] = 444,
  [445] = 445,
  [446] = 446,
  [447] = 447,
  [448] = 448,
  [449] = 449,
  [450] = 450,
  [451] = 451,
  [452] = 452,
  [453] = 453,
  [454] = 454,
  [455] = 455,
  [456] = 456,
  [457] = 457,
  [458] = 458,
  [459] = 459,
  [460] = 460,
  [461] = 461,
  [462] = 462,
  [463] = 463,
  [464] = 464,
  [465] = 465,
  [466] = 466,
  [467] = 467,
  [468] = 468,
  [469] = 469,
  [470] = 470,
  [471] = 471,
  [472] = 472,
  [473] = 473,
  [474] = 474,
  [475] = 475,
  [476] = 476,
  [477] = 477,
  [478] = 478,
  [479] = 479,
  [480] = 480,
  [481] = 481,
  [482] = 482,
  [483] = 483,
  [484] = 484,
  [485] = 485,
  [486] = 486,
  [487] = 487,
  [488] = 488,
  [489] = 489,
  [490] = 490,
  [491] = 491,
  [492] = 492,
  [493] = 493,
  [494] = 494,
  [495] = 495,
  [496] = 496,
  [497] = 497,
  [498] = 498,
  [499] = 499,
  [500] = 500,
  [501] = 501,
  [502] = 502,
  [503] = 503,
  [504] = 504,
  [505] = 505,
  [506] = 506,
  [507] = 507,
  [508] = 508,
  [509] = 509,
  [510] = 510,
  [511] = 511,
  [512] = 512,
  [513] = 513,
  [514] = 514,
  [515] = 515,
  [516] = 516,
  [517] = 517,
  [518] = 518,
  [519] = 519,
  [520] = 520,
  [521] = 521,
  [522] = 522,
  [523] = 523,
  [524] = 524,
  [525] = 525,
  [526] = 526,
  [527] = 527,
  [528] = 528,
  [529] = 529,
  [530] = 530,
  [531] = 531,
  [532] = 532,
  [533] = 533,
  [534] = 534,
  [535] = 535,
  [536] = 536,
  [537] = 537,
  [538] = 538,
  [539] = 539,
  [540] = 540,
  [541] = 541,
  [542] = 542,
  [543] = 543,
  [544] = 544,
  [545] = 545,
  [546] = 546,
  [547] = 547,
  [548] = 548,
  [549] = 549,
  [550] = 550,
  [551] = 551,
  [552] = 552,
  [553] = 553,
  [554] = 554,
  [555] = 555,
  [556] = 556,
  [557] = 557,
  [558] = 558,
  [559] = 559,
  [560] = 560,
  [561] = 561,
  [562] = 562,
  [563] = 563,
  [564] = 564,
  [565] = 565,
  [566] = 566,
  [567] = 567,
  [568] = 568,
  [569] = 569,
  [570] = 570,
  [571] = 571,
  [572] = 572,
  [573] = 573,
  [574] = 574,
  [575] = 575,
  [576] = 576,
  [577] = 577,
  [578] = 578,
  [579] = 579,
  [580] = 580,
  [581] = 581,
  [582] = 582,
  [583] = 583,
  [584] = 584,
  [585] = 585,
  [586] = 586,
  [587] = 587,
  [588] = 588,
  [589] = 589,
  [590] = 590,
  [591] = 591,
  [592] = 592,
  [593] = 593,
  [594] = 594,
  [595] = 595,
  [596] = 596,
  [597] = 597,
  [598] = 598,
  [599] = 599,
  [600] = 600,
  [601] = 601,
  [602] = 602,
  [603] = 601,
  [604] = 604,
  [605] = 605,
  [606] = 606,
  [607] = 607,
  [608] = 608,
  [609] = 609,
  [610] = 610,
  [611] = 87,
  [612] = 612,
  [613] = 613,
  [614] = 614,
  [615] = 615,
  [616] = 616,
  [617] = 617,
  [618] = 618,
  [619] = 619,
  [620] = 620,
  [621] = 621,
  [622] = 320,
  [623] = 609,
  [624] = 624,
  [625] = 625,
  [626] = 626,
  [627] = 627,
  [628] = 628,
  [629] = 11,
  [630] = 630,
  [631] = 631,
  [632] = 632,
  [633] = 633,
  [634] = 634,
  [635] = 635,
  [636] = 636,
  [637] = 637,
  [638] = 638,
  [639] = 639,
  [640] = 640,
  [641] = 641,
  [642] = 642,
  [643] = 643,
  [644] = 644,
  [645] = 645,
  [646] = 646,
  [647] = 647,
  [648] = 648,
  [649] = 649,
  [650] = 650,
  [651] = 651,
  [652] = 652,
  [653] = 653,
  [654] = 654,
  [655] = 655,
  [656] = 656,
  [657] = 657,
  [658] = 658,
  [659] = 659,
  [660] = 660,
  [661] = 661,
  [662] = 662,
  [663] = 663,
  [664] = 664,
  [665] = 665,
  [666] = 666,
  [667] = 667,
  [668] = 668,
  [669] = 669,
  [670] = 670,
  [671] = 671,
  [672] = 672,
  [673] = 673,
  [674] = 674,
  [675] = 675,
  [676] = 676,
  [677] = 677,
  [678] = 678,
  [679] = 679,
  [680] = 680,
  [681] = 681,
  [682] = 682,
  [683] = 683,
  [684] = 684,
  [685] = 685,
  [686] = 686,
  [687] = 687,
  [688] = 688,
  [689] = 689,
  [690] = 690,
  [691] = 691,
  [692] = 692,
  [693] = 693,
  [694] = 694,
  [695] = 695,
  [696] = 696,
  [697] = 697,
  [698] = 698,
  [699] = 699,
  [700] = 700,
  [701] = 701,
  [702] = 702,
  [703] = 703,
  [704] = 704,
  [705] = 705,
  [706] = 706,
  [707] = 707,
  [708] = 708,
  [709] = 709,
  [710] = 710,
  [711] = 711,
  [712] = 712,
  [713] = 713,
  [714] = 714,
  [715] = 715,
  [716] = 716,
  [717] = 717,
  [718] = 718,
  [719] = 719,
  [720] = 720,
  [721] = 721,
  [722] = 722,
  [723] = 723,
  [724] = 724,
  [725] = 725,
  [726] = 726,
  [727] = 727,
  [728] = 728,
  [729] = 729,
  [730] = 730,
  [731] = 731,
  [732] = 732,
  [733] = 733,
  [734] = 734,
  [735] = 735,
  [736] = 736,
  [737] = 737,
  [738] = 738,
  [739] = 739,
  [740] = 740,
  [741] = 741,
  [742] = 742,
  [743] = 743,
  [744] = 744,
  [745] = 745,
  [746] = 746,
  [747] = 747,
  [748] = 748,
  [749] = 749,
  [750] = 750,
  [751] = 751,
  [752] = 752,
  [753] = 753,
  [754] = 754,
  [755] = 755,
  [756] = 756,
  [757] = 757,
  [758] = 758,
  [759] = 759,
  [760] = 760,
  [761] = 761,
  [762] = 762,
  [763] = 763,
  [764] = 764,
  [765] = 765,
  [766] = 766,
  [767] = 767,
  [768] = 768,
  [769] = 769,
  [770] = 770,
  [771] = 771,
  [772] = 772,
  [773] = 773,
  [774] = 774,
  [775] = 775,
  [776] = 776,
  [777] = 777,
  [778] = 778,
  [779] = 779,
  [780] = 780,
  [781] = 781,
  [782] = 782,
  [783] = 783,
  [784] = 784,
  [785] = 785,
  [786] = 786,
  [787] = 787,
  [788] = 788,
  [789] = 789,
  [790] = 790,
  [791] = 791,
  [792] = 792,
  [793] = 793,
  [794] = 794,
  [795] = 795,
  [796] = 796,
  [797] = 797,
  [798] = 798,
  [799] = 799,
  [800] = 800,
  [801] = 801,
  [802] = 802,
  [803] = 803,
  [804] = 804,
  [805] = 805,
  [806] = 806,
  [807] = 807,
  [808] = 808,
  [809] = 809,
  [810] = 810,
  [811] = 811,
  [812] = 812,
  [813] = 813,
  [814] = 814,
  [815] = 815,
  [816] = 816,
  [817] = 817,
  [818] = 818,
  [819] = 819,
  [820] = 820,
  [821] = 821,
  [822] = 822,
  [823] = 823,
  [824] = 824,
  [825] = 825,
  [826] = 826,
  [827] = 827,
  [828] = 828,
  [829] = 829,
  [830] = 830,
  [831] = 831,
  [832] = 832,
  [833] = 833,
  [834] = 834,
  [835] = 835,
  [836] = 836,
  [837] = 837,
  [838] = 838,
  [839] = 839,
  [840] = 840,
  [841] = 841,
  [842] = 842,
  [843] = 843,
  [844] = 844,
  [845] = 845,
  [846] = 846,
  [847] = 847,
  [848] = 848,
  [849] = 849,
  [850] = 850,
  [851] = 851,
  [852] = 852,
  [853] = 853,
  [854] = 854,
  [855] = 855,
  [856] = 856,
  [857] = 857,
  [858] = 858,
  [859] = 859,
  [860] = 860,
  [861] = 861,
  [862] = 862,
  [863] = 863,
  [864] = 864,
  [865] = 865,
  [866] = 866,
  [867] = 867,
  [868] = 868,
  [869] = 869,
  [870] = 870,
  [871] = 871,
  [872] = 872,
  [873] = 873,
  [874] = 874,
  [875] = 875,
  [876] = 876,
  [877] = 877,
  [878] = 878,
  [879] = 879,
  [880] = 880,
  [881] = 881,
  [882] = 882,
  [883] = 883,
  [884] = 884,
  [885] = 885,
  [886] = 886,
  [887] = 887,
  [888] = 888,
  [889] = 889,
  [890] = 890,
  [891] = 891,
  [892] = 892,
  [893] = 893,
  [894] = 894,
  [895] = 895,
  [896] = 896,
  [897] = 897,
  [898] = 898,
  [899] = 899,
  [900] = 900,
  [901] = 901,
  [902] = 902,
  [903] = 903,
  [904] = 904,
  [905] = 905,
  [906] = 906,
  [907] = 907,
  [908] = 908,
  [909] = 909,
  [910] = 910,
  [911] = 911,
  [912] = 912,
  [913] = 913,
  [914] = 914,
  [915] = 915,
  [916] = 916,
  [917] = 917,
  [918] = 918,
  [919] = 919,
  [920] = 920,
  [921] = 921,
  [922] = 922,
  [923] = 923,
  [924] = 924,
  [925] = 925,
  [926] = 926,
  [927] = 927,
  [928] = 928,
  [929] = 929,
  [930] = 930,
  [931] = 931,
  [932] = 932,
  [933] = 933,
  [934] = 934,
  [935] = 935,
  [936] = 936,
  [937] = 937,
  [938] = 938,
  [939] = 939,
  [940] = 940,
  [941] = 941,
  [942] = 942,
  [943] = 943,
  [944] = 944,
  [945] = 945,
  [946] = 946,
  [947] = 947,
  [948] = 948,
  [949] = 949,
  [950] = 950,
  [951] = 951,
  [952] = 952,
  [953] = 953,
  [954] = 954,
  [955] = 955,
  [956] = 956,
  [957] = 957,
  [958] = 958,
  [959] = 959,
  [960] = 960,
  [961] = 961,
  [962] = 962,
  [963] = 963,
  [964] = 964,
  [965] = 965,
  [966] = 966,
  [967] = 967,
  [968] = 968,
  [969] = 969,
  [970] = 970,
  [971] = 971,
  [972] = 972,
  [973] = 973,
  [974] = 974,
  [975] = 975,
  [976] = 976,
  [977] = 977,
  [978] = 978,
  [979] = 979,
  [980] = 980,
  [981] = 981,
  [982] = 982,
  [983] = 983,
  [984] = 984,
  [985] = 985,
  [986] = 986,
  [987] = 987,
  [988] = 988,
  [989] = 989,
  [990] = 990,
  [991] = 991,
  [992] = 992,
  [993] = 993,
  [994] = 994,
  [995] = 995,
  [996] = 996,
  [997] = 997,
  [998] = 998,
  [999] = 999,
  [1000] = 1000,
  [1001] = 1001,
  [1002] = 1002,
  [1003] = 1003,
  [1004] = 1004,
  [1005] = 1005,
  [1006] = 1006,
  [1007] = 1007,
  [1008] = 1008,
  [1009] = 1009,
  [1010] = 1010,
  [1011] = 1011,
  [1012] = 1012,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(501);
      if (lookahead == '"') ADVANCE(506);
      if (lookahead == '$') ADVANCE(24);
      if (lookahead == '%') ADVANCE(598);
      if (lookahead == '\'') ADVANCE(505);
      if (lookahead == '(') ADVANCE(596);
      if (lookahead == ')') ADVANCE(597);
      if (lookahead == '*') ADVANCE(609);
      if (lookahead == '+') ADVANCE(578);
      if (lookahead == ',') ADVANCE(502);
      if (lookahead == '-') ADVANCE(570);
      if (lookahead == '.') ADVANCE(503);
      if (lookahead == '/') ADVANCE(598);
      if (lookahead == '0') ADVANCE(562);
      if (lookahead == ':') ADVANCE(601);
      if (lookahead == ';') ADVANCE(504);
      if (lookahead == '<') ADVANCE(602);
      if (lookahead == '=') ADVANCE(623);
      if (lookahead == '>') ADVANCE(603);
      if (lookahead == '?') ADVANCE(600);
      if (lookahead == 'F') ADVANCE(510);
      if (lookahead == 'I') ADVANCE(514);
      if (lookahead == 'N') ADVANCE(511);
      if (lookahead == 'T') ADVANCE(516);
      if (lookahead == '[') ADVANCE(606);
      if (lookahead == ']') ADVANCE(608);
      if (lookahead == '_') ADVANCE(559);
      if (lookahead == 'f') ADVANCE(546);
      if (lookahead == 'i') ADVANCE(532);
      if (lookahead == 't') ADVANCE(519);
      if (lookahead == '{') ADVANCE(604);
      if (lookahead == '}') ADVANCE(605);
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(521);
      if (lookahead == 'B' ||
          lookahead == 'b') ADVANCE(522);
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(548);
      if (lookahead == 'D' ||
          lookahead == 'd') ADVANCE(523);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(555);
      if (lookahead == 'G' ||
          lookahead == 'g') ADVANCE(549);
      if (lookahead == 'J' ||
          lookahead == 'j') ADVANCE(552);
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(536);
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(551);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(525);
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(526);
      if (lookahead == 'U' ||
          lookahead == 'u') ADVANCE(544);
      if (lookahead == 'W' ||
          lookahead == 'w') ADVANCE(534);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0)
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(560);
      if (('H' <= lookahead && lookahead <= 'Z') ||
          ('h' <= lookahead && lookahead <= 'z')) ADVANCE(509);
      END_STATE();
    case 1:
      if (lookahead == '"') ADVANCE(506);
      if (lookahead == '$') ADVANCE(24);
      if (lookahead == '\'') ADVANCE(505);
      if (lookahead == '(') ADVANCE(596);
      if (lookahead == '-') ADVANCE(570);
      if (lookahead == '0') ADVANCE(561);
      if (lookahead == ':') ADVANCE(601);
      if (lookahead == '?') ADVANCE(600);
      if (lookahead == 'F') ADVANCE(512);
      if (lookahead == 'I') ADVANCE(515);
      if (lookahead == 'N') ADVANCE(513);
      if (lookahead == 'T') ADVANCE(517);
      if (lookahead == '[') ADVANCE(607);
      if (lookahead == '{') ADVANCE(604);
      if (('\\' <= lookahead && lookahead <= '`')) ADVANCE(485);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(1)
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(563);
      if (('g' <= lookahead && lookahead <= 'z')) ADVANCE(509);
      if (('A' <= lookahead && lookahead <= 'f')) ADVANCE(557);
      END_STATE();
    case 2:
      if (lookahead == '"') ADVANCE(506);
      if (lookahead == '(') ADVANCE(596);
      if (lookahead == '*') ADVANCE(609);
      if (lookahead == '_') ADVANCE(559);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(2)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(560);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(509);
      END_STATE();
    case 3:
      if (lookahead == '"') ADVANCE(506);
      if (lookahead == '*') ADVANCE(609);
      if (lookahead == 'D' ||
          lookahead == 'd') ADVANCE(535);
      if (lookahead == 'J' ||
          lookahead == 'j') ADVANCE(552);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(3)
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(509);
      END_STATE();
    case 4:
      if (lookahead == '"') ADVANCE(506);
      if (lookahead == '*') ADVANCE(609);
      if (lookahead == 'J' ||
          lookahead == 'j') ADVANCE(552);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(4)
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(509);
      END_STATE();
    case 5:
      if (lookahead == '"') ADVANCE(506);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(531);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(5)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(560);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(509);
      END_STATE();
    case 6:
      if (lookahead == '"') ADVANCE(506);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(565);
      if (lookahead != 0) ADVANCE(564);
      END_STATE();
    case 7:
      if (lookahead == '"') ADVANCE(496);
      if (lookahead == '$') ADVANCE(24);
      if (lookahead == '\'') ADVANCE(505);
      if (lookahead == '(') ADVANCE(596);
      if (lookahead == '-') ADVANCE(570);
      if (lookahead == '0') ADVANCE(561);
      if (lookahead == 'F') ADVANCE(750);
      if (lookahead == 'I') ADVANCE(760);
      if (lookahead == 'N') ADVANCE(751);
      if (lookahead == 'T') ADVANCE(763);
      if (lookahead == '[') ADVANCE(607);
      if (lookahead == '{') ADVANCE(604);
      if (('\\' <= lookahead && lookahead <= '`')) ADVANCE(485);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(7)
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(563);
      if (('g' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      if (('A' <= lookahead && lookahead <= 'f')) ADVANCE(927);
      END_STATE();
    case 8:
      if (lookahead == '"') ADVANCE(496);
      if (lookahead == '$') ADVANCE(24);
      if (lookahead == '\'') ADVANCE(505);
      if (lookahead == '-') ADVANCE(570);
      if (lookahead == '[') ADVANCE(606);
      if (lookahead == '{') ADVANCE(604);
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(883);
      if (lookahead == 'B' ||
          lookahead == 'b') ADVANCE(813);
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(864);
      if (lookahead == 'D' ||
          lookahead == 'd') ADVANCE(768);
      if (lookahead == 'F' ||
          lookahead == 'f') ADVANCE(833);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(848);
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(817);
      if (lookahead == 'M' ||
          lookahead == 'm') ADVANCE(769);
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(800);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(792);
      if (lookahead == 'U' ||
          lookahead == 'u') ADVANCE(909);
      if (lookahead == 'V' ||
          lookahead == 'v') ADVANCE(770);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(8)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(560);
      if (('E' <= lookahead && lookahead <= 'Z') ||
          ('e' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 9:
      if (lookahead == '"') ADVANCE(496);
      if (lookahead == '$') ADVANCE(24);
      if (lookahead == '\'') ADVANCE(505);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(809);
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(851);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(9)
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 10:
      if (lookahead == '"') ADVANCE(496);
      if (lookahead == '$') ADVANCE(24);
      if (lookahead == '\'') ADVANCE(505);
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(851);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(10)
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 11:
      if (lookahead == '"') ADVANCE(496);
      if (lookahead == '(') ADVANCE(596);
      if (lookahead == ')') ADVANCE(597);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(11)
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 12:
      if (lookahead == '"') ADVANCE(496);
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(837);
      if (lookahead == 'F' ||
          lookahead == 'f') ADVANCE(913);
      if (lookahead == 'K' ||
          lookahead == 'k') ADVANCE(807);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(869);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(780);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(12)
      if (('B' <= lookahead && lookahead <= 'Z') ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 13:
      if (lookahead == '"') ADVANCE(496);
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(834);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(13)
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 14:
      if (lookahead == '"') ADVANCE(496);
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(868);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(14)
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 15:
      if (lookahead == '"') ADVANCE(496);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(858);
      if (lookahead == 'F' ||
          lookahead == 'f') ADVANCE(914);
      if (lookahead == 'K' ||
          lookahead == 'k') ADVANCE(802);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(15)
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 16:
      if (lookahead == '"') ADVANCE(496);
      if (lookahead == 'F' ||
          lookahead == 'f') ADVANCE(879);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(16)
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 17:
      if (lookahead == '"') ADVANCE(496);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(809);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(17)
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 18:
      if (lookahead == '"') ADVANCE(496);
      if (lookahead == 'P' ||
          lookahead == 'p') ADVANCE(882);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(18)
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 19:
      if (lookahead == '"') ADVANCE(748);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(19);
      END_STATE();
    case 20:
      if (lookahead == '"') ADVANCE(507);
      if (lookahead == '(') ADVANCE(596);
      if (lookahead == '-') ADVANCE(462);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(556);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(20)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(647);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(558);
      END_STATE();
    case 21:
      if (lookahead == '"') ADVANCE(507);
      if (lookahead == '(') ADVANCE(596);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(21)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(560);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(558);
      END_STATE();
    case 22:
      if (lookahead == '$') ADVANCE(24);
      if (lookahead == '\'') ADVANCE(505);
      if (lookahead == '-') ADVANCE(570);
      if (lookahead == '0') ADVANCE(561);
      if (lookahead == 'F') ADVANCE(39);
      if (lookahead == 'I') ADVANCE(59);
      if (lookahead == 'K') ADVANCE(159);
      if (lookahead == 'N') ADVANCE(40);
      if (lookahead == 'T') ADVANCE(64);
      if (lookahead == 'k') ADVANCE(175);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(22)
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(563);
      if (('A' <= lookahead && lookahead <= 'f')) ADVANCE(485);
      END_STATE();
    case 23:
      if (lookahead == '$') ADVANCE(24);
      if (lookahead == '\'') ADVANCE(505);
      if (lookahead == '-') ADVANCE(570);
      if (lookahead == 'I') ADVANCE(61);
      if (lookahead == 'N') ADVANCE(38);
      if (lookahead == 'i') ADVANCE(289);
      if (lookahead == '{') ADVANCE(604);
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(211);
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(344);
      if (lookahead == 'D' ||
          lookahead == 'd') ADVANCE(192);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(452);
      if (lookahead == 'F' ||
          lookahead == 'f') ADVANCE(444);
      if (lookahead == 'K' ||
          lookahead == 'k') ADVANCE(175);
      if (lookahead == 'M' ||
          lookahead == 'm') ADVANCE(324);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(329);
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(199);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(23)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(560);
      END_STATE();
    case 24:
      if (lookahead == '$') ADVANCE(508);
      END_STATE();
    case 25:
      if (lookahead == '$') ADVANCE(26);
      END_STATE();
    case 26:
      if (lookahead == '$') ADVANCE(498);
      if (lookahead != 0) ADVANCE(29);
      END_STATE();
    case 27:
      if (lookahead == '$') ADVANCE(618);
      if (lookahead != 0) ADVANCE(29);
      END_STATE();
    case 28:
      if (lookahead == '$') ADVANCE(497);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(568);
      if (lookahead != 0) ADVANCE(569);
      END_STATE();
    case 29:
      if (lookahead == '$') ADVANCE(27);
      if (lookahead != 0) ADVANCE(29);
      END_STATE();
    case 30:
      if (lookahead == '\'') ADVANCE(505);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(567);
      if (lookahead != 0) ADVANCE(566);
      END_STATE();
    case 31:
      if (lookahead == ')') ADVANCE(597);
      if (lookahead == ';') ADVANCE(504);
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(212);
      if (lookahead == 'D' ||
          lookahead == 'd') ADVANCE(193);
      if (lookahead == 'F' ||
          lookahead == 'f') ADVANCE(444);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(309);
      if (lookahead == 'K' ||
          lookahead == 'k') ADVANCE(201);
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(236);
      if (lookahead == 'M' ||
          lookahead == 'm') ADVANCE(103);
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(351);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(332);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(81);
      if (lookahead == 'U' ||
          lookahead == 'u') ADVANCE(397);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(31)
      END_STATE();
    case 32:
      if (lookahead == ',') ADVANCE(502);
      if (lookahead == '_') ADVANCE(559);
      if (lookahead == 'F' ||
          lookahead == 'f') ADVANCE(546);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(32)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(560);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(509);
      END_STATE();
    case 33:
      if (lookahead == '-') ADVANCE(477);
      END_STATE();
    case 34:
      if (lookahead == '-') ADVANCE(483);
      END_STATE();
    case 35:
      if (lookahead == '-') ADVANCE(489);
      END_STATE();
    case 36:
      if (lookahead == '-') ADVANCE(495);
      END_STATE();
    case 37:
      if (lookahead == ';') ADVANCE(504);
      if (lookahead == '_') ADVANCE(559);
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(540);
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(538);
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(551);
      if (lookahead == 'W' ||
          lookahead == 'w') ADVANCE(533);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(37)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(560);
      if (('B' <= lookahead && lookahead <= 'Z') ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(509);
      END_STATE();
    case 38:
      if (lookahead == 'A') ADVANCE(58);
      END_STATE();
    case 39:
      if (lookahead == 'A') ADVANCE(54);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'f')) ADVANCE(479);
      END_STATE();
    case 40:
      if (lookahead == 'A') ADVANCE(60);
      if (lookahead == 'U') ADVANCE(57);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'f')) ADVANCE(479);
      END_STATE();
    case 41:
      if (lookahead == 'E') ADVANCE(579);
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(125);
      END_STATE();
    case 42:
      if (lookahead == 'E') ADVANCE(582);
      END_STATE();
    case 43:
      if (lookahead == 'E') ADVANCE(581);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(471);
      END_STATE();
    case 44:
      if (lookahead == 'E') ADVANCE(584);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(469);
      END_STATE();
    case 45:
      if (lookahead == 'F') ADVANCE(50);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(402);
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(168);
      END_STATE();
    case 46:
      if (lookahead == 'F') ADVANCE(50);
      if (lookahead == 'P' ||
          lookahead == 'p') ADVANCE(436);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(317);
      END_STATE();
    case 47:
      if (lookahead == 'F') ADVANCE(51);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(473);
      END_STATE();
    case 48:
      if (lookahead == 'I') ADVANCE(67);
      END_STATE();
    case 49:
      if (lookahead == 'I') ADVANCE(68);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(467);
      END_STATE();
    case 50:
      if (lookahead == 'I') ADVANCE(62);
      END_STATE();
    case 51:
      if (lookahead == 'I') ADVANCE(63);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(471);
      END_STATE();
    case 52:
      if (lookahead == 'L') ADVANCE(65);
      END_STATE();
    case 53:
      if (lookahead == 'L') ADVANCE(593);
      END_STATE();
    case 54:
      if (lookahead == 'L') ADVANCE(66);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(473);
      END_STATE();
    case 55:
      if (lookahead == 'L') ADVANCE(595);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(471);
      END_STATE();
    case 56:
      if (lookahead == 'L') ADVANCE(53);
      END_STATE();
    case 57:
      if (lookahead == 'L') ADVANCE(55);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(473);
      END_STATE();
    case 58:
      if (lookahead == 'N') ADVANCE(571);
      END_STATE();
    case 59:
      if (lookahead == 'N') ADVANCE(47);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(479);
      END_STATE();
    case 60:
      if (lookahead == 'N') ADVANCE(573);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(473);
      END_STATE();
    case 61:
      if (lookahead == 'N') ADVANCE(46);
      if (lookahead == 'n') ADVANCE(336);
      END_STATE();
    case 62:
      if (lookahead == 'N') ADVANCE(48);
      END_STATE();
    case 63:
      if (lookahead == 'N') ADVANCE(49);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(469);
      END_STATE();
    case 64:
      if (lookahead == 'R') ADVANCE(70);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(479);
      END_STATE();
    case 65:
      if (lookahead == 'S') ADVANCE(42);
      END_STATE();
    case 66:
      if (lookahead == 'S') ADVANCE(44);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(471);
      END_STATE();
    case 67:
      if (lookahead == 'T') ADVANCE(71);
      END_STATE();
    case 68:
      if (lookahead == 'T') ADVANCE(72);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(465);
      END_STATE();
    case 69:
      if (lookahead == 'U') ADVANCE(41);
      if (lookahead == 'u') ADVANCE(292);
      END_STATE();
    case 70:
      if (lookahead == 'U') ADVANCE(43);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(473);
      END_STATE();
    case 71:
      if (lookahead == 'Y') ADVANCE(574);
      END_STATE();
    case 72:
      if (lookahead == 'Y') ADVANCE(575);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(35);
      END_STATE();
    case 73:
      if (lookahead == 'Y') ADVANCE(628);
      if (lookahead == 'y') ADVANCE(627);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(473);
      END_STATE();
    case 74:
      if (lookahead == '_') ADVANCE(559);
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(520);
      if (lookahead == 'D' ||
          lookahead == 'd') ADVANCE(550);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(528);
      if (lookahead == 'W' ||
          lookahead == 'w') ADVANCE(537);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(74)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(560);
      if (('B' <= lookahead && lookahead <= 'Z') ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(509);
      END_STATE();
    case 75:
      if (lookahead == '_') ADVANCE(559);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(542);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(75)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(560);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(509);
      END_STATE();
    case 76:
      if (lookahead == '_') ADVANCE(559);
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(554);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(76)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(560);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(509);
      END_STATE();
    case 77:
      if (lookahead == '_') ADVANCE(559);
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(529);
      if (lookahead == 'U' ||
          lookahead == 'u') ADVANCE(553);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(77)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(560);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(509);
      END_STATE();
    case 78:
      if (lookahead == '_') ADVANCE(559);
      if (lookahead == 'U' ||
          lookahead == 'u') ADVANCE(553);
      if (lookahead == 'W' ||
          lookahead == 'w') ADVANCE(533);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(78)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(560);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(509);
      END_STATE();
    case 79:
      if (lookahead == '_') ADVANCE(559);
      if (lookahead == 'W' ||
          lookahead == 'w') ADVANCE(533);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(79)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(560);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(509);
      END_STATE();
    case 80:
      if (lookahead == '_') ADVANCE(449);
      END_STATE();
    case 81:
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(107);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(252);
      if (lookahead == 'Y' ||
          lookahead == 'y') ADVANCE(341);
      END_STATE();
    case 82:
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(283);
      END_STATE();
    case 83:
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(300);
      END_STATE();
    case 84:
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(275);
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(306);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(167);
      END_STATE();
    case 85:
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(388);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(354);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(233);
      END_STATE();
    case 86:
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(419);
      END_STATE();
    case 87:
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(280);
      END_STATE();
    case 88:
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(214);
      END_STATE();
    case 89:
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(263);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(169);
      END_STATE();
    case 90:
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(296);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(279);
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(207);
      END_STATE();
    case 91:
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(118);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(121);
      END_STATE();
    case 92:
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(257);
      END_STATE();
    case 93:
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(274);
      END_STATE();
    case 94:
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(415);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(209);
      if (lookahead == 'Y' ||
          lookahead == 'y') ADVANCE(630);
      END_STATE();
    case 95:
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(356);
      END_STATE();
    case 96:
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(245);
      END_STATE();
    case 97:
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(119);
      END_STATE();
    case 98:
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(421);
      END_STATE();
    case 99:
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(216);
      END_STATE();
    case 100:
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(120);
      END_STATE();
    case 101:
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(422);
      END_STATE();
    case 102:
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(427);
      END_STATE();
    case 103:
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(428);
      END_STATE();
    case 104:
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(108);
      END_STATE();
    case 105:
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(430);
      END_STATE();
    case 106:
      if (lookahead == 'B' ||
          lookahead == 'b') ADVANCE(161);
      END_STATE();
    case 107:
      if (lookahead == 'B' ||
          lookahead == 'b') ADVANCE(268);
      END_STATE();
    case 108:
      if (lookahead == 'B' ||
          lookahead == 'b') ADVANCE(272);
      END_STATE();
    case 109:
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(700);
      END_STATE();
    case 110:
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(702);
      END_STATE();
    case 111:
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(631);
      END_STATE();
    case 112:
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(632);
      END_STATE();
    case 113:
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(223);
      END_STATE();
    case 114:
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(442);
      END_STATE();
    case 115:
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(407);
      END_STATE();
    case 116:
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(408);
      END_STATE();
    case 117:
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(362);
      END_STATE();
    case 118:
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(155);
      END_STATE();
    case 119:
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(188);
      END_STATE();
    case 120:
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(165);
      END_STATE();
    case 121:
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(105);
      END_STATE();
    case 122:
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(321);
      END_STATE();
    case 123:
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(435);
      END_STATE();
    case 124:
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(429);
      END_STATE();
    case 125:
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(101);
      END_STATE();
    case 126:
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(431);
      END_STATE();
    case 127:
      if (lookahead == 'D' ||
          lookahead == 'd') ADVANCE(745);
      END_STATE();
    case 128:
      if (lookahead == 'D' ||
          lookahead == 'd') ADVANCE(703);
      END_STATE();
    case 129:
      if (lookahead == 'D' ||
          lookahead == 'd') ADVANCE(620);
      END_STATE();
    case 130:
      if (lookahead == 'D' ||
          lookahead == 'd') ADVANCE(730);
      END_STATE();
    case 131:
      if (lookahead == 'D' ||
          lookahead == 'd') ADVANCE(639);
      END_STATE();
    case 132:
      if (lookahead == 'D' ||
          lookahead == 'd') ADVANCE(735);
      END_STATE();
    case 133:
      if (lookahead == 'D' ||
          lookahead == 'd') ADVANCE(640);
      END_STATE();
    case 134:
      if (lookahead == 'D' ||
          lookahead == 'd') ADVANCE(693);
      END_STATE();
    case 135:
      if (lookahead == 'D' ||
          lookahead == 'd') ADVANCE(174);
      END_STATE();
    case 136:
      if (lookahead == 'D' ||
          lookahead == 'd') ADVANCE(232);
      END_STATE();
    case 137:
      if (lookahead == 'D' ||
          lookahead == 'd') ADVANCE(170);
      END_STATE();
    case 138:
      if (lookahead == 'D' ||
          lookahead == 'd') ADVANCE(98);
      END_STATE();
    case 139:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(264);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(318);
      if (lookahead == 'U' ||
          lookahead == 'u') ADVANCE(355);
      END_STATE();
    case 140:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(667);
      END_STATE();
    case 141:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(667);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(291);
      END_STATE();
    case 142:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(361);
      END_STATE();
    case 143:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(654);
      END_STATE();
    case 144:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(701);
      END_STATE();
    case 145:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(619);
      END_STATE();
    case 146:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(656);
      END_STATE();
    case 147:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(633);
      END_STATE();
    case 148:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(746);
      END_STATE();
    case 149:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(670);
      END_STATE();
    case 150:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(664);
      END_STATE();
    case 151:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(653);
      END_STATE();
    case 152:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(338);
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(270);
      END_STATE();
    case 153:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(696);
      END_STATE();
    case 154:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(80);
      END_STATE();
    case 155:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(699);
      END_STATE();
    case 156:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(742);
      END_STATE();
    case 157:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(708);
      END_STATE();
    case 158:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(691);
      END_STATE();
    case 159:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(73);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(479);
      END_STATE();
    case 160:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(677);
      END_STATE();
    case 161:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(676);
      END_STATE();
    case 162:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(692);
      END_STATE();
    case 163:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(675);
      END_STATE();
    case 164:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(686);
      END_STATE();
    case 165:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(680);
      END_STATE();
    case 166:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(267);
      if (lookahead == 'F' ||
          lookahead == 'f') ADVANCE(440);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(322);
      if (lookahead == 'U' ||
          lookahead == 'u') ADVANCE(340);
      END_STATE();
    case 167:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(86);
      END_STATE();
    case 168:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(360);
      END_STATE();
    case 169:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(448);
      END_STATE();
    case 170:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(451);
      END_STATE();
    case 171:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(458);
      END_STATE();
    case 172:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(346);
      END_STATE();
    case 173:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(115);
      END_STATE();
    case 174:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(347);
      END_STATE();
    case 175:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(455);
      END_STATE();
    case 176:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(130);
      END_STATE();
    case 177:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(123);
      END_STATE();
    case 178:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(131);
      END_STATE();
    case 179:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(373);
      END_STATE();
    case 180:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(374);
      END_STATE();
    case 181:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(133);
      END_STATE();
    case 182:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(221);
      END_STATE();
    case 183:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(357);
      END_STATE();
    case 184:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(134);
      END_STATE();
    case 185:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(370);
      END_STATE();
    case 186:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(114);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(389);
      END_STATE();
    case 187:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(348);
      END_STATE();
    case 188:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(379);
      END_STATE();
    case 189:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(349);
      END_STATE();
    case 190:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(381);
      END_STATE();
    case 191:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(350);
      END_STATE();
    case 192:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(392);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(318);
      END_STATE();
    case 193:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(393);
      END_STATE();
    case 194:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(352);
      END_STATE();
    case 195:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(366);
      END_STATE();
    case 196:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(353);
      END_STATE();
    case 197:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(420);
      END_STATE();
    case 198:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(394);
      END_STATE();
    case 199:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(266);
      END_STATE();
    case 200:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(371);
      END_STATE();
    case 201:
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(459);
      END_STATE();
    case 202:
      if (lookahead == 'F' ||
          lookahead == 'f') ADVANCE(634);
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(625);
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(705);
      END_STATE();
    case 203:
      if (lookahead == 'F' ||
          lookahead == 'f') ADVANCE(690);
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(658);
      if (lookahead == 'P' ||
          lookahead == 'p') ADVANCE(416);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(135);
      END_STATE();
    case 204:
      if (lookahead == 'F' ||
          lookahead == 'f') ADVANCE(456);
      END_STATE();
    case 205:
      if (lookahead == 'F' ||
          lookahead == 'f') ADVANCE(441);
      END_STATE();
    case 206:
      if (lookahead == 'G' ||
          lookahead == 'g') ADVANCE(644);
      END_STATE();
    case 207:
      if (lookahead == 'G' ||
          lookahead == 'g') ADVANCE(213);
      END_STATE();
    case 208:
      if (lookahead == 'G' ||
          lookahead == 'g') ADVANCE(616);
      END_STATE();
    case 209:
      if (lookahead == 'G' ||
          lookahead == 'g') ADVANCE(235);
      END_STATE();
    case 210:
      if (lookahead == 'G' ||
          lookahead == 'g') ADVANCE(438);
      END_STATE();
    case 211:
      if (lookahead == 'G' ||
          lookahead == 'g') ADVANCE(218);
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(258);
      if (lookahead == 'U' ||
          lookahead == 'u') ADVANCE(412);
      END_STATE();
    case 212:
      if (lookahead == 'G' ||
          lookahead == 'g') ADVANCE(218);
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(261);
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(111);
      END_STATE();
    case 213:
      if (lookahead == 'G' ||
          lookahead == 'g') ADVANCE(178);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(287);
      END_STATE();
    case 214:
      if (lookahead == 'G' ||
          lookahead == 'g') ADVANCE(156);
      END_STATE();
    case 215:
      if (lookahead == 'G' ||
          lookahead == 'g') ADVANCE(181);
      END_STATE();
    case 216:
      if (lookahead == 'G' ||
          lookahead == 'g') ADVANCE(157);
      END_STATE();
    case 217:
      if (lookahead == 'G' ||
          lookahead == 'g') ADVANCE(196);
      END_STATE();
    case 218:
      if (lookahead == 'G' ||
          lookahead == 'g') ADVANCE(368);
      END_STATE();
    case 219:
      if (lookahead == 'G' ||
          lookahead == 'g') ADVANCE(215);
      END_STATE();
    case 220:
      if (lookahead == 'G' ||
          lookahead == 'g') ADVANCE(217);
      END_STATE();
    case 221:
      if (lookahead == 'G' ||
          lookahead == 'g') ADVANCE(102);
      END_STATE();
    case 222:
      if (lookahead == 'H' ||
          lookahead == 'h') ADVANCE(732);
      END_STATE();
    case 223:
      if (lookahead == 'H' ||
          lookahead == 'h') ADVANCE(643);
      END_STATE();
    case 224:
      if (lookahead == 'H' ||
          lookahead == 'h') ADVANCE(142);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(401);
      END_STATE();
    case 225:
      if (lookahead == 'H' ||
          lookahead == 'h') ADVANCE(328);
      END_STATE();
    case 226:
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(276);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(313);
      if (lookahead == 'U' ||
          lookahead == 'u') ADVANCE(297);
      END_STATE();
    case 227:
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(446);
      END_STATE();
    case 228:
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(460);
      END_STATE();
    case 229:
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(106);
      END_STATE();
    case 230:
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(402);
      END_STATE();
    case 231:
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(402);
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(168);
      END_STATE();
    case 232:
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(204);
      END_STATE();
    case 233:
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(282);
      END_STATE();
    case 234:
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(291);
      END_STATE();
    case 235:
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(286);
      END_STATE();
    case 236:
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(278);
      END_STATE();
    case 237:
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(405);
      END_STATE();
    case 238:
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(299);
      END_STATE();
    case 239:
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(389);
      END_STATE();
    case 240:
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(310);
      END_STATE();
    case 241:
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(461);
      END_STATE();
    case 242:
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(284);
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(669);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(432);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(255);
      if (lookahead == 'Y' ||
          lookahead == 'y') ADVANCE(341);
      END_STATE();
    case 243:
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(391);
      END_STATE();
    case 244:
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(93);
      END_STATE();
    case 245:
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(305);
      END_STATE();
    case 246:
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(323);
      END_STATE();
    case 247:
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(330);
      END_STATE();
    case 248:
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(331);
      END_STATE();
    case 249:
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(325);
      END_STATE();
    case 250:
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(326);
      END_STATE();
    case 251:
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(425);
      END_STATE();
    case 252:
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(220);
      END_STATE();
    case 253:
      if (lookahead == 'K' ||
          lookahead == 'k') ADVANCE(149);
      END_STATE();
    case 254:
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(262);
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(129);
      if (lookahead == 'P' ||
          lookahead == 'p') ADVANCE(335);
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(704);
      END_STATE();
    case 255:
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(652);
      END_STATE();
    case 256:
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(706);
      END_STATE();
    case 257:
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(205);
      END_STATE();
    case 258:
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(671);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(172);
      END_STATE();
    case 259:
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(453);
      END_STATE();
    case 260:
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(91);
      END_STATE();
    case 261:
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(314);
      END_STATE();
    case 262:
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(314);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(172);
      END_STATE();
    case 263:
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(437);
      END_STATE();
    case 264:
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(197);
      END_STATE();
    case 265:
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(320);
      END_STATE();
    case 266:
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(173);
      END_STATE();
    case 267:
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(173);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(665);
      END_STATE();
    case 268:
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(143);
      END_STATE();
    case 269:
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(256);
      END_STATE();
    case 270:
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(179);
      END_STATE();
    case 271:
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(176);
      END_STATE();
    case 272:
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(154);
      END_STATE();
    case 273:
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(164);
      END_STATE();
    case 274:
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(241);
      END_STATE();
    case 275:
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(271);
      END_STATE();
    case 276:
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(423);
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(92);
      END_STATE();
    case 277:
      if (lookahead == 'M' ||
          lookahead == 'm') ADVANCE(610);
      END_STATE();
    case 278:
      if (lookahead == 'M' ||
          lookahead == 'm') ADVANCE(237);
      END_STATE();
    case 279:
      if (lookahead == 'M' ||
          lookahead == 'm') ADVANCE(237);
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(403);
      END_STATE();
    case 280:
      if (lookahead == 'M' ||
          lookahead == 'm') ADVANCE(334);
      END_STATE();
    case 281:
      if (lookahead == 'M' ||
          lookahead == 'm') ADVANCE(243);
      END_STATE();
    case 282:
      if (lookahead == 'M' ||
          lookahead == 'm') ADVANCE(95);
      END_STATE();
    case 283:
      if (lookahead == 'M' ||
          lookahead == 'm') ADVANCE(148);
      END_STATE();
    case 284:
      if (lookahead == 'M' ||
          lookahead == 'm') ADVANCE(198);
      END_STATE();
    case 285:
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(614);
      END_STATE();
    case 286:
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(638);
      END_STATE();
    case 287:
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(736);
      END_STATE();
    case 288:
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(733);
      END_STATE();
    case 289:
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(336);
      END_STATE();
    case 290:
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(684);
      END_STATE();
    case 291:
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(206);
      END_STATE();
    case 292:
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(125);
      END_STATE();
    case 293:
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(82);
      END_STATE();
    case 294:
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(82);
      if (lookahead == 'V' ||
          lookahead == 'v') ADVANCE(315);
      END_STATE();
    case 295:
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(128);
      END_STATE();
    case 296:
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(210);
      END_STATE();
    case 297:
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(124);
      END_STATE();
    case 298:
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(265);
      if (lookahead == 'P' ||
          lookahead == 'p') ADVANCE(138);
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(141);
      END_STATE();
    case 299:
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(208);
      END_STATE();
    case 300:
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(404);
      END_STATE();
    case 301:
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(109);
      END_STATE();
    case 302:
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(375);
      END_STATE();
    case 303:
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(110);
      END_STATE();
    case 304:
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(376);
      END_STATE();
    case 305:
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(377);
      END_STATE();
    case 306:
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(417);
      if (lookahead == 'U' ||
          lookahead == 'u') ADVANCE(311);
      END_STATE();
    case 307:
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(378);
      END_STATE();
    case 308:
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(380);
      END_STATE();
    case 309:
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(137);
      END_STATE();
    case 310:
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(116);
      END_STATE();
    case 311:
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(424);
      END_STATE();
    case 312:
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(126);
      END_STATE();
    case 313:
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(277);
      END_STATE();
    case 314:
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(447);
      END_STATE();
    case 315:
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(253);
      END_STATE();
    case 316:
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(367);
      if (lookahead == 'U' ||
          lookahead == 'u') ADVANCE(269);
      END_STATE();
    case 317:
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(649);
      END_STATE();
    case 318:
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(333);
      END_STATE();
    case 319:
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(285);
      END_STATE();
    case 320:
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(219);
      END_STATE();
    case 321:
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(295);
      END_STATE();
    case 322:
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(359);
      END_STATE();
    case 323:
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(302);
      END_STATE();
    case 324:
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(136);
      END_STATE();
    case 325:
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(288);
      END_STATE();
    case 326:
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(290);
      END_STATE();
    case 327:
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(358);
      END_STATE();
    case 328:
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(364);
      END_STATE();
    case 329:
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(270);
      END_STATE();
    case 330:
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(307);
      END_STATE();
    case 331:
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(308);
      END_STATE();
    case 332:
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(273);
      END_STATE();
    case 333:
      if (lookahead == 'P' ||
          lookahead == 'p') ADVANCE(663);
      END_STATE();
    case 334:
      if (lookahead == 'P' ||
          lookahead == 'p') ADVANCE(645);
      END_STATE();
    case 335:
      if (lookahead == 'P' ||
          lookahead == 'p') ADVANCE(259);
      END_STATE();
    case 336:
      if (lookahead == 'P' ||
          lookahead == 'p') ADVANCE(436);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(317);
      END_STATE();
    case 337:
      if (lookahead == 'P' ||
          lookahead == 'p') ADVANCE(144);
      END_STATE();
    case 338:
      if (lookahead == 'P' ||
          lookahead == 'p') ADVANCE(260);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(433);
      if (lookahead == 'V' ||
          lookahead == 'v') ADVANCE(315);
      END_STATE();
    case 339:
      if (lookahead == 'P' ||
          lookahead == 'p') ADVANCE(97);
      END_STATE();
    case 340:
      if (lookahead == 'P' ||
          lookahead == 'p') ADVANCE(183);
      END_STATE();
    case 341:
      if (lookahead == 'P' ||
          lookahead == 'p') ADVANCE(153);
      END_STATE();
    case 342:
      if (lookahead == 'P' ||
          lookahead == 'p') ADVANCE(100);
      END_STATE();
    case 343:
      if (lookahead == 'P' ||
          lookahead == 'p') ADVANCE(200);
      END_STATE();
    case 344:
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(167);
      END_STATE();
    case 345:
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(83);
      END_STATE();
    case 346:
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(674);
      END_STATE();
    case 347:
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(629);
      END_STATE();
    case 348:
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(641);
      END_STATE();
    case 349:
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(737);
      END_STATE();
    case 350:
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(744);
      END_STATE();
    case 351:
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(698);
      END_STATE();
    case 352:
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(697);
      END_STATE();
    case 353:
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(695);
      END_STATE();
    case 354:
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(281);
      END_STATE();
    case 355:
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(104);
      END_STATE();
    case 356:
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(454);
      END_STATE();
    case 357:
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(434);
      END_STATE();
    case 358:
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(132);
      END_STATE();
    case 359:
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(88);
      END_STATE();
    case 360:
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(406);
      END_STATE();
    case 361:
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(145);
      END_STATE();
    case 362:
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(229);
      END_STATE();
    case 363:
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(304);
      END_STATE();
    case 364:
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(228);
      END_STATE();
    case 365:
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(390);
      END_STATE();
    case 366:
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(244);
      END_STATE();
    case 367:
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(177);
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(443);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(650);
      END_STATE();
    case 368:
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(182);
      END_STATE();
    case 369:
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(251);
      END_STATE();
    case 370:
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(238);
      END_STATE();
    case 371:
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(439);
      END_STATE();
    case 372:
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(636);
      END_STATE();
    case 373:
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(683);
      END_STATE();
    case 374:
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(651);
      END_STATE();
    case 375:
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(738);
      END_STATE();
    case 376:
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(707);
      END_STATE();
    case 377:
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(626);
      END_STATE();
    case 378:
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(679);
      END_STATE();
    case 379:
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(682);
      END_STATE();
    case 380:
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(673);
      END_STATE();
    case 381:
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(734);
      END_STATE();
    case 382:
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(319);
      END_STATE();
    case 383:
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(168);
      END_STATE();
    case 384:
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(414);
      END_STATE();
    case 385:
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(450);
      END_STATE();
    case 386:
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(339);
      END_STATE();
    case 387:
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(403);
      END_STATE();
    case 388:
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(385);
      END_STATE();
    case 389:
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(411);
      END_STATE();
    case 390:
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(227);
      END_STATE();
    case 391:
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(398);
      END_STATE();
    case 392:
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(117);
      END_STATE();
    case 393:
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(112);
      END_STATE();
    case 394:
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(418);
      END_STATE();
    case 395:
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(189);
      END_STATE();
    case 396:
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(191);
      END_STATE();
    case 397:
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(194);
      END_STATE();
    case 398:
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(248);
      END_STATE();
    case 399:
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(342);
      END_STATE();
    case 400:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(665);
      END_STATE();
    case 401:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(222);
      END_STATE();
    case 402:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(122);
      END_STATE();
    case 403:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(688);
      END_STATE();
    case 404:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(668);
      END_STATE();
    case 405:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(617);
      END_STATE();
    case 406:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(648);
      END_STATE();
    case 407:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(612);
      END_STATE();
    case 408:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(613);
      END_STATE();
    case 409:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(731);
      END_STATE();
    case 410:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(518);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(410)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(560);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(509);
      END_STATE();
    case 411:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(372);
      END_STATE();
    case 412:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(225);
      END_STATE();
    case 413:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(172);
      END_STATE();
    case 414:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(240);
      END_STATE();
    case 415:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(113);
      END_STATE();
    case 416:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(246);
      END_STATE();
    case 417:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(96);
      END_STATE();
    case 418:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(87);
      END_STATE();
    case 419:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(146);
      END_STATE();
    case 420:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(147);
      END_STATE();
    case 421:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(150);
      END_STATE();
    case 422:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(151);
      END_STATE();
    case 423:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(185);
      END_STATE();
    case 424:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(187);
      END_STATE();
    case 425:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(190);
      END_STATE();
    case 426:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(160);
      END_STATE();
    case 427:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(162);
      END_STATE();
    case 428:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(195);
      END_STATE();
    case 429:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(247);
      END_STATE();
    case 430:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(249);
      END_STATE();
    case 431:
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(250);
      END_STATE();
    case 432:
      if (lookahead == 'U' ||
          lookahead == 'u') ADVANCE(292);
      END_STATE();
    case 433:
      if (lookahead == 'U' ||
          lookahead == 'u') ADVANCE(363);
      END_STATE();
    case 434:
      if (lookahead == 'U' ||
          lookahead == 'u') ADVANCE(395);
      END_STATE();
    case 435:
      if (lookahead == 'U' ||
          lookahead == 'u') ADVANCE(365);
      END_STATE();
    case 436:
      if (lookahead == 'U' ||
          lookahead == 'u') ADVANCE(409);
      END_STATE();
    case 437:
      if (lookahead == 'U' ||
          lookahead == 'u') ADVANCE(180);
      END_STATE();
    case 438:
      if (lookahead == 'U' ||
          lookahead == 'u') ADVANCE(99);
      END_STATE();
    case 439:
      if (lookahead == 'U' ||
          lookahead == 'u') ADVANCE(396);
      END_STATE();
    case 440:
      if (lookahead == 'U' ||
          lookahead == 'u') ADVANCE(301);
      END_STATE();
    case 441:
      if (lookahead == 'U' ||
          lookahead == 'u') ADVANCE(303);
      END_STATE();
    case 442:
      if (lookahead == 'U' ||
          lookahead == 'u') ADVANCE(426);
      END_STATE();
    case 443:
      if (lookahead == 'U' ||
          lookahead == 'u') ADVANCE(343);
      END_STATE();
    case 444:
      if (lookahead == 'U' ||
          lookahead == 'u') ADVANCE(312);
      END_STATE();
    case 445:
      if (lookahead == 'V' ||
          lookahead == 'v') ADVANCE(315);
      END_STATE();
    case 446:
      if (lookahead == 'V' ||
          lookahead == 'v') ADVANCE(158);
      END_STATE();
    case 447:
      if (lookahead == 'W' ||
          lookahead == 'w') ADVANCE(615);
      END_STATE();
    case 448:
      if (lookahead == 'W' ||
          lookahead == 'w') ADVANCE(694);
      END_STATE();
    case 449:
      if (lookahead == 'W' ||
          lookahead == 'w') ADVANCE(369);
      END_STATE();
    case 450:
      if (lookahead == 'W' ||
          lookahead == 'w') ADVANCE(327);
      END_STATE();
    case 451:
      if (lookahead == 'X' ||
          lookahead == 'x') ADVANCE(657);
      END_STATE();
    case 452:
      if (lookahead == 'X' ||
          lookahead == 'x') ADVANCE(186);
      END_STATE();
    case 453:
      if (lookahead == 'Y' ||
          lookahead == 'y') ADVANCE(747);
      END_STATE();
    case 454:
      if (lookahead == 'Y' ||
          lookahead == 'y') ADVANCE(739);
      END_STATE();
    case 455:
      if (lookahead == 'Y' ||
          lookahead == 'y') ADVANCE(627);
      END_STATE();
    case 456:
      if (lookahead == 'Y' ||
          lookahead == 'y') ADVANCE(678);
      END_STATE();
    case 457:
      if (lookahead == 'Y' ||
          lookahead == 'y') ADVANCE(337);
      END_STATE();
    case 458:
      if (lookahead == 'Y' ||
          lookahead == 'y') ADVANCE(386);
      END_STATE();
    case 459:
      if (lookahead == 'Y' ||
          lookahead == 'y') ADVANCE(399);
      END_STATE();
    case 460:
      if (lookahead == 'Z' ||
          lookahead == 'z') ADVANCE(163);
      END_STATE();
    case 461:
      if (lookahead == 'Z' ||
          lookahead == 'z') ADVANCE(184);
      END_STATE();
    case 462:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(647);
      END_STATE();
    case 463:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(587);
      END_STATE();
    case 464:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(592);
      if (('G' <= lookahead && lookahead <= '`')) ADVANCE(473);
      END_STATE();
    case 465:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(35);
      END_STATE();
    case 466:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(585);
      END_STATE();
    case 467:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(465);
      END_STATE();
    case 468:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(466);
      END_STATE();
    case 469:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(467);
      END_STATE();
    case 470:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(468);
      END_STATE();
    case 471:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(469);
      END_STATE();
    case 472:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(470);
      END_STATE();
    case 473:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(471);
      END_STATE();
    case 474:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(36);
      END_STATE();
    case 475:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(474);
      END_STATE();
    case 476:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(475);
      END_STATE();
    case 477:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(476);
      END_STATE();
    case 478:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(472);
      END_STATE();
    case 479:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(473);
      END_STATE();
    case 480:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(33);
      END_STATE();
    case 481:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(480);
      END_STATE();
    case 482:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(481);
      END_STATE();
    case 483:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(482);
      END_STATE();
    case 484:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(478);
      END_STATE();
    case 485:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(479);
      END_STATE();
    case 486:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(34);
      END_STATE();
    case 487:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(486);
      END_STATE();
    case 488:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(487);
      END_STATE();
    case 489:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(488);
      END_STATE();
    case 490:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(484);
      END_STATE();
    case 491:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(490);
      END_STATE();
    case 492:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(491);
      END_STATE();
    case 493:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(492);
      END_STATE();
    case 494:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(493);
      END_STATE();
    case 495:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(494);
      END_STATE();
    case 496:
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(19);
      END_STATE();
    case 497:
      if (lookahead != 0 &&
          lookahead != '$') ADVANCE(569);
      END_STATE();
    case 498:
      if (lookahead != 0 &&
          lookahead != '$') ADVANCE(29);
      END_STATE();
    case 499:
      if (eof) ADVANCE(501);
      if (lookahead == '$') ADVANCE(25);
      if (lookahead == '\'') ADVANCE(505);
      if (lookahead == ')') ADVANCE(597);
      if (lookahead == ',') ADVANCE(502);
      if (lookahead == '.') ADVANCE(503);
      if (lookahead == ':') ADVANCE(601);
      if (lookahead == ';') ADVANCE(504);
      if (lookahead == '<') ADVANCE(602);
      if (lookahead == '=') ADVANCE(623);
      if (lookahead == '>') ADVANCE(603);
      if (lookahead == ']') ADVANCE(608);
      if (lookahead == '}') ADVANCE(605);
      if (lookahead == '*' ||
          lookahead == '/') ADVANCE(599);
      if (('+' <= lookahead && lookahead <= '-')) ADVANCE(578);
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(254);
      if (lookahead == 'B' ||
          lookahead == 'b') ADVANCE(94);
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(84);
      if (lookahead == 'D' ||
          lookahead == 'd') ADVANCE(139);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(577);
      if (lookahead == 'F' ||
          lookahead == 'f') ADVANCE(226);
      if (lookahead == 'G' ||
          lookahead == 'g') ADVANCE(345);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(202);
      if (lookahead == 'J' ||
          lookahead == 'j') ADVANCE(382);
      if (lookahead == 'K' ||
          lookahead == 'k') ADVANCE(171);
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(90);
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(316);
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(203);
      if (lookahead == 'P' ||
          lookahead == 'p') ADVANCE(85);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(152);
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(166);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(242);
      if (lookahead == 'U' ||
          lookahead == 'u') ADVANCE(298);
      if (lookahead == 'V' ||
          lookahead == 'v') ADVANCE(89);
      if (lookahead == 'W' ||
          lookahead == 'w') ADVANCE(224);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(499)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(560);
      END_STATE();
    case 500:
      if (eof) ADVANCE(501);
      if (lookahead == ';') ADVANCE(504);
      if (lookahead == '_') ADVANCE(559);
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(541);
      if (lookahead == 'B' ||
          lookahead == 'b') ADVANCE(522);
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(548);
      if (lookahead == 'D' ||
          lookahead == 'd') ADVANCE(524);
      if (lookahead == 'G' ||
          lookahead == 'g') ADVANCE(549);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(543);
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(539);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(527);
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(530);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(547);
      if (lookahead == 'U' ||
          lookahead == 'u') ADVANCE(545);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(500)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(560);
      if (('E' <= lookahead && lookahead <= 'Z') ||
          ('e' <= lookahead && lookahead <= 'z')) ADVANCE(509);
      END_STATE();
    case 501:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 502:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 503:
      ACCEPT_TOKEN(anon_sym_DOT);
      END_STATE();
    case 504:
      ACCEPT_TOKEN(anon_sym_SEMI);
      END_STATE();
    case 505:
      ACCEPT_TOKEN(anon_sym_SQUOTE);
      END_STATE();
    case 506:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      END_STATE();
    case 507:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(19);
      END_STATE();
    case 508:
      ACCEPT_TOKEN(sym_double_dollar);
      END_STATE();
    case 509:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      END_STATE();
    case 510:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'A') ADVANCE(52);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(313);
      END_STATE();
    case 511:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'A') ADVANCE(58);
      if (lookahead == 'U') ADVANCE(56);
      END_STATE();
    case 512:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'A') ADVANCE(54);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'f')) ADVANCE(479);
      END_STATE();
    case 513:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'A') ADVANCE(60);
      if (lookahead == 'U') ADVANCE(57);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'f')) ADVANCE(479);
      END_STATE();
    case 514:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'N') ADVANCE(45);
      if (lookahead == 'n') ADVANCE(231);
      if (lookahead == 'F' ||
          lookahead == 'f') ADVANCE(634);
      END_STATE();
    case 515:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'N') ADVANCE(47);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(479);
      END_STATE();
    case 516:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'R') ADVANCE(69);
      if (lookahead == 'r') ADVANCE(432);
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(107);
      END_STATE();
    case 517:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'R') ADVANCE(70);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(479);
      END_STATE();
    case 518:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(107);
      END_STATE();
    case 519:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(107);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(432);
      END_STATE();
    case 520:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'D' ||
          lookahead == 'd') ADVANCE(127);
      END_STATE();
    case 521:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'D' ||
          lookahead == 'd') ADVANCE(127);
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(262);
      if (lookahead == 'P' ||
          lookahead == 'p') ADVANCE(335);
      END_STATE();
    case 522:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(209);
      END_STATE();
    case 523:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(264);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(384);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(318);
      END_STATE();
    case 524:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(264);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(318);
      END_STATE();
    case 525:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(294);
      END_STATE();
    case 526:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(267);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(457);
      END_STATE();
    case 527:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(445);
      END_STATE();
    case 528:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(293);
      END_STATE();
    case 529:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(400);
      END_STATE();
    case 530:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(266);
      END_STATE();
    case 531:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'F' ||
          lookahead == 'f') ADVANCE(634);
      END_STATE();
    case 532:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'F' ||
          lookahead == 'f') ADVANCE(634);
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(231);
      END_STATE();
    case 533:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'H' ||
          lookahead == 'h') ADVANCE(142);
      END_STATE();
    case 534:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'H' ||
          lookahead == 'h') ADVANCE(142);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(401);
      END_STATE();
    case 535:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(384);
      END_STATE();
    case 536:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(279);
      END_STATE();
    case 537:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(401);
      END_STATE();
    case 538:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(278);
      END_STATE();
    case 539:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(387);
      END_STATE();
    case 540:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(261);
      END_STATE();
    case 541:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(413);
      if (lookahead == 'P' ||
          lookahead == 'p') ADVANCE(335);
      END_STATE();
    case 542:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(230);
      END_STATE();
    case 543:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(383);
      END_STATE();
    case 544:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'P' ||
          lookahead == 'p') ADVANCE(138);
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(141);
      END_STATE();
    case 545:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'P' ||
          lookahead == 'p') ADVANCE(138);
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(140);
      END_STATE();
    case 546:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(313);
      END_STATE();
    case 547:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(432);
      END_STATE();
    case 548:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(167);
      END_STATE();
    case 549:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(83);
      END_STATE();
    case 550:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(318);
      END_STATE();
    case 551:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(135);
      END_STATE();
    case 552:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(319);
      END_STATE();
    case 553:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(234);
      END_STATE();
    case 554:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(457);
      END_STATE();
    case 555:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'X' ||
          lookahead == 'x') ADVANCE(239);
      END_STATE();
    case 556:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == 'X' ||
          lookahead == 'x') ADVANCE(825);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 557:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(479);
      END_STATE();
    case 558:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token1);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 559:
      ACCEPT_TOKEN(anon_sym__);
      END_STATE();
    case 560:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token2);
      END_STATE();
    case 561:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token2);
      if (lookahead == 'X') ADVANCE(464);
      if (lookahead == 'x') ADVANCE(463);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(479);
      END_STATE();
    case 562:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token2);
      if (lookahead == 'X' ||
          lookahead == 'x') ADVANCE(463);
      END_STATE();
    case 563:
      ACCEPT_TOKEN(aux_sym_unquoted_identifier_token2);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(479);
      END_STATE();
    case 564:
      ACCEPT_TOKEN(aux_sym_quoted_identifier_token1);
      END_STATE();
    case 565:
      ACCEPT_TOKEN(aux_sym_quoted_identifier_token1);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(565);
      if (lookahead != 0 &&
          lookahead != '"') ADVANCE(564);
      END_STATE();
    case 566:
      ACCEPT_TOKEN(aux_sym_string_literal_token1);
      END_STATE();
    case 567:
      ACCEPT_TOKEN(aux_sym_string_literal_token1);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(567);
      if (lookahead != 0 &&
          lookahead != '\'') ADVANCE(566);
      END_STATE();
    case 568:
      ACCEPT_TOKEN(aux_sym_string_literal_token2);
      if (lookahead == '$') ADVANCE(497);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(568);
      if (lookahead != 0) ADVANCE(569);
      END_STATE();
    case 569:
      ACCEPT_TOKEN(aux_sym_string_literal_token2);
      if (lookahead == '$') ADVANCE(497);
      if (lookahead != 0) ADVANCE(569);
      END_STATE();
    case 570:
      ACCEPT_TOKEN(anon_sym_DASH);
      END_STATE();
    case 571:
      ACCEPT_TOKEN(sym_nan);
      END_STATE();
    case 572:
      ACCEPT_TOKEN(sym_nan);
      if (('[' <= lookahead && lookahead <= '^') ||
          lookahead == '`') ADVANCE(471);
      if (lookahead == '$' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(924);
      END_STATE();
    case 573:
      ACCEPT_TOKEN(sym_nan);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(471);
      END_STATE();
    case 574:
      ACCEPT_TOKEN(sym_infinity);
      END_STATE();
    case 575:
      ACCEPT_TOKEN(sym_infinity);
      if (lookahead == '-') ADVANCE(489);
      END_STATE();
    case 576:
      ACCEPT_TOKEN(sym_infinity);
      if (lookahead == '-') ADVANCE(489);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 577:
      ACCEPT_TOKEN(sym_scientific_notation_exponent);
      END_STATE();
    case 578:
      ACCEPT_TOKEN(aux_sym_scientific_notation_token1);
      END_STATE();
    case 579:
      ACCEPT_TOKEN(sym_true_literal);
      END_STATE();
    case 580:
      ACCEPT_TOKEN(sym_true_literal);
      if (('[' <= lookahead && lookahead <= '^') ||
          lookahead == '`') ADVANCE(469);
      if (lookahead == '$' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(923);
      END_STATE();
    case 581:
      ACCEPT_TOKEN(sym_true_literal);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(469);
      END_STATE();
    case 582:
      ACCEPT_TOKEN(sym_false_literal);
      END_STATE();
    case 583:
      ACCEPT_TOKEN(sym_false_literal);
      if (('[' <= lookahead && lookahead <= '^') ||
          lookahead == '`') ADVANCE(467);
      if (lookahead == '$' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(922);
      END_STATE();
    case 584:
      ACCEPT_TOKEN(sym_false_literal);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(467);
      END_STATE();
    case 585:
      ACCEPT_TOKEN(sym_uuid_literal);
      END_STATE();
    case 586:
      ACCEPT_TOKEN(sym_blob_literal);
      if (lookahead == '-') ADVANCE(489);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(587);
      END_STATE();
    case 587:
      ACCEPT_TOKEN(sym_blob_literal);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(587);
      END_STATE();
    case 588:
      ACCEPT_TOKEN(sym_blob_literal);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(586);
      if (('G' <= lookahead && lookahead <= '`')) ADVANCE(35);
      END_STATE();
    case 589:
      ACCEPT_TOKEN(sym_blob_literal);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(590);
      if (('G' <= lookahead && lookahead <= '`')) ADVANCE(467);
      END_STATE();
    case 590:
      ACCEPT_TOKEN(sym_blob_literal);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(588);
      if (('G' <= lookahead && lookahead <= '`')) ADVANCE(465);
      END_STATE();
    case 591:
      ACCEPT_TOKEN(sym_blob_literal);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(589);
      if (('G' <= lookahead && lookahead <= '`')) ADVANCE(469);
      END_STATE();
    case 592:
      ACCEPT_TOKEN(sym_blob_literal);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(591);
      if (('G' <= lookahead && lookahead <= '`')) ADVANCE(471);
      END_STATE();
    case 593:
      ACCEPT_TOKEN(sym_null_literal);
      END_STATE();
    case 594:
      ACCEPT_TOKEN(sym_null_literal);
      if (('[' <= lookahead && lookahead <= '^') ||
          lookahead == '`') ADVANCE(469);
      if (lookahead == '$' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(923);
      END_STATE();
    case 595:
      ACCEPT_TOKEN(sym_null_literal);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(469);
      END_STATE();
    case 596:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 597:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 598:
      ACCEPT_TOKEN(sym_arithmetic_operator);
      END_STATE();
    case 599:
      ACCEPT_TOKEN(aux_sym_arithmetic_operation_token1);
      END_STATE();
    case 600:
      ACCEPT_TOKEN(anon_sym_QMARK);
      END_STATE();
    case 601:
      ACCEPT_TOKEN(anon_sym_COLON);
      END_STATE();
    case 602:
      ACCEPT_TOKEN(anon_sym_LT);
      if (lookahead == '=') ADVANCE(621);
      if (lookahead == '>') ADVANCE(622);
      END_STATE();
    case 603:
      ACCEPT_TOKEN(anon_sym_GT);
      if (lookahead == '=') ADVANCE(624);
      END_STATE();
    case 604:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 605:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 606:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      END_STATE();
    case 607:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(479);
      END_STATE();
    case 608:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      END_STATE();
    case 609:
      ACCEPT_TOKEN(sym_column_glob);
      END_STATE();
    case 610:
      ACCEPT_TOKEN(aux_sym_from_spec_token1);
      END_STATE();
    case 611:
      ACCEPT_TOKEN(aux_sym_from_spec_token1);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 612:
      ACCEPT_TOKEN(aux_sym_select_statement_token1);
      END_STATE();
    case 613:
      ACCEPT_TOKEN(aux_sym_select_statement_token2);
      END_STATE();
    case 614:
      ACCEPT_TOKEN(aux_sym_select_statement_token3);
      END_STATE();
    case 615:
      ACCEPT_TOKEN(aux_sym_select_statement_token4);
      END_STATE();
    case 616:
      ACCEPT_TOKEN(aux_sym_select_statement_token5);
      END_STATE();
    case 617:
      ACCEPT_TOKEN(aux_sym_limit_spec_token1);
      END_STATE();
    case 618:
      ACCEPT_TOKEN(sym__code_block);
      END_STATE();
    case 619:
      ACCEPT_TOKEN(aux_sym_where_spec_token1);
      END_STATE();
    case 620:
      ACCEPT_TOKEN(aux_sym_relation_elements_token1);
      END_STATE();
    case 621:
      ACCEPT_TOKEN(anon_sym_LT_EQ);
      END_STATE();
    case 622:
      ACCEPT_TOKEN(anon_sym_LT_GT);
      END_STATE();
    case 623:
      ACCEPT_TOKEN(anon_sym_EQ);
      END_STATE();
    case 624:
      ACCEPT_TOKEN(anon_sym_GT_EQ);
      END_STATE();
    case 625:
      ACCEPT_TOKEN(aux_sym_relation_element_token1);
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(168);
      END_STATE();
    case 626:
      ACCEPT_TOKEN(aux_sym_relation_contains_key_token1);
      END_STATE();
    case 627:
      ACCEPT_TOKEN(aux_sym_relation_contains_key_token2);
      END_STATE();
    case 628:
      ACCEPT_TOKEN(aux_sym_relation_contains_key_token2);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(471);
      END_STATE();
    case 629:
      ACCEPT_TOKEN(aux_sym_order_spec_token1);
      END_STATE();
    case 630:
      ACCEPT_TOKEN(aux_sym_order_spec_token2);
      END_STATE();
    case 631:
      ACCEPT_TOKEN(aux_sym_order_spec_token3);
      END_STATE();
    case 632:
      ACCEPT_TOKEN(aux_sym_order_spec_token4);
      END_STATE();
    case 633:
      ACCEPT_TOKEN(aux_sym_delete_statement_token1);
      END_STATE();
    case 634:
      ACCEPT_TOKEN(aux_sym_delete_statement_token2);
      END_STATE();
    case 635:
      ACCEPT_TOKEN(aux_sym_delete_statement_token2);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 636:
      ACCEPT_TOKEN(aux_sym_delete_statement_token3);
      END_STATE();
    case 637:
      ACCEPT_TOKEN(aux_sym_delete_statement_token3);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 638:
      ACCEPT_TOKEN(aux_sym_begin_batch_token1);
      END_STATE();
    case 639:
      ACCEPT_TOKEN(aux_sym_begin_batch_token2);
      END_STATE();
    case 640:
      ACCEPT_TOKEN(aux_sym_begin_batch_token3);
      END_STATE();
    case 641:
      ACCEPT_TOKEN(aux_sym_begin_batch_token4);
      END_STATE();
    case 642:
      ACCEPT_TOKEN(aux_sym_begin_batch_token4);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 643:
      ACCEPT_TOKEN(aux_sym_begin_batch_token5);
      END_STATE();
    case 644:
      ACCEPT_TOKEN(aux_sym_using_timestamp_spec_token1);
      END_STATE();
    case 645:
      ACCEPT_TOKEN(aux_sym_using_timestamp_spec_token2);
      END_STATE();
    case 646:
      ACCEPT_TOKEN(aux_sym_using_timestamp_spec_token2);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 647:
      ACCEPT_TOKEN(aux_sym_using_timestamp_spec_token3);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(647);
      END_STATE();
    case 648:
      ACCEPT_TOKEN(aux_sym_insert_statement_token1);
      END_STATE();
    case 649:
      ACCEPT_TOKEN(aux_sym_insert_statement_token2);
      END_STATE();
    case 650:
      ACCEPT_TOKEN(aux_sym_insert_statement_token3);
      END_STATE();
    case 651:
      ACCEPT_TOKEN(aux_sym_insert_values_spec_token1);
      END_STATE();
    case 652:
      ACCEPT_TOKEN(aux_sym_using_ttl_timestamp_token1);
      END_STATE();
    case 653:
      ACCEPT_TOKEN(aux_sym_truncate_token1);
      END_STATE();
    case 654:
      ACCEPT_TOKEN(aux_sym_truncate_token2);
      END_STATE();
    case 655:
      ACCEPT_TOKEN(aux_sym_truncate_token2);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 656:
      ACCEPT_TOKEN(aux_sym_create_index_token1);
      END_STATE();
    case 657:
      ACCEPT_TOKEN(aux_sym_create_index_token2);
      END_STATE();
    case 658:
      ACCEPT_TOKEN(aux_sym_create_index_token3);
      END_STATE();
    case 659:
      ACCEPT_TOKEN(aux_sym_create_index_token3);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 660:
      ACCEPT_TOKEN(aux_sym_index_keys_spec_token1);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 661:
      ACCEPT_TOKEN(aux_sym_index_entries_s_spec_token1);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 662:
      ACCEPT_TOKEN(aux_sym_index_full_spec_token1);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 663:
      ACCEPT_TOKEN(aux_sym_drop_index_token1);
      END_STATE();
    case 664:
      ACCEPT_TOKEN(aux_sym_update_token1);
      END_STATE();
    case 665:
      ACCEPT_TOKEN(aux_sym_update_assignments_token1);
      END_STATE();
    case 666:
      ACCEPT_TOKEN(aux_sym_update_assignments_token1);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 667:
      ACCEPT_TOKEN(aux_sym_use_token1);
      END_STATE();
    case 668:
      ACCEPT_TOKEN(aux_sym_grant_token1);
      END_STATE();
    case 669:
      ACCEPT_TOKEN(aux_sym_grant_token2);
      END_STATE();
    case 670:
      ACCEPT_TOKEN(aux_sym_revoke_token1);
      END_STATE();
    case 671:
      ACCEPT_TOKEN(aux_sym_privilege_token1);
      END_STATE();
    case 672:
      ACCEPT_TOKEN(aux_sym_privilege_token1);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 673:
      ACCEPT_TOKEN(aux_sym_privilege_token2);
      END_STATE();
    case 674:
      ACCEPT_TOKEN(aux_sym_privilege_token3);
      END_STATE();
    case 675:
      ACCEPT_TOKEN(aux_sym_privilege_token4);
      END_STATE();
    case 676:
      ACCEPT_TOKEN(aux_sym_privilege_token5);
      END_STATE();
    case 677:
      ACCEPT_TOKEN(aux_sym_privilege_token6);
      END_STATE();
    case 678:
      ACCEPT_TOKEN(aux_sym_privilege_token7);
      END_STATE();
    case 679:
      ACCEPT_TOKEN(aux_sym_resource_token1);
      END_STATE();
    case 680:
      ACCEPT_TOKEN(aux_sym_resource_token2);
      END_STATE();
    case 681:
      ACCEPT_TOKEN(aux_sym_resource_token2);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 682:
      ACCEPT_TOKEN(aux_sym_resource_token3);
      END_STATE();
    case 683:
      ACCEPT_TOKEN(aux_sym_resource_token4);
      END_STATE();
    case 684:
      ACCEPT_TOKEN(aux_sym_resource_token5);
      END_STATE();
    case 685:
      ACCEPT_TOKEN(aux_sym_resource_token5);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 686:
      ACCEPT_TOKEN(aux_sym_resource_token6);
      END_STATE();
    case 687:
      ACCEPT_TOKEN(aux_sym_resource_token6);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 688:
      ACCEPT_TOKEN(aux_sym_list_roles_token1);
      END_STATE();
    case 689:
      ACCEPT_TOKEN(aux_sym_list_roles_token1);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 690:
      ACCEPT_TOKEN(aux_sym_list_roles_token2);
      END_STATE();
    case 691:
      ACCEPT_TOKEN(aux_sym_list_roles_token3);
      END_STATE();
    case 692:
      ACCEPT_TOKEN(aux_sym_drop_aggregate_token1);
      END_STATE();
    case 693:
      ACCEPT_TOKEN(aux_sym_drop_materialized_view_token1);
      END_STATE();
    case 694:
      ACCEPT_TOKEN(aux_sym_drop_materialized_view_token2);
      END_STATE();
    case 695:
      ACCEPT_TOKEN(aux_sym_drop_trigger_token1);
      END_STATE();
    case 696:
      ACCEPT_TOKEN(aux_sym_drop_type_token1);
      END_STATE();
    case 697:
      ACCEPT_TOKEN(aux_sym_drop_user_token1);
      END_STATE();
    case 698:
      ACCEPT_TOKEN(aux_sym_create_aggregate_token1);
      END_STATE();
    case 699:
      ACCEPT_TOKEN(aux_sym_create_aggregate_token2);
      END_STATE();
    case 700:
      ACCEPT_TOKEN(aux_sym_create_aggregate_token3);
      END_STATE();
    case 701:
      ACCEPT_TOKEN(aux_sym_create_aggregate_token4);
      END_STATE();
    case 702:
      ACCEPT_TOKEN(aux_sym_create_aggregate_token5);
      END_STATE();
    case 703:
      ACCEPT_TOKEN(aux_sym_create_aggregate_token6);
      END_STATE();
    case 704:
      ACCEPT_TOKEN(aux_sym_create_materialized_view_token1);
      END_STATE();
    case 705:
      ACCEPT_TOKEN(aux_sym_column_not_null_token1);
      END_STATE();
    case 706:
      ACCEPT_TOKEN(aux_sym_column_not_null_token2);
      END_STATE();
    case 707:
      ACCEPT_TOKEN(aux_sym_create_function_token1);
      END_STATE();
    case 708:
      ACCEPT_TOKEN(aux_sym_create_function_token2);
      END_STATE();
    case 709:
      ACCEPT_TOKEN(aux_sym_data_type_name_token1);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 710:
      ACCEPT_TOKEN(aux_sym_data_type_name_token2);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 711:
      ACCEPT_TOKEN(aux_sym_data_type_name_token3);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 712:
      ACCEPT_TOKEN(aux_sym_data_type_name_token4);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 713:
      ACCEPT_TOKEN(aux_sym_data_type_name_token5);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 714:
      ACCEPT_TOKEN(aux_sym_data_type_name_token6);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 715:
      ACCEPT_TOKEN(aux_sym_data_type_name_token7);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 716:
      ACCEPT_TOKEN(aux_sym_data_type_name_token8);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 717:
      ACCEPT_TOKEN(aux_sym_data_type_name_token9);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 718:
      ACCEPT_TOKEN(aux_sym_data_type_name_token10);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 719:
      ACCEPT_TOKEN(aux_sym_data_type_name_token11);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 720:
      ACCEPT_TOKEN(aux_sym_data_type_name_token12);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 721:
      ACCEPT_TOKEN(aux_sym_data_type_name_token13);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 722:
      ACCEPT_TOKEN(aux_sym_data_type_name_token14);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 723:
      ACCEPT_TOKEN(aux_sym_data_type_name_token15);
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(905);
      if (lookahead == 'U' ||
          lookahead == 'u') ADVANCE(912);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 724:
      ACCEPT_TOKEN(aux_sym_data_type_name_token16);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 725:
      ACCEPT_TOKEN(aux_sym_data_type_name_token17);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 726:
      ACCEPT_TOKEN(aux_sym_data_type_name_token18);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 727:
      ACCEPT_TOKEN(aux_sym_data_type_name_token19);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 728:
      ACCEPT_TOKEN(aux_sym_data_type_name_token20);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 729:
      ACCEPT_TOKEN(aux_sym_data_type_name_token21);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 730:
      ACCEPT_TOKEN(aux_sym_return_mode_token1);
      END_STATE();
    case 731:
      ACCEPT_TOKEN(aux_sym_return_mode_token2);
      END_STATE();
    case 732:
      ACCEPT_TOKEN(aux_sym_create_keyspace_token1);
      END_STATE();
    case 733:
      ACCEPT_TOKEN(aux_sym_create_keyspace_token2);
      END_STATE();
    case 734:
      ACCEPT_TOKEN(aux_sym_durable_writes_token1);
      END_STATE();
    case 735:
      ACCEPT_TOKEN(aux_sym_role_with_option_token1);
      END_STATE();
    case 736:
      ACCEPT_TOKEN(aux_sym_role_with_option_token2);
      END_STATE();
    case 737:
      ACCEPT_TOKEN(aux_sym_role_with_option_token3);
      END_STATE();
    case 738:
      ACCEPT_TOKEN(aux_sym_role_with_option_token4);
      END_STATE();
    case 739:
      ACCEPT_TOKEN(aux_sym_primary_key_column_token1);
      END_STATE();
    case 740:
      ACCEPT_TOKEN(aux_sym_primary_key_column_token1);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 741:
      ACCEPT_TOKEN(aux_sym_compact_storage_token1);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 742:
      ACCEPT_TOKEN(aux_sym_compact_storage_token2);
      END_STATE();
    case 743:
      ACCEPT_TOKEN(aux_sym_clustering_order_token1);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 744:
      ACCEPT_TOKEN(aux_sym_user_super_user_token1);
      END_STATE();
    case 745:
      ACCEPT_TOKEN(aux_sym_alter_table_add_token1);
      END_STATE();
    case 746:
      ACCEPT_TOKEN(aux_sym_alter_table_rename_token1);
      END_STATE();
    case 747:
      ACCEPT_TOKEN(aux_sym_apply_batch_token1);
      END_STATE();
    case 748:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == '"') ADVANCE(19);
      END_STATE();
    case 749:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == '-') ADVANCE(489);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 750:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'A') ADVANCE(757);
      if (('[' <= lookahead && lookahead <= '^') ||
          lookahead == '`') ADVANCE(479);
      if (lookahead == '$' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'f')) ADVANCE(926);
      END_STATE();
    case 751:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'A') ADVANCE(761);
      if (lookahead == 'U') ADVANCE(759);
      if (('[' <= lookahead && lookahead <= '^') ||
          lookahead == '`') ADVANCE(479);
      if (lookahead == '$' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'f')) ADVANCE(926);
      END_STATE();
    case 752:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'E') ADVANCE(580);
      if (('[' <= lookahead && lookahead <= '^') ||
          lookahead == '`') ADVANCE(471);
      if (lookahead == '$' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(924);
      END_STATE();
    case 753:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'E') ADVANCE(583);
      if (('[' <= lookahead && lookahead <= '^') ||
          lookahead == '`') ADVANCE(469);
      if (lookahead == '$' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(923);
      END_STATE();
    case 754:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'F') ADVANCE(756);
      if (('[' <= lookahead && lookahead <= '^') ||
          lookahead == '`') ADVANCE(473);
      if (lookahead == '$' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(925);
      END_STATE();
    case 755:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'I') ADVANCE(765);
      if (('[' <= lookahead && lookahead <= '^') ||
          lookahead == '`') ADVANCE(467);
      if (lookahead == '$' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(922);
      END_STATE();
    case 756:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'I') ADVANCE(762);
      if (('[' <= lookahead && lookahead <= '^') ||
          lookahead == '`') ADVANCE(471);
      if (lookahead == '$' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(924);
      END_STATE();
    case 757:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'L') ADVANCE(764);
      if (('[' <= lookahead && lookahead <= '^') ||
          lookahead == '`') ADVANCE(473);
      if (lookahead == '$' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(925);
      END_STATE();
    case 758:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'L') ADVANCE(594);
      if (('[' <= lookahead && lookahead <= '^') ||
          lookahead == '`') ADVANCE(471);
      if (lookahead == '$' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(924);
      END_STATE();
    case 759:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'L') ADVANCE(758);
      if (('[' <= lookahead && lookahead <= '^') ||
          lookahead == '`') ADVANCE(473);
      if (lookahead == '$' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(925);
      END_STATE();
    case 760:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'N') ADVANCE(754);
      if (('[' <= lookahead && lookahead <= '^') ||
          lookahead == '`') ADVANCE(479);
      if (lookahead == '$' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(926);
      END_STATE();
    case 761:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'N') ADVANCE(572);
      if (('[' <= lookahead && lookahead <= '^') ||
          lookahead == '`') ADVANCE(473);
      if (lookahead == '$' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(925);
      END_STATE();
    case 762:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'N') ADVANCE(755);
      if (('[' <= lookahead && lookahead <= '^') ||
          lookahead == '`') ADVANCE(469);
      if (lookahead == '$' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(923);
      END_STATE();
    case 763:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'R') ADVANCE(766);
      if (('[' <= lookahead && lookahead <= '^') ||
          lookahead == '`') ADVANCE(479);
      if (lookahead == '$' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(926);
      END_STATE();
    case 764:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'S') ADVANCE(753);
      if (('[' <= lookahead && lookahead <= '^') ||
          lookahead == '`') ADVANCE(471);
      if (lookahead == '$' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(924);
      END_STATE();
    case 765:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'T') ADVANCE(767);
      if (('[' <= lookahead && lookahead <= '^') ||
          lookahead == '`') ADVANCE(465);
      if (lookahead == '$' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(921);
      END_STATE();
    case 766:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'U') ADVANCE(752);
      if (('[' <= lookahead && lookahead <= '^') ||
          lookahead == '`') ADVANCE(473);
      if (lookahead == '$' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(925);
      END_STATE();
    case 767:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'Y') ADVANCE(576);
      if (('[' <= lookahead && lookahead <= '^') ||
          lookahead == '`') ADVANCE(35);
      if (lookahead == '$' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(749);
      END_STATE();
    case 768:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(891);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(786);
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(910);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 769:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(870);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 770:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(875);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 771:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(788);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 772:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(831);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 773:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(844);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 774:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(787);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 775:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(877);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 776:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(828);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 777:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(850);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 778:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(896);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 779:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(878);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 780:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'A' ||
          lookahead == 'a') ADVANCE(783);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 781:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'B' ||
          lookahead == 'b') ADVANCE(711);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 782:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'B' ||
          lookahead == 'b') ADVANCE(838);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 783:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'B' ||
          lookahead == 'b') ADVANCE(840);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 784:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(812);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(855);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 785:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(821);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 786:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(815);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 787:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(799);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 788:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(901);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 789:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'C' ||
          lookahead == 'c') ADVANCE(906);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 790:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'D' ||
          lookahead == 'd') ADVANCE(729);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 791:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'D' ||
          lookahead == 'd') ADVANCE(724);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 792:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(915);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(843);
      if (lookahead == 'U' ||
          lookahead == 'u') ADVANCE(874);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 793:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(713);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 794:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(723);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 795:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(726);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 796:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(715);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 797:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(687);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 798:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(655);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 799:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(681);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 800:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(892);
      if (lookahead == 'M' ||
          lookahead == 'm') ADVANCE(772);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 801:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(876);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 802:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(917);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 803:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(893);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(719);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 804:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(849);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 805:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(886);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 806:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(777);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 807:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(918);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 808:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(881);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 809:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'F' ||
          lookahead == 'f') ADVANCE(635);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 810:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'G' ||
          lookahead == 'g') ADVANCE(743);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 811:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'G' ||
          lookahead == 'g') ADVANCE(819);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 812:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'H' ||
          lookahead == 'h') ADVANCE(775);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 813:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(811);
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(861);
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(862);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 814:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(790);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 815:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(846);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 816:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(709);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 817:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(887);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 818:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(791);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 819:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(854);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 820:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(867);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 821:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(816);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 822:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(853);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 823:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(805);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 824:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(847);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 825:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(888);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 826:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(856);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 827:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'I' ||
          lookahead == 'i') ADVANCE(857);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 828:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(714);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 829:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(662);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 830:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(672);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 831:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(841);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 832:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(806);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 833:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(866);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(863);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 834:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(911);
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(845);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 835:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(829);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 836:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(795);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 837:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(830);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 838:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(796);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 839:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(797);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 840:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(798);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 841:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'L' ||
          lookahead == 'l') ADVANCE(827);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 842:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'M' ||
          lookahead == 'm') ADVANCE(611);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 843:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'M' ||
          lookahead == 'm') ADVANCE(794);
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(919);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 844:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'M' ||
          lookahead == 'm') ADVANCE(871);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 845:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'M' ||
          lookahead == 'm') ADVANCE(872);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 846:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'M' ||
          lookahead == 'm') ADVANCE(776);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 847:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'M' ||
          lookahead == 'm') ADVANCE(779);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 848:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(803);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 849:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(717);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 850:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(712);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 851:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(659);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 852:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(685);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 853:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(810);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 854:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(897);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 855:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(898);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 856:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(899);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 857:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(900);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 858:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(903);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 859:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(904);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 860:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'N' ||
          lookahead == 'n') ADVANCE(789);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 861:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(781);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 862:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(832);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 863:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(920);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 864:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(908);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 865:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(842);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 866:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(778);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 867:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(852);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 868:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(845);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 869:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'O' ||
          lookahead == 'o') ADVANCE(839);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 870:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'P' ||
          lookahead == 'p') ADVANCE(720);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 871:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'P' ||
          lookahead == 'p') ADVANCE(646);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 872:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'P' ||
          lookahead == 'p') ADVANCE(771);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 873:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'P' ||
          lookahead == 'p') ADVANCE(774);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 874:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'P' ||
          lookahead == 'p') ADVANCE(836);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 875:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(784);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 876:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(642);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 877:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(727);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 878:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(916);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 879:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(865);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 880:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(823);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 881:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(822);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 882:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'R' ||
          lookahead == 'r') ADVANCE(824);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 883:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(785);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 884:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(637);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 885:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(660);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 886:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(661);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 887:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(894);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 888:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(902);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 889:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(873);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 890:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'S' ||
          lookahead == 's') ADVANCE(907);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 891:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(793);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 892:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(666);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 893:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(718);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 894:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(689);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 895:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(722);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 896:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(716);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 897:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(710);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 898:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(728);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 899:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(725);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 900:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(721);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 901:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(741);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 902:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(884);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 903:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(880);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 904:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(801);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 905:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(773);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 906:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(820);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 907:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'T' ||
          lookahead == 't') ADVANCE(808);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 908:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'U' ||
          lookahead == 'u') ADVANCE(859);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 909:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'U' ||
          lookahead == 'u') ADVANCE(814);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 910:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'U' ||
          lookahead == 'u') ADVANCE(782);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 911:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'U' ||
          lookahead == 'u') ADVANCE(890);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 912:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'U' ||
          lookahead == 'u') ADVANCE(818);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 913:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'U' ||
          lookahead == 'u') ADVANCE(860);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 914:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'U' ||
          lookahead == 'u') ADVANCE(835);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 915:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'X' ||
          lookahead == 'x') ADVANCE(895);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 916:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'Y' ||
          lookahead == 'y') ADVANCE(740);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 917:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'Y' ||
          lookahead == 'y') ADVANCE(885);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 918:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'Y' ||
          lookahead == 'y') ADVANCE(889);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 919:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'Y' ||
          lookahead == 'y') ADVANCE(826);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    case 920:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == 'Z' ||
          lookahead == 'z') ADVANCE(804);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Y') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'y')) ADVANCE(928);
      END_STATE();
    case 921:
      ACCEPT_TOKEN(sym_object_name);
      if (('[' <= lookahead && lookahead <= '^') ||
          lookahead == '`') ADVANCE(35);
      if (lookahead == '$' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(749);
      END_STATE();
    case 922:
      ACCEPT_TOKEN(sym_object_name);
      if (('[' <= lookahead && lookahead <= '^') ||
          lookahead == '`') ADVANCE(465);
      if (lookahead == '$' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(921);
      END_STATE();
    case 923:
      ACCEPT_TOKEN(sym_object_name);
      if (('[' <= lookahead && lookahead <= '^') ||
          lookahead == '`') ADVANCE(467);
      if (lookahead == '$' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(922);
      END_STATE();
    case 924:
      ACCEPT_TOKEN(sym_object_name);
      if (('[' <= lookahead && lookahead <= '^') ||
          lookahead == '`') ADVANCE(469);
      if (lookahead == '$' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(923);
      END_STATE();
    case 925:
      ACCEPT_TOKEN(sym_object_name);
      if (('[' <= lookahead && lookahead <= '^') ||
          lookahead == '`') ADVANCE(471);
      if (lookahead == '$' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(924);
      END_STATE();
    case 926:
      ACCEPT_TOKEN(sym_object_name);
      if (('[' <= lookahead && lookahead <= '^') ||
          lookahead == '`') ADVANCE(473);
      if (lookahead == '$' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(925);
      END_STATE();
    case 927:
      ACCEPT_TOKEN(sym_object_name);
      if (('[' <= lookahead && lookahead <= '^') ||
          lookahead == '`') ADVANCE(479);
      if (lookahead == '$' ||
          ('g' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'f')) ADVANCE(926);
      END_STATE();
    case 928:
      ACCEPT_TOKEN(sym_object_name);
      if (lookahead == '$' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(928);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 0},
  [2] = {.lex_state = 0},
  [3] = {.lex_state = 0},
  [4] = {.lex_state = 499},
  [5] = {.lex_state = 499},
  [6] = {.lex_state = 1},
  [7] = {.lex_state = 499},
  [8] = {.lex_state = 499},
  [9] = {.lex_state = 1},
  [10] = {.lex_state = 499},
  [11] = {.lex_state = 499},
  [12] = {.lex_state = 499},
  [13] = {.lex_state = 1},
  [14] = {.lex_state = 499},
  [15] = {.lex_state = 1},
  [16] = {.lex_state = 499},
  [17] = {.lex_state = 1},
  [18] = {.lex_state = 1},
  [19] = {.lex_state = 1},
  [20] = {.lex_state = 1},
  [21] = {.lex_state = 499},
  [22] = {.lex_state = 499},
  [23] = {.lex_state = 1},
  [24] = {.lex_state = 499},
  [25] = {.lex_state = 1},
  [26] = {.lex_state = 1},
  [27] = {.lex_state = 499},
  [28] = {.lex_state = 1},
  [29] = {.lex_state = 1},
  [30] = {.lex_state = 1},
  [31] = {.lex_state = 499},
  [32] = {.lex_state = 1},
  [33] = {.lex_state = 499},
  [34] = {.lex_state = 499},
  [35] = {.lex_state = 499},
  [36] = {.lex_state = 499},
  [37] = {.lex_state = 8},
  [38] = {.lex_state = 8},
  [39] = {.lex_state = 8},
  [40] = {.lex_state = 8},
  [41] = {.lex_state = 8},
  [42] = {.lex_state = 8},
  [43] = {.lex_state = 8},
  [44] = {.lex_state = 8},
  [45] = {.lex_state = 8},
  [46] = {.lex_state = 8},
  [47] = {.lex_state = 8},
  [48] = {.lex_state = 8},
  [49] = {.lex_state = 8},
  [50] = {.lex_state = 8},
  [51] = {.lex_state = 8},
  [52] = {.lex_state = 8},
  [53] = {.lex_state = 8},
  [54] = {.lex_state = 8},
  [55] = {.lex_state = 8},
  [56] = {.lex_state = 8},
  [57] = {.lex_state = 8},
  [58] = {.lex_state = 7},
  [59] = {.lex_state = 1},
  [60] = {.lex_state = 1},
  [61] = {.lex_state = 1},
  [62] = {.lex_state = 1},
  [63] = {.lex_state = 499},
  [64] = {.lex_state = 1},
  [65] = {.lex_state = 1},
  [66] = {.lex_state = 499},
  [67] = {.lex_state = 7},
  [68] = {.lex_state = 499},
  [69] = {.lex_state = 499},
  [70] = {.lex_state = 499},
  [71] = {.lex_state = 499},
  [72] = {.lex_state = 499},
  [73] = {.lex_state = 499},
  [74] = {.lex_state = 499},
  [75] = {.lex_state = 499},
  [76] = {.lex_state = 499},
  [77] = {.lex_state = 499},
  [78] = {.lex_state = 499},
  [79] = {.lex_state = 499},
  [80] = {.lex_state = 1},
  [81] = {.lex_state = 499},
  [82] = {.lex_state = 0},
  [83] = {.lex_state = 499},
  [84] = {.lex_state = 499},
  [85] = {.lex_state = 499},
  [86] = {.lex_state = 499},
  [87] = {.lex_state = 0},
  [88] = {.lex_state = 499},
  [89] = {.lex_state = 499},
  [90] = {.lex_state = 499},
  [91] = {.lex_state = 499},
  [92] = {.lex_state = 499},
  [93] = {.lex_state = 22},
  [94] = {.lex_state = 0},
  [95] = {.lex_state = 499},
  [96] = {.lex_state = 500},
  [97] = {.lex_state = 499},
  [98] = {.lex_state = 500},
  [99] = {.lex_state = 0},
  [100] = {.lex_state = 500},
  [101] = {.lex_state = 1},
  [102] = {.lex_state = 1},
  [103] = {.lex_state = 499},
  [104] = {.lex_state = 1},
  [105] = {.lex_state = 0},
  [106] = {.lex_state = 1},
  [107] = {.lex_state = 500},
  [108] = {.lex_state = 499},
  [109] = {.lex_state = 499},
  [110] = {.lex_state = 500},
  [111] = {.lex_state = 1},
  [112] = {.lex_state = 499},
  [113] = {.lex_state = 0},
  [114] = {.lex_state = 499},
  [115] = {.lex_state = 499},
  [116] = {.lex_state = 0},
  [117] = {.lex_state = 0},
  [118] = {.lex_state = 499},
  [119] = {.lex_state = 499},
  [120] = {.lex_state = 0},
  [121] = {.lex_state = 0},
  [122] = {.lex_state = 499},
  [123] = {.lex_state = 499},
  [124] = {.lex_state = 499},
  [125] = {.lex_state = 499},
  [126] = {.lex_state = 0},
  [127] = {.lex_state = 499},
  [128] = {.lex_state = 0},
  [129] = {.lex_state = 499},
  [130] = {.lex_state = 499},
  [131] = {.lex_state = 0},
  [132] = {.lex_state = 0},
  [133] = {.lex_state = 0},
  [134] = {.lex_state = 0},
  [135] = {.lex_state = 0},
  [136] = {.lex_state = 0},
  [137] = {.lex_state = 0},
  [138] = {.lex_state = 0},
  [139] = {.lex_state = 0},
  [140] = {.lex_state = 0},
  [141] = {.lex_state = 0},
  [142] = {.lex_state = 0},
  [143] = {.lex_state = 0},
  [144] = {.lex_state = 0},
  [145] = {.lex_state = 499},
  [146] = {.lex_state = 0},
  [147] = {.lex_state = 0},
  [148] = {.lex_state = 499},
  [149] = {.lex_state = 0},
  [150] = {.lex_state = 499},
  [151] = {.lex_state = 0},
  [152] = {.lex_state = 0},
  [153] = {.lex_state = 499},
  [154] = {.lex_state = 0},
  [155] = {.lex_state = 0},
  [156] = {.lex_state = 499},
  [157] = {.lex_state = 0},
  [158] = {.lex_state = 0},
  [159] = {.lex_state = 0},
  [160] = {.lex_state = 0},
  [161] = {.lex_state = 499},
  [162] = {.lex_state = 0},
  [163] = {.lex_state = 0},
  [164] = {.lex_state = 499},
  [165] = {.lex_state = 499},
  [166] = {.lex_state = 0},
  [167] = {.lex_state = 499},
  [168] = {.lex_state = 499},
  [169] = {.lex_state = 0},
  [170] = {.lex_state = 499},
  [171] = {.lex_state = 0},
  [172] = {.lex_state = 499},
  [173] = {.lex_state = 0},
  [174] = {.lex_state = 0},
  [175] = {.lex_state = 0},
  [176] = {.lex_state = 0},
  [177] = {.lex_state = 0},
  [178] = {.lex_state = 499},
  [179] = {.lex_state = 0},
  [180] = {.lex_state = 499},
  [181] = {.lex_state = 0},
  [182] = {.lex_state = 499},
  [183] = {.lex_state = 499},
  [184] = {.lex_state = 499},
  [185] = {.lex_state = 499},
  [186] = {.lex_state = 499},
  [187] = {.lex_state = 499},
  [188] = {.lex_state = 499},
  [189] = {.lex_state = 499},
  [190] = {.lex_state = 499},
  [191] = {.lex_state = 499},
  [192] = {.lex_state = 499},
  [193] = {.lex_state = 499},
  [194] = {.lex_state = 499},
  [195] = {.lex_state = 499},
  [196] = {.lex_state = 499},
  [197] = {.lex_state = 499},
  [198] = {.lex_state = 499},
  [199] = {.lex_state = 0},
  [200] = {.lex_state = 0},
  [201] = {.lex_state = 499},
  [202] = {.lex_state = 499},
  [203] = {.lex_state = 499},
  [204] = {.lex_state = 499},
  [205] = {.lex_state = 0},
  [206] = {.lex_state = 0},
  [207] = {.lex_state = 0},
  [208] = {.lex_state = 499},
  [209] = {.lex_state = 0},
  [210] = {.lex_state = 499},
  [211] = {.lex_state = 0},
  [212] = {.lex_state = 0},
  [213] = {.lex_state = 0},
  [214] = {.lex_state = 0},
  [215] = {.lex_state = 0},
  [216] = {.lex_state = 0},
  [217] = {.lex_state = 0},
  [218] = {.lex_state = 0},
  [219] = {.lex_state = 0},
  [220] = {.lex_state = 0},
  [221] = {.lex_state = 0},
  [222] = {.lex_state = 0},
  [223] = {.lex_state = 0},
  [224] = {.lex_state = 0},
  [225] = {.lex_state = 0},
  [226] = {.lex_state = 23},
  [227] = {.lex_state = 0},
  [228] = {.lex_state = 0},
  [229] = {.lex_state = 0},
  [230] = {.lex_state = 0},
  [231] = {.lex_state = 0},
  [232] = {.lex_state = 0},
  [233] = {.lex_state = 0},
  [234] = {.lex_state = 0},
  [235] = {.lex_state = 0},
  [236] = {.lex_state = 0},
  [237] = {.lex_state = 0},
  [238] = {.lex_state = 0},
  [239] = {.lex_state = 0},
  [240] = {.lex_state = 0},
  [241] = {.lex_state = 0},
  [242] = {.lex_state = 0},
  [243] = {.lex_state = 0},
  [244] = {.lex_state = 0},
  [245] = {.lex_state = 0},
  [246] = {.lex_state = 0},
  [247] = {.lex_state = 0},
  [248] = {.lex_state = 0},
  [249] = {.lex_state = 0},
  [250] = {.lex_state = 0},
  [251] = {.lex_state = 0},
  [252] = {.lex_state = 0},
  [253] = {.lex_state = 0},
  [254] = {.lex_state = 0},
  [255] = {.lex_state = 0},
  [256] = {.lex_state = 0},
  [257] = {.lex_state = 0},
  [258] = {.lex_state = 0},
  [259] = {.lex_state = 0},
  [260] = {.lex_state = 0},
  [261] = {.lex_state = 0},
  [262] = {.lex_state = 0},
  [263] = {.lex_state = 0},
  [264] = {.lex_state = 0},
  [265] = {.lex_state = 0},
  [266] = {.lex_state = 0},
  [267] = {.lex_state = 0},
  [268] = {.lex_state = 0},
  [269] = {.lex_state = 0},
  [270] = {.lex_state = 0},
  [271] = {.lex_state = 0},
  [272] = {.lex_state = 0},
  [273] = {.lex_state = 0},
  [274] = {.lex_state = 0},
  [275] = {.lex_state = 0},
  [276] = {.lex_state = 0},
  [277] = {.lex_state = 0},
  [278] = {.lex_state = 0},
  [279] = {.lex_state = 0},
  [280] = {.lex_state = 0},
  [281] = {.lex_state = 0},
  [282] = {.lex_state = 0},
  [283] = {.lex_state = 0},
  [284] = {.lex_state = 0},
  [285] = {.lex_state = 0},
  [286] = {.lex_state = 0},
  [287] = {.lex_state = 0},
  [288] = {.lex_state = 0},
  [289] = {.lex_state = 0},
  [290] = {.lex_state = 0},
  [291] = {.lex_state = 0},
  [292] = {.lex_state = 0},
  [293] = {.lex_state = 0},
  [294] = {.lex_state = 0},
  [295] = {.lex_state = 0},
  [296] = {.lex_state = 0},
  [297] = {.lex_state = 0},
  [298] = {.lex_state = 0},
  [299] = {.lex_state = 0},
  [300] = {.lex_state = 0},
  [301] = {.lex_state = 0},
  [302] = {.lex_state = 0},
  [303] = {.lex_state = 0},
  [304] = {.lex_state = 0},
  [305] = {.lex_state = 0},
  [306] = {.lex_state = 0},
  [307] = {.lex_state = 0},
  [308] = {.lex_state = 0},
  [309] = {.lex_state = 0},
  [310] = {.lex_state = 0},
  [311] = {.lex_state = 0},
  [312] = {.lex_state = 0},
  [313] = {.lex_state = 0},
  [314] = {.lex_state = 0},
  [315] = {.lex_state = 20},
  [316] = {.lex_state = 20},
  [317] = {.lex_state = 20},
  [318] = {.lex_state = 20},
  [319] = {.lex_state = 0},
  [320] = {.lex_state = 1},
  [321] = {.lex_state = 20},
  [322] = {.lex_state = 20},
  [323] = {.lex_state = 20},
  [324] = {.lex_state = 21},
  [325] = {.lex_state = 21},
  [326] = {.lex_state = 21},
  [327] = {.lex_state = 23},
  [328] = {.lex_state = 3},
  [329] = {.lex_state = 23},
  [330] = {.lex_state = 31},
  [331] = {.lex_state = 4},
  [332] = {.lex_state = 2},
  [333] = {.lex_state = 2},
  [334] = {.lex_state = 0},
  [335] = {.lex_state = 31},
  [336] = {.lex_state = 23},
  [337] = {.lex_state = 23},
  [338] = {.lex_state = 37},
  [339] = {.lex_state = 0},
  [340] = {.lex_state = 0},
  [341] = {.lex_state = 37},
  [342] = {.lex_state = 8},
  [343] = {.lex_state = 0},
  [344] = {.lex_state = 37},
  [345] = {.lex_state = 499},
  [346] = {.lex_state = 5},
  [347] = {.lex_state = 15},
  [348] = {.lex_state = 8},
  [349] = {.lex_state = 74},
  [350] = {.lex_state = 5},
  [351] = {.lex_state = 2},
  [352] = {.lex_state = 9},
  [353] = {.lex_state = 5},
  [354] = {.lex_state = 15},
  [355] = {.lex_state = 15},
  [356] = {.lex_state = 499},
  [357] = {.lex_state = 15},
  [358] = {.lex_state = 74},
  [359] = {.lex_state = 74},
  [360] = {.lex_state = 13},
  [361] = {.lex_state = 8},
  [362] = {.lex_state = 13},
  [363] = {.lex_state = 2},
  [364] = {.lex_state = 499},
  [365] = {.lex_state = 10},
  [366] = {.lex_state = 2},
  [367] = {.lex_state = 12},
  [368] = {.lex_state = 12},
  [369] = {.lex_state = 499},
  [370] = {.lex_state = 2},
  [371] = {.lex_state = 499},
  [372] = {.lex_state = 0},
  [373] = {.lex_state = 499},
  [374] = {.lex_state = 2},
  [375] = {.lex_state = 2},
  [376] = {.lex_state = 2},
  [377] = {.lex_state = 499},
  [378] = {.lex_state = 2},
  [379] = {.lex_state = 12},
  [380] = {.lex_state = 2},
  [381] = {.lex_state = 0},
  [382] = {.lex_state = 2},
  [383] = {.lex_state = 0},
  [384] = {.lex_state = 2},
  [385] = {.lex_state = 2},
  [386] = {.lex_state = 0},
  [387] = {.lex_state = 0},
  [388] = {.lex_state = 31},
  [389] = {.lex_state = 499},
  [390] = {.lex_state = 32},
  [391] = {.lex_state = 0},
  [392] = {.lex_state = 77},
  [393] = {.lex_state = 21},
  [394] = {.lex_state = 0},
  [395] = {.lex_state = 77},
  [396] = {.lex_state = 21},
  [397] = {.lex_state = 78},
  [398] = {.lex_state = 0},
  [399] = {.lex_state = 78},
  [400] = {.lex_state = 32},
  [401] = {.lex_state = 78},
  [402] = {.lex_state = 32},
  [403] = {.lex_state = 77},
  [404] = {.lex_state = 79},
  [405] = {.lex_state = 0},
  [406] = {.lex_state = 2},
  [407] = {.lex_state = 0},
  [408] = {.lex_state = 2},
  [409] = {.lex_state = 75},
  [410] = {.lex_state = 11},
  [411] = {.lex_state = 0},
  [412] = {.lex_state = 0},
  [413] = {.lex_state = 75},
  [414] = {.lex_state = 0},
  [415] = {.lex_state = 2},
  [416] = {.lex_state = 30},
  [417] = {.lex_state = 499},
  [418] = {.lex_state = 76},
  [419] = {.lex_state = 30},
  [420] = {.lex_state = 2},
  [421] = {.lex_state = 76},
  [422] = {.lex_state = 499},
  [423] = {.lex_state = 499},
  [424] = {.lex_state = 2},
  [425] = {.lex_state = 30},
  [426] = {.lex_state = 75},
  [427] = {.lex_state = 76},
  [428] = {.lex_state = 0},
  [429] = {.lex_state = 0},
  [430] = {.lex_state = 6},
  [431] = {.lex_state = 0},
  [432] = {.lex_state = 0},
  [433] = {.lex_state = 31},
  [434] = {.lex_state = 0},
  [435] = {.lex_state = 79},
  [436] = {.lex_state = 16},
  [437] = {.lex_state = 16},
  [438] = {.lex_state = 79},
  [439] = {.lex_state = 6},
  [440] = {.lex_state = 6},
  [441] = {.lex_state = 0},
  [442] = {.lex_state = 0},
  [443] = {.lex_state = 499},
  [444] = {.lex_state = 0},
  [445] = {.lex_state = 0},
  [446] = {.lex_state = 499},
  [447] = {.lex_state = 0},
  [448] = {.lex_state = 410},
  [449] = {.lex_state = 0},
  [450] = {.lex_state = 18},
  [451] = {.lex_state = 499},
  [452] = {.lex_state = 0},
  [453] = {.lex_state = 499},
  [454] = {.lex_state = 0},
  [455] = {.lex_state = 0},
  [456] = {.lex_state = 0},
  [457] = {.lex_state = 0},
  [458] = {.lex_state = 0},
  [459] = {.lex_state = 499},
  [460] = {.lex_state = 0},
  [461] = {.lex_state = 0},
  [462] = {.lex_state = 0},
  [463] = {.lex_state = 0},
  [464] = {.lex_state = 18},
  [465] = {.lex_state = 499},
  [466] = {.lex_state = 8},
  [467] = {.lex_state = 499},
  [468] = {.lex_state = 5},
  [469] = {.lex_state = 499},
  [470] = {.lex_state = 0},
  [471] = {.lex_state = 8},
  [472] = {.lex_state = 0},
  [473] = {.lex_state = 499},
  [474] = {.lex_state = 499},
  [475] = {.lex_state = 499},
  [476] = {.lex_state = 5},
  [477] = {.lex_state = 0},
  [478] = {.lex_state = 0},
  [479] = {.lex_state = 0},
  [480] = {.lex_state = 499},
  [481] = {.lex_state = 0},
  [482] = {.lex_state = 499},
  [483] = {.lex_state = 0},
  [484] = {.lex_state = 0},
  [485] = {.lex_state = 0},
  [486] = {.lex_state = 0},
  [487] = {.lex_state = 0},
  [488] = {.lex_state = 17},
  [489] = {.lex_state = 17},
  [490] = {.lex_state = 17},
  [491] = {.lex_state = 499},
  [492] = {.lex_state = 0},
  [493] = {.lex_state = 0},
  [494] = {.lex_state = 0},
  [495] = {.lex_state = 0},
  [496] = {.lex_state = 17},
  [497] = {.lex_state = 0},
  [498] = {.lex_state = 17},
  [499] = {.lex_state = 0},
  [500] = {.lex_state = 17},
  [501] = {.lex_state = 17},
  [502] = {.lex_state = 499},
  [503] = {.lex_state = 0},
  [504] = {.lex_state = 0},
  [505] = {.lex_state = 0},
  [506] = {.lex_state = 17},
  [507] = {.lex_state = 0},
  [508] = {.lex_state = 0},
  [509] = {.lex_state = 17},
  [510] = {.lex_state = 11},
  [511] = {.lex_state = 0},
  [512] = {.lex_state = 17},
  [513] = {.lex_state = 0},
  [514] = {.lex_state = 2},
  [515] = {.lex_state = 11},
  [516] = {.lex_state = 11},
  [517] = {.lex_state = 2},
  [518] = {.lex_state = 17},
  [519] = {.lex_state = 17},
  [520] = {.lex_state = 17},
  [521] = {.lex_state = 499},
  [522] = {.lex_state = 0},
  [523] = {.lex_state = 499},
  [524] = {.lex_state = 2},
  [525] = {.lex_state = 17},
  [526] = {.lex_state = 499},
  [527] = {.lex_state = 0},
  [528] = {.lex_state = 2},
  [529] = {.lex_state = 499},
  [530] = {.lex_state = 0},
  [531] = {.lex_state = 11},
  [532] = {.lex_state = 499},
  [533] = {.lex_state = 499},
  [534] = {.lex_state = 2},
  [535] = {.lex_state = 2},
  [536] = {.lex_state = 0},
  [537] = {.lex_state = 499},
  [538] = {.lex_state = 0},
  [539] = {.lex_state = 0},
  [540] = {.lex_state = 2},
  [541] = {.lex_state = 0},
  [542] = {.lex_state = 2},
  [543] = {.lex_state = 0},
  [544] = {.lex_state = 0},
  [545] = {.lex_state = 2},
  [546] = {.lex_state = 0},
  [547] = {.lex_state = 0},
  [548] = {.lex_state = 0},
  [549] = {.lex_state = 2},
  [550] = {.lex_state = 499},
  [551] = {.lex_state = 0},
  [552] = {.lex_state = 0},
  [553] = {.lex_state = 0},
  [554] = {.lex_state = 0},
  [555] = {.lex_state = 0},
  [556] = {.lex_state = 0},
  [557] = {.lex_state = 0},
  [558] = {.lex_state = 0},
  [559] = {.lex_state = 0},
  [560] = {.lex_state = 0},
  [561] = {.lex_state = 0},
  [562] = {.lex_state = 0},
  [563] = {.lex_state = 499},
  [564] = {.lex_state = 0},
  [565] = {.lex_state = 0},
  [566] = {.lex_state = 0},
  [567] = {.lex_state = 0},
  [568] = {.lex_state = 0},
  [569] = {.lex_state = 0},
  [570] = {.lex_state = 0},
  [571] = {.lex_state = 0},
  [572] = {.lex_state = 11},
  [573] = {.lex_state = 0},
  [574] = {.lex_state = 17},
  [575] = {.lex_state = 2},
  [576] = {.lex_state = 499},
  [577] = {.lex_state = 0},
  [578] = {.lex_state = 499},
  [579] = {.lex_state = 11},
  [580] = {.lex_state = 17},
  [581] = {.lex_state = 499},
  [582] = {.lex_state = 2},
  [583] = {.lex_state = 0},
  [584] = {.lex_state = 2},
  [585] = {.lex_state = 499},
  [586] = {.lex_state = 499},
  [587] = {.lex_state = 0},
  [588] = {.lex_state = 2},
  [589] = {.lex_state = 2},
  [590] = {.lex_state = 31},
  [591] = {.lex_state = 0},
  [592] = {.lex_state = 0},
  [593] = {.lex_state = 2},
  [594] = {.lex_state = 0},
  [595] = {.lex_state = 11},
  [596] = {.lex_state = 0},
  [597] = {.lex_state = 0},
  [598] = {.lex_state = 11},
  [599] = {.lex_state = 499},
  [600] = {.lex_state = 499},
  [601] = {.lex_state = 2},
  [602] = {.lex_state = 0},
  [603] = {.lex_state = 2},
  [604] = {.lex_state = 499},
  [605] = {.lex_state = 0},
  [606] = {.lex_state = 0},
  [607] = {.lex_state = 11},
  [608] = {.lex_state = 0},
  [609] = {.lex_state = 0},
  [610] = {.lex_state = 0},
  [611] = {.lex_state = 6},
  [612] = {.lex_state = 0},
  [613] = {.lex_state = 0},
  [614] = {.lex_state = 0},
  [615] = {.lex_state = 0},
  [616] = {.lex_state = 0},
  [617] = {.lex_state = 11},
  [618] = {.lex_state = 11},
  [619] = {.lex_state = 11},
  [620] = {.lex_state = 11},
  [621] = {.lex_state = 0},
  [622] = {.lex_state = 2},
  [623] = {.lex_state = 0},
  [624] = {.lex_state = 0},
  [625] = {.lex_state = 11},
  [626] = {.lex_state = 11},
  [627] = {.lex_state = 11},
  [628] = {.lex_state = 0},
  [629] = {.lex_state = 30},
  [630] = {.lex_state = 0},
  [631] = {.lex_state = 0},
  [632] = {.lex_state = 0},
  [633] = {.lex_state = 0},
  [634] = {.lex_state = 0},
  [635] = {.lex_state = 0},
  [636] = {.lex_state = 0},
  [637] = {.lex_state = 23},
  [638] = {.lex_state = 499},
  [639] = {.lex_state = 11},
  [640] = {.lex_state = 499},
  [641] = {.lex_state = 0},
  [642] = {.lex_state = 0},
  [643] = {.lex_state = 0},
  [644] = {.lex_state = 0},
  [645] = {.lex_state = 11},
  [646] = {.lex_state = 11},
  [647] = {.lex_state = 0},
  [648] = {.lex_state = 0},
  [649] = {.lex_state = 11},
  [650] = {.lex_state = 499},
  [651] = {.lex_state = 0},
  [652] = {.lex_state = 0},
  [653] = {.lex_state = 6},
  [654] = {.lex_state = 0},
  [655] = {.lex_state = 0},
  [656] = {.lex_state = 0},
  [657] = {.lex_state = 2},
  [658] = {.lex_state = 499},
  [659] = {.lex_state = 499},
  [660] = {.lex_state = 0},
  [661] = {.lex_state = 499},
  [662] = {.lex_state = 0},
  [663] = {.lex_state = 0},
  [664] = {.lex_state = 0},
  [665] = {.lex_state = 0},
  [666] = {.lex_state = 11},
  [667] = {.lex_state = 499},
  [668] = {.lex_state = 11},
  [669] = {.lex_state = 0},
  [670] = {.lex_state = 0},
  [671] = {.lex_state = 11},
  [672] = {.lex_state = 11},
  [673] = {.lex_state = 11},
  [674] = {.lex_state = 499},
  [675] = {.lex_state = 11},
  [676] = {.lex_state = 499},
  [677] = {.lex_state = 0},
  [678] = {.lex_state = 11},
  [679] = {.lex_state = 11},
  [680] = {.lex_state = 11},
  [681] = {.lex_state = 11},
  [682] = {.lex_state = 0},
  [683] = {.lex_state = 11},
  [684] = {.lex_state = 11},
  [685] = {.lex_state = 11},
  [686] = {.lex_state = 0},
  [687] = {.lex_state = 0},
  [688] = {.lex_state = 499},
  [689] = {.lex_state = 11},
  [690] = {.lex_state = 0},
  [691] = {.lex_state = 0},
  [692] = {.lex_state = 14},
  [693] = {.lex_state = 11},
  [694] = {.lex_state = 0},
  [695] = {.lex_state = 499},
  [696] = {.lex_state = 0},
  [697] = {.lex_state = 0},
  [698] = {.lex_state = 11},
  [699] = {.lex_state = 0},
  [700] = {.lex_state = 11},
  [701] = {.lex_state = 11},
  [702] = {.lex_state = 0},
  [703] = {.lex_state = 0},
  [704] = {.lex_state = 0},
  [705] = {.lex_state = 0},
  [706] = {.lex_state = 0},
  [707] = {.lex_state = 0},
  [708] = {.lex_state = 30},
  [709] = {.lex_state = 0},
  [710] = {.lex_state = 11},
  [711] = {.lex_state = 11},
  [712] = {.lex_state = 0},
  [713] = {.lex_state = 11},
  [714] = {.lex_state = 11},
  [715] = {.lex_state = 499},
  [716] = {.lex_state = 0},
  [717] = {.lex_state = 11},
  [718] = {.lex_state = 499},
  [719] = {.lex_state = 11},
  [720] = {.lex_state = 11},
  [721] = {.lex_state = 0},
  [722] = {.lex_state = 11},
  [723] = {.lex_state = 0},
  [724] = {.lex_state = 0},
  [725] = {.lex_state = 0},
  [726] = {.lex_state = 0},
  [727] = {.lex_state = 11},
  [728] = {.lex_state = 499},
  [729] = {.lex_state = 0},
  [730] = {.lex_state = 0},
  [731] = {.lex_state = 499},
  [732] = {.lex_state = 0},
  [733] = {.lex_state = 0},
  [734] = {.lex_state = 0},
  [735] = {.lex_state = 23},
  [736] = {.lex_state = 0},
  [737] = {.lex_state = 499},
  [738] = {.lex_state = 0},
  [739] = {.lex_state = 499},
  [740] = {.lex_state = 0},
  [741] = {.lex_state = 499},
  [742] = {.lex_state = 0},
  [743] = {.lex_state = 499},
  [744] = {.lex_state = 499},
  [745] = {.lex_state = 499},
  [746] = {.lex_state = 11},
  [747] = {.lex_state = 11},
  [748] = {.lex_state = 0},
  [749] = {.lex_state = 0},
  [750] = {.lex_state = 0},
  [751] = {.lex_state = 0},
  [752] = {.lex_state = 0},
  [753] = {.lex_state = 23},
  [754] = {.lex_state = 499},
  [755] = {.lex_state = 11},
  [756] = {.lex_state = 11},
  [757] = {.lex_state = 499},
  [758] = {.lex_state = 0},
  [759] = {.lex_state = 0},
  [760] = {.lex_state = 499},
  [761] = {.lex_state = 499},
  [762] = {.lex_state = 0},
  [763] = {.lex_state = 23},
  [764] = {.lex_state = 499},
  [765] = {.lex_state = 11},
  [766] = {.lex_state = 499},
  [767] = {.lex_state = 11},
  [768] = {.lex_state = 11},
  [769] = {.lex_state = 0},
  [770] = {.lex_state = 0},
  [771] = {.lex_state = 11},
  [772] = {.lex_state = 499},
  [773] = {.lex_state = 23},
  [774] = {.lex_state = 499},
  [775] = {.lex_state = 0},
  [776] = {.lex_state = 0},
  [777] = {.lex_state = 0},
  [778] = {.lex_state = 499},
  [779] = {.lex_state = 0},
  [780] = {.lex_state = 0},
  [781] = {.lex_state = 0},
  [782] = {.lex_state = 0},
  [783] = {.lex_state = 0},
  [784] = {.lex_state = 0},
  [785] = {.lex_state = 499},
  [786] = {.lex_state = 0},
  [787] = {.lex_state = 0},
  [788] = {.lex_state = 0},
  [789] = {.lex_state = 23},
  [790] = {.lex_state = 0},
  [791] = {.lex_state = 0},
  [792] = {.lex_state = 0},
  [793] = {.lex_state = 0},
  [794] = {.lex_state = 0},
  [795] = {.lex_state = 0},
  [796] = {.lex_state = 11},
  [797] = {.lex_state = 0},
  [798] = {.lex_state = 0},
  [799] = {.lex_state = 499},
  [800] = {.lex_state = 0},
  [801] = {.lex_state = 0},
  [802] = {.lex_state = 499},
  [803] = {.lex_state = 0},
  [804] = {.lex_state = 499},
  [805] = {.lex_state = 0},
  [806] = {.lex_state = 0},
  [807] = {.lex_state = 23},
  [808] = {.lex_state = 0},
  [809] = {.lex_state = 11},
  [810] = {.lex_state = 499},
  [811] = {.lex_state = 0},
  [812] = {.lex_state = 499},
  [813] = {.lex_state = 11},
  [814] = {.lex_state = 0},
  [815] = {.lex_state = 0},
  [816] = {.lex_state = 499},
  [817] = {.lex_state = 0},
  [818] = {.lex_state = 499},
  [819] = {.lex_state = 499},
  [820] = {.lex_state = 11},
  [821] = {.lex_state = 499},
  [822] = {.lex_state = 0},
  [823] = {.lex_state = 0},
  [824] = {.lex_state = 499},
  [825] = {.lex_state = 11},
  [826] = {.lex_state = 11},
  [827] = {.lex_state = 499},
  [828] = {.lex_state = 0},
  [829] = {.lex_state = 0},
  [830] = {.lex_state = 0},
  [831] = {.lex_state = 11},
  [832] = {.lex_state = 11},
  [833] = {.lex_state = 0},
  [834] = {.lex_state = 0},
  [835] = {.lex_state = 0},
  [836] = {.lex_state = 0},
  [837] = {.lex_state = 0},
  [838] = {.lex_state = 20},
  [839] = {.lex_state = 0},
  [840] = {.lex_state = 20},
  [841] = {.lex_state = 499},
  [842] = {.lex_state = 0},
  [843] = {.lex_state = 0},
  [844] = {.lex_state = 23},
  [845] = {.lex_state = 0},
  [846] = {.lex_state = 0},
  [847] = {.lex_state = 0},
  [848] = {.lex_state = 499},
  [849] = {.lex_state = 499},
  [850] = {.lex_state = 11},
  [851] = {.lex_state = 499},
  [852] = {.lex_state = 0},
  [853] = {.lex_state = 499},
  [854] = {.lex_state = 499},
  [855] = {.lex_state = 499},
  [856] = {.lex_state = 11},
  [857] = {.lex_state = 0},
  [858] = {.lex_state = 0},
  [859] = {.lex_state = 23},
  [860] = {.lex_state = 499},
  [861] = {.lex_state = 499},
  [862] = {.lex_state = 11},
  [863] = {.lex_state = 23},
  [864] = {.lex_state = 11},
  [865] = {.lex_state = 499},
  [866] = {.lex_state = 23},
  [867] = {.lex_state = 499},
  [868] = {.lex_state = 499},
  [869] = {.lex_state = 11},
  [870] = {.lex_state = 0},
  [871] = {.lex_state = 23},
  [872] = {.lex_state = 0},
  [873] = {.lex_state = 499},
  [874] = {.lex_state = 11},
  [875] = {.lex_state = 499},
  [876] = {.lex_state = 23},
  [877] = {.lex_state = 499},
  [878] = {.lex_state = 499},
  [879] = {.lex_state = 499},
  [880] = {.lex_state = 23},
  [881] = {.lex_state = 0},
  [882] = {.lex_state = 0},
  [883] = {.lex_state = 499},
  [884] = {.lex_state = 499},
  [885] = {.lex_state = 0},
  [886] = {.lex_state = 23},
  [887] = {.lex_state = 0},
  [888] = {.lex_state = 499},
  [889] = {.lex_state = 23},
  [890] = {.lex_state = 23},
  [891] = {.lex_state = 499},
  [892] = {.lex_state = 23},
  [893] = {.lex_state = 0},
  [894] = {.lex_state = 499},
  [895] = {.lex_state = 11},
  [896] = {.lex_state = 499},
  [897] = {.lex_state = 23},
  [898] = {.lex_state = 499},
  [899] = {.lex_state = 499},
  [900] = {.lex_state = 20},
  [901] = {.lex_state = 499},
  [902] = {.lex_state = 499},
  [903] = {.lex_state = 0},
  [904] = {.lex_state = 499},
  [905] = {.lex_state = 11},
  [906] = {.lex_state = 0},
  [907] = {.lex_state = 499},
  [908] = {.lex_state = 499},
  [909] = {.lex_state = 0},
  [910] = {.lex_state = 0},
  [911] = {.lex_state = 0},
  [912] = {.lex_state = 499},
  [913] = {.lex_state = 499},
  [914] = {.lex_state = 11},
  [915] = {.lex_state = 499},
  [916] = {.lex_state = 499},
  [917] = {.lex_state = 11},
  [918] = {.lex_state = 499},
  [919] = {.lex_state = 11},
  [920] = {.lex_state = 31},
  [921] = {.lex_state = 11},
  [922] = {.lex_state = 11},
  [923] = {.lex_state = 499},
  [924] = {.lex_state = 11},
  [925] = {.lex_state = 11},
  [926] = {.lex_state = 0},
  [927] = {.lex_state = 499},
  [928] = {.lex_state = 499},
  [929] = {.lex_state = 499},
  [930] = {.lex_state = 0},
  [931] = {.lex_state = 11},
  [932] = {.lex_state = 0},
  [933] = {.lex_state = 0},
  [934] = {.lex_state = 11},
  [935] = {.lex_state = 0},
  [936] = {.lex_state = 499},
  [937] = {.lex_state = 11},
  [938] = {.lex_state = 499},
  [939] = {.lex_state = 499},
  [940] = {.lex_state = 23},
  [941] = {.lex_state = 23},
  [942] = {.lex_state = 499},
  [943] = {.lex_state = 499},
  [944] = {.lex_state = 23},
  [945] = {.lex_state = 23},
  [946] = {.lex_state = 23},
  [947] = {.lex_state = 23},
  [948] = {.lex_state = 23},
  [949] = {.lex_state = 23},
  [950] = {.lex_state = 23},
  [951] = {.lex_state = 0},
  [952] = {.lex_state = 11},
  [953] = {.lex_state = 0},
  [954] = {.lex_state = 499},
  [955] = {.lex_state = 11},
  [956] = {.lex_state = 499},
  [957] = {.lex_state = 0},
  [958] = {.lex_state = 23},
  [959] = {.lex_state = 0},
  [960] = {.lex_state = 11},
  [961] = {.lex_state = 0},
  [962] = {.lex_state = 499},
  [963] = {.lex_state = 0},
  [964] = {.lex_state = 0},
  [965] = {.lex_state = 499},
  [966] = {.lex_state = 499},
  [967] = {.lex_state = 499},
  [968] = {.lex_state = 0},
  [969] = {.lex_state = 499},
  [970] = {.lex_state = 499},
  [971] = {.lex_state = 499},
  [972] = {.lex_state = 0},
  [973] = {.lex_state = 0},
  [974] = {.lex_state = 499},
  [975] = {.lex_state = 499},
  [976] = {.lex_state = 499},
  [977] = {.lex_state = 499},
  [978] = {.lex_state = 499},
  [979] = {.lex_state = 28},
  [980] = {.lex_state = 0},
  [981] = {.lex_state = 0},
  [982] = {.lex_state = 499},
  [983] = {.lex_state = 20},
  [984] = {.lex_state = 20},
  [985] = {.lex_state = 0},
  [986] = {.lex_state = 499},
  [987] = {.lex_state = 0},
  [988] = {.lex_state = 499},
  [989] = {.lex_state = 0},
  [990] = {.lex_state = 499},
  [991] = {.lex_state = 23},
  [992] = {.lex_state = 499},
  [993] = {.lex_state = 499},
  [994] = {.lex_state = 499},
  [995] = {.lex_state = 499},
  [996] = {.lex_state = 0},
  [997] = {.lex_state = 499},
  [998] = {.lex_state = 499},
  [999] = {.lex_state = 499},
  [1000] = {.lex_state = 499},
  [1001] = {.lex_state = 499},
  [1002] = {.lex_state = 499},
  [1003] = {.lex_state = 11},
  [1004] = {.lex_state = 11},
  [1005] = {.lex_state = 11},
  [1006] = {.lex_state = 0},
  [1007] = {.lex_state = 0},
  [1008] = {.lex_state = 0},
  [1009] = {.lex_state = 0},
  [1010] = {.lex_state = 499},
  [1011] = {.lex_state = 11},
  [1012] = {.lex_state = 23},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [anon_sym_COMMA] = ACTIONS(1),
    [anon_sym_DOT] = ACTIONS(1),
    [anon_sym_SEMI] = ACTIONS(1),
    [anon_sym_SQUOTE] = ACTIONS(1),
    [anon_sym_DQUOTE] = ACTIONS(1),
    [sym_double_dollar] = ACTIONS(1),
    [aux_sym_unquoted_identifier_token1] = ACTIONS(1),
    [anon_sym__] = ACTIONS(1),
    [aux_sym_unquoted_identifier_token2] = ACTIONS(1),
    [anon_sym_DASH] = ACTIONS(1),
    [sym_nan] = ACTIONS(1),
    [sym_infinity] = ACTIONS(1),
    [sym_scientific_notation_exponent] = ACTIONS(1),
    [aux_sym_scientific_notation_token1] = ACTIONS(1),
    [sym_true_literal] = ACTIONS(1),
    [sym_false_literal] = ACTIONS(1),
    [sym_blob_literal] = ACTIONS(1),
    [sym_null_literal] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [sym_arithmetic_operator] = ACTIONS(1),
    [aux_sym_arithmetic_operation_token1] = ACTIONS(1),
    [anon_sym_QMARK] = ACTIONS(1),
    [anon_sym_COLON] = ACTIONS(1),
    [anon_sym_LT] = ACTIONS(1),
    [anon_sym_GT] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [anon_sym_LBRACK] = ACTIONS(1),
    [anon_sym_RBRACK] = ACTIONS(1),
    [sym_column_glob] = ACTIONS(1),
    [aux_sym_from_spec_token1] = ACTIONS(1),
    [aux_sym_select_statement_token1] = ACTIONS(1),
    [aux_sym_select_statement_token2] = ACTIONS(1),
    [aux_sym_select_statement_token3] = ACTIONS(1),
    [aux_sym_select_statement_token4] = ACTIONS(1),
    [aux_sym_limit_spec_token1] = ACTIONS(1),
    [aux_sym_where_spec_token1] = ACTIONS(1),
    [anon_sym_LT_EQ] = ACTIONS(1),
    [anon_sym_LT_GT] = ACTIONS(1),
    [anon_sym_EQ] = ACTIONS(1),
    [anon_sym_GT_EQ] = ACTIONS(1),
    [aux_sym_order_spec_token1] = ACTIONS(1),
    [aux_sym_delete_statement_token1] = ACTIONS(1),
    [aux_sym_delete_statement_token2] = ACTIONS(1),
    [aux_sym_delete_statement_token3] = ACTIONS(1),
    [aux_sym_begin_batch_token1] = ACTIONS(1),
    [aux_sym_using_timestamp_spec_token1] = ACTIONS(1),
    [aux_sym_insert_statement_token1] = ACTIONS(1),
    [aux_sym_truncate_token1] = ACTIONS(1),
    [aux_sym_truncate_token2] = ACTIONS(1),
    [aux_sym_create_index_token1] = ACTIONS(1),
    [aux_sym_drop_index_token1] = ACTIONS(1),
    [aux_sym_update_token1] = ACTIONS(1),
    [aux_sym_update_assignments_token1] = ACTIONS(1),
    [aux_sym_use_token1] = ACTIONS(1),
    [aux_sym_grant_token1] = ACTIONS(1),
    [aux_sym_revoke_token1] = ACTIONS(1),
    [aux_sym_privilege_token3] = ACTIONS(1),
    [aux_sym_list_roles_token1] = ACTIONS(1),
    [aux_sym_create_aggregate_token4] = ACTIONS(1),
    [aux_sym_create_aggregate_token6] = ACTIONS(1),
    [aux_sym_create_keyspace_token1] = ACTIONS(1),
    [aux_sym_alter_table_add_token1] = ACTIONS(1),
    [aux_sym_alter_table_rename_token1] = ACTIONS(1),
    [aux_sym_apply_batch_token1] = ACTIONS(1),
  },
  [1] = {
    [sym_source_file] = STATE(1009),
    [sym_select_statement] = STATE(221),
    [sym__statement] = STATE(2),
    [sym_delete_statement] = STATE(221),
    [sym_begin_batch] = STATE(567),
    [sym_insert_statement] = STATE(221),
    [sym_truncate] = STATE(221),
    [sym_create_index] = STATE(221),
    [sym_drop_index] = STATE(221),
    [sym_update] = STATE(221),
    [sym_use] = STATE(221),
    [sym_grant] = STATE(221),
    [sym_revoke] = STATE(221),
    [sym_list_roles] = STATE(221),
    [sym_list_permissions] = STATE(221),
    [sym_drop_aggregate] = STATE(221),
    [sym_drop_materialized_view] = STATE(221),
    [sym_drop_function] = STATE(221),
    [sym_drop_keyspace] = STATE(221),
    [sym_drop_role] = STATE(221),
    [sym_drop_table] = STATE(221),
    [sym_drop_trigger] = STATE(221),
    [sym_drop_type] = STATE(221),
    [sym_drop_user] = STATE(221),
    [sym_create_aggregate] = STATE(221),
    [sym_create_materialized_view] = STATE(221),
    [sym_create_function] = STATE(221),
    [sym_create_keyspace] = STATE(221),
    [sym_create_role] = STATE(221),
    [sym_create_table] = STATE(221),
    [sym_create_trigger] = STATE(221),
    [sym_create_type] = STATE(221),
    [sym_create_user] = STATE(221),
    [sym_alter_materialized_view] = STATE(221),
    [sym_alter_keyspace] = STATE(221),
    [sym_alter_role] = STATE(221),
    [sym_alter_table] = STATE(221),
    [sym_alter_type] = STATE(221),
    [sym_alter_user] = STATE(221),
    [sym_apply_batch] = STATE(221),
    [aux_sym_source_file_repeat1] = STATE(2),
    [ts_builtin_sym_end] = ACTIONS(3),
    [aux_sym_select_statement_token1] = ACTIONS(5),
    [aux_sym_delete_statement_token1] = ACTIONS(7),
    [aux_sym_begin_batch_token1] = ACTIONS(9),
    [aux_sym_insert_statement_token1] = ACTIONS(11),
    [aux_sym_truncate_token1] = ACTIONS(13),
    [aux_sym_create_index_token1] = ACTIONS(15),
    [aux_sym_drop_index_token1] = ACTIONS(17),
    [aux_sym_update_token1] = ACTIONS(19),
    [aux_sym_use_token1] = ACTIONS(21),
    [aux_sym_grant_token1] = ACTIONS(23),
    [aux_sym_revoke_token1] = ACTIONS(25),
    [aux_sym_privilege_token3] = ACTIONS(27),
    [aux_sym_list_roles_token1] = ACTIONS(29),
    [aux_sym_apply_batch_token1] = ACTIONS(31),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 18,
    ACTIONS(5), 1,
      aux_sym_select_statement_token1,
    ACTIONS(7), 1,
      aux_sym_delete_statement_token1,
    ACTIONS(9), 1,
      aux_sym_begin_batch_token1,
    ACTIONS(11), 1,
      aux_sym_insert_statement_token1,
    ACTIONS(13), 1,
      aux_sym_truncate_token1,
    ACTIONS(15), 1,
      aux_sym_create_index_token1,
    ACTIONS(17), 1,
      aux_sym_drop_index_token1,
    ACTIONS(19), 1,
      aux_sym_update_token1,
    ACTIONS(21), 1,
      aux_sym_use_token1,
    ACTIONS(23), 1,
      aux_sym_grant_token1,
    ACTIONS(25), 1,
      aux_sym_revoke_token1,
    ACTIONS(27), 1,
      aux_sym_privilege_token3,
    ACTIONS(29), 1,
      aux_sym_list_roles_token1,
    ACTIONS(31), 1,
      aux_sym_apply_batch_token1,
    ACTIONS(33), 1,
      ts_builtin_sym_end,
    STATE(567), 1,
      sym_begin_batch,
    STATE(3), 2,
      sym__statement,
      aux_sym_source_file_repeat1,
    STATE(221), 37,
      sym_select_statement,
      sym_delete_statement,
      sym_insert_statement,
      sym_truncate,
      sym_create_index,
      sym_drop_index,
      sym_update,
      sym_use,
      sym_grant,
      sym_revoke,
      sym_list_roles,
      sym_list_permissions,
      sym_drop_aggregate,
      sym_drop_materialized_view,
      sym_drop_function,
      sym_drop_keyspace,
      sym_drop_role,
      sym_drop_table,
      sym_drop_trigger,
      sym_drop_type,
      sym_drop_user,
      sym_create_aggregate,
      sym_create_materialized_view,
      sym_create_function,
      sym_create_keyspace,
      sym_create_role,
      sym_create_table,
      sym_create_trigger,
      sym_create_type,
      sym_create_user,
      sym_alter_materialized_view,
      sym_alter_keyspace,
      sym_alter_role,
      sym_alter_table,
      sym_alter_type,
      sym_alter_user,
      sym_apply_batch,
  [92] = 18,
    ACTIONS(35), 1,
      ts_builtin_sym_end,
    ACTIONS(37), 1,
      aux_sym_select_statement_token1,
    ACTIONS(40), 1,
      aux_sym_delete_statement_token1,
    ACTIONS(43), 1,
      aux_sym_begin_batch_token1,
    ACTIONS(46), 1,
      aux_sym_insert_statement_token1,
    ACTIONS(49), 1,
      aux_sym_truncate_token1,
    ACTIONS(52), 1,
      aux_sym_create_index_token1,
    ACTIONS(55), 1,
      aux_sym_drop_index_token1,
    ACTIONS(58), 1,
      aux_sym_update_token1,
    ACTIONS(61), 1,
      aux_sym_use_token1,
    ACTIONS(64), 1,
      aux_sym_grant_token1,
    ACTIONS(67), 1,
      aux_sym_revoke_token1,
    ACTIONS(70), 1,
      aux_sym_privilege_token3,
    ACTIONS(73), 1,
      aux_sym_list_roles_token1,
    ACTIONS(76), 1,
      aux_sym_apply_batch_token1,
    STATE(567), 1,
      sym_begin_batch,
    STATE(3), 2,
      sym__statement,
      aux_sym_source_file_repeat1,
    STATE(221), 37,
      sym_select_statement,
      sym_delete_statement,
      sym_insert_statement,
      sym_truncate,
      sym_create_index,
      sym_drop_index,
      sym_update,
      sym_use,
      sym_grant,
      sym_revoke,
      sym_list_roles,
      sym_list_permissions,
      sym_drop_aggregate,
      sym_drop_materialized_view,
      sym_drop_function,
      sym_drop_keyspace,
      sym_drop_role,
      sym_drop_table,
      sym_drop_trigger,
      sym_drop_type,
      sym_drop_user,
      sym_create_aggregate,
      sym_create_materialized_view,
      sym_create_function,
      sym_create_keyspace,
      sym_create_role,
      sym_create_table,
      sym_create_trigger,
      sym_create_type,
      sym_create_user,
      sym_alter_materialized_view,
      sym_alter_keyspace,
      sym_alter_role,
      sym_alter_table,
      sym_alter_type,
      sym_alter_user,
      sym_apply_batch,
  [184] = 2,
    ACTIONS(81), 2,
      anon_sym_LT,
      anon_sym_GT,
    ACTIONS(79), 33,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_SEMI,
      aux_sym_scientific_notation_token1,
      anon_sym_RPAREN,
      aux_sym_arithmetic_operation_token1,
      anon_sym_COLON,
      anon_sym_RBRACE,
      anon_sym_RBRACK,
      aux_sym_select_statement_token1,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_relation_elements_token1,
      anon_sym_LT_EQ,
      anon_sym_LT_GT,
      anon_sym_EQ,
      anon_sym_GT_EQ,
      aux_sym_order_spec_token1,
      aux_sym_delete_statement_token1,
      aux_sym_delete_statement_token2,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_primary_key_column_token1,
      aux_sym_apply_batch_token1,
  [224] = 3,
    ACTIONS(85), 1,
      aux_sym_unquoted_identifier_token2,
    STATE(8), 1,
      aux_sym_integer_repeat1,
    ACTIONS(83), 33,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_DOT,
      anon_sym_SEMI,
      sym_scientific_notation_exponent,
      aux_sym_scientific_notation_token1,
      anon_sym_RPAREN,
      aux_sym_arithmetic_operation_token1,
      anon_sym_COLON,
      anon_sym_RBRACE,
      anon_sym_RBRACK,
      aux_sym_select_statement_token1,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_where_spec_token1,
      aux_sym_relation_elements_token1,
      aux_sym_order_spec_token1,
      aux_sym_delete_statement_token1,
      aux_sym_delete_statement_token2,
      aux_sym_begin_batch_token1,
      aux_sym_using_timestamp_spec_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_primary_key_column_token1,
      aux_sym_apply_batch_token1,
  [266] = 25,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(89), 1,
      anon_sym_DQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    ACTIONS(93), 1,
      aux_sym_unquoted_identifier_token1,
    ACTIONS(95), 1,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(97), 1,
      anon_sym_DASH,
    ACTIONS(103), 1,
      sym_uuid_literal,
    ACTIONS(107), 1,
      anon_sym_QMARK,
    ACTIONS(109), 1,
      anon_sym_COLON,
    STATE(5), 1,
      aux_sym_integer_repeat1,
    STATE(10), 1,
      sym_integer,
    STATE(121), 1,
      sym_identifier,
    STATE(416), 1,
      sym_single_quote,
    STATE(440), 1,
      sym_double_quote,
    STATE(581), 1,
      sym_term,
    STATE(788), 1,
      sym_map_entry,
    STATE(903), 1,
      sym_function_name,
    STATE(964), 1,
      sym_map_key,
    ACTIONS(99), 2,
      sym_nan,
      sym_infinity,
    ACTIONS(101), 2,
      sym_true_literal,
      sym_false_literal,
    ACTIONS(105), 2,
      sym_blob_literal,
      sym_null_literal,
    STATE(34), 2,
      sym_standard_decimal_notation,
      sym_scientific_notation,
    STATE(94), 2,
      sym_unquoted_identifier,
      sym_quoted_identifier,
    STATE(31), 3,
      sym_string_literal,
      sym_float_literal,
      sym_boolean_literal,
    STATE(373), 4,
      sym_constant,
      sym_function_call,
      sym_arithmetic_operation,
      sym_bind_marker,
  [352] = 3,
    ACTIONS(85), 1,
      aux_sym_unquoted_identifier_token2,
    STATE(8), 1,
      aux_sym_integer_repeat1,
    ACTIONS(111), 33,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_DOT,
      anon_sym_SEMI,
      sym_scientific_notation_exponent,
      aux_sym_scientific_notation_token1,
      anon_sym_RPAREN,
      aux_sym_arithmetic_operation_token1,
      anon_sym_COLON,
      anon_sym_RBRACE,
      anon_sym_RBRACK,
      aux_sym_select_statement_token1,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_where_spec_token1,
      aux_sym_relation_elements_token1,
      aux_sym_order_spec_token1,
      aux_sym_delete_statement_token1,
      aux_sym_delete_statement_token2,
      aux_sym_begin_batch_token1,
      aux_sym_using_timestamp_spec_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_primary_key_column_token1,
      aux_sym_apply_batch_token1,
  [394] = 3,
    ACTIONS(115), 1,
      aux_sym_unquoted_identifier_token2,
    STATE(8), 1,
      aux_sym_integer_repeat1,
    ACTIONS(113), 33,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_DOT,
      anon_sym_SEMI,
      sym_scientific_notation_exponent,
      aux_sym_scientific_notation_token1,
      anon_sym_RPAREN,
      aux_sym_arithmetic_operation_token1,
      anon_sym_COLON,
      anon_sym_RBRACE,
      anon_sym_RBRACK,
      aux_sym_select_statement_token1,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_where_spec_token1,
      aux_sym_relation_elements_token1,
      aux_sym_order_spec_token1,
      aux_sym_delete_statement_token1,
      aux_sym_delete_statement_token2,
      aux_sym_begin_batch_token1,
      aux_sym_using_timestamp_spec_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_primary_key_column_token1,
      aux_sym_apply_batch_token1,
  [436] = 25,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(89), 1,
      anon_sym_DQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    ACTIONS(93), 1,
      aux_sym_unquoted_identifier_token1,
    ACTIONS(95), 1,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(97), 1,
      anon_sym_DASH,
    ACTIONS(103), 1,
      sym_uuid_literal,
    ACTIONS(107), 1,
      anon_sym_QMARK,
    ACTIONS(109), 1,
      anon_sym_COLON,
    STATE(5), 1,
      aux_sym_integer_repeat1,
    STATE(10), 1,
      sym_integer,
    STATE(121), 1,
      sym_identifier,
    STATE(416), 1,
      sym_single_quote,
    STATE(422), 1,
      sym_term,
    STATE(440), 1,
      sym_double_quote,
    STATE(633), 1,
      sym_map_entry,
    STATE(903), 1,
      sym_function_name,
    STATE(964), 1,
      sym_map_key,
    ACTIONS(99), 2,
      sym_nan,
      sym_infinity,
    ACTIONS(101), 2,
      sym_true_literal,
      sym_false_literal,
    ACTIONS(105), 2,
      sym_blob_literal,
      sym_null_literal,
    STATE(34), 2,
      sym_standard_decimal_notation,
      sym_scientific_notation,
    STATE(94), 2,
      sym_unquoted_identifier,
      sym_quoted_identifier,
    STATE(31), 3,
      sym_string_literal,
      sym_float_literal,
      sym_boolean_literal,
    STATE(373), 4,
      sym_constant,
      sym_function_call,
      sym_arithmetic_operation,
      sym_bind_marker,
  [522] = 5,
    ACTIONS(120), 1,
      anon_sym_DOT,
    ACTIONS(122), 1,
      sym_scientific_notation_exponent,
    STATE(27), 1,
      sym_decimal_fraction,
    STATE(638), 1,
      sym_dot_sep,
    ACTIONS(118), 31,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_SEMI,
      aux_sym_scientific_notation_token1,
      anon_sym_RPAREN,
      aux_sym_arithmetic_operation_token1,
      anon_sym_COLON,
      anon_sym_RBRACE,
      anon_sym_RBRACK,
      aux_sym_select_statement_token1,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_where_spec_token1,
      aux_sym_relation_elements_token1,
      aux_sym_order_spec_token1,
      aux_sym_delete_statement_token1,
      aux_sym_delete_statement_token2,
      aux_sym_begin_batch_token1,
      aux_sym_using_timestamp_spec_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_primary_key_column_token1,
      aux_sym_apply_batch_token1,
  [568] = 1,
    ACTIONS(124), 35,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_SQUOTE,
      aux_sym_scientific_notation_token1,
      anon_sym_RPAREN,
      aux_sym_arithmetic_operation_token1,
      anon_sym_COLON,
      anon_sym_RBRACE,
      anon_sym_RBRACK,
      aux_sym_select_statement_token1,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_where_spec_token1,
      aux_sym_relation_elements_token1,
      aux_sym_order_spec_token1,
      aux_sym_delete_statement_token1,
      aux_sym_delete_statement_token2,
      aux_sym_begin_batch_token1,
      aux_sym_using_timestamp_spec_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_create_index_token3,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_role_with_option_token3,
      aux_sym_primary_key_column_token1,
      aux_sym_user_super_user_token1,
      aux_sym_apply_batch_token1,
  [606] = 2,
    ACTIONS(128), 1,
      anon_sym_SQUOTE,
    ACTIONS(126), 34,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_SEMI,
      aux_sym_scientific_notation_token1,
      anon_sym_RPAREN,
      aux_sym_arithmetic_operation_token1,
      anon_sym_COLON,
      anon_sym_RBRACE,
      anon_sym_RBRACK,
      aux_sym_select_statement_token1,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_where_spec_token1,
      aux_sym_relation_elements_token1,
      aux_sym_order_spec_token1,
      aux_sym_delete_statement_token1,
      aux_sym_delete_statement_token2,
      aux_sym_begin_batch_token1,
      aux_sym_using_timestamp_spec_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_create_index_token3,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_role_with_option_token3,
      aux_sym_primary_key_column_token1,
      aux_sym_user_super_user_token1,
      aux_sym_apply_batch_token1,
  [646] = 24,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(89), 1,
      anon_sym_DQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    ACTIONS(93), 1,
      aux_sym_unquoted_identifier_token1,
    ACTIONS(95), 1,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(97), 1,
      anon_sym_DASH,
    ACTIONS(103), 1,
      sym_uuid_literal,
    ACTIONS(107), 1,
      anon_sym_QMARK,
    ACTIONS(109), 1,
      anon_sym_COLON,
    STATE(5), 1,
      aux_sym_integer_repeat1,
    STATE(10), 1,
      sym_integer,
    STATE(121), 1,
      sym_identifier,
    STATE(416), 1,
      sym_single_quote,
    STATE(440), 1,
      sym_double_quote,
    STATE(451), 1,
      sym_term,
    STATE(709), 1,
      sym_map_value,
    STATE(903), 1,
      sym_function_name,
    ACTIONS(99), 2,
      sym_nan,
      sym_infinity,
    ACTIONS(101), 2,
      sym_true_literal,
      sym_false_literal,
    ACTIONS(105), 2,
      sym_blob_literal,
      sym_null_literal,
    STATE(34), 2,
      sym_standard_decimal_notation,
      sym_scientific_notation,
    STATE(94), 2,
      sym_unquoted_identifier,
      sym_quoted_identifier,
    STATE(31), 3,
      sym_string_literal,
      sym_float_literal,
      sym_boolean_literal,
    STATE(373), 4,
      sym_constant,
      sym_function_call,
      sym_arithmetic_operation,
      sym_bind_marker,
  [729] = 3,
    ACTIONS(85), 1,
      aux_sym_unquoted_identifier_token2,
    STATE(8), 1,
      aux_sym_integer_repeat1,
    ACTIONS(130), 32,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_SEMI,
      sym_scientific_notation_exponent,
      aux_sym_scientific_notation_token1,
      anon_sym_RPAREN,
      aux_sym_arithmetic_operation_token1,
      anon_sym_COLON,
      anon_sym_RBRACE,
      anon_sym_RBRACK,
      aux_sym_select_statement_token1,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_where_spec_token1,
      aux_sym_relation_elements_token1,
      aux_sym_order_spec_token1,
      aux_sym_delete_statement_token1,
      aux_sym_delete_statement_token2,
      aux_sym_begin_batch_token1,
      aux_sym_using_timestamp_spec_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_primary_key_column_token1,
      aux_sym_apply_batch_token1,
  [770] = 24,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(89), 1,
      anon_sym_DQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    ACTIONS(93), 1,
      aux_sym_unquoted_identifier_token1,
    ACTIONS(95), 1,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(97), 1,
      anon_sym_DASH,
    ACTIONS(103), 1,
      sym_uuid_literal,
    ACTIONS(107), 1,
      anon_sym_QMARK,
    ACTIONS(109), 1,
      anon_sym_COLON,
    STATE(5), 1,
      aux_sym_integer_repeat1,
    STATE(10), 1,
      sym_integer,
    STATE(121), 1,
      sym_identifier,
    STATE(389), 1,
      sym_term,
    STATE(416), 1,
      sym_single_quote,
    STATE(440), 1,
      sym_double_quote,
    STATE(903), 1,
      sym_function_name,
    STATE(953), 1,
      sym_function_args,
    ACTIONS(99), 2,
      sym_nan,
      sym_infinity,
    ACTIONS(101), 2,
      sym_true_literal,
      sym_false_literal,
    ACTIONS(105), 2,
      sym_blob_literal,
      sym_null_literal,
    STATE(34), 2,
      sym_standard_decimal_notation,
      sym_scientific_notation,
    STATE(94), 2,
      sym_unquoted_identifier,
      sym_quoted_identifier,
    STATE(31), 3,
      sym_string_literal,
      sym_float_literal,
      sym_boolean_literal,
    STATE(373), 4,
      sym_constant,
      sym_function_call,
      sym_arithmetic_operation,
      sym_bind_marker,
  [853] = 1,
    ACTIONS(126), 34,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_SEMI,
      aux_sym_scientific_notation_token1,
      anon_sym_RPAREN,
      aux_sym_arithmetic_operation_token1,
      anon_sym_COLON,
      anon_sym_RBRACE,
      anon_sym_RBRACK,
      aux_sym_select_statement_token1,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_where_spec_token1,
      aux_sym_relation_elements_token1,
      aux_sym_order_spec_token1,
      aux_sym_delete_statement_token1,
      aux_sym_delete_statement_token2,
      aux_sym_begin_batch_token1,
      aux_sym_using_timestamp_spec_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_create_index_token3,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_role_with_option_token3,
      aux_sym_primary_key_column_token1,
      aux_sym_user_super_user_token1,
      aux_sym_apply_batch_token1,
  [890] = 24,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(89), 1,
      anon_sym_DQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    ACTIONS(93), 1,
      aux_sym_unquoted_identifier_token1,
    ACTIONS(95), 1,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(97), 1,
      anon_sym_DASH,
    ACTIONS(103), 1,
      sym_uuid_literal,
    ACTIONS(107), 1,
      anon_sym_QMARK,
    ACTIONS(109), 1,
      anon_sym_COLON,
    STATE(5), 1,
      aux_sym_integer_repeat1,
    STATE(10), 1,
      sym_integer,
    STATE(121), 1,
      sym_identifier,
    STATE(389), 1,
      sym_term,
    STATE(416), 1,
      sym_single_quote,
    STATE(440), 1,
      sym_double_quote,
    STATE(769), 1,
      sym_function_args,
    STATE(903), 1,
      sym_function_name,
    ACTIONS(99), 2,
      sym_nan,
      sym_infinity,
    ACTIONS(101), 2,
      sym_true_literal,
      sym_false_literal,
    ACTIONS(105), 2,
      sym_blob_literal,
      sym_null_literal,
    STATE(34), 2,
      sym_standard_decimal_notation,
      sym_scientific_notation,
    STATE(94), 2,
      sym_unquoted_identifier,
      sym_quoted_identifier,
    STATE(31), 3,
      sym_string_literal,
      sym_float_literal,
      sym_boolean_literal,
    STATE(373), 4,
      sym_constant,
      sym_function_call,
      sym_arithmetic_operation,
      sym_bind_marker,
  [973] = 23,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(89), 1,
      anon_sym_DQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    ACTIONS(93), 1,
      aux_sym_unquoted_identifier_token1,
    ACTIONS(95), 1,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(97), 1,
      anon_sym_DASH,
    ACTIONS(103), 1,
      sym_uuid_literal,
    ACTIONS(107), 1,
      anon_sym_QMARK,
    ACTIONS(109), 1,
      anon_sym_COLON,
    STATE(5), 1,
      aux_sym_integer_repeat1,
    STATE(10), 1,
      sym_integer,
    STATE(121), 1,
      sym_identifier,
    STATE(416), 1,
      sym_single_quote,
    STATE(440), 1,
      sym_double_quote,
    STATE(475), 1,
      sym_term,
    STATE(903), 1,
      sym_function_name,
    ACTIONS(99), 2,
      sym_nan,
      sym_infinity,
    ACTIONS(101), 2,
      sym_true_literal,
      sym_false_literal,
    ACTIONS(105), 2,
      sym_blob_literal,
      sym_null_literal,
    STATE(34), 2,
      sym_standard_decimal_notation,
      sym_scientific_notation,
    STATE(94), 2,
      sym_unquoted_identifier,
      sym_quoted_identifier,
    STATE(31), 3,
      sym_string_literal,
      sym_float_literal,
      sym_boolean_literal,
    STATE(373), 4,
      sym_constant,
      sym_function_call,
      sym_arithmetic_operation,
      sym_bind_marker,
  [1053] = 23,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(89), 1,
      anon_sym_DQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    ACTIONS(93), 1,
      aux_sym_unquoted_identifier_token1,
    ACTIONS(95), 1,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(97), 1,
      anon_sym_DASH,
    ACTIONS(103), 1,
      sym_uuid_literal,
    ACTIONS(107), 1,
      anon_sym_QMARK,
    ACTIONS(109), 1,
      anon_sym_COLON,
    STATE(5), 1,
      aux_sym_integer_repeat1,
    STATE(10), 1,
      sym_integer,
    STATE(121), 1,
      sym_identifier,
    STATE(369), 1,
      sym_term,
    STATE(416), 1,
      sym_single_quote,
    STATE(440), 1,
      sym_double_quote,
    STATE(903), 1,
      sym_function_name,
    ACTIONS(99), 2,
      sym_nan,
      sym_infinity,
    ACTIONS(101), 2,
      sym_true_literal,
      sym_false_literal,
    ACTIONS(105), 2,
      sym_blob_literal,
      sym_null_literal,
    STATE(34), 2,
      sym_standard_decimal_notation,
      sym_scientific_notation,
    STATE(94), 2,
      sym_unquoted_identifier,
      sym_quoted_identifier,
    STATE(31), 3,
      sym_string_literal,
      sym_float_literal,
      sym_boolean_literal,
    STATE(373), 4,
      sym_constant,
      sym_function_call,
      sym_arithmetic_operation,
      sym_bind_marker,
  [1133] = 23,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(89), 1,
      anon_sym_DQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    ACTIONS(93), 1,
      aux_sym_unquoted_identifier_token1,
    ACTIONS(95), 1,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(97), 1,
      anon_sym_DASH,
    ACTIONS(103), 1,
      sym_uuid_literal,
    ACTIONS(107), 1,
      anon_sym_QMARK,
    ACTIONS(109), 1,
      anon_sym_COLON,
    STATE(5), 1,
      aux_sym_integer_repeat1,
    STATE(10), 1,
      sym_integer,
    STATE(121), 1,
      sym_identifier,
    STATE(377), 1,
      sym_term,
    STATE(416), 1,
      sym_single_quote,
    STATE(440), 1,
      sym_double_quote,
    STATE(903), 1,
      sym_function_name,
    ACTIONS(99), 2,
      sym_nan,
      sym_infinity,
    ACTIONS(101), 2,
      sym_true_literal,
      sym_false_literal,
    ACTIONS(105), 2,
      sym_blob_literal,
      sym_null_literal,
    STATE(34), 2,
      sym_standard_decimal_notation,
      sym_scientific_notation,
    STATE(94), 2,
      sym_unquoted_identifier,
      sym_quoted_identifier,
    STATE(31), 3,
      sym_string_literal,
      sym_float_literal,
      sym_boolean_literal,
    STATE(373), 4,
      sym_constant,
      sym_function_call,
      sym_arithmetic_operation,
      sym_bind_marker,
  [1213] = 3,
    ACTIONS(85), 1,
      aux_sym_unquoted_identifier_token2,
    STATE(8), 1,
      aux_sym_integer_repeat1,
    ACTIONS(132), 31,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_SEMI,
      aux_sym_scientific_notation_token1,
      anon_sym_RPAREN,
      aux_sym_arithmetic_operation_token1,
      anon_sym_COLON,
      anon_sym_RBRACE,
      anon_sym_RBRACK,
      aux_sym_select_statement_token1,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_where_spec_token1,
      aux_sym_relation_elements_token1,
      aux_sym_order_spec_token1,
      aux_sym_delete_statement_token1,
      aux_sym_delete_statement_token2,
      aux_sym_begin_batch_token1,
      aux_sym_using_timestamp_spec_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_primary_key_column_token1,
      aux_sym_apply_batch_token1,
  [1253] = 3,
    ACTIONS(85), 1,
      aux_sym_unquoted_identifier_token2,
    STATE(8), 1,
      aux_sym_integer_repeat1,
    ACTIONS(134), 31,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_SEMI,
      aux_sym_scientific_notation_token1,
      anon_sym_RPAREN,
      aux_sym_arithmetic_operation_token1,
      anon_sym_COLON,
      anon_sym_RBRACE,
      anon_sym_RBRACK,
      aux_sym_select_statement_token1,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_where_spec_token1,
      aux_sym_relation_elements_token1,
      aux_sym_order_spec_token1,
      aux_sym_delete_statement_token1,
      aux_sym_delete_statement_token2,
      aux_sym_begin_batch_token1,
      aux_sym_using_timestamp_spec_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_primary_key_column_token1,
      aux_sym_apply_batch_token1,
  [1293] = 23,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(89), 1,
      anon_sym_DQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    ACTIONS(93), 1,
      aux_sym_unquoted_identifier_token1,
    ACTIONS(95), 1,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(97), 1,
      anon_sym_DASH,
    ACTIONS(103), 1,
      sym_uuid_literal,
    ACTIONS(107), 1,
      anon_sym_QMARK,
    ACTIONS(109), 1,
      anon_sym_COLON,
    STATE(5), 1,
      aux_sym_integer_repeat1,
    STATE(10), 1,
      sym_integer,
    STATE(121), 1,
      sym_identifier,
    STATE(416), 1,
      sym_single_quote,
    STATE(440), 1,
      sym_double_quote,
    STATE(585), 1,
      sym_term,
    STATE(903), 1,
      sym_function_name,
    ACTIONS(99), 2,
      sym_nan,
      sym_infinity,
    ACTIONS(101), 2,
      sym_true_literal,
      sym_false_literal,
    ACTIONS(105), 2,
      sym_blob_literal,
      sym_null_literal,
    STATE(34), 2,
      sym_standard_decimal_notation,
      sym_scientific_notation,
    STATE(94), 2,
      sym_unquoted_identifier,
      sym_quoted_identifier,
    STATE(31), 3,
      sym_string_literal,
      sym_float_literal,
      sym_boolean_literal,
    STATE(373), 4,
      sym_constant,
      sym_function_call,
      sym_arithmetic_operation,
      sym_bind_marker,
  [1373] = 3,
    ACTIONS(85), 1,
      aux_sym_unquoted_identifier_token2,
    STATE(8), 1,
      aux_sym_integer_repeat1,
    ACTIONS(136), 31,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_SEMI,
      aux_sym_scientific_notation_token1,
      anon_sym_RPAREN,
      aux_sym_arithmetic_operation_token1,
      anon_sym_COLON,
      anon_sym_RBRACE,
      anon_sym_RBRACK,
      aux_sym_select_statement_token1,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_where_spec_token1,
      aux_sym_relation_elements_token1,
      aux_sym_order_spec_token1,
      aux_sym_delete_statement_token1,
      aux_sym_delete_statement_token2,
      aux_sym_begin_batch_token1,
      aux_sym_using_timestamp_spec_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_primary_key_column_token1,
      aux_sym_apply_batch_token1,
  [1413] = 23,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(89), 1,
      anon_sym_DQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    ACTIONS(93), 1,
      aux_sym_unquoted_identifier_token1,
    ACTIONS(95), 1,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(97), 1,
      anon_sym_DASH,
    ACTIONS(103), 1,
      sym_uuid_literal,
    ACTIONS(107), 1,
      anon_sym_QMARK,
    ACTIONS(109), 1,
      anon_sym_COLON,
    STATE(5), 1,
      aux_sym_integer_repeat1,
    STATE(10), 1,
      sym_integer,
    STATE(121), 1,
      sym_identifier,
    STATE(416), 1,
      sym_single_quote,
    STATE(440), 1,
      sym_double_quote,
    STATE(453), 1,
      sym_term,
    STATE(903), 1,
      sym_function_name,
    ACTIONS(99), 2,
      sym_nan,
      sym_infinity,
    ACTIONS(101), 2,
      sym_true_literal,
      sym_false_literal,
    ACTIONS(105), 2,
      sym_blob_literal,
      sym_null_literal,
    STATE(34), 2,
      sym_standard_decimal_notation,
      sym_scientific_notation,
    STATE(94), 2,
      sym_unquoted_identifier,
      sym_quoted_identifier,
    STATE(31), 3,
      sym_string_literal,
      sym_float_literal,
      sym_boolean_literal,
    STATE(373), 4,
      sym_constant,
      sym_function_call,
      sym_arithmetic_operation,
      sym_bind_marker,
  [1493] = 23,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(89), 1,
      anon_sym_DQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    ACTIONS(93), 1,
      aux_sym_unquoted_identifier_token1,
    ACTIONS(95), 1,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(97), 1,
      anon_sym_DASH,
    ACTIONS(103), 1,
      sym_uuid_literal,
    ACTIONS(107), 1,
      anon_sym_QMARK,
    ACTIONS(109), 1,
      anon_sym_COLON,
    STATE(5), 1,
      aux_sym_integer_repeat1,
    STATE(10), 1,
      sym_integer,
    STATE(121), 1,
      sym_identifier,
    STATE(416), 1,
      sym_single_quote,
    STATE(440), 1,
      sym_double_quote,
    STATE(578), 1,
      sym_term,
    STATE(903), 1,
      sym_function_name,
    ACTIONS(99), 2,
      sym_nan,
      sym_infinity,
    ACTIONS(101), 2,
      sym_true_literal,
      sym_false_literal,
    ACTIONS(105), 2,
      sym_blob_literal,
      sym_null_literal,
    STATE(34), 2,
      sym_standard_decimal_notation,
      sym_scientific_notation,
    STATE(94), 2,
      sym_unquoted_identifier,
      sym_quoted_identifier,
    STATE(31), 3,
      sym_string_literal,
      sym_float_literal,
      sym_boolean_literal,
    STATE(373), 4,
      sym_constant,
      sym_function_call,
      sym_arithmetic_operation,
      sym_bind_marker,
  [1573] = 2,
    ACTIONS(140), 1,
      sym_scientific_notation_exponent,
    ACTIONS(138), 31,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_SEMI,
      aux_sym_scientific_notation_token1,
      anon_sym_RPAREN,
      aux_sym_arithmetic_operation_token1,
      anon_sym_COLON,
      anon_sym_RBRACE,
      anon_sym_RBRACK,
      aux_sym_select_statement_token1,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_where_spec_token1,
      aux_sym_relation_elements_token1,
      aux_sym_order_spec_token1,
      aux_sym_delete_statement_token1,
      aux_sym_delete_statement_token2,
      aux_sym_begin_batch_token1,
      aux_sym_using_timestamp_spec_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_primary_key_column_token1,
      aux_sym_apply_batch_token1,
  [1610] = 22,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(89), 1,
      anon_sym_DQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    ACTIONS(93), 1,
      aux_sym_unquoted_identifier_token1,
    ACTIONS(95), 1,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(97), 1,
      anon_sym_DASH,
    ACTIONS(103), 1,
      sym_uuid_literal,
    ACTIONS(107), 1,
      anon_sym_QMARK,
    ACTIONS(109), 1,
      anon_sym_COLON,
    STATE(5), 1,
      aux_sym_integer_repeat1,
    STATE(10), 1,
      sym_integer,
    STATE(121), 1,
      sym_identifier,
    STATE(416), 1,
      sym_single_quote,
    STATE(440), 1,
      sym_double_quote,
    STATE(903), 1,
      sym_function_name,
    ACTIONS(99), 2,
      sym_nan,
      sym_infinity,
    ACTIONS(101), 2,
      sym_true_literal,
      sym_false_literal,
    ACTIONS(105), 2,
      sym_blob_literal,
      sym_null_literal,
    STATE(34), 2,
      sym_standard_decimal_notation,
      sym_scientific_notation,
    STATE(94), 2,
      sym_unquoted_identifier,
      sym_quoted_identifier,
    STATE(31), 3,
      sym_string_literal,
      sym_float_literal,
      sym_boolean_literal,
    STATE(84), 4,
      sym_constant,
      sym_function_call,
      sym_bind_marker,
      sym__value_marker,
  [1687] = 21,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    ACTIONS(95), 1,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(97), 1,
      anon_sym_DASH,
    ACTIONS(103), 1,
      sym_uuid_literal,
    ACTIONS(107), 1,
      anon_sym_QMARK,
    ACTIONS(109), 1,
      anon_sym_COLON,
    ACTIONS(142), 1,
      anon_sym_LPAREN,
    ACTIONS(144), 1,
      anon_sym_LBRACE,
    ACTIONS(146), 1,
      anon_sym_LBRACK,
    STATE(5), 1,
      aux_sym_integer_repeat1,
    STATE(10), 1,
      sym_integer,
    STATE(416), 1,
      sym_single_quote,
    STATE(577), 1,
      sym_expression,
    STATE(961), 1,
      sym_expression_list,
    ACTIONS(99), 2,
      sym_nan,
      sym_infinity,
    ACTIONS(101), 2,
      sym_true_literal,
      sym_false_literal,
    ACTIONS(105), 2,
      sym_blob_literal,
      sym_null_literal,
    STATE(34), 2,
      sym_standard_decimal_notation,
      sym_scientific_notation,
    STATE(31), 3,
      sym_string_literal,
      sym_float_literal,
      sym_boolean_literal,
    STATE(635), 6,
      sym_constant,
      sym_bind_marker,
      sym_map_literal,
      sym_set_literal,
      sym_list_literal,
      sym_assignment_tuple,
  [1762] = 21,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    ACTIONS(95), 1,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(97), 1,
      anon_sym_DASH,
    ACTIONS(103), 1,
      sym_uuid_literal,
    ACTIONS(107), 1,
      anon_sym_QMARK,
    ACTIONS(109), 1,
      anon_sym_COLON,
    ACTIONS(142), 1,
      anon_sym_LPAREN,
    ACTIONS(144), 1,
      anon_sym_LBRACE,
    ACTIONS(146), 1,
      anon_sym_LBRACK,
    STATE(5), 1,
      aux_sym_integer_repeat1,
    STATE(10), 1,
      sym_integer,
    STATE(416), 1,
      sym_single_quote,
    STATE(577), 1,
      sym_expression,
    STATE(852), 1,
      sym_expression_list,
    ACTIONS(99), 2,
      sym_nan,
      sym_infinity,
    ACTIONS(101), 2,
      sym_true_literal,
      sym_false_literal,
    ACTIONS(105), 2,
      sym_blob_literal,
      sym_null_literal,
    STATE(34), 2,
      sym_standard_decimal_notation,
      sym_scientific_notation,
    STATE(31), 3,
      sym_string_literal,
      sym_float_literal,
      sym_boolean_literal,
    STATE(635), 6,
      sym_constant,
      sym_bind_marker,
      sym_map_literal,
      sym_set_literal,
      sym_list_literal,
      sym_assignment_tuple,
  [1837] = 1,
    ACTIONS(118), 31,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_SEMI,
      aux_sym_scientific_notation_token1,
      anon_sym_RPAREN,
      aux_sym_arithmetic_operation_token1,
      anon_sym_COLON,
      anon_sym_RBRACE,
      anon_sym_RBRACK,
      aux_sym_select_statement_token1,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_where_spec_token1,
      aux_sym_relation_elements_token1,
      aux_sym_order_spec_token1,
      aux_sym_delete_statement_token1,
      aux_sym_delete_statement_token2,
      aux_sym_begin_batch_token1,
      aux_sym_using_timestamp_spec_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_primary_key_column_token1,
      aux_sym_apply_batch_token1,
  [1871] = 20,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    ACTIONS(95), 1,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(97), 1,
      anon_sym_DASH,
    ACTIONS(103), 1,
      sym_uuid_literal,
    ACTIONS(107), 1,
      anon_sym_QMARK,
    ACTIONS(109), 1,
      anon_sym_COLON,
    ACTIONS(142), 1,
      anon_sym_LPAREN,
    ACTIONS(144), 1,
      anon_sym_LBRACE,
    ACTIONS(146), 1,
      anon_sym_LBRACK,
    STATE(5), 1,
      aux_sym_integer_repeat1,
    STATE(10), 1,
      sym_integer,
    STATE(416), 1,
      sym_single_quote,
    STATE(730), 1,
      sym_expression,
    ACTIONS(99), 2,
      sym_nan,
      sym_infinity,
    ACTIONS(101), 2,
      sym_true_literal,
      sym_false_literal,
    ACTIONS(105), 2,
      sym_blob_literal,
      sym_null_literal,
    STATE(34), 2,
      sym_standard_decimal_notation,
      sym_scientific_notation,
    STATE(31), 3,
      sym_string_literal,
      sym_float_literal,
      sym_boolean_literal,
    STATE(635), 6,
      sym_constant,
      sym_bind_marker,
      sym_map_literal,
      sym_set_literal,
      sym_list_literal,
      sym_assignment_tuple,
  [1943] = 1,
    ACTIONS(148), 31,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_SEMI,
      aux_sym_scientific_notation_token1,
      anon_sym_RPAREN,
      aux_sym_arithmetic_operation_token1,
      anon_sym_COLON,
      anon_sym_RBRACE,
      anon_sym_RBRACK,
      aux_sym_select_statement_token1,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_where_spec_token1,
      aux_sym_relation_elements_token1,
      aux_sym_order_spec_token1,
      aux_sym_delete_statement_token1,
      aux_sym_delete_statement_token2,
      aux_sym_begin_batch_token1,
      aux_sym_using_timestamp_spec_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_primary_key_column_token1,
      aux_sym_apply_batch_token1,
  [1977] = 1,
    ACTIONS(150), 31,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_SEMI,
      aux_sym_scientific_notation_token1,
      anon_sym_RPAREN,
      aux_sym_arithmetic_operation_token1,
      anon_sym_COLON,
      anon_sym_RBRACE,
      anon_sym_RBRACK,
      aux_sym_select_statement_token1,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_where_spec_token1,
      aux_sym_relation_elements_token1,
      aux_sym_order_spec_token1,
      aux_sym_delete_statement_token1,
      aux_sym_delete_statement_token2,
      aux_sym_begin_batch_token1,
      aux_sym_using_timestamp_spec_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_primary_key_column_token1,
      aux_sym_apply_batch_token1,
  [2011] = 1,
    ACTIONS(152), 29,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_SEMI,
      aux_sym_scientific_notation_token1,
      anon_sym_RPAREN,
      aux_sym_arithmetic_operation_token1,
      anon_sym_COLON,
      anon_sym_RBRACE,
      anon_sym_RBRACK,
      aux_sym_select_statement_token1,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_relation_elements_token1,
      aux_sym_order_spec_token1,
      aux_sym_delete_statement_token1,
      aux_sym_delete_statement_token2,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_primary_key_column_token1,
      aux_sym_apply_batch_token1,
  [2043] = 1,
    ACTIONS(154), 29,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_SEMI,
      aux_sym_scientific_notation_token1,
      anon_sym_RPAREN,
      aux_sym_arithmetic_operation_token1,
      anon_sym_COLON,
      anon_sym_RBRACE,
      anon_sym_RBRACK,
      aux_sym_select_statement_token1,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_relation_elements_token1,
      aux_sym_order_spec_token1,
      aux_sym_delete_statement_token1,
      aux_sym_delete_statement_token2,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_primary_key_column_token1,
      aux_sym_apply_batch_token1,
  [2075] = 3,
    STATE(74), 1,
      sym_data_type_name,
    STATE(443), 1,
      sym_data_type,
    ACTIONS(156), 26,
      aux_sym_begin_batch_token4,
      aux_sym_using_timestamp_spec_token2,
      aux_sym_update_assignments_token1,
      aux_sym_list_roles_token1,
      aux_sym_data_type_name_token1,
      aux_sym_data_type_name_token2,
      aux_sym_data_type_name_token3,
      aux_sym_data_type_name_token4,
      aux_sym_data_type_name_token5,
      aux_sym_data_type_name_token6,
      aux_sym_data_type_name_token7,
      aux_sym_data_type_name_token8,
      aux_sym_data_type_name_token9,
      aux_sym_data_type_name_token10,
      aux_sym_data_type_name_token11,
      aux_sym_data_type_name_token12,
      aux_sym_data_type_name_token13,
      aux_sym_data_type_name_token14,
      aux_sym_data_type_name_token15,
      aux_sym_data_type_name_token16,
      aux_sym_data_type_name_token17,
      aux_sym_data_type_name_token18,
      aux_sym_data_type_name_token19,
      aux_sym_data_type_name_token20,
      aux_sym_data_type_name_token21,
      sym_object_name,
  [2110] = 3,
    STATE(74), 1,
      sym_data_type_name,
    STATE(896), 1,
      sym_data_type,
    ACTIONS(156), 26,
      aux_sym_begin_batch_token4,
      aux_sym_using_timestamp_spec_token2,
      aux_sym_update_assignments_token1,
      aux_sym_list_roles_token1,
      aux_sym_data_type_name_token1,
      aux_sym_data_type_name_token2,
      aux_sym_data_type_name_token3,
      aux_sym_data_type_name_token4,
      aux_sym_data_type_name_token5,
      aux_sym_data_type_name_token6,
      aux_sym_data_type_name_token7,
      aux_sym_data_type_name_token8,
      aux_sym_data_type_name_token9,
      aux_sym_data_type_name_token10,
      aux_sym_data_type_name_token11,
      aux_sym_data_type_name_token12,
      aux_sym_data_type_name_token13,
      aux_sym_data_type_name_token14,
      aux_sym_data_type_name_token15,
      aux_sym_data_type_name_token16,
      aux_sym_data_type_name_token17,
      aux_sym_data_type_name_token18,
      aux_sym_data_type_name_token19,
      aux_sym_data_type_name_token20,
      aux_sym_data_type_name_token21,
      sym_object_name,
  [2145] = 3,
    STATE(74), 1,
      sym_data_type_name,
    STATE(899), 1,
      sym_data_type,
    ACTIONS(156), 26,
      aux_sym_begin_batch_token4,
      aux_sym_using_timestamp_spec_token2,
      aux_sym_update_assignments_token1,
      aux_sym_list_roles_token1,
      aux_sym_data_type_name_token1,
      aux_sym_data_type_name_token2,
      aux_sym_data_type_name_token3,
      aux_sym_data_type_name_token4,
      aux_sym_data_type_name_token5,
      aux_sym_data_type_name_token6,
      aux_sym_data_type_name_token7,
      aux_sym_data_type_name_token8,
      aux_sym_data_type_name_token9,
      aux_sym_data_type_name_token10,
      aux_sym_data_type_name_token11,
      aux_sym_data_type_name_token12,
      aux_sym_data_type_name_token13,
      aux_sym_data_type_name_token14,
      aux_sym_data_type_name_token15,
      aux_sym_data_type_name_token16,
      aux_sym_data_type_name_token17,
      aux_sym_data_type_name_token18,
      aux_sym_data_type_name_token19,
      aux_sym_data_type_name_token20,
      aux_sym_data_type_name_token21,
      sym_object_name,
  [2180] = 3,
    STATE(74), 1,
      sym_data_type_name,
    STATE(939), 1,
      sym_data_type,
    ACTIONS(156), 26,
      aux_sym_begin_batch_token4,
      aux_sym_using_timestamp_spec_token2,
      aux_sym_update_assignments_token1,
      aux_sym_list_roles_token1,
      aux_sym_data_type_name_token1,
      aux_sym_data_type_name_token2,
      aux_sym_data_type_name_token3,
      aux_sym_data_type_name_token4,
      aux_sym_data_type_name_token5,
      aux_sym_data_type_name_token6,
      aux_sym_data_type_name_token7,
      aux_sym_data_type_name_token8,
      aux_sym_data_type_name_token9,
      aux_sym_data_type_name_token10,
      aux_sym_data_type_name_token11,
      aux_sym_data_type_name_token12,
      aux_sym_data_type_name_token13,
      aux_sym_data_type_name_token14,
      aux_sym_data_type_name_token15,
      aux_sym_data_type_name_token16,
      aux_sym_data_type_name_token17,
      aux_sym_data_type_name_token18,
      aux_sym_data_type_name_token19,
      aux_sym_data_type_name_token20,
      aux_sym_data_type_name_token21,
      sym_object_name,
  [2215] = 3,
    STATE(74), 1,
      sym_data_type_name,
    STATE(827), 1,
      sym_data_type,
    ACTIONS(156), 26,
      aux_sym_begin_batch_token4,
      aux_sym_using_timestamp_spec_token2,
      aux_sym_update_assignments_token1,
      aux_sym_list_roles_token1,
      aux_sym_data_type_name_token1,
      aux_sym_data_type_name_token2,
      aux_sym_data_type_name_token3,
      aux_sym_data_type_name_token4,
      aux_sym_data_type_name_token5,
      aux_sym_data_type_name_token6,
      aux_sym_data_type_name_token7,
      aux_sym_data_type_name_token8,
      aux_sym_data_type_name_token9,
      aux_sym_data_type_name_token10,
      aux_sym_data_type_name_token11,
      aux_sym_data_type_name_token12,
      aux_sym_data_type_name_token13,
      aux_sym_data_type_name_token14,
      aux_sym_data_type_name_token15,
      aux_sym_data_type_name_token16,
      aux_sym_data_type_name_token17,
      aux_sym_data_type_name_token18,
      aux_sym_data_type_name_token19,
      aux_sym_data_type_name_token20,
      aux_sym_data_type_name_token21,
      sym_object_name,
  [2250] = 3,
    STATE(74), 1,
      sym_data_type_name,
    STATE(938), 1,
      sym_data_type,
    ACTIONS(156), 26,
      aux_sym_begin_batch_token4,
      aux_sym_using_timestamp_spec_token2,
      aux_sym_update_assignments_token1,
      aux_sym_list_roles_token1,
      aux_sym_data_type_name_token1,
      aux_sym_data_type_name_token2,
      aux_sym_data_type_name_token3,
      aux_sym_data_type_name_token4,
      aux_sym_data_type_name_token5,
      aux_sym_data_type_name_token6,
      aux_sym_data_type_name_token7,
      aux_sym_data_type_name_token8,
      aux_sym_data_type_name_token9,
      aux_sym_data_type_name_token10,
      aux_sym_data_type_name_token11,
      aux_sym_data_type_name_token12,
      aux_sym_data_type_name_token13,
      aux_sym_data_type_name_token14,
      aux_sym_data_type_name_token15,
      aux_sym_data_type_name_token16,
      aux_sym_data_type_name_token17,
      aux_sym_data_type_name_token18,
      aux_sym_data_type_name_token19,
      aux_sym_data_type_name_token20,
      aux_sym_data_type_name_token21,
      sym_object_name,
  [2285] = 3,
    STATE(74), 1,
      sym_data_type_name,
    STATE(821), 1,
      sym_data_type,
    ACTIONS(156), 26,
      aux_sym_begin_batch_token4,
      aux_sym_using_timestamp_spec_token2,
      aux_sym_update_assignments_token1,
      aux_sym_list_roles_token1,
      aux_sym_data_type_name_token1,
      aux_sym_data_type_name_token2,
      aux_sym_data_type_name_token3,
      aux_sym_data_type_name_token4,
      aux_sym_data_type_name_token5,
      aux_sym_data_type_name_token6,
      aux_sym_data_type_name_token7,
      aux_sym_data_type_name_token8,
      aux_sym_data_type_name_token9,
      aux_sym_data_type_name_token10,
      aux_sym_data_type_name_token11,
      aux_sym_data_type_name_token12,
      aux_sym_data_type_name_token13,
      aux_sym_data_type_name_token14,
      aux_sym_data_type_name_token15,
      aux_sym_data_type_name_token16,
      aux_sym_data_type_name_token17,
      aux_sym_data_type_name_token18,
      aux_sym_data_type_name_token19,
      aux_sym_data_type_name_token20,
      aux_sym_data_type_name_token21,
      sym_object_name,
  [2320] = 3,
    STATE(74), 1,
      sym_data_type_name,
    STATE(174), 1,
      sym_data_type,
    ACTIONS(156), 26,
      aux_sym_begin_batch_token4,
      aux_sym_using_timestamp_spec_token2,
      aux_sym_update_assignments_token1,
      aux_sym_list_roles_token1,
      aux_sym_data_type_name_token1,
      aux_sym_data_type_name_token2,
      aux_sym_data_type_name_token3,
      aux_sym_data_type_name_token4,
      aux_sym_data_type_name_token5,
      aux_sym_data_type_name_token6,
      aux_sym_data_type_name_token7,
      aux_sym_data_type_name_token8,
      aux_sym_data_type_name_token9,
      aux_sym_data_type_name_token10,
      aux_sym_data_type_name_token11,
      aux_sym_data_type_name_token12,
      aux_sym_data_type_name_token13,
      aux_sym_data_type_name_token14,
      aux_sym_data_type_name_token15,
      aux_sym_data_type_name_token16,
      aux_sym_data_type_name_token17,
      aux_sym_data_type_name_token18,
      aux_sym_data_type_name_token19,
      aux_sym_data_type_name_token20,
      aux_sym_data_type_name_token21,
      sym_object_name,
  [2355] = 3,
    STATE(74), 1,
      sym_data_type_name,
    STATE(798), 1,
      sym_data_type,
    ACTIONS(156), 26,
      aux_sym_begin_batch_token4,
      aux_sym_using_timestamp_spec_token2,
      aux_sym_update_assignments_token1,
      aux_sym_list_roles_token1,
      aux_sym_data_type_name_token1,
      aux_sym_data_type_name_token2,
      aux_sym_data_type_name_token3,
      aux_sym_data_type_name_token4,
      aux_sym_data_type_name_token5,
      aux_sym_data_type_name_token6,
      aux_sym_data_type_name_token7,
      aux_sym_data_type_name_token8,
      aux_sym_data_type_name_token9,
      aux_sym_data_type_name_token10,
      aux_sym_data_type_name_token11,
      aux_sym_data_type_name_token12,
      aux_sym_data_type_name_token13,
      aux_sym_data_type_name_token14,
      aux_sym_data_type_name_token15,
      aux_sym_data_type_name_token16,
      aux_sym_data_type_name_token17,
      aux_sym_data_type_name_token18,
      aux_sym_data_type_name_token19,
      aux_sym_data_type_name_token20,
      aux_sym_data_type_name_token21,
      sym_object_name,
  [2390] = 3,
    STATE(74), 1,
      sym_data_type_name,
    STATE(833), 1,
      sym_data_type,
    ACTIONS(156), 26,
      aux_sym_begin_batch_token4,
      aux_sym_using_timestamp_spec_token2,
      aux_sym_update_assignments_token1,
      aux_sym_list_roles_token1,
      aux_sym_data_type_name_token1,
      aux_sym_data_type_name_token2,
      aux_sym_data_type_name_token3,
      aux_sym_data_type_name_token4,
      aux_sym_data_type_name_token5,
      aux_sym_data_type_name_token6,
      aux_sym_data_type_name_token7,
      aux_sym_data_type_name_token8,
      aux_sym_data_type_name_token9,
      aux_sym_data_type_name_token10,
      aux_sym_data_type_name_token11,
      aux_sym_data_type_name_token12,
      aux_sym_data_type_name_token13,
      aux_sym_data_type_name_token14,
      aux_sym_data_type_name_token15,
      aux_sym_data_type_name_token16,
      aux_sym_data_type_name_token17,
      aux_sym_data_type_name_token18,
      aux_sym_data_type_name_token19,
      aux_sym_data_type_name_token20,
      aux_sym_data_type_name_token21,
      sym_object_name,
  [2425] = 3,
    STATE(74), 1,
      sym_data_type_name,
    STATE(875), 1,
      sym_data_type,
    ACTIONS(156), 26,
      aux_sym_begin_batch_token4,
      aux_sym_using_timestamp_spec_token2,
      aux_sym_update_assignments_token1,
      aux_sym_list_roles_token1,
      aux_sym_data_type_name_token1,
      aux_sym_data_type_name_token2,
      aux_sym_data_type_name_token3,
      aux_sym_data_type_name_token4,
      aux_sym_data_type_name_token5,
      aux_sym_data_type_name_token6,
      aux_sym_data_type_name_token7,
      aux_sym_data_type_name_token8,
      aux_sym_data_type_name_token9,
      aux_sym_data_type_name_token10,
      aux_sym_data_type_name_token11,
      aux_sym_data_type_name_token12,
      aux_sym_data_type_name_token13,
      aux_sym_data_type_name_token14,
      aux_sym_data_type_name_token15,
      aux_sym_data_type_name_token16,
      aux_sym_data_type_name_token17,
      aux_sym_data_type_name_token18,
      aux_sym_data_type_name_token19,
      aux_sym_data_type_name_token20,
      aux_sym_data_type_name_token21,
      sym_object_name,
  [2460] = 3,
    STATE(74), 1,
      sym_data_type_name,
    STATE(766), 1,
      sym_data_type,
    ACTIONS(156), 26,
      aux_sym_begin_batch_token4,
      aux_sym_using_timestamp_spec_token2,
      aux_sym_update_assignments_token1,
      aux_sym_list_roles_token1,
      aux_sym_data_type_name_token1,
      aux_sym_data_type_name_token2,
      aux_sym_data_type_name_token3,
      aux_sym_data_type_name_token4,
      aux_sym_data_type_name_token5,
      aux_sym_data_type_name_token6,
      aux_sym_data_type_name_token7,
      aux_sym_data_type_name_token8,
      aux_sym_data_type_name_token9,
      aux_sym_data_type_name_token10,
      aux_sym_data_type_name_token11,
      aux_sym_data_type_name_token12,
      aux_sym_data_type_name_token13,
      aux_sym_data_type_name_token14,
      aux_sym_data_type_name_token15,
      aux_sym_data_type_name_token16,
      aux_sym_data_type_name_token17,
      aux_sym_data_type_name_token18,
      aux_sym_data_type_name_token19,
      aux_sym_data_type_name_token20,
      aux_sym_data_type_name_token21,
      sym_object_name,
  [2495] = 3,
    STATE(74), 1,
      sym_data_type_name,
    STATE(891), 1,
      sym_data_type,
    ACTIONS(156), 26,
      aux_sym_begin_batch_token4,
      aux_sym_using_timestamp_spec_token2,
      aux_sym_update_assignments_token1,
      aux_sym_list_roles_token1,
      aux_sym_data_type_name_token1,
      aux_sym_data_type_name_token2,
      aux_sym_data_type_name_token3,
      aux_sym_data_type_name_token4,
      aux_sym_data_type_name_token5,
      aux_sym_data_type_name_token6,
      aux_sym_data_type_name_token7,
      aux_sym_data_type_name_token8,
      aux_sym_data_type_name_token9,
      aux_sym_data_type_name_token10,
      aux_sym_data_type_name_token11,
      aux_sym_data_type_name_token12,
      aux_sym_data_type_name_token13,
      aux_sym_data_type_name_token14,
      aux_sym_data_type_name_token15,
      aux_sym_data_type_name_token16,
      aux_sym_data_type_name_token17,
      aux_sym_data_type_name_token18,
      aux_sym_data_type_name_token19,
      aux_sym_data_type_name_token20,
      aux_sym_data_type_name_token21,
      sym_object_name,
  [2530] = 3,
    STATE(74), 1,
      sym_data_type_name,
    STATE(985), 1,
      sym_data_type,
    ACTIONS(156), 26,
      aux_sym_begin_batch_token4,
      aux_sym_using_timestamp_spec_token2,
      aux_sym_update_assignments_token1,
      aux_sym_list_roles_token1,
      aux_sym_data_type_name_token1,
      aux_sym_data_type_name_token2,
      aux_sym_data_type_name_token3,
      aux_sym_data_type_name_token4,
      aux_sym_data_type_name_token5,
      aux_sym_data_type_name_token6,
      aux_sym_data_type_name_token7,
      aux_sym_data_type_name_token8,
      aux_sym_data_type_name_token9,
      aux_sym_data_type_name_token10,
      aux_sym_data_type_name_token11,
      aux_sym_data_type_name_token12,
      aux_sym_data_type_name_token13,
      aux_sym_data_type_name_token14,
      aux_sym_data_type_name_token15,
      aux_sym_data_type_name_token16,
      aux_sym_data_type_name_token17,
      aux_sym_data_type_name_token18,
      aux_sym_data_type_name_token19,
      aux_sym_data_type_name_token20,
      aux_sym_data_type_name_token21,
      sym_object_name,
  [2565] = 3,
    STATE(74), 1,
      sym_data_type_name,
    STATE(233), 1,
      sym_data_type,
    ACTIONS(156), 26,
      aux_sym_begin_batch_token4,
      aux_sym_using_timestamp_spec_token2,
      aux_sym_update_assignments_token1,
      aux_sym_list_roles_token1,
      aux_sym_data_type_name_token1,
      aux_sym_data_type_name_token2,
      aux_sym_data_type_name_token3,
      aux_sym_data_type_name_token4,
      aux_sym_data_type_name_token5,
      aux_sym_data_type_name_token6,
      aux_sym_data_type_name_token7,
      aux_sym_data_type_name_token8,
      aux_sym_data_type_name_token9,
      aux_sym_data_type_name_token10,
      aux_sym_data_type_name_token11,
      aux_sym_data_type_name_token12,
      aux_sym_data_type_name_token13,
      aux_sym_data_type_name_token14,
      aux_sym_data_type_name_token15,
      aux_sym_data_type_name_token16,
      aux_sym_data_type_name_token17,
      aux_sym_data_type_name_token18,
      aux_sym_data_type_name_token19,
      aux_sym_data_type_name_token20,
      aux_sym_data_type_name_token21,
      sym_object_name,
  [2600] = 3,
    STATE(74), 1,
      sym_data_type_name,
    STATE(804), 1,
      sym_data_type,
    ACTIONS(156), 26,
      aux_sym_begin_batch_token4,
      aux_sym_using_timestamp_spec_token2,
      aux_sym_update_assignments_token1,
      aux_sym_list_roles_token1,
      aux_sym_data_type_name_token1,
      aux_sym_data_type_name_token2,
      aux_sym_data_type_name_token3,
      aux_sym_data_type_name_token4,
      aux_sym_data_type_name_token5,
      aux_sym_data_type_name_token6,
      aux_sym_data_type_name_token7,
      aux_sym_data_type_name_token8,
      aux_sym_data_type_name_token9,
      aux_sym_data_type_name_token10,
      aux_sym_data_type_name_token11,
      aux_sym_data_type_name_token12,
      aux_sym_data_type_name_token13,
      aux_sym_data_type_name_token14,
      aux_sym_data_type_name_token15,
      aux_sym_data_type_name_token16,
      aux_sym_data_type_name_token17,
      aux_sym_data_type_name_token18,
      aux_sym_data_type_name_token19,
      aux_sym_data_type_name_token20,
      aux_sym_data_type_name_token21,
      sym_object_name,
  [2635] = 3,
    STATE(74), 1,
      sym_data_type_name,
    STATE(851), 1,
      sym_data_type,
    ACTIONS(156), 26,
      aux_sym_begin_batch_token4,
      aux_sym_using_timestamp_spec_token2,
      aux_sym_update_assignments_token1,
      aux_sym_list_roles_token1,
      aux_sym_data_type_name_token1,
      aux_sym_data_type_name_token2,
      aux_sym_data_type_name_token3,
      aux_sym_data_type_name_token4,
      aux_sym_data_type_name_token5,
      aux_sym_data_type_name_token6,
      aux_sym_data_type_name_token7,
      aux_sym_data_type_name_token8,
      aux_sym_data_type_name_token9,
      aux_sym_data_type_name_token10,
      aux_sym_data_type_name_token11,
      aux_sym_data_type_name_token12,
      aux_sym_data_type_name_token13,
      aux_sym_data_type_name_token14,
      aux_sym_data_type_name_token15,
      aux_sym_data_type_name_token16,
      aux_sym_data_type_name_token17,
      aux_sym_data_type_name_token18,
      aux_sym_data_type_name_token19,
      aux_sym_data_type_name_token20,
      aux_sym_data_type_name_token21,
      sym_object_name,
  [2670] = 3,
    STATE(74), 1,
      sym_data_type_name,
    STATE(775), 1,
      sym_data_type,
    ACTIONS(156), 26,
      aux_sym_begin_batch_token4,
      aux_sym_using_timestamp_spec_token2,
      aux_sym_update_assignments_token1,
      aux_sym_list_roles_token1,
      aux_sym_data_type_name_token1,
      aux_sym_data_type_name_token2,
      aux_sym_data_type_name_token3,
      aux_sym_data_type_name_token4,
      aux_sym_data_type_name_token5,
      aux_sym_data_type_name_token6,
      aux_sym_data_type_name_token7,
      aux_sym_data_type_name_token8,
      aux_sym_data_type_name_token9,
      aux_sym_data_type_name_token10,
      aux_sym_data_type_name_token11,
      aux_sym_data_type_name_token12,
      aux_sym_data_type_name_token13,
      aux_sym_data_type_name_token14,
      aux_sym_data_type_name_token15,
      aux_sym_data_type_name_token16,
      aux_sym_data_type_name_token17,
      aux_sym_data_type_name_token18,
      aux_sym_data_type_name_token19,
      aux_sym_data_type_name_token20,
      aux_sym_data_type_name_token21,
      sym_object_name,
  [2705] = 3,
    STATE(74), 1,
      sym_data_type_name,
    STATE(923), 1,
      sym_data_type,
    ACTIONS(156), 26,
      aux_sym_begin_batch_token4,
      aux_sym_using_timestamp_spec_token2,
      aux_sym_update_assignments_token1,
      aux_sym_list_roles_token1,
      aux_sym_data_type_name_token1,
      aux_sym_data_type_name_token2,
      aux_sym_data_type_name_token3,
      aux_sym_data_type_name_token4,
      aux_sym_data_type_name_token5,
      aux_sym_data_type_name_token6,
      aux_sym_data_type_name_token7,
      aux_sym_data_type_name_token8,
      aux_sym_data_type_name_token9,
      aux_sym_data_type_name_token10,
      aux_sym_data_type_name_token11,
      aux_sym_data_type_name_token12,
      aux_sym_data_type_name_token13,
      aux_sym_data_type_name_token14,
      aux_sym_data_type_name_token15,
      aux_sym_data_type_name_token16,
      aux_sym_data_type_name_token17,
      aux_sym_data_type_name_token18,
      aux_sym_data_type_name_token19,
      aux_sym_data_type_name_token20,
      aux_sym_data_type_name_token21,
      sym_object_name,
  [2740] = 2,
    STATE(716), 1,
      sym_data_type_name,
    ACTIONS(156), 26,
      aux_sym_begin_batch_token4,
      aux_sym_using_timestamp_spec_token2,
      aux_sym_update_assignments_token1,
      aux_sym_list_roles_token1,
      aux_sym_data_type_name_token1,
      aux_sym_data_type_name_token2,
      aux_sym_data_type_name_token3,
      aux_sym_data_type_name_token4,
      aux_sym_data_type_name_token5,
      aux_sym_data_type_name_token6,
      aux_sym_data_type_name_token7,
      aux_sym_data_type_name_token8,
      aux_sym_data_type_name_token9,
      aux_sym_data_type_name_token10,
      aux_sym_data_type_name_token11,
      aux_sym_data_type_name_token12,
      aux_sym_data_type_name_token13,
      aux_sym_data_type_name_token14,
      aux_sym_data_type_name_token15,
      aux_sym_data_type_name_token16,
      aux_sym_data_type_name_token17,
      aux_sym_data_type_name_token18,
      aux_sym_data_type_name_token19,
      aux_sym_data_type_name_token20,
      aux_sym_data_type_name_token21,
      sym_object_name,
  [2772] = 2,
    STATE(591), 1,
      sym_data_type_name,
    ACTIONS(156), 26,
      aux_sym_begin_batch_token4,
      aux_sym_using_timestamp_spec_token2,
      aux_sym_update_assignments_token1,
      aux_sym_list_roles_token1,
      aux_sym_data_type_name_token1,
      aux_sym_data_type_name_token2,
      aux_sym_data_type_name_token3,
      aux_sym_data_type_name_token4,
      aux_sym_data_type_name_token5,
      aux_sym_data_type_name_token6,
      aux_sym_data_type_name_token7,
      aux_sym_data_type_name_token8,
      aux_sym_data_type_name_token9,
      aux_sym_data_type_name_token10,
      aux_sym_data_type_name_token11,
      aux_sym_data_type_name_token12,
      aux_sym_data_type_name_token13,
      aux_sym_data_type_name_token14,
      aux_sym_data_type_name_token15,
      aux_sym_data_type_name_token16,
      aux_sym_data_type_name_token17,
      aux_sym_data_type_name_token18,
      aux_sym_data_type_name_token19,
      aux_sym_data_type_name_token20,
      aux_sym_data_type_name_token21,
      sym_object_name,
  [2804] = 18,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    ACTIONS(95), 1,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(97), 1,
      anon_sym_DASH,
    ACTIONS(103), 1,
      sym_uuid_literal,
    ACTIONS(144), 1,
      anon_sym_LBRACE,
    ACTIONS(146), 1,
      anon_sym_LBRACK,
    ACTIONS(158), 1,
      sym_object_name,
    STATE(5), 1,
      aux_sym_integer_repeat1,
    STATE(10), 1,
      sym_integer,
    STATE(416), 1,
      sym_single_quote,
    STATE(655), 1,
      sym_constant,
    ACTIONS(99), 2,
      sym_nan,
      sym_infinity,
    ACTIONS(101), 2,
      sym_true_literal,
      sym_false_literal,
    ACTIONS(105), 2,
      sym_blob_literal,
      sym_null_literal,
    STATE(34), 2,
      sym_standard_decimal_notation,
      sym_scientific_notation,
    STATE(31), 3,
      sym_string_literal,
      sym_float_literal,
      sym_boolean_literal,
    STATE(521), 3,
      sym_map_literal,
      sym_set_literal,
      sym_list_literal,
  [2867] = 16,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    ACTIONS(95), 1,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(97), 1,
      anon_sym_DASH,
    ACTIONS(103), 1,
      sym_uuid_literal,
    ACTIONS(160), 1,
      anon_sym_LPAREN,
    STATE(5), 1,
      aux_sym_integer_repeat1,
    STATE(10), 1,
      sym_integer,
    STATE(416), 1,
      sym_single_quote,
    STATE(634), 1,
      sym_init_cond_definition,
    ACTIONS(99), 2,
      sym_nan,
      sym_infinity,
    ACTIONS(101), 2,
      sym_true_literal,
      sym_false_literal,
    ACTIONS(105), 2,
      sym_blob_literal,
      sym_null_literal,
    STATE(34), 2,
      sym_standard_decimal_notation,
      sym_scientific_notation,
    STATE(31), 3,
      sym_string_literal,
      sym_float_literal,
      sym_boolean_literal,
    STATE(181), 4,
      sym_constant,
      sym_init_cond_list,
      sym_init_cond_nested_list,
      sym_init_cond_hash,
  [2925] = 16,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    ACTIONS(95), 1,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(97), 1,
      anon_sym_DASH,
    ACTIONS(103), 1,
      sym_uuid_literal,
    ACTIONS(160), 1,
      anon_sym_LPAREN,
    STATE(5), 1,
      aux_sym_integer_repeat1,
    STATE(10), 1,
      sym_integer,
    STATE(289), 1,
      sym_init_cond_definition,
    STATE(416), 1,
      sym_single_quote,
    ACTIONS(99), 2,
      sym_nan,
      sym_infinity,
    ACTIONS(101), 2,
      sym_true_literal,
      sym_false_literal,
    ACTIONS(105), 2,
      sym_blob_literal,
      sym_null_literal,
    STATE(34), 2,
      sym_standard_decimal_notation,
      sym_scientific_notation,
    STATE(31), 3,
      sym_string_literal,
      sym_float_literal,
      sym_boolean_literal,
    STATE(181), 4,
      sym_constant,
      sym_init_cond_list,
      sym_init_cond_nested_list,
      sym_init_cond_hash,
  [2983] = 16,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    ACTIONS(95), 1,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(97), 1,
      anon_sym_DASH,
    ACTIONS(103), 1,
      sym_uuid_literal,
    ACTIONS(160), 1,
      anon_sym_LPAREN,
    STATE(5), 1,
      aux_sym_integer_repeat1,
    STATE(10), 1,
      sym_integer,
    STATE(300), 1,
      sym_init_cond_definition,
    STATE(416), 1,
      sym_single_quote,
    ACTIONS(99), 2,
      sym_nan,
      sym_infinity,
    ACTIONS(101), 2,
      sym_true_literal,
      sym_false_literal,
    ACTIONS(105), 2,
      sym_blob_literal,
      sym_null_literal,
    STATE(34), 2,
      sym_standard_decimal_notation,
      sym_scientific_notation,
    STATE(31), 3,
      sym_string_literal,
      sym_float_literal,
      sym_boolean_literal,
    STATE(181), 4,
      sym_constant,
      sym_init_cond_list,
      sym_init_cond_nested_list,
      sym_init_cond_hash,
  [3041] = 16,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    ACTIONS(95), 1,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(97), 1,
      anon_sym_DASH,
    ACTIONS(103), 1,
      sym_uuid_literal,
    ACTIONS(160), 1,
      anon_sym_LPAREN,
    STATE(5), 1,
      aux_sym_integer_repeat1,
    STATE(10), 1,
      sym_integer,
    STATE(306), 1,
      sym_init_cond_definition,
    STATE(416), 1,
      sym_single_quote,
    ACTIONS(99), 2,
      sym_nan,
      sym_infinity,
    ACTIONS(101), 2,
      sym_true_literal,
      sym_false_literal,
    ACTIONS(105), 2,
      sym_blob_literal,
      sym_null_literal,
    STATE(34), 2,
      sym_standard_decimal_notation,
      sym_scientific_notation,
    STATE(31), 3,
      sym_string_literal,
      sym_float_literal,
      sym_boolean_literal,
    STATE(181), 4,
      sym_constant,
      sym_init_cond_list,
      sym_init_cond_nested_list,
      sym_init_cond_hash,
  [3099] = 3,
    ACTIONS(164), 1,
      anon_sym_COMMA,
    STATE(63), 1,
      aux_sym_relation_element_repeat2,
    ACTIONS(162), 23,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      aux_sym_select_statement_token1,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_relation_elements_token1,
      aux_sym_order_spec_token1,
      aux_sym_delete_statement_token1,
      aux_sym_delete_statement_token2,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_primary_key_column_token1,
      aux_sym_apply_batch_token1,
  [3131] = 16,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    ACTIONS(95), 1,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(97), 1,
      anon_sym_DASH,
    ACTIONS(103), 1,
      sym_uuid_literal,
    ACTIONS(160), 1,
      anon_sym_LPAREN,
    STATE(5), 1,
      aux_sym_integer_repeat1,
    STATE(10), 1,
      sym_integer,
    STATE(264), 1,
      sym_init_cond_definition,
    STATE(416), 1,
      sym_single_quote,
    ACTIONS(99), 2,
      sym_nan,
      sym_infinity,
    ACTIONS(101), 2,
      sym_true_literal,
      sym_false_literal,
    ACTIONS(105), 2,
      sym_blob_literal,
      sym_null_literal,
    STATE(34), 2,
      sym_standard_decimal_notation,
      sym_scientific_notation,
    STATE(31), 3,
      sym_string_literal,
      sym_float_literal,
      sym_boolean_literal,
    STATE(181), 4,
      sym_constant,
      sym_init_cond_list,
      sym_init_cond_nested_list,
      sym_init_cond_hash,
  [3189] = 16,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    ACTIONS(95), 1,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(97), 1,
      anon_sym_DASH,
    ACTIONS(103), 1,
      sym_uuid_literal,
    ACTIONS(107), 1,
      anon_sym_QMARK,
    ACTIONS(109), 1,
      anon_sym_COLON,
    STATE(5), 1,
      aux_sym_integer_repeat1,
    STATE(10), 1,
      sym_integer,
    STATE(416), 1,
      sym_single_quote,
    ACTIONS(99), 2,
      sym_nan,
      sym_infinity,
    ACTIONS(101), 2,
      sym_true_literal,
      sym_false_literal,
    ACTIONS(105), 2,
      sym_blob_literal,
      sym_null_literal,
    STATE(34), 2,
      sym_standard_decimal_notation,
      sym_scientific_notation,
    STATE(31), 3,
      sym_string_literal,
      sym_float_literal,
      sym_boolean_literal,
    STATE(88), 3,
      sym_constant,
      sym_bind_marker,
      sym__value_marker,
  [3246] = 3,
    ACTIONS(169), 1,
      anon_sym_COMMA,
    STATE(68), 1,
      aux_sym_relation_element_repeat2,
    ACTIONS(167), 22,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_relation_elements_token1,
      aux_sym_order_spec_token1,
      aux_sym_delete_statement_token1,
      aux_sym_delete_statement_token2,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_primary_key_column_token1,
      aux_sym_apply_batch_token1,
  [3277] = 18,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    ACTIONS(95), 1,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(97), 1,
      anon_sym_DASH,
    ACTIONS(103), 1,
      sym_uuid_literal,
    ACTIONS(171), 1,
      anon_sym_LPAREN,
    ACTIONS(173), 1,
      sym_object_name,
    STATE(5), 1,
      aux_sym_integer_repeat1,
    STATE(10), 1,
      sym_integer,
    STATE(416), 1,
      sym_single_quote,
    STATE(493), 1,
      sym_constant,
    STATE(592), 1,
      sym_init_cond_hash_item,
    STATE(606), 1,
      sym_init_cond_list,
    ACTIONS(99), 2,
      sym_nan,
      sym_infinity,
    ACTIONS(101), 2,
      sym_true_literal,
      sym_false_literal,
    ACTIONS(105), 2,
      sym_blob_literal,
      sym_null_literal,
    STATE(34), 2,
      sym_standard_decimal_notation,
      sym_scientific_notation,
    STATE(31), 3,
      sym_string_literal,
      sym_float_literal,
      sym_boolean_literal,
  [3338] = 3,
    ACTIONS(169), 1,
      anon_sym_COMMA,
    STATE(63), 1,
      aux_sym_relation_element_repeat2,
    ACTIONS(175), 22,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_relation_elements_token1,
      aux_sym_order_spec_token1,
      aux_sym_delete_statement_token1,
      aux_sym_delete_statement_token2,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_primary_key_column_token1,
      aux_sym_apply_batch_token1,
  [3369] = 3,
    ACTIONS(169), 1,
      anon_sym_COMMA,
    STATE(63), 1,
      aux_sym_relation_element_repeat2,
    ACTIONS(177), 22,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_relation_elements_token1,
      aux_sym_order_spec_token1,
      aux_sym_delete_statement_token1,
      aux_sym_delete_statement_token2,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_primary_key_column_token1,
      aux_sym_apply_batch_token1,
  [3400] = 3,
    ACTIONS(169), 1,
      anon_sym_COMMA,
    STATE(69), 1,
      aux_sym_relation_element_repeat2,
    ACTIONS(175), 22,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_relation_elements_token1,
      aux_sym_order_spec_token1,
      aux_sym_delete_statement_token1,
      aux_sym_delete_statement_token2,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_primary_key_column_token1,
      aux_sym_apply_batch_token1,
  [3431] = 1,
    ACTIONS(179), 24,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      aux_sym_select_statement_token1,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_relation_elements_token1,
      aux_sym_order_spec_token1,
      aux_sym_delete_statement_token1,
      aux_sym_delete_statement_token2,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_primary_key_column_token1,
      aux_sym_apply_batch_token1,
  [3458] = 1,
    ACTIONS(162), 24,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      aux_sym_select_statement_token1,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_relation_elements_token1,
      aux_sym_order_spec_token1,
      aux_sym_delete_statement_token1,
      aux_sym_delete_statement_token2,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_primary_key_column_token1,
      aux_sym_apply_batch_token1,
  [3485] = 3,
    ACTIONS(183), 1,
      aux_sym_relation_elements_token1,
    STATE(73), 1,
      aux_sym_relation_elements_repeat1,
    ACTIONS(181), 21,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_order_spec_token1,
      aux_sym_delete_statement_token1,
      aux_sym_delete_statement_token2,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_primary_key_column_token1,
      aux_sym_apply_batch_token1,
  [3515] = 3,
    ACTIONS(188), 1,
      anon_sym_LT,
    STATE(91), 1,
      sym_data_type_definition,
    ACTIONS(186), 21,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_create_aggregate_token5,
      aux_sym_create_function_token2,
      aux_sym_primary_key_column_token1,
      aux_sym_apply_batch_token1,
  [3545] = 1,
    ACTIONS(190), 23,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      anon_sym_LT,
      anon_sym_GT,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_create_aggregate_token5,
      aux_sym_create_function_token2,
      aux_sym_primary_key_column_token1,
      aux_sym_apply_batch_token1,
  [3571] = 1,
    ACTIONS(192), 22,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_relation_elements_token1,
      aux_sym_order_spec_token1,
      aux_sym_delete_statement_token1,
      aux_sym_delete_statement_token2,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_primary_key_column_token1,
      aux_sym_apply_batch_token1,
  [3596] = 1,
    ACTIONS(194), 22,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_relation_elements_token1,
      aux_sym_order_spec_token1,
      aux_sym_delete_statement_token1,
      aux_sym_delete_statement_token2,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_primary_key_column_token1,
      aux_sym_apply_batch_token1,
  [3621] = 1,
    ACTIONS(177), 22,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_relation_elements_token1,
      aux_sym_order_spec_token1,
      aux_sym_delete_statement_token1,
      aux_sym_delete_statement_token2,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_primary_key_column_token1,
      aux_sym_apply_batch_token1,
  [3646] = 1,
    ACTIONS(196), 22,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_relation_elements_token1,
      aux_sym_order_spec_token1,
      aux_sym_delete_statement_token1,
      aux_sym_delete_statement_token2,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_primary_key_column_token1,
      aux_sym_apply_batch_token1,
  [3671] = 15,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    ACTIONS(95), 1,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(97), 1,
      anon_sym_DASH,
    ACTIONS(103), 1,
      sym_uuid_literal,
    ACTIONS(171), 1,
      anon_sym_LPAREN,
    STATE(5), 1,
      aux_sym_integer_repeat1,
    STATE(10), 1,
      sym_integer,
    STATE(416), 1,
      sym_single_quote,
    ACTIONS(99), 2,
      sym_nan,
      sym_infinity,
    ACTIONS(101), 2,
      sym_true_literal,
      sym_false_literal,
    ACTIONS(105), 2,
      sym_blob_literal,
      sym_null_literal,
    STATE(34), 2,
      sym_standard_decimal_notation,
      sym_scientific_notation,
    STATE(631), 2,
      sym_constant,
      sym_init_cond_list,
    STATE(31), 3,
      sym_string_literal,
      sym_float_literal,
      sym_boolean_literal,
  [3724] = 3,
    ACTIONS(200), 1,
      aux_sym_relation_elements_token1,
    STATE(85), 1,
      aux_sym_relation_elements_repeat1,
    ACTIONS(198), 20,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_order_spec_token1,
      aux_sym_delete_statement_token1,
      aux_sym_delete_statement_token2,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [3753] = 2,
    ACTIONS(204), 1,
      anon_sym_DQUOTE,
    ACTIONS(202), 21,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_LPAREN,
      aux_sym_from_spec_token1,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_create_aggregate_token4,
      aux_sym_create_aggregate_token6,
      aux_sym_apply_batch_token1,
  [3780] = 1,
    ACTIONS(181), 22,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_relation_elements_token1,
      aux_sym_order_spec_token1,
      aux_sym_delete_statement_token1,
      aux_sym_delete_statement_token2,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_primary_key_column_token1,
      aux_sym_apply_batch_token1,
  [3805] = 1,
    ACTIONS(206), 22,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_relation_elements_token1,
      aux_sym_order_spec_token1,
      aux_sym_delete_statement_token1,
      aux_sym_delete_statement_token2,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_primary_key_column_token1,
      aux_sym_apply_batch_token1,
  [3830] = 3,
    ACTIONS(200), 1,
      aux_sym_relation_elements_token1,
    STATE(73), 1,
      aux_sym_relation_elements_repeat1,
    ACTIONS(208), 20,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_order_spec_token1,
      aux_sym_delete_statement_token1,
      aux_sym_delete_statement_token2,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [3859] = 1,
    ACTIONS(210), 22,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_relation_elements_token1,
      aux_sym_order_spec_token1,
      aux_sym_delete_statement_token1,
      aux_sym_delete_statement_token2,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_primary_key_column_token1,
      aux_sym_apply_batch_token1,
  [3884] = 1,
    ACTIONS(212), 22,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_DQUOTE,
      anon_sym_LPAREN,
      aux_sym_from_spec_token1,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_create_aggregate_token4,
      aux_sym_create_aggregate_token6,
      aux_sym_apply_batch_token1,
  [3909] = 1,
    ACTIONS(214), 22,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_relation_elements_token1,
      aux_sym_order_spec_token1,
      aux_sym_delete_statement_token1,
      aux_sym_delete_statement_token2,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_primary_key_column_token1,
      aux_sym_apply_batch_token1,
  [3934] = 1,
    ACTIONS(216), 22,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_relation_elements_token1,
      aux_sym_order_spec_token1,
      aux_sym_delete_statement_token1,
      aux_sym_delete_statement_token2,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_primary_key_column_token1,
      aux_sym_apply_batch_token1,
  [3959] = 1,
    ACTIONS(218), 22,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_relation_elements_token1,
      aux_sym_order_spec_token1,
      aux_sym_delete_statement_token1,
      aux_sym_delete_statement_token2,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_primary_key_column_token1,
      aux_sym_apply_batch_token1,
  [3984] = 1,
    ACTIONS(220), 21,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_create_aggregate_token5,
      aux_sym_create_function_token2,
      aux_sym_primary_key_column_token1,
      aux_sym_apply_batch_token1,
  [4008] = 1,
    ACTIONS(222), 21,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_create_aggregate_token5,
      aux_sym_create_function_token2,
      aux_sym_primary_key_column_token1,
      aux_sym_apply_batch_token1,
  [4032] = 15,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    ACTIONS(95), 1,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(97), 1,
      anon_sym_DASH,
    ACTIONS(103), 1,
      sym_uuid_literal,
    ACTIONS(224), 1,
      aux_sym_relation_contains_key_token2,
    STATE(5), 1,
      aux_sym_integer_repeat1,
    STATE(10), 1,
      sym_integer,
    STATE(86), 1,
      sym_constant,
    STATE(416), 1,
      sym_single_quote,
    ACTIONS(99), 2,
      sym_nan,
      sym_infinity,
    ACTIONS(101), 2,
      sym_true_literal,
      sym_false_literal,
    ACTIONS(105), 2,
      sym_blob_literal,
      sym_null_literal,
    STATE(34), 2,
      sym_standard_decimal_notation,
      sym_scientific_notation,
    STATE(31), 3,
      sym_string_literal,
      sym_float_literal,
      sym_boolean_literal,
  [4084] = 1,
    ACTIONS(226), 21,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_LPAREN,
      aux_sym_from_spec_token1,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_create_aggregate_token4,
      aux_sym_create_aggregate_token6,
      aux_sym_apply_batch_token1,
  [4108] = 1,
    ACTIONS(228), 21,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_create_aggregate_token5,
      aux_sym_create_function_token2,
      aux_sym_primary_key_column_token1,
      aux_sym_apply_batch_token1,
  [4132] = 4,
    ACTIONS(232), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(107), 1,
      aux_sym_unquoted_identifier_repeat1,
    ACTIONS(234), 2,
      anon_sym__,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(230), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [4161] = 2,
    ACTIONS(238), 1,
      anon_sym_DOT,
    ACTIONS(236), 19,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_from_spec_token1,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_grant_token2,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_list_roles_token2,
      aux_sym_apply_batch_token1,
  [4186] = 4,
    ACTIONS(242), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(110), 1,
      aux_sym_unquoted_identifier_repeat1,
    ACTIONS(244), 2,
      anon_sym__,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(240), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [4215] = 2,
    ACTIONS(248), 1,
      anon_sym_DOT,
    ACTIONS(246), 19,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_LPAREN,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_alter_table_add_token1,
      aux_sym_alter_table_rename_token1,
      aux_sym_apply_batch_token1,
  [4240] = 4,
    ACTIONS(252), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(100), 1,
      aux_sym_unquoted_identifier_repeat1,
    ACTIONS(255), 2,
      anon_sym__,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(250), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [4269] = 14,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    ACTIONS(95), 1,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(97), 1,
      anon_sym_DASH,
    ACTIONS(103), 1,
      sym_uuid_literal,
    STATE(5), 1,
      aux_sym_integer_repeat1,
    STATE(10), 1,
      sym_integer,
    STATE(416), 1,
      sym_single_quote,
    STATE(493), 1,
      sym_constant,
    ACTIONS(99), 2,
      sym_nan,
      sym_infinity,
    ACTIONS(101), 2,
      sym_true_literal,
      sym_false_literal,
    ACTIONS(105), 2,
      sym_blob_literal,
      sym_null_literal,
    STATE(34), 2,
      sym_standard_decimal_notation,
      sym_scientific_notation,
    STATE(31), 3,
      sym_string_literal,
      sym_float_literal,
      sym_boolean_literal,
  [4318] = 14,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    ACTIONS(95), 1,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(97), 1,
      anon_sym_DASH,
    ACTIONS(103), 1,
      sym_uuid_literal,
    STATE(5), 1,
      aux_sym_integer_repeat1,
    STATE(10), 1,
      sym_integer,
    STATE(416), 1,
      sym_single_quote,
    STATE(655), 1,
      sym_constant,
    ACTIONS(99), 2,
      sym_nan,
      sym_infinity,
    ACTIONS(101), 2,
      sym_true_literal,
      sym_false_literal,
    ACTIONS(105), 2,
      sym_blob_literal,
      sym_null_literal,
    STATE(34), 2,
      sym_standard_decimal_notation,
      sym_scientific_notation,
    STATE(31), 3,
      sym_string_literal,
      sym_float_literal,
      sym_boolean_literal,
  [4367] = 2,
    ACTIONS(260), 1,
      anon_sym_DOT,
    ACTIONS(258), 19,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_from_spec_token1,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_grant_token2,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_list_roles_token2,
      aux_sym_apply_batch_token1,
  [4392] = 14,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    ACTIONS(95), 1,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(97), 1,
      anon_sym_DASH,
    ACTIONS(103), 1,
      sym_uuid_literal,
    STATE(5), 1,
      aux_sym_integer_repeat1,
    STATE(10), 1,
      sym_integer,
    STATE(416), 1,
      sym_single_quote,
    STATE(632), 1,
      sym_constant,
    ACTIONS(99), 2,
      sym_nan,
      sym_infinity,
    ACTIONS(101), 2,
      sym_true_literal,
      sym_false_literal,
    ACTIONS(105), 2,
      sym_blob_literal,
      sym_null_literal,
    STATE(34), 2,
      sym_standard_decimal_notation,
      sym_scientific_notation,
    STATE(31), 3,
      sym_string_literal,
      sym_float_literal,
      sym_boolean_literal,
  [4441] = 1,
    ACTIONS(262), 20,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_order_spec_token1,
      aux_sym_delete_statement_token1,
      aux_sym_delete_statement_token2,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [4464] = 14,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    ACTIONS(95), 1,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(97), 1,
      anon_sym_DASH,
    ACTIONS(103), 1,
      sym_uuid_literal,
    STATE(5), 1,
      aux_sym_integer_repeat1,
    STATE(10), 1,
      sym_integer,
    STATE(76), 1,
      sym_constant,
    STATE(416), 1,
      sym_single_quote,
    ACTIONS(99), 2,
      sym_nan,
      sym_infinity,
    ACTIONS(101), 2,
      sym_true_literal,
      sym_false_literal,
    ACTIONS(105), 2,
      sym_blob_literal,
      sym_null_literal,
    STATE(34), 2,
      sym_standard_decimal_notation,
      sym_scientific_notation,
    STATE(31), 3,
      sym_string_literal,
      sym_float_literal,
      sym_boolean_literal,
  [4513] = 4,
    ACTIONS(266), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(100), 1,
      aux_sym_unquoted_identifier_repeat1,
    ACTIONS(268), 2,
      anon_sym__,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(264), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [4542] = 2,
    ACTIONS(272), 1,
      aux_sym_relation_element_token1,
    ACTIONS(270), 19,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_from_spec_token1,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_grant_token2,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_list_roles_token2,
      aux_sym_apply_batch_token1,
  [4567] = 2,
    ACTIONS(276), 1,
      anon_sym_DOT,
    ACTIONS(274), 19,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_from_spec_token1,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_grant_token2,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_list_roles_token2,
      aux_sym_apply_batch_token1,
  [4592] = 4,
    ACTIONS(266), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(100), 1,
      aux_sym_unquoted_identifier_repeat1,
    ACTIONS(268), 2,
      anon_sym__,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(278), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [4621] = 14,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    ACTIONS(95), 1,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(97), 1,
      anon_sym_DASH,
    ACTIONS(103), 1,
      sym_uuid_literal,
    STATE(5), 1,
      aux_sym_integer_repeat1,
    STATE(10), 1,
      sym_integer,
    STATE(171), 1,
      sym_constant,
    STATE(416), 1,
      sym_single_quote,
    ACTIONS(99), 2,
      sym_nan,
      sym_infinity,
    ACTIONS(101), 2,
      sym_true_literal,
      sym_false_literal,
    ACTIONS(105), 2,
      sym_blob_literal,
      sym_null_literal,
    STATE(34), 2,
      sym_standard_decimal_notation,
      sym_scientific_notation,
    STATE(31), 3,
      sym_string_literal,
      sym_float_literal,
      sym_boolean_literal,
  [4670] = 1,
    ACTIONS(280), 19,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_from_spec_token1,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_grant_token2,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_list_roles_token2,
      aux_sym_apply_batch_token1,
  [4692] = 4,
    ACTIONS(284), 1,
      aux_sym_delete_statement_token2,
    ACTIONS(286), 1,
      aux_sym_using_timestamp_spec_token1,
    STATE(245), 1,
      sym_using_ttl_timestamp,
    ACTIONS(282), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [4720] = 1,
    ACTIONS(288), 19,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_from_spec_token1,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_grant_token2,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_list_roles_token2,
      aux_sym_apply_batch_token1,
  [4742] = 1,
    ACTIONS(270), 19,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_from_spec_token1,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_grant_token2,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_list_roles_token2,
      aux_sym_apply_batch_token1,
  [4764] = 4,
    ACTIONS(286), 1,
      aux_sym_using_timestamp_spec_token1,
    ACTIONS(292), 1,
      aux_sym_delete_statement_token2,
    STATE(235), 1,
      sym_using_ttl_timestamp,
    ACTIONS(290), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [4792] = 3,
    ACTIONS(296), 1,
      anon_sym_COMMA,
    STATE(117), 1,
      aux_sym_create_function_repeat1,
    ACTIONS(294), 17,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [4818] = 2,
    ACTIONS(301), 1,
      anon_sym_DOT,
    ACTIONS(299), 18,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_create_materialized_view_token1,
      aux_sym_create_keyspace_token1,
      aux_sym_apply_batch_token1,
  [4842] = 1,
    ACTIONS(303), 19,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_from_spec_token1,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_grant_token2,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_list_roles_token2,
      aux_sym_apply_batch_token1,
  [4864] = 3,
    ACTIONS(307), 1,
      anon_sym_COMMA,
    STATE(120), 1,
      aux_sym_clustering_key_list_repeat1,
    ACTIONS(305), 17,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [4890] = 1,
    ACTIONS(310), 19,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_LPAREN,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_create_aggregate_token4,
      aux_sym_create_aggregate_token6,
      aux_sym_apply_batch_token1,
  [4912] = 2,
    ACTIONS(314), 1,
      aux_sym_privilege_token2,
    ACTIONS(312), 18,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_create_index_token3,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_list_roles_token2,
      aux_sym_apply_batch_token1,
  [4936] = 1,
    ACTIONS(316), 19,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_from_spec_token1,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_grant_token2,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_list_roles_token2,
      aux_sym_apply_batch_token1,
  [4958] = 1,
    ACTIONS(318), 19,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_from_spec_token1,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_grant_token2,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_list_roles_token2,
      aux_sym_apply_batch_token1,
  [4980] = 3,
    STATE(212), 1,
      sym_user_super_user,
    ACTIONS(322), 2,
      aux_sym_role_with_option_token3,
      aux_sym_user_super_user_token1,
    ACTIONS(320), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [5006] = 1,
    ACTIONS(324), 19,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_LPAREN,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_alter_table_add_token1,
      aux_sym_alter_table_rename_token1,
      aux_sym_apply_batch_token1,
  [5028] = 1,
    ACTIONS(326), 19,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_from_spec_token1,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_grant_token2,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_list_roles_token2,
      aux_sym_apply_batch_token1,
  [5050] = 3,
    ACTIONS(330), 1,
      aux_sym_create_keyspace_token1,
    STATE(218), 1,
      sym_with_element,
    ACTIONS(328), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [5075] = 3,
    ACTIONS(334), 1,
      aux_sym_relation_elements_token1,
    STATE(129), 1,
      aux_sym_role_with_repeat1,
    ACTIONS(332), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [5100] = 2,
    ACTIONS(339), 1,
      aux_sym_relation_elements_token1,
    ACTIONS(337), 17,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_update_assignments_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [5123] = 3,
    ACTIONS(330), 1,
      aux_sym_create_keyspace_token1,
    STATE(229), 1,
      sym_with_element,
    ACTIONS(341), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [5148] = 3,
    ACTIONS(345), 1,
      aux_sym_create_keyspace_token1,
    STATE(241), 1,
      sym_role_with,
    ACTIONS(343), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [5173] = 1,
    ACTIONS(347), 18,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_create_keyspace_token1,
      aux_sym_apply_batch_token1,
  [5194] = 2,
    ACTIONS(351), 1,
      anon_sym_DOT,
    ACTIONS(349), 17,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_LPAREN,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [5217] = 1,
    ACTIONS(353), 18,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [5238] = 1,
    ACTIONS(294), 18,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [5259] = 3,
    ACTIONS(357), 1,
      aux_sym_delete_statement_token2,
    STATE(223), 1,
      sym_if_spec,
    ACTIONS(355), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [5284] = 1,
    ACTIONS(359), 18,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [5305] = 1,
    ACTIONS(305), 18,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [5326] = 1,
    ACTIONS(361), 18,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [5347] = 1,
    ACTIONS(363), 18,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [5368] = 1,
    ACTIONS(365), 18,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [5389] = 3,
    ACTIONS(369), 1,
      aux_sym_delete_statement_token2,
    STATE(219), 1,
      sym_if_spec,
    ACTIONS(367), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [5414] = 3,
    ACTIONS(373), 1,
      aux_sym_delete_statement_token2,
    STATE(234), 1,
      sym_if_spec,
    ACTIONS(371), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [5439] = 3,
    ACTIONS(377), 1,
      aux_sym_relation_elements_token1,
    STATE(168), 1,
      aux_sym_alter_type_rename_repeat1,
    ACTIONS(375), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [5464] = 3,
    ACTIONS(330), 1,
      aux_sym_create_keyspace_token1,
    STATE(288), 1,
      sym_with_element,
    ACTIONS(379), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [5489] = 1,
    ACTIONS(381), 18,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [5510] = 3,
    ACTIONS(385), 1,
      aux_sym_relation_elements_token1,
    STATE(178), 1,
      aux_sym_role_with_repeat1,
    ACTIONS(383), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [5535] = 3,
    ACTIONS(389), 1,
      anon_sym_COMMA,
    STATE(162), 1,
      aux_sym_clustering_key_list_repeat1,
    ACTIONS(387), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [5560] = 3,
    ACTIONS(393), 1,
      aux_sym_relation_elements_token1,
    STATE(161), 1,
      aux_sym_table_options_repeat1,
    ACTIONS(391), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [5585] = 3,
    ACTIONS(397), 1,
      anon_sym_COMMA,
    STATE(159), 1,
      aux_sym_create_function_repeat1,
    ACTIONS(395), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [5610] = 3,
    ACTIONS(397), 1,
      anon_sym_COMMA,
    STATE(155), 1,
      aux_sym_create_function_repeat1,
    ACTIONS(399), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [5635] = 3,
    ACTIONS(403), 1,
      aux_sym_relation_elements_token1,
    STATE(153), 1,
      aux_sym_table_options_repeat1,
    ACTIONS(401), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [5660] = 3,
    ACTIONS(408), 1,
      aux_sym_delete_statement_token2,
    STATE(222), 1,
      sym_if_spec,
    ACTIONS(406), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [5685] = 3,
    ACTIONS(397), 1,
      anon_sym_COMMA,
    STATE(117), 1,
      aux_sym_create_function_repeat1,
    ACTIONS(410), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [5710] = 3,
    ACTIONS(377), 1,
      aux_sym_relation_elements_token1,
    STATE(145), 1,
      aux_sym_alter_type_rename_repeat1,
    ACTIONS(412), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [5735] = 3,
    ACTIONS(416), 1,
      aux_sym_delete_statement_token2,
    STATE(314), 1,
      sym_if_spec,
    ACTIONS(414), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [5760] = 1,
    ACTIONS(418), 18,
      ts_builtin_sym_end,
      anon_sym_DOT,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_create_keyspace_token1,
      aux_sym_apply_batch_token1,
  [5781] = 3,
    ACTIONS(397), 1,
      anon_sym_COMMA,
    STATE(117), 1,
      aux_sym_create_function_repeat1,
    ACTIONS(420), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [5806] = 3,
    ACTIONS(424), 1,
      aux_sym_delete_statement_token2,
    STATE(211), 1,
      sym_if_spec,
    ACTIONS(422), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [5831] = 3,
    ACTIONS(393), 1,
      aux_sym_relation_elements_token1,
    STATE(153), 1,
      aux_sym_table_options_repeat1,
    ACTIONS(426), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [5856] = 3,
    ACTIONS(389), 1,
      anon_sym_COMMA,
    STATE(120), 1,
      aux_sym_clustering_key_list_repeat1,
    ACTIONS(428), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [5881] = 3,
    ACTIONS(432), 1,
      aux_sym_delete_statement_token2,
    STATE(267), 1,
      sym_if_spec,
    ACTIONS(430), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [5906] = 1,
    ACTIONS(434), 18,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_create_index_token3,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_list_roles_token2,
      aux_sym_apply_batch_token1,
  [5927] = 3,
    ACTIONS(438), 1,
      aux_sym_create_index_token3,
    ACTIONS(440), 1,
      aux_sym_list_roles_token2,
    ACTIONS(436), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [5952] = 3,
    ACTIONS(286), 1,
      aux_sym_using_timestamp_spec_token1,
    STATE(262), 1,
      sym_using_ttl_timestamp,
    ACTIONS(442), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [5977] = 3,
    ACTIONS(446), 1,
      aux_sym_list_roles_token2,
    ACTIONS(448), 1,
      aux_sym_list_roles_token3,
    ACTIONS(444), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6002] = 3,
    ACTIONS(452), 1,
      aux_sym_relation_elements_token1,
    STATE(168), 1,
      aux_sym_alter_type_rename_repeat1,
    ACTIONS(450), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6027] = 3,
    ACTIONS(345), 1,
      aux_sym_create_keyspace_token1,
    STATE(285), 1,
      sym_role_with,
    ACTIONS(455), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6052] = 2,
    ACTIONS(459), 1,
      aux_sym_relation_elements_token1,
    ACTIONS(457), 17,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_update_assignments_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6075] = 1,
    ACTIONS(461), 18,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_delete_statement_token2,
      aux_sym_begin_batch_token1,
      aux_sym_using_timestamp_spec_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6096] = 1,
    ACTIONS(312), 18,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_create_index_token3,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_list_roles_token2,
      aux_sym_apply_batch_token1,
  [6117] = 3,
    ACTIONS(286), 1,
      aux_sym_using_timestamp_spec_token1,
    STATE(263), 1,
      sym_using_ttl_timestamp,
    ACTIONS(463), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6142] = 1,
    ACTIONS(465), 18,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6163] = 1,
    ACTIONS(467), 18,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_delete_statement_token2,
      aux_sym_begin_batch_token1,
      aux_sym_using_timestamp_spec_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6184] = 3,
    ACTIONS(330), 1,
      aux_sym_create_keyspace_token1,
    STATE(307), 1,
      sym_with_element,
    ACTIONS(469), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6209] = 3,
    ACTIONS(345), 1,
      aux_sym_create_keyspace_token1,
    STATE(213), 1,
      sym_role_with,
    ACTIONS(471), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6234] = 3,
    ACTIONS(385), 1,
      aux_sym_relation_elements_token1,
    STATE(129), 1,
      aux_sym_role_with_repeat1,
    ACTIONS(473), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6259] = 3,
    ACTIONS(330), 1,
      aux_sym_create_keyspace_token1,
    STATE(255), 1,
      sym_with_element,
    ACTIONS(475), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6284] = 1,
    ACTIONS(477), 18,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_role_with_option_token3,
      aux_sym_user_super_user_token1,
      aux_sym_apply_batch_token1,
  [6305] = 1,
    ACTIONS(479), 18,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6326] = 1,
    ACTIONS(481), 18,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_create_materialized_view_token1,
      aux_sym_create_keyspace_token1,
      aux_sym_apply_batch_token1,
  [6347] = 2,
    ACTIONS(485), 1,
      aux_sym_relation_elements_token1,
    ACTIONS(483), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6369] = 2,
    ACTIONS(489), 1,
      aux_sym_list_roles_token3,
    ACTIONS(487), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6391] = 2,
    ACTIONS(493), 1,
      aux_sym_list_roles_token2,
    ACTIONS(491), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6413] = 2,
    ACTIONS(497), 1,
      aux_sym_relation_elements_token1,
    ACTIONS(495), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6435] = 1,
    ACTIONS(499), 17,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_relation_elements_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6455] = 1,
    ACTIONS(501), 17,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_relation_elements_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6475] = 1,
    ACTIONS(450), 17,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_relation_elements_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6495] = 1,
    ACTIONS(503), 17,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_relation_elements_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6515] = 1,
    ACTIONS(332), 17,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_relation_elements_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6535] = 1,
    ACTIONS(505), 17,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_relation_elements_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6555] = 1,
    ACTIONS(507), 17,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_relation_elements_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6575] = 2,
    ACTIONS(511), 1,
      aux_sym_relation_elements_token1,
    ACTIONS(509), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6597] = 1,
    ACTIONS(513), 17,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_relation_elements_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6617] = 1,
    ACTIONS(515), 17,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_relation_elements_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6637] = 1,
    ACTIONS(517), 17,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_relation_elements_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6657] = 1,
    ACTIONS(519), 17,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_relation_elements_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6677] = 1,
    ACTIONS(521), 17,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_update_assignments_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6697] = 1,
    ACTIONS(523), 17,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_update_assignments_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6717] = 1,
    ACTIONS(525), 17,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_relation_elements_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6737] = 1,
    ACTIONS(527), 17,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_relation_elements_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6757] = 1,
    ACTIONS(529), 17,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_relation_elements_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6777] = 1,
    ACTIONS(401), 17,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_relation_elements_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6797] = 1,
    ACTIONS(531), 17,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_LPAREN,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6817] = 2,
    ACTIONS(535), 1,
      anon_sym_DOT,
    ACTIONS(533), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6839] = 1,
    ACTIONS(537), 17,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_create_keyspace_token1,
      aux_sym_apply_batch_token1,
  [6859] = 1,
    ACTIONS(539), 17,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_relation_elements_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6879] = 1,
    ACTIONS(541), 17,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_create_keyspace_token1,
      aux_sym_apply_batch_token1,
  [6899] = 1,
    ACTIONS(543), 17,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_relation_elements_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6919] = 1,
    ACTIONS(367), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6938] = 1,
    ACTIONS(545), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6957] = 1,
    ACTIONS(547), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6976] = 1,
    ACTIONS(549), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [6995] = 1,
    ACTIONS(551), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7014] = 1,
    ACTIONS(553), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7033] = 1,
    ACTIONS(555), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7052] = 1,
    ACTIONS(557), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7071] = 1,
    ACTIONS(559), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7090] = 1,
    ACTIONS(561), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7109] = 2,
    ACTIONS(565), 1,
      anon_sym_SEMI,
    ACTIONS(563), 15,
      ts_builtin_sym_end,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7130] = 1,
    ACTIONS(414), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7149] = 1,
    ACTIONS(567), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7168] = 1,
    ACTIONS(569), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7187] = 1,
    ACTIONS(571), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7206] = 12,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    ACTIONS(97), 1,
      anon_sym_DASH,
    ACTIONS(573), 1,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(577), 1,
      anon_sym_LBRACE,
    STATE(5), 1,
      aux_sym_integer_repeat1,
    STATE(416), 1,
      sym_single_quote,
    STATE(465), 1,
      sym_integer,
    ACTIONS(575), 2,
      sym_nan,
      sym_infinity,
    STATE(34), 2,
      sym_standard_decimal_notation,
      sym_scientific_notation,
    STATE(197), 2,
      sym_option_hash,
      sym_table_option_value,
    STATE(201), 2,
      sym_string_literal,
      sym_float_literal,
  [7247] = 1,
    ACTIONS(579), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7266] = 1,
    ACTIONS(581), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7285] = 1,
    ACTIONS(583), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7304] = 1,
    ACTIONS(585), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7323] = 1,
    ACTIONS(587), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7342] = 1,
    ACTIONS(589), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7361] = 1,
    ACTIONS(591), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7380] = 1,
    ACTIONS(355), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7399] = 1,
    ACTIONS(593), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7418] = 1,
    ACTIONS(595), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7437] = 1,
    ACTIONS(597), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7456] = 1,
    ACTIONS(599), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7475] = 1,
    ACTIONS(601), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7494] = 1,
    ACTIONS(603), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7513] = 1,
    ACTIONS(605), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7532] = 1,
    ACTIONS(607), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7551] = 1,
    ACTIONS(609), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7570] = 1,
    ACTIONS(611), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7589] = 1,
    ACTIONS(290), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7608] = 1,
    ACTIONS(613), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7627] = 1,
    ACTIONS(615), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7646] = 1,
    ACTIONS(617), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7665] = 1,
    ACTIONS(619), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7684] = 1,
    ACTIONS(621), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7703] = 1,
    ACTIONS(623), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7722] = 1,
    ACTIONS(625), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7741] = 1,
    ACTIONS(627), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7760] = 1,
    ACTIONS(629), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7779] = 1,
    ACTIONS(631), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7798] = 1,
    ACTIONS(633), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7817] = 1,
    ACTIONS(635), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7836] = 1,
    ACTIONS(637), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7855] = 1,
    ACTIONS(639), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7874] = 1,
    ACTIONS(641), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7893] = 1,
    ACTIONS(643), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7912] = 1,
    ACTIONS(645), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7931] = 1,
    ACTIONS(442), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7950] = 1,
    ACTIONS(647), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7969] = 1,
    ACTIONS(649), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [7988] = 1,
    ACTIONS(651), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8007] = 1,
    ACTIONS(371), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8026] = 1,
    ACTIONS(653), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8045] = 1,
    ACTIONS(655), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8064] = 1,
    ACTIONS(657), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8083] = 1,
    ACTIONS(659), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8102] = 1,
    ACTIONS(661), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8121] = 1,
    ACTIONS(663), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8140] = 1,
    ACTIONS(665), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8159] = 1,
    ACTIONS(667), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8178] = 1,
    ACTIONS(669), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8197] = 1,
    ACTIONS(671), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8216] = 1,
    ACTIONS(673), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8235] = 1,
    ACTIONS(675), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8254] = 1,
    ACTIONS(677), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8273] = 1,
    ACTIONS(679), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8292] = 1,
    ACTIONS(681), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8311] = 1,
    ACTIONS(683), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8330] = 1,
    ACTIONS(685), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8349] = 1,
    ACTIONS(687), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8368] = 1,
    ACTIONS(689), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8387] = 1,
    ACTIONS(691), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8406] = 1,
    ACTIONS(693), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8425] = 1,
    ACTIONS(695), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8444] = 1,
    ACTIONS(697), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8463] = 1,
    ACTIONS(699), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8482] = 1,
    ACTIONS(701), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8501] = 1,
    ACTIONS(703), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8520] = 1,
    ACTIONS(705), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8539] = 1,
    ACTIONS(707), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8558] = 1,
    ACTIONS(709), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8577] = 1,
    ACTIONS(711), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8596] = 1,
    ACTIONS(713), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8615] = 1,
    ACTIONS(715), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8634] = 1,
    ACTIONS(717), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8653] = 1,
    ACTIONS(719), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8672] = 1,
    ACTIONS(721), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8691] = 1,
    ACTIONS(723), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8710] = 1,
    ACTIONS(725), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8729] = 1,
    ACTIONS(727), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8748] = 1,
    ACTIONS(729), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8767] = 1,
    ACTIONS(731), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8786] = 1,
    ACTIONS(733), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8805] = 1,
    ACTIONS(735), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8824] = 1,
    ACTIONS(737), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8843] = 1,
    ACTIONS(739), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8862] = 1,
    ACTIONS(741), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8881] = 1,
    ACTIONS(743), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8900] = 1,
    ACTIONS(422), 16,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [8919] = 13,
    ACTIONS(93), 1,
      aux_sym_unquoted_identifier_token1,
    ACTIONS(745), 1,
      anon_sym_DQUOTE,
    ACTIONS(747), 1,
      anon_sym_LPAREN,
    ACTIONS(749), 1,
      aux_sym_delete_statement_token3,
    ACTIONS(751), 1,
      sym_object_name,
    STATE(81), 1,
      sym_relation_element,
    STATE(121), 1,
      sym_identifier,
    STATE(312), 1,
      sym_relation_elements,
    STATE(387), 1,
      sym_function_call,
    STATE(440), 1,
      sym_double_quote,
    STATE(903), 1,
      sym_function_name,
    STATE(79), 2,
      sym_relation_contains_key,
      sym_relation_contains,
    STATE(94), 2,
      sym_unquoted_identifier,
      sym_quoted_identifier,
  [8961] = 13,
    ACTIONS(93), 1,
      aux_sym_unquoted_identifier_token1,
    ACTIONS(745), 1,
      anon_sym_DQUOTE,
    ACTIONS(747), 1,
      anon_sym_LPAREN,
    ACTIONS(751), 1,
      sym_object_name,
    ACTIONS(753), 1,
      aux_sym_delete_statement_token3,
    STATE(81), 1,
      sym_relation_element,
    STATE(121), 1,
      sym_identifier,
    STATE(312), 1,
      sym_relation_elements,
    STATE(387), 1,
      sym_function_call,
    STATE(440), 1,
      sym_double_quote,
    STATE(903), 1,
      sym_function_name,
    STATE(79), 2,
      sym_relation_contains_key,
      sym_relation_contains,
    STATE(94), 2,
      sym_unquoted_identifier,
      sym_quoted_identifier,
  [9003] = 13,
    ACTIONS(93), 1,
      aux_sym_unquoted_identifier_token1,
    ACTIONS(745), 1,
      anon_sym_DQUOTE,
    ACTIONS(747), 1,
      anon_sym_LPAREN,
    ACTIONS(751), 1,
      sym_object_name,
    ACTIONS(755), 1,
      aux_sym_delete_statement_token3,
    STATE(81), 1,
      sym_relation_element,
    STATE(121), 1,
      sym_identifier,
    STATE(312), 1,
      sym_relation_elements,
    STATE(387), 1,
      sym_function_call,
    STATE(440), 1,
      sym_double_quote,
    STATE(903), 1,
      sym_function_name,
    STATE(79), 2,
      sym_relation_contains_key,
      sym_relation_contains,
    STATE(94), 2,
      sym_unquoted_identifier,
      sym_quoted_identifier,
  [9045] = 13,
    ACTIONS(93), 1,
      aux_sym_unquoted_identifier_token1,
    ACTIONS(745), 1,
      anon_sym_DQUOTE,
    ACTIONS(747), 1,
      anon_sym_LPAREN,
    ACTIONS(751), 1,
      sym_object_name,
    ACTIONS(757), 1,
      aux_sym_delete_statement_token3,
    STATE(81), 1,
      sym_relation_element,
    STATE(121), 1,
      sym_identifier,
    STATE(312), 1,
      sym_relation_elements,
    STATE(387), 1,
      sym_function_call,
    STATE(440), 1,
      sym_double_quote,
    STATE(903), 1,
      sym_function_name,
    STATE(79), 2,
      sym_relation_contains_key,
      sym_relation_contains,
    STATE(94), 2,
      sym_unquoted_identifier,
      sym_quoted_identifier,
  [9087] = 1,
    ACTIONS(759), 15,
      ts_builtin_sym_end,
      aux_sym_select_statement_token1,
      aux_sym_delete_statement_token1,
      aux_sym_begin_batch_token1,
      aux_sym_insert_statement_token1,
      aux_sym_truncate_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_update_token1,
      aux_sym_use_token1,
      aux_sym_grant_token1,
      aux_sym_revoke_token1,
      aux_sym_privilege_token3,
      aux_sym_list_roles_token1,
      aux_sym_apply_batch_token1,
  [9105] = 2,
    ACTIONS(761), 7,
      anon_sym_SQUOTE,
      anon_sym_DQUOTE,
      sym_double_dollar,
      anon_sym_DASH,
      sym_uuid_literal,
      anon_sym_QMARK,
      anon_sym_COLON,
    ACTIONS(763), 8,
      aux_sym_unquoted_identifier_token1,
      aux_sym_unquoted_identifier_token2,
      sym_nan,
      sym_infinity,
      sym_true_literal,
      sym_false_literal,
      sym_blob_literal,
      sym_null_literal,
  [9125] = 13,
    ACTIONS(93), 1,
      aux_sym_unquoted_identifier_token1,
    ACTIONS(745), 1,
      anon_sym_DQUOTE,
    ACTIONS(747), 1,
      anon_sym_LPAREN,
    ACTIONS(751), 1,
      sym_object_name,
    ACTIONS(765), 1,
      aux_sym_delete_statement_token3,
    STATE(81), 1,
      sym_relation_element,
    STATE(121), 1,
      sym_identifier,
    STATE(312), 1,
      sym_relation_elements,
    STATE(387), 1,
      sym_function_call,
    STATE(440), 1,
      sym_double_quote,
    STATE(903), 1,
      sym_function_name,
    STATE(79), 2,
      sym_relation_contains_key,
      sym_relation_contains,
    STATE(94), 2,
      sym_unquoted_identifier,
      sym_quoted_identifier,
  [9167] = 13,
    ACTIONS(93), 1,
      aux_sym_unquoted_identifier_token1,
    ACTIONS(745), 1,
      anon_sym_DQUOTE,
    ACTIONS(747), 1,
      anon_sym_LPAREN,
    ACTIONS(751), 1,
      sym_object_name,
    ACTIONS(767), 1,
      aux_sym_delete_statement_token3,
    STATE(81), 1,
      sym_relation_element,
    STATE(121), 1,
      sym_identifier,
    STATE(312), 1,
      sym_relation_elements,
    STATE(387), 1,
      sym_function_call,
    STATE(440), 1,
      sym_double_quote,
    STATE(903), 1,
      sym_function_name,
    STATE(79), 2,
      sym_relation_contains_key,
      sym_relation_contains,
    STATE(94), 2,
      sym_unquoted_identifier,
      sym_quoted_identifier,
  [9209] = 13,
    ACTIONS(93), 1,
      aux_sym_unquoted_identifier_token1,
    ACTIONS(745), 1,
      anon_sym_DQUOTE,
    ACTIONS(747), 1,
      anon_sym_LPAREN,
    ACTIONS(751), 1,
      sym_object_name,
    ACTIONS(769), 1,
      aux_sym_delete_statement_token3,
    STATE(81), 1,
      sym_relation_element,
    STATE(121), 1,
      sym_identifier,
    STATE(312), 1,
      sym_relation_elements,
    STATE(387), 1,
      sym_function_call,
    STATE(440), 1,
      sym_double_quote,
    STATE(903), 1,
      sym_function_name,
    STATE(79), 2,
      sym_relation_contains_key,
      sym_relation_contains,
    STATE(94), 2,
      sym_unquoted_identifier,
      sym_quoted_identifier,
  [9251] = 12,
    ACTIONS(93), 1,
      aux_sym_unquoted_identifier_token1,
    ACTIONS(745), 1,
      anon_sym_DQUOTE,
    ACTIONS(747), 1,
      anon_sym_LPAREN,
    ACTIONS(751), 1,
      sym_object_name,
    STATE(81), 1,
      sym_relation_element,
    STATE(105), 1,
      sym_relation_elements,
    STATE(121), 1,
      sym_identifier,
    STATE(387), 1,
      sym_function_call,
    STATE(440), 1,
      sym_double_quote,
    STATE(903), 1,
      sym_function_name,
    STATE(79), 2,
      sym_relation_contains_key,
      sym_relation_contains,
    STATE(94), 2,
      sym_unquoted_identifier,
      sym_quoted_identifier,
  [9290] = 12,
    ACTIONS(93), 1,
      aux_sym_unquoted_identifier_token1,
    ACTIONS(745), 1,
      anon_sym_DQUOTE,
    ACTIONS(747), 1,
      anon_sym_LPAREN,
    ACTIONS(771), 1,
      sym_object_name,
    STATE(83), 1,
      sym_relation_element,
    STATE(121), 1,
      sym_identifier,
    STATE(387), 1,
      sym_function_call,
    STATE(440), 1,
      sym_double_quote,
    STATE(659), 1,
      sym_column_not_null,
    STATE(903), 1,
      sym_function_name,
    STATE(79), 2,
      sym_relation_contains_key,
      sym_relation_contains,
    STATE(94), 2,
      sym_unquoted_identifier,
      sym_quoted_identifier,
  [9329] = 11,
    ACTIONS(93), 1,
      aux_sym_unquoted_identifier_token1,
    ACTIONS(745), 1,
      anon_sym_DQUOTE,
    ACTIONS(747), 1,
      anon_sym_LPAREN,
    ACTIONS(751), 1,
      sym_object_name,
    STATE(83), 1,
      sym_relation_element,
    STATE(121), 1,
      sym_identifier,
    STATE(387), 1,
      sym_function_call,
    STATE(440), 1,
      sym_double_quote,
    STATE(903), 1,
      sym_function_name,
    STATE(79), 2,
      sym_relation_contains_key,
      sym_relation_contains,
    STATE(94), 2,
      sym_unquoted_identifier,
      sym_quoted_identifier,
  [9365] = 10,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    ACTIONS(97), 1,
      anon_sym_DASH,
    ACTIONS(573), 1,
      aux_sym_unquoted_identifier_token2,
    STATE(5), 1,
      aux_sym_integer_repeat1,
    STATE(416), 1,
      sym_single_quote,
    STATE(465), 1,
      sym_integer,
    ACTIONS(575), 2,
      sym_nan,
      sym_infinity,
    STATE(34), 2,
      sym_standard_decimal_notation,
      sym_scientific_notation,
    STATE(691), 2,
      sym_string_literal,
      sym_float_literal,
  [9399] = 11,
    ACTIONS(89), 1,
      anon_sym_DQUOTE,
    ACTIONS(773), 1,
      aux_sym_unquoted_identifier_token1,
    ACTIONS(775), 1,
      sym_column_glob,
    ACTIONS(777), 1,
      aux_sym_select_statement_token2,
    ACTIONS(779), 1,
      aux_sym_select_statement_token3,
    STATE(440), 1,
      sym_double_quote,
    STATE(461), 1,
      sym_select_element,
    STATE(613), 1,
      sym_identifier,
    STATE(614), 1,
      sym_column_name,
    STATE(615), 1,
      sym_select_expression,
    STATE(94), 2,
      sym_unquoted_identifier,
      sym_quoted_identifier,
  [9434] = 4,
    ACTIONS(783), 1,
      aux_sym_privilege_token1,
    ACTIONS(785), 1,
      aux_sym_resource_token4,
    STATE(165), 1,
      sym_privilege,
    ACTIONS(781), 8,
      aux_sym_select_statement_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_privilege_token3,
      aux_sym_privilege_token4,
      aux_sym_privilege_token5,
      aux_sym_privilege_token6,
      aux_sym_privilege_token7,
  [9454] = 11,
    ACTIONS(787), 1,
      aux_sym_truncate_token2,
    ACTIONS(789), 1,
      aux_sym_create_index_token2,
    ACTIONS(791), 1,
      aux_sym_resource_token2,
    ACTIONS(793), 1,
      aux_sym_resource_token5,
    ACTIONS(795), 1,
      aux_sym_resource_token6,
    ACTIONS(797), 1,
      aux_sym_drop_aggregate_token1,
    ACTIONS(799), 1,
      aux_sym_drop_materialized_view_token1,
    ACTIONS(801), 1,
      aux_sym_drop_trigger_token1,
    ACTIONS(803), 1,
      aux_sym_drop_type_token1,
    ACTIONS(805), 1,
      aux_sym_drop_user_token1,
    ACTIONS(807), 1,
      aux_sym_create_aggregate_token1,
  [9488] = 10,
    ACTIONS(89), 1,
      anon_sym_DQUOTE,
    ACTIONS(773), 1,
      aux_sym_unquoted_identifier_token1,
    ACTIONS(775), 1,
      sym_column_glob,
    ACTIONS(809), 1,
      aux_sym_select_statement_token3,
    STATE(440), 1,
      sym_double_quote,
    STATE(461), 1,
      sym_select_element,
    STATE(613), 1,
      sym_identifier,
    STATE(614), 1,
      sym_column_name,
    STATE(621), 1,
      sym_select_expression,
    STATE(94), 2,
      sym_unquoted_identifier,
      sym_quoted_identifier,
  [9520] = 9,
    ACTIONS(89), 1,
      anon_sym_DQUOTE,
    ACTIONS(775), 1,
      sym_column_glob,
    ACTIONS(811), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(440), 1,
      sym_double_quote,
    STATE(461), 1,
      sym_select_element,
    STATE(613), 1,
      sym_identifier,
    STATE(614), 1,
      sym_column_name,
    STATE(621), 1,
      sym_select_expression,
    STATE(94), 2,
      sym_unquoted_identifier,
      sym_quoted_identifier,
  [9549] = 9,
    ACTIONS(89), 1,
      anon_sym_DQUOTE,
    ACTIONS(775), 1,
      sym_column_glob,
    ACTIONS(811), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(440), 1,
      sym_double_quote,
    STATE(461), 1,
      sym_select_element,
    STATE(613), 1,
      sym_identifier,
    STATE(614), 1,
      sym_column_name,
    STATE(652), 1,
      sym_select_expression,
    STATE(94), 2,
      sym_unquoted_identifier,
      sym_quoted_identifier,
  [9578] = 6,
    ACTIONS(330), 1,
      aux_sym_create_keyspace_token1,
    ACTIONS(813), 1,
      aux_sym_drop_index_token1,
    ACTIONS(815), 1,
      aux_sym_alter_table_add_token1,
    ACTIONS(817), 1,
      aux_sym_alter_table_rename_token1,
    STATE(283), 1,
      sym_alter_table_operation,
    STATE(282), 5,
      sym_with_element,
      sym_alter_table_add,
      sym_alter_table_drop_columns,
      sym_alter_table_drop_compact_storage,
      sym_alter_table_rename,
  [9601] = 10,
    ACTIONS(819), 1,
      aux_sym_truncate_token2,
    ACTIONS(821), 1,
      aux_sym_create_index_token2,
    ACTIONS(823), 1,
      aux_sym_resource_token2,
    ACTIONS(825), 1,
      aux_sym_resource_token5,
    ACTIONS(827), 1,
      aux_sym_resource_token6,
    ACTIONS(829), 1,
      aux_sym_drop_aggregate_token1,
    ACTIONS(831), 1,
      aux_sym_drop_materialized_view_token1,
    ACTIONS(833), 1,
      aux_sym_drop_trigger_token1,
    ACTIONS(835), 1,
      aux_sym_drop_type_token1,
    ACTIONS(837), 1,
      aux_sym_drop_user_token1,
  [9632] = 3,
    ACTIONS(783), 1,
      aux_sym_privilege_token1,
    STATE(998), 1,
      sym_privilege,
    ACTIONS(781), 8,
      aux_sym_select_statement_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_privilege_token3,
      aux_sym_privilege_token4,
      aux_sym_privilege_token5,
      aux_sym_privilege_token6,
      aux_sym_privilege_token7,
  [9649] = 3,
    ACTIONS(783), 1,
      aux_sym_privilege_token1,
    STATE(997), 1,
      sym_privilege,
    ACTIONS(781), 8,
      aux_sym_select_statement_token1,
      aux_sym_create_index_token1,
      aux_sym_drop_index_token1,
      aux_sym_privilege_token3,
      aux_sym_privilege_token4,
      aux_sym_privilege_token5,
      aux_sym_privilege_token6,
      aux_sym_privilege_token7,
  [9666] = 4,
    ACTIONS(839), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(344), 1,
      aux_sym_unquoted_identifier_repeat1,
    ACTIONS(841), 2,
      anon_sym__,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(264), 5,
      anon_sym_SEMI,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_where_spec_token1,
      aux_sym_order_spec_token1,
  [9684] = 9,
    ACTIONS(843), 1,
      anon_sym_SEMI,
    ACTIONS(845), 1,
      aux_sym_select_statement_token4,
    ACTIONS(847), 1,
      aux_sym_limit_spec_token1,
    ACTIONS(849), 1,
      aux_sym_where_spec_token1,
    ACTIONS(851), 1,
      aux_sym_order_spec_token1,
    STATE(301), 1,
      sym_semi_sep,
    STATE(386), 1,
      sym_where_spec,
    STATE(411), 1,
      sym_order_spec,
    STATE(569), 1,
      sym_limit_spec,
  [9712] = 9,
    ACTIONS(843), 1,
      anon_sym_SEMI,
    ACTIONS(847), 1,
      aux_sym_limit_spec_token1,
    ACTIONS(849), 1,
      aux_sym_where_spec_token1,
    ACTIONS(851), 1,
      aux_sym_order_spec_token1,
    ACTIONS(853), 1,
      aux_sym_select_statement_token4,
    STATE(248), 1,
      sym_semi_sep,
    STATE(372), 1,
      sym_where_spec,
    STATE(431), 1,
      sym_order_spec,
    STATE(602), 1,
      sym_limit_spec,
  [9740] = 4,
    ACTIONS(855), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(338), 1,
      aux_sym_unquoted_identifier_repeat1,
    ACTIONS(857), 2,
      anon_sym__,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(230), 5,
      anon_sym_SEMI,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_where_spec_token1,
      aux_sym_order_spec_token1,
  [9758] = 7,
    ACTIONS(97), 1,
      anon_sym_DASH,
    ACTIONS(144), 1,
      anon_sym_LBRACE,
    ACTIONS(573), 1,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(859), 1,
      anon_sym_LBRACK,
    STATE(5), 1,
      aux_sym_integer_repeat1,
    STATE(724), 1,
      sym_integer,
    STATE(725), 3,
      sym_map_literal,
      sym_set_literal,
      sym_list_literal,
  [9782] = 9,
    ACTIONS(843), 1,
      anon_sym_SEMI,
    ACTIONS(847), 1,
      aux_sym_limit_spec_token1,
    ACTIONS(849), 1,
      aux_sym_where_spec_token1,
    ACTIONS(851), 1,
      aux_sym_order_spec_token1,
    ACTIONS(861), 1,
      aux_sym_select_statement_token4,
    STATE(269), 1,
      sym_semi_sep,
    STATE(381), 1,
      sym_where_spec,
    STATE(441), 1,
      sym_order_spec,
    STATE(486), 1,
      sym_limit_spec,
  [9810] = 4,
    ACTIONS(863), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(344), 1,
      aux_sym_unquoted_identifier_repeat1,
    ACTIONS(866), 2,
      anon_sym__,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(250), 5,
      anon_sym_SEMI,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_where_spec_token1,
      aux_sym_order_spec_token1,
  [9828] = 5,
    ACTIONS(873), 1,
      aux_sym_relation_element_token1,
    ACTIONS(875), 1,
      aux_sym_relation_contains_key_token1,
    ACTIONS(877), 1,
      aux_sym_column_not_null_token1,
    ACTIONS(869), 2,
      anon_sym_LT,
      anon_sym_GT,
    ACTIONS(871), 4,
      anon_sym_LT_EQ,
      anon_sym_LT_GT,
      anon_sym_EQ,
      anon_sym_GT_EQ,
  [9848] = 7,
    ACTIONS(89), 1,
      anon_sym_DQUOTE,
    ACTIONS(93), 1,
      aux_sym_unquoted_identifier_token1,
    ACTIONS(879), 1,
      aux_sym_delete_statement_token2,
    STATE(121), 1,
      sym_identifier,
    STATE(440), 1,
      sym_double_quote,
    STATE(759), 1,
      sym_function_name,
    STATE(94), 2,
      sym_unquoted_identifier,
      sym_quoted_identifier,
  [9871] = 6,
    ACTIONS(881), 1,
      aux_sym_index_keys_spec_token1,
    ACTIONS(883), 1,
      aux_sym_index_entries_s_spec_token1,
    ACTIONS(885), 1,
      aux_sym_index_full_spec_token1,
    ACTIONS(887), 1,
      sym_object_name,
    STATE(808), 1,
      sym_index_column_spec,
    STATE(811), 3,
      sym_index_keys_spec,
      sym_index_entries_s_spec,
      sym_index_full_spec,
  [9892] = 7,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    ACTIONS(97), 1,
      anon_sym_DASH,
    ACTIONS(573), 1,
      aux_sym_unquoted_identifier_token2,
    STATE(5), 1,
      aux_sym_integer_repeat1,
    STATE(416), 1,
      sym_single_quote,
    STATE(697), 2,
      sym_string_literal,
      sym_integer,
  [9915] = 4,
    ACTIONS(889), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(358), 1,
      aux_sym_unquoted_identifier_repeat1,
    ACTIONS(891), 2,
      anon_sym__,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(264), 4,
      aux_sym_drop_index_token1,
      aux_sym_create_keyspace_token1,
      aux_sym_alter_table_add_token1,
      aux_sym_alter_table_rename_token1,
  [9932] = 7,
    ACTIONS(89), 1,
      anon_sym_DQUOTE,
    ACTIONS(93), 1,
      aux_sym_unquoted_identifier_token1,
    ACTIONS(893), 1,
      aux_sym_delete_statement_token2,
    STATE(121), 1,
      sym_identifier,
    STATE(440), 1,
      sym_double_quote,
    STATE(968), 1,
      sym_function_name,
    STATE(94), 2,
      sym_unquoted_identifier,
      sym_quoted_identifier,
  [9955] = 7,
    ACTIONS(89), 1,
      anon_sym_DQUOTE,
    ACTIONS(811), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(440), 1,
      sym_double_quote,
    STATE(613), 1,
      sym_identifier,
    STATE(614), 1,
      sym_column_name,
    STATE(656), 1,
      sym_select_element,
    STATE(94), 2,
      sym_unquoted_identifier,
      sym_quoted_identifier,
  [9978] = 8,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    ACTIONS(895), 1,
      aux_sym_delete_statement_token2,
    ACTIONS(897), 1,
      aux_sym_create_index_token3,
    ACTIONS(899), 1,
      sym_object_name,
    STATE(416), 1,
      sym_single_quote,
    STATE(976), 1,
      sym_short_index_name,
    STATE(977), 1,
      sym_string_literal,
  [10003] = 7,
    ACTIONS(89), 1,
      anon_sym_DQUOTE,
    ACTIONS(901), 1,
      aux_sym_unquoted_identifier_token1,
    ACTIONS(903), 1,
      aux_sym_delete_statement_token2,
    STATE(121), 1,
      sym_identifier,
    STATE(299), 1,
      sym_function_name,
    STATE(440), 1,
      sym_double_quote,
    STATE(94), 2,
      sym_unquoted_identifier,
      sym_quoted_identifier,
  [10026] = 6,
    ACTIONS(881), 1,
      aux_sym_index_keys_spec_token1,
    ACTIONS(883), 1,
      aux_sym_index_entries_s_spec_token1,
    ACTIONS(885), 1,
      aux_sym_index_full_spec_token1,
    ACTIONS(887), 1,
      sym_object_name,
    STATE(803), 1,
      sym_index_column_spec,
    STATE(811), 3,
      sym_index_keys_spec,
      sym_index_entries_s_spec,
      sym_index_full_spec,
  [10047] = 6,
    ACTIONS(881), 1,
      aux_sym_index_keys_spec_token1,
    ACTIONS(883), 1,
      aux_sym_index_entries_s_spec_token1,
    ACTIONS(885), 1,
      aux_sym_index_full_spec_token1,
    ACTIONS(887), 1,
      sym_object_name,
    STATE(748), 1,
      sym_index_column_spec,
    STATE(811), 3,
      sym_index_keys_spec,
      sym_index_entries_s_spec,
      sym_index_full_spec,
  [10068] = 4,
    ACTIONS(873), 1,
      aux_sym_relation_element_token1,
    ACTIONS(875), 1,
      aux_sym_relation_contains_key_token1,
    ACTIONS(869), 2,
      anon_sym_LT,
      anon_sym_GT,
    ACTIONS(871), 4,
      anon_sym_LT_EQ,
      anon_sym_LT_GT,
      anon_sym_EQ,
      anon_sym_GT_EQ,
  [10085] = 6,
    ACTIONS(881), 1,
      aux_sym_index_keys_spec_token1,
    ACTIONS(883), 1,
      aux_sym_index_entries_s_spec_token1,
    ACTIONS(885), 1,
      aux_sym_index_full_spec_token1,
    ACTIONS(887), 1,
      sym_object_name,
    STATE(996), 1,
      sym_index_column_spec,
    STATE(811), 3,
      sym_index_keys_spec,
      sym_index_entries_s_spec,
      sym_index_full_spec,
  [10106] = 4,
    ACTIONS(905), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(358), 1,
      aux_sym_unquoted_identifier_repeat1,
    ACTIONS(908), 2,
      anon_sym__,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(250), 4,
      aux_sym_drop_index_token1,
      aux_sym_create_keyspace_token1,
      aux_sym_alter_table_add_token1,
      aux_sym_alter_table_rename_token1,
  [10123] = 4,
    ACTIONS(911), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(349), 1,
      aux_sym_unquoted_identifier_repeat1,
    ACTIONS(913), 2,
      anon_sym__,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(230), 4,
      aux_sym_drop_index_token1,
      aux_sym_create_keyspace_token1,
      aux_sym_alter_table_add_token1,
      aux_sym_alter_table_rename_token1,
  [10140] = 6,
    ACTIONS(915), 1,
      aux_sym_compact_storage_token1,
    ACTIONS(917), 1,
      aux_sym_clustering_order_token1,
    ACTIONS(919), 1,
      sym_object_name,
    STATE(257), 1,
      sym_table_options,
    STATE(738), 1,
      sym_table_option_name,
    STATE(150), 3,
      sym_table_option_item,
      sym_compact_storage,
      sym_clustering_order,
  [10161] = 7,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    ACTIONS(97), 1,
      anon_sym_DASH,
    ACTIONS(573), 1,
      aux_sym_unquoted_identifier_token2,
    STATE(5), 1,
      aux_sym_integer_repeat1,
    STATE(416), 1,
      sym_single_quote,
    STATE(906), 2,
      sym_string_literal,
      sym_integer,
  [10184] = 5,
    ACTIONS(915), 1,
      aux_sym_compact_storage_token1,
    ACTIONS(917), 1,
      aux_sym_clustering_order_token1,
    ACTIONS(919), 1,
      sym_object_name,
    STATE(738), 1,
      sym_table_option_name,
    STATE(204), 3,
      sym_table_option_item,
      sym_compact_storage,
      sym_clustering_order,
  [10202] = 6,
    ACTIONS(89), 1,
      anon_sym_DQUOTE,
    ACTIONS(921), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(121), 1,
      sym_identifier,
    STATE(440), 1,
      sym_double_quote,
    STATE(834), 1,
      sym_function_name,
    STATE(94), 2,
      sym_unquoted_identifier,
      sym_quoted_identifier,
  [10222] = 3,
    ACTIONS(927), 1,
      aux_sym_relation_element_token1,
    ACTIONS(923), 2,
      anon_sym_LT,
      anon_sym_GT,
    ACTIONS(925), 4,
      anon_sym_LT_EQ,
      anon_sym_LT_GT,
      anon_sym_EQ,
      anon_sym_GT_EQ,
  [10236] = 7,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    ACTIONS(899), 1,
      sym_object_name,
    ACTIONS(929), 1,
      aux_sym_create_index_token3,
    STATE(416), 1,
      sym_single_quote,
    STATE(785), 1,
      sym_short_index_name,
    STATE(977), 1,
      sym_string_literal,
  [10258] = 6,
    ACTIONS(89), 1,
      anon_sym_DQUOTE,
    ACTIONS(921), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(121), 1,
      sym_identifier,
    STATE(440), 1,
      sym_double_quote,
    STATE(909), 1,
      sym_function_name,
    STATE(94), 2,
      sym_unquoted_identifier,
      sym_quoted_identifier,
  [10278] = 7,
    ACTIONS(931), 1,
      aux_sym_truncate_token2,
    ACTIONS(933), 1,
      aux_sym_privilege_token1,
    ACTIONS(935), 1,
      aux_sym_resource_token2,
    ACTIONS(937), 1,
      aux_sym_resource_token5,
    ACTIONS(939), 1,
      aux_sym_resource_token6,
    ACTIONS(941), 1,
      sym_object_name,
    STATE(185), 1,
      sym_resource,
  [10300] = 7,
    ACTIONS(931), 1,
      aux_sym_truncate_token2,
    ACTIONS(933), 1,
      aux_sym_privilege_token1,
    ACTIONS(935), 1,
      aux_sym_resource_token2,
    ACTIONS(937), 1,
      aux_sym_resource_token5,
    ACTIONS(939), 1,
      aux_sym_resource_token6,
    ACTIONS(941), 1,
      sym_object_name,
    STATE(817), 1,
      sym_resource,
  [10322] = 1,
    ACTIONS(943), 7,
      anon_sym_COMMA,
      aux_sym_scientific_notation_token1,
      anon_sym_RPAREN,
      aux_sym_arithmetic_operation_token1,
      anon_sym_COLON,
      anon_sym_RBRACE,
      anon_sym_RBRACK,
  [10332] = 6,
    ACTIONS(89), 1,
      anon_sym_DQUOTE,
    ACTIONS(945), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(121), 1,
      sym_identifier,
    STATE(440), 1,
      sym_double_quote,
    STATE(972), 1,
      sym_function_name,
    STATE(94), 2,
      sym_unquoted_identifier,
      sym_quoted_identifier,
  [10352] = 3,
    ACTIONS(951), 1,
      aux_sym_relation_element_token1,
    ACTIONS(947), 2,
      anon_sym_LT,
      anon_sym_GT,
    ACTIONS(949), 4,
      anon_sym_LT_EQ,
      anon_sym_LT_GT,
      anon_sym_EQ,
      anon_sym_GT_EQ,
  [10366] = 7,
    ACTIONS(843), 1,
      anon_sym_SEMI,
    ACTIONS(847), 1,
      aux_sym_limit_spec_token1,
    ACTIONS(851), 1,
      aux_sym_order_spec_token1,
    ACTIONS(953), 1,
      aux_sym_select_statement_token4,
    STATE(224), 1,
      sym_semi_sep,
    STATE(407), 1,
      sym_order_spec,
    STATE(554), 1,
      sym_limit_spec,
  [10388] = 1,
    ACTIONS(955), 7,
      anon_sym_COMMA,
      aux_sym_scientific_notation_token1,
      anon_sym_RPAREN,
      aux_sym_arithmetic_operation_token1,
      anon_sym_COLON,
      anon_sym_RBRACE,
      anon_sym_RBRACK,
  [10398] = 6,
    ACTIONS(89), 1,
      anon_sym_DQUOTE,
    ACTIONS(945), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(121), 1,
      sym_identifier,
    STATE(440), 1,
      sym_double_quote,
    STATE(930), 1,
      sym_function_name,
    STATE(94), 2,
      sym_unquoted_identifier,
      sym_quoted_identifier,
  [10418] = 6,
    ACTIONS(89), 1,
      anon_sym_DQUOTE,
    ACTIONS(957), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(121), 1,
      sym_identifier,
    STATE(275), 1,
      sym_function_name,
    STATE(440), 1,
      sym_double_quote,
    STATE(94), 2,
      sym_unquoted_identifier,
      sym_quoted_identifier,
  [10438] = 6,
    ACTIONS(89), 1,
      anon_sym_DQUOTE,
    ACTIONS(945), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(121), 1,
      sym_identifier,
    STATE(440), 1,
      sym_double_quote,
    STATE(881), 1,
      sym_function_name,
    STATE(94), 2,
      sym_unquoted_identifier,
      sym_quoted_identifier,
  [10458] = 2,
    ACTIONS(959), 1,
      aux_sym_arithmetic_operation_token1,
    ACTIONS(943), 6,
      anon_sym_COMMA,
      aux_sym_scientific_notation_token1,
      anon_sym_RPAREN,
      anon_sym_COLON,
      anon_sym_RBRACE,
      anon_sym_RBRACK,
  [10470] = 6,
    ACTIONS(89), 1,
      anon_sym_DQUOTE,
    ACTIONS(921), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(121), 1,
      sym_identifier,
    STATE(440), 1,
      sym_double_quote,
    STATE(797), 1,
      sym_function_name,
    STATE(94), 2,
      sym_unquoted_identifier,
      sym_quoted_identifier,
  [10490] = 7,
    ACTIONS(931), 1,
      aux_sym_truncate_token2,
    ACTIONS(933), 1,
      aux_sym_privilege_token1,
    ACTIONS(935), 1,
      aux_sym_resource_token2,
    ACTIONS(937), 1,
      aux_sym_resource_token5,
    ACTIONS(939), 1,
      aux_sym_resource_token6,
    ACTIONS(941), 1,
      sym_object_name,
    STATE(824), 1,
      sym_resource,
  [10512] = 6,
    ACTIONS(89), 1,
      anon_sym_DQUOTE,
    ACTIONS(945), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(121), 1,
      sym_identifier,
    STATE(440), 1,
      sym_double_quote,
    STATE(926), 1,
      sym_function_name,
    STATE(94), 2,
      sym_unquoted_identifier,
      sym_quoted_identifier,
  [10532] = 7,
    ACTIONS(843), 1,
      anon_sym_SEMI,
    ACTIONS(845), 1,
      aux_sym_select_statement_token4,
    ACTIONS(847), 1,
      aux_sym_limit_spec_token1,
    ACTIONS(851), 1,
      aux_sym_order_spec_token1,
    STATE(301), 1,
      sym_semi_sep,
    STATE(411), 1,
      sym_order_spec,
    STATE(569), 1,
      sym_limit_spec,
  [10554] = 6,
    ACTIONS(89), 1,
      anon_sym_DQUOTE,
    ACTIONS(961), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(121), 1,
      sym_identifier,
    STATE(440), 1,
      sym_double_quote,
    STATE(823), 1,
      sym_function_name,
    STATE(94), 2,
      sym_unquoted_identifier,
      sym_quoted_identifier,
  [10574] = 5,
    ACTIONS(963), 1,
      aux_sym_privilege_token3,
    ACTIONS(965), 1,
      aux_sym_alter_table_add_token1,
    ACTIONS(967), 1,
      aux_sym_alter_table_rename_token1,
    STATE(290), 1,
      sym_alter_type_operation,
    STATE(291), 3,
      sym_alter_type_alter_type,
      sym_alter_type_add,
      sym_alter_type_rename,
  [10592] = 6,
    ACTIONS(89), 1,
      anon_sym_DQUOTE,
    ACTIONS(921), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(121), 1,
      sym_identifier,
    STATE(440), 1,
      sym_double_quote,
    STATE(857), 1,
      sym_function_name,
    STATE(94), 2,
      sym_unquoted_identifier,
      sym_quoted_identifier,
  [10612] = 6,
    ACTIONS(89), 1,
      anon_sym_DQUOTE,
    ACTIONS(961), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(121), 1,
      sym_identifier,
    STATE(440), 1,
      sym_double_quote,
    STATE(777), 1,
      sym_function_name,
    STATE(94), 2,
      sym_unquoted_identifier,
      sym_quoted_identifier,
  [10632] = 7,
    ACTIONS(843), 1,
      anon_sym_SEMI,
    ACTIONS(847), 1,
      aux_sym_limit_spec_token1,
    ACTIONS(851), 1,
      aux_sym_order_spec_token1,
    ACTIONS(853), 1,
      aux_sym_select_statement_token4,
    STATE(248), 1,
      sym_semi_sep,
    STATE(431), 1,
      sym_order_spec,
    STATE(602), 1,
      sym_limit_spec,
  [10654] = 2,
    ACTIONS(969), 2,
      anon_sym_LT,
      anon_sym_GT,
    ACTIONS(971), 4,
      anon_sym_LT_EQ,
      anon_sym_LT_GT,
      anon_sym_EQ,
      anon_sym_GT_EQ,
  [10665] = 6,
    ACTIONS(973), 1,
      aux_sym_truncate_token2,
    ACTIONS(975), 1,
      aux_sym_resource_token2,
    ACTIONS(977), 1,
      aux_sym_resource_token6,
    ACTIONS(979), 1,
      aux_sym_drop_materialized_view_token1,
    ACTIONS(981), 1,
      aux_sym_drop_type_token1,
    ACTIONS(983), 1,
      aux_sym_drop_user_token1,
  [10684] = 6,
    ACTIONS(959), 1,
      aux_sym_arithmetic_operation_token1,
    ACTIONS(985), 1,
      anon_sym_COMMA,
    ACTIONS(987), 1,
      aux_sym_scientific_notation_token1,
    ACTIONS(989), 1,
      anon_sym_RPAREN,
    STATE(18), 1,
      sym_comma_sep,
    STATE(454), 1,
      aux_sym_function_args_repeat1,
  [10703] = 4,
    ACTIONS(991), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(402), 1,
      aux_sym_unquoted_identifier_repeat1,
    ACTIONS(240), 2,
      anon_sym_COMMA,
      aux_sym_from_spec_token1,
    ACTIONS(993), 2,
      anon_sym__,
      aux_sym_unquoted_identifier_token2,
  [10718] = 1,
    ACTIONS(995), 6,
      anon_sym_SEMI,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_where_spec_token1,
      aux_sym_order_spec_token1,
      aux_sym_using_timestamp_spec_token1,
  [10727] = 4,
    ACTIONS(997), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(392), 1,
      aux_sym_unquoted_identifier_repeat1,
    ACTIONS(250), 2,
      aux_sym_using_timestamp_spec_token1,
      aux_sym_update_assignments_token1,
    ACTIONS(1000), 2,
      anon_sym__,
      aux_sym_unquoted_identifier_token2,
  [10742] = 6,
    ACTIONS(1003), 1,
      aux_sym_unquoted_identifier_token1,
    ACTIONS(1005), 1,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(1007), 1,
      sym_object_name,
    STATE(391), 1,
      sym_table_expression,
    STATE(394), 1,
      sym_table_name,
    STATE(609), 1,
      sym_keyspace_name,
  [10761] = 1,
    ACTIONS(1009), 6,
      anon_sym_SEMI,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_where_spec_token1,
      aux_sym_order_spec_token1,
      aux_sym_using_timestamp_spec_token1,
  [10770] = 4,
    ACTIONS(1011), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(392), 1,
      aux_sym_unquoted_identifier_repeat1,
    ACTIONS(264), 2,
      aux_sym_using_timestamp_spec_token1,
      aux_sym_update_assignments_token1,
    ACTIONS(1013), 2,
      anon_sym__,
      aux_sym_unquoted_identifier_token2,
  [10785] = 6,
    ACTIONS(1007), 1,
      sym_object_name,
    ACTIONS(1015), 1,
      aux_sym_unquoted_identifier_token1,
    ACTIONS(1017), 1,
      aux_sym_unquoted_identifier_token2,
    STATE(391), 1,
      sym_table_expression,
    STATE(394), 1,
      sym_table_name,
    STATE(623), 1,
      sym_keyspace_name,
  [10804] = 4,
    ACTIONS(1019), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(401), 1,
      aux_sym_unquoted_identifier_repeat1,
    ACTIONS(230), 2,
      aux_sym_where_spec_token1,
      aux_sym_using_timestamp_spec_token1,
    ACTIONS(1021), 2,
      anon_sym__,
      aux_sym_unquoted_identifier_token2,
  [10819] = 1,
    ACTIONS(1023), 6,
      anon_sym_SEMI,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
      aux_sym_where_spec_token1,
      aux_sym_order_spec_token1,
      aux_sym_using_timestamp_spec_token1,
  [10828] = 4,
    ACTIONS(1025), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(399), 1,
      aux_sym_unquoted_identifier_repeat1,
    ACTIONS(250), 2,
      aux_sym_where_spec_token1,
      aux_sym_using_timestamp_spec_token1,
    ACTIONS(1028), 2,
      anon_sym__,
      aux_sym_unquoted_identifier_token2,
  [10843] = 4,
    ACTIONS(1031), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(400), 1,
      aux_sym_unquoted_identifier_repeat1,
    ACTIONS(250), 2,
      anon_sym_COMMA,
      aux_sym_from_spec_token1,
    ACTIONS(1034), 2,
      anon_sym__,
      aux_sym_unquoted_identifier_token2,
  [10858] = 4,
    ACTIONS(1037), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(399), 1,
      aux_sym_unquoted_identifier_repeat1,
    ACTIONS(264), 2,
      aux_sym_where_spec_token1,
      aux_sym_using_timestamp_spec_token1,
    ACTIONS(1039), 2,
      anon_sym__,
      aux_sym_unquoted_identifier_token2,
  [10873] = 4,
    ACTIONS(1041), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(400), 1,
      aux_sym_unquoted_identifier_repeat1,
    ACTIONS(278), 2,
      anon_sym_COMMA,
      aux_sym_from_spec_token1,
    ACTIONS(1043), 2,
      anon_sym__,
      aux_sym_unquoted_identifier_token2,
  [10888] = 4,
    ACTIONS(1045), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(395), 1,
      aux_sym_unquoted_identifier_repeat1,
    ACTIONS(230), 2,
      aux_sym_using_timestamp_spec_token1,
      aux_sym_update_assignments_token1,
    ACTIONS(1047), 2,
      anon_sym__,
      aux_sym_unquoted_identifier_token2,
  [10903] = 4,
    ACTIONS(250), 1,
      aux_sym_where_spec_token1,
    ACTIONS(1049), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(404), 1,
      aux_sym_unquoted_identifier_repeat1,
    ACTIONS(1052), 2,
      anon_sym__,
      aux_sym_unquoted_identifier_token2,
  [10917] = 5,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    STATE(416), 1,
      sym_single_quote,
    STATE(479), 1,
      sym_option_hash_item,
    STATE(801), 1,
      sym_string_literal,
  [10933] = 3,
    ACTIONS(240), 1,
      anon_sym_LPAREN,
    STATE(408), 1,
      aux_sym_unquoted_identifier_repeat1,
    ACTIONS(1055), 3,
      aux_sym_unquoted_identifier_token1,
      anon_sym__,
      aux_sym_unquoted_identifier_token2,
  [10945] = 5,
    ACTIONS(843), 1,
      anon_sym_SEMI,
    ACTIONS(847), 1,
      aux_sym_limit_spec_token1,
    ACTIONS(1057), 1,
      aux_sym_select_statement_token4,
    STATE(238), 1,
      sym_semi_sep,
    STATE(511), 1,
      sym_limit_spec,
  [10961] = 3,
    ACTIONS(278), 1,
      anon_sym_LPAREN,
    STATE(424), 1,
      aux_sym_unquoted_identifier_repeat1,
    ACTIONS(1059), 3,
      aux_sym_unquoted_identifier_token1,
      anon_sym__,
      aux_sym_unquoted_identifier_token2,
  [10973] = 4,
    ACTIONS(240), 1,
      aux_sym_create_aggregate_token6,
    ACTIONS(1061), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(413), 1,
      aux_sym_unquoted_identifier_repeat1,
    ACTIONS(1063), 2,
      anon_sym__,
      aux_sym_unquoted_identifier_token2,
  [10987] = 4,
    ACTIONS(1065), 1,
      anon_sym_LPAREN,
    ACTIONS(1067), 1,
      sym_object_name,
    STATE(805), 1,
      sym_primary_key_definition,
    STATE(806), 2,
      sym_compound_key,
      sym_composite_key,
  [11001] = 5,
    ACTIONS(843), 1,
      anon_sym_SEMI,
    ACTIONS(847), 1,
      aux_sym_limit_spec_token1,
    ACTIONS(853), 1,
      aux_sym_select_statement_token4,
    STATE(248), 1,
      sym_semi_sep,
    STATE(602), 1,
      sym_limit_spec,
  [11017] = 5,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    STATE(293), 1,
      sym_trigger_class,
    STATE(294), 1,
      sym_string_literal,
    STATE(416), 1,
      sym_single_quote,
  [11033] = 4,
    ACTIONS(278), 1,
      aux_sym_create_aggregate_token6,
    ACTIONS(1069), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(426), 1,
      aux_sym_unquoted_identifier_repeat1,
    ACTIONS(1071), 2,
      anon_sym__,
      aux_sym_unquoted_identifier_token2,
  [11047] = 3,
    ACTIONS(1075), 1,
      aux_sym_using_timestamp_spec_token1,
    STATE(538), 1,
      sym_using_timestamp_spec,
    ACTIONS(1073), 3,
      aux_sym_delete_statement_token1,
      aux_sym_insert_statement_token1,
      aux_sym_update_token1,
  [11059] = 3,
    ACTIONS(264), 1,
      anon_sym_LPAREN,
    STATE(424), 1,
      aux_sym_unquoted_identifier_repeat1,
    ACTIONS(1059), 3,
      aux_sym_unquoted_identifier_token1,
      anon_sym__,
      aux_sym_unquoted_identifier_token2,
  [11071] = 4,
    ACTIONS(1077), 1,
      anon_sym_SQUOTE,
    ACTIONS(1079), 1,
      aux_sym_string_literal_token1,
    STATE(842), 1,
      sym_single_quote,
    STATE(425), 2,
      sym_escaped_single_quote,
      aux_sym_string_literal_repeat1,
  [11085] = 5,
    ACTIONS(1081), 1,
      aux_sym_role_with_option_token1,
    ACTIONS(1083), 1,
      aux_sym_role_with_option_token2,
    ACTIONS(1085), 1,
      aux_sym_role_with_option_token3,
    ACTIONS(1087), 1,
      aux_sym_role_with_option_token4,
    STATE(191), 1,
      sym_role_with_option,
  [11101] = 4,
    ACTIONS(278), 1,
      aux_sym_create_aggregate_token4,
    ACTIONS(1089), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(427), 1,
      aux_sym_unquoted_identifier_repeat1,
    ACTIONS(1091), 2,
      anon_sym__,
      aux_sym_unquoted_identifier_token2,
  [11115] = 4,
    ACTIONS(1093), 1,
      anon_sym_SQUOTE,
    ACTIONS(1096), 1,
      aux_sym_string_literal_token1,
    STATE(842), 1,
      sym_single_quote,
    STATE(419), 2,
      sym_escaped_single_quote,
      aux_sym_string_literal_repeat1,
  [11129] = 3,
    ACTIONS(230), 1,
      anon_sym_LPAREN,
    STATE(415), 1,
      aux_sym_unquoted_identifier_repeat1,
    ACTIONS(1099), 3,
      aux_sym_unquoted_identifier_token1,
      anon_sym__,
      aux_sym_unquoted_identifier_token2,
  [11141] = 4,
    ACTIONS(240), 1,
      aux_sym_create_aggregate_token4,
    ACTIONS(1101), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(418), 1,
      aux_sym_unquoted_identifier_repeat1,
    ACTIONS(1103), 2,
      anon_sym__,
      aux_sym_unquoted_identifier_token2,
  [11155] = 5,
    ACTIONS(959), 1,
      aux_sym_arithmetic_operation_token1,
    ACTIONS(985), 1,
      anon_sym_COMMA,
    ACTIONS(987), 1,
      aux_sym_scientific_notation_token1,
    ACTIONS(1105), 1,
      anon_sym_COLON,
    STATE(26), 1,
      sym_comma_sep,
  [11171] = 5,
    ACTIONS(1081), 1,
      aux_sym_role_with_option_token1,
    ACTIONS(1083), 1,
      aux_sym_role_with_option_token2,
    ACTIONS(1085), 1,
      aux_sym_role_with_option_token3,
    ACTIONS(1087), 1,
      aux_sym_role_with_option_token4,
    STATE(148), 1,
      sym_role_with_option,
  [11187] = 3,
    ACTIONS(250), 1,
      anon_sym_LPAREN,
    STATE(424), 1,
      aux_sym_unquoted_identifier_repeat1,
    ACTIONS(1107), 3,
      aux_sym_unquoted_identifier_token1,
      anon_sym__,
      aux_sym_unquoted_identifier_token2,
  [11199] = 4,
    ACTIONS(1077), 1,
      anon_sym_SQUOTE,
    ACTIONS(1110), 1,
      aux_sym_string_literal_token1,
    STATE(12), 1,
      sym_single_quote,
    STATE(419), 2,
      sym_escaped_single_quote,
      aux_sym_string_literal_repeat1,
  [11213] = 4,
    ACTIONS(250), 1,
      aux_sym_create_aggregate_token6,
    ACTIONS(1112), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(426), 1,
      aux_sym_unquoted_identifier_repeat1,
    ACTIONS(1115), 2,
      anon_sym__,
      aux_sym_unquoted_identifier_token2,
  [11227] = 4,
    ACTIONS(250), 1,
      aux_sym_create_aggregate_token4,
    ACTIONS(1118), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(427), 1,
      aux_sym_unquoted_identifier_repeat1,
    ACTIONS(1121), 2,
      anon_sym__,
      aux_sym_unquoted_identifier_token2,
  [11241] = 3,
    ACTIONS(1075), 1,
      aux_sym_using_timestamp_spec_token1,
    STATE(548), 1,
      sym_using_timestamp_spec,
    ACTIONS(1124), 3,
      aux_sym_delete_statement_token1,
      aux_sym_insert_statement_token1,
      aux_sym_update_token1,
  [11253] = 5,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    STATE(416), 1,
      sym_single_quote,
    STATE(696), 1,
      sym_replication_list_item,
    STATE(815), 1,
      sym_string_literal,
  [11269] = 4,
    ACTIONS(1126), 1,
      anon_sym_DQUOTE,
    ACTIONS(1129), 1,
      aux_sym_quoted_identifier_token1,
    STATE(989), 1,
      sym_double_quote,
    STATE(430), 2,
      sym_escaped_double_quote,
      aux_sym_quoted_identifier_repeat1,
  [11283] = 5,
    ACTIONS(843), 1,
      anon_sym_SEMI,
    ACTIONS(847), 1,
      aux_sym_limit_spec_token1,
    ACTIONS(953), 1,
      aux_sym_select_statement_token4,
    STATE(224), 1,
      sym_semi_sep,
    STATE(554), 1,
      sym_limit_spec,
  [11299] = 5,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    STATE(246), 1,
      sym_trigger_class,
    STATE(294), 1,
      sym_string_literal,
    STATE(416), 1,
      sym_single_quote,
  [11315] = 2,
    ACTIONS(1134), 2,
      aux_sym_order_spec_token3,
      aux_sym_order_spec_token4,
    ACTIONS(1132), 3,
      anon_sym_SEMI,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
  [11325] = 5,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    STATE(416), 1,
      sym_single_quote,
    STATE(484), 1,
      sym_replication_list_item,
    STATE(815), 1,
      sym_string_literal,
  [11341] = 4,
    ACTIONS(230), 1,
      aux_sym_where_spec_token1,
    ACTIONS(1136), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(438), 1,
      aux_sym_unquoted_identifier_repeat1,
    ACTIONS(1138), 2,
      anon_sym__,
      aux_sym_unquoted_identifier_token2,
  [11355] = 5,
    ACTIONS(1140), 1,
      aux_sym_from_spec_token1,
    ACTIONS(1142), 1,
      sym_object_name,
    STATE(452), 1,
      sym_from_spec,
    STATE(541), 1,
      sym_delete_column_item,
    STATE(651), 1,
      sym_delete_column_list,
  [11371] = 5,
    ACTIONS(1140), 1,
      aux_sym_from_spec_token1,
    ACTIONS(1142), 1,
      sym_object_name,
    STATE(463), 1,
      sym_from_spec,
    STATE(541), 1,
      sym_delete_column_item,
    STATE(616), 1,
      sym_delete_column_list,
  [11387] = 4,
    ACTIONS(264), 1,
      aux_sym_where_spec_token1,
    ACTIONS(1144), 1,
      aux_sym_unquoted_identifier_token1,
    STATE(404), 1,
      aux_sym_unquoted_identifier_repeat1,
    ACTIONS(1146), 2,
      anon_sym__,
      aux_sym_unquoted_identifier_token2,
  [11401] = 4,
    ACTIONS(1148), 1,
      anon_sym_DQUOTE,
    ACTIONS(1150), 1,
      aux_sym_quoted_identifier_token1,
    STATE(82), 1,
      sym_double_quote,
    STATE(430), 2,
      sym_escaped_double_quote,
      aux_sym_quoted_identifier_repeat1,
  [11415] = 4,
    ACTIONS(1148), 1,
      anon_sym_DQUOTE,
    ACTIONS(1152), 1,
      aux_sym_quoted_identifier_token1,
    STATE(989), 1,
      sym_double_quote,
    STATE(439), 2,
      sym_escaped_double_quote,
      aux_sym_quoted_identifier_repeat1,
  [11429] = 5,
    ACTIONS(843), 1,
      anon_sym_SEMI,
    ACTIONS(845), 1,
      aux_sym_select_statement_token4,
    ACTIONS(847), 1,
      aux_sym_limit_spec_token1,
    STATE(301), 1,
      sym_semi_sep,
    STATE(569), 1,
      sym_limit_spec,
  [11445] = 5,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    STATE(416), 1,
      sym_single_quote,
    STATE(690), 1,
      sym_option_hash_item,
    STATE(801), 1,
      sym_string_literal,
  [11461] = 3,
    ACTIONS(1156), 1,
      aux_sym_primary_key_column_token1,
    STATE(610), 1,
      sym_primary_key_column,
    ACTIONS(1154), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [11472] = 4,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    STATE(188), 1,
      sym_string_literal,
    STATE(416), 1,
      sym_single_quote,
  [11485] = 1,
    ACTIONS(1158), 4,
      aux_sym_where_spec_token1,
      aux_sym_delete_statement_token1,
      aux_sym_insert_statement_token1,
      aux_sym_update_token1,
  [11492] = 2,
    ACTIONS(1162), 1,
      aux_sym_begin_batch_token5,
    ACTIONS(1160), 3,
      aux_sym_begin_batch_token2,
      aux_sym_begin_batch_token3,
      aux_sym_begin_batch_token4,
  [11501] = 4,
    ACTIONS(1164), 1,
      anon_sym_COMMA,
    ACTIONS(1166), 1,
      aux_sym_from_spec_token1,
    STATE(351), 1,
      sym_comma_sep,
    STATE(462), 1,
      aux_sym_select_expression_repeat1,
  [11514] = 4,
    ACTIONS(1168), 1,
      aux_sym_unquoted_identifier_token1,
    ACTIONS(1170), 1,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(1172), 1,
      aux_sym_truncate_token2,
    STATE(227), 1,
      sym_table_name,
  [11527] = 3,
    ACTIONS(1174), 1,
      anon_sym_COMMA,
    STATE(455), 1,
      aux_sym_relation_element_repeat1,
    ACTIONS(1176), 2,
      anon_sym_RPAREN,
      aux_sym_from_spec_token1,
  [11538] = 4,
    ACTIONS(1178), 1,
      aux_sym_primary_key_column_token1,
    ACTIONS(1180), 1,
      sym_object_name,
    STATE(612), 1,
      sym_column_definition,
    STATE(843), 1,
      sym_primary_key_element,
  [11551] = 3,
    ACTIONS(959), 1,
      aux_sym_arithmetic_operation_token1,
    ACTIONS(987), 1,
      aux_sym_scientific_notation_token1,
    ACTIONS(1182), 2,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [11562] = 4,
    ACTIONS(849), 1,
      aux_sym_where_spec_token1,
    ACTIONS(1075), 1,
      aux_sym_using_timestamp_spec_token1,
    STATE(157), 1,
      sym_where_spec,
    STATE(662), 1,
      sym_using_timestamp_spec,
  [11575] = 4,
    ACTIONS(959), 1,
      aux_sym_arithmetic_operation_token1,
    ACTIONS(985), 1,
      anon_sym_COMMA,
    ACTIONS(987), 1,
      aux_sym_scientific_notation_token1,
    STATE(23), 1,
      sym_comma_sep,
  [11588] = 4,
    ACTIONS(985), 1,
      anon_sym_COMMA,
    ACTIONS(1184), 1,
      anon_sym_RPAREN,
    STATE(18), 1,
      sym_comma_sep,
    STATE(472), 1,
      aux_sym_function_args_repeat1,
  [11601] = 3,
    ACTIONS(1174), 1,
      anon_sym_COMMA,
    STATE(457), 1,
      aux_sym_relation_element_repeat1,
    ACTIONS(1186), 2,
      anon_sym_RPAREN,
      aux_sym_from_spec_token1,
  [11612] = 4,
    ACTIONS(286), 1,
      aux_sym_using_timestamp_spec_token1,
    ACTIONS(1188), 1,
      aux_sym_update_assignments_token1,
    STATE(687), 1,
      sym_update_assignments,
    STATE(703), 1,
      sym_using_ttl_timestamp,
  [11625] = 3,
    ACTIONS(1190), 1,
      anon_sym_COMMA,
    STATE(457), 1,
      aux_sym_relation_element_repeat1,
    ACTIONS(1193), 2,
      anon_sym_RPAREN,
      aux_sym_from_spec_token1,
  [11636] = 4,
    ACTIONS(849), 1,
      aux_sym_where_spec_token1,
    ACTIONS(1075), 1,
      aux_sym_using_timestamp_spec_token1,
    STATE(160), 1,
      sym_where_spec,
    STATE(726), 1,
      sym_using_timestamp_spec,
  [11649] = 4,
    ACTIONS(1195), 1,
      aux_sym_relation_elements_token1,
    ACTIONS(1197), 1,
      aux_sym_primary_key_column_token1,
    STATE(467), 1,
      aux_sym_materialized_view_where_repeat1,
    STATE(529), 1,
      aux_sym_relation_elements_repeat1,
  [11662] = 4,
    ACTIONS(87), 1,
      anon_sym_SQUOTE,
    ACTIONS(91), 1,
      sym_double_dollar,
    STATE(180), 1,
      sym_string_literal,
    STATE(416), 1,
      sym_single_quote,
  [11675] = 4,
    ACTIONS(1164), 1,
      anon_sym_COMMA,
    ACTIONS(1199), 1,
      aux_sym_from_spec_token1,
    STATE(351), 1,
      sym_comma_sep,
    STATE(447), 1,
      aux_sym_select_expression_repeat1,
  [11688] = 4,
    ACTIONS(1201), 1,
      anon_sym_COMMA,
    ACTIONS(1204), 1,
      aux_sym_from_spec_token1,
    STATE(351), 1,
      sym_comma_sep,
    STATE(462), 1,
      aux_sym_select_expression_repeat1,
  [11701] = 4,
    ACTIONS(849), 1,
      aux_sym_where_spec_token1,
    ACTIONS(1075), 1,
      aux_sym_using_timestamp_spec_token1,
    STATE(154), 1,
      sym_where_spec,
    STATE(624), 1,
      sym_using_timestamp_spec,
  [11714] = 4,
    ACTIONS(1178), 1,
      aux_sym_primary_key_column_token1,
    ACTIONS(1180), 1,
      sym_object_name,
    STATE(612), 1,
      sym_column_definition,
    STATE(1008), 1,
      sym_primary_key_element,
  [11727] = 4,
    ACTIONS(120), 1,
      anon_sym_DOT,
    ACTIONS(122), 1,
      sym_scientific_notation_exponent,
    STATE(27), 1,
      sym_decimal_fraction,
    STATE(638), 1,
      sym_dot_sep,
  [11740] = 4,
    ACTIONS(97), 1,
      anon_sym_DASH,
    ACTIONS(573), 1,
      aux_sym_unquoted_identifier_token2,
    STATE(5), 1,
      aux_sym_integer_repeat1,
    STATE(705), 1,
      sym_integer,
  [11753] = 4,
    ACTIONS(1195), 1,
      aux_sym_relation_elements_token1,
    ACTIONS(1206), 1,
      aux_sym_primary_key_column_token1,
    STATE(599), 1,
      aux_sym_relation_elements_repeat1,
    STATE(600), 1,
      aux_sym_materialized_view_where_repeat1,
  [11766] = 4,
    ACTIONS(1208), 1,
      aux_sym_unquoted_identifier_token1,
    ACTIONS(1210), 1,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(1212), 1,
      aux_sym_delete_statement_token2,
    STATE(981), 1,
      sym_table_name,
  [11779] = 1,
    ACTIONS(1214), 4,
      anon_sym_COMMA,
      aux_sym_scientific_notation_token1,
      anon_sym_RPAREN,
      aux_sym_where_spec_token1,
  [11786] = 4,
    ACTIONS(286), 1,
      aux_sym_using_timestamp_spec_token1,
    ACTIONS(1188), 1,
      aux_sym_update_assignments_token1,
    STATE(642), 1,
      sym_using_ttl_timestamp,
    STATE(643), 1,
      sym_update_assignments,
  [11799] = 4,
    ACTIONS(97), 1,
      anon_sym_DASH,
    ACTIONS(573), 1,
      aux_sym_unquoted_identifier_token2,
    STATE(5), 1,
      aux_sym_integer_repeat1,
    STATE(910), 1,
      sym_integer,
  [11812] = 4,
    ACTIONS(1216), 1,
      anon_sym_COMMA,
    ACTIONS(1219), 1,
      anon_sym_RPAREN,
    STATE(18), 1,
      sym_comma_sep,
    STATE(472), 1,
      aux_sym_function_args_repeat1,
  [11825] = 1,
    ACTIONS(1221), 4,
      anon_sym_COMMA,
      aux_sym_scientific_notation_token1,
      anon_sym_RPAREN,
      aux_sym_where_spec_token1,
  [11832] = 1,
    ACTIONS(1223), 4,
      anon_sym_COMMA,
      aux_sym_scientific_notation_token1,
      anon_sym_RPAREN,
      aux_sym_where_spec_token1,
  [11839] = 3,
    ACTIONS(959), 1,
      aux_sym_arithmetic_operation_token1,
    ACTIONS(987), 1,
      aux_sym_scientific_notation_token1,
    ACTIONS(1219), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [11850] = 4,
    ACTIONS(1168), 1,
      aux_sym_unquoted_identifier_token1,
    ACTIONS(1170), 1,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(1225), 1,
      aux_sym_delete_statement_token2,
    STATE(296), 1,
      sym_table_name,
  [11863] = 3,
    ACTIONS(397), 1,
      anon_sym_COMMA,
    ACTIONS(1227), 1,
      anon_sym_RPAREN,
    STATE(485), 1,
      aux_sym_create_function_repeat1,
  [11873] = 3,
    ACTIONS(1229), 1,
      anon_sym_COMMA,
    ACTIONS(1232), 1,
      anon_sym_RBRACE,
    STATE(478), 1,
      aux_sym_replication_list_repeat1,
  [11883] = 3,
    ACTIONS(1234), 1,
      anon_sym_COMMA,
    ACTIONS(1236), 1,
      anon_sym_RBRACE,
    STATE(558), 1,
      aux_sym_option_hash_repeat1,
  [11893] = 3,
    ACTIONS(1238), 1,
      aux_sym_create_function_token1,
    ACTIONS(1240), 1,
      aux_sym_return_mode_token1,
    STATE(888), 1,
      sym_return_mode,
  [11903] = 3,
    ACTIONS(397), 1,
      anon_sym_COMMA,
    ACTIONS(1242), 1,
      anon_sym_RPAREN,
    STATE(552), 1,
      aux_sym_create_function_repeat1,
  [11913] = 3,
    ACTIONS(1238), 1,
      aux_sym_create_function_token1,
    ACTIONS(1240), 1,
      aux_sym_return_mode_token1,
    STATE(760), 1,
      sym_return_mode,
  [11923] = 3,
    ACTIONS(1244), 1,
      anon_sym_COMMA,
    ACTIONS(1247), 1,
      anon_sym_RPAREN,
    STATE(483), 1,
      aux_sym_expression_list_repeat1,
  [11933] = 3,
    ACTIONS(1249), 1,
      anon_sym_COMMA,
    ACTIONS(1251), 1,
      anon_sym_RBRACE,
    STATE(546), 1,
      aux_sym_replication_list_repeat1,
  [11943] = 3,
    ACTIONS(397), 1,
      anon_sym_COMMA,
    ACTIONS(1253), 1,
      anon_sym_RPAREN,
    STATE(117), 1,
      aux_sym_create_function_repeat1,
  [11953] = 3,
    ACTIONS(843), 1,
      anon_sym_SEMI,
    ACTIONS(845), 1,
      aux_sym_select_statement_token4,
    STATE(301), 1,
      sym_semi_sep,
  [11963] = 3,
    ACTIONS(1255), 1,
      anon_sym_COMMA,
    ACTIONS(1257), 1,
      anon_sym_RPAREN,
    STATE(483), 1,
      aux_sym_expression_list_repeat1,
  [11973] = 3,
    ACTIONS(1259), 1,
      aux_sym_delete_statement_token2,
    ACTIONS(1261), 1,
      sym_object_name,
    STATE(308), 1,
      sym_user_name,
  [11983] = 3,
    ACTIONS(1263), 1,
      aux_sym_delete_statement_token2,
    ACTIONS(1265), 1,
      sym_object_name,
    STATE(305), 1,
      sym_type_name,
  [11993] = 3,
    ACTIONS(1267), 1,
      aux_sym_delete_statement_token2,
    ACTIONS(1269), 1,
      sym_object_name,
    STATE(943), 1,
      sym_trigger_name,
  [12003] = 3,
    ACTIONS(1238), 1,
      aux_sym_create_function_token1,
    ACTIONS(1240), 1,
      aux_sym_return_mode_token1,
    STATE(990), 1,
      sym_return_mode,
  [12013] = 3,
    ACTIONS(397), 1,
      anon_sym_COMMA,
    ACTIONS(1271), 1,
      anon_sym_RPAREN,
    STATE(117), 1,
      aux_sym_create_function_repeat1,
  [12023] = 3,
    ACTIONS(1273), 1,
      anon_sym_COMMA,
    ACTIONS(1275), 1,
      anon_sym_RPAREN,
    STATE(562), 1,
      aux_sym_init_cond_list_repeat1,
  [12033] = 2,
    STATE(203), 1,
      sym_boolean_literal,
    ACTIONS(1277), 2,
      sym_true_literal,
      sym_false_literal,
  [12041] = 2,
    STATE(202), 1,
      sym_boolean_literal,
    ACTIONS(1277), 2,
      sym_true_literal,
      sym_false_literal,
  [12049] = 3,
    ACTIONS(1279), 1,
      aux_sym_delete_statement_token2,
    ACTIONS(1281), 1,
      sym_object_name,
    STATE(303), 1,
      sym_aggregate_name,
  [12059] = 3,
    ACTIONS(1283), 1,
      anon_sym_COMMA,
    ACTIONS(1285), 1,
      aux_sym_where_spec_token1,
    STATE(508), 1,
      aux_sym_update_assignments_repeat1,
  [12069] = 3,
    ACTIONS(1287), 1,
      aux_sym_delete_statement_token2,
    ACTIONS(1289), 1,
      sym_object_name,
    STATE(259), 1,
      sym_role_name,
  [12079] = 3,
    ACTIONS(1291), 1,
      anon_sym_COMMA,
    ACTIONS(1294), 1,
      anon_sym_RPAREN,
    STATE(499), 1,
      aux_sym_init_cond_hash_repeat1,
  [12089] = 3,
    ACTIONS(1007), 1,
      sym_object_name,
    ACTIONS(1296), 1,
      aux_sym_delete_statement_token2,
    STATE(298), 1,
      sym_keyspace_name,
  [12099] = 3,
    ACTIONS(1298), 1,
      aux_sym_delete_statement_token2,
    ACTIONS(1300), 1,
      sym_object_name,
    STATE(297), 1,
      sym_index_name,
  [12109] = 3,
    ACTIONS(1302), 1,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(1304), 1,
      aux_sym_scientific_notation_token1,
    STATE(24), 1,
      aux_sym_integer_repeat1,
  [12119] = 3,
    ACTIONS(389), 1,
      anon_sym_COMMA,
    ACTIONS(1306), 1,
      anon_sym_RPAREN,
    STATE(120), 1,
      aux_sym_clustering_key_list_repeat1,
  [12129] = 3,
    ACTIONS(397), 1,
      anon_sym_COMMA,
    ACTIONS(1308), 1,
      anon_sym_RPAREN,
    STATE(117), 1,
      aux_sym_create_function_repeat1,
  [12139] = 3,
    ACTIONS(1310), 1,
      anon_sym_COMMA,
    ACTIONS(1313), 1,
      anon_sym_RPAREN,
    STATE(505), 1,
      aux_sym_init_cond_nested_list_repeat1,
  [12149] = 3,
    ACTIONS(1261), 1,
      sym_object_name,
    ACTIONS(1315), 1,
      aux_sym_delete_statement_token2,
    STATE(636), 1,
      sym_user_name,
  [12159] = 3,
    ACTIONS(1317), 1,
      anon_sym_COMMA,
    ACTIONS(1320), 1,
      anon_sym_RPAREN,
    STATE(507), 1,
      aux_sym_init_cond_list_repeat1,
  [12169] = 3,
    ACTIONS(1283), 1,
      anon_sym_COMMA,
    ACTIONS(1322), 1,
      aux_sym_where_spec_token1,
    STATE(522), 1,
      aux_sym_update_assignments_repeat1,
  [12179] = 3,
    ACTIONS(1265), 1,
      sym_object_name,
    ACTIONS(1324), 1,
      aux_sym_delete_statement_token2,
    STATE(957), 1,
      sym_type_name,
  [12189] = 3,
    ACTIONS(1271), 1,
      anon_sym_RPAREN,
    ACTIONS(1326), 1,
      sym_object_name,
    STATE(594), 1,
      sym_typed_name,
  [12199] = 3,
    ACTIONS(843), 1,
      anon_sym_SEMI,
    ACTIONS(1328), 1,
      aux_sym_select_statement_token4,
    STATE(256), 1,
      sym_semi_sep,
  [12209] = 3,
    ACTIONS(1269), 1,
      sym_object_name,
    ACTIONS(1330), 1,
      aux_sym_delete_statement_token2,
    STATE(959), 1,
      sym_trigger_name,
  [12219] = 3,
    ACTIONS(389), 1,
      anon_sym_COMMA,
    ACTIONS(1332), 1,
      anon_sym_RPAREN,
    STATE(564), 1,
      aux_sym_clustering_key_list_repeat1,
  [12229] = 2,
    STATE(216), 1,
      sym_table_name,
    ACTIONS(1170), 2,
      aux_sym_unquoted_identifier_token1,
      aux_sym_unquoted_identifier_token2,
  [12237] = 3,
    ACTIONS(1326), 1,
      sym_object_name,
    ACTIONS(1334), 1,
      anon_sym_RPAREN,
    STATE(573), 1,
      sym_typed_name,
  [12247] = 3,
    ACTIONS(1336), 1,
      sym_object_name,
    STATE(654), 1,
      sym_assignment_element,
    STATE(836), 1,
      sym_indexed_column,
  [12257] = 2,
    STATE(787), 1,
      sym_table_name,
    ACTIONS(1210), 2,
      aux_sym_unquoted_identifier_token1,
      aux_sym_unquoted_identifier_token2,
  [12265] = 3,
    ACTIONS(1338), 1,
      aux_sym_delete_statement_token2,
    ACTIONS(1340), 1,
      sym_object_name,
    STATE(867), 1,
      sym_materialized_view_name,
  [12275] = 3,
    ACTIONS(1281), 1,
      sym_object_name,
    ACTIONS(1342), 1,
      aux_sym_delete_statement_token2,
    STATE(963), 1,
      sym_aggregate_name,
  [12285] = 3,
    ACTIONS(1289), 1,
      sym_object_name,
    ACTIONS(1344), 1,
      aux_sym_delete_statement_token2,
    STATE(132), 1,
      sym_role_name,
  [12295] = 2,
    ACTIONS(1348), 1,
      aux_sym_scientific_notation_token1,
    ACTIONS(1346), 2,
      anon_sym_COMMA,
      aux_sym_where_spec_token1,
  [12303] = 3,
    ACTIONS(1350), 1,
      anon_sym_COMMA,
    ACTIONS(1353), 1,
      aux_sym_where_spec_token1,
    STATE(522), 1,
      aux_sym_update_assignments_repeat1,
  [12313] = 2,
    ACTIONS(1355), 1,
      anon_sym_DOT,
    ACTIONS(1357), 2,
      aux_sym_using_timestamp_spec_token1,
      aux_sym_create_index_token3,
  [12321] = 2,
    STATE(456), 1,
      sym_table_name,
    ACTIONS(1359), 2,
      aux_sym_unquoted_identifier_token1,
      aux_sym_unquoted_identifier_token2,
  [12329] = 3,
    ACTIONS(1007), 1,
      sym_object_name,
    ACTIONS(1361), 1,
      aux_sym_delete_statement_token2,
    STATE(973), 1,
      sym_keyspace_name,
  [12339] = 2,
    ACTIONS(1363), 1,
      aux_sym_resource_token1,
    ACTIONS(1365), 2,
      aux_sym_resource_token3,
      aux_sym_resource_token4,
  [12347] = 3,
    ACTIONS(1367), 1,
      anon_sym_COMMA,
    ACTIONS(1370), 1,
      anon_sym_RBRACE,
    STATE(527), 1,
      aux_sym_option_hash_repeat1,
  [12357] = 2,
    STATE(885), 1,
      sym_table_name,
    ACTIONS(1210), 2,
      aux_sym_unquoted_identifier_token1,
      aux_sym_unquoted_identifier_token2,
  [12365] = 3,
    ACTIONS(200), 1,
      aux_sym_relation_elements_token1,
    ACTIONS(1206), 1,
      aux_sym_primary_key_column_token1,
    STATE(73), 1,
      aux_sym_relation_elements_repeat1,
  [12375] = 3,
    ACTIONS(169), 1,
      anon_sym_COMMA,
    ACTIONS(1372), 1,
      anon_sym_RPAREN,
    STATE(63), 1,
      aux_sym_relation_element_repeat2,
  [12385] = 3,
    ACTIONS(1374), 1,
      sym_object_name,
    STATE(583), 1,
      sym_column_definition,
    STATE(790), 1,
      sym_column_definition_list,
  [12395] = 3,
    ACTIONS(1376), 1,
      aux_sym_select_statement_token3,
    ACTIONS(1378), 1,
      aux_sym_insert_values_spec_token1,
    STATE(113), 1,
      sym_insert_values_spec,
  [12405] = 3,
    ACTIONS(1238), 1,
      aux_sym_create_function_token1,
    ACTIONS(1240), 1,
      aux_sym_return_mode_token1,
    STATE(908), 1,
      sym_return_mode,
  [12415] = 2,
    STATE(260), 1,
      sym_table_name,
    ACTIONS(1170), 2,
      aux_sym_unquoted_identifier_token1,
      aux_sym_unquoted_identifier_token2,
  [12423] = 2,
    STATE(628), 1,
      sym_table_name,
    ACTIONS(1210), 2,
      aux_sym_unquoted_identifier_token1,
      aux_sym_unquoted_identifier_token2,
  [12431] = 3,
    ACTIONS(1380), 1,
      anon_sym_COMMA,
    ACTIONS(1382), 1,
      anon_sym_GT,
    STATE(568), 1,
      aux_sym_data_type_definition_repeat1,
  [12441] = 3,
    ACTIONS(1238), 1,
      aux_sym_create_function_token1,
    ACTIONS(1240), 1,
      aux_sym_return_mode_token1,
    STATE(853), 1,
      sym_return_mode,
  [12451] = 1,
    ACTIONS(1384), 3,
      aux_sym_delete_statement_token1,
      aux_sym_insert_statement_token1,
      aux_sym_update_token1,
  [12457] = 2,
    STATE(253), 1,
      sym_boolean_literal,
    ACTIONS(1277), 2,
      sym_true_literal,
      sym_false_literal,
  [12465] = 2,
    STATE(1006), 1,
      sym_table_name,
    ACTIONS(1210), 2,
      aux_sym_unquoted_identifier_token1,
      aux_sym_unquoted_identifier_token2,
  [12473] = 3,
    ACTIONS(1386), 1,
      anon_sym_COMMA,
    ACTIONS(1388), 1,
      aux_sym_from_spec_token1,
    STATE(561), 1,
      aux_sym_delete_column_list_repeat1,
  [12483] = 2,
    STATE(272), 1,
      sym_table_name,
    ACTIONS(1170), 2,
      aux_sym_unquoted_identifier_token1,
      aux_sym_unquoted_identifier_token2,
  [12491] = 3,
    ACTIONS(1390), 1,
      anon_sym_COMMA,
    ACTIONS(1392), 1,
      anon_sym_RPAREN,
    STATE(587), 1,
      aux_sym_column_definition_list_repeat1,
  [12501] = 2,
    ACTIONS(1396), 1,
      anon_sym_LBRACK,
    ACTIONS(1394), 2,
      anon_sym_COMMA,
      aux_sym_from_spec_token1,
  [12509] = 2,
    STATE(334), 1,
      sym_table_name,
    ACTIONS(1398), 2,
      aux_sym_unquoted_identifier_token1,
      aux_sym_unquoted_identifier_token2,
  [12517] = 3,
    ACTIONS(1249), 1,
      anon_sym_COMMA,
    ACTIONS(1400), 1,
      anon_sym_RBRACE,
    STATE(478), 1,
      aux_sym_replication_list_repeat1,
  [12527] = 3,
    ACTIONS(1402), 1,
      anon_sym_COMMA,
    ACTIONS(1405), 1,
      aux_sym_from_spec_token1,
    STATE(547), 1,
      aux_sym_delete_column_list_repeat1,
  [12537] = 1,
    ACTIONS(1073), 3,
      aux_sym_delete_statement_token1,
      aux_sym_insert_statement_token1,
      aux_sym_update_token1,
  [12543] = 2,
    STATE(712), 1,
      sym_table_name,
    ACTIONS(1407), 2,
      aux_sym_unquoted_identifier_token1,
      aux_sym_unquoted_identifier_token2,
  [12551] = 3,
    ACTIONS(1238), 1,
      aux_sym_create_function_token1,
    ACTIONS(1240), 1,
      aux_sym_return_mode_token1,
    STATE(816), 1,
      sym_return_mode,
  [12561] = 3,
    ACTIONS(397), 1,
      anon_sym_COMMA,
    ACTIONS(1409), 1,
      anon_sym_RPAREN,
    STATE(504), 1,
      aux_sym_create_function_repeat1,
  [12571] = 3,
    ACTIONS(397), 1,
      anon_sym_COMMA,
    ACTIONS(1411), 1,
      anon_sym_RPAREN,
    STATE(117), 1,
      aux_sym_create_function_repeat1,
  [12581] = 3,
    ACTIONS(1413), 1,
      anon_sym_COMMA,
    ACTIONS(1415), 1,
      anon_sym_RPAREN,
    STATE(499), 1,
      aux_sym_init_cond_hash_repeat1,
  [12591] = 3,
    ACTIONS(843), 1,
      anon_sym_SEMI,
    ACTIONS(1057), 1,
      aux_sym_select_statement_token4,
    STATE(238), 1,
      sym_semi_sep,
  [12601] = 3,
    ACTIONS(1417), 1,
      anon_sym_COMMA,
    ACTIONS(1419), 1,
      anon_sym_RPAREN,
    STATE(505), 1,
      aux_sym_init_cond_nested_list_repeat1,
  [12611] = 1,
    ACTIONS(1421), 3,
      anon_sym_SEMI,
      aux_sym_select_statement_token4,
      aux_sym_limit_spec_token1,
  [12617] = 1,
    ACTIONS(1423), 3,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      aux_sym_from_spec_token1,
  [12623] = 3,
    ACTIONS(1234), 1,
      anon_sym_COMMA,
    ACTIONS(1425), 1,
      anon_sym_RBRACE,
    STATE(527), 1,
      aux_sym_option_hash_repeat1,
  [12633] = 3,
    ACTIONS(169), 1,
      anon_sym_COMMA,
    ACTIONS(1427), 1,
      anon_sym_RPAREN,
    STATE(566), 1,
      aux_sym_relation_element_repeat2,
  [12643] = 3,
    ACTIONS(169), 1,
      anon_sym_COMMA,
    ACTIONS(1429), 1,
      anon_sym_RPAREN,
    STATE(530), 1,
      aux_sym_relation_element_repeat2,
  [12653] = 3,
    ACTIONS(1386), 1,
      anon_sym_COMMA,
    ACTIONS(1431), 1,
      aux_sym_from_spec_token1,
    STATE(547), 1,
      aux_sym_delete_column_list_repeat1,
  [12663] = 3,
    ACTIONS(1273), 1,
      anon_sym_COMMA,
    ACTIONS(1433), 1,
      anon_sym_RPAREN,
    STATE(507), 1,
      aux_sym_init_cond_list_repeat1,
  [12673] = 3,
    ACTIONS(1435), 1,
      aux_sym_unquoted_identifier_token2,
    ACTIONS(1437), 1,
      aux_sym_scientific_notation_token1,
    STATE(22), 1,
      aux_sym_integer_repeat1,
  [12683] = 3,
    ACTIONS(389), 1,
      anon_sym_COMMA,
    ACTIONS(1439), 1,
      anon_sym_RPAREN,
    STATE(120), 1,
      aux_sym_clustering_key_list_repeat1,
  [12693] = 3,
    ACTIONS(389), 1,
      anon_sym_COMMA,
    ACTIONS(1441), 1,
      anon_sym_RPAREN,
    STATE(503), 1,
      aux_sym_clustering_key_list_repeat1,
  [12703] = 3,
    ACTIONS(169), 1,
      anon_sym_COMMA,
    ACTIONS(1429), 1,
      anon_sym_RPAREN,
    STATE(63), 1,
      aux_sym_relation_element_repeat2,
  [12713] = 3,
    ACTIONS(1443), 1,
      aux_sym_delete_statement_token1,
    ACTIONS(1445), 1,
      aux_sym_insert_statement_token1,
    ACTIONS(1447), 1,
      aux_sym_update_token1,
  [12723] = 3,
    ACTIONS(1449), 1,
      anon_sym_COMMA,
    ACTIONS(1452), 1,
      anon_sym_GT,
    STATE(568), 1,
      aux_sym_data_type_definition_repeat1,
  [12733] = 3,
    ACTIONS(843), 1,
      anon_sym_SEMI,
    ACTIONS(853), 1,
      aux_sym_select_statement_token4,
    STATE(248), 1,
      sym_semi_sep,
  [12743] = 3,
    ACTIONS(397), 1,
      anon_sym_COMMA,
    ACTIONS(1454), 1,
      anon_sym_RPAREN,
    STATE(117), 1,
      aux_sym_create_function_repeat1,
  [12753] = 3,
    ACTIONS(397), 1,
      anon_sym_COMMA,
    ACTIONS(1456), 1,
      anon_sym_RPAREN,
    STATE(570), 1,
      aux_sym_create_function_repeat1,
  [12763] = 3,
    ACTIONS(1326), 1,
      sym_object_name,
    ACTIONS(1411), 1,
      anon_sym_RPAREN,
    STATE(477), 1,
      sym_typed_name,
  [12773] = 3,
    ACTIONS(397), 1,
      anon_sym_COMMA,
    ACTIONS(1458), 1,
      anon_sym_RPAREN,
    STATE(492), 1,
      aux_sym_create_function_repeat1,
  [12783] = 3,
    ACTIONS(1340), 1,
      sym_object_name,
    ACTIONS(1460), 1,
      aux_sym_delete_statement_token2,
    STATE(258), 1,
      sym_materialized_view_name,
  [12793] = 2,
    STATE(280), 1,
      sym_table_name,
    ACTIONS(1170), 2,
      aux_sym_unquoted_identifier_token1,
      aux_sym_unquoted_identifier_token2,
  [12801] = 3,
    ACTIONS(1238), 1,
      aux_sym_create_function_token1,
    ACTIONS(1240), 1,
      aux_sym_return_mode_token1,
    STATE(849), 1,
      sym_return_mode,
  [12811] = 3,
    ACTIONS(1255), 1,
      anon_sym_COMMA,
    ACTIONS(1462), 1,
      anon_sym_RPAREN,
    STATE(487), 1,
      aux_sym_expression_list_repeat1,
  [12821] = 3,
    ACTIONS(959), 1,
      aux_sym_arithmetic_operation_token1,
    ACTIONS(987), 1,
      aux_sym_scientific_notation_token1,
    ACTIONS(1464), 1,
      anon_sym_RBRACE,
  [12831] = 3,
    ACTIONS(1374), 1,
      sym_object_name,
    STATE(583), 1,
      sym_column_definition,
    STATE(847), 1,
      sym_column_definition_list,
  [12841] = 3,
    ACTIONS(1281), 1,
      sym_object_name,
    ACTIONS(1466), 1,
      aux_sym_delete_statement_token2,
    STATE(749), 1,
      sym_aggregate_name,
  [12851] = 3,
    ACTIONS(959), 1,
      aux_sym_arithmetic_operation_token1,
    ACTIONS(987), 1,
      aux_sym_scientific_notation_token1,
    ACTIONS(1105), 1,
      anon_sym_COLON,
  [12861] = 2,
    STATE(702), 1,
      sym_table_name,
    ACTIONS(1210), 2,
      aux_sym_unquoted_identifier_token1,
      aux_sym_unquoted_identifier_token2,
  [12869] = 3,
    ACTIONS(1468), 1,
      anon_sym_COMMA,
    ACTIONS(1470), 1,
      anon_sym_RPAREN,
    STATE(543), 1,
      aux_sym_column_definition_list_repeat1,
  [12879] = 2,
    STATE(470), 1,
      sym_table_name,
    ACTIONS(1359), 2,
      aux_sym_unquoted_identifier_token1,
      aux_sym_unquoted_identifier_token2,
  [12887] = 3,
    ACTIONS(959), 1,
      aux_sym_arithmetic_operation_token1,
    ACTIONS(987), 1,
      aux_sym_scientific_notation_token1,
    ACTIONS(1472), 1,
      anon_sym_RBRACK,
  [12897] = 3,
    ACTIONS(1376), 1,
      aux_sym_select_statement_token3,
    ACTIONS(1378), 1,
      aux_sym_insert_values_spec_token1,
    STATE(116), 1,
      sym_insert_values_spec,
  [12907] = 3,
    ACTIONS(1474), 1,
      anon_sym_COMMA,
    ACTIONS(1477), 1,
      anon_sym_RPAREN,
    STATE(587), 1,
      aux_sym_column_definition_list_repeat1,
  [12917] = 2,
    STATE(783), 1,
      sym_table_name,
    ACTIONS(1210), 2,
      aux_sym_unquoted_identifier_token1,
      aux_sym_unquoted_identifier_token2,
  [12925] = 2,
    STATE(837), 1,
      sym_table_name,
    ACTIONS(1210), 2,
      aux_sym_unquoted_identifier_token1,
      aux_sym_unquoted_identifier_token2,
  [12933] = 2,
    ACTIONS(1479), 1,
      anon_sym_RPAREN,
    ACTIONS(1481), 2,
      aux_sym_order_spec_token3,
      aux_sym_order_spec_token4,
  [12941] = 3,
    ACTIONS(1380), 1,
      anon_sym_COMMA,
    ACTIONS(1483), 1,
      anon_sym_GT,
    STATE(536), 1,
      aux_sym_data_type_definition_repeat1,
  [12951] = 3,
    ACTIONS(1413), 1,
      anon_sym_COMMA,
    ACTIONS(1485), 1,
      anon_sym_RPAREN,
    STATE(553), 1,
      aux_sym_init_cond_hash_repeat1,
  [12961] = 2,
    STATE(670), 1,
      sym_table_name,
    ACTIONS(1407), 2,
      aux_sym_unquoted_identifier_token1,
      aux_sym_unquoted_identifier_token2,
  [12969] = 3,
    ACTIONS(397), 1,
      anon_sym_COMMA,
    ACTIONS(1487), 1,
      anon_sym_RPAREN,
    STATE(597), 1,
      aux_sym_create_function_repeat1,
  [12979] = 3,
    ACTIONS(1336), 1,
      sym_object_name,
    STATE(497), 1,
      sym_assignment_element,
    STATE(836), 1,
      sym_indexed_column,
  [12989] = 3,
    ACTIONS(1174), 1,
      anon_sym_COMMA,
    ACTIONS(1489), 1,
      anon_sym_RPAREN,
    STATE(605), 1,
      aux_sym_relation_element_repeat1,
  [12999] = 3,
    ACTIONS(397), 1,
      anon_sym_COMMA,
    ACTIONS(1242), 1,
      anon_sym_RPAREN,
    STATE(117), 1,
      aux_sym_create_function_repeat1,
  [13009] = 3,
    ACTIONS(1326), 1,
      sym_object_name,
    ACTIONS(1487), 1,
      anon_sym_RPAREN,
    STATE(481), 1,
      sym_typed_name,
  [13019] = 3,
    ACTIONS(200), 1,
      aux_sym_relation_elements_token1,
    ACTIONS(1491), 1,
      aux_sym_primary_key_column_token1,
    STATE(73), 1,
      aux_sym_relation_elements_repeat1,
  [13029] = 3,
    ACTIONS(1493), 1,
      aux_sym_relation_elements_token1,
    ACTIONS(1496), 1,
      aux_sym_primary_key_column_token1,
    STATE(600), 1,
      aux_sym_materialized_view_where_repeat1,
  [13039] = 2,
    STATE(398), 1,
      sym_table_name,
    ACTIONS(1005), 2,
      aux_sym_unquoted_identifier_token1,
      aux_sym_unquoted_identifier_token2,
  [13047] = 3,
    ACTIONS(843), 1,
      anon_sym_SEMI,
    ACTIONS(953), 1,
      aux_sym_select_statement_token4,
    STATE(224), 1,
      sym_semi_sep,
  [13057] = 2,
    STATE(398), 1,
      sym_table_name,
    ACTIONS(1017), 2,
      aux_sym_unquoted_identifier_token1,
      aux_sym_unquoted_identifier_token2,
  [13065] = 3,
    ACTIONS(1238), 1,
      aux_sym_create_function_token1,
    ACTIONS(1240), 1,
      aux_sym_return_mode_token1,
    STATE(802), 1,
      sym_return_mode,
  [13075] = 3,
    ACTIONS(1174), 1,
      anon_sym_COMMA,
    ACTIONS(1498), 1,
      anon_sym_RPAREN,
    STATE(457), 1,
      aux_sym_relation_element_repeat1,
  [13085] = 3,
    ACTIONS(1417), 1,
      anon_sym_COMMA,
    ACTIONS(1500), 1,
      anon_sym_RPAREN,
    STATE(555), 1,
      aux_sym_init_cond_nested_list_repeat1,
  [13095] = 2,
    ACTIONS(1502), 1,
      sym_object_name,
    STATE(276), 1,
      sym_keyspace_name,
  [13102] = 2,
    ACTIONS(142), 1,
      anon_sym_LPAREN,
    STATE(72), 1,
      sym_assignment_tuple,
  [13109] = 2,
    ACTIONS(120), 1,
      anon_sym_DOT,
    STATE(601), 1,
      sym_dot_sep,
  [13116] = 1,
    ACTIONS(1504), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [13121] = 2,
    ACTIONS(212), 1,
      aux_sym_quoted_identifier_token1,
    ACTIONS(1506), 1,
      anon_sym_DQUOTE,
  [13128] = 1,
    ACTIONS(1477), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [13133] = 1,
    ACTIONS(1508), 2,
      anon_sym_COMMA,
      aux_sym_from_spec_token1,
  [13138] = 1,
    ACTIONS(1510), 2,
      anon_sym_COMMA,
      aux_sym_from_spec_token1,
  [13143] = 2,
    ACTIONS(1512), 1,
      aux_sym_from_spec_token1,
    STATE(343), 1,
      sym_from_spec,
  [13150] = 2,
    ACTIONS(1514), 1,
      aux_sym_from_spec_token1,
    STATE(452), 1,
      sym_from_spec,
  [13157] = 2,
    ACTIONS(1502), 1,
      sym_object_name,
    STATE(933), 1,
      sym_keyspace_name,
  [13164] = 2,
    ACTIONS(1516), 1,
      sym_object_name,
    STATE(169), 1,
      sym_role_name,
  [13171] = 2,
    ACTIONS(1518), 1,
      sym_object_name,
    STATE(383), 1,
      sym_type_name,
  [13178] = 2,
    ACTIONS(1520), 1,
      sym_object_name,
    STATE(648), 1,
      sym_user_name,
  [13185] = 2,
    ACTIONS(1512), 1,
      aux_sym_from_spec_token1,
    STATE(339), 1,
      sym_from_spec,
  [13192] = 1,
    ACTIONS(761), 2,
      anon_sym_DQUOTE,
      aux_sym_unquoted_identifier_token1,
  [13197] = 2,
    ACTIONS(120), 1,
      anon_sym_DOT,
    STATE(603), 1,
      sym_dot_sep,
  [13204] = 2,
    ACTIONS(849), 1,
      aux_sym_where_spec_token1,
    STATE(157), 1,
      sym_where_spec,
  [13211] = 2,
    ACTIONS(1326), 1,
      sym_object_name,
    STATE(571), 1,
      sym_typed_name,
  [13218] = 2,
    ACTIONS(1522), 1,
      sym_object_name,
    STATE(776), 1,
      sym_aggregate_name,
  [13225] = 2,
    ACTIONS(1524), 1,
      sym_object_name,
    STATE(663), 1,
      sym_delete_column_item,
  [13232] = 2,
    ACTIONS(1526), 1,
      anon_sym_LPAREN,
    STATE(532), 1,
      sym_insert_column_spec,
  [13239] = 2,
    ACTIONS(124), 1,
      aux_sym_string_literal_token1,
    ACTIONS(1528), 1,
      anon_sym_SQUOTE,
  [13246] = 1,
    ACTIONS(1294), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [13251] = 1,
    ACTIONS(1313), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [13256] = 1,
    ACTIONS(1320), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [13261] = 2,
    ACTIONS(985), 1,
      anon_sym_COMMA,
    STATE(6), 1,
      sym_comma_sep,
  [13268] = 1,
    ACTIONS(1530), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [13273] = 1,
    ACTIONS(1532), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [13278] = 2,
    ACTIONS(1534), 1,
      aux_sym_create_keyspace_token1,
    STATE(249), 1,
      sym_user_with,
  [13285] = 2,
    ACTIONS(1536), 1,
      aux_sym_resource_token5,
    ACTIONS(1538), 1,
      aux_sym_drop_aggregate_token1,
  [13292] = 2,
    ACTIONS(1540), 1,
      aux_sym_unquoted_identifier_token2,
    STATE(14), 1,
      aux_sym_integer_repeat1,
  [13299] = 2,
    ACTIONS(1542), 1,
      sym_object_name,
    STATE(630), 1,
      sym_init_cond_hash_item,
  [13306] = 2,
    ACTIONS(1544), 1,
      aux_sym_using_timestamp_spec_token2,
    ACTIONS(1546), 1,
      aux_sym_using_ttl_timestamp_token1,
  [13313] = 2,
    ACTIONS(142), 1,
      anon_sym_LPAREN,
    STATE(66), 1,
      sym_assignment_tuple,
  [13320] = 2,
    ACTIONS(1188), 1,
      aux_sym_update_assignments_token1,
    STATE(687), 1,
      sym_update_assignments,
  [13327] = 2,
    ACTIONS(849), 1,
      aux_sym_where_spec_token1,
    STATE(163), 1,
      sym_where_spec,
  [13334] = 2,
    ACTIONS(843), 1,
      anon_sym_SEMI,
    STATE(238), 1,
      sym_semi_sep,
  [13341] = 2,
    ACTIONS(1548), 1,
      sym_object_name,
    STATE(189), 1,
      sym_alter_type_rename_item,
  [13348] = 2,
    ACTIONS(1550), 1,
      sym_object_name,
    STATE(179), 1,
      sym_materialized_view_name,
  [13355] = 2,
    ACTIONS(1552), 1,
      anon_sym_LBRACE,
    STATE(194), 1,
      sym_replication_list,
  [13362] = 2,
    ACTIONS(1534), 1,
      aux_sym_create_keyspace_token1,
    STATE(292), 1,
      sym_user_with,
  [13369] = 2,
    ACTIONS(1554), 1,
      sym_object_name,
    STATE(659), 1,
      sym_column_not_null,
  [13376] = 1,
    ACTIONS(1556), 2,
      aux_sym_relation_elements_token1,
      aux_sym_primary_key_column_token1,
  [13381] = 2,
    ACTIONS(1514), 1,
      aux_sym_from_spec_token1,
    STATE(458), 1,
      sym_from_spec,
  [13388] = 2,
    ACTIONS(1512), 1,
      aux_sym_from_spec_token1,
    STATE(340), 1,
      sym_from_spec,
  [13395] = 2,
    ACTIONS(1558), 1,
      anon_sym_DQUOTE,
    ACTIONS(1560), 1,
      aux_sym_quoted_identifier_token1,
  [13402] = 1,
    ACTIONS(1353), 2,
      anon_sym_COMMA,
      aux_sym_where_spec_token1,
  [13407] = 1,
    ACTIONS(1346), 2,
      anon_sym_COMMA,
      aux_sym_where_spec_token1,
  [13412] = 1,
    ACTIONS(1204), 2,
      anon_sym_COMMA,
      aux_sym_from_spec_token1,
  [13417] = 1,
    ACTIONS(1562), 2,
      aux_sym_unquoted_identifier_token1,
      aux_sym_unquoted_identifier_token2,
  [13422] = 2,
    ACTIONS(1564), 1,
      aux_sym_unquoted_identifier_token2,
    STATE(7), 1,
      aux_sym_integer_repeat1,
  [13429] = 1,
    ACTIONS(1496), 2,
      aux_sym_relation_elements_token1,
      aux_sym_primary_key_column_token1,
  [13434] = 2,
    ACTIONS(843), 1,
      anon_sym_SEMI,
    STATE(256), 1,
      sym_semi_sep,
  [13441] = 2,
    ACTIONS(1566), 1,
      aux_sym_primary_key_column_token1,
    STATE(176), 1,
      sym_primary_key_element,
  [13448] = 2,
    ACTIONS(849), 1,
      aux_sym_where_spec_token1,
    STATE(160), 1,
      sym_where_spec,
  [13455] = 1,
    ACTIONS(1405), 2,
      anon_sym_COMMA,
      aux_sym_from_spec_token1,
  [13460] = 2,
    ACTIONS(142), 1,
      anon_sym_LPAREN,
    STATE(559), 1,
      sym_assignment_tuple,
  [13467] = 2,
    ACTIONS(142), 1,
      anon_sym_LPAREN,
    STATE(70), 1,
      sym_assignment_tuple,
  [13474] = 2,
    ACTIONS(1568), 1,
      sym_object_name,
    STATE(911), 1,
      sym_clustering_key_list,
  [13481] = 2,
    ACTIONS(1302), 1,
      aux_sym_unquoted_identifier_token2,
    STATE(24), 1,
      aux_sym_integer_repeat1,
  [13488] = 2,
    ACTIONS(1570), 1,
      sym_object_name,
    STATE(792), 1,
      sym_column_list,
  [13495] = 2,
    ACTIONS(1534), 1,
      aux_sym_create_keyspace_token1,
    STATE(214), 1,
      sym_user_with,
  [13502] = 2,
    ACTIONS(1572), 1,
      aux_sym_where_spec_token1,
    STATE(661), 1,
      sym_materialized_view_where,
  [13509] = 2,
    ACTIONS(1326), 1,
      sym_object_name,
    STATE(551), 1,
      sym_typed_name,
  [13516] = 2,
    ACTIONS(1570), 1,
      sym_object_name,
    STATE(987), 1,
      sym_column_list,
  [13523] = 2,
    ACTIONS(1550), 1,
      sym_object_name,
    STATE(988), 1,
      sym_materialized_view_name,
  [13530] = 2,
    ACTIONS(1574), 1,
      aux_sym_role_with_option_token1,
    STATE(125), 1,
      sym_user_password,
  [13537] = 2,
    ACTIONS(1576), 1,
      sym_object_name,
    STATE(279), 1,
      sym_index_name,
  [13544] = 2,
    ACTIONS(1578), 1,
      aux_sym_durable_writes_token1,
    STATE(237), 1,
      sym_durable_writes,
  [13551] = 2,
    ACTIONS(577), 1,
      anon_sym_LBRACE,
    STATE(195), 1,
      sym_option_hash,
  [13558] = 2,
    ACTIONS(1326), 1,
      sym_object_name,
    STATE(136), 1,
      sym_typed_name,
  [13565] = 2,
    ACTIONS(1516), 1,
      sym_object_name,
    STATE(274), 1,
      sym_role_name,
  [13572] = 2,
    ACTIONS(1522), 1,
      sym_object_name,
    STATE(273), 1,
      sym_aggregate_name,
  [13579] = 2,
    ACTIONS(1568), 1,
      sym_object_name,
    STATE(872), 1,
      sym_clustering_key_list,
  [13586] = 1,
    ACTIONS(1580), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [13591] = 2,
    ACTIONS(1582), 1,
      sym_object_name,
    STATE(754), 1,
      sym_trigger_name,
  [13598] = 2,
    ACTIONS(1520), 1,
      sym_object_name,
    STATE(268), 1,
      sym_user_name,
  [13605] = 2,
    ACTIONS(1374), 1,
      sym_object_name,
    STATE(612), 1,
      sym_column_definition,
  [13612] = 2,
    ACTIONS(1584), 1,
      anon_sym_LBRACK,
    ACTIONS(1586), 1,
      anon_sym_EQ,
  [13619] = 2,
    ACTIONS(849), 1,
      aux_sym_where_spec_token1,
    STATE(144), 1,
      sym_where_spec,
  [13626] = 2,
    ACTIONS(1566), 1,
      aux_sym_primary_key_column_token1,
    STATE(131), 1,
      sym_primary_key_element,
  [13633] = 2,
    ACTIONS(1554), 1,
      sym_object_name,
    STATE(459), 1,
      sym_column_not_null,
  [13640] = 1,
    ACTIONS(1370), 2,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [13645] = 1,
    ACTIONS(1588), 2,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [13650] = 2,
    ACTIONS(1590), 1,
      aux_sym_compact_storage_token1,
    ACTIONS(1592), 1,
      sym_object_name,
  [13657] = 2,
    ACTIONS(1326), 1,
      sym_object_name,
    STATE(151), 1,
      sym_typed_name,
  [13664] = 2,
    ACTIONS(1552), 1,
      anon_sym_LBRACE,
    STATE(183), 1,
      sym_replication_list,
  [13671] = 2,
    ACTIONS(1578), 1,
      aux_sym_durable_writes_token1,
    STATE(286), 1,
      sym_durable_writes,
  [13678] = 1,
    ACTIONS(1232), 2,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [13683] = 1,
    ACTIONS(1594), 2,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [13688] = 2,
    ACTIONS(1326), 1,
      sym_object_name,
    STATE(152), 1,
      sym_typed_name,
  [13695] = 2,
    ACTIONS(1596), 1,
      anon_sym_COMMA,
    ACTIONS(1598), 1,
      anon_sym_RPAREN,
  [13702] = 2,
    ACTIONS(1600), 1,
      sym_object_name,
    STATE(845), 1,
      sym_partition_key_list,
  [13709] = 2,
    ACTIONS(1548), 1,
      sym_object_name,
    STATE(156), 1,
      sym_alter_type_rename_item,
  [13716] = 2,
    ACTIONS(1526), 1,
      anon_sym_LPAREN,
    STATE(586), 1,
      sym_insert_column_spec,
  [13723] = 2,
    ACTIONS(1188), 1,
      aux_sym_update_assignments_token1,
    STATE(723), 1,
      sym_update_assignments,
  [13730] = 2,
    ACTIONS(843), 1,
      anon_sym_SEMI,
    STATE(248), 1,
      sym_semi_sep,
  [13737] = 1,
    ACTIONS(1602), 2,
      anon_sym_SEMI,
      aux_sym_select_statement_token4,
  [13742] = 1,
    ACTIONS(1604), 2,
      anon_sym_COMMA,
      aux_sym_from_spec_token1,
  [13747] = 2,
    ACTIONS(843), 1,
      anon_sym_SEMI,
    STATE(261), 1,
      sym_semi_sep,
  [13754] = 2,
    ACTIONS(1606), 1,
      anon_sym_SQUOTE,
    ACTIONS(1608), 1,
      aux_sym_string_literal_token1,
  [13761] = 1,
    ACTIONS(1610), 2,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [13766] = 2,
    ACTIONS(1502), 1,
      sym_object_name,
    STATE(814), 1,
      sym_keyspace_name,
  [13773] = 2,
    ACTIONS(1516), 1,
      sym_object_name,
    STATE(177), 1,
      sym_role_name,
  [13780] = 2,
    ACTIONS(1572), 1,
      aux_sym_where_spec_token1,
    STATE(688), 1,
      sym_materialized_view_where,
  [13787] = 2,
    ACTIONS(1570), 1,
      sym_object_name,
    STATE(828), 1,
      sym_column_list,
  [13794] = 2,
    ACTIONS(1522), 1,
      sym_object_name,
    STATE(858), 1,
      sym_aggregate_name,
  [13801] = 1,
    ACTIONS(1612), 2,
      aux_sym_select_statement_token3,
      aux_sym_insert_values_spec_token1,
  [13806] = 1,
    ACTIONS(1452), 2,
      anon_sym_COMMA,
      anon_sym_GT,
  [13811] = 2,
    ACTIONS(1582), 1,
      sym_object_name,
    STATE(882), 1,
      sym_trigger_name,
  [13818] = 1,
    ACTIONS(1614), 2,
      aux_sym_using_timestamp_spec_token1,
      aux_sym_create_index_token3,
  [13823] = 2,
    ACTIONS(1518), 1,
      sym_object_name,
    STATE(762), 1,
      sym_type_name,
  [13830] = 2,
    ACTIONS(1520), 1,
      sym_object_name,
    STATE(669), 1,
      sym_user_name,
  [13837] = 2,
    ACTIONS(843), 1,
      anon_sym_SEMI,
    STATE(224), 1,
      sym_semi_sep,
  [13844] = 2,
    ACTIONS(1518), 1,
      sym_object_name,
    STATE(271), 1,
      sym_type_name,
  [13851] = 2,
    ACTIONS(849), 1,
      aux_sym_where_spec_token1,
    STATE(137), 1,
      sym_where_spec,
  [13858] = 1,
    ACTIONS(1616), 2,
      anon_sym_COMMA,
      aux_sym_where_spec_token1,
  [13863] = 1,
    ACTIONS(1618), 2,
      anon_sym_COMMA,
      aux_sym_where_spec_token1,
  [13868] = 2,
    ACTIONS(849), 1,
      aux_sym_where_spec_token1,
    STATE(143), 1,
      sym_where_spec,
  [13875] = 2,
    ACTIONS(1550), 1,
      sym_object_name,
    STATE(239), 1,
      sym_materialized_view_name,
  [13882] = 2,
    ACTIONS(1578), 1,
      aux_sym_durable_writes_token1,
    STATE(311), 1,
      sym_durable_writes,
  [13889] = 2,
    ACTIONS(1552), 1,
      anon_sym_LBRACE,
    STATE(186), 1,
      sym_replication_list,
  [13896] = 1,
    ACTIONS(1247), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [13901] = 2,
    ACTIONS(1620), 1,
      aux_sym_unquoted_identifier_token2,
    STATE(21), 1,
      aux_sym_integer_repeat1,
  [13908] = 2,
    ACTIONS(142), 1,
      anon_sym_LPAREN,
    STATE(560), 1,
      sym_assignment_tuple,
  [13915] = 2,
    ACTIONS(843), 1,
      anon_sym_SEMI,
    STATE(310), 1,
      sym_semi_sep,
  [13922] = 1,
    ACTIONS(1622), 1,
      anon_sym_LPAREN,
  [13926] = 1,
    ACTIONS(1624), 1,
      aux_sym_delete_statement_token3,
  [13930] = 1,
    ACTIONS(1626), 1,
      anon_sym_EQ,
  [13934] = 1,
    ACTIONS(1628), 1,
      aux_sym_grant_token2,
  [13938] = 1,
    ACTIONS(1630), 1,
      anon_sym_EQ,
  [13942] = 1,
    ACTIONS(1632), 1,
      aux_sym_select_statement_token5,
  [13946] = 1,
    ACTIONS(1634), 1,
      anon_sym_EQ,
  [13950] = 1,
    ACTIONS(1636), 1,
      aux_sym_drop_type_token1,
  [13954] = 1,
    ACTIONS(1638), 1,
      aux_sym_order_spec_token1,
  [13958] = 1,
    ACTIONS(1640), 1,
      aux_sym_grant_token2,
  [13962] = 1,
    ACTIONS(1642), 1,
      aux_sym_compact_storage_token2,
  [13966] = 1,
    ACTIONS(1644), 1,
      aux_sym_compact_storage_token2,
  [13970] = 1,
    ACTIONS(1646), 1,
      sym_object_name,
  [13974] = 1,
    ACTIONS(1648), 1,
      sym_object_name,
  [13978] = 1,
    ACTIONS(1650), 1,
      anon_sym_RPAREN,
  [13982] = 1,
    ACTIONS(1652), 1,
      anon_sym_LPAREN,
  [13986] = 1,
    ACTIONS(1654), 1,
      anon_sym_RPAREN,
  [13990] = 1,
    ACTIONS(1656), 1,
      anon_sym_RPAREN,
  [13994] = 1,
    ACTIONS(1658), 1,
      anon_sym_RPAREN,
  [13998] = 1,
    ACTIONS(1660), 1,
      aux_sym_delete_statement_token3,
  [14002] = 1,
    ACTIONS(1662), 1,
      aux_sym_create_index_token3,
  [14006] = 1,
    ACTIONS(1664), 1,
      sym_object_name,
  [14010] = 1,
    ACTIONS(1666), 1,
      sym_object_name,
  [14014] = 1,
    ACTIONS(1668), 1,
      aux_sym_insert_statement_token3,
  [14018] = 1,
    ACTIONS(1670), 1,
      anon_sym_EQ,
  [14022] = 1,
    ACTIONS(1672), 1,
      anon_sym_LPAREN,
  [14026] = 1,
    ACTIONS(1674), 1,
      aux_sym_create_function_token1,
  [14030] = 1,
    ACTIONS(1676), 1,
      aux_sym_insert_statement_token3,
  [14034] = 1,
    ACTIONS(1678), 1,
      anon_sym_LPAREN,
  [14038] = 1,
    ACTIONS(1680), 1,
      aux_sym_return_mode_token2,
  [14042] = 1,
    ACTIONS(1682), 1,
      aux_sym_create_function_token1,
  [14046] = 1,
    ACTIONS(1684), 1,
      sym_object_name,
  [14050] = 1,
    ACTIONS(1686), 1,
      aux_sym_create_function_token2,
  [14054] = 1,
    ACTIONS(1688), 1,
      sym_object_name,
  [14058] = 1,
    ACTIONS(1690), 1,
      sym_object_name,
  [14062] = 1,
    ACTIONS(1692), 1,
      anon_sym_RPAREN,
  [14066] = 1,
    ACTIONS(1694), 1,
      aux_sym_select_statement_token1,
  [14070] = 1,
    ACTIONS(1696), 1,
      sym_object_name,
  [14074] = 1,
    ACTIONS(1698), 1,
      aux_sym_create_aggregate_token3,
  [14078] = 1,
    ACTIONS(1700), 1,
      aux_sym_delete_statement_token3,
  [14082] = 1,
    ACTIONS(1702), 1,
      aux_sym_create_aggregate_token3,
  [14086] = 1,
    ACTIONS(1704), 1,
      anon_sym_RPAREN,
  [14090] = 1,
    ACTIONS(1706), 1,
      anon_sym_LPAREN,
  [14094] = 1,
    ACTIONS(1708), 1,
      anon_sym_LPAREN,
  [14098] = 1,
    ACTIONS(1710), 1,
      aux_sym_insert_statement_token3,
  [14102] = 1,
    ACTIONS(1712), 1,
      anon_sym_EQ,
  [14106] = 1,
    ACTIONS(1714), 1,
      anon_sym_EQ,
  [14110] = 1,
    ACTIONS(1716), 1,
      anon_sym_EQ,
  [14114] = 1,
    ACTIONS(1718), 1,
      anon_sym_EQ,
  [14118] = 1,
    ACTIONS(1720), 1,
      anon_sym_LPAREN,
  [14122] = 1,
    ACTIONS(1722), 1,
      anon_sym_EQ,
  [14126] = 1,
    ACTIONS(1724), 1,
      aux_sym_create_index_token3,
  [14130] = 1,
    ACTIONS(1726), 1,
      aux_sym_select_statement_token1,
  [14134] = 1,
    ACTIONS(1728), 1,
      anon_sym_LPAREN,
  [14138] = 1,
    ACTIONS(1730), 1,
      anon_sym_RBRACE,
  [14142] = 1,
    ACTIONS(1732), 1,
      aux_sym_delete_statement_token3,
  [14146] = 1,
    ACTIONS(1734), 1,
      anon_sym_RPAREN,
  [14150] = 1,
    ACTIONS(1736), 1,
      anon_sym_LPAREN,
  [14154] = 1,
    ACTIONS(1738), 1,
      anon_sym_RPAREN,
  [14158] = 1,
    ACTIONS(1740), 1,
      anon_sym_LPAREN,
  [14162] = 1,
    ACTIONS(1742), 1,
      anon_sym_LPAREN,
  [14166] = 1,
    ACTIONS(1744), 1,
      anon_sym_LPAREN,
  [14170] = 1,
    ACTIONS(1746), 1,
      sym_object_name,
  [14174] = 1,
    ACTIONS(1748), 1,
      aux_sym_create_aggregate_token4,
  [14178] = 1,
    ACTIONS(1750), 1,
      anon_sym_RPAREN,
  [14182] = 1,
    ACTIONS(1752), 1,
      aux_sym_select_statement_token5,
  [14186] = 1,
    ACTIONS(1754), 1,
      anon_sym_RPAREN,
  [14190] = 1,
    ACTIONS(1756), 1,
      anon_sym_COLON,
  [14194] = 1,
    ACTIONS(1758), 1,
      aux_sym_create_function_token1,
  [14198] = 1,
    ACTIONS(1760), 1,
      anon_sym_RPAREN,
  [14202] = 1,
    ACTIONS(1762), 1,
      aux_sym_create_function_token2,
  [14206] = 1,
    ACTIONS(1764), 1,
      anon_sym_RPAREN,
  [14210] = 1,
    ACTIONS(1766), 1,
      anon_sym_RPAREN,
  [14214] = 1,
    ACTIONS(1768), 1,
      aux_sym_return_mode_token2,
  [14218] = 1,
    ACTIONS(1770), 1,
      anon_sym_RPAREN,
  [14222] = 1,
    ACTIONS(1772), 1,
      sym_object_name,
  [14226] = 1,
    ACTIONS(1774), 1,
      aux_sym_column_not_null_token2,
  [14230] = 1,
    ACTIONS(1776), 1,
      anon_sym_RPAREN,
  [14234] = 1,
    ACTIONS(1778), 1,
      aux_sym_create_keyspace_token2,
  [14238] = 1,
    ACTIONS(1780), 1,
      sym_object_name,
  [14242] = 1,
    ACTIONS(1782), 1,
      aux_sym_create_keyspace_token1,
  [14246] = 1,
    ACTIONS(1784), 1,
      anon_sym_COLON,
  [14250] = 1,
    ACTIONS(1786), 1,
      aux_sym_create_function_token1,
  [14254] = 1,
    ACTIONS(1788), 1,
      aux_sym_from_spec_token1,
  [14258] = 1,
    ACTIONS(1790), 1,
      aux_sym_create_function_token1,
  [14262] = 1,
    ACTIONS(1792), 1,
      aux_sym_create_materialized_view_token1,
  [14266] = 1,
    ACTIONS(1794), 1,
      sym_object_name,
  [14270] = 1,
    ACTIONS(1796), 1,
      aux_sym_create_function_token2,
  [14274] = 1,
    ACTIONS(1798), 1,
      anon_sym_EQ,
  [14278] = 1,
    ACTIONS(1800), 1,
      anon_sym_LPAREN,
  [14282] = 1,
    ACTIONS(1802), 1,
      aux_sym_grant_token2,
  [14286] = 1,
    ACTIONS(1804), 1,
      sym_object_name,
  [14290] = 1,
    ACTIONS(1806), 1,
      sym_object_name,
  [14294] = 1,
    ACTIONS(1808), 1,
      aux_sym_create_aggregate_token5,
  [14298] = 1,
    ACTIONS(1810), 1,
      aux_sym_from_spec_token1,
  [14302] = 1,
    ACTIONS(1812), 1,
      anon_sym_RPAREN,
  [14306] = 1,
    ACTIONS(1814), 1,
      anon_sym_RPAREN,
  [14310] = 1,
    ACTIONS(1816), 1,
      sym_object_name,
  [14314] = 1,
    ACTIONS(1818), 1,
      sym_object_name,
  [14318] = 1,
    ACTIONS(1820), 1,
      anon_sym_RPAREN,
  [14322] = 1,
    ACTIONS(1822), 1,
      aux_sym_create_aggregate_token4,
  [14326] = 1,
    ACTIONS(1824), 1,
      anon_sym_RPAREN,
  [14330] = 1,
    ACTIONS(1826), 1,
      anon_sym_EQ,
  [14334] = 1,
    ACTIONS(1828), 1,
      anon_sym_LPAREN,
  [14338] = 1,
    ACTIONS(1830), 1,
      aux_sym_using_timestamp_spec_token3,
  [14342] = 1,
    ACTIONS(1832), 1,
      anon_sym_RPAREN,
  [14346] = 1,
    ACTIONS(1834), 1,
      aux_sym_using_timestamp_spec_token3,
  [14350] = 1,
    ACTIONS(1836), 1,
      aux_sym_column_not_null_token2,
  [14354] = 1,
    ACTIONS(128), 1,
      anon_sym_SQUOTE,
  [14358] = 1,
    ACTIONS(1838), 1,
      anon_sym_RPAREN,
  [14362] = 1,
    ACTIONS(1840), 1,
      aux_sym_delete_statement_token3,
  [14366] = 1,
    ACTIONS(1842), 1,
      anon_sym_RPAREN,
  [14370] = 1,
    ACTIONS(1844), 1,
      anon_sym_LPAREN,
  [14374] = 1,
    ACTIONS(1846), 1,
      anon_sym_RPAREN,
  [14378] = 1,
    ACTIONS(1848), 1,
      aux_sym_create_index_token3,
  [14382] = 1,
    ACTIONS(1850), 1,
      aux_sym_create_function_token1,
  [14386] = 1,
    ACTIONS(1852), 1,
      sym_object_name,
  [14390] = 1,
    ACTIONS(1854), 1,
      aux_sym_create_function_token2,
  [14394] = 1,
    ACTIONS(1856), 1,
      anon_sym_RPAREN,
  [14398] = 1,
    ACTIONS(1858), 1,
      aux_sym_create_function_token1,
  [14402] = 1,
    ACTIONS(1860), 1,
      sym__code_block,
  [14406] = 1,
    ACTIONS(1862), 1,
      aux_sym_create_materialized_view_token1,
  [14410] = 1,
    ACTIONS(1864), 1,
      sym_object_name,
  [14414] = 1,
    ACTIONS(1866), 1,
      aux_sym_create_aggregate_token4,
  [14418] = 1,
    ACTIONS(1868), 1,
      anon_sym_LPAREN,
  [14422] = 1,
    ACTIONS(1870), 1,
      aux_sym_delete_statement_token3,
  [14426] = 1,
    ACTIONS(877), 1,
      aux_sym_column_not_null_token1,
  [14430] = 1,
    ACTIONS(1872), 1,
      aux_sym_create_aggregate_token3,
  [14434] = 1,
    ACTIONS(1874), 1,
      sym_object_name,
  [14438] = 1,
    ACTIONS(1876), 1,
      aux_sym_delete_statement_token3,
  [14442] = 1,
    ACTIONS(1878), 1,
      sym_object_name,
  [14446] = 1,
    ACTIONS(1880), 1,
      aux_sym_create_aggregate_token3,
  [14450] = 1,
    ACTIONS(1882), 1,
      aux_sym_delete_statement_token3,
  [14454] = 1,
    ACTIONS(1884), 1,
      aux_sym_create_materialized_view_token1,
  [14458] = 1,
    ACTIONS(1886), 1,
      aux_sym_insert_statement_token3,
  [14462] = 1,
    ACTIONS(1888), 1,
      sym_object_name,
  [14466] = 1,
    ACTIONS(1890), 1,
      anon_sym_COMMA,
  [14470] = 1,
    ACTIONS(1892), 1,
      aux_sym_delete_statement_token3,
  [14474] = 1,
    ACTIONS(1894), 1,
      anon_sym_RPAREN,
  [14478] = 1,
    ACTIONS(1896), 1,
      aux_sym_select_statement_token5,
  [14482] = 1,
    ACTIONS(1898), 1,
      sym_object_name,
  [14486] = 1,
    ACTIONS(1900), 1,
      aux_sym_create_function_token2,
  [14490] = 1,
    ACTIONS(1902), 1,
      aux_sym_delete_statement_token3,
  [14494] = 1,
    ACTIONS(1904), 1,
      aux_sym_create_keyspace_token2,
  [14498] = 1,
    ACTIONS(1906), 1,
      sym__code_block,
  [14502] = 1,
    ACTIONS(1908), 1,
      aux_sym_create_materialized_view_token1,
  [14506] = 1,
    ACTIONS(1910), 1,
      aux_sym_delete_statement_token3,
  [14510] = 1,
    ACTIONS(1912), 1,
      aux_sym_create_aggregate_token6,
  [14514] = 1,
    ACTIONS(1914), 1,
      aux_sym_using_timestamp_spec_token1,
  [14518] = 1,
    ACTIONS(1916), 1,
      aux_sym_insert_statement_token3,
  [14522] = 1,
    ACTIONS(1918), 1,
      aux_sym_insert_statement_token3,
  [14526] = 1,
    ACTIONS(1920), 1,
      anon_sym_LPAREN,
  [14530] = 1,
    ACTIONS(1922), 1,
      aux_sym_delete_statement_token3,
  [14534] = 1,
    ACTIONS(1924), 1,
      sym_double_dollar,
  [14538] = 1,
    ACTIONS(1926), 1,
      aux_sym_create_function_token1,
  [14542] = 1,
    ACTIONS(1928), 1,
      aux_sym_delete_statement_token3,
  [14546] = 1,
    ACTIONS(1930), 1,
      aux_sym_relation_contains_key_token2,
  [14550] = 1,
    ACTIONS(1932), 1,
      aux_sym_create_aggregate_token5,
  [14554] = 1,
    ACTIONS(1934), 1,
      aux_sym_delete_statement_token3,
  [14558] = 1,
    ACTIONS(1936), 1,
      anon_sym_LPAREN,
  [14562] = 1,
    ACTIONS(1938), 1,
      aux_sym_create_materialized_view_token1,
  [14566] = 1,
    ACTIONS(1940), 1,
      sym_object_name,
  [14570] = 1,
    ACTIONS(1942), 1,
      aux_sym_create_function_token2,
  [14574] = 1,
    ACTIONS(1944), 1,
      aux_sym_delete_statement_token3,
  [14578] = 1,
    ACTIONS(1946), 1,
      sym__code_block,
  [14582] = 1,
    ACTIONS(1948), 1,
      aux_sym_create_aggregate_token5,
  [14586] = 1,
    ACTIONS(1950), 1,
      aux_sym_using_timestamp_spec_token3,
  [14590] = 1,
    ACTIONS(1952), 1,
      aux_sym_using_ttl_timestamp_token1,
  [14594] = 1,
    ACTIONS(1954), 1,
      aux_sym_column_not_null_token2,
  [14598] = 1,
    ACTIONS(1956), 1,
      anon_sym_LPAREN,
  [14602] = 1,
    ACTIONS(1958), 1,
      aux_sym_select_statement_token5,
  [14606] = 1,
    ACTIONS(1960), 1,
      sym_object_name,
  [14610] = 1,
    ACTIONS(1962), 1,
      anon_sym_RBRACK,
  [14614] = 1,
    ACTIONS(1964), 1,
      aux_sym_using_timestamp_spec_token2,
  [14618] = 1,
    ACTIONS(1966), 1,
      aux_sym_create_function_token1,
  [14622] = 1,
    ACTIONS(1968), 1,
      aux_sym_create_aggregate_token4,
  [14626] = 1,
    ACTIONS(1970), 1,
      anon_sym_RBRACK,
  [14630] = 1,
    ACTIONS(1972), 1,
      anon_sym_RPAREN,
  [14634] = 1,
    ACTIONS(1974), 1,
      sym__code_block,
  [14638] = 1,
    ACTIONS(1976), 1,
      aux_sym_create_materialized_view_token1,
  [14642] = 1,
    ACTIONS(1978), 1,
      sym_object_name,
  [14646] = 1,
    ACTIONS(1980), 1,
      aux_sym_order_spec_token2,
  [14650] = 1,
    ACTIONS(1982), 1,
      aux_sym_select_statement_token5,
  [14654] = 1,
    ACTIONS(1984), 1,
      sym_object_name,
  [14658] = 1,
    ACTIONS(1986), 1,
      aux_sym_insert_statement_token3,
  [14662] = 1,
    ACTIONS(1988), 1,
      sym_object_name,
  [14666] = 1,
    ACTIONS(1990), 1,
      aux_sym_resource_token2,
  [14670] = 1,
    ACTIONS(1992), 1,
      sym_object_name,
  [14674] = 1,
    ACTIONS(1994), 1,
      sym_object_name,
  [14678] = 1,
    ACTIONS(1996), 1,
      aux_sym_create_function_token2,
  [14682] = 1,
    ACTIONS(1998), 1,
      sym_object_name,
  [14686] = 1,
    ACTIONS(2000), 1,
      sym_object_name,
  [14690] = 1,
    ACTIONS(2002), 1,
      aux_sym_create_aggregate_token6,
  [14694] = 1,
    ACTIONS(2004), 1,
      aux_sym_order_spec_token2,
  [14698] = 1,
    ACTIONS(2006), 1,
      sym__code_block,
  [14702] = 1,
    ACTIONS(2008), 1,
      aux_sym_create_materialized_view_token1,
  [14706] = 1,
    ACTIONS(2010), 1,
      aux_sym_create_aggregate_token6,
  [14710] = 1,
    ACTIONS(2012), 1,
      sym_object_name,
  [14714] = 1,
    ACTIONS(2014), 1,
      anon_sym_COLON,
  [14718] = 1,
    ACTIONS(2016), 1,
      aux_sym_create_keyspace_token1,
  [14722] = 1,
    ACTIONS(2018), 1,
      sym_object_name,
  [14726] = 1,
    ACTIONS(2020), 1,
      anon_sym_LPAREN,
  [14730] = 1,
    ACTIONS(2022), 1,
      aux_sym_select_statement_token5,
  [14734] = 1,
    ACTIONS(2024), 1,
      sym_object_name,
  [14738] = 1,
    ACTIONS(2026), 1,
      aux_sym_create_function_token2,
  [14742] = 1,
    ACTIONS(2028), 1,
      aux_sym_create_aggregate_token5,
  [14746] = 1,
    ACTIONS(2030), 1,
      aux_sym_delete_statement_token3,
  [14750] = 1,
    ACTIONS(2032), 1,
      aux_sym_delete_statement_token3,
  [14754] = 1,
    ACTIONS(2034), 1,
      sym__code_block,
  [14758] = 1,
    ACTIONS(2036), 1,
      aux_sym_create_index_token3,
  [14762] = 1,
    ACTIONS(2038), 1,
      aux_sym_delete_statement_token3,
  [14766] = 1,
    ACTIONS(2040), 1,
      aux_sym_delete_statement_token3,
  [14770] = 1,
    ACTIONS(2042), 1,
      aux_sym_delete_statement_token3,
  [14774] = 1,
    ACTIONS(2044), 1,
      aux_sym_delete_statement_token3,
  [14778] = 1,
    ACTIONS(2046), 1,
      aux_sym_delete_statement_token3,
  [14782] = 1,
    ACTIONS(2048), 1,
      aux_sym_delete_statement_token3,
  [14786] = 1,
    ACTIONS(2050), 1,
      aux_sym_delete_statement_token3,
  [14790] = 1,
    ACTIONS(2052), 1,
      anon_sym_LPAREN,
  [14794] = 1,
    ACTIONS(2054), 1,
      sym_object_name,
  [14798] = 1,
    ACTIONS(2056), 1,
      anon_sym_RPAREN,
  [14802] = 1,
    ACTIONS(2058), 1,
      aux_sym_create_materialized_view_token1,
  [14806] = 1,
    ACTIONS(2060), 1,
      sym_object_name,
  [14810] = 1,
    ACTIONS(2062), 1,
      aux_sym_insert_statement_token3,
  [14814] = 1,
    ACTIONS(2064), 1,
      anon_sym_LPAREN,
  [14818] = 1,
    ACTIONS(2066), 1,
      aux_sym_insert_statement_token2,
  [14822] = 1,
    ACTIONS(2068), 1,
      aux_sym_using_timestamp_spec_token1,
  [14826] = 1,
    ACTIONS(2070), 1,
      sym_object_name,
  [14830] = 1,
    ACTIONS(2072), 1,
      anon_sym_RPAREN,
  [14834] = 1,
    ACTIONS(2074), 1,
      aux_sym_insert_statement_token3,
  [14838] = 1,
    ACTIONS(2076), 1,
      anon_sym_LPAREN,
  [14842] = 1,
    ACTIONS(2078), 1,
      anon_sym_COLON,
  [14846] = 1,
    ACTIONS(2080), 1,
      aux_sym_insert_statement_token3,
  [14850] = 1,
    ACTIONS(2082), 1,
      aux_sym_insert_statement_token3,
  [14854] = 1,
    ACTIONS(2084), 1,
      aux_sym_scientific_notation_token1,
  [14858] = 1,
    ACTIONS(2086), 1,
      anon_sym_LPAREN,
  [14862] = 1,
    ACTIONS(2088), 1,
      aux_sym_insert_statement_token3,
  [14866] = 1,
    ACTIONS(2090), 1,
      sym__code_block,
  [14870] = 1,
    ACTIONS(2092), 1,
      aux_sym_create_materialized_view_token1,
  [14874] = 1,
    ACTIONS(2094), 1,
      aux_sym_create_aggregate_token6,
  [14878] = 1,
    ACTIONS(2096), 1,
      aux_sym_create_keyspace_token1,
  [14882] = 1,
    ACTIONS(2098), 1,
      sym__code_block,
  [14886] = 1,
    ACTIONS(2100), 1,
      aux_sym_insert_statement_token3,
  [14890] = 1,
    ACTIONS(2102), 1,
      aux_sym_create_index_token3,
  [14894] = 1,
    ACTIONS(2104), 1,
      aux_sym_create_index_token3,
  [14898] = 1,
    ACTIONS(2106), 1,
      aux_sym_insert_statement_token3,
  [14902] = 1,
    ACTIONS(2108), 1,
      aux_sym_string_literal_token2,
  [14906] = 1,
    ACTIONS(2110), 1,
      anon_sym_EQ,
  [14910] = 1,
    ACTIONS(2112), 1,
      anon_sym_LPAREN,
  [14914] = 1,
    ACTIONS(2114), 1,
      aux_sym_insert_statement_token3,
  [14918] = 1,
    ACTIONS(2116), 1,
      aux_sym_using_timestamp_spec_token3,
  [14922] = 1,
    ACTIONS(2118), 1,
      aux_sym_using_timestamp_spec_token3,
  [14926] = 1,
    ACTIONS(2120), 1,
      anon_sym_RPAREN,
  [14930] = 1,
    ACTIONS(2122), 1,
      aux_sym_using_timestamp_spec_token2,
  [14934] = 1,
    ACTIONS(2124), 1,
      aux_sym_from_spec_token1,
  [14938] = 1,
    ACTIONS(2126), 1,
      aux_sym_create_materialized_view_token1,
  [14942] = 1,
    ACTIONS(204), 1,
      anon_sym_DQUOTE,
  [14946] = 1,
    ACTIONS(2128), 1,
      aux_sym_create_function_token1,
  [14950] = 1,
    ACTIONS(2130), 1,
      aux_sym_insert_statement_token2,
  [14954] = 1,
    ACTIONS(2132), 1,
      aux_sym_column_not_null_token2,
  [14958] = 1,
    ACTIONS(2134), 1,
      aux_sym_create_index_token3,
  [14962] = 1,
    ACTIONS(2136), 1,
      aux_sym_drop_materialized_view_token2,
  [14966] = 1,
    ACTIONS(2138), 1,
      aux_sym_create_keyspace_token2,
  [14970] = 1,
    ACTIONS(2140), 1,
      anon_sym_RPAREN,
  [14974] = 1,
    ACTIONS(2142), 1,
      aux_sym_create_index_token3,
  [14978] = 1,
    ACTIONS(2144), 1,
      aux_sym_create_index_token3,
  [14982] = 1,
    ACTIONS(2146), 1,
      aux_sym_drop_materialized_view_token2,
  [14986] = 1,
    ACTIONS(2148), 1,
      aux_sym_create_aggregate_token2,
  [14990] = 1,
    ACTIONS(2150), 1,
      aux_sym_drop_materialized_view_token2,
  [14994] = 1,
    ACTIONS(2152), 1,
      aux_sym_begin_batch_token5,
  [14998] = 1,
    ACTIONS(2154), 1,
      sym_object_name,
  [15002] = 1,
    ACTIONS(2156), 1,
      sym_object_name,
  [15006] = 1,
    ACTIONS(2158), 1,
      sym_object_name,
  [15010] = 1,
    ACTIONS(2160), 1,
      anon_sym_LPAREN,
  [15014] = 1,
    ACTIONS(1199), 1,
      aux_sym_from_spec_token1,
  [15018] = 1,
    ACTIONS(2162), 1,
      anon_sym_RPAREN,
  [15022] = 1,
    ACTIONS(2164), 1,
      ts_builtin_sym_end,
  [15026] = 1,
    ACTIONS(2166), 1,
      aux_sym_begin_batch_token5,
  [15030] = 1,
    ACTIONS(2168), 1,
      sym_object_name,
  [15034] = 1,
    ACTIONS(2170), 1,
      aux_sym_relation_contains_key_token2,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 92,
  [SMALL_STATE(4)] = 184,
  [SMALL_STATE(5)] = 224,
  [SMALL_STATE(6)] = 266,
  [SMALL_STATE(7)] = 352,
  [SMALL_STATE(8)] = 394,
  [SMALL_STATE(9)] = 436,
  [SMALL_STATE(10)] = 522,
  [SMALL_STATE(11)] = 568,
  [SMALL_STATE(12)] = 606,
  [SMALL_STATE(13)] = 646,
  [SMALL_STATE(14)] = 729,
  [SMALL_STATE(15)] = 770,
  [SMALL_STATE(16)] = 853,
  [SMALL_STATE(17)] = 890,
  [SMALL_STATE(18)] = 973,
  [SMALL_STATE(19)] = 1053,
  [SMALL_STATE(20)] = 1133,
  [SMALL_STATE(21)] = 1213,
  [SMALL_STATE(22)] = 1253,
  [SMALL_STATE(23)] = 1293,
  [SMALL_STATE(24)] = 1373,
  [SMALL_STATE(25)] = 1413,
  [SMALL_STATE(26)] = 1493,
  [SMALL_STATE(27)] = 1573,
  [SMALL_STATE(28)] = 1610,
  [SMALL_STATE(29)] = 1687,
  [SMALL_STATE(30)] = 1762,
  [SMALL_STATE(31)] = 1837,
  [SMALL_STATE(32)] = 1871,
  [SMALL_STATE(33)] = 1943,
  [SMALL_STATE(34)] = 1977,
  [SMALL_STATE(35)] = 2011,
  [SMALL_STATE(36)] = 2043,
  [SMALL_STATE(37)] = 2075,
  [SMALL_STATE(38)] = 2110,
  [SMALL_STATE(39)] = 2145,
  [SMALL_STATE(40)] = 2180,
  [SMALL_STATE(41)] = 2215,
  [SMALL_STATE(42)] = 2250,
  [SMALL_STATE(43)] = 2285,
  [SMALL_STATE(44)] = 2320,
  [SMALL_STATE(45)] = 2355,
  [SMALL_STATE(46)] = 2390,
  [SMALL_STATE(47)] = 2425,
  [SMALL_STATE(48)] = 2460,
  [SMALL_STATE(49)] = 2495,
  [SMALL_STATE(50)] = 2530,
  [SMALL_STATE(51)] = 2565,
  [SMALL_STATE(52)] = 2600,
  [SMALL_STATE(53)] = 2635,
  [SMALL_STATE(54)] = 2670,
  [SMALL_STATE(55)] = 2705,
  [SMALL_STATE(56)] = 2740,
  [SMALL_STATE(57)] = 2772,
  [SMALL_STATE(58)] = 2804,
  [SMALL_STATE(59)] = 2867,
  [SMALL_STATE(60)] = 2925,
  [SMALL_STATE(61)] = 2983,
  [SMALL_STATE(62)] = 3041,
  [SMALL_STATE(63)] = 3099,
  [SMALL_STATE(64)] = 3131,
  [SMALL_STATE(65)] = 3189,
  [SMALL_STATE(66)] = 3246,
  [SMALL_STATE(67)] = 3277,
  [SMALL_STATE(68)] = 3338,
  [SMALL_STATE(69)] = 3369,
  [SMALL_STATE(70)] = 3400,
  [SMALL_STATE(71)] = 3431,
  [SMALL_STATE(72)] = 3458,
  [SMALL_STATE(73)] = 3485,
  [SMALL_STATE(74)] = 3515,
  [SMALL_STATE(75)] = 3545,
  [SMALL_STATE(76)] = 3571,
  [SMALL_STATE(77)] = 3596,
  [SMALL_STATE(78)] = 3621,
  [SMALL_STATE(79)] = 3646,
  [SMALL_STATE(80)] = 3671,
  [SMALL_STATE(81)] = 3724,
  [SMALL_STATE(82)] = 3753,
  [SMALL_STATE(83)] = 3780,
  [SMALL_STATE(84)] = 3805,
  [SMALL_STATE(85)] = 3830,
  [SMALL_STATE(86)] = 3859,
  [SMALL_STATE(87)] = 3884,
  [SMALL_STATE(88)] = 3909,
  [SMALL_STATE(89)] = 3934,
  [SMALL_STATE(90)] = 3959,
  [SMALL_STATE(91)] = 3984,
  [SMALL_STATE(92)] = 4008,
  [SMALL_STATE(93)] = 4032,
  [SMALL_STATE(94)] = 4084,
  [SMALL_STATE(95)] = 4108,
  [SMALL_STATE(96)] = 4132,
  [SMALL_STATE(97)] = 4161,
  [SMALL_STATE(98)] = 4186,
  [SMALL_STATE(99)] = 4215,
  [SMALL_STATE(100)] = 4240,
  [SMALL_STATE(101)] = 4269,
  [SMALL_STATE(102)] = 4318,
  [SMALL_STATE(103)] = 4367,
  [SMALL_STATE(104)] = 4392,
  [SMALL_STATE(105)] = 4441,
  [SMALL_STATE(106)] = 4464,
  [SMALL_STATE(107)] = 4513,
  [SMALL_STATE(108)] = 4542,
  [SMALL_STATE(109)] = 4567,
  [SMALL_STATE(110)] = 4592,
  [SMALL_STATE(111)] = 4621,
  [SMALL_STATE(112)] = 4670,
  [SMALL_STATE(113)] = 4692,
  [SMALL_STATE(114)] = 4720,
  [SMALL_STATE(115)] = 4742,
  [SMALL_STATE(116)] = 4764,
  [SMALL_STATE(117)] = 4792,
  [SMALL_STATE(118)] = 4818,
  [SMALL_STATE(119)] = 4842,
  [SMALL_STATE(120)] = 4864,
  [SMALL_STATE(121)] = 4890,
  [SMALL_STATE(122)] = 4912,
  [SMALL_STATE(123)] = 4936,
  [SMALL_STATE(124)] = 4958,
  [SMALL_STATE(125)] = 4980,
  [SMALL_STATE(126)] = 5006,
  [SMALL_STATE(127)] = 5028,
  [SMALL_STATE(128)] = 5050,
  [SMALL_STATE(129)] = 5075,
  [SMALL_STATE(130)] = 5100,
  [SMALL_STATE(131)] = 5123,
  [SMALL_STATE(132)] = 5148,
  [SMALL_STATE(133)] = 5173,
  [SMALL_STATE(134)] = 5194,
  [SMALL_STATE(135)] = 5217,
  [SMALL_STATE(136)] = 5238,
  [SMALL_STATE(137)] = 5259,
  [SMALL_STATE(138)] = 5284,
  [SMALL_STATE(139)] = 5305,
  [SMALL_STATE(140)] = 5326,
  [SMALL_STATE(141)] = 5347,
  [SMALL_STATE(142)] = 5368,
  [SMALL_STATE(143)] = 5389,
  [SMALL_STATE(144)] = 5414,
  [SMALL_STATE(145)] = 5439,
  [SMALL_STATE(146)] = 5464,
  [SMALL_STATE(147)] = 5489,
  [SMALL_STATE(148)] = 5510,
  [SMALL_STATE(149)] = 5535,
  [SMALL_STATE(150)] = 5560,
  [SMALL_STATE(151)] = 5585,
  [SMALL_STATE(152)] = 5610,
  [SMALL_STATE(153)] = 5635,
  [SMALL_STATE(154)] = 5660,
  [SMALL_STATE(155)] = 5685,
  [SMALL_STATE(156)] = 5710,
  [SMALL_STATE(157)] = 5735,
  [SMALL_STATE(158)] = 5760,
  [SMALL_STATE(159)] = 5781,
  [SMALL_STATE(160)] = 5806,
  [SMALL_STATE(161)] = 5831,
  [SMALL_STATE(162)] = 5856,
  [SMALL_STATE(163)] = 5881,
  [SMALL_STATE(164)] = 5906,
  [SMALL_STATE(165)] = 5927,
  [SMALL_STATE(166)] = 5952,
  [SMALL_STATE(167)] = 5977,
  [SMALL_STATE(168)] = 6002,
  [SMALL_STATE(169)] = 6027,
  [SMALL_STATE(170)] = 6052,
  [SMALL_STATE(171)] = 6075,
  [SMALL_STATE(172)] = 6096,
  [SMALL_STATE(173)] = 6117,
  [SMALL_STATE(174)] = 6142,
  [SMALL_STATE(175)] = 6163,
  [SMALL_STATE(176)] = 6184,
  [SMALL_STATE(177)] = 6209,
  [SMALL_STATE(178)] = 6234,
  [SMALL_STATE(179)] = 6259,
  [SMALL_STATE(180)] = 6284,
  [SMALL_STATE(181)] = 6305,
  [SMALL_STATE(182)] = 6326,
  [SMALL_STATE(183)] = 6347,
  [SMALL_STATE(184)] = 6369,
  [SMALL_STATE(185)] = 6391,
  [SMALL_STATE(186)] = 6413,
  [SMALL_STATE(187)] = 6435,
  [SMALL_STATE(188)] = 6455,
  [SMALL_STATE(189)] = 6475,
  [SMALL_STATE(190)] = 6495,
  [SMALL_STATE(191)] = 6515,
  [SMALL_STATE(192)] = 6535,
  [SMALL_STATE(193)] = 6555,
  [SMALL_STATE(194)] = 6575,
  [SMALL_STATE(195)] = 6597,
  [SMALL_STATE(196)] = 6617,
  [SMALL_STATE(197)] = 6637,
  [SMALL_STATE(198)] = 6657,
  [SMALL_STATE(199)] = 6677,
  [SMALL_STATE(200)] = 6697,
  [SMALL_STATE(201)] = 6717,
  [SMALL_STATE(202)] = 6737,
  [SMALL_STATE(203)] = 6757,
  [SMALL_STATE(204)] = 6777,
  [SMALL_STATE(205)] = 6797,
  [SMALL_STATE(206)] = 6817,
  [SMALL_STATE(207)] = 6839,
  [SMALL_STATE(208)] = 6859,
  [SMALL_STATE(209)] = 6879,
  [SMALL_STATE(210)] = 6899,
  [SMALL_STATE(211)] = 6919,
  [SMALL_STATE(212)] = 6938,
  [SMALL_STATE(213)] = 6957,
  [SMALL_STATE(214)] = 6976,
  [SMALL_STATE(215)] = 6995,
  [SMALL_STATE(216)] = 7014,
  [SMALL_STATE(217)] = 7033,
  [SMALL_STATE(218)] = 7052,
  [SMALL_STATE(219)] = 7071,
  [SMALL_STATE(220)] = 7090,
  [SMALL_STATE(221)] = 7109,
  [SMALL_STATE(222)] = 7130,
  [SMALL_STATE(223)] = 7149,
  [SMALL_STATE(224)] = 7168,
  [SMALL_STATE(225)] = 7187,
  [SMALL_STATE(226)] = 7206,
  [SMALL_STATE(227)] = 7247,
  [SMALL_STATE(228)] = 7266,
  [SMALL_STATE(229)] = 7285,
  [SMALL_STATE(230)] = 7304,
  [SMALL_STATE(231)] = 7323,
  [SMALL_STATE(232)] = 7342,
  [SMALL_STATE(233)] = 7361,
  [SMALL_STATE(234)] = 7380,
  [SMALL_STATE(235)] = 7399,
  [SMALL_STATE(236)] = 7418,
  [SMALL_STATE(237)] = 7437,
  [SMALL_STATE(238)] = 7456,
  [SMALL_STATE(239)] = 7475,
  [SMALL_STATE(240)] = 7494,
  [SMALL_STATE(241)] = 7513,
  [SMALL_STATE(242)] = 7532,
  [SMALL_STATE(243)] = 7551,
  [SMALL_STATE(244)] = 7570,
  [SMALL_STATE(245)] = 7589,
  [SMALL_STATE(246)] = 7608,
  [SMALL_STATE(247)] = 7627,
  [SMALL_STATE(248)] = 7646,
  [SMALL_STATE(249)] = 7665,
  [SMALL_STATE(250)] = 7684,
  [SMALL_STATE(251)] = 7703,
  [SMALL_STATE(252)] = 7722,
  [SMALL_STATE(253)] = 7741,
  [SMALL_STATE(254)] = 7760,
  [SMALL_STATE(255)] = 7779,
  [SMALL_STATE(256)] = 7798,
  [SMALL_STATE(257)] = 7817,
  [SMALL_STATE(258)] = 7836,
  [SMALL_STATE(259)] = 7855,
  [SMALL_STATE(260)] = 7874,
  [SMALL_STATE(261)] = 7893,
  [SMALL_STATE(262)] = 7912,
  [SMALL_STATE(263)] = 7931,
  [SMALL_STATE(264)] = 7950,
  [SMALL_STATE(265)] = 7969,
  [SMALL_STATE(266)] = 7988,
  [SMALL_STATE(267)] = 8007,
  [SMALL_STATE(268)] = 8026,
  [SMALL_STATE(269)] = 8045,
  [SMALL_STATE(270)] = 8064,
  [SMALL_STATE(271)] = 8083,
  [SMALL_STATE(272)] = 8102,
  [SMALL_STATE(273)] = 8121,
  [SMALL_STATE(274)] = 8140,
  [SMALL_STATE(275)] = 8159,
  [SMALL_STATE(276)] = 8178,
  [SMALL_STATE(277)] = 8197,
  [SMALL_STATE(278)] = 8216,
  [SMALL_STATE(279)] = 8235,
  [SMALL_STATE(280)] = 8254,
  [SMALL_STATE(281)] = 8273,
  [SMALL_STATE(282)] = 8292,
  [SMALL_STATE(283)] = 8311,
  [SMALL_STATE(284)] = 8330,
  [SMALL_STATE(285)] = 8349,
  [SMALL_STATE(286)] = 8368,
  [SMALL_STATE(287)] = 8387,
  [SMALL_STATE(288)] = 8406,
  [SMALL_STATE(289)] = 8425,
  [SMALL_STATE(290)] = 8444,
  [SMALL_STATE(291)] = 8463,
  [SMALL_STATE(292)] = 8482,
  [SMALL_STATE(293)] = 8501,
  [SMALL_STATE(294)] = 8520,
  [SMALL_STATE(295)] = 8539,
  [SMALL_STATE(296)] = 8558,
  [SMALL_STATE(297)] = 8577,
  [SMALL_STATE(298)] = 8596,
  [SMALL_STATE(299)] = 8615,
  [SMALL_STATE(300)] = 8634,
  [SMALL_STATE(301)] = 8653,
  [SMALL_STATE(302)] = 8672,
  [SMALL_STATE(303)] = 8691,
  [SMALL_STATE(304)] = 8710,
  [SMALL_STATE(305)] = 8729,
  [SMALL_STATE(306)] = 8748,
  [SMALL_STATE(307)] = 8767,
  [SMALL_STATE(308)] = 8786,
  [SMALL_STATE(309)] = 8805,
  [SMALL_STATE(310)] = 8824,
  [SMALL_STATE(311)] = 8843,
  [SMALL_STATE(312)] = 8862,
  [SMALL_STATE(313)] = 8881,
  [SMALL_STATE(314)] = 8900,
  [SMALL_STATE(315)] = 8919,
  [SMALL_STATE(316)] = 8961,
  [SMALL_STATE(317)] = 9003,
  [SMALL_STATE(318)] = 9045,
  [SMALL_STATE(319)] = 9087,
  [SMALL_STATE(320)] = 9105,
  [SMALL_STATE(321)] = 9125,
  [SMALL_STATE(322)] = 9167,
  [SMALL_STATE(323)] = 9209,
  [SMALL_STATE(324)] = 9251,
  [SMALL_STATE(325)] = 9290,
  [SMALL_STATE(326)] = 9329,
  [SMALL_STATE(327)] = 9365,
  [SMALL_STATE(328)] = 9399,
  [SMALL_STATE(329)] = 9434,
  [SMALL_STATE(330)] = 9454,
  [SMALL_STATE(331)] = 9488,
  [SMALL_STATE(332)] = 9520,
  [SMALL_STATE(333)] = 9549,
  [SMALL_STATE(334)] = 9578,
  [SMALL_STATE(335)] = 9601,
  [SMALL_STATE(336)] = 9632,
  [SMALL_STATE(337)] = 9649,
  [SMALL_STATE(338)] = 9666,
  [SMALL_STATE(339)] = 9684,
  [SMALL_STATE(340)] = 9712,
  [SMALL_STATE(341)] = 9740,
  [SMALL_STATE(342)] = 9758,
  [SMALL_STATE(343)] = 9782,
  [SMALL_STATE(344)] = 9810,
  [SMALL_STATE(345)] = 9828,
  [SMALL_STATE(346)] = 9848,
  [SMALL_STATE(347)] = 9871,
  [SMALL_STATE(348)] = 9892,
  [SMALL_STATE(349)] = 9915,
  [SMALL_STATE(350)] = 9932,
  [SMALL_STATE(351)] = 9955,
  [SMALL_STATE(352)] = 9978,
  [SMALL_STATE(353)] = 10003,
  [SMALL_STATE(354)] = 10026,
  [SMALL_STATE(355)] = 10047,
  [SMALL_STATE(356)] = 10068,
  [SMALL_STATE(357)] = 10085,
  [SMALL_STATE(358)] = 10106,
  [SMALL_STATE(359)] = 10123,
  [SMALL_STATE(360)] = 10140,
  [SMALL_STATE(361)] = 10161,
  [SMALL_STATE(362)] = 10184,
  [SMALL_STATE(363)] = 10202,
  [SMALL_STATE(364)] = 10222,
  [SMALL_STATE(365)] = 10236,
  [SMALL_STATE(366)] = 10258,
  [SMALL_STATE(367)] = 10278,
  [SMALL_STATE(368)] = 10300,
  [SMALL_STATE(369)] = 10322,
  [SMALL_STATE(370)] = 10332,
  [SMALL_STATE(371)] = 10352,
  [SMALL_STATE(372)] = 10366,
  [SMALL_STATE(373)] = 10388,
  [SMALL_STATE(374)] = 10398,
  [SMALL_STATE(375)] = 10418,
  [SMALL_STATE(376)] = 10438,
  [SMALL_STATE(377)] = 10458,
  [SMALL_STATE(378)] = 10470,
  [SMALL_STATE(379)] = 10490,
  [SMALL_STATE(380)] = 10512,
  [SMALL_STATE(381)] = 10532,
  [SMALL_STATE(382)] = 10554,
  [SMALL_STATE(383)] = 10574,
  [SMALL_STATE(384)] = 10592,
  [SMALL_STATE(385)] = 10612,
  [SMALL_STATE(386)] = 10632,
  [SMALL_STATE(387)] = 10654,
  [SMALL_STATE(388)] = 10665,
  [SMALL_STATE(389)] = 10684,
  [SMALL_STATE(390)] = 10703,
  [SMALL_STATE(391)] = 10718,
  [SMALL_STATE(392)] = 10727,
  [SMALL_STATE(393)] = 10742,
  [SMALL_STATE(394)] = 10761,
  [SMALL_STATE(395)] = 10770,
  [SMALL_STATE(396)] = 10785,
  [SMALL_STATE(397)] = 10804,
  [SMALL_STATE(398)] = 10819,
  [SMALL_STATE(399)] = 10828,
  [SMALL_STATE(400)] = 10843,
  [SMALL_STATE(401)] = 10858,
  [SMALL_STATE(402)] = 10873,
  [SMALL_STATE(403)] = 10888,
  [SMALL_STATE(404)] = 10903,
  [SMALL_STATE(405)] = 10917,
  [SMALL_STATE(406)] = 10933,
  [SMALL_STATE(407)] = 10945,
  [SMALL_STATE(408)] = 10961,
  [SMALL_STATE(409)] = 10973,
  [SMALL_STATE(410)] = 10987,
  [SMALL_STATE(411)] = 11001,
  [SMALL_STATE(412)] = 11017,
  [SMALL_STATE(413)] = 11033,
  [SMALL_STATE(414)] = 11047,
  [SMALL_STATE(415)] = 11059,
  [SMALL_STATE(416)] = 11071,
  [SMALL_STATE(417)] = 11085,
  [SMALL_STATE(418)] = 11101,
  [SMALL_STATE(419)] = 11115,
  [SMALL_STATE(420)] = 11129,
  [SMALL_STATE(421)] = 11141,
  [SMALL_STATE(422)] = 11155,
  [SMALL_STATE(423)] = 11171,
  [SMALL_STATE(424)] = 11187,
  [SMALL_STATE(425)] = 11199,
  [SMALL_STATE(426)] = 11213,
  [SMALL_STATE(427)] = 11227,
  [SMALL_STATE(428)] = 11241,
  [SMALL_STATE(429)] = 11253,
  [SMALL_STATE(430)] = 11269,
  [SMALL_STATE(431)] = 11283,
  [SMALL_STATE(432)] = 11299,
  [SMALL_STATE(433)] = 11315,
  [SMALL_STATE(434)] = 11325,
  [SMALL_STATE(435)] = 11341,
  [SMALL_STATE(436)] = 11355,
  [SMALL_STATE(437)] = 11371,
  [SMALL_STATE(438)] = 11387,
  [SMALL_STATE(439)] = 11401,
  [SMALL_STATE(440)] = 11415,
  [SMALL_STATE(441)] = 11429,
  [SMALL_STATE(442)] = 11445,
  [SMALL_STATE(443)] = 11461,
  [SMALL_STATE(444)] = 11472,
  [SMALL_STATE(445)] = 11485,
  [SMALL_STATE(446)] = 11492,
  [SMALL_STATE(447)] = 11501,
  [SMALL_STATE(448)] = 11514,
  [SMALL_STATE(449)] = 11527,
  [SMALL_STATE(450)] = 11538,
  [SMALL_STATE(451)] = 11551,
  [SMALL_STATE(452)] = 11562,
  [SMALL_STATE(453)] = 11575,
  [SMALL_STATE(454)] = 11588,
  [SMALL_STATE(455)] = 11601,
  [SMALL_STATE(456)] = 11612,
  [SMALL_STATE(457)] = 11625,
  [SMALL_STATE(458)] = 11636,
  [SMALL_STATE(459)] = 11649,
  [SMALL_STATE(460)] = 11662,
  [SMALL_STATE(461)] = 11675,
  [SMALL_STATE(462)] = 11688,
  [SMALL_STATE(463)] = 11701,
  [SMALL_STATE(464)] = 11714,
  [SMALL_STATE(465)] = 11727,
  [SMALL_STATE(466)] = 11740,
  [SMALL_STATE(467)] = 11753,
  [SMALL_STATE(468)] = 11766,
  [SMALL_STATE(469)] = 11779,
  [SMALL_STATE(470)] = 11786,
  [SMALL_STATE(471)] = 11799,
  [SMALL_STATE(472)] = 11812,
  [SMALL_STATE(473)] = 11825,
  [SMALL_STATE(474)] = 11832,
  [SMALL_STATE(475)] = 11839,
  [SMALL_STATE(476)] = 11850,
  [SMALL_STATE(477)] = 11863,
  [SMALL_STATE(478)] = 11873,
  [SMALL_STATE(479)] = 11883,
  [SMALL_STATE(480)] = 11893,
  [SMALL_STATE(481)] = 11903,
  [SMALL_STATE(482)] = 11913,
  [SMALL_STATE(483)] = 11923,
  [SMALL_STATE(484)] = 11933,
  [SMALL_STATE(485)] = 11943,
  [SMALL_STATE(486)] = 11953,
  [SMALL_STATE(487)] = 11963,
  [SMALL_STATE(488)] = 11973,
  [SMALL_STATE(489)] = 11983,
  [SMALL_STATE(490)] = 11993,
  [SMALL_STATE(491)] = 12003,
  [SMALL_STATE(492)] = 12013,
  [SMALL_STATE(493)] = 12023,
  [SMALL_STATE(494)] = 12033,
  [SMALL_STATE(495)] = 12041,
  [SMALL_STATE(496)] = 12049,
  [SMALL_STATE(497)] = 12059,
  [SMALL_STATE(498)] = 12069,
  [SMALL_STATE(499)] = 12079,
  [SMALL_STATE(500)] = 12089,
  [SMALL_STATE(501)] = 12099,
  [SMALL_STATE(502)] = 12109,
  [SMALL_STATE(503)] = 12119,
  [SMALL_STATE(504)] = 12129,
  [SMALL_STATE(505)] = 12139,
  [SMALL_STATE(506)] = 12149,
  [SMALL_STATE(507)] = 12159,
  [SMALL_STATE(508)] = 12169,
  [SMALL_STATE(509)] = 12179,
  [SMALL_STATE(510)] = 12189,
  [SMALL_STATE(511)] = 12199,
  [SMALL_STATE(512)] = 12209,
  [SMALL_STATE(513)] = 12219,
  [SMALL_STATE(514)] = 12229,
  [SMALL_STATE(515)] = 12237,
  [SMALL_STATE(516)] = 12247,
  [SMALL_STATE(517)] = 12257,
  [SMALL_STATE(518)] = 12265,
  [SMALL_STATE(519)] = 12275,
  [SMALL_STATE(520)] = 12285,
  [SMALL_STATE(521)] = 12295,
  [SMALL_STATE(522)] = 12303,
  [SMALL_STATE(523)] = 12313,
  [SMALL_STATE(524)] = 12321,
  [SMALL_STATE(525)] = 12329,
  [SMALL_STATE(526)] = 12339,
  [SMALL_STATE(527)] = 12347,
  [SMALL_STATE(528)] = 12357,
  [SMALL_STATE(529)] = 12365,
  [SMALL_STATE(530)] = 12375,
  [SMALL_STATE(531)] = 12385,
  [SMALL_STATE(532)] = 12395,
  [SMALL_STATE(533)] = 12405,
  [SMALL_STATE(534)] = 12415,
  [SMALL_STATE(535)] = 12423,
  [SMALL_STATE(536)] = 12431,
  [SMALL_STATE(537)] = 12441,
  [SMALL_STATE(538)] = 12451,
  [SMALL_STATE(539)] = 12457,
  [SMALL_STATE(540)] = 12465,
  [SMALL_STATE(541)] = 12473,
  [SMALL_STATE(542)] = 12483,
  [SMALL_STATE(543)] = 12491,
  [SMALL_STATE(544)] = 12501,
  [SMALL_STATE(545)] = 12509,
  [SMALL_STATE(546)] = 12517,
  [SMALL_STATE(547)] = 12527,
  [SMALL_STATE(548)] = 12537,
  [SMALL_STATE(549)] = 12543,
  [SMALL_STATE(550)] = 12551,
  [SMALL_STATE(551)] = 12561,
  [SMALL_STATE(552)] = 12571,
  [SMALL_STATE(553)] = 12581,
  [SMALL_STATE(554)] = 12591,
  [SMALL_STATE(555)] = 12601,
  [SMALL_STATE(556)] = 12611,
  [SMALL_STATE(557)] = 12617,
  [SMALL_STATE(558)] = 12623,
  [SMALL_STATE(559)] = 12633,
  [SMALL_STATE(560)] = 12643,
  [SMALL_STATE(561)] = 12653,
  [SMALL_STATE(562)] = 12663,
  [SMALL_STATE(563)] = 12673,
  [SMALL_STATE(564)] = 12683,
  [SMALL_STATE(565)] = 12693,
  [SMALL_STATE(566)] = 12703,
  [SMALL_STATE(567)] = 12713,
  [SMALL_STATE(568)] = 12723,
  [SMALL_STATE(569)] = 12733,
  [SMALL_STATE(570)] = 12743,
  [SMALL_STATE(571)] = 12753,
  [SMALL_STATE(572)] = 12763,
  [SMALL_STATE(573)] = 12773,
  [SMALL_STATE(574)] = 12783,
  [SMALL_STATE(575)] = 12793,
  [SMALL_STATE(576)] = 12801,
  [SMALL_STATE(577)] = 12811,
  [SMALL_STATE(578)] = 12821,
  [SMALL_STATE(579)] = 12831,
  [SMALL_STATE(580)] = 12841,
  [SMALL_STATE(581)] = 12851,
  [SMALL_STATE(582)] = 12861,
  [SMALL_STATE(583)] = 12869,
  [SMALL_STATE(584)] = 12879,
  [SMALL_STATE(585)] = 12887,
  [SMALL_STATE(586)] = 12897,
  [SMALL_STATE(587)] = 12907,
  [SMALL_STATE(588)] = 12917,
  [SMALL_STATE(589)] = 12925,
  [SMALL_STATE(590)] = 12933,
  [SMALL_STATE(591)] = 12941,
  [SMALL_STATE(592)] = 12951,
  [SMALL_STATE(593)] = 12961,
  [SMALL_STATE(594)] = 12969,
  [SMALL_STATE(595)] = 12979,
  [SMALL_STATE(596)] = 12989,
  [SMALL_STATE(597)] = 12999,
  [SMALL_STATE(598)] = 13009,
  [SMALL_STATE(599)] = 13019,
  [SMALL_STATE(600)] = 13029,
  [SMALL_STATE(601)] = 13039,
  [SMALL_STATE(602)] = 13047,
  [SMALL_STATE(603)] = 13057,
  [SMALL_STATE(604)] = 13065,
  [SMALL_STATE(605)] = 13075,
  [SMALL_STATE(606)] = 13085,
  [SMALL_STATE(607)] = 13095,
  [SMALL_STATE(608)] = 13102,
  [SMALL_STATE(609)] = 13109,
  [SMALL_STATE(610)] = 13116,
  [SMALL_STATE(611)] = 13121,
  [SMALL_STATE(612)] = 13128,
  [SMALL_STATE(613)] = 13133,
  [SMALL_STATE(614)] = 13138,
  [SMALL_STATE(615)] = 13143,
  [SMALL_STATE(616)] = 13150,
  [SMALL_STATE(617)] = 13157,
  [SMALL_STATE(618)] = 13164,
  [SMALL_STATE(619)] = 13171,
  [SMALL_STATE(620)] = 13178,
  [SMALL_STATE(621)] = 13185,
  [SMALL_STATE(622)] = 13192,
  [SMALL_STATE(623)] = 13197,
  [SMALL_STATE(624)] = 13204,
  [SMALL_STATE(625)] = 13211,
  [SMALL_STATE(626)] = 13218,
  [SMALL_STATE(627)] = 13225,
  [SMALL_STATE(628)] = 13232,
  [SMALL_STATE(629)] = 13239,
  [SMALL_STATE(630)] = 13246,
  [SMALL_STATE(631)] = 13251,
  [SMALL_STATE(632)] = 13256,
  [SMALL_STATE(633)] = 13261,
  [SMALL_STATE(634)] = 13268,
  [SMALL_STATE(635)] = 13273,
  [SMALL_STATE(636)] = 13278,
  [SMALL_STATE(637)] = 13285,
  [SMALL_STATE(638)] = 13292,
  [SMALL_STATE(639)] = 13299,
  [SMALL_STATE(640)] = 13306,
  [SMALL_STATE(641)] = 13313,
  [SMALL_STATE(642)] = 13320,
  [SMALL_STATE(643)] = 13327,
  [SMALL_STATE(644)] = 13334,
  [SMALL_STATE(645)] = 13341,
  [SMALL_STATE(646)] = 13348,
  [SMALL_STATE(647)] = 13355,
  [SMALL_STATE(648)] = 13362,
  [SMALL_STATE(649)] = 13369,
  [SMALL_STATE(650)] = 13376,
  [SMALL_STATE(651)] = 13381,
  [SMALL_STATE(652)] = 13388,
  [SMALL_STATE(653)] = 13395,
  [SMALL_STATE(654)] = 13402,
  [SMALL_STATE(655)] = 13407,
  [SMALL_STATE(656)] = 13412,
  [SMALL_STATE(657)] = 13417,
  [SMALL_STATE(658)] = 13422,
  [SMALL_STATE(659)] = 13429,
  [SMALL_STATE(660)] = 13434,
  [SMALL_STATE(661)] = 13441,
  [SMALL_STATE(662)] = 13448,
  [SMALL_STATE(663)] = 13455,
  [SMALL_STATE(664)] = 13460,
  [SMALL_STATE(665)] = 13467,
  [SMALL_STATE(666)] = 13474,
  [SMALL_STATE(667)] = 13481,
  [SMALL_STATE(668)] = 13488,
  [SMALL_STATE(669)] = 13495,
  [SMALL_STATE(670)] = 13502,
  [SMALL_STATE(671)] = 13509,
  [SMALL_STATE(672)] = 13516,
  [SMALL_STATE(673)] = 13523,
  [SMALL_STATE(674)] = 13530,
  [SMALL_STATE(675)] = 13537,
  [SMALL_STATE(676)] = 13544,
  [SMALL_STATE(677)] = 13551,
  [SMALL_STATE(678)] = 13558,
  [SMALL_STATE(679)] = 13565,
  [SMALL_STATE(680)] = 13572,
  [SMALL_STATE(681)] = 13579,
  [SMALL_STATE(682)] = 13586,
  [SMALL_STATE(683)] = 13591,
  [SMALL_STATE(684)] = 13598,
  [SMALL_STATE(685)] = 13605,
  [SMALL_STATE(686)] = 13612,
  [SMALL_STATE(687)] = 13619,
  [SMALL_STATE(688)] = 13626,
  [SMALL_STATE(689)] = 13633,
  [SMALL_STATE(690)] = 13640,
  [SMALL_STATE(691)] = 13645,
  [SMALL_STATE(692)] = 13650,
  [SMALL_STATE(693)] = 13657,
  [SMALL_STATE(694)] = 13664,
  [SMALL_STATE(695)] = 13671,
  [SMALL_STATE(696)] = 13678,
  [SMALL_STATE(697)] = 13683,
  [SMALL_STATE(698)] = 13688,
  [SMALL_STATE(699)] = 13695,
  [SMALL_STATE(700)] = 13702,
  [SMALL_STATE(701)] = 13709,
  [SMALL_STATE(702)] = 13716,
  [SMALL_STATE(703)] = 13723,
  [SMALL_STATE(704)] = 13730,
  [SMALL_STATE(705)] = 13737,
  [SMALL_STATE(706)] = 13742,
  [SMALL_STATE(707)] = 13747,
  [SMALL_STATE(708)] = 13754,
  [SMALL_STATE(709)] = 13761,
  [SMALL_STATE(710)] = 13766,
  [SMALL_STATE(711)] = 13773,
  [SMALL_STATE(712)] = 13780,
  [SMALL_STATE(713)] = 13787,
  [SMALL_STATE(714)] = 13794,
  [SMALL_STATE(715)] = 13801,
  [SMALL_STATE(716)] = 13806,
  [SMALL_STATE(717)] = 13811,
  [SMALL_STATE(718)] = 13818,
  [SMALL_STATE(719)] = 13823,
  [SMALL_STATE(720)] = 13830,
  [SMALL_STATE(721)] = 13837,
  [SMALL_STATE(722)] = 13844,
  [SMALL_STATE(723)] = 13851,
  [SMALL_STATE(724)] = 13858,
  [SMALL_STATE(725)] = 13863,
  [SMALL_STATE(726)] = 13868,
  [SMALL_STATE(727)] = 13875,
  [SMALL_STATE(728)] = 13882,
  [SMALL_STATE(729)] = 13889,
  [SMALL_STATE(730)] = 13896,
  [SMALL_STATE(731)] = 13901,
  [SMALL_STATE(732)] = 13908,
  [SMALL_STATE(733)] = 13915,
  [SMALL_STATE(734)] = 13922,
  [SMALL_STATE(735)] = 13926,
  [SMALL_STATE(736)] = 13930,
  [SMALL_STATE(737)] = 13934,
  [SMALL_STATE(738)] = 13938,
  [SMALL_STATE(739)] = 13942,
  [SMALL_STATE(740)] = 13946,
  [SMALL_STATE(741)] = 13950,
  [SMALL_STATE(742)] = 13954,
  [SMALL_STATE(743)] = 13958,
  [SMALL_STATE(744)] = 13962,
  [SMALL_STATE(745)] = 13966,
  [SMALL_STATE(746)] = 13970,
  [SMALL_STATE(747)] = 13974,
  [SMALL_STATE(748)] = 13978,
  [SMALL_STATE(749)] = 13982,
  [SMALL_STATE(750)] = 13986,
  [SMALL_STATE(751)] = 13990,
  [SMALL_STATE(752)] = 13994,
  [SMALL_STATE(753)] = 13998,
  [SMALL_STATE(754)] = 14002,
  [SMALL_STATE(755)] = 14006,
  [SMALL_STATE(756)] = 14010,
  [SMALL_STATE(757)] = 14014,
  [SMALL_STATE(758)] = 14018,
  [SMALL_STATE(759)] = 14022,
  [SMALL_STATE(760)] = 14026,
  [SMALL_STATE(761)] = 14030,
  [SMALL_STATE(762)] = 14034,
  [SMALL_STATE(763)] = 14038,
  [SMALL_STATE(764)] = 14042,
  [SMALL_STATE(765)] = 14046,
  [SMALL_STATE(766)] = 14050,
  [SMALL_STATE(767)] = 14054,
  [SMALL_STATE(768)] = 14058,
  [SMALL_STATE(769)] = 14062,
  [SMALL_STATE(770)] = 14066,
  [SMALL_STATE(771)] = 14070,
  [SMALL_STATE(772)] = 14074,
  [SMALL_STATE(773)] = 14078,
  [SMALL_STATE(774)] = 14082,
  [SMALL_STATE(775)] = 14086,
  [SMALL_STATE(776)] = 14090,
  [SMALL_STATE(777)] = 14094,
  [SMALL_STATE(778)] = 14098,
  [SMALL_STATE(779)] = 14102,
  [SMALL_STATE(780)] = 14106,
  [SMALL_STATE(781)] = 14110,
  [SMALL_STATE(782)] = 14114,
  [SMALL_STATE(783)] = 14118,
  [SMALL_STATE(784)] = 14122,
  [SMALL_STATE(785)] = 14126,
  [SMALL_STATE(786)] = 14130,
  [SMALL_STATE(787)] = 14134,
  [SMALL_STATE(788)] = 14138,
  [SMALL_STATE(789)] = 14142,
  [SMALL_STATE(790)] = 14146,
  [SMALL_STATE(791)] = 14150,
  [SMALL_STATE(792)] = 14154,
  [SMALL_STATE(793)] = 14158,
  [SMALL_STATE(794)] = 14162,
  [SMALL_STATE(795)] = 14166,
  [SMALL_STATE(796)] = 14170,
  [SMALL_STATE(797)] = 14174,
  [SMALL_STATE(798)] = 14178,
  [SMALL_STATE(799)] = 14182,
  [SMALL_STATE(800)] = 14186,
  [SMALL_STATE(801)] = 14190,
  [SMALL_STATE(802)] = 14194,
  [SMALL_STATE(803)] = 14198,
  [SMALL_STATE(804)] = 14202,
  [SMALL_STATE(805)] = 14206,
  [SMALL_STATE(806)] = 14210,
  [SMALL_STATE(807)] = 14214,
  [SMALL_STATE(808)] = 14218,
  [SMALL_STATE(809)] = 14222,
  [SMALL_STATE(810)] = 14226,
  [SMALL_STATE(811)] = 14230,
  [SMALL_STATE(812)] = 14234,
  [SMALL_STATE(813)] = 14238,
  [SMALL_STATE(814)] = 14242,
  [SMALL_STATE(815)] = 14246,
  [SMALL_STATE(816)] = 14250,
  [SMALL_STATE(817)] = 14254,
  [SMALL_STATE(818)] = 14258,
  [SMALL_STATE(819)] = 14262,
  [SMALL_STATE(820)] = 14266,
  [SMALL_STATE(821)] = 14270,
  [SMALL_STATE(822)] = 14274,
  [SMALL_STATE(823)] = 14278,
  [SMALL_STATE(824)] = 14282,
  [SMALL_STATE(825)] = 14286,
  [SMALL_STATE(826)] = 14290,
  [SMALL_STATE(827)] = 14294,
  [SMALL_STATE(828)] = 14298,
  [SMALL_STATE(829)] = 14302,
  [SMALL_STATE(830)] = 14306,
  [SMALL_STATE(831)] = 14310,
  [SMALL_STATE(832)] = 14314,
  [SMALL_STATE(833)] = 14318,
  [SMALL_STATE(834)] = 14322,
  [SMALL_STATE(835)] = 14326,
  [SMALL_STATE(836)] = 14330,
  [SMALL_STATE(837)] = 14334,
  [SMALL_STATE(838)] = 14338,
  [SMALL_STATE(839)] = 14342,
  [SMALL_STATE(840)] = 14346,
  [SMALL_STATE(841)] = 14350,
  [SMALL_STATE(842)] = 14354,
  [SMALL_STATE(843)] = 14358,
  [SMALL_STATE(844)] = 14362,
  [SMALL_STATE(845)] = 14366,
  [SMALL_STATE(846)] = 14370,
  [SMALL_STATE(847)] = 14374,
  [SMALL_STATE(848)] = 14378,
  [SMALL_STATE(849)] = 14382,
  [SMALL_STATE(850)] = 14386,
  [SMALL_STATE(851)] = 14390,
  [SMALL_STATE(852)] = 14394,
  [SMALL_STATE(853)] = 14398,
  [SMALL_STATE(854)] = 14402,
  [SMALL_STATE(855)] = 14406,
  [SMALL_STATE(856)] = 14410,
  [SMALL_STATE(857)] = 14414,
  [SMALL_STATE(858)] = 14418,
  [SMALL_STATE(859)] = 14422,
  [SMALL_STATE(860)] = 14426,
  [SMALL_STATE(861)] = 14430,
  [SMALL_STATE(862)] = 14434,
  [SMALL_STATE(863)] = 14438,
  [SMALL_STATE(864)] = 14442,
  [SMALL_STATE(865)] = 14446,
  [SMALL_STATE(866)] = 14450,
  [SMALL_STATE(867)] = 14454,
  [SMALL_STATE(868)] = 14458,
  [SMALL_STATE(869)] = 14462,
  [SMALL_STATE(870)] = 14466,
  [SMALL_STATE(871)] = 14470,
  [SMALL_STATE(872)] = 14474,
  [SMALL_STATE(873)] = 14478,
  [SMALL_STATE(874)] = 14482,
  [SMALL_STATE(875)] = 14486,
  [SMALL_STATE(876)] = 14490,
  [SMALL_STATE(877)] = 14494,
  [SMALL_STATE(878)] = 14498,
  [SMALL_STATE(879)] = 14502,
  [SMALL_STATE(880)] = 14506,
  [SMALL_STATE(881)] = 14510,
  [SMALL_STATE(882)] = 14514,
  [SMALL_STATE(883)] = 14518,
  [SMALL_STATE(884)] = 14522,
  [SMALL_STATE(885)] = 14526,
  [SMALL_STATE(886)] = 14530,
  [SMALL_STATE(887)] = 14534,
  [SMALL_STATE(888)] = 14538,
  [SMALL_STATE(889)] = 14542,
  [SMALL_STATE(890)] = 14546,
  [SMALL_STATE(891)] = 14550,
  [SMALL_STATE(892)] = 14554,
  [SMALL_STATE(893)] = 14558,
  [SMALL_STATE(894)] = 14562,
  [SMALL_STATE(895)] = 14566,
  [SMALL_STATE(896)] = 14570,
  [SMALL_STATE(897)] = 14574,
  [SMALL_STATE(898)] = 14578,
  [SMALL_STATE(899)] = 14582,
  [SMALL_STATE(900)] = 14586,
  [SMALL_STATE(901)] = 14590,
  [SMALL_STATE(902)] = 14594,
  [SMALL_STATE(903)] = 14598,
  [SMALL_STATE(904)] = 14602,
  [SMALL_STATE(905)] = 14606,
  [SMALL_STATE(906)] = 14610,
  [SMALL_STATE(907)] = 14614,
  [SMALL_STATE(908)] = 14618,
  [SMALL_STATE(909)] = 14622,
  [SMALL_STATE(910)] = 14626,
  [SMALL_STATE(911)] = 14630,
  [SMALL_STATE(912)] = 14634,
  [SMALL_STATE(913)] = 14638,
  [SMALL_STATE(914)] = 14642,
  [SMALL_STATE(915)] = 14646,
  [SMALL_STATE(916)] = 14650,
  [SMALL_STATE(917)] = 14654,
  [SMALL_STATE(918)] = 14658,
  [SMALL_STATE(919)] = 14662,
  [SMALL_STATE(920)] = 14666,
  [SMALL_STATE(921)] = 14670,
  [SMALL_STATE(922)] = 14674,
  [SMALL_STATE(923)] = 14678,
  [SMALL_STATE(924)] = 14682,
  [SMALL_STATE(925)] = 14686,
  [SMALL_STATE(926)] = 14690,
  [SMALL_STATE(927)] = 14694,
  [SMALL_STATE(928)] = 14698,
  [SMALL_STATE(929)] = 14702,
  [SMALL_STATE(930)] = 14706,
  [SMALL_STATE(931)] = 14710,
  [SMALL_STATE(932)] = 14714,
  [SMALL_STATE(933)] = 14718,
  [SMALL_STATE(934)] = 14722,
  [SMALL_STATE(935)] = 14726,
  [SMALL_STATE(936)] = 14730,
  [SMALL_STATE(937)] = 14734,
  [SMALL_STATE(938)] = 14738,
  [SMALL_STATE(939)] = 14742,
  [SMALL_STATE(940)] = 14746,
  [SMALL_STATE(941)] = 14750,
  [SMALL_STATE(942)] = 14754,
  [SMALL_STATE(943)] = 14758,
  [SMALL_STATE(944)] = 14762,
  [SMALL_STATE(945)] = 14766,
  [SMALL_STATE(946)] = 14770,
  [SMALL_STATE(947)] = 14774,
  [SMALL_STATE(948)] = 14778,
  [SMALL_STATE(949)] = 14782,
  [SMALL_STATE(950)] = 14786,
  [SMALL_STATE(951)] = 14790,
  [SMALL_STATE(952)] = 14794,
  [SMALL_STATE(953)] = 14798,
  [SMALL_STATE(954)] = 14802,
  [SMALL_STATE(955)] = 14806,
  [SMALL_STATE(956)] = 14810,
  [SMALL_STATE(957)] = 14814,
  [SMALL_STATE(958)] = 14818,
  [SMALL_STATE(959)] = 14822,
  [SMALL_STATE(960)] = 14826,
  [SMALL_STATE(961)] = 14830,
  [SMALL_STATE(962)] = 14834,
  [SMALL_STATE(963)] = 14838,
  [SMALL_STATE(964)] = 14842,
  [SMALL_STATE(965)] = 14846,
  [SMALL_STATE(966)] = 14850,
  [SMALL_STATE(967)] = 14854,
  [SMALL_STATE(968)] = 14858,
  [SMALL_STATE(969)] = 14862,
  [SMALL_STATE(970)] = 14866,
  [SMALL_STATE(971)] = 14870,
  [SMALL_STATE(972)] = 14874,
  [SMALL_STATE(973)] = 14878,
  [SMALL_STATE(974)] = 14882,
  [SMALL_STATE(975)] = 14886,
  [SMALL_STATE(976)] = 14890,
  [SMALL_STATE(977)] = 14894,
  [SMALL_STATE(978)] = 14898,
  [SMALL_STATE(979)] = 14902,
  [SMALL_STATE(980)] = 14906,
  [SMALL_STATE(981)] = 14910,
  [SMALL_STATE(982)] = 14914,
  [SMALL_STATE(983)] = 14918,
  [SMALL_STATE(984)] = 14922,
  [SMALL_STATE(985)] = 14926,
  [SMALL_STATE(986)] = 14930,
  [SMALL_STATE(987)] = 14934,
  [SMALL_STATE(988)] = 14938,
  [SMALL_STATE(989)] = 14942,
  [SMALL_STATE(990)] = 14946,
  [SMALL_STATE(991)] = 14950,
  [SMALL_STATE(992)] = 14954,
  [SMALL_STATE(993)] = 14958,
  [SMALL_STATE(994)] = 14962,
  [SMALL_STATE(995)] = 14966,
  [SMALL_STATE(996)] = 14970,
  [SMALL_STATE(997)] = 14974,
  [SMALL_STATE(998)] = 14978,
  [SMALL_STATE(999)] = 14982,
  [SMALL_STATE(1000)] = 14986,
  [SMALL_STATE(1001)] = 14990,
  [SMALL_STATE(1002)] = 14994,
  [SMALL_STATE(1003)] = 14998,
  [SMALL_STATE(1004)] = 15002,
  [SMALL_STATE(1005)] = 15006,
  [SMALL_STATE(1006)] = 15010,
  [SMALL_STATE(1007)] = 15014,
  [SMALL_STATE(1008)] = 15018,
  [SMALL_STATE(1009)] = 15022,
  [SMALL_STATE(1010)] = 15026,
  [SMALL_STATE(1011)] = 15030,
  [SMALL_STATE(1012)] = 15034,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(328),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(437),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(446),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(958),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(448),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(330),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(335),
  [19] = {.entry = {.count = 1, .reusable = true}}, SHIFT(584),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(1011),
  [23] = {.entry = {.count = 1, .reusable = true}}, SHIFT(336),
  [25] = {.entry = {.count = 1, .reusable = true}}, SHIFT(337),
  [27] = {.entry = {.count = 1, .reusable = true}}, SHIFT(388),
  [29] = {.entry = {.count = 1, .reusable = true}}, SHIFT(329),
  [31] = {.entry = {.count = 1, .reusable = true}}, SHIFT(1010),
  [33] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1),
  [35] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2),
  [37] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(328),
  [40] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(437),
  [43] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(446),
  [46] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(958),
  [49] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(448),
  [52] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(330),
  [55] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(335),
  [58] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(584),
  [61] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(1011),
  [64] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(336),
  [67] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(337),
  [70] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(388),
  [73] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(329),
  [76] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(1010),
  [79] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_function_call, 4, .production_id = 30),
  [81] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_function_call, 4, .production_id = 30),
  [83] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_integer, 1),
  [85] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [87] = {.entry = {.count = 1, .reusable = true}}, SHIFT(629),
  [89] = {.entry = {.count = 1, .reusable = true}}, SHIFT(611),
  [91] = {.entry = {.count = 1, .reusable = true}}, SHIFT(979),
  [93] = {.entry = {.count = 1, .reusable = false}}, SHIFT(406),
  [95] = {.entry = {.count = 1, .reusable = false}}, SHIFT(5),
  [97] = {.entry = {.count = 1, .reusable = true}}, SHIFT(658),
  [99] = {.entry = {.count = 1, .reusable = false}}, SHIFT(34),
  [101] = {.entry = {.count = 1, .reusable = false}}, SHIFT(33),
  [103] = {.entry = {.count = 1, .reusable = true}}, SHIFT(31),
  [105] = {.entry = {.count = 1, .reusable = false}}, SHIFT(31),
  [107] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [109] = {.entry = {.count = 1, .reusable = true}}, SHIFT(768),
  [111] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_integer, 2),
  [113] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_integer_repeat1, 2),
  [115] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_integer_repeat1, 2), SHIFT_REPEAT(8),
  [118] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_constant, 1),
  [120] = {.entry = {.count = 1, .reusable = true}}, SHIFT(657),
  [122] = {.entry = {.count = 1, .reusable = true}}, SHIFT(563),
  [124] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_single_quote, 1),
  [126] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string_literal, 3, .production_id = 11),
  [128] = {.entry = {.count = 1, .reusable = true}}, SHIFT(708),
  [130] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_decimal_fraction, 2),
  [132] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_scientific_notation, 5),
  [134] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_scientific_notation, 3),
  [136] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_scientific_notation, 4),
  [138] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_standard_decimal_notation, 2),
  [140] = {.entry = {.count = 1, .reusable = true}}, SHIFT(502),
  [142] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [144] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [146] = {.entry = {.count = 1, .reusable = false}}, SHIFT(25),
  [148] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_boolean_literal, 1),
  [150] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_float_literal, 1),
  [152] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_bind_marker, 1),
  [154] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_bind_marker, 2),
  [156] = {.entry = {.count = 1, .reusable = false}}, SHIFT(75),
  [158] = {.entry = {.count = 1, .reusable = false}}, SHIFT(967),
  [160] = {.entry = {.count = 1, .reusable = true}}, SHIFT(67),
  [162] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_relation_element_repeat2, 2),
  [164] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_relation_element_repeat2, 2), SHIFT_REPEAT(608),
  [167] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_relation_element, 5, .production_id = 29),
  [169] = {.entry = {.count = 1, .reusable = true}}, SHIFT(608),
  [171] = {.entry = {.count = 1, .reusable = true}}, SHIFT(101),
  [173] = {.entry = {.count = 1, .reusable = false}}, SHIFT(932),
  [175] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_relation_element, 6, .production_id = 29),
  [177] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_relation_element, 7, .production_id = 29),
  [179] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_assignment_tuple, 3),
  [181] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_relation_elements_repeat1, 2),
  [183] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_relation_elements_repeat1, 2), SHIFT_REPEAT(326),
  [186] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_data_type, 1),
  [188] = {.entry = {.count = 1, .reusable = true}}, SHIFT(57),
  [190] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_data_type_name, 1),
  [192] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_relation_contains_key, 4, .production_id = 1),
  [194] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_relation_element, 8, .production_id = 29),
  [196] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_relation_element, 1),
  [198] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_relation_elements, 1),
  [200] = {.entry = {.count = 1, .reusable = true}}, SHIFT(326),
  [202] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_quoted_identifier, 3, .production_id = 11),
  [204] = {.entry = {.count = 1, .reusable = true}}, SHIFT(653),
  [206] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_relation_element, 3),
  [208] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_relation_elements, 2),
  [210] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_relation_contains, 3, .production_id = 1),
  [212] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_double_quote, 1),
  [214] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_relation_element, 3, .production_id = 1),
  [216] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_relation_element, 9, .production_id = 29),
  [218] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_relation_element, 5, .production_id = 1),
  [220] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_data_type, 2),
  [222] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_data_type_definition, 3),
  [224] = {.entry = {.count = 1, .reusable = false}}, SHIFT(106),
  [226] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_identifier, 1),
  [228] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_data_type_definition, 4),
  [230] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_table_name, 1),
  [232] = {.entry = {.count = 1, .reusable = false}}, SHIFT(107),
  [234] = {.entry = {.count = 1, .reusable = true}}, SHIFT(107),
  [236] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_resource, 2, .production_id = 22),
  [238] = {.entry = {.count = 1, .reusable = true}}, SHIFT(919),
  [240] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_unquoted_identifier, 1),
  [242] = {.entry = {.count = 1, .reusable = false}}, SHIFT(110),
  [244] = {.entry = {.count = 1, .reusable = true}}, SHIFT(110),
  [246] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_name, 1, .production_id = 8),
  [248] = {.entry = {.count = 1, .reusable = true}}, SHIFT(862),
  [250] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_unquoted_identifier_repeat1, 2),
  [252] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_unquoted_identifier_repeat1, 2), SHIFT_REPEAT(100),
  [255] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_unquoted_identifier_repeat1, 2), SHIFT_REPEAT(100),
  [258] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_resource, 1, .production_id = 13),
  [260] = {.entry = {.count = 1, .reusable = true}}, SHIFT(917),
  [262] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_where_spec, 2),
  [264] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_table_name, 2),
  [266] = {.entry = {.count = 1, .reusable = false}}, SHIFT(100),
  [268] = {.entry = {.count = 1, .reusable = true}}, SHIFT(100),
  [270] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_resource, 2),
  [272] = {.entry = {.count = 1, .reusable = false}}, SHIFT(920),
  [274] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_resource, 2, .production_id = 23),
  [276] = {.entry = {.count = 1, .reusable = true}}, SHIFT(921),
  [278] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_unquoted_identifier, 2),
  [280] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_resource, 2, .production_id = 24),
  [282] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_insert_statement, 5),
  [284] = {.entry = {.count = 1, .reusable = true}}, SHIFT(778),
  [286] = {.entry = {.count = 1, .reusable = true}}, SHIFT(640),
  [288] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_resource, 2, .production_id = 2),
  [290] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_insert_statement, 6),
  [292] = {.entry = {.count = 1, .reusable = true}}, SHIFT(918),
  [294] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_create_function_repeat1, 2),
  [296] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_create_function_repeat1, 2), SHIFT_REPEAT(678),
  [299] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_materialized_view_name, 1, .production_id = 12),
  [301] = {.entry = {.count = 1, .reusable = true}}, SHIFT(771),
  [303] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_resource, 4, .production_id = 35),
  [305] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_clustering_key_list_repeat1, 2),
  [307] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_clustering_key_list_repeat1, 2), SHIFT_REPEAT(922),
  [310] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_function_name, 1),
  [312] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_privilege, 1),
  [314] = {.entry = {.count = 1, .reusable = true}}, SHIFT(164),
  [316] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_resource, 3, .production_id = 27),
  [318] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_resource, 4, .production_id = 36),
  [320] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_user_with, 2),
  [322] = {.entry = {.count = 1, .reusable = true}}, SHIFT(240),
  [324] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_name, 3, .production_id = 19),
  [326] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_resource, 5, .production_id = 41),
  [328] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_table, 6),
  [330] = {.entry = {.count = 1, .reusable = true}}, SHIFT(360),
  [332] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_role_with_repeat1, 2),
  [334] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_role_with_repeat1, 2), SHIFT_REPEAT(417),
  [337] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_using_ttl_timestamp, 3),
  [339] = {.entry = {.count = 1, .reusable = true}}, SHIFT(901),
  [341] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_materialized_view, 11),
  [343] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_role, 3),
  [345] = {.entry = {.count = 1, .reusable = true}}, SHIFT(423),
  [347] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_primary_key_element, 5),
  [349] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_aggregate_name, 1, .production_id = 6),
  [351] = {.entry = {.count = 1, .reusable = true}}, SHIFT(869),
  [353] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_init_cond_list, 4),
  [355] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_update, 6),
  [357] = {.entry = {.count = 1, .reusable = true}}, SHIFT(316),
  [359] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_init_cond_hash, 3),
  [361] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_init_cond_nested_list, 3),
  [363] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_init_cond_nested_list, 4),
  [365] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_init_cond_hash, 4),
  [367] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_delete_statement, 6),
  [369] = {.entry = {.count = 1, .reusable = true}}, SHIFT(315),
  [371] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_update, 5),
  [373] = {.entry = {.count = 1, .reusable = true}}, SHIFT(318),
  [375] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_alter_type_rename, 3),
  [377] = {.entry = {.count = 1, .reusable = true}}, SHIFT(645),
  [379] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_table, 9),
  [381] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_init_cond_list, 3),
  [383] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_role_with, 2),
  [385] = {.entry = {.count = 1, .reusable = true}}, SHIFT(417),
  [387] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_alter_table_drop_columns, 2),
  [389] = {.entry = {.count = 1, .reusable = true}}, SHIFT(922),
  [391] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_table_options, 1),
  [393] = {.entry = {.count = 1, .reusable = true}}, SHIFT(362),
  [395] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_alter_table_add, 2),
  [397] = {.entry = {.count = 1, .reusable = true}}, SHIFT(678),
  [399] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_alter_type_add, 2),
  [401] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_table_options_repeat1, 2),
  [403] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_table_options_repeat1, 2), SHIFT_REPEAT(362),
  [406] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_delete_statement, 3),
  [408] = {.entry = {.count = 1, .reusable = true}}, SHIFT(322),
  [410] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_alter_type_add, 3),
  [412] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_alter_type_rename, 2),
  [414] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_delete_statement, 4),
  [416] = {.entry = {.count = 1, .reusable = true}}, SHIFT(323),
  [418] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_keyspace_name, 1, .production_id = 3),
  [420] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_alter_table_add, 3),
  [422] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_delete_statement, 5),
  [424] = {.entry = {.count = 1, .reusable = true}}, SHIFT(321),
  [426] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_table_options, 2),
  [428] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_alter_table_drop_columns, 3),
  [430] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_update, 4),
  [432] = {.entry = {.count = 1, .reusable = true}}, SHIFT(317),
  [434] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_privilege, 2),
  [436] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_list_permissions, 2),
  [438] = {.entry = {.count = 1, .reusable = true}}, SHIFT(367),
  [440] = {.entry = {.count = 1, .reusable = true}}, SHIFT(924),
  [442] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_insert_statement, 9),
  [444] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_list_roles, 2),
  [446] = {.entry = {.count = 1, .reusable = true}}, SHIFT(925),
  [448] = {.entry = {.count = 1, .reusable = true}}, SHIFT(309),
  [450] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_alter_type_rename_repeat1, 2),
  [452] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_alter_type_rename_repeat1, 2), SHIFT_REPEAT(645),
  [455] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_alter_role, 3),
  [457] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_using_ttl_timestamp, 3, .production_id = 21),
  [459] = {.entry = {.count = 1, .reusable = true}}, SHIFT(907),
  [461] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_insert_values_spec, 2),
  [463] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_insert_statement, 8),
  [465] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_typed_name, 2, .production_id = 1),
  [467] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_insert_values_spec, 4),
  [469] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_materialized_view, 14),
  [471] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_role, 6),
  [473] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_role_with, 3),
  [475] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_alter_materialized_view, 4),
  [477] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_user_password, 2, .production_id = 26),
  [479] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_init_cond_definition, 1),
  [481] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_materialized_view_name, 3, .production_id = 25),
  [483] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_keyspace, 7),
  [485] = {.entry = {.count = 1, .reusable = true}}, SHIFT(695),
  [487] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_list_roles, 4, .production_id = 14),
  [489] = {.entry = {.count = 1, .reusable = true}}, SHIFT(250),
  [491] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_list_permissions, 4),
  [493] = {.entry = {.count = 1, .reusable = true}}, SHIFT(755),
  [495] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_keyspace, 10),
  [497] = {.entry = {.count = 1, .reusable = true}}, SHIFT(676),
  [499] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_replication_list, 4),
  [501] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_role_with_option, 3, .production_id = 31),
  [503] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_option_hash, 4),
  [505] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_clustering_order, 6, .production_id = 49),
  [507] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_alter_type_rename_item, 3, .production_id = 38),
  [509] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_alter_keyspace, 7),
  [511] = {.entry = {.count = 1, .reusable = true}}, SHIFT(728),
  [513] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_role_with_option, 3),
  [515] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_compact_storage, 2),
  [517] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_table_option_item, 3),
  [519] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_clustering_order, 7, .production_id = 49),
  [521] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_using_ttl_timestamp, 6, .production_id = 39),
  [523] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_using_ttl_timestamp, 6, .production_id = 21),
  [525] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_table_option_value, 1),
  [527] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_role_with_option, 3, .production_id = 33),
  [529] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_role_with_option, 3, .production_id = 32),
  [531] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_aggregate_name, 3, .production_id = 17),
  [533] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_index_name, 1, .production_id = 4),
  [535] = {.entry = {.count = 1, .reusable = true}}, SHIFT(850),
  [537] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_user_name, 1, .production_id = 9),
  [539] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_option_hash, 3),
  [541] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_role_name, 1, .production_id = 5),
  [543] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_replication_list, 3),
  [545] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_user_with, 3),
  [547] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_role, 7),
  [549] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_user, 7),
  [551] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_type, 7),
  [553] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_drop_trigger, 7),
  [555] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_index, 7),
  [557] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_table, 7),
  [559] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_delete_statement, 7),
  [561] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_function, 13, .production_id = 53),
  [563] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__statement, 1),
  [565] = {.entry = {.count = 1, .reusable = true}}, SHIFT(319),
  [567] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_update, 7),
  [569] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_select_statement, 7),
  [571] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_list_permissions, 6, .production_id = 28),
  [573] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [575] = {.entry = {.count = 1, .reusable = true}}, SHIFT(34),
  [577] = {.entry = {.count = 1, .reusable = true}}, SHIFT(405),
  [579] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_truncate, 2),
  [581] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_alter_table_rename, 4, .production_id = 37),
  [583] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_materialized_view, 12),
  [585] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_alter_table_drop_compact_storage, 3),
  [587] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_revoke, 6, .production_id = 28),
  [589] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_grant, 6, .production_id = 28),
  [591] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_alter_type_alter_type, 4, .production_id = 29),
  [593] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_insert_statement, 7),
  [595] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_function, 12, .production_id = 52),
  [597] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_keyspace, 12),
  [599] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_select_statement, 8),
  [601] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_drop_materialized_view, 6),
  [603] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_user_super_user, 1),
  [605] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_role, 4),
  [607] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_type, 6),
  [609] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_index, 8),
  [611] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_use, 2, .production_id = 2),
  [613] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_trigger, 8),
  [615] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_apply_batch, 2),
  [617] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_select_statement, 6),
  [619] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_user, 4),
  [621] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_list_roles, 5, .production_id = 14),
  [623] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_delete_statement, 8),
  [625] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_update, 8),
  [627] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_durable_writes, 3, .production_id = 50),
  [629] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_index, 11),
  [631] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_alter_materialized_view, 5),
  [633] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_select_statement, 9),
  [635] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_with_element, 2),
  [637] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_drop_materialized_view, 4),
  [639] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_drop_role, 3),
  [641] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_truncate, 3),
  [643] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_select_statement, 11),
  [645] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_insert_statement, 10),
  [647] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_aggregate, 19, .production_id = 64),
  [649] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_function, 19, .production_id = 63),
  [651] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_function, 18, .production_id = 62),
  [653] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_drop_user, 5),
  [655] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_select_statement, 4),
  [657] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_type, 10),
  [659] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_drop_type, 5),
  [661] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_drop_trigger, 5),
  [663] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_drop_aggregate, 5),
  [665] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_drop_role, 5),
  [667] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_drop_function, 5),
  [669] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_drop_keyspace, 5),
  [671] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_function, 14, .production_id = 54),
  [673] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_index_name, 3, .production_id = 20),
  [675] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_drop_index, 5),
  [677] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_drop_table, 5),
  [679] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_semi_sep, 1),
  [681] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_alter_table_operation, 1),
  [683] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_alter_table, 4),
  [685] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_function, 17, .production_id = 59),
  [687] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_alter_role, 4),
  [689] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_keyspace, 9),
  [691] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_index, 10),
  [693] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_table, 10),
  [695] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_aggregate, 16, .production_id = 58),
  [697] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_alter_type, 4),
  [699] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_alter_type_operation, 1),
  [701] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_alter_user, 4),
  [703] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_trigger, 5),
  [705] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_trigger_class, 1),
  [707] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_list_permissions, 4, .production_id = 14),
  [709] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_drop_table, 3),
  [711] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_drop_index, 3),
  [713] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_drop_keyspace, 3),
  [715] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_drop_function, 3),
  [717] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_aggregate, 17, .production_id = 60),
  [719] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_select_statement, 5),
  [721] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_type, 9),
  [723] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_drop_aggregate, 3),
  [725] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_function, 16, .production_id = 57),
  [727] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_drop_type, 3),
  [729] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_aggregate, 14, .production_id = 55),
  [731] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_materialized_view, 15),
  [733] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_drop_user, 3),
  [735] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_list_roles, 3),
  [737] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_select_statement, 10),
  [739] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_alter_keyspace, 9),
  [741] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_if_spec, 2),
  [743] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_function, 15, .production_id = 56),
  [745] = {.entry = {.count = 1, .reusable = false}}, SHIFT(611),
  [747] = {.entry = {.count = 1, .reusable = true}}, SHIFT(905),
  [749] = {.entry = {.count = 1, .reusable = false}}, SHIFT(251),
  [751] = {.entry = {.count = 1, .reusable = false}}, SHIFT(356),
  [753] = {.entry = {.count = 1, .reusable = false}}, SHIFT(252),
  [755] = {.entry = {.count = 1, .reusable = false}}, SHIFT(234),
  [757] = {.entry = {.count = 1, .reusable = false}}, SHIFT(223),
  [759] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__statement, 2),
  [761] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comma_sep, 1),
  [763] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_comma_sep, 1),
  [765] = {.entry = {.count = 1, .reusable = false}}, SHIFT(219),
  [767] = {.entry = {.count = 1, .reusable = false}}, SHIFT(314),
  [769] = {.entry = {.count = 1, .reusable = false}}, SHIFT(211),
  [771] = {.entry = {.count = 1, .reusable = false}}, SHIFT(345),
  [773] = {.entry = {.count = 1, .reusable = false}}, SHIFT(390),
  [775] = {.entry = {.count = 1, .reusable = true}}, SHIFT(1007),
  [777] = {.entry = {.count = 1, .reusable = true}}, SHIFT(331),
  [779] = {.entry = {.count = 1, .reusable = true}}, SHIFT(332),
  [781] = {.entry = {.count = 1, .reusable = true}}, SHIFT(172),
  [783] = {.entry = {.count = 1, .reusable = true}}, SHIFT(122),
  [785] = {.entry = {.count = 1, .reusable = true}}, SHIFT(167),
  [787] = {.entry = {.count = 1, .reusable = true}}, SHIFT(468),
  [789] = {.entry = {.count = 1, .reusable = true}}, SHIFT(352),
  [791] = {.entry = {.count = 1, .reusable = true}}, SHIFT(525),
  [793] = {.entry = {.count = 1, .reusable = true}}, SHIFT(350),
  [795] = {.entry = {.count = 1, .reusable = true}}, SHIFT(520),
  [797] = {.entry = {.count = 1, .reusable = true}}, SHIFT(519),
  [799] = {.entry = {.count = 1, .reusable = true}}, SHIFT(1001),
  [801] = {.entry = {.count = 1, .reusable = true}}, SHIFT(512),
  [803] = {.entry = {.count = 1, .reusable = true}}, SHIFT(509),
  [805] = {.entry = {.count = 1, .reusable = true}}, SHIFT(506),
  [807] = {.entry = {.count = 1, .reusable = true}}, SHIFT(1000),
  [809] = {.entry = {.count = 1, .reusable = true}}, SHIFT(333),
  [811] = {.entry = {.count = 1, .reusable = true}}, SHIFT(390),
  [813] = {.entry = {.count = 1, .reusable = true}}, SHIFT(692),
  [815] = {.entry = {.count = 1, .reusable = true}}, SHIFT(693),
  [817] = {.entry = {.count = 1, .reusable = true}}, SHIFT(813),
  [819] = {.entry = {.count = 1, .reusable = true}}, SHIFT(476),
  [821] = {.entry = {.count = 1, .reusable = true}}, SHIFT(501),
  [823] = {.entry = {.count = 1, .reusable = true}}, SHIFT(500),
  [825] = {.entry = {.count = 1, .reusable = true}}, SHIFT(353),
  [827] = {.entry = {.count = 1, .reusable = true}}, SHIFT(498),
  [829] = {.entry = {.count = 1, .reusable = true}}, SHIFT(496),
  [831] = {.entry = {.count = 1, .reusable = true}}, SHIFT(999),
  [833] = {.entry = {.count = 1, .reusable = true}}, SHIFT(490),
  [835] = {.entry = {.count = 1, .reusable = true}}, SHIFT(489),
  [837] = {.entry = {.count = 1, .reusable = true}}, SHIFT(488),
  [839] = {.entry = {.count = 1, .reusable = false}}, SHIFT(344),
  [841] = {.entry = {.count = 1, .reusable = true}}, SHIFT(344),
  [843] = {.entry = {.count = 1, .reusable = true}}, SHIFT(281),
  [845] = {.entry = {.count = 1, .reusable = true}}, SHIFT(799),
  [847] = {.entry = {.count = 1, .reusable = true}}, SHIFT(466),
  [849] = {.entry = {.count = 1, .reusable = true}}, SHIFT(324),
  [851] = {.entry = {.count = 1, .reusable = true}}, SHIFT(915),
  [853] = {.entry = {.count = 1, .reusable = true}}, SHIFT(739),
  [855] = {.entry = {.count = 1, .reusable = false}}, SHIFT(338),
  [857] = {.entry = {.count = 1, .reusable = true}}, SHIFT(338),
  [859] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [861] = {.entry = {.count = 1, .reusable = true}}, SHIFT(916),
  [863] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_unquoted_identifier_repeat1, 2), SHIFT_REPEAT(344),
  [866] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_unquoted_identifier_repeat1, 2), SHIFT_REPEAT(344),
  [869] = {.entry = {.count = 1, .reusable = false}}, SHIFT(65),
  [871] = {.entry = {.count = 1, .reusable = true}}, SHIFT(65),
  [873] = {.entry = {.count = 1, .reusable = true}}, SHIFT(793),
  [875] = {.entry = {.count = 1, .reusable = true}}, SHIFT(93),
  [877] = {.entry = {.count = 1, .reusable = true}}, SHIFT(883),
  [879] = {.entry = {.count = 1, .reusable = true}}, SHIFT(761),
  [881] = {.entry = {.count = 1, .reusable = false}}, SHIFT(734),
  [883] = {.entry = {.count = 1, .reusable = false}}, SHIFT(794),
  [885] = {.entry = {.count = 1, .reusable = false}}, SHIFT(795),
  [887] = {.entry = {.count = 1, .reusable = false}}, SHIFT(800),
  [889] = {.entry = {.count = 1, .reusable = false}}, SHIFT(358),
  [891] = {.entry = {.count = 1, .reusable = true}}, SHIFT(358),
  [893] = {.entry = {.count = 1, .reusable = true}}, SHIFT(969),
  [895] = {.entry = {.count = 1, .reusable = false}}, SHIFT(978),
  [897] = {.entry = {.count = 1, .reusable = false}}, SHIFT(528),
  [899] = {.entry = {.count = 1, .reusable = false}}, SHIFT(977),
  [901] = {.entry = {.count = 1, .reusable = false}}, SHIFT(98),
  [903] = {.entry = {.count = 1, .reusable = true}}, SHIFT(947),
  [905] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_unquoted_identifier_repeat1, 2), SHIFT_REPEAT(358),
  [908] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_unquoted_identifier_repeat1, 2), SHIFT_REPEAT(358),
  [911] = {.entry = {.count = 1, .reusable = false}}, SHIFT(349),
  [913] = {.entry = {.count = 1, .reusable = true}}, SHIFT(349),
  [915] = {.entry = {.count = 1, .reusable = false}}, SHIFT(744),
  [917] = {.entry = {.count = 1, .reusable = false}}, SHIFT(742),
  [919] = {.entry = {.count = 1, .reusable = false}}, SHIFT(740),
  [921] = {.entry = {.count = 1, .reusable = true}}, SHIFT(421),
  [923] = {.entry = {.count = 1, .reusable = false}}, SHIFT(665),
  [925] = {.entry = {.count = 1, .reusable = true}}, SHIFT(665),
  [927] = {.entry = {.count = 1, .reusable = true}}, SHIFT(893),
  [929] = {.entry = {.count = 1, .reusable = false}}, SHIFT(540),
  [931] = {.entry = {.count = 1, .reusable = false}}, SHIFT(832),
  [933] = {.entry = {.count = 1, .reusable = false}}, SHIFT(526),
  [935] = {.entry = {.count = 1, .reusable = false}}, SHIFT(831),
  [937] = {.entry = {.count = 1, .reusable = false}}, SHIFT(826),
  [939] = {.entry = {.count = 1, .reusable = false}}, SHIFT(825),
  [941] = {.entry = {.count = 1, .reusable = false}}, SHIFT(103),
  [943] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_arithmetic_operation, 3),
  [945] = {.entry = {.count = 1, .reusable = true}}, SHIFT(409),
  [947] = {.entry = {.count = 1, .reusable = false}}, SHIFT(641),
  [949] = {.entry = {.count = 1, .reusable = true}}, SHIFT(641),
  [951] = {.entry = {.count = 1, .reusable = true}}, SHIFT(951),
  [953] = {.entry = {.count = 1, .reusable = true}}, SHIFT(936),
  [955] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_term, 1),
  [957] = {.entry = {.count = 1, .reusable = true}}, SHIFT(98),
  [959] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [961] = {.entry = {.count = 1, .reusable = true}}, SHIFT(406),
  [963] = {.entry = {.count = 1, .reusable = true}}, SHIFT(809),
  [965] = {.entry = {.count = 1, .reusable = true}}, SHIFT(698),
  [967] = {.entry = {.count = 1, .reusable = true}}, SHIFT(701),
  [969] = {.entry = {.count = 1, .reusable = false}}, SHIFT(28),
  [971] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [973] = {.entry = {.count = 1, .reusable = true}}, SHIFT(545),
  [975] = {.entry = {.count = 1, .reusable = true}}, SHIFT(617),
  [977] = {.entry = {.count = 1, .reusable = true}}, SHIFT(618),
  [979] = {.entry = {.count = 1, .reusable = true}}, SHIFT(994),
  [981] = {.entry = {.count = 1, .reusable = true}}, SHIFT(619),
  [983] = {.entry = {.count = 1, .reusable = true}}, SHIFT(620),
  [985] = {.entry = {.count = 1, .reusable = true}}, SHIFT(320),
  [987] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [989] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_function_args, 1),
  [991] = {.entry = {.count = 1, .reusable = false}}, SHIFT(402),
  [993] = {.entry = {.count = 1, .reusable = true}}, SHIFT(402),
  [995] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_from_spec, 2),
  [997] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_unquoted_identifier_repeat1, 2), SHIFT_REPEAT(392),
  [1000] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_unquoted_identifier_repeat1, 2), SHIFT_REPEAT(392),
  [1003] = {.entry = {.count = 1, .reusable = false}}, SHIFT(341),
  [1005] = {.entry = {.count = 1, .reusable = true}}, SHIFT(341),
  [1007] = {.entry = {.count = 1, .reusable = false}}, SHIFT(158),
  [1009] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_table_expression, 1),
  [1011] = {.entry = {.count = 1, .reusable = false}}, SHIFT(392),
  [1013] = {.entry = {.count = 1, .reusable = true}}, SHIFT(392),
  [1015] = {.entry = {.count = 1, .reusable = false}}, SHIFT(397),
  [1017] = {.entry = {.count = 1, .reusable = true}}, SHIFT(397),
  [1019] = {.entry = {.count = 1, .reusable = false}}, SHIFT(401),
  [1021] = {.entry = {.count = 1, .reusable = true}}, SHIFT(401),
  [1023] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_table_expression, 3),
  [1025] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_unquoted_identifier_repeat1, 2), SHIFT_REPEAT(399),
  [1028] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_unquoted_identifier_repeat1, 2), SHIFT_REPEAT(399),
  [1031] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_unquoted_identifier_repeat1, 2), SHIFT_REPEAT(400),
  [1034] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_unquoted_identifier_repeat1, 2), SHIFT_REPEAT(400),
  [1037] = {.entry = {.count = 1, .reusable = false}}, SHIFT(399),
  [1039] = {.entry = {.count = 1, .reusable = true}}, SHIFT(399),
  [1041] = {.entry = {.count = 1, .reusable = false}}, SHIFT(400),
  [1043] = {.entry = {.count = 1, .reusable = true}}, SHIFT(400),
  [1045] = {.entry = {.count = 1, .reusable = false}}, SHIFT(395),
  [1047] = {.entry = {.count = 1, .reusable = true}}, SHIFT(395),
  [1049] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_unquoted_identifier_repeat1, 2), SHIFT_REPEAT(404),
  [1052] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_unquoted_identifier_repeat1, 2), SHIFT_REPEAT(404),
  [1055] = {.entry = {.count = 1, .reusable = true}}, SHIFT(408),
  [1057] = {.entry = {.count = 1, .reusable = true}}, SHIFT(904),
  [1059] = {.entry = {.count = 1, .reusable = true}}, SHIFT(424),
  [1061] = {.entry = {.count = 1, .reusable = false}}, SHIFT(413),
  [1063] = {.entry = {.count = 1, .reusable = true}}, SHIFT(413),
  [1065] = {.entry = {.count = 1, .reusable = true}}, SHIFT(700),
  [1067] = {.entry = {.count = 1, .reusable = true}}, SHIFT(699),
  [1069] = {.entry = {.count = 1, .reusable = false}}, SHIFT(426),
  [1071] = {.entry = {.count = 1, .reusable = true}}, SHIFT(426),
  [1073] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_begin_batch, 3),
  [1075] = {.entry = {.count = 1, .reusable = true}}, SHIFT(986),
  [1077] = {.entry = {.count = 1, .reusable = false}}, SHIFT(11),
  [1079] = {.entry = {.count = 1, .reusable = true}}, SHIFT(425),
  [1081] = {.entry = {.count = 1, .reusable = true}}, SHIFT(782),
  [1083] = {.entry = {.count = 1, .reusable = true}}, SHIFT(781),
  [1085] = {.entry = {.count = 1, .reusable = true}}, SHIFT(780),
  [1087] = {.entry = {.count = 1, .reusable = true}}, SHIFT(779),
  [1089] = {.entry = {.count = 1, .reusable = false}}, SHIFT(427),
  [1091] = {.entry = {.count = 1, .reusable = true}}, SHIFT(427),
  [1093] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_string_literal_repeat1, 2), SHIFT_REPEAT(11),
  [1096] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_string_literal_repeat1, 2), SHIFT_REPEAT(419),
  [1099] = {.entry = {.count = 1, .reusable = true}}, SHIFT(415),
  [1101] = {.entry = {.count = 1, .reusable = false}}, SHIFT(418),
  [1103] = {.entry = {.count = 1, .reusable = true}}, SHIFT(418),
  [1105] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map_key, 1),
  [1107] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_unquoted_identifier_repeat1, 2), SHIFT_REPEAT(424),
  [1110] = {.entry = {.count = 1, .reusable = true}}, SHIFT(419),
  [1112] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_unquoted_identifier_repeat1, 2), SHIFT_REPEAT(426),
  [1115] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_unquoted_identifier_repeat1, 2), SHIFT_REPEAT(426),
  [1118] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_unquoted_identifier_repeat1, 2), SHIFT_REPEAT(427),
  [1121] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_unquoted_identifier_repeat1, 2), SHIFT_REPEAT(427),
  [1124] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_begin_batch, 2),
  [1126] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_quoted_identifier_repeat1, 2), SHIFT_REPEAT(87),
  [1129] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_quoted_identifier_repeat1, 2), SHIFT_REPEAT(430),
  [1132] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_order_spec, 3),
  [1134] = {.entry = {.count = 1, .reusable = true}}, SHIFT(556),
  [1136] = {.entry = {.count = 1, .reusable = false}}, SHIFT(438),
  [1138] = {.entry = {.count = 1, .reusable = true}}, SHIFT(438),
  [1140] = {.entry = {.count = 1, .reusable = false}}, SHIFT(396),
  [1142] = {.entry = {.count = 1, .reusable = false}}, SHIFT(544),
  [1144] = {.entry = {.count = 1, .reusable = false}}, SHIFT(404),
  [1146] = {.entry = {.count = 1, .reusable = true}}, SHIFT(404),
  [1148] = {.entry = {.count = 1, .reusable = false}}, SHIFT(87),
  [1150] = {.entry = {.count = 1, .reusable = true}}, SHIFT(430),
  [1152] = {.entry = {.count = 1, .reusable = true}}, SHIFT(439),
  [1154] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_column_definition, 2, .production_id = 1),
  [1156] = {.entry = {.count = 1, .reusable = true}}, SHIFT(890),
  [1158] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_using_timestamp_spec, 3),
  [1160] = {.entry = {.count = 1, .reusable = true}}, SHIFT(1002),
  [1162] = {.entry = {.count = 1, .reusable = true}}, SHIFT(428),
  [1164] = {.entry = {.count = 1, .reusable = true}}, SHIFT(622),
  [1166] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_select_expression, 2),
  [1168] = {.entry = {.count = 1, .reusable = false}}, SHIFT(96),
  [1170] = {.entry = {.count = 1, .reusable = true}}, SHIFT(96),
  [1172] = {.entry = {.count = 1, .reusable = true}}, SHIFT(534),
  [1174] = {.entry = {.count = 1, .reusable = true}}, SHIFT(767),
  [1176] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_column_list, 1, .production_id = 1),
  [1178] = {.entry = {.count = 1, .reusable = false}}, SHIFT(1012),
  [1180] = {.entry = {.count = 1, .reusable = false}}, SHIFT(37),
  [1182] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map_value, 1),
  [1184] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_function_args, 2),
  [1186] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_column_list, 2, .production_id = 1),
  [1188] = {.entry = {.count = 1, .reusable = true}}, SHIFT(595),
  [1190] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_relation_element_repeat1, 2), SHIFT_REPEAT(767),
  [1193] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_relation_element_repeat1, 2),
  [1195] = {.entry = {.count = 1, .reusable = true}}, SHIFT(325),
  [1197] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_materialized_view_where, 2),
  [1199] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_select_expression, 1),
  [1201] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_select_expression_repeat1, 2), SHIFT_REPEAT(622),
  [1204] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_select_expression_repeat1, 2),
  [1206] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_materialized_view_where, 3),
  [1208] = {.entry = {.count = 1, .reusable = false}}, SHIFT(420),
  [1210] = {.entry = {.count = 1, .reusable = true}}, SHIFT(420),
  [1212] = {.entry = {.count = 1, .reusable = true}}, SHIFT(982),
  [1214] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_list_literal, 5, .production_id = 48),
  [1216] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_function_args_repeat1, 2), SHIFT_REPEAT(320),
  [1219] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_function_args_repeat1, 2),
  [1221] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map_literal, 5, .production_id = 47),
  [1223] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_set_literal, 5, .production_id = 47),
  [1225] = {.entry = {.count = 1, .reusable = true}}, SHIFT(950),
  [1227] = {.entry = {.count = 1, .reusable = true}}, SHIFT(480),
  [1229] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_replication_list_repeat1, 2), SHIFT_REPEAT(429),
  [1232] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_replication_list_repeat1, 2),
  [1234] = {.entry = {.count = 1, .reusable = true}}, SHIFT(442),
  [1236] = {.entry = {.count = 1, .reusable = true}}, SHIFT(208),
  [1238] = {.entry = {.count = 1, .reusable = true}}, SHIFT(841),
  [1240] = {.entry = {.count = 1, .reusable = true}}, SHIFT(848),
  [1242] = {.entry = {.count = 1, .reusable = true}}, SHIFT(550),
  [1244] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_expression_list_repeat1, 2), SHIFT_REPEAT(32),
  [1247] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_expression_list_repeat1, 2),
  [1249] = {.entry = {.count = 1, .reusable = true}}, SHIFT(429),
  [1251] = {.entry = {.count = 1, .reusable = true}}, SHIFT(210),
  [1253] = {.entry = {.count = 1, .reusable = true}}, SHIFT(533),
  [1255] = {.entry = {.count = 1, .reusable = true}}, SHIFT(32),
  [1257] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_expression_list, 2),
  [1259] = {.entry = {.count = 1, .reusable = false}}, SHIFT(940),
  [1261] = {.entry = {.count = 1, .reusable = false}}, SHIFT(207),
  [1263] = {.entry = {.count = 1, .reusable = false}}, SHIFT(941),
  [1265] = {.entry = {.count = 1, .reusable = false}}, SHIFT(99),
  [1267] = {.entry = {.count = 1, .reusable = false}}, SHIFT(944),
  [1269] = {.entry = {.count = 1, .reusable = false}}, SHIFT(523),
  [1271] = {.entry = {.count = 1, .reusable = true}}, SHIFT(604),
  [1273] = {.entry = {.count = 1, .reusable = true}}, SHIFT(104),
  [1275] = {.entry = {.count = 1, .reusable = true}}, SHIFT(147),
  [1277] = {.entry = {.count = 1, .reusable = true}}, SHIFT(33),
  [1279] = {.entry = {.count = 1, .reusable = false}}, SHIFT(945),
  [1281] = {.entry = {.count = 1, .reusable = false}}, SHIFT(134),
  [1283] = {.entry = {.count = 1, .reusable = true}}, SHIFT(516),
  [1285] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_update_assignments, 2),
  [1287] = {.entry = {.count = 1, .reusable = false}}, SHIFT(946),
  [1289] = {.entry = {.count = 1, .reusable = false}}, SHIFT(209),
  [1291] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_init_cond_hash_repeat1, 2), SHIFT_REPEAT(639),
  [1294] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_init_cond_hash_repeat1, 2),
  [1296] = {.entry = {.count = 1, .reusable = false}}, SHIFT(948),
  [1298] = {.entry = {.count = 1, .reusable = false}}, SHIFT(949),
  [1300] = {.entry = {.count = 1, .reusable = false}}, SHIFT(206),
  [1302] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [1304] = {.entry = {.count = 1, .reusable = true}}, SHIFT(731),
  [1306] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_partition_key_list, 2),
  [1308] = {.entry = {.count = 1, .reusable = true}}, SHIFT(215),
  [1310] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_init_cond_nested_list_repeat1, 2), SHIFT_REPEAT(80),
  [1313] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_init_cond_nested_list_repeat1, 2),
  [1315] = {.entry = {.count = 1, .reusable = false}}, SHIFT(956),
  [1317] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_init_cond_list_repeat1, 2), SHIFT_REPEAT(104),
  [1320] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_init_cond_list_repeat1, 2),
  [1322] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_update_assignments, 3),
  [1324] = {.entry = {.count = 1, .reusable = false}}, SHIFT(884),
  [1326] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [1328] = {.entry = {.count = 1, .reusable = true}}, SHIFT(873),
  [1330] = {.entry = {.count = 1, .reusable = false}}, SHIFT(962),
  [1332] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_clustering_key_list, 1),
  [1334] = {.entry = {.count = 1, .reusable = true}}, SHIFT(576),
  [1336] = {.entry = {.count = 1, .reusable = true}}, SHIFT(686),
  [1338] = {.entry = {.count = 1, .reusable = false}}, SHIFT(868),
  [1340] = {.entry = {.count = 1, .reusable = false}}, SHIFT(118),
  [1342] = {.entry = {.count = 1, .reusable = false}}, SHIFT(965),
  [1344] = {.entry = {.count = 1, .reusable = false}}, SHIFT(966),
  [1346] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_assignment_element, 3),
  [1348] = {.entry = {.count = 1, .reusable = true}}, SHIFT(960),
  [1350] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_update_assignments_repeat1, 2), SHIFT_REPEAT(516),
  [1353] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_update_assignments_repeat1, 2),
  [1355] = {.entry = {.count = 1, .reusable = true}}, SHIFT(864),
  [1357] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_trigger_name, 1, .production_id = 7),
  [1359] = {.entry = {.count = 1, .reusable = true}}, SHIFT(403),
  [1361] = {.entry = {.count = 1, .reusable = false}}, SHIFT(975),
  [1363] = {.entry = {.count = 1, .reusable = true}}, SHIFT(108),
  [1365] = {.entry = {.count = 1, .reusable = true}}, SHIFT(115),
  [1367] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_option_hash_repeat1, 2), SHIFT_REPEAT(442),
  [1370] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_option_hash_repeat1, 2),
  [1372] = {.entry = {.count = 1, .reusable = true}}, SHIFT(89),
  [1374] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [1376] = {.entry = {.count = 1, .reusable = true}}, SHIFT(111),
  [1378] = {.entry = {.count = 1, .reusable = true}}, SHIFT(791),
  [1380] = {.entry = {.count = 1, .reusable = true}}, SHIFT(56),
  [1382] = {.entry = {.count = 1, .reusable = true}}, SHIFT(95),
  [1384] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_begin_batch, 4),
  [1386] = {.entry = {.count = 1, .reusable = true}}, SHIFT(627),
  [1388] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_delete_column_list, 1),
  [1390] = {.entry = {.count = 1, .reusable = true}}, SHIFT(450),
  [1392] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_column_definition_list, 2),
  [1394] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_delete_column_item, 1, .production_id = 1),
  [1396] = {.entry = {.count = 1, .reusable = true}}, SHIFT(361),
  [1398] = {.entry = {.count = 1, .reusable = true}}, SHIFT(359),
  [1400] = {.entry = {.count = 1, .reusable = true}}, SHIFT(187),
  [1402] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_delete_column_list_repeat1, 2), SHIFT_REPEAT(627),
  [1405] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_delete_column_list_repeat1, 2),
  [1407] = {.entry = {.count = 1, .reusable = true}}, SHIFT(435),
  [1409] = {.entry = {.count = 1, .reusable = true}}, SHIFT(242),
  [1411] = {.entry = {.count = 1, .reusable = true}}, SHIFT(537),
  [1413] = {.entry = {.count = 1, .reusable = true}}, SHIFT(639),
  [1415] = {.entry = {.count = 1, .reusable = true}}, SHIFT(142),
  [1417] = {.entry = {.count = 1, .reusable = true}}, SHIFT(80),
  [1419] = {.entry = {.count = 1, .reusable = true}}, SHIFT(141),
  [1421] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_order_spec, 4),
  [1423] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_relation_element_repeat1, 2, .production_id = 29),
  [1425] = {.entry = {.count = 1, .reusable = true}}, SHIFT(190),
  [1427] = {.entry = {.count = 1, .reusable = true}}, SHIFT(78),
  [1429] = {.entry = {.count = 1, .reusable = true}}, SHIFT(77),
  [1431] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_delete_column_list, 2),
  [1433] = {.entry = {.count = 1, .reusable = true}}, SHIFT(135),
  [1435] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [1437] = {.entry = {.count = 1, .reusable = true}}, SHIFT(667),
  [1439] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_clustering_key_list, 2),
  [1441] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_partition_key_list, 1),
  [1443] = {.entry = {.count = 1, .reusable = true}}, SHIFT(436),
  [1445] = {.entry = {.count = 1, .reusable = true}}, SHIFT(991),
  [1447] = {.entry = {.count = 1, .reusable = true}}, SHIFT(524),
  [1449] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_data_type_definition_repeat1, 2), SHIFT_REPEAT(56),
  [1452] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_data_type_definition_repeat1, 2),
  [1454] = {.entry = {.count = 1, .reusable = true}}, SHIFT(270),
  [1456] = {.entry = {.count = 1, .reusable = true}}, SHIFT(302),
  [1458] = {.entry = {.count = 1, .reusable = true}}, SHIFT(491),
  [1460] = {.entry = {.count = 1, .reusable = false}}, SHIFT(844),
  [1462] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_expression_list, 1),
  [1464] = {.entry = {.count = 1, .reusable = true}}, SHIFT(474),
  [1466] = {.entry = {.count = 1, .reusable = false}}, SHIFT(757),
  [1468] = {.entry = {.count = 1, .reusable = true}}, SHIFT(464),
  [1470] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_column_definition_list, 1),
  [1472] = {.entry = {.count = 1, .reusable = true}}, SHIFT(469),
  [1474] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_column_definition_list_repeat1, 2), SHIFT_REPEAT(685),
  [1477] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_column_definition_list_repeat1, 2),
  [1479] = {.entry = {.count = 1, .reusable = true}}, SHIFT(192),
  [1481] = {.entry = {.count = 1, .reusable = true}}, SHIFT(839),
  [1483] = {.entry = {.count = 1, .reusable = true}}, SHIFT(92),
  [1485] = {.entry = {.count = 1, .reusable = true}}, SHIFT(138),
  [1487] = {.entry = {.count = 1, .reusable = true}}, SHIFT(482),
  [1489] = {.entry = {.count = 1, .reusable = true}}, SHIFT(371),
  [1491] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_materialized_view_where, 4),
  [1493] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_materialized_view_where_repeat1, 2), SHIFT_REPEAT(649),
  [1496] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_materialized_view_where_repeat1, 2),
  [1498] = {.entry = {.count = 1, .reusable = true}}, SHIFT(364),
  [1500] = {.entry = {.count = 1, .reusable = true}}, SHIFT(140),
  [1502] = {.entry = {.count = 1, .reusable = true}}, SHIFT(158),
  [1504] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_column_definition, 3, .production_id = 1),
  [1506] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_double_quote, 1),
  [1508] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_column_name, 1),
  [1510] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_select_element, 1),
  [1512] = {.entry = {.count = 1, .reusable = true}}, SHIFT(393),
  [1514] = {.entry = {.count = 1, .reusable = true}}, SHIFT(396),
  [1516] = {.entry = {.count = 1, .reusable = true}}, SHIFT(209),
  [1518] = {.entry = {.count = 1, .reusable = true}}, SHIFT(99),
  [1520] = {.entry = {.count = 1, .reusable = true}}, SHIFT(207),
  [1522] = {.entry = {.count = 1, .reusable = true}}, SHIFT(134),
  [1524] = {.entry = {.count = 1, .reusable = true}}, SHIFT(544),
  [1526] = {.entry = {.count = 1, .reusable = true}}, SHIFT(668),
  [1528] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_single_quote, 1),
  [1530] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_init_cond_hash_item, 3, .production_id = 61),
  [1532] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_expression, 1),
  [1534] = {.entry = {.count = 1, .reusable = true}}, SHIFT(674),
  [1536] = {.entry = {.count = 1, .reusable = true}}, SHIFT(346),
  [1538] = {.entry = {.count = 1, .reusable = true}}, SHIFT(580),
  [1540] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [1542] = {.entry = {.count = 1, .reusable = true}}, SHIFT(932),
  [1544] = {.entry = {.count = 1, .reusable = true}}, SHIFT(840),
  [1546] = {.entry = {.count = 1, .reusable = true}}, SHIFT(838),
  [1548] = {.entry = {.count = 1, .reusable = true}}, SHIFT(743),
  [1550] = {.entry = {.count = 1, .reusable = true}}, SHIFT(118),
  [1552] = {.entry = {.count = 1, .reusable = true}}, SHIFT(434),
  [1554] = {.entry = {.count = 1, .reusable = true}}, SHIFT(860),
  [1556] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_column_not_null, 4),
  [1558] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_escaped_double_quote, 2, .production_id = 10),
  [1560] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_escaped_double_quote, 2, .production_id = 10),
  [1562] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_dot_sep, 1),
  [1564] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [1566] = {.entry = {.count = 1, .reusable = true}}, SHIFT(1012),
  [1568] = {.entry = {.count = 1, .reusable = true}}, SHIFT(513),
  [1570] = {.entry = {.count = 1, .reusable = true}}, SHIFT(449),
  [1572] = {.entry = {.count = 1, .reusable = true}}, SHIFT(689),
  [1574] = {.entry = {.count = 1, .reusable = true}}, SHIFT(460),
  [1576] = {.entry = {.count = 1, .reusable = true}}, SHIFT(206),
  [1578] = {.entry = {.count = 1, .reusable = true}}, SHIFT(758),
  [1580] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_primary_key_column, 2),
  [1582] = {.entry = {.count = 1, .reusable = true}}, SHIFT(523),
  [1584] = {.entry = {.count = 1, .reusable = true}}, SHIFT(471),
  [1586] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
  [1588] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_option_hash_item, 3, .production_id = 46),
  [1590] = {.entry = {.count = 1, .reusable = false}}, SHIFT(745),
  [1592] = {.entry = {.count = 1, .reusable = false}}, SHIFT(149),
  [1594] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_replication_list_item, 3, .production_id = 46),
  [1596] = {.entry = {.count = 1, .reusable = true}}, SHIFT(681),
  [1598] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_primary_key_definition, 1, .production_id = 45),
  [1600] = {.entry = {.count = 1, .reusable = true}}, SHIFT(565),
  [1602] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_limit_spec, 2, .production_id = 15),
  [1604] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_delete_column_item, 4, .production_id = 16),
  [1606] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_escaped_single_quote, 2, .production_id = 10),
  [1608] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_escaped_single_quote, 2, .production_id = 10),
  [1610] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_map_entry, 3),
  [1612] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_insert_column_spec, 3),
  [1614] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_trigger_name, 3, .production_id = 18),
  [1616] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_assignment_element, 5, .production_id = 40),
  [1618] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_assignment_element, 5),
  [1620] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [1622] = {.entry = {.count = 1, .reusable = true}}, SHIFT(1005),
  [1624] = {.entry = {.count = 1, .reusable = true}}, SHIFT(711),
  [1626] = {.entry = {.count = 1, .reusable = true}}, SHIFT(647),
  [1628] = {.entry = {.count = 1, .reusable = true}}, SHIFT(931),
  [1630] = {.entry = {.count = 1, .reusable = true}}, SHIFT(226),
  [1632] = {.entry = {.count = 1, .reusable = true}}, SHIFT(644),
  [1634] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_table_option_name, 1),
  [1636] = {.entry = {.count = 1, .reusable = true}}, SHIFT(51),
  [1638] = {.entry = {.count = 1, .reusable = true}}, SHIFT(927),
  [1640] = {.entry = {.count = 1, .reusable = true}}, SHIFT(934),
  [1642] = {.entry = {.count = 1, .reusable = true}}, SHIFT(196),
  [1644] = {.entry = {.count = 1, .reusable = true}}, SHIFT(230),
  [1646] = {.entry = {.count = 1, .reusable = true}}, SHIFT(231),
  [1648] = {.entry = {.count = 1, .reusable = true}}, SHIFT(232),
  [1650] = {.entry = {.count = 1, .reusable = true}}, SHIFT(287),
  [1652] = {.entry = {.count = 1, .reusable = true}}, SHIFT(50),
  [1654] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_index_keys_spec, 4, .production_id = 42),
  [1656] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_index_entries_s_spec, 4, .production_id = 43),
  [1658] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_index_full_spec, 4, .production_id = 44),
  [1660] = {.entry = {.count = 1, .reusable = true}}, SHIFT(166),
  [1662] = {.entry = {.count = 1, .reusable = true}}, SHIFT(514),
  [1664] = {.entry = {.count = 1, .reusable = true}}, SHIFT(225),
  [1666] = {.entry = {.count = 1, .reusable = true}}, SHIFT(590),
  [1668] = {.entry = {.count = 1, .reusable = true}}, SHIFT(897),
  [1670] = {.entry = {.count = 1, .reusable = true}}, SHIFT(539),
  [1672] = {.entry = {.count = 1, .reusable = true}}, SHIFT(510),
  [1674] = {.entry = {.count = 1, .reusable = true}}, SHIFT(53),
  [1676] = {.entry = {.count = 1, .reusable = true}}, SHIFT(892),
  [1678] = {.entry = {.count = 1, .reusable = true}}, SHIFT(625),
  [1680] = {.entry = {.count = 1, .reusable = true}}, SHIFT(818),
  [1682] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_return_mode, 4),
  [1684] = {.entry = {.count = 1, .reusable = true}}, SHIFT(819),
  [1686] = {.entry = {.count = 1, .reusable = true}}, SHIFT(820),
  [1688] = {.entry = {.count = 1, .reusable = true}}, SHIFT(557),
  [1690] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [1692] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [1694] = {.entry = {.count = 1, .reusable = true}}, SHIFT(672),
  [1696] = {.entry = {.count = 1, .reusable = true}}, SHIFT(182),
  [1698] = {.entry = {.count = 1, .reusable = true}}, SHIFT(384),
  [1700] = {.entry = {.count = 1, .reusable = true}}, SHIFT(673),
  [1702] = {.entry = {.count = 1, .reusable = true}}, SHIFT(363),
  [1704] = {.entry = {.count = 1, .reusable = true}}, SHIFT(861),
  [1706] = {.entry = {.count = 1, .reusable = true}}, SHIFT(46),
  [1708] = {.entry = {.count = 1, .reusable = true}}, SHIFT(572),
  [1710] = {.entry = {.count = 1, .reusable = true}}, SHIFT(789),
  [1712] = {.entry = {.count = 1, .reusable = true}}, SHIFT(677),
  [1714] = {.entry = {.count = 1, .reusable = true}}, SHIFT(495),
  [1716] = {.entry = {.count = 1, .reusable = true}}, SHIFT(494),
  [1718] = {.entry = {.count = 1, .reusable = true}}, SHIFT(444),
  [1720] = {.entry = {.count = 1, .reusable = true}}, SHIFT(579),
  [1722] = {.entry = {.count = 1, .reusable = true}}, SHIFT(694),
  [1724] = {.entry = {.count = 1, .reusable = true}}, SHIFT(589),
  [1726] = {.entry = {.count = 1, .reusable = true}}, SHIFT(713),
  [1728] = {.entry = {.count = 1, .reusable = true}}, SHIFT(357),
  [1730] = {.entry = {.count = 1, .reusable = true}}, SHIFT(473),
  [1732] = {.entry = {.count = 1, .reusable = true}}, SHIFT(173),
  [1734] = {.entry = {.count = 1, .reusable = true}}, SHIFT(128),
  [1736] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [1738] = {.entry = {.count = 1, .reusable = true}}, SHIFT(715),
  [1740] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [1742] = {.entry = {.count = 1, .reusable = true}}, SHIFT(1004),
  [1744] = {.entry = {.count = 1, .reusable = true}}, SHIFT(1003),
  [1746] = {.entry = {.count = 1, .reusable = true}}, SHIFT(433),
  [1748] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [1750] = {.entry = {.count = 1, .reusable = true}}, SHIFT(772),
  [1752] = {.entry = {.count = 1, .reusable = true}}, SHIFT(721),
  [1754] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_index_column_spec, 1, .production_id = 1),
  [1756] = {.entry = {.count = 1, .reusable = true}}, SHIFT(327),
  [1758] = {.entry = {.count = 1, .reusable = true}}, SHIFT(43),
  [1760] = {.entry = {.count = 1, .reusable = true}}, SHIFT(217),
  [1762] = {.entry = {.count = 1, .reusable = true}}, SHIFT(765),
  [1764] = {.entry = {.count = 1, .reusable = true}}, SHIFT(133),
  [1766] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_primary_key_definition, 1),
  [1768] = {.entry = {.count = 1, .reusable = true}}, SHIFT(764),
  [1770] = {.entry = {.count = 1, .reusable = true}}, SHIFT(254),
  [1772] = {.entry = {.count = 1, .reusable = true}}, SHIFT(741),
  [1774] = {.entry = {.count = 1, .reusable = true}}, SHIFT(763),
  [1776] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_index_column_spec, 1),
  [1778] = {.entry = {.count = 1, .reusable = true}}, SHIFT(736),
  [1780] = {.entry = {.count = 1, .reusable = true}}, SHIFT(737),
  [1782] = {.entry = {.count = 1, .reusable = true}}, SHIFT(995),
  [1784] = {.entry = {.count = 1, .reusable = true}}, SHIFT(348),
  [1786] = {.entry = {.count = 1, .reusable = true}}, SHIFT(47),
  [1788] = {.entry = {.count = 1, .reusable = true}}, SHIFT(746),
  [1790] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_return_mode, 5),
  [1792] = {.entry = {.count = 1, .reusable = true}}, SHIFT(854),
  [1794] = {.entry = {.count = 1, .reusable = true}}, SHIFT(855),
  [1796] = {.entry = {.count = 1, .reusable = true}}, SHIFT(856),
  [1798] = {.entry = {.count = 1, .reusable = true}}, SHIFT(729),
  [1800] = {.entry = {.count = 1, .reusable = true}}, SHIFT(598),
  [1802] = {.entry = {.count = 1, .reusable = true}}, SHIFT(747),
  [1804] = {.entry = {.count = 1, .reusable = true}}, SHIFT(112),
  [1806] = {.entry = {.count = 1, .reusable = true}}, SHIFT(109),
  [1808] = {.entry = {.count = 1, .reusable = true}}, SHIFT(376),
  [1810] = {.entry = {.count = 1, .reusable = true}}, SHIFT(593),
  [1812] = {.entry = {.count = 1, .reusable = true}}, SHIFT(752),
  [1814] = {.entry = {.count = 1, .reusable = true}}, SHIFT(751),
  [1816] = {.entry = {.count = 1, .reusable = true}}, SHIFT(114),
  [1818] = {.entry = {.count = 1, .reusable = true}}, SHIFT(97),
  [1820] = {.entry = {.count = 1, .reusable = true}}, SHIFT(865),
  [1822] = {.entry = {.count = 1, .reusable = true}}, SHIFT(49),
  [1824] = {.entry = {.count = 1, .reusable = true}}, SHIFT(750),
  [1826] = {.entry = {.count = 1, .reusable = true}}, SHIFT(102),
  [1828] = {.entry = {.count = 1, .reusable = true}}, SHIFT(347),
  [1830] = {.entry = {.count = 1, .reusable = true}}, SHIFT(170),
  [1832] = {.entry = {.count = 1, .reusable = true}}, SHIFT(198),
  [1834] = {.entry = {.count = 1, .reusable = true}}, SHIFT(130),
  [1836] = {.entry = {.count = 1, .reusable = true}}, SHIFT(993),
  [1838] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_column_definition_list, 4),
  [1840] = {.entry = {.count = 1, .reusable = true}}, SHIFT(727),
  [1842] = {.entry = {.count = 1, .reusable = true}}, SHIFT(870),
  [1844] = {.entry = {.count = 1, .reusable = true}}, SHIFT(410),
  [1846] = {.entry = {.count = 1, .reusable = true}}, SHIFT(146),
  [1848] = {.entry = {.count = 1, .reusable = true}}, SHIFT(992),
  [1850] = {.entry = {.count = 1, .reusable = true}}, SHIFT(52),
  [1852] = {.entry = {.count = 1, .reusable = true}}, SHIFT(278),
  [1854] = {.entry = {.count = 1, .reusable = true}}, SHIFT(874),
  [1856] = {.entry = {.count = 1, .reusable = true}}, SHIFT(71),
  [1858] = {.entry = {.count = 1, .reusable = true}}, SHIFT(38),
  [1860] = {.entry = {.count = 1, .reusable = true}}, SHIFT(236),
  [1862] = {.entry = {.count = 1, .reusable = true}}, SHIFT(878),
  [1864] = {.entry = {.count = 1, .reusable = true}}, SHIFT(879),
  [1866] = {.entry = {.count = 1, .reusable = true}}, SHIFT(39),
  [1868] = {.entry = {.count = 1, .reusable = true}}, SHIFT(45),
  [1870] = {.entry = {.count = 1, .reusable = true}}, SHIFT(720),
  [1872] = {.entry = {.count = 1, .reusable = true}}, SHIFT(378),
  [1874] = {.entry = {.count = 1, .reusable = true}}, SHIFT(126),
  [1876] = {.entry = {.count = 1, .reusable = true}}, SHIFT(719),
  [1878] = {.entry = {.count = 1, .reusable = true}}, SHIFT(718),
  [1880] = {.entry = {.count = 1, .reusable = true}}, SHIFT(366),
  [1882] = {.entry = {.count = 1, .reusable = true}}, SHIFT(717),
  [1884] = {.entry = {.count = 1, .reusable = true}}, SHIFT(770),
  [1886] = {.entry = {.count = 1, .reusable = true}}, SHIFT(773),
  [1888] = {.entry = {.count = 1, .reusable = true}}, SHIFT(205),
  [1890] = {.entry = {.count = 1, .reusable = true}}, SHIFT(666),
  [1892] = {.entry = {.count = 1, .reusable = true}}, SHIFT(714),
  [1894] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_compound_key, 3, .production_id = 51),
  [1896] = {.entry = {.count = 1, .reusable = true}}, SHIFT(707),
  [1898] = {.entry = {.count = 1, .reusable = true}}, SHIFT(894),
  [1900] = {.entry = {.count = 1, .reusable = true}}, SHIFT(895),
  [1902] = {.entry = {.count = 1, .reusable = true}}, SHIFT(382),
  [1904] = {.entry = {.count = 1, .reusable = true}}, SHIFT(784),
  [1906] = {.entry = {.count = 1, .reusable = true}}, SHIFT(220),
  [1908] = {.entry = {.count = 1, .reusable = true}}, SHIFT(898),
  [1910] = {.entry = {.count = 1, .reusable = true}}, SHIFT(710),
  [1912] = {.entry = {.count = 1, .reusable = true}}, SHIFT(62),
  [1914] = {.entry = {.count = 1, .reusable = true}}, SHIFT(432),
  [1916] = {.entry = {.count = 1, .reusable = true}}, SHIFT(902),
  [1918] = {.entry = {.count = 1, .reusable = true}}, SHIFT(863),
  [1920] = {.entry = {.count = 1, .reusable = true}}, SHIFT(354),
  [1922] = {.entry = {.count = 1, .reusable = true}}, SHIFT(365),
  [1924] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [1926] = {.entry = {.count = 1, .reusable = true}}, SHIFT(55),
  [1928] = {.entry = {.count = 1, .reusable = true}}, SHIFT(588),
  [1930] = {.entry = {.count = 1, .reusable = true}}, SHIFT(682),
  [1932] = {.entry = {.count = 1, .reusable = true}}, SHIFT(380),
  [1934] = {.entry = {.count = 1, .reusable = true}}, SHIFT(385),
  [1936] = {.entry = {.count = 1, .reusable = true}}, SHIFT(732),
  [1938] = {.entry = {.count = 1, .reusable = true}}, SHIFT(912),
  [1940] = {.entry = {.count = 1, .reusable = true}}, SHIFT(913),
  [1942] = {.entry = {.count = 1, .reusable = true}}, SHIFT(914),
  [1944] = {.entry = {.count = 1, .reusable = true}}, SHIFT(626),
  [1946] = {.entry = {.count = 1, .reusable = true}}, SHIFT(277),
  [1948] = {.entry = {.count = 1, .reusable = true}}, SHIFT(374),
  [1950] = {.entry = {.count = 1, .reusable = true}}, SHIFT(445),
  [1952] = {.entry = {.count = 1, .reusable = true}}, SHIFT(984),
  [1954] = {.entry = {.count = 1, .reusable = true}}, SHIFT(650),
  [1956] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [1958] = {.entry = {.count = 1, .reusable = true}}, SHIFT(733),
  [1960] = {.entry = {.count = 1, .reusable = true}}, SHIFT(596),
  [1962] = {.entry = {.count = 1, .reusable = true}}, SHIFT(706),
  [1964] = {.entry = {.count = 1, .reusable = true}}, SHIFT(983),
  [1966] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [1968] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [1970] = {.entry = {.count = 1, .reusable = true}}, SHIFT(980),
  [1972] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_composite_key, 5),
  [1974] = {.entry = {.count = 1, .reusable = true}}, SHIFT(313),
  [1976] = {.entry = {.count = 1, .reusable = true}}, SHIFT(928),
  [1978] = {.entry = {.count = 1, .reusable = true}}, SHIFT(929),
  [1980] = {.entry = {.count = 1, .reusable = true}}, SHIFT(796),
  [1982] = {.entry = {.count = 1, .reusable = true}}, SHIFT(704),
  [1984] = {.entry = {.count = 1, .reusable = true}}, SHIFT(123),
  [1986] = {.entry = {.count = 1, .reusable = true}}, SHIFT(753),
  [1988] = {.entry = {.count = 1, .reusable = true}}, SHIFT(119),
  [1990] = {.entry = {.count = 1, .reusable = true}}, SHIFT(952),
  [1992] = {.entry = {.count = 1, .reusable = true}}, SHIFT(124),
  [1994] = {.entry = {.count = 1, .reusable = true}}, SHIFT(139),
  [1996] = {.entry = {.count = 1, .reusable = true}}, SHIFT(937),
  [1998] = {.entry = {.count = 1, .reusable = true}}, SHIFT(295),
  [2000] = {.entry = {.count = 1, .reusable = true}}, SHIFT(184),
  [2002] = {.entry = {.count = 1, .reusable = true}}, SHIFT(60),
  [2004] = {.entry = {.count = 1, .reusable = true}}, SHIFT(935),
  [2006] = {.entry = {.count = 1, .reusable = true}}, SHIFT(304),
  [2008] = {.entry = {.count = 1, .reusable = true}}, SHIFT(942),
  [2010] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [2012] = {.entry = {.count = 1, .reusable = true}}, SHIFT(228),
  [2014] = {.entry = {.count = 1, .reusable = true}}, SHIFT(59),
  [2016] = {.entry = {.count = 1, .reusable = true}}, SHIFT(812),
  [2018] = {.entry = {.count = 1, .reusable = true}}, SHIFT(193),
  [2020] = {.entry = {.count = 1, .reusable = true}}, SHIFT(756),
  [2022] = {.entry = {.count = 1, .reusable = true}}, SHIFT(660),
  [2024] = {.entry = {.count = 1, .reusable = true}}, SHIFT(954),
  [2026] = {.entry = {.count = 1, .reusable = true}}, SHIFT(955),
  [2028] = {.entry = {.count = 1, .reusable = true}}, SHIFT(370),
  [2030] = {.entry = {.count = 1, .reusable = true}}, SHIFT(684),
  [2032] = {.entry = {.count = 1, .reusable = true}}, SHIFT(722),
  [2034] = {.entry = {.count = 1, .reusable = true}}, SHIFT(284),
  [2036] = {.entry = {.count = 1, .reusable = true}}, SHIFT(542),
  [2038] = {.entry = {.count = 1, .reusable = true}}, SHIFT(683),
  [2040] = {.entry = {.count = 1, .reusable = true}}, SHIFT(680),
  [2042] = {.entry = {.count = 1, .reusable = true}}, SHIFT(679),
  [2044] = {.entry = {.count = 1, .reusable = true}}, SHIFT(375),
  [2046] = {.entry = {.count = 1, .reusable = true}}, SHIFT(607),
  [2048] = {.entry = {.count = 1, .reusable = true}}, SHIFT(675),
  [2050] = {.entry = {.count = 1, .reusable = true}}, SHIFT(575),
  [2052] = {.entry = {.count = 1, .reusable = true}}, SHIFT(664),
  [2054] = {.entry = {.count = 1, .reusable = true}}, SHIFT(127),
  [2056] = {.entry = {.count = 1, .reusable = true}}, SHIFT(90),
  [2058] = {.entry = {.count = 1, .reusable = true}}, SHIFT(970),
  [2060] = {.entry = {.count = 1, .reusable = true}}, SHIFT(971),
  [2062] = {.entry = {.count = 1, .reusable = true}}, SHIFT(859),
  [2064] = {.entry = {.count = 1, .reusable = true}}, SHIFT(671),
  [2066] = {.entry = {.count = 1, .reusable = true}}, SHIFT(535),
  [2068] = {.entry = {.count = 1, .reusable = true}}, SHIFT(412),
  [2070] = {.entry = {.count = 1, .reusable = true}}, SHIFT(724),
  [2072] = {.entry = {.count = 1, .reusable = true}}, SHIFT(175),
  [2074] = {.entry = {.count = 1, .reusable = true}}, SHIFT(866),
  [2076] = {.entry = {.count = 1, .reusable = true}}, SHIFT(54),
  [2078] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [2080] = {.entry = {.count = 1, .reusable = true}}, SHIFT(871),
  [2082] = {.entry = {.count = 1, .reusable = true}}, SHIFT(735),
  [2084] = {.entry = {.count = 1, .reusable = true}}, SHIFT(342),
  [2086] = {.entry = {.count = 1, .reusable = true}}, SHIFT(515),
  [2088] = {.entry = {.count = 1, .reusable = true}}, SHIFT(876),
  [2090] = {.entry = {.count = 1, .reusable = true}}, SHIFT(266),
  [2092] = {.entry = {.count = 1, .reusable = true}}, SHIFT(974),
  [2094] = {.entry = {.count = 1, .reusable = true}}, SHIFT(64),
  [2096] = {.entry = {.count = 1, .reusable = true}}, SHIFT(877),
  [2098] = {.entry = {.count = 1, .reusable = true}}, SHIFT(265),
  [2100] = {.entry = {.count = 1, .reusable = true}}, SHIFT(880),
  [2102] = {.entry = {.count = 1, .reusable = true}}, SHIFT(517),
  [2104] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_short_index_name, 1, .production_id = 4),
  [2106] = {.entry = {.count = 1, .reusable = true}}, SHIFT(886),
  [2108] = {.entry = {.count = 1, .reusable = true}}, SHIFT(887),
  [2110] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_indexed_column, 4, .production_id = 34),
  [2112] = {.entry = {.count = 1, .reusable = true}}, SHIFT(531),
  [2114] = {.entry = {.count = 1, .reusable = true}}, SHIFT(889),
  [2116] = {.entry = {.count = 1, .reusable = true}}, SHIFT(200),
  [2118] = {.entry = {.count = 1, .reusable = true}}, SHIFT(199),
  [2120] = {.entry = {.count = 1, .reusable = true}}, SHIFT(774),
  [2122] = {.entry = {.count = 1, .reusable = true}}, SHIFT(900),
  [2124] = {.entry = {.count = 1, .reusable = true}}, SHIFT(549),
  [2126] = {.entry = {.count = 1, .reusable = true}}, SHIFT(786),
  [2128] = {.entry = {.count = 1, .reusable = true}}, SHIFT(48),
  [2130] = {.entry = {.count = 1, .reusable = true}}, SHIFT(582),
  [2132] = {.entry = {.count = 1, .reusable = true}}, SHIFT(807),
  [2134] = {.entry = {.count = 1, .reusable = true}}, SHIFT(810),
  [2136] = {.entry = {.count = 1, .reusable = true}}, SHIFT(646),
  [2138] = {.entry = {.count = 1, .reusable = true}}, SHIFT(822),
  [2140] = {.entry = {.count = 1, .reusable = true}}, SHIFT(243),
  [2142] = {.entry = {.count = 1, .reusable = true}}, SHIFT(368),
  [2144] = {.entry = {.count = 1, .reusable = true}}, SHIFT(379),
  [2146] = {.entry = {.count = 1, .reusable = true}}, SHIFT(574),
  [2148] = {.entry = {.count = 1, .reusable = true}}, SHIFT(637),
  [2150] = {.entry = {.count = 1, .reusable = true}}, SHIFT(518),
  [2152] = {.entry = {.count = 1, .reusable = true}}, SHIFT(414),
  [2154] = {.entry = {.count = 1, .reusable = true}}, SHIFT(829),
  [2156] = {.entry = {.count = 1, .reusable = true}}, SHIFT(830),
  [2158] = {.entry = {.count = 1, .reusable = true}}, SHIFT(835),
  [2160] = {.entry = {.count = 1, .reusable = true}}, SHIFT(355),
  [2162] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_column_definition_list, 3),
  [2164] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [2166] = {.entry = {.count = 1, .reusable = true}}, SHIFT(247),
  [2168] = {.entry = {.count = 1, .reusable = true}}, SHIFT(244),
  [2170] = {.entry = {.count = 1, .reusable = true}}, SHIFT(846),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef _WIN32
#define extern __declspec(dllexport)
#endif

extern const TSLanguage *tree_sitter_cql(void) {
  static const TSLanguage language = {
    .version = LANGUAGE_VERSION,
    .symbol_count = SYMBOL_COUNT,
    .alias_count = ALIAS_COUNT,
    .token_count = TOKEN_COUNT,
    .external_token_count = EXTERNAL_TOKEN_COUNT,
    .state_count = STATE_COUNT,
    .large_state_count = LARGE_STATE_COUNT,
    .production_id_count = PRODUCTION_ID_COUNT,
    .field_count = FIELD_COUNT,
    .max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,
    .parse_table = &ts_parse_table[0][0],
    .small_parse_table = ts_small_parse_table,
    .small_parse_table_map = ts_small_parse_table_map,
    .parse_actions = ts_parse_actions,
    .symbol_names = ts_symbol_names,
    .field_names = ts_field_names,
    .field_map_slices = ts_field_map_slices,
    .field_map_entries = ts_field_map_entries,
    .symbol_metadata = ts_symbol_metadata,
    .public_symbol_map = ts_symbol_map,
    .alias_map = ts_non_terminal_alias_map,
    .alias_sequences = &ts_alias_sequences[0][0],
    .lex_modes = ts_lex_modes,
    .lex_fn = ts_lex,
    .primary_state_ids = ts_primary_state_ids,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
