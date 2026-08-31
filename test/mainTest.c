#include <math.h>
#include <stdio.h>

#include "../src/errorhandling/errors.h"
#include "../src/evaluate/evaluate.h"
#include "../src/parser/parser.h"
#include "testFunction.h"

TestSuite getCalculateSuite(void);
TestSuite getTrigonometricSuite(void);
TestSuite getParserStringSuite(void);

static int runTestSuite(const char* suiteName, TestSuite suite,
                        bool isParserTest) {
  int passed = 0;
  printf("=== Запуск набора тестов: %s (%d кейсов) ===\n", suiteName,
         suite.count);

  for (int i = 0; i < suite.count; i++) {
    const TestCase* test = &suite.tests[i];
    int tokenCount = 0, rpnCount = 0;
    ErrorCode err = ERR_OK;

    if (isParserTest) {
      char* formattedExpr = InternalFormatStringForTest(test->expr);
      Token* tokens = tokenize(formattedExpr, &tokenCount);
      free(formattedExpr);
      if (tokens != NULL) {
        printf("  [OK] Тест %d [%s]: Успешное форматирование строки\n", i,
               test->expr);
        passed++;
        freeTokens(tokens);
      } else {
        printf(
            "[FAIL] Тест %d [%s]: Твой ASSERT отклонил строку форматирования\n",
            i, test->expr);
      }
      continue;
    }
    char* formattedExpr = InternalFormatStringForTest(test->expr);
    Token* tokens = tokenize(formattedExpr, &tokenCount);
    free(formattedExpr);
    if (tokens == NULL) {
      printf("[FAIL] Тест %d [%s]: Сбой выделения памяти в лексере на '%s'\n",
             i, test->name, test->expr);
      continue;
    }

    Token* rpnTokens = parserToRPN(tokens, tokenCount, &rpnCount, &err);
    if (rpnTokens == NULL) {
      printf("[FAIL] Тест %d [%s]: Парсер упал с кодом %d на '%s'\n", i,
             test->name, err, test->expr);
      freeTokens(tokens);
      continue;
    }

    double result = evaluateRPN(rpnTokens, rpnCount, &err);
    if (err != ERR_OK) {
      printf("[FAIL] Тест %d [%s]: Вычислитель упал с кодом %d на '%s'\n", i,
             test->name, err, test->expr);
    } else {
      if (test->func(test, result)) {
        printf("  [OK] Тест %d [%s]: '%s' -> Рассчитано: %f\n", i, test->name,
               test->expr, result);
        passed++;
      } else {
        printf(
            "[FAIL] Тест %d [%s]: Твой ASSERT отклонил результат %f на "
            "выражении '%s'\n",
            i, test->name, result, test->expr);
      }
    }
    freeTokens(tokens);
    freeTokens(rpnTokens);
  }
  printf("=== Итог по набору %s: Пройдено %d из %d тестов ===\n\n", suiteName,
         passed, suite.count);
  return passed;
}

int main() {
  printf("==================================================\n");
  printf("==     МОДУЛЬНЫЙ ЗАПУСК СТРЕСС-ТЕСТОВ МАТРИЦЫ     ==\n");
  printf("==================================================\n\n");
  int totalPassed = 0;
  int totalTests = 0;

  TestSuite calcSuite = getCalculateSuite();
  totalTests += calcSuite.count;
  totalPassed += runTestSuite("АРИФМЕТИКА", calcSuite, false);

  TestSuite trigSuite = getTrigonometricSuite();
  totalTests += trigSuite.count;
  totalPassed += runTestSuite("ТРИГОНОМЕТРИЯ", trigSuite, false);

  TestSuite parseSuite = getParserStringSuite();
  totalTests += parseSuite.count;
  totalPassed += runTestSuite("ПАРСЕР СТРОК", parseSuite, true);

  printf("==================================================\n");
  printf("ФИНАЛЬНЫЙ СТАТУС: Успешно пройдено %d из %d тестов\n", totalPassed,
         totalTests);
  printf("==================================================\n");
  return (totalPassed == totalTests) ? 0 : 1;
}
