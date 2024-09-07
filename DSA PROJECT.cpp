#include <iostream>
#include <limits>

using namespace std;

class Student {
public:
    string name;
    
    int rollNumber;
    
    string course;
    
    int totalMarks;
    
    Student* next;

    Student(string n, int r, string c, int m) : name(n), rollNumber(r), course(c), totalMarks(m), next(NULL) {}
};

class StudentRecordManagement {
private:
	
    Student* head;

public:
	
    StudentRecordManagement() : head(NULL) {}

    bool isRollNumberExist(int rollNumber) const {
        Student* current = head;
        while (current != NULL) {
            if (current->rollNumber == rollNumber) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void insertStudent(const string& name, int rollNumber, const string& course, int totalMarks) {
        if (isRollNumberExist(rollNumber)) {
            cout << "Student with Roll Number " << rollNumber << " already exists. Cannot add duplicate records.\n";
            return;
        }
        if (totalMarks > 100) {
            cout << "Total marks cannot be greater than 100.\n";
            return;
        }
        Student* newStudent = new Student(name, rollNumber, course, totalMarks);
        newStudent->next = head;
        head = newStudent;
        system("cls");
        cout << "Student record added successfully.\n";
    }

    void deleteStudent(int rollNumber) {
        Student* temp = head;
        Student* prev = NULL;

        if (temp != NULL && temp->rollNumber == rollNumber) {
            head = temp->next;
            delete temp;
            cout << "Student record deleted successfully.\n";
            return;
        }

        while (temp != NULL && temp->rollNumber != rollNumber) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL) {
            cout << "Student record not found.\n";
            return;
        }

        prev->next = temp->next;
        delete temp;
        cout << "Student record deleted successfully.\n";
    }

    void showStudents() const {
        Student* current = head;
        if (current == NULL) {
            cout << "No student records available.\n";
            return;
        }
        while (current != NULL) {
            cout << "Name: " << current->name << ", Roll Number: " << current->rollNumber 
                 << ", Course: " << current->course << ", Total Marks: " << current->totalMarks << endl;
            current = current->next;
        }
    }

    void searchStudent(int rollNumber) const {
        Student* current = head;
        while (current != NULL) {
            if (current->rollNumber == rollNumber) {
                cout << "Name: " << current->name << ", Roll Number: " << current->rollNumber 
                     << ", Course: " << current->course << ", Total Marks: " << current->totalMarks << endl;
                return;
            }
            current = current->next;
        }
        cout << "Student record not found.\n";
    }
};

void displayMainMenu() {
    cout << "\n=====================================\n";
    cout << "      Student Record Management\n";
    cout << "=====================================\n";
    cout << "1. Insert Student Record\n";
    cout << "2. Delete Student Record\n";
    cout << "3. Show All Student Records\n";
    cout << "4. Search Student Record\n";
    cout << "5. Exit\n";
    cout << "=====================================\n";
    cout << "Select an option: ";
}

int getValidatedIntInput() {
    int input;
    while (true) {
        cin >> input;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid integer: ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return input;
        }
    }
}

string getValidatedStringInput(const string& prompt) {
    string input;
    cout << prompt;
    cin.ignore();
    getline(cin, input);
    return input;
}

int main() {
    StudentRecordManagement sys;
    char choice;

    while (true) {
        displayMainMenu();
        cin >> choice;

        if (!isdigit(choice)) {
            system("cls");
            cout << "Invalid choice. Please enter a number between 1 and 5.\n";
            continue;
        }

        if (choice == '5') {
            break;
        }

        string name, course;
        int rollNumber, totalMarks;

        switch (choice) {
        case '1':
            cout << "------------------------------\n";
            cout << "  Insert Student Record\n";
            cout << "------------------------------\n";
            name = getValidatedStringInput("Enter Student Name: ");
            cout << "Enter Roll Number: ";
            rollNumber = getValidatedIntInput();
            course = getValidatedStringInput("Enter Course: ");
            cout << "Enter Total Marks: ";
            totalMarks = getValidatedIntInput();
            sys.insertStudent(name, rollNumber, course, totalMarks);
            break;

        case '2':
            cout << "------------------------------\n";
            cout << "  Delete Student Record\n";
            cout << "------------------------------\n";
            cout << "Enter Roll Number of Student to Delete: ";
            rollNumber = getValidatedIntInput();
            sys.deleteStudent(rollNumber);
            break;

        case '3':
            cout << "------------------------------\n";
            cout << "  Show All Student Records\n";
            cout << "------------------------------\n";
            sys.showStudents();
            break;

        case '4':
            cout << "------------------------------\n";
            cout << "  Search Student Record\n";
            cout << "------------------------------\n";
            cout << "Enter Roll Number of Student to Search: ";
            rollNumber = getValidatedIntInput();
            sys.searchStudent(rollNumber);
            break;

        default:
            system("cls");
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    }

    return 0;
}

