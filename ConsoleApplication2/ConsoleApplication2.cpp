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

    // Получение пути к директории от пользователя
    std::cout << "Введите путь к директории: ";
    std::getline(std::cin,directoryPath);

    // Поиск файлов и заполнение хеш-таблицы
    for (const auto& entry : std::filesystem::recursive_directory_iterator(directoryPath)) {
        if (entry.is_regular_file()) {
            std::string content = readFile(entry.path());
            std::size_t hashValue = simpleHash(content);
            filesMap[hashValue].push_back(entry.path());
        }
    }

    // Поиск и вывод дубликатов
    for (const auto& [hash, paths] : filesMap) {
        if (paths.size() > 1) {
            std::cout << "Найдены дубликаты с хешем " << hash << ":\n";
            for (const auto& path : paths) {
                std::cout<< path << '\n';
            }

            // Запрос на удаление файла
            std::string input;
            while (input != "0") {
                std::cout << "Введите путь к файлу для удаления или '0' для пропуска: ";
                std::cin >> input;
                std::filesystem::remove(input);
                std::cout << "Файл удален: " << input << '\n';
                
            }
        }
    }

    return 0;
}
