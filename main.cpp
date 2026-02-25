#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Student {
    int roll;
    char name[50];
    float marks;

public:
    void getData() {
        cout << "\nEnter Roll No: ";
        cin >> roll;
        cin.ignore();
        cout << "Enter Name: ";
        cin.getline(name, 50);
        cout << "Enter Marks: ";
        cin >> marks;
    }

    void showData() const {
        cout << left << setw(10) << roll
             << setw(20) << name
             << setw(10) << marks << endl;
    }

    int getRoll() const {
        return roll;
    }
};

// Add Record
void addStudent() {
    Student s;
    ofstream file("students.dat", ios::binary | ios::app);
    s.getData();
    file.write((char*)&s, sizeof(s));
    file.close();
    cout << "Record Added Successfully!\n";
}

// Display All
void displayAll() {
    Student s;
    ifstream file("students.dat", ios::binary);
    cout << "\nRoll      Name                Marks\n";
    cout << "-------------------------------------\n";
    while (file.read((char*)&s, sizeof(s))) {
        s.showData();
    }
    file.close();
}

// Search
void searchStudent() {
    Student s;
    int r, found = 0;
    ifstream file("students.dat", ios::binary);

    cout << "Enter Roll No to search: ";
    cin >> r;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.getRoll() == r) {
            cout << "\nRecord Found:\n";
            s.showData();
            found = 1;
        }
    }
    file.close();
    if (!found)
        cout << "Record Not Found!\n";
}

// Delete
void deleteStudent() {
    Student s;
    int r;
    ifstream file("students.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    cout << "Enter Roll No to delete: ";
    cin >> r;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.getRoll() != r)
            temp.write((char*)&s, sizeof(s));
    }

    file.close();
    temp.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    cout << "Record Deleted!\n";
}

int main() {
    int choice;

    do {
        cout << "\n===== Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addStudent(); break;
        case 2: displayAll(); break;
        case 3: searchStudent(); break;
        case 4: deleteStudent(); break;
        case 5: cout << "Goodbye!\n"; break;
        default: cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}
