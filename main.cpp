#include <iostream>
#include <string>
#include <set>
#include <vector>
// validation header file
#include "Validation.h" 

using namespace std;
const int maxSize = 2; // Maximum number of classes per student

// Student class
class Student {
public:
    int id;
    string name;
    string address;
    string dob;  // Date of birth
    string contact;
    string classes[maxSize];    
    int grades[maxSize];        
    int attendance[maxSize];   

    // Constructor to initialize the student object
    Student() {
        id = 0;
        name = "";
        address = "";
        dob = "";
        contact = "";
        for (int i = 0; i < maxSize; i++) {
            classes[i] = "";   
            grades[i] = 0;      
            attendance[i] = 0;  
        }
    }
    ~Student(){
        
    };             

};

// Node for linked list
struct Node {
    Student student;  
    Node* next;      
};

// Global pointer to the head of the linked list
Node* head = nullptr;

// Function to add a new student
void addStudent() {
    Node* newNode = new Node;

    // Validate numeric ID
    newNode->student.id = getValidNumericInput("Enter Student ID: ");

    // Validate name
    newNode->student.name = getValidStringInput("Enter Student Name: ");

    // Validate address
    newNode->student.address = getValidStringInput("Enter Address: ");

    // Validate date of birth
    newNode->student.dob = getValidStringInput("Enter Date of Birth (DD/MM/YYYY): ");

    // Validate phone number
    newNode->student.contact = getValidPhoneNumber("Enter Contact Number (Saudi format, e.g., 0507105054): ");

    // Validate classes, grades, and attendance
    for (int i = 0; i < maxSize; i++) {
        newNode->student.classes[i] = getValidStringInput("Enter name of class " + to_string(i + 1) + ": ");
        newNode->student.grades[i] = getValidNumericInput("Enter grade for " + newNode->student.classes[i] + ": ");
        newNode->student.attendance[i] = getValidNumericInput("Enter attendance for " + newNode->student.classes[i] + " (days): ");
    }

    // Add to the linked list
    newNode->next = head;
    head = newNode;

    cout << "Student added successfully!" << endl;
}

// function to remove student
void removeStudent() {
    if (head == nullptr) {
        cout << "No students in the database to remove." << endl;
        return;
    }

    int removeId = getValidNumericInput("Enter the ID of the student to remove: ");

    Node* current = head;
    Node* previous = nullptr;

    // Traverse the linked list to find the node to remove
    while (current != nullptr) {
        if (current->student.id == removeId) {
            // Found the student to remove
            if (previous == nullptr) {
                // Removing the head node
                head = current->next;
            } else {
                // Removing an intermediate or last node
                previous->next = current->next;
            }

            delete current; // Free the memory
            cout << "Student with ID " << removeId << " removed successfully." << endl;
            return;
        }

        // Move to the next node
        previous = current;
        current = current->next;
    }

    // student not found
    cout << "Student with ID " << removeId << " not found." << endl;
}

