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
        std::cerr << "ERROR: Помилка відкриття файлу: "<< filename << '\n';
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
            std::cerr << "ERROR: Перевищено максимальну кількість завдань.\n";
            return false;
        }
        if (line.length() >= MAX_TASK_LENGTH) {
            std::cerr << "ERROR: Занадто довгий текст завдання.\n";
            return false;
        }
        // Копіюємо текст у масив
        std::strcpy(tasks[taskCount], line.c_str());
        taskCount++;
    }
    if (file.bad()) {
        std::cerr << "ERROR: Помилка читання файлу.\n";
        return false;
    }
    if (taskCount == 0) {
        std::cerr << "ERROR: Файл не містить завдань.\n";
        return false;
    }
    std::cout << "Повідомлення: Завантажено завдань: "<< taskCount << "\n\n";
    return true;
}
// Функція для цілого числа з консолі
int readPositiveInteger(const char* prompt, int minValue, int maxValue) {
    int value;

    while (true) {
        std::cout << prompt;
        if (!(std::cin >> value)) {
            if (std::cin.eof()) {
                std::cerr << "ERROR: Введення недоступне.\n";
                std::exit(1);
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'
            );
            std::cerr << "ERROR: Помилка: введіть ціле число.\n";
            continue;
        }
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n'
        );
        if (value < minValue || value > maxValue) {
            std::cerr << "ERROR: Введіть число від "<< minValue << " до " << maxValue << ".\n";
            continue;
        }
        return value;
    }
}
// Функція для виведення параметрів генерації
bool printParameters(int variantCount, int tasksPerVariant, int taskCount) {
    if (variantCount != 0 && tasksPerVariant != 0 && taskCount != 0) {
        std::cout << "\nПараметри генерації:\n";
        std::cout << "Кількість варіантів: "<< variantCount << '\n';
        std::cout << "Завдань у кожному варіанті: "<< tasksPerVariant << '\n';
        return true;
    } else {
        std::cerr << "ERROR: Параметри генерації не встановлені.\n";
        return false;
    }
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
// Функція для виведення варіантів у консоль
void printVariants(const int variants[][MAX_TASKS_PER_VARIANT],int variantCount,int tasksPerVariant,const char tasks[][MAX_TASK_LENGTH]) {
    for (int i = 0; i < variantCount; i++) {
        std::cout << "\n========================================\n"<< "             ВАРІАНТ №" << i + 1 << '\n'<< "========================================\n";
        for (int j = 0; j < tasksPerVariant; j++) {
            int taskIndex = variants[i][j];
            std::cout << "\nЗавдання " << j + 1
                      << " (№" << taskIndex + 1
                      << " у банку):\n";
            std::cout << tasks[taskIndex] << "\n";
        }
    }
    std::cout << "\n========================================\n"<< "Генерацію завершено.\n";
}
bool saveVariants(const char* filename,const int variants[][MAX_TASKS_PER_VARIANT],int variantCount,int tasksPerVariant,const char tasks[][MAX_TASK_LENGTH]) {
    // Відкриваємо файл для запису та перевіряємо його відкриття
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "ERROR: Помилка створення файлу: "<< filename << '\n';
        return false;
    }
    // Записуємо результати у файл
    file << "ГЕНЕРАТОР ВАРІАНТІВ КОНТРОЛЬНОЇ РОБОТИ\n"<< "========================================\n\n"<< "Кількість варіантів: "<< variantCount << '\n'<< "Завдань у кожному варіанті: "<< tasksPerVariant << "\n\n";
    for (int i = 0; i < variantCount; i++) {
        file << "========================================\n"<< "ВАРІАНТ №" << i + 1 << '\n'<< "========================================\n";
        for (int j = 0; j < tasksPerVariant; j++) {
            int taskIndex = variants[i][j];
            file << "\nЗавдання " << j + 1<< " (№" << taskIndex + 1<< " у банку):\n"<< tasks[taskIndex] << '\n';
        }
        file << '\n';
    }
    // Перевірка на помилки запису
    file.flush();
    if (!file) {
        std::cerr << "ERROR: Помилка запису у файл: "<< filename << '\n';
        return false;
    }
    //Закриваємо файл
    file.close();
    // Перевірка на помилки закриття файлу
    if (file.fail()) {
        std::cerr << "ERROR: Помилка завершення запису файлу.\n";
        return false;
    }
    std::cout << "\nПовідомлення: Результат збережено у файл variants.txt\n";
    return true;
}
int main() {
    // Встановлення кодування консолі на UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    std::cout << "--Генератор варіантів контрольної роботи--\n\n";
    // Завантаження завдань із файлу
    if (!loadTasks("task.txt", tasks, taskCount)) {return 1;}
    // Зчитування параметрів генерації
    int variantCount = readPositiveInteger("Введіть кількість варіантів (1-100): ", 1, MAX_VARIANTS);
    int tasksPerVariant = readPositiveInteger("Введіть кількість завдань у кожному варіанті (1-50): ", 1, std::min(MAX_TASKS_PER_VARIANT, taskCount));
    // Виведення параметрів генерації
    if (!printParameters(variantCount, tasksPerVariant, taskCount)) {return 1;}
    // Генерація варіантів
    generateVariants(variants,variantCount,tasksPerVariant,taskCount);
    // Виведення варіантів у консоль
    printVariants(variants,variantCount,tasksPerVariant,tasks);
    // Збереження варіантів у файл
    if (!saveVariants("variants.txt",variants,variantCount,tasksPerVariant,tasks)) {return 1;}
    return 0;
}