#include <stdio.h>
#include "labD.h"


void expectEq(const char* testName, int got, int expected) {
    if (got == expected) {
        printf("OK %s\n", testName);
    }
    else {
        printf("FAIL %s\n", testName);
    }
}

//Тесты 

//1.Пустой список (крайний случай)
void TestEmptyInput_no1() {
    expectEq("TestEmptyInput_no1",minUnfinished(NULL, 0),0);
}

//2.Один вагон — укладывается в дедлайн
void TestSingleWagon_HappyPath_no2() {
    Wagon w[] = { {2, 5} };
    expectEq("TestSingleWagon_HappyPath_no2",minUnfinished(w, 1),0);
}

//3.Один вагон — не укладывается
void TestSingleWagon_DeadlineMiss_no3() {
    Wagon w[] = { {6, 5} };
    expectEq("TestSingleWagon_DeadlineMiss_no3",minUnfinished(w, 1),1);
}

//4.Несколько вагонов — все укладываются
void TestAllWagonsFit_HappyPath_no4() {
    Wagon w[] = { {1, 3}, {2, 5}, {1, 6} };
    expectEq("TestAllWagonsFit_HappyPath_no4",minUnfinished(w, 3),0);
}

//5.Ни один вагон не может быть выполнен
void TestNoWagonFits_no5() {
    Wagon w[] = { {5, 1}, {6, 2}, {7, 3} };
    expectEq("TestNoWagonFits_no5",minUnfinished(w, 3),3);
}

//6.Все дедлайны одинаковые
void TestSameDeadlines_VariousTimes_no6() {
    Wagon w[] = { {3, 5}, {4, 5}, {2, 5} };
    expectEq("TestSameDeadlines_VariousTimes_no6",minUnfinished(w, 3),1);
}

//7.Все времена одинаковые
void TestSameTimes_VariousDeadlines_no7() {
    Wagon w[] = { {2, 2}, {2, 4}, {2, 6} };
    expectEq("TestSameTimes_VariousDeadlines_no7",minUnfinished(w, 3),0);
}

//8.Конфликт — удаляется самый долгий вагон
void TestRemoveLongestOnConflict_no8() {
    Wagon w[] = { {4, 4}, {3, 5}, {1, 6} };
    expectEq("TestRemoveLongestOnConflict_no8",minUnfinished(w, 3),1);
}

//9. Случайный порядок входных данных
void TestUnsortedInput_no9() {
    Wagon w[] = { {3, 4}, {2, 3}, {1, 5}, {4, 6} };
    expectEq("TestUnsortedInput_no9",minUnfinished(w, 4),2);
}

//10. Сложный комбинированный сценарий
void TestComplexScenario_no10() {
    Wagon w[] = { {5, 5}, {2, 6}, {3, 7}, {4, 8} };
    expectEq("TestComplexScenario_no10",minUnfinished(w, 4),2);
}

int main() {
    TestEmptyInput_no1();
    TestSingleWagon_HappyPath_no2();
    TestSingleWagon_DeadlineMiss_no3();
    TestAllWagonsFit_HappyPath_no4();
    TestNoWagonFits_no5();
    TestSameDeadlines_VariousTimes_no6();
    TestSameTimes_VariousDeadlines_no7();
    TestRemoveLongestOnConflict_no8();
    TestUnsortedInput_no9();
    TestComplexScenario_no10();
    return 0;
}