#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

const int MAX_STUDENTS = 100;
const int MAX_SUBJECTS = 10;

string ids[MAX_STUDENTS];
string names[MAX_STUDENTS];
int marks[MAX_STUDENTS][MAX_SUBJECTS];
int numSubjects[MAX_STUDENTS];
int studentCount = 0;
string subjectNames[MAX_SUBJECTS];
int subjectCount = 0;

void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        cout << "Database full!\n";
        return;
    }
    cout << "Enter Student ID: ";
    cin >> ids[studentCount];
    cout << "Enter Student Name: ";
    cin.ignore();
    getline(cin, names[studentCount]);
    numSubjects[studentCount] = subjectCount;
    cout << "Enter marks:\n";
    for (int i = 0; i < subjectCount; ++i) {
    cout << subjectNames[i] << ": ";
    cin >> marks[studentCount][i];
    }    
    studentCount++;
    cout << "Student added!\n";
}

void enterSubjects() {
    cout << "Enter number of subjects: ";
    cin >> subjectCount;
    cin.ignore();
    for (int i = 0; i < subjectCount; ++i) {
        cout << "Enter name of subject " << i + 1 << ": ";
        getline(cin, subjectNames[i]);
    }
}

void searchByID() {
    string key;
    cout << "Enter Student ID to search: ";
    cin >> key;
    bool found = false;
    for (int i = 0; i < studentCount; ++i) {
        if (ids[i] == key) {
            found = true;
            cout << "Name: " << names[i] <<"\n";
            for (int j = 0; j < numSubjects[i]; ++j) {
                cout << subjectNames[j]<<" : "<<marks[i][j] << " ";
            }
            double sum = 0;
            for (int j = 0; j < numSubjects[i]; ++j) {
                sum += marks[i][j];
            }
            cout << "\nAverage: " << (sum / numSubjects[i]) << "\n";
            break;
        }
    }
    if (!found) {
        cout << "Student not found!\n";
    }
}

void searchByName() {
    string key;
    cout << "Enter Student Name to search: ";
    cin.ignore();
    getline(cin, key);
    bool found = false;
    for (int i = 0; i < studentCount; ++i) {
        if (names[i] == key) {
            found = true;
            cout << "ID: " << ids[i] << "\nMarks: ";
            for (int j = 0; j < numSubjects[i]; ++j) {
                cout << subjectNames[j]<<" : "<<marks[i][j] << " ";
            }
            double sum = 0;
            for (int j = 0; j < numSubjects[i]; ++j) {
                sum += marks[i][j];
            }
            cout << "\nAverage: " << (sum / numSubjects[i]) << "\n";
            break;
        }
    }
    if (!found) {
        cout << "Student not found!\n";
    }
}

void rankStudents() {
    cout << "Available Subjects:\n";
    for (int i = 0; i < subjectCount; ++i) {
        cout << i << ". " << subjectNames[i] << "\n";
    }
    
    int subjectIndex;
    cout << "Enter subject index: ";
    cin >> subjectIndex;

    if (subjectIndex < 0 || subjectIndex >= subjectCount) {
        cout << "Invalid subject index!\n";
        return;
    }

    int score[MAX_STUDENTS];
    string studentNames[MAX_STUDENTS];

    for (int i = 0; i < studentCount; ++i) {
        if (subjectIndex < numSubjects[i]) {
            score[i] = marks[i][subjectIndex];
            studentNames[i] = names[i];
        } else {
            score[i] = -1;  
        }
    }

    for (int i = 0; i < studentCount; ++i) {
        for (int j = i + 1; j < studentCount; ++j) {
            if (score[i] < score[j]) {
                swap(score[i], score[j]);
                swap(studentNames[i], studentNames[j]);
            }
        }
    }

    cout << "Ranking by " << subjectNames[subjectIndex] << ":\n";
    int rank = 1;
    for (int i = 0; i < studentCount; ++i) {
        if (score[i] >= 0) {
            cout << rank++ << ". " << studentNames[i] << " -> " << score[i] << "\n";
        }
    }
}

void showProgress() {
    double avg[MAX_STUDENTS];
    string studentNames[MAX_STUDENTS];

    for (int i = 0; i < studentCount; ++i) {
        double sum = 0;
        for (int j = 0; j < numSubjects[i]; ++j) {
            sum += marks[i][j];
        }
        avg[i] = sum / numSubjects[i];
        studentNames[i] = names[i];
    }

    for (int i = 0; i < studentCount; ++i) {
        for (int j = i + 1; j < studentCount; ++j) {
            if (avg[i] < avg[j]) {
                swap(avg[i], avg[j]);
                swap(studentNames[i], studentNames[j]);
            }
        }
    }

    cout << "Progress Trends:\n";
    for (int i = 0; i < studentCount; ++i) {
        cout << studentNames[i] << ": " << avg[i] << "\n";
    }
}

int main() {
    int choice;
    cout<<" Hola! Welcome to my DSA mini-project\n";
    do {
        cout << "\nStudent Performance Analyzer\n";
        cout << "1. Add Subjects\n2. Add Student\n3. Search by ID\n4. Search by Name\n5. Rank Students\n6. Show Progress Trends\n0. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 2: addStudent(); break;
            case 1: enterSubjects(); break;
            case 3: searchByID(); break;
            case 4: searchByName(); break;
            case 5: rankStudents(); break;
            case 6: showProgress(); break;
            case 0: cout << "The End\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}
