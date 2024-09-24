#include <iostream>
#include <string>
using namespace std;

// Define a node structure for the linked list
struct TaskNode {
    int taskID;
    string description;
    int priority;
    TaskNode* next;
};

// Define the Task Management class// Define the Task Management
class TaskManagement {
private:
    TaskNode* head;  // Pointer to the head of the list

public:
    // Constructor to initialize the head
    TaskManagement() {
        head = nullptr;
    }

    // Function to add a new task to the list based on priority
    void addTask(int id, string desc, int priority) {
        TaskNode* newTask = new TaskNode();
        newTask->taskID = id;
        newTask->description = desc;
        newTask->priority = priority;
        newTask->next = nullptr;

        // If the list is empty or the new task has a higher priority than the head
        if (head == nullptr || head->priority < priority) {
            newTask->next = head;
            head = newTask;
        } else {
            // Find the correct position for the new task
            TaskNode* current = head;
            while (current->next != nullptr && current->next->priority >= priority) {
                current = current->next;
            }
            newTask->next = current->next;
            current->next = newTask;
        }
        cout << "Task added successfully!\n";
    }

    // Function to remove the highest priority task (from the start)
    void removeHighestPriorityTask() {
        if (head == nullptr) {
            cout << "No tasks to remove.\n";
            return;
        }
        TaskNode* temp = head;
        head = head->next;
        cout << "Removing Task ID: " << temp->taskID << " with Priority: " << temp->priority << "\n";
        delete temp;
    }

    // Function to remove a task by its task ID
    void removeTaskByID(int id) {
        if (head == nullptr) {
            cout << "No tasks to remove.\n";
            return;
        }

        // If the task to be removed is the head
        if (head->taskID == id) {
            TaskNode* temp = head;
            head = head->next;
            delete temp;
            cout << "Task removed successfully!\n";
            return;
        }

        // Traverse the list to find the task
        TaskNode* current = head;
        TaskNode* prev = nullptr;

        while (current != nullptr && current->taskID != id) {
            prev = current;
            current = current->next;
        }

        if (current == nullptr) {
            cout << "Task with ID: " << id << " not found.\n";
            return;
        }

        prev->next = current->next;
        delete current;
        cout << "Task removed successfully!\n";
    }

    // Function to display all tasks
    void displayTasks() {
        if (head == nullptr) {
            cout << "No tasks to display.\n";
            return;
        }

        TaskNode* current = head;
        cout << "\nCurrent Tasks:\n";
        while (current != nullptr) {
            cout << "Task ID: " << current->taskID << " | Description: " << current->description
                 << " | Priority: " << current->priority << "\n";
            current = current->next;
        }
    }

    // Destructor to free memory
    ~TaskManagement() {
        TaskNode* current = head;
        while (current != nullptr) {
            TaskNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

// Function to display the menu
void displayMenu() {
    cout << "\nTask Management System\n";
    cout << "1. Add a New Task\n";
    cout << "2. View All Tasks\n";
    cout << "3. Remove Task with Highest Priority\n";
    cout << "4. Remove Task by ID\n";
    cout << "5. Exit\n";
}

int main() {
    TaskManagement taskManager;
    int choice, taskID, priority;
    string description;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            // Add a new task
            cout << "Enter Task ID: ";
            cin >> taskID;
            cin.ignore();  // To consume the newline character after cin
            cout << "Enter Task Description: ";
            getline(cin, description);
            cout << "Enter Task Priority (higher number means higher priority): ";
            cin >> priority;
            taskManager.addTask(taskID, description, priority);
            break;

        case 2:
            // View all tasks
            taskManager.displayTasks();
            break;

        case 3:
            // Remove the highest priority task
            taskManager.removeHighestPriorityTask();
            break;

        case 4:
            // Remove task by ID
            cout << "Enter Task ID to remove: ";
            cin >> taskID;
            taskManager.removeTaskByID(taskID);
            break;

        case 5:
            cout << "Exiting the program.\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