// function to search student
void searchStudent() {
    if (head == nullptr) {
        cout << "No students in the database to search." << endl;
        return;
    }

    int searchChoice;
    cout << "Search by:\n 1. ID,\n 2. Name\n ";
    searchChoice = getValidNumericInput("");

    if (searchChoice == 1) {
        // Search by ID
        int searchId = getValidNumericInput("Enter Student ID: ");

        Node* current = head;
        while (current != nullptr) {
            if (current->student.id == searchId) {
                cout << "Student found!" << endl;
                cout << "ID: " << current->student.id << endl;
                cout << "Name: " << current->student.name << endl;
                cout << "Address: " << current->student.address << endl;
                cout << "Date of Birth: " << current->student.dob << endl;
                cout << "Contact: " << current->student.contact << endl;
                // Display classes and corresponding grades
                cout << "Classes: " << endl;
                for (int i = 0; i < maxSize; i++) {
                    if (!current->student.classes[i].empty()) { // Only show if class name is not empty
                        cout << " course name: " << current->student.classes[i] << endl;
                    }
                }
                // cout << "Grades: ";
                // for (int i = 0; i < maxSize; i++) {
                //     cout << current->student.grades[i] << " ";
                // }
                // cout << endl;
                return;
            }
            current = current->next;
        }
        cout << "Student with ID " << searchId << " not found." << endl;

    } else if (searchChoice == 2) {
        // Search by Name
        string searchName = getValidStringInput("Enter Student Name: ");


        Node* current = head;
        while (current != nullptr) {
            if (current->student.name == searchName) {
                cout << "Student found!" << endl;
                cout << "ID: " << current->student.id << endl;
                cout << "Name: " << current->student.name << endl;
                cout << "Address: " << current->student.address << endl;
                cout << "Date of Birth: " << current->student.dob << endl;
                cout << "Contact: " << current->student.contact << endl;
                // Display classes and corresponding grades
                cout << "Classes: " << endl;
                for (int i = 0; i < maxSize; i++) {
                    if (!current->student.classes[i].empty()) { 
                        cout << " course name: " << current->student.classes[i] << endl;
                    }
                }
                return;
            }
            current = current->next;
        }
        cout << "Student with Name \"" << searchName << "\" not found." << endl;

    } else {
        cout << "Invalid choice. Please try again." << endl;
    }
}

// function to list all students
void listAllStudents() {
    if (head == nullptr) {
        cout << "No students in the database." << endl;
        return;
    }

    Node* current = head; 
    cout << "\n=== List of All Students ===" << endl;

    while (current != nullptr) {
        cout << "Student ID: " << current->student.id << endl;
        cout << "Name: " << current->student.name << endl;
        cout << "Address: " << current->student.address << endl;
        cout << "Date of Birth: " << current->student.dob << endl;
        cout << "Contact: " << current->student.contact << endl;

        // Display classes and corresponding grades
        cout << "Classes and Grades: " << endl;
        for (int i = 0; i < maxSize; i++) {
            if (!current->student.classes[i].empty()) { 
                cout << "  " << current->student.classes[i] 
                     << " - Grade: " << current->student.grades[i] 
                     << ", Attendance: " << current->student.attendance[i] << " days" << endl;
            }
        }

        cout << "---------------------------" << endl;
        current = current->next; // Move to the next node
    }
}

// function to generate reports
void generateReports() {
    if (head == nullptr) {
        cout << "No students in the database to generate reports." << endl;
        return;
    }

    Node* current = head;
    int totalGrades = 0; // Total sum of all grades
    int totalSubjects = 0; // Total number of grades across all students
    Student* topStudent = nullptr; // Pointer to the top-performing student
    double highestAverage = 0.0; // Highest average grade

    cout << "=== Student Performance Report ===" << endl;

    while (current != nullptr) {
        // Calculate the average grade for the current student
        int studentTotal = 0;
        for (int i = 0; i < maxSize; i++) {
            studentTotal += current->student.grades[i];
        }
        double studentAverage = studentTotal / (double)maxSize; // Use maxSize here

        // Display the student summary
        cout << "ID: " << current->student.id
             << ", Name: " << current->student.name
             << ", Average Grade: " << studentAverage << endl;

        // Update total grades and subjects
        totalGrades += studentTotal;
        totalSubjects += maxSize; 

        // Check if this student is the top performer
        if (studentAverage > highestAverage) {
            highestAverage = studentAverage;
            topStudent = &current->student;
        }

        current = current->next;
    }

    // Calculate and display the overall average
    double overallAverage = totalGrades / (double)totalSubjects;
    cout << "Overall Average Grade: " << overallAverage << endl;

    // Display the top-performing student
    if (topStudent != nullptr) {
        cout << "Top-Performing Student: " << endl;
        cout << "ID: " << topStudent->id << ", Name: " << topStudent->name
             << ", Average Grade: " << highestAverage << endl;
    }
}

