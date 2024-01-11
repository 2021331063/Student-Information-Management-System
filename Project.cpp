#include<bits/stdc++.h>
using namespace std;

struct Student {
    string name;
    string fatherName;
    string motherName;
    string address;
    string dateOfBirth;
    string mobileNumber;
    long long registrationNumber;
};

bool readDataFromCSV(vector<Student>& students) {
    ifstream file("students.csv");
    if (!file.is_open()) {
        cerr << "Error opening file for reading!" << endl;
        return false;
    }

    string line;
    getline(file, line); // skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string name, fatherName, motherName, address, dateOfBirth, mobileNumber, regNumberStr;
        getline(ss, name, ',');
        getline(ss, fatherName, ',');
        getline(ss, motherName, ',');
        getline(ss, address, ',');
        getline(ss, dateOfBirth, ',');
        getline(ss, mobileNumber, ',');
        getline(ss, regNumberStr, ',');

        long long registrationNumber;
        stringstream(regNumberStr) >> registrationNumber;

        students.push_back({name, fatherName, motherName, address, dateOfBirth, mobileNumber, registrationNumber});
    }
    file.close();

    return true;
}

bool saveDataToCSV(const vector<Student>& students) {
    ofstream file("students.csv");
    if (!file.is_open()) {
        cout << "Error opening file for writing!" << endl;
        return false;
    }

    file << "Name,Father Name,Mother Name,Address,Date of Birth,Mobile Number,Registration Number\n"; // CSV header

    for (const auto& student : students) {
        file << student.name << "," << student.fatherName << "," << student.motherName << ","
             << student.address << "," << student.dateOfBirth << "," << student.mobileNumber << ","
             << student.registrationNumber << "\n";
    }

    file.close();
    return true;
}

void displayStudent(const Student& student) {

    cout << "| " << setw(22) << student.name
         << " | " << setw(22) << student.fatherName
         << " | " << setw(22) << student.motherName
         << " | " << setw(20) << student.address
         << " | " << setw(12) << student.dateOfBirth
         << " | " << setw(15) << student.mobileNumber
         << " | " << setw(20) << student.registrationNumber
         << " |\n";
}

void displayAllStudents(const vector<Student>& students) {
    cout << "List of Students:\n";
    cout << "----------------------------------------------------------------------"
         << "-------------------------------------------------------------------------------------\n";
    cout << "|                Name    | Father's Name          | Mother's Name          |"
         << " Address              | Date of Birth| Mobile Number   | Registration Number  |\n";
    cout << "----------------------------------------------------------------------"
         << "-------------------------------------------------------------------------------------\n";

    for (const auto& student : students) {
        displayStudent(student);
    }

    cout << "----------------------------------------------------------------------"
         << "-------------------------------------------------------------------------------------\n";
}

bool compareByRegistrationNumber(const Student& a, const Student& b) {
    return a.registrationNumber < b.registrationNumber;
}

template<typename Comparator>
void sortStudents(vector<Student>& students, Comparator compareFunction) {
    sort(students.begin(), students.end(), compareFunction);
}

void sortAndSaveByRegistrationNumber(vector<Student>& students) {
    sortStudents(students, compareByRegistrationNumber);

    if (saveDataToCSV(students)) {
        cout << "Data sorted by registration number and saved to students.csv\n";
    } else {
        cout << "Failed to save sorted data to CSV file.\n";
    }
}

void sortAndSaveByName(vector<Student>& students) {
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.name < b.name;
    });

    if (saveDataToCSV(students)) {
        cout << "Data sorted by name and saved to students.csv\n";
    } else {
        cout << "Failed to save sorted data to CSV file.\n";
    }
}

void addStudent() {
    vector<Student> students;
    if (!readDataFromCSV(students)) {
        cout << "Unable to read data from CSV file.\n";
        return;
    }

    Student newStudent;
    cin.ignore();
    cout << "Enter name: ";
    getline(cin, newStudent.name);
    cout << "Enter father's name: ";
    getline(cin, newStudent.fatherName);
    cout << "Enter mother's name: ";
    getline(cin, newStudent.motherName);
    cout << "Enter address: ";
    getline(cin, newStudent.address);
    cout << "Enter date of birth (DD/MM/YYYY): ";
    getline(cin, newStudent.dateOfBirth);
    cout << "Enter mobile number: ";
    getline(cin, newStudent.mobileNumber);
    cout << "Enter registration number: ";
    cin >> newStudent.registrationNumber;

    students.push_back(newStudent);
    if (saveDataToCSV(students)) {
        cout << "Student added and data saved to students.csv\n";
    } else {
        cout << "Failed to add student and save data to CSV file.\n";
    }
}

