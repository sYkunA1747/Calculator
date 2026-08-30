#include "testFunction.h"
#include <stdio.h>

int main() {
    printf("Запуск проверки тестов...\n");

    printf("Тестируем Plus...\n");     TestCalculatePlus(5.0, 2.0);
    printf("Тестируем Minus...\n");    TestCalculateMinus(5.0, 2.0);
    printf("Тестируем Multiply...\n"); TestCalculateMultiply(5.0, 2.0);
    printf("Тестируем Division...\n"); TestCalculateDivision(5.0, 2.0);
    printf("Тестируем NthRoot...\n");  TestCalculateNthRoot(25.0, 2.0);
    printf("Тестируем Pow...\n");      TestCalculatePow(5.0, 2.0);

    printf("Тестируем Cos...\n");     TestCalculateCos(0.0);
    printf("Тестируем Sin...\n");     TestCalculateSin(0.0);
    
    printf("Тестируем ArcCos...\n");  TestCalculateArcCos(0.5);
    printf("Тестируем ArcSin...\n");  TestCalculateArcSin(0.5);
    printf("Тестируем ArcTan...\n");  TestCalculateArcTan(1.0);
    printf("Тестируем ArcCot...\n");  TestCalculateArcCot(1.0);

    printf("Тестируем Tan_Valid...\n"); TestCalculateTan_Valid(0.0);
    printf("Тестируем Cot_Valid...\n"); TestCalculateCot_Valid(M_PI_2);

    printf("Тестируем Tan_Singularity...\n");    TestCalculateTan_Singularity();
    printf("Тестируем Cot_Singularity...\n");    TestCalculateCot_Singularity();
    printf("Тестируем ArcCos_InvalidInput...\n"); TestCalculateArcCos_InvalidInput();
    printf("Тестируем ArcSin_InvalidInput...\n"); TestCalculateArcSin_InvalidInput();

    printf("Тестируем ParseOneStr...\n");   TestParseOneStr();
    printf("Тестируем ParseTwoStr...\n");   TestParseTwoStr();
    printf("Тестируем ParseThreeStr...\n"); TestParseThreeStr();

    printf("Все тесты успешно вызваны! Сборка и линковка прошли чики-пуки.\n");
    return 0;
}
