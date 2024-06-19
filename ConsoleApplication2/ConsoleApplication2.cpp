#include <iostream>
#include <filesystem>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <Windows.h>

namespace fs = std::filesystem;
using namespace std;
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
    getline(cin,directory_path);

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
            for (const auto& path : paths) {
                std::cout << path << '\n';
            }
            std::cout << "Удалить эти файлы? (Да/Нет): ";
            string choice;
            std::cin >> choice;
            if (choice == "Да" || choice == "да"|| choice=="ДА") {
                for (const auto& path : paths) {
                    fs::remove(path);
                    std::cout << "Удален файл: " << path << '\n';
                }
            }
        }
    }

    return 0;
}
