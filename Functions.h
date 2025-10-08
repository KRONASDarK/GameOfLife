#pragma once

#include <iostream>
#include <fstream>
#include <vector>

// Структура для хранения координат клетки
struct Cell {
    int row, col;
};

// Чтение файла.
bool readFile(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Ошибка открытия файла: ";
        return true;
    }
    return false;
}

// Функция для чтения стартового состояния игрового поля из файла
void writeUniverse(const std::string& filename, std::vector<std::vector<char>>& universe) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Файл не открыт." << std::endl;
        return;
    }

    // Чтение размеров игрового поля
    int rows, cols;
    infile >> rows >> cols;
    universe.resize(rows, std::vector<char>(cols, '-'));

    // Чтение начальных живых клеток
    while (infile.good()) {
        int row, col;
        infile >> row >> col;
        if (infile.fail() || infile.bad()) break;
        universe[row][col] = '*';
    }
}

// Функция для подсчета живых соседей клетки
int countNeighbors(const std::vector<std::vector<char>>& universe, int row, int col) {
    const int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 }; // Смещения по оси X
    const int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 }; // Смещения по оси Y
    int count = 0;

    for (int k = 0; k < 8; ++k) {
        int nRow = row + dx[k];
        int nCol = col + dy[k];
        if (nRow >= 0 && nRow < universe.size() &&
            nCol >= 0 && nCol < universe[nRow].size() &&
            universe[nRow][nCol] == '*') {
            count++;
        }
    }
    return count;
}

// Обновление клетки в зависимости от правил игры
char nextCellState(char currentState, int liveNeighbors) {
    if (currentState == '-') {
        return (liveNeighbors == 3 ? '*' : '-');
    }
    else {
        return ((liveNeighbors == 2 || liveNeighbors == 3) ? '*' : '-');
    }
}

// Вывод текущего состояния игрового поля
void displayUniverse(const std::vector<std::vector<char>>& universe, int generation, int aliveCells) {
    std::cout << "\nПоколение: " << generation << ", Живые клетки: " << aliveCells << std::endl;
    for (const auto& row : universe) {
        for (char cell : row) {
            std::cout << cell << ' ';
        }
        std::cout << '\n';
    }
}

// Основная логика игры
bool evolve(std::vector<std::vector<char>>& universe, std::vector<std::vector<char>>& nextGeneration) {
    bool changed = false;
    int rows = universe.size();
    int cols = universe.front().size();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            char currentState = universe[i][j];
            int liveNeighbors = countNeighbors(universe, i, j);
            char nextState = nextCellState(currentState, liveNeighbors);
            nextGeneration[i][j] = nextState;
            if (currentState != nextState) changed = true;
        }
    }

    // Меняем местами старую и новую версию поля
    universe.swap(nextGeneration);
    return changed;
}