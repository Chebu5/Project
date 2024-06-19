#include <iostream>
#include <filesystem>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <windows.h>
using namespace std;
namespace fs = std::filesystem;
std::string file_hash(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return std::to_string(std::hash<std::string>{}(buffer.str()));
}

int main() {
    string director_path;
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::unordered_map<std::string, std::string> hashes;
    std::string directory_path = "D:\\ConsoleApplication2\\ConsoleApplication2\\Папка1";

    for (const auto& entry : fs::recursive_directory_iterator(directory_path)) {
        if (fs::is_regular_file(entry.status())) {
            std::string file_path = entry.path().string();
            std::string hash = file_hash(file_path);

            if (hashes.find(hash) != hashes.end()) {
                std::cout << "Найдены дубликаты: " << endl << "1." << file_path << endl << " и " << endl << "2." << hashes[hash] << std::endl;
                cout << "Введите путь к файлу который хотите удалить: ";
                getline(cin, director_path);
                if (fs::remove(director_path) != 0)
                    cout << "Файл успешно удалён" << endl;
                else
                    cout << "Ошибка удаления файла" << endl;

            }
            else {
                hashes[hash] = file_path;
            }
        }
    }

    return 0;

}