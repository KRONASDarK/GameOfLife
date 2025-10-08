#include "Functions.h"
#include <iostream>

int main() {
    setlocale(LC_ALL, "Rus");
    std::string filename;
    std::cout << "Введите имя файла с начальной конфигурацией: ";
    std::cin >> filename;

    std::vector<std::vector<char>> universe;
    if (readFile(filename)) {
        std::cerr << "Ошибка при загрузке файла конфигурации." << std::endl;
        return 1;
    }

    writeUniverse(filename, universe);

    if (universe.empty()) {
        std::cerr << "Неверная структура файла." << std::endl;
        return 1;
    }

    int generation = 1;
    std::vector<std::vector<char>> nextGen(universe.size(), std::vector<char>(universe.front().size()));

    while (true) {
        // Подсчет количества живых клеток
        int aliveCells = 0;
        for (auto& row : universe) {
            for (char cell : row) {
                if (cell == '*') aliveCells++;
            }
        }

        // Отображение текущего состояния
        displayUniverse(universe, generation++, aliveCells);

        // Проверка на завершение симуляции
        if (aliveCells == 0) {
            std::cout << "\nВсе клетки умерли.\n";
            break;
        }

        // Эволюционируем игровое поле
        if (!evolve(universe, nextGen)) {
            displayUniverse(universe, generation++, aliveCells);
            std::cout << "\nИгра завершилась, стабильное состояние достигнуто.\n";
            break;
        }
    }

    return 0;
}