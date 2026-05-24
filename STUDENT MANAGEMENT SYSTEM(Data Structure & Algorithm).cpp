#include <iostream>
using namespace std;

// Structure for Student
struct Student {
    int id;
    string name;
    float cgpa;
    Student* next;
};

// Head pointer
Student* head = NULL;

// STACK for undo delete
Student* deletedStack = NULL;

// QUEUE for fee line
Student* front = NULL;
Student* rear = NULL;


// Add Student (Linked List)
void addStudent(int id, string name, float cgpa) {
    Student* newStudent = new Student;
    newStudent->id = id;
    newStudent->name = name;
    newStudent->cgpa = cgpa;
    newStudent->next = head;
    head = newStudent;

    cout << "Student Added Successfully!\n";
}


// Display Students
void displayStudents() {
    Student* temp = head;
    if (temp == NULL) {
        cout << "No Record Found\n";
        return;
    }

    while (temp != NULL) {
        cout << "ID: " << temp->id
             << " Name: " << temp->name
             << " CGPA: " << temp->cgpa << endl;
        temp = temp->next;
    }
}


// Delete Student (Push to Stack)
void deleteStudent(int id) {
    Student* temp = head;
    Student* prev = NULL;

    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        cout << "Student Not Found\n";
        return;
    }

    if (prev == NULL)
        head = temp->next;
    else
        prev->next = temp->next;

    // Push into stack
    temp->next = deletedStack;
    deletedStack = temp;

    cout << "Student Deleted (You can Undo)\n";
}


// Undo Delete (Pop from Stack)
void undoDelete() {
    if (deletedStack == NULL) {
        cout << "Nothing to Undo\n";
        return;
    }

    Student* temp = deletedStack;
    deletedStack = deletedStack->next;

    temp->next = head;
    head = temp;

    cout << "Undo Successful!\n";
}


// Add to Fee Queue
void addToQueue(int id) {
    Student* temp = head;

    while (temp != NULL && temp->id != id)
        temp = temp->next;

    if (temp == NULL) {
        cout << "Student Not Found\n";
        return;
    }

    Student* qNode = new Student;
    *qNode = *temp;
    qNode->next = NULL;

    if (rear == NULL) {
        front = rear = qNode;
    } else {
        rear->next = qNode;
        rear = qNode;
    }

    cout << "Student Added to Fee Queue\n";
}


// Display Queue
void displayQueue() {
    Student* temp = front;

    if (temp == NULL) {
        cout << "Queue Empty\n";
        return;
    }

    cout << "Fee Payment Line:\n";
    while (temp != NULL) {
        cout << temp->name << endl;
        temp = temp->next;
    }
}


int main() {
    int choice, id;
    string name;
    float cgpa;

    do {
        cout << "\n1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Delete Student\n";
        cout << "4. Undo Delete\n";
        cout << "5. Add to Fee Queue\n";
        cout << "6. Display Fee Queue\n";
        cout << "0. Exit\n";
         cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter Name: ";
            cin >> name;
            cout << "Enter CGPA: ";
            cin >> cgpa;
            addStudent(id, name, cgpa);
            break;

        case 2:
            displayStudents();
            break;

        case 3:
            cout << "Enter ID to Delete: ";
            cin >> id;
            deleteStudent(id);
            break;

        case 4:
            undoDelete();
            break;

        case 5:
            cout << "Enter ID for Fee Queue: ";
            cin >> id;
            addToQueue(id);
            break;

        case 6:
            displayQueue();
            break;
        }

    } while (choice != 0);

    return 0;
}