void searchByName(const vector<Student>& students, const string& searchName) {
    bool found = false;
    for (const auto& student : students) {
        if (student.name == searchName) {
            displayStudent(student);
            found = true;
        }
    }
    if (!found) {
        cout << "Student with name '" << searchName << "' not found.\n";
    }
}

void searchByRegNumber(const vector<Student>& students, long long regNumber) {
    bool found = false;
    for (const auto& student : students) {
        if (student.registrationNumber == regNumber) {
            cout << "+----------------------+----------------------+----------------------+"
         << "----------------------------+--------------+-----------------+----------------------+\n";
    cout << "| Name                 | Father's Name        | Mother's Name        |"
         << " Address              | Date of Birth | Mobile Number   | Registration Number |\n";
    cout << "+----------------------+----------------------+----------------------+"
         << "----------------------------+--------------+-----------------+----------------------+\n";
            displayStudent(student);
            cout << "+----------------------+----------------------+----------------------+"
         << "----------------------------+--------------+-----------------+----------------------+\n";
            found = true;
        }
    }
    if (!found) {
        cout << "Student with registration number '" << regNumber << "' not found.\n";
    }
}

void editStudentData(vector<Student>& students, long long regNumber) {
    for (auto& student : students) {
        if (student.registrationNumber == regNumber) {
            cout << "Editing information for student with registration number " << regNumber << ":\n";
            cin.ignore();
            cout << "Enter new name: ";
            getline(cin, student.name);
            cout << "Enter new father's name: ";
            getline(cin, student.fatherName);
            cout << "Enter new mother's name: ";
            getline(cin, student.motherName);
            cout << "Enter new address: ";
            getline(cin, student.address);
            cout << "Enter new date of birth (DD/MM/YYYY): ";
            getline(cin, student.dateOfBirth);
            cout << "Enter new mobile number: ";
            getline(cin, student.mobileNumber);

            saveDataToCSV(students); // Save changes to CSV file
            cout << "Student data updated successfully.\n";
            return;
        }
    }

    cout << "Student with registration number '" << regNumber << "' not found.\n";
}

void deleteStudentByRegNumber(vector<Student>& students, long long regNumber) {
    auto it = remove_if(students.begin(), students.end(), [regNumber](const Student& student) {
        return student.registrationNumber == regNumber;
    });

    if (it != students.end()) {
        students.erase(it, students.end());
        saveDataToCSV(students); // Save changes to CSV file
        cout << "Student with registration number '" << regNumber << "' deleted successfully.\n";
    } else {
        cout << "Student with registration number '" << regNumber << "' not found.\n";
    }
}

int main() {
    vector<Student> students;
    if (!readDataFromCSV(students)) {
        cout << "Unable to read data from CSV file.\n";
        return 1;
    }

    int choice = 0;
    while (choice != 9) {
        cout << "\nStudent Information Management System\n";

        cout << " 1. Display All Students\n";
        cout << " 2. Sort  Data by Name\n";
        cout << " 3. Sort  Data by Registration Number\n";
        cout << " 4. Add Student\n";
        cout << " 5. Search Student by Name\n";
        cout << " 6. Search Student by Registration Number\n";
        cout << " 7. Edit Student Data\n";
        cout << " 8. Delete Student by from the file\n";
        cout << " 9. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayAllStudents(students);
                break;
            case 2:
                sortAndSaveByName(students);
                break;
            case 3:
                sortAndSaveByRegistrationNumber(students);
                break;
            case 4:
                addStudent();
                break;
            case 5: {
                cin.ignore();
                string nameToSearch;
                cout << "Enter the name to search: ";
                getline(cin, nameToSearch);
                searchByName(students, nameToSearch);
                break;
            }
            case 6: {
                long long regNumToSearch;
                cout << "Enter the registration number to search: ";
                cin >> regNumToSearch;
                searchByRegNumber(students, regNumToSearch);
                break;
            }
            case 7: {
                long long regNumToEdit;
                cout << "Enter the registration number to edit: ";
                cin >> regNumToEdit;
                editStudentData(students, regNumToEdit);
                break;
            }
            case 8: {
                long long regNumToDelete;
                cout << "Enter the registration number to delete: ";
                cin >> regNumToDelete;
                deleteStudentByRegNumber(students, regNumToDelete);
                break;
            }
            case 9:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
                break;
        }
    }

    return 0;
}