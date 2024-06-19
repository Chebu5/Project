#include <iostream>
#include <filesystem>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
namespace fs = std::filesystem;
std::string file_hash(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return std::to_string(std::hash<std::string>{}(buffer.str()));
}

int main() {
    setlocale(LC_ALL, "RU");
    std::unordered_map<std::string, std::string> hashes;
    //Установить свой путь к папке
    std::string directory_path = "D:\\Код для Vs\\ConsoleApplication2\\ConsoleApplication2\\Папка1";
    for (const auto& entry : fs::recursive_directory_iterator(directory_path)) {
        if (fs::is_regular_file(entry.status())) {
            std::string file_path = entry.path().string();
            std::string hash = file_hash(file_path);

            if (hashes.find(hash) != hashes.end()) {
                std::cout << "Найдены дубликаты: " << endl << file_path << endl << " и " << endl << hashes[hash] << std::endl;
            }
            else {
                hashes[hash] = file_path;
            }
        }
    }

    return 0;
}