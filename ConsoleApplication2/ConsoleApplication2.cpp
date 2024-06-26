#include <iostream>
#include <filesystem>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <string>
#include<Windows.h>
std::size_t simpleHash(const std::string& data) {
    std::size_t hashValue = 0;
    for (char c : data) {
        hashValue = c + (hashValue << 6) + (hashValue << 16) - hashValue;
    }
    return hashValue;
}
// Функция для чтения содержимого файла
std::string readFile(const std::filesystem::path& path) {
    std::ifstream file(path, std::ios::binary);
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return content;
}
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::unordered_map<std::size_t, std::vector<std::filesystem::path>> filesMap;
    std::string directoryPath;
    std::cout << "Введите путь к директории: ";
    std::getline(std::cin, directoryPath);
    if (std::filesystem::exists(directoryPath)) {
        // Поиск файлов и заполнение хеш-таблицы
        for (const auto& entry : std::filesystem::recursive_directory_iterator(directoryPath)) {
            if (entry.is_regular_file()) {
                std::string content = readFile(entry.path());
                std::size_t hashValue = simpleHash(content);
                filesMap[hashValue].push_back(entry.path());
            }
        }

        for (const auto& [hash, paths] : filesMap) {
            if (paths.size() > 1) {
                std::cout << "Найдены дубликаты:\n";
                for (size_t i = 0; i < paths.size(); ++i) {
                    std::cout << i + 1 << ": " << paths[i] << '\n';
                }
                int choice=-3;
                std::cout << "Введите номер файла для удаления или 0 для пропуска: ";
                std::cin >> choice;
                while (choice != 0) {
                    if (choice <= paths.size()) {
                        if (std::filesystem::exists(paths[choice - 1])) {
                            std::filesystem::remove(paths[choice - 1]);
                            std::cout << "Удален файл: " << paths[choice - 1] << '\n';
                        }
                        else
                            std::cout << "Данного файла не существует" << std::endl;
                    }
                    else
                        std::cout << "Данного файла не существует" << std::endl;
                    std::cout << "Введите номер файла для удаления или 0 для пропуска: ";
                    std::cin >> choice;
                }
            }
        }
    }
    else
        std::cout << "Данной папки не существует" << std::endl;

    return 0;
}
