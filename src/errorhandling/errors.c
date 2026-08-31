#include "errors.h"

#include <stdio.h>

static const char* error_messages[] = {
    "Операция выполнена успешно.",
    "Критическая ошибка лексера: обнаружен неизвестный символ.",
    "Ошибка синтаксиса: обнаружена лишняя закрывающая скобка ')'.",
    "Ошибка синтаксиса: обнаружена незакрытая открывающая скобка '('.",
    "Ошибка вычисления: недостаточно операндов для выполнения операции.",
    "Системная ошибка: не удалось выделить динамическую память (Heap "
    "Overflow)."};

void logError(ErrorCode code, const char* contex) {
  if (code < 0 || code >= sizeof(error_messages) / sizeof(error_messages[0])) {
    fprintf(stderr, "Неизвестный код ошибки (%d).\n", code);
    return;
  }
  if (contex != NULL && contex[0] != '\0')
    fprintf(stderr, "[Ошибка] %s (котнекст: %s)\n", error_messages[code],
            contex);
  else
    fprintf(stderr, "[Ошибка] %s\n", error_messages[code]);
}