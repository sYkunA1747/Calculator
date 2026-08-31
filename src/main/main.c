#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../errorhandling/errors.h"
#include "../evaluate/evaluate.h"
#include "../parser/parser.h"

#define LEN 1024

int main(int argc, char* argv[]) {
  char expr[LEN];
  Token *tokens, *rpnTokens;
  double result = 0.0;
  int rpnCount = 0, tokenCount = 0;
  ErrorCode err = ERR_OK;
  if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      tokens = tokenize(argv[i], &tokenCount);
      if (tokens == NULL) {
        logError(ERROR_MEMORY_ALLOCATION, "Лексический анализ");
        return 1;
      }
      rpnTokens = parserToRPN(tokens, tokenCount, &rpnCount, &err);
      if (rpnTokens == NULL) {
        logError(err, "Синтаксический анализ");
        freeTokens(tokens);
        return 1;
      }
      result = evaluateRPN(rpnTokens, rpnCount, &err);
      if (err != ERR_OK) {
        logError(err, " Вычислитель ОПЗ");
        freeTokens(tokens);
        freeTokens(rpnTokens);
        return 1;
      }
      printf("Результат: %f\n", result);
      freeTokens(tokens);
      freeTokens(rpnTokens);
    }
    return 0;
  }
  while (1) {
    printf("calculate : ");
    fflush(stdout);
    if (fgets(expr, sizeof(expr), stdin) == NULL) break;
    expr[strcspn(expr, "\n")] = '\0';
    if (strcmp(expr, "exit") == 0) break;
    if (strlen(expr) == 0) {
      printf("пустое выражение, Введите выражение или 'exit'.\n");
      continue;
    }
    tokens = tokenize(expr, &tokenCount);
    if (tokens == NULL) {
      logError(ERROR_MEMORY_ALLOCATION, "Лексический анализ");
      continue;
    }
    rpnTokens = parserToRPN(tokens, tokenCount, &rpnCount, &err);
    if (rpnTokens == NULL) {
      logError(err, "Синтаксический анализ");
      freeTokens(tokens);
      continue;
    }
    result = evaluateRPN(rpnTokens, rpnCount, &err);
    if (err != ERR_OK) {
      logError(err, " Вычислитель ОПЗ");
      freeTokens(tokens);
      freeTokens(rpnTokens);
      continue;
    }
    printf("Результат: %f\n", result);
    freeTokens(tokens);
    freeTokens(rpnTokens);
  }
  return 0;
}
