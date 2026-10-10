#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <random>
#include <algorithm>
#include <limits>
#include <windows.h>

// Максимальні розміри даних
const int MAX_TASKS = 1000, MAX_TASK_LENGTH = 500, MAX_VARIANTS = 100, MAX_TASKS_PER_VARIANT = 50;
// Масив текстів завдань
char tasks[MAX_TASKS][MAX_TASK_LENGTH];
// Матриця індексів завдань для варіантів
int variants[MAX_VARIANTS][MAX_TASKS_PER_VARIANT];
// Кількість завдань, зчитаних із файлу
int taskCount = 0;






int main() {
    // Встановлення кодування консолі на UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "Генератор варіантів контрольної роботи\n";
    std::cout << "Масиви та матриця успішно оголошені.\n";

    return 0;
}