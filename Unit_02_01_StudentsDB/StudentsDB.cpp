#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class Student {
private:
    string name;
    int id;
    double gpa;

public:
    Student(string n, int i, double g)
        : name(n), id(i), gpa(g) {}

    string getName() const { return name; }
    int getId() const { return id; }
    double getGpa() const { return gpa; }

    void display() const {
        cout << left << setw(15) << name
             << setw(10) << id
             << setw(10) << fixed << setprecision(2) << gpa << endl;
    }
};

class StudentsDB {
private:
    vector<Student> students;

public:
    void addStudent(const Student& s) {
        students.push_back(s);
        cout << "Student added successfully!\n";
    }

    void displayAll() const {
        if (students.empty()) {
            cout << "No student records found.\n";
            return;
        }

        cout << left << setw(15) << "Name"
             << setw(10) << "ID"
             << setw(10) << "GPA" << endl;
        cout << string(35, '-') << endl;

        for (const auto& s : students)
            s.display();
    }

    void searchById(int id) const {
        for (const auto& s : students) {
            if (s.getId() == id) {
                cout << "Student found:\n";
                s.display();
                return;
            }
        }
        cout << "Student with ID " << id << " not found.\n";
    }
};

bool validateProfessor() {
    string name;
    cout << "Enter professor name for validation: ";
    getline(cin, name);

    if (name == "Uju Makhene") {
        cout << "Access granted.\n\n";
        return true;
    } else {
        cout << "Access denied. Invalid professor name.\n";
        return false;
    }
}

int main() {
    if (!validateProfessor())
        return 0;

    StudentsDB db;
    int choice;

    do {
        cout << "\n===== Student Database Menu =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student by ID\n";
        cout << "4. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string name;
            int id;
            double gpa;

            cout << "Enter student name: ";
            getline(cin, name);
            cout << "Enter student ID: ";
            cin >> id;
            cout << "Enter student GPA: ";
            cin >> gpa;
            cin.ignore();

            Student s(name, id, gpa);
            db.addStudent(s);
        }
        else if (choice == 2) {
            db.displayAll();
        }
        else if (choice == 3) {
            int searchId;
            cout << "Enter student ID to search: ";
            cin >> searchId;
            cin.ignore();
            db.searchById(searchId);
        }
        else if (choice == 4) {
            cout << "Exiting program. Goodbye!\n";
        }
        else {
            cout << "Invalid option. Try again.\n";
        }

    } while (choice != 4);

    return 0;
}


