(identifier
  (quoted_identifier
    left_quote: (double_quote) @string
    right_quote: (double_quote) @string
  )
)

(escaped_double_quote
  escape_char: (double_quote) @diff.minus
)

[
  (comma_sep)
  (dot_sep)
  (semi_sep)
] @punctuation.delimiter


[
  (select_statement)
] @keyword

[
  (keyspace_name)
] @module

[
  (table_name)
  (column_name)
] @Identifier

[
  (column_glob)
] @string.regexp

; [
; ] @attribute
;
; [
; ] @punctuation.bracket
;
; [
; ] @field
; @variablexxx guifg=#cdd6f5
; @variable.builtinxxx guifg=#f38ba9
; @variable.parameterxxx guifg=#eba0ad
; @variable.parameter.builtinxxx links to Special
; @constantxxx links to Constant
; @constant.builtinxxx guifg=#fab388
; @modulexxx cterm=italic gui=italic guifg=#b4beff
; @module.builtinxxx links to Special
; @labelxxx links to Label
; @stringxxx links to String
; @string.regexpxxx guifg=#fab388
; @string.specialxxx links to Special
; @string.escapexxx guifg=#f5c2e8
; @string.special.urlxxx cterm=underline,italic gui=underline,italic guifg=#f5e0dd
; @characterxxx links to Character
; @character.specialxxx links to SpecialChar
; @booleanxxx links to Boolean
; @numberxxx links to Number
; @number.floatxxx links to Float
; @typexxx links to Type
; @type.builtinxxx guifg=#f9e2b0
; @attributexxx links to Constant
; @attribute.builtinxxx links to Special
; @propertyxxx guifg=#b4beff
; @functionxxx links to Function
; @function.builtinxxx guifg=#fab388
; @constructorxxx guifg=#74c7ed
; @operatorxxx links to Operator
; @keywordxxx links to Keyword
; @punctuationxxx links to Delimiter
; @punctuation.specialxxx links to Special
; @commentxxx links to Comment
; @comment.errorxxx guifg=#1e1e2f guibg=#f38ba9
; @comment.warningxxx guifg=#1e1e2f guibg=#f9e2b0
; @comment.notexxx guifg=#1e1e2f guibg=#89b4fb
; @comment.todoxxx guifg=#1e1e2f guibg=#f2cdce
; @markupxxx guifg=#cdd6f5
; @markup.strongxxx cterm=bold gui=bold guifg=#eba0ad
; @markup.italicxxx cterm=italic gui=italic guifg=#eba0ad
; @markup.strikethroughxxx cterm=strikethrough gui=strikethrough guifg=#cdd6f5
; @markup.underlinexxx links to Underlined
; @markup.headingxxx cterm=bold gui=bold guifg=#89b4fb
; @markup.linkxxx links to Tag
; @diffxxx cleared
; @diff.plusxxx links to diffAdded
; @diff.minusxxx links to diffRemoved
; @diff.deltaxxx links to diffChanged
; @tagxxx guifg=#cba6f8
; @tag.builtinxxx links to Special
; @lspxxx cleared
; @lsp.type.classxxx links to @type
; @lsp.type.commentxxx links to @comment
; @lsp.type.enumxxx links to @type
; @lsp.type.enumMemberxxx links to @constant
; @lsp.type.eventxxx links to @type
; @lsp.type.functionxxx links to @function
; @lsp.type.interfacexxx guifg=#f2cdce
; @lsp.type.keywordxxx links to @keyword
; @lsp.type.macroxxx links to @constant.macro
; @constant.macroxxx links to Macro
; @lsp.type.methodxxx links to @function.method
; @function.methodxxx links to Function
; @lsp.type.modifierxxx links to @type.qualifier
; @type.qualifierxxx links to Keyword
; @lsp.type.namespacexxx links to @module
; @lsp.type.numberxxx links to @number
; @lsp.type.operatorxxx links to @operator
; @lsp.type.parameterxxx links to @parameter
; @lsp.type.propertyxxx links to @property
; @lsp.type.regexpxxx links to @string.regexp
; @lsp.type.structxxx links to @type
; @lsp.type.typexxx links to @type
; @lsp.type.typeParameterxxx links to @type.definition
; @type.definitionxxx links to Type
; @lsp.type.variablexxx cleared
; @lsp.mod.deprecatedxxx links to DiagnosticDeprecated
; @variable.memberxxx guifg=#b4beff
; @keyword.functionxxx guifg=#cba6f8
; @string.documentationxxx guifg=#94e2d6
; @markup.listxxx links to Special
; @punctuation.delimiterxxx links to Delimiter
; @markup.link.urlxxx cterm=underline,italic gui=underline,italic guifg=#f5e0dd
; @comment.hintxxx guifg=#1e1e2f guibg=#89b4fb
; @markup.mathxxx guifg=#89b4fb
; @markup.rawxxx guifg=#94e2d6
; @markup.environmentxxx guifg=#f5c2e8
; @markup.environment.namexxx guifg=#89b4fb
; @nonexxx cleared
; @tag.delimiterxxx guifg=#89dcec
; @tag.attributexxx cterm=italic gui=italic guifg=#94e2d6
; @markup.link.labelxxx links to Label
; @keyword.repeatxxx links to Repeat
; @keyword.directivexxx links to PreProc
; @namespacexxx cterm=italic gui=italic guifg=#b4beff
; @function.method.callxxx links to Function
; @keyword.returnxxx guifg=#cba6f8
; @keyword.operatorxxx links to Operator
; @keyword.importxxx links to Include
; @function.macroxxx guifg=#94e2d6
; @function.callxxx links to Function
; @keyword.exceptionxxx links to Exception
; @keyword.directive.definexxx links to Define
; @punctuation.bracketxxx guifg=#9399b3
; @markup.heading.1.markdownxxx links to rainbow1
; @markup.heading.2.markdownxxx links to rainbow2
; @markup.heading.3.markdownxxx links to rainbow3
; @markup.heading.4.markdownxxx links to rainbow4
; @markup.heading.5.markdownxxx links to rainbow5
; @markup.heading.6.markdownxxx links to rainbow6
; @lsp.typemod.variable.injectedxxx links to @variable
; @lsp.typemod.variable.defaultLibraryxxx links to @variable.builtin
; @lsp.typemod.type.defaultLibraryxxx links to @type.builtin
; @lsp.typemod.string.injectedxxx links to @string
; @lsp.typemod.operator.injectedxxx links to @operator
; @lsp.typemod.method.defaultLibraryxxx links to @function.builtin
; @lsp.typemod.macro.defaultLibraryxxx links to @function.builtin
; @lsp.typemod.keyword.asyncxxx links to @keyword.coroutine
; @keyword.coroutinexxx links to Keyword
; @lsp.typemod.function.defaultLibraryxxx links to @function.builtin
; @lsp.typemod.enumMember.defaultLibraryxxx links to @constant.builtin
; @lsp.typemod.enum.defaultLibraryxxx links to @type.builtin
; @lsp.typemod.class.defaultLibraryxxx links to @type.builtin
; @lsp.type.unresolvedReferencexxx links to @error
; @lsp.type.typeAliasxxx links to @type.definition
; @lsp.type.selfKeywordxxx links to @variable.builtin
; @keyword.storagexxx links to Keyword
; @lsp.type.formatSpecifierxxx links to @punctuation.special
;  @lsp.type.escapeSequencexxx links to @string.escape
; @lsp.type.builtinTypexxx links to @type.builtin
; @lsp.type.booleanxxx links to @boolean
; @constructor.tsxxxx guifg=#b4beff
; @markup.list.checkedxxx guifg=#a6e3a2
; @markup.list.uncheckedxxx guifg=#7f849d
; @keyword.debugxxx links to Exception
; @keyword.conditionalxxx links to Conditional
; @annotationxxx cleared
; @methodxxx links to Function
; @method.phpxxx links to Function
; @textxxx guifg=#cdd6f5
; @text.titlexxx cterm=bold gui=bold guifg=#89b4fb
; @text.title.5.markdownxxx links to rainbow5
; @text.title.3.markdownxxx links to rainbow3
; @text.title.2.markdownxxx links to rainbow2
; @symbolxxx guifg=#f2cdce
; @symbol.rubyxxx guifg=#f2cdce
; @repeatxxx links to Repeat
; @includexxx links to Include
; @exceptionxxx links to Exception
; @conditionalxxx links to Conditional
; @storageclassxxx links to Keyword
; @preprocxxx links to PreProc
; @definexxx links to Define
; @text.diff.deletexxx links to diffRemoved
; @text.diff.addxxx links to diffAdded
; @method.callxxx links to Function
; @text.dangerxxx guifg=#1e1e2f guibg=#f38ba9
; @text.notexxx guifg=#1e1e2f guibg=#89b4fb
; @text.warningxxx guifg=#1e1e2f guibg=#f9e2b0
; @text.todoxxx guifg=#1e1e2f guibg=#f2cdce
; @text.todo.uncheckedxxx guifg=#7f849d
; @text.todo.checkedxxx guifg=#a6e3a2
; @text.referencexxx links to Tag
; @text.literalxxx guifg=#94e2d6
; @text.environmentxxx guifg=#f5c2e8
; @text.environment.namexxx guifg=#89b4fb
; @text.mathxxx guifg=#89b4fb
; @text.emphasisxxx cterm=italic gui=italic guifg=#eba0ad
; @text.strongxxx cterm=bold gui=bold guifg=#eba0ad
; @string.regexxxx guifg=#fab388
; @fieldxxx guifg=#b4beff
; @parameterxxx guifg=#eba0ad
; @comment.warning.gitcommitxxx guifg=#f9e2b0
; @type.builtin.cppxxx guifg=#f9e2b0
; @property.cppxxx guifg=#cdd6f5
; @type.builtin.cxxx guifg=#f9e2b0
; @function.method.call.phpxxx links to Function
; @function.method.phpxxx links to Function
; @string.special.symbolxxx guifg=#f2cdce
; @string.special.symbol.rubyxxx guifg=#f2cdce
; @constructor.luaxxx guifg=#f2cdce
; @label.jsonxxx guifg=#89b4fb
; @property.tomlxxx guifg=#89b4fb
; @number.cssxxx guifg=#fab388
; @string.plain.cssxxx guifg=#fab388
; @type.tag.cssxxx guifg=#cba6f8
; @type.cssxxx guifg=#b4beff
; @property.cssxxx guifg=#b4beff
; @constant.javaxxx guifg=#94e2d6
; @errorxxx links to Error
; @markup.quotexxx cterm=bold gui=bold guifg=#eba0ad
; @comment.documentationxxx links to Comment
; @keyword.exportxxx guifg=#89dcec
; @keyword.conditional.ternaryxxx links to Operator
; @keyword.modifierxxx links to Keyword
; @string.special.pathxxx links to Special
; @text.strikexxx cterm=strikethrough gui=strikethrough guifg=#cdd6f5
; @text.title.1.markdownxxx links to rainbow1
; @method.call.phpxxx links to Function
; @floatxxx links to Float
; @tag.attribute.tsxxxx cterm=italic gui=italic guifg=#94e2d6
; @constructor.typescriptxxx guifg=#b4beff
; @function.builtin.bashxxx cterm=italic gui=italic guifg=#f38ba9
; @text.title.4.markdownxxx links to rainbow4
; @property.id.cssxxx guifg=#89b4fb
; @property.typescriptxxx guifg=#b4beff
; @property.class.cssxxx guifg=#f9e2b0
; @text.title.6.markdownxxx links to rainbow6
; @text.underlinexxx links to Underlined
; @keyword.typexxx links to Keyword
; @iblxxx cleared
; @ibl.indent.char.1xxx cterm=nocombine gui=nocombine guifg=#313245
; @ibl.whitespace.char.1xxx cterm=nocombine gui=nocombine guifg=#45475b
; @ibl.scope.char.1xxx cterm=nocombine gui=nocombine guifg=#cdd6f5
; @ibl.scope.underline.1xxx cterm=underline gui=underline guisp=#cdd6f5
; @spellxxx cleared
; @concealxxx cleared
; @macroxxx cleared
