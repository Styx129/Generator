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
// Функція для завантаження завдань із файлу
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
// Функція для цілого числа з консолі
int readPositiveInteger(const char* prompt){
    int value;

    std::cout << prompt;
    std::cin >> value;

    return value;
}
// Функція для генерації варіантів
void generateVariants(int variants[][MAX_TASKS_PER_VARIANT],int variantCount,int tasksPerVariant,int taskCount) {
    int indexes[MAX_TASKS];
    // Ініціалізація рандомайзера
    std::random_device rand;
    std::mt19937 generator(rand());
    for (int i = 0; i < variantCount; i++) {
        // Створюємо масив індексів усіх завдань
        for (int j = 0; j < taskCount; j++) {
            indexes[j] = j;
        }
        // Рандомайзер індексів завдань
        std::shuffle(indexes,indexes + taskCount,generator);

        // Записуємо вибрані завдання в матрицю
        for (int j = 0; j < tasksPerVariant; j++) {
            variants[i][j] = indexes[j];
        }
    }
}

int main() {
    // Встановлення кодування консолі на UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    std::cout << "Генератор варіантів контрольної роботи\n\n";
    // Завантаження завдань із файлу
    if (!loadTasks("task.txt", tasks, taskCount)) {return 1;}
    std::cout << "Завантажено завдань: "<< taskCount << "\n\n";
    // Зчитування кількості варіантів та завдань у кожному варіанті та перевірка їх
    int variantCount = readPositiveInteger("Введіть кількість варіантів: ");
    if (variantCount < 1 || variantCount > MAX_VARIANTS) {
        std::cerr << "Помилка: кількість варіантів має бути від 1 до " << MAX_VARIANTS << ".\n";
        return 1;
    }    
    int tasksPerVariant = readPositiveInteger("Введіть кількість завдань у варіанті: ");
    if (tasksPerVariant < 1 || tasksPerVariant > MAX_TASKS_PER_VARIANT || tasksPerVariant > taskCount) {
        std::cerr << "Помилка: некоректна кількість завдань "
                  << "у варіанті.\n";
        return 1;
    }
    std::cout << "\nПараметри генерації:\n";
    std::cout << "Кількість варіантів: "<< variantCount << '\n';
    std::cout << "Завдань у кожному варіанті: "<< tasksPerVariant << '\n';
    // Генерація варіантів
    generateVariants(variants,variantCount,tasksPerVariant,taskCount);
    std::cout << "\nЗгенеровані варіанти:\n";
    // Виведення згенерованих варіантів у вигляді індексів
    for (int i = 0; i < variantCount; i++) {
        std::cout << "Варіант " << i + 1 << ": ";
        for (int j = 0; j < tasksPerVariant; j++) {
            std::cout << variants[i][j] + 1 << " ";
        }
        std::cout << '\n';
    }
    return 0;
}