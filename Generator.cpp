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

bool loadTasks(const char* filename,char tasks[][MAX_TASK_LENGTH],int& taskCount) {
    // Відкриваємо файл для читання та перевіряємо його відкриття
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Помилка відкриття файлу: "<< filename << '\n';
        return false;
    }
    // Кількість завдань у файлі та рядок для зчитування
    taskCount = 0;
    std::string line;
    // Читання рядків у масив
    while (std::getline(file, line)) {
        // Пропускаємо порожні рядки
        if (line.find_first_not_of(" \t\r") == std::string::npos) {
            continue;
        }
        // Перевіряємо кількість завдань, довжину тексту
        if (taskCount >= MAX_TASKS) {
            std::cerr << "Перевищено максимальну кількість завдань.\n";
            return false;
        }
        if (line.length() >= MAX_TASK_LENGTH) {
            std::cerr << "Занадто довгий текст завдання.\n";
            return false;
        }
        // Копіюємо текст у масив
        std::strcpy(tasks[taskCount], line.c_str());
        taskCount++;
    }
    if (file.bad()) {
        std::cerr << "Помилка читання файлу.\n";
        return false;
    }
    if (taskCount == 0) {
        std::cerr << "Файл не містить завдань.\n";
        return false;
    }
    return true;
}


int main() {
    // Встановлення кодування консолі на UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "Генератор варіантів контрольної роботи\n\n";
    // Завантаження завдань із файлу
    if (!loadTasks("task.txt", tasks, taskCount)) {
        std::cin.get();
        return 1;
    }

    std::cout << "Завдання успішно завантажені!\n";
    std::cout << "Кількість завдань: " << taskCount << '\n';

    std::cin.get();

    return 0;
}