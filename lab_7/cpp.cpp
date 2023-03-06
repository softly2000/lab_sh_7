#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Student {
    string surname;
    string name;
    string direction;
    int course;
};

int main() {
    Student* students = new Student[1000];
    int num_students = 0;
    Student* duplicates = new Student[1000];
    int num_duplicates = 0;

    ifstream input_file("text.txt");
    if (!input_file.is_open()) {
        cout << "Невозможно открыть входной файл" << endl;
        return 1;
    }

    int course = 0;
    string line;
    while (getline(input_file, line)) {
        string surname, name, direction;
        // если строка содержит число, то это курс
        if (isdigit(line[0])) {
            course = stoi(line);
            getline(input_file, surname);
            getline(input_file, direction);
            students[num_students++] = {surname, name, direction, course};
        }
        else {
            name = line;
            getline(input_file, surname);
            getline(input_file, direction);
            students[num_students++] = {surname, name, direction, course};
        }
    }
    input_file.close();

    // анализируем данные и выводим результат
    for (int i = 0; i < num_students; i++) {
        cout << "Направления - " << students[i].direction << endl;
        cout << "Курс - " << students[i].course << endl;
        cout << "\t" << students[i].surname << " " << students[i].name << endl;
        for (int j = i + 1; j < num_students;) {
            if (students[i].direction == students[j].direction && students[i].course == students[j].course) {
                cout << "\t" << students[j].surname << " " << students[j].name << endl;
                duplicates[num_duplicates++] = students[j];
                for (int k = j; k < num_students - 1; k++) {
                    students[k] = students[k + 1];
                }
                num_students--;
            }
            else {
                j++;
            }
        }
        cout << endl;
    }

    delete[] students;
    delete[] duplicates;

    return 0;
}