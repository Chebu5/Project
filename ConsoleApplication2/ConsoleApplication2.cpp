#include <iostream>
#include <filesystem>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
void get_files(vector<string>& paths, const string& current_path) {
	for (const auto& file : filesystem::directory_iterator(current_path)) {
		if (filesystem::is_directory(file)) {
			get_files(paths, file.path().string());
		}
		else {
			paths.push_back(file.path().string());
		}
	}
}
int main() {
	setlocale(LC_ALL, "RU");
	vector<string>paths;
	get_files(paths, "D:\\Код для Vs\\ConsoleApplication2\\ConsoleApplication2");
	for (int i = 0; i < paths.size(); i++) {
		cout << paths[i] << endl;
	}
}