// function to calculate class averages
void calculateClassAverages() {
    if (head == nullptr) {
        cout << "No students in the database to calculate averages." << endl;
        return;
    }

    string targetClass;
    cout << "Enter the class name to calculate its average grade (or type 'ALL' for all classes): ";
    cin.ignore();
    getline(cin, targetClass);

    Node* current = head;
    double totalSum = 0;
    int totalCount = 0;
    bool classFound = false;

    while (current != nullptr) {
        for (int i = 0; i < maxSize; i++) {
            if (targetClass == "ALL" || current->student.classes[i] == targetClass) {
                totalSum += current->student.grades[i];
                totalCount++;
                classFound = true;
            }
        }
        current = current->next;
    }

    if (totalCount > 0) {
        cout << "Average grade for " << (targetClass == "ALL" ? "all classes" : targetClass)
             << ": " << totalSum / totalCount << endl;
    } else if (!classFound) {
        cout << "Class \"" << targetClass << "\" not found in the database." << endl;
    }
}

// function to calculate attendance
void calculateAttendance() {
    if (head == nullptr) {
        cout << "No students in the database to calculate attendance." << endl;
        return;
    }

    string targetClass;
    cout << "Enter the class name to calculate its average attendance (or type 'ALL' for all classes): ";
    cin.ignore();
    getline(cin, targetClass);

    Node* current = head;
    double totalAttendance = 0;
    int totalCount = 0;
    bool classFound = false;

    while (current != nullptr) {
        for (int i = 0; i < maxSize; i++) {
            if (targetClass == "ALL" || current->student.classes[i] == targetClass) {
                totalAttendance += current->student.attendance[i];
                totalCount++;
                classFound = true;
            }
        }
        current = current->next;
    }

    if (totalCount > 0) {
        cout << "Average attendance for " << (targetClass == "ALL" ? "all classes" : targetClass)
             << ": " << totalAttendance / totalCount << " days" << endl;
    } else if (!classFound) {
        cout << "Class \"" << targetClass << "\" not found in the database." << endl;
    }
}

// function to print students in class
void printStudentsInClass() {
    if (head == nullptr) {
        cout << "No students in the database." << endl;
        return;
    }

    string targetClass;
    cout << "Enter the class name to view enrolled students: ";
    cin.ignore();
    getline(cin, targetClass);

    Node* current = head;
    bool found = false;

    cout << "\n=== Students in Class: " << targetClass << " ===" << endl;

    while (current != nullptr) {
        for (int i = 0; i < maxSize; i++) {
            if (current->student.classes[i] == targetClass) {
                // Print student details
                cout << "Student ID: " << current->student.id << endl;
                cout << "Name: " << current->student.name << endl;
                cout << "Grade: " << current->student.grades[i] << endl;
                cout << "Attendance: " << current->student.attendance[i] << " days" << endl;
                cout << "---------------------------" << endl;
                found = true;
            }
        }
        current = current->next;
    }

    if (!found) {
        cout << "No students found in class \"" << targetClass << "\"." << endl;
    }
}

// function to print all subjects
void printAllSubjects() {
    if (head == nullptr) {
        cout << "No students in the database." << endl;
        return;
    }

    Node* current = head;
    set<string> uniqueSubjects; // Use a set to store unique class names

    while (current != nullptr) {
        for (int i = 0; i < maxSize; i++) {
            if (!current->student.classes[i].empty()) {
                uniqueSubjects.insert(current->student.classes[i]); // Add to the set
            }
        }
        current = current->next;
    }

    cout << "\n=== All Subjects in the System ===" << endl;
    for (const string& subject : uniqueSubjects) {
        cout << subject << endl;
    }
}

