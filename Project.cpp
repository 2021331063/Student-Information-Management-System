#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Student {
    string name;
    string fatherName;
    string motherName;
    string address;
    string dateOfBirth;
    string mobileNumber;
    string email;
    string bloodGroup;  
    long long registrationNumber;

};

bool readDataFromCSV(vector<Student>& students) {
    ifstream file("students.csv");
    if (!file.is_open()) {
        cerr << "Error opening file for reading!" << endl;
        return false;
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string name, fatherName, motherName, address, dateOfBirth, mobileNumber, email, bloodGroup, regNumberStr;
        getline(ss, name, ',');
        getline(ss, fatherName, ',');
        getline(ss, motherName, ',');
        getline(ss, address, ',');
        getline(ss, dateOfBirth, ',');
        getline(ss, mobileNumber, ',');
        getline(ss, email, ',');
        getline(ss, bloodGroup, ','); 
        getline(ss, regNumberStr, ',');

        long long registrationNumber;
        stringstream(regNumberStr) >> registrationNumber;

        students.push_back({name, fatherName, motherName, address, dateOfBirth, mobileNumber, email, bloodGroup, registrationNumber});
    }
    file.close();

    return true;
}
bool saveDataToCSV(const vector<Student>& students) {
    ofstream file("students.csv");
    if (!file.is_open()) {
        cerr << "Error opening file for writing!" << endl;
        return false;
    }

    file << "Name,Father Name,Mother Name,Address,Date of Birth,Mobile Number,Email,Blood Group,Registration Number\n"; 

    for (const auto& student : students) {
        file << student.name << "," << student.fatherName << "," << student.motherName << ","
             << student.address << "," << student.dateOfBirth << "," << student.mobileNumber << ","
             << student.email << "," << student.bloodGroup << "," << student.registrationNumber << "\n";
    }

    file.close();
    return true;
}

