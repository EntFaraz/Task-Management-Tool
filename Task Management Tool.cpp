#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct Task {
    string description;
    bool completed;
};

class TaskManager {
private:
    vector<Task> tasks;

public:
    void addTask(const string description) {
        Task t;
        t.description = description;
        t.completed = false;
        tasks.push_back(t);
    }

    void viewTasks() const {
        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << i + 1 << ". " << tasks[i].description << (tasks[i].completed ? " [Completed]" : "") << endl;
        }
    }

    void markTaskCompleted(int index) {
        if (index >= 0 && index < tasks.size()) {
            tasks[index].completed = true;
        } else {
            cout << "Invalid task index." << endl;
        }
    }

    void saveToFile(const string filename) const {
        ofstream file(filename.c_str());
        if (file.is_open()) {
            for (size_t i = 0; i < tasks.size(); ++i) {
                file << tasks[i].description << "," << tasks[i].completed << endl;
            }
            file.close();
        } else {
            cout << "Error opening file for writing." << endl;
        }
    }

    void loadFromFile(const string filename) {
        ifstream file(filename.c_str());
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                size_t pos = line.find(',');
                if (pos != string::npos) {
                    string description = line.substr(0, pos);
                    bool completed = (line.substr(pos + 1) == "1");
                    Task t;
                    t.description = description;
                    t.completed = completed;
                    tasks.push_back(t);
                }
            }
            file.close();
        } else {
            cout << "Error opening file for reading." << endl;
        }
    }
};

int main() {
    TaskManager manager;
    manager.loadFromFile("tasks.txt");

    int choice;
    do {
        cout << "1. Add Task\n2. View Tasks\n3. Mark Task Completed\n4. Save & Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string description;
            cout << "Enter task description: ";
            cin.ignore();
            getline(cin, description);
            manager.addTask(description);
        } else if (choice == 2) {
            manager.viewTasks();
        } else if (choice == 3) {
            int index;
            cout << "Enter task number to mark as completed: ";
            cin >> index;
            manager.markTaskCompleted(index - 1);
        }
    } while (choice != 4);

    manager.saveToFile("tasks.txt");
    return 0;
}
