#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;


struct Task {
  string taskName;
  string description;
  int priority;
  string dueDate;
};


// make vector param const | no cahnges to vector
// setw => sets width for input and output !
void displayTasks(const vector<Task>& tasks){
  if(tasks.empty()){
    cout << "No tasks to display!!";
  }else {
    cout << "\nYour Tasks:\n";
    cout << setw(5) << "No" << setw(10) << "Title" << setw(25) << "Description" 
          << setw(15) << "Priority" << setw(15) << "Due Date\n";
    cout << string(60, '-') << endl;
    for(size_t i=0; i<tasks.size();i++){
      cout << setw(5) << i + 1 
           << setw(10) << tasks[i].taskName
           << setw(25) << tasks[i].description 
           << setw(15) << tasks[i].priority 
           << setw(15) << tasks[i].dueDate << endl;
    }
  }
}

void  deleteTask(vector<Task>& tasks){
  int taskNum;
  displayTasks(tasks);
  if(!tasks.empty()){
    cout << "Enter the number to delete: ";
    cin >> taskNum;
    if(taskNum > 0 && taskNum <= tasks.size()){
      //delete's the task entered!
      tasks.erase(tasks.begin() + taskNum - 1);
      cout << "Task Deleted!\n";
    }else {
      cout << "INvalid task number!\n";
    }
  }
}

//save the tasks to a file so then to be able to load the tasks
//using ofstream
void saveTasks(vector<Task>& tasks){
  ofstream file("tasks.txt");
  if(file.is_open()){
    for(const auto& task: tasks){
      file << task.taskName << endl
            << task.description << endl
            << task.priority << endl
            << task.dueDate << endl;
    }
    file.close();
  }else {
    cout << "Error saving tasks to file !!\n";
  }
}

//load the tasks if saved in file
//using ifstream
void loadTasks(vector<Task>& tasks){
  ifstream file("tasks.txt");
  if(file.is_open()){
    Task task;
    while(getline(file, task.taskName)){
      file >> task.description;
      file >> task.priority;
      //ignore newline same as cin.ignore()
      file.ignore();
      getline(file, task.dueDate);
      //push task vektor to tasks 
      tasks.push_back(task);
    }
    file.close();
    cout << "Tasks loaded successfully !!!\n";
  }else {
    cout << "No saved tasks in file foudn !!!\n";
  }
}


//pass vector to param
// add tasks 
void addTask(vector<Task>& tasks){
  Task newTask;

  cout << "Enter task name: ";
  getline(cin, newTask.taskName);

  cout << "\nEnter task description: ";
  getline(cin, newTask.description);
  
  cout << "Enter task priority: ";
  cin >> newTask.priority;
  cin.ignore();

  cout << "Enter Due date (e.g., DD-MM-YYYY):";
  getline(cin, newTask.dueDate);

  //puz struct to vector
  tasks.push_back(newTask);
  cout << "\nTask added!!";
}


int main(){
  vector<Task> tasks;
  int choice;

  // Load tasks from file on startup
  loadTasks(tasks);

  do {
    cout << "\nTo-Do List Menu:\n";
    cout << "1. View Tasks\n";
    cout << "2. Add Task\n";
    cout << "3. Delete Task\n";
    cout << "4. Save and Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore(); // To ignore the newline after the choice input

    switch (choice) {
      case 1:
        displayTasks(tasks);
        break;
      case 2:
        addTask(tasks);
        break;
      case 3:
        deleteTask(tasks);
        break;
      case 4:
        saveTasks(tasks);
        cout << "Tasks saved! Exiting...\n";
        break;
      default:
        cout << "Invalid choice! Please try again.\n";
    }
  } while (choice != 4);

  return 0;
}