void displayStudent(const Student& student) {
    cout << "| " << setw(15) << student.name
         << " | " << setw(15) << student.fatherName
         << " | " << setw(15) << student.motherName
         << " | " << setw(12) << student.address
         << " | " << setw(12) << student.dateOfBirth
         << " | " << setw(15) << student.mobileNumber
         << " | " << setw(30) << student.email
         << " | " << setw(13) << student.bloodGroup
         << " | " << setw(13) << student.registrationNumber
         << " |\n";
}
void displayAllStudents(const vector<Student>& students) {
    cout << "List of Students:\n";
    cout << "----------------------------------------------------------------------"
         << "--------------------------------------------------------------------------------------------------\n";
    cout << "|             Name|    Father's Name|    Mother's Name|"
         << "       Address| Date of Birth|    Mobile Number|                           Email|    Blood Group|    Reg. Number|\n";
    cout << "----------------------------------------------------------------------"
         << "--------------------------------------------------------------------------------------------------\n";

    for (const auto& student : students) {
        displayStudent(student);
    }

    cout << "----------------------------------------------------------------------"
         << "--------------------------------------------------------------------------------------------------\n";
}
void addStudent(vector<Student>& students) {
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
    cout << "Enter email: ";
    getline(cin, newStudent.email);
    cout << "Enter blood group: ";
    getline(cin, newStudent.bloodGroup);
    cout << "Enter registration number: ";
    cin >> newStudent.registrationNumber;

    students.push_back(newStudent);
    saveDataToCSV(students);
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
void searchByName(const vector<Student>& students, const string& searchName) {
    bool found = false;
    for (const auto& student : students) {
        if (student.name == searchName) {
            cout << "List of Students:\n";
    cout << "----------------------------------------------------------------------"
         << "--------------------------------------------------------------------------------------------------\n";
    cout << "|             Name|    Father's Name|    Mother's Name|"
         << "       Address| Date of Birth|    Mobile Number|                           Email|    Blood Group|    Reg. Number|\n";
    cout << "----------------------------------------------------------------------"
         << "--------------------------------------------------------------------------------------------------\n";
            displayStudent(student);
            cout << "----------------------------------------------------------------------"
         << "--------------------------------------------------------------------------------------------------\n";
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
            cout << "List of Students:\n";
    cout << "----------------------------------------------------------------------"
         << "--------------------------------------------------------------------------------------------------\n";
    cout << "|             Name|    Father's Name|    Mother's Name|"
         << "       Address| Date of Birth|    Mobile Number|                           Email|    Blood Group|    Reg. Number|\n";
    cout << "----------------------------------------------------------------------"
         << "--------------------------------------------------------------------------------------------------\n";
            displayStudent(student);
             cout << "----------------------------------------------------------------------"
         << "--------------------------------------------------------------------------------------------------\n";
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
            cout << "Now edit what you want: " <<endl<<"1.Name"<<endl<<"2.Father name"<<endl<<"3.Mother name"
            <<endl<<"4.Date of Birth"<<endl<<"5.Address"<<endl<<"6.Mobile Number"<<endl<<"7.Email"
            <<endl<<"8.Bloodbroup"<<endl<<"9.All"<<endl;
            int s;
            cout<<"Enter the button with which data you want to edit: ";
            cin>>s;
            cin.ignore();
            switch(s){
            case 1:
            cout << "Enter new name: ";
            getline(cin, student.name);
            break;
             case 2:

            cout << "Enter modified father name: ";
            getline(cin, student.fatherName);
            break;

             case 3:
               {
            cout << "Enter modified mother name: ";
            getline(cin, student.motherName);
            break;
            }
             case 4:
                {
            cout << "Enter new address: ";
            getline(cin, student.address);
            break;
            }
             case 5:
                {
            cout << "Enter new date of birth (DD/MM/YYYY): ";
            getline(cin, student.dateOfBirth);
            break;
            }
             case 6:
                {
            cout << "Enter new mobile number: ";
            getline(cin, student.mobileNumber);
            break;
            }
             case 7:
                {
            cout << "Enter new email: ";
            getline(cin, student.email);
            break;
            }
             case 8:
                {
                 cout << "Enter new bloodgroup: ";
                 getline(cin, student.bloodGroup);
                 break;
                }
            case 9:
               {
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
            cout << "Enter new email: ";
            getline(cin, student.email);
            break;
            }
            default :
                  cout<<"Enter valid optin"<<endl;
                  break;
            }
            saveDataToCSV(students); 
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
        saveDataToCSV(students); 
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
    long long regToSearch;
    int choice = 0;
    int choicets = 0;
    string nameToSearch;
    while (choice != 8) {
        cout << "\nStudent Information Management System\n";

        cout << " 1. Display All Students\n";
        cout << " 2. Add Student\n";
        cout << " 3. Search Student\n";
        cout << " 4. Edit Student Data\n";
        cout << " 5. Sort  Data by Name\n";
        cout << " 6. Sort  Data by Registration Number\n";
        cout << " 7. Delete Student\n";
        cout << " 8. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayAllStudents(students);
                break;
            case 2:
                addStudent(students);
                break;
            case 3:{
               cout<<"How you want to search student?"<<endl;
                    cout<<"1. By Name"<<endl<<"2. By Registration Number"<<endl;
                    cin>>choicets;
                    switch(choicets){
                             case 1:
                                {
                                cout << "Enter the Name to search: ";
                                cin.ignore();
                                getline(cin, nameToSearch);
                                searchByName(students, nameToSearch);
                                break;
                                }
                             case 2:
                                {
                                 cout << "Enter the Registration Number to search: ";
                                 cin >> regToSearch;
                                 searchByRegNumber(students, regToSearch);
                                break;
                                }
                             default :
                                 cout<<"You click wrong key \n";
                                 break;
                           }
                           break;
            }
            case 4: {
                long long regNumToEdit;
                cout << "Enter the registration number to edit: ";
                cin >> regNumToEdit;
                editStudentData(students, regNumToEdit);
                break;
            }
            case 5:
                sortAndSaveByName(students);
                break;
            case 6:
                sortAndSaveByRegistrationNumber(students);
                break;
            case 7: {
                long long regNumToDelete;
                cout << "Enter the registration number to delete: ";
                cin >> regNumToDelete;
                deleteStudentByRegNumber(students, regNumToDelete);
                break;
            }
            case 8:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
                break;
        }
    }

    return 0;
}
