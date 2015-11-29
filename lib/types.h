#ifndef __types_h
#define __types_h

#ifndef YYTOKENTYPE
#define YYTOKENTYPE

// Tokens: must be kept in sync when changes are made to lexer/parser
enum yytokentype {
  TOKEN_TRUE = 258,
  TOKEN_FALSE = 259,
  TOKEN_LOCAL_ASSIGN = 260,
  TOKEN_COLON = 261,
  TOKEN_IMPORT = 262,
  TOKEN_SEMICOLON = 263,
  TOKEN_LINE_END = 264,
  TOKEN_COMMA = 265,
  TOKEN_STRING = 266,
  TOKEN_EVAL_STRING = 267,
  TOKEN_INTEGER = 268,
  TOKEN_FLOAT = 269,
  TOKEN_REGEX = 270,
  TOKEN_ID = 271,
  TOKEN_CLASS_ID = 272,
  TOKEN_DEFERRED_ARGUMENT = 273,
  TOKEN_ELIPSES = 274,
  TOKEN_DOT = 275,
  TOKEN_FUNCTION_DECLARATION = 276,
  TOKEN_OPEN_BRACE = 277,
  TOKEN_CLOSE_BRACE = 278,
  TOKEN_OPEN_PAREN = 279,
  TOKEN_CLOSE_PAREN = 280,
  TOKEN_AND = 281,
  TOKEN_OR = 282,
  TOKEN_EQUALITY = 283,
  TOKEN_STRICT_EQUALITY = 284,
  TOKEN_NOT = 285,
  TOKEN_EOF = 286,
  TOKEN_LEX_ERROR_ILLEGAL_VARIABLE = 287,
  TOKEN_LEX_ERROR_UNKNOWN_TOKEN = 288
};

#endif

enum {
  // Number types
  FX_INT_SHORT = TOKEN_EOF+10,
  FX_INT_STANDARD,
  FX_INT_LONG,
  FX_INT_LLONG,
  FX_DECIMAL_DOUBLE,
  FX_DECIMAL_LDOUBLE,

  // Bit Types
  FX_BIT_STRING,
  FX_BIT_NUMBER,

  // Expression Types
  FX_ST_LITERAL,
  FX_ST_LOOKUP,
  FX_ST_METHOD_CALL,
  FX_ST_FUNCTION_DEFINITION,
  FX_ST_GROUPED,
  FX_ST_LIST,
  FX_ST_METHOD_CALL_ARGUMENTS,
  FX_ST_FUNCTION_DEFINITION_ARGUMENTS,
  FX_ST_LOCAL_ASSIGN,
  FX_ST_COLON_EXPRESSION,
  FX_ST_EXPORT,
  FX_ST_EXPRESSIONS,

  // Contexts
  FX_OBJECT,
  FX_CLASS,
  FX_GLOBALS
};


#endif
