#include "Functions.h"
#include <iostream>

int main() {
    setlocale(LC_ALL, "Rus");
    std::string filename;
    std::cout << "������� ��� ����� � ��������� �������������: ";
    std::cin >> filename;

    std::vector<std::vector<char>> universe;
    if (readFile(filename)) {
        std::cerr << "������ ��� �������� ����� ������������." << std::endl;
        return 1;
    }

    writeUniverse(filename, universe);

    if (universe.empty()) {
        std::cerr << "�������� ��������� �����." << std::endl;
        return 1;
    }

    int generation = 1;
    std::vector<std::vector<char>> nextGen(universe.size(), std::vector<char>(universe.front().size()));

    while (true) {
        // ������� ���������� ����� ������
        int aliveCells = 0;
        for (auto& row : universe) {
            for (char cell : row) {
                if (cell == '*') aliveCells++;
            }
        }

        // ����������� �������� ���������
        displayUniverse(universe, generation++, aliveCells);

        // �������� �� ���������� ���������
        if (aliveCells == 0) {
            std::cout << "\n��� ������ ������.\n";
            break;
        }

        // �������������� ������� ����
        if (!evolve(universe, nextGen)) {
            displayUniverse(universe, generation++, aliveCells);
            std::cout << "\n���� �����������, ���������� ��������� ����������.\n";
            break;
        }
    }

    return 0;
}