// function to find top performing students
void findTopPerformingStudents() {
    if (head == nullptr) {
        cout << "No students in the database to determine top performers." << endl;
        return;
    }

    Node* current = head;
    double highestAverage = 0.0;
    vector<Student*> topStudents; // To store pointers to top-performing students

    while (current != nullptr) {
        // Calculate the average grade for the current student
        double totalGrades = 0;
        for (int i = 0; i < maxSize; i++) {
            totalGrades += current->student.grades[i];
        }
        double studentAverage = totalGrades / maxSize;

        // Check if this student has the highest average
        if (studentAverage > highestAverage) {
            // New highest average found, clear previous top students
            highestAverage = studentAverage;
            topStudents.clear();
            topStudents.push_back(&current->student);
        } else if (studentAverage == highestAverage) {
            // Handle ties by adding this student to the top students list
            topStudents.push_back(&current->student);
        }

        current = current->next;
    }

    // Display the top-performing student(s)
    cout << "\n=== Top-Performing Students ===" << endl;
    cout << "Highest Average Grade: " << highestAverage << endl;
    for (Student* student : topStudents) {
        cout << "ID: " << student->id << endl;
        cout << "Name: " << student->name << endl;
        cout << "Average Grade: " << highestAverage << endl;
        cout << "Classes and Grades: " << endl;
        for (int i = 0; i < maxSize; i++) {
            cout << "  " << student->classes[i] 
                 << " - Grade: " << student->grades[i] << endl;
        }
        cout << "---------------------------" << endl;
    }
}

// function to generate dummy data
void generateDummyData() {
    const int dummyCount = 3; // Number of dummy student records to generate
    string names[] = {"Azzam Alkhodairi", "Ahmed Alharbi", "Fahad Alshehri"};
    string addresses[] = {"Riyadh, Saudi Arabia", "Jeddah, Saudi Arabia", "Dammam, Saudi Arabia"};
    string dobs[] = {"15/08/2000", "22/05/1999", "10/11/2001"};
    string contacts[] = {"0507105054", "0551234567", "0569876543"};
    string classes[maxSize] = {"CS182", "IT188"};

    for (int i = 0; i < dummyCount; i++) {
        Node* newNode = new Node;

        newNode->student.id = i + 1;
        newNode->student.name = names[i];
        newNode->student.address = addresses[i];
        newNode->student.dob = dobs[i];
        newNode->student.contact = contacts[i];

        // Assign classes, grades, and attendance
        for (int j = 0; j < maxSize; j++) {
            newNode->student.classes[j] = classes[j];
            newNode->student.grades[j] = 70 + (rand() % 31); // Random grade between 70 and 100
            newNode->student.attendance[j] = 10 + (rand() % 11); // Random attendance between 10 and 20
        }

        // Add to the linked list
        newNode->next = head;
        head = newNode;
    }

    cout << dummyCount << " dummy student records added successfully!" << endl;
}



int main() {


    int choice;

    while (true) {
        cout << "\n=== Student Record System ===" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Remove Student" << endl;
        cout << "3. Search Student" << endl;
        cout << "4. Display All Students" << endl;
        cout << "5. Reports Menu" << endl;
        cout << "6. Print All Students in Specific Class" << endl;
        cout << "7. Print All Subjects" << endl;
        cout << "8. Find Top-Performing Students" << endl;
        cout << "9. Generate Dummy Data" << endl;
        cout << "10. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                removeStudent();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                listAllStudents();
                break;
            case 5: {
                int reportChoice;
                cout << "\n=== Reports Menu ===" << endl;
                cout << "1. Average Grades for Classes" << endl;
                cout << "2. Average Attendance for Classes" << endl;
                cout << "Enter your choice: ";
                cin >> reportChoice;

                switch (reportChoice) {
                    case 1:
                        calculateClassAverages();
                        break;
                    case 2:
                        calculateAttendance();
                        break;
                    default:
                        cout << "Invalid choice in Reports Menu. Returning to main menu." << endl;
                        break;
                }
                break;
            }
            case 6:
                printStudentsInClass();
                break;
            case 7:
                printAllSubjects();
                break;
            case 8:
                findTopPerformingStudents();
                break;
            case 9:
                generateDummyData();
                break;
            case 10:
                cout << "Exiting the program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
