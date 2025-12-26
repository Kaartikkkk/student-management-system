#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct Student {
    int rollNo;
    char name[50];
    int age;
};

// Function declarations
void addStudent();
void viewStudents();
void searchStudent();

int main() {
    int choice;

    do {
        cout << "\n==============================\n";
        cout << "   STUDENT MANAGEMENT SYSTEM  \n";
        cout << "==============================\n";
        cout << "1. Add Student\n";
        cout << "2. View All Students\n";
        cout << "3. Search Student by Roll No\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                viewStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                cout << "Exiting program. Thank you!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}

// Function to add student
void addStudent() {
    Student s;
    ofstream outFile("students.dat", ios::binary | ios::app);

    cout << "\nEnter Roll Number: ";
    cin >> s.rollNo;
    cout << "Enter Name: ";
    cin.ignore();
    cin.getline(s.name, 50);
    cout << "Enter Age: ";
    cin >> s.age;

    outFile.write(reinterpret_cast<char*>(&s), sizeof(s));
    outFile.close();

    cout << "Student record added successfully.\n";
}

// Function to view all students
void viewStudents() {
    Student s;
    ifstream inFile("students.dat", ios::binary);

    if (!inFile) {
        cout << "No records found.\n";
        return;
    }

    cout << "\n----------------------------------------\n";
    cout << left << setw(10) << "Roll No"
         << setw(20) << "Name"
         << setw(5) << "Age" << endl;
    cout << "----------------------------------------\n";

    while (inFile.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        cout << left << setw(10) << s.rollNo
             << setw(20) << s.name
             << setw(5) << s.age << endl;
    }

    inFile.close();
}

// Function to search student
void searchStudent() {
    Student s;
    int roll;
    bool found = false;

    ifstream inFile("students.dat", ios::binary);

    if (!inFile) {
        cout << "No records found.\n";
        return;
    }

    cout << "Enter Roll Number to search: ";
    cin >> roll;

    while (inFile.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.rollNo == roll) {
            cout << "\nStudent Found!\n";
            cout << "Roll No: " << s.rollNo << endl;
            cout << "Name   : " << s.name << endl;
            cout << "Age    : " << s.age << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Student record not found.\n";
    }

    inFile.close();
}

