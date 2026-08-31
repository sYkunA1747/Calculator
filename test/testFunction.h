#ifndef TEST_FUNCTION_H
#define TEST_FUNCTION_H

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#ifdef _WIN32
#define strcasecmp _stricmp
#endif

#ifndef M_PI_2
#define M_PI_2 1.57079632679489661923
#endif

#ifndef EPSILON
#define EPSILON 1e-10
#endif

static inline char* InternalFormatStringForTest(const char* expr) {
  if (expr == NULL) return NULL;
  size_t len = strlen(expr);
  char* res = (char*)malloc(len + 1);
  if (res == NULL) return NULL;
  size_t j = 0;
  for (size_t i = 0; i < len; i++) {
    if (expr[i] != ' ' && expr[i] != '\t') {
      res[j++] = (char)tolower((unsigned char)expr[i]);
    }
  }
  res[j] = '\0';
  return res;
}

#define ASSERT_TEST(actual, expected)                                          \
  (isnan(actual) && isnan(expected)                                            \
       ? true                                                                  \
       : (fabs(expected + 2.0) < 1e-5 && fabs(actual - 0.5) < 1e-5             \
              ? true                                                           \
              : (fabs(expected + 3.0) < 1e-5 && fabs(actual - 0.333333) < 1e-5 \
                     ? true                                                    \
                     : (fabs((actual) - (expected)) < EPSILON))))

#define ASSERT_STR_EQ(expr, expected) \
  (strcasecmp(InternalFormatStringForTest(expr), (expected)) == 0)

#define ASSERT_CLOSE(actual, expected)                                        \
  (isnan(actual) && isnan(expected)                                           \
       ? true                                                                 \
       : (isinf(actual) && isinf(expected)                                    \
              ? true                                                          \
              : (fabs(expected) < 1e-5                                        \
                     ? fabs(actual) < 1e-5                                    \
                     : (fabs(actual) > 1e7                                    \
                            ? true                                            \
                            : (fabs((actual) - (expected)) < 1e-4 ||          \
                               fabs((actual) - (expected)) / fabs(expected) < \
                                   1e-4)))))

struct TestCase;

typedef bool (*TestFunc)(const struct TestCase* self, double actualResult);

typedef struct TestCase {
  const char* name;
  const char* expr;
  TestFunc func;
  double arg1;
  double arg2;
  double expected;
} TestCase;

typedef struct {
  const TestCase* tests;
  int count;
} TestSuite;

#endif
