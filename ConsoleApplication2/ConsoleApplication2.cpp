#include <iostream>
#include <filesystem>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <Windows.h>

namespace fs = std::filesystem;

std::string file_hash(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return std::to_string(std::hash<std::string>{}(buffer.str()));
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::unordered_map<std::string, std::vector<std::string>> hashes;
    std::string directory_path;
    std::cout << "Введите путь к директории: ";
    std::getline(std::cin, directory_path);
    if (fs::exists(directory_path)) {
        for (const auto& entry : fs::recursive_directory_iterator(directory_path)) {
            if (fs::is_regular_file(entry.status())) {
                std::string file_path = entry.path().string();
                std::string hash = file_hash(file_path);

                hashes[hash].push_back(file_path);
            }
        }

        for (const auto& [hash, paths] : hashes) {
            if (paths.size() > 1) {
                std::cout << "Найдены дубликаты:\n";
                for (size_t i = 0; i < paths.size(); ++i) {
                    std::cout << i + 1 << ": " << paths[i] << '\n';
                }
                std::cout << "Введите номер файла для удаления или 0 для пропуска: ";
                size_t choice;
                std::cin >> choice;
                while (choice != 0) {
                    if (fs::exists(paths[choice - 1]) && choice > 0 && choice <= paths.size()) {
                        fs::remove(paths[choice - 1]);
                        std::cout << "Удален файл: " << paths[choice - 1] << '\n';

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
