#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>

#define MAX_TOKEN_LEN 22
#define START_SIZE 128

#ifndef FUNCTION_LIST
#define FUNCTION_LIST            \
  X("sin", TOKEN_SIN)            \
  X("cos", TOKEN_COS)            \
  X("tan", TOKEN_TAN)            \
  X("cot", TOKEN_COT)            \
  X("arcsin", TOKEN_ARCSIN)      \
  X("arccos", TOKEN_ARCCOS)      \
  X("arctan", TOKEN_ARCTAN)      \
  X("arccot", TOKEN_ARCCOT)      \
  X("mypow", TOKEN_POW_FUNCTION) \
  X("nthroot", TOKEN_NTHROOT_FUNCTION)
#endif

typedef enum {
  STATE_SPACE_HANDLING,
  STATE_VARIABLE_HANDLING,
  STATE_OPERATOR_HANDLING,
  STATE_FUNCTION_HANDLING,
  STATE_ERROR_HANDLING
} States;

typedef enum {
  TOKEN_VARIABLE,
  TOKEN_NUMBER,

  // Operator
  TOKEN_PLUS,
  TOKEN_UNAR_MINUS,
  TOKEN_MINUS,
  TOKEN_MULTIPLY,
  TOKEN_DIVISION,
  TOKEN_POW_OPERATOR,
  TOKEN_NTHROOT_OPERATOR,

#define X(str, enum_type) enum_type,
  FUNCTION_LIST
#undef X

      // Parens
      TOKEN_OPEN_PAREN,
  TOKEN_CLOSE_PAREN,

  // Special Tokens
  TOKEN_UNKNOWN,
  TOKEN_EOF

} TypeToken;

typedef struct {
  TypeToken token;
  union {
    double number;
    char name[MAX_TOKEN_LEN];
  } Val;
} Token;

typedef struct {
  const char* str;
  int index;
  int count;
  States type;
  Token* tokens;
  int capacity;
} Context;

typedef struct {
  int precedence;
  bool isAssociative;
  bool isOperator;
  bool isRightAssociative;
  bool isFunction;
} TokenProperties;

/*********************************/
/*     FUNCTION PROTOTYPES       */
/*                               */
/******************************* */
bool dispatchState(Context* context);
Token* tokenize(const char* expr, int* tokenCount);

bool isOperator(TypeToken type);
bool isFunction(TypeToken type);
bool isOperand(TypeToken type);
bool isRightAssociative(TypeToken type);

void freeTokens(Context* context);

bool parserToRPN(const Context* inCtx, Context* outCtx);

#endif