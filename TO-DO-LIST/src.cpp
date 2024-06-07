#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <deque>

using namespace std;

enum taskState {
    Do = 1,
    Doing = 2,
    Done = 3
};
enum window {
    TasksMenu = 1,
    AddTask = 2,
    MoveTask = 3,
    DeleteTask = 4,
    Exit = 5 
};
class clsTask {
    private:
    taskState state;
    string _body;
    fstream DoTasks, DoingTasks, DoneTasks;
    void file(deque<string>& v, fstream& data, string op, string fileName);
    protected:
    
    deque<string> doTasks, doingTasks, doneTasks;
    public:
    clsTask(){
        file(doTasks, DoTasks, "load", "do tasks.txt");
        file(doingTasks, DoingTasks, "load", "doing tasks.txt");
        file(doneTasks, DoneTasks, "load", "done tasks.txt");
    }
    void setBody(string body);
    void addTask(pair<string, int> task);
    ~clsTask() {
        
        file(doTasks, DoTasks, "save", "do tasks.txt");
        file(doingTasks, DoingTasks, "save", "doing tasks.txt");
        file(doneTasks, DoneTasks, "save", "done tasks.txt");
    }

};

class clsDoDoingDone : public clsTask{
    private:
    int windowChoosen;
    public:
    void showTasks();
    void start();
    void addTaskWindow();
    void moveTaskWindow();
    void printVector(deque<string>& v);
    void deleteTask(deque<string>& tasks, int indx);
    void deleteTaskMenu();
    
};

int main() {
    clsDoDoingDone sys;
    sys.start();
    
}

void clsDoDoingDone::showTasks() {
    system("cls");
    
    cout << "\t\t\t\t\tTASKS..\n\n";
    
    // cout << "DO:\n";
    // printVector(doTasks);
    // cout << "\n\nDONIG:\n";
    // printVector(doingTasks);
    // cout << "\n\nDONE:\n";
    // printVector(doneTasks);
    // cout << "\n\n";
    cout << setw(35) << left << "DO" << setw(35) << left <<"|DOING" << "|DONE\n";
    cout << "---------------------------------------------------------------------------------------------------\n";
    long long t = max(doTasks.size(), doingTasks.size());
    long long size = max(t, (long long)doneTasks.size());
    int s = min(doTasks.size(), doingTasks.size());
    int start = min(s, (int)doneTasks.size());

    for(int i = 0; i < size; i++) {
        if(i >= doTasks.size()) {
            cout << setw(35) << left << " ";
        }
        else 
            cout << setw(35) << left << doTasks[i];
        
        if(i >= doingTasks.size()) 
            cout << "|" << setw(34) << left << " ";
        else    
            cout << "|" << setw(34) << left << doingTasks[i];
        
        if(i >= doneTasks.size()) 
            cout << "|";
        else    
            cout << "|"  <<  doneTasks[i];
        
        
        
        cout << endl;
    }
    cout  << "---------------------------------------------------------------------------------------------------\n\n";
    system("pause");
    
}
void clsDoDoingDone::start() {
    bool cont = true;
    do{
    
    system("cls");
    cout << "------------------------------\n";
    cout << "TO-DO-LIST\n";
    cout << "------------------------------\n\n";
    cout << "[1] Tasks Menu.\n";
    cout << "[2] Add Task.\n";
    cout << "[3] Move Task.\n";
    cout << "[4] Delete Task.\n";
    cout << "[5] Exit.\n";
    cout << "\nChoose window [1] to [5]: ";
    cin >> windowChoosen;
    switch (windowChoosen)
    {
    case TasksMenu:
        showTasks();
        break;
    case AddTask:
        addTaskWindow();
        break;
    case MoveTask:
        moveTaskWindow();
        break;
    case DeleteTask:
        deleteTaskMenu();
        break;
    default:
        cont = false;
        break;
    }
    }while(cont);
}

void clsDoDoingDone::addTaskWindow() {
    
    char cont;
    string body;
    int state;
    do {
        system("cls");
        cout << "------------------------------\n";
        cout << "ADD TASK SCREEN\n";
        cout << "------------------------------\n\n";
        cout << "TASK: ";
        cin.ignore(1, '\n');
        getline(cin, body);
        cout << "\nSTATE [1] DO [2] DOING [3] DONE: ";
        cin >> state;
        addTask({body, state});
        cout << "Task Added succefully, Do you want to add another [y or n]: ";
        cin >> cont;
    }while(cont == 'y');
    
    system("pause");
    
    
}

void clsDoDoingDone::moveTaskWindow() {
    char cont;
    do{
        system("cls");
    cout << "------------------------------\n";
    cout << "MOVING TASK SCREEN\n";
    cout << "------------------------------\n\n";
    cout << "[1] DO -> DOING.\n";
    cout << "[2] DOING -> DONE.\n";
    cout << "choose [1] or [2]: ";
    int choise;
    cin >> choise;
    if(choise == 1) {
        system("cls");
        cout << "DO TASKS\n\n";
        printVector(doTasks);
        cout << "\n\nchoose the task you want to move: ";
        int indx;
        cin >> indx;
        doingTasks.push_front(doTasks[indx - 1]);
        deleteTask(doTasks, indx - 1);

    }
    else {
        system("cls");
        cout << "DOING TASKS\n\n";
        printVector(doingTasks);
        cout << "\n\nchoose the task you want to move: ";
        int indx;
        cin >> indx;
        doneTasks.push_front(doingTasks[indx - 1]);
        deleteTask(doingTasks, indx - 1);
    }
    cout << "\n\ndo you want to move another task [y or n]? ";
    cin >> cont;
    }while(cont == 'y');
    system("pause");
}

void clsDoDoingDone::printVector(deque<string>& v) {
    
    for(int i = 0; i < v.size(); i++) {
        cout << "[" << i+1 << "] " << v[i] << endl;
    }
}

void clsDoDoingDone::deleteTask(deque<string>& tasks, int indx) {
    
    tasks.erase(tasks.begin() + indx);
}

void clsDoDoingDone::deleteTaskMenu() {
    char cont;
    do{
    system("cls");
    cout << "------------------------------\n";
    cout << "DELETING TASK SCREEN\n";
    cout << "------------------------------\n\n";
    cout << "[1] DO\n[2] DOING\n[3] DONE\nChoose list: ";
    int list;
    cin >> list;
    system("cls");
    if(list == Do) {
        cout << "DO TASKS\n\n";
        printVector(doTasks);
        cout << "choose task: ";
        int indx;
        cin >> indx;
        deleteTask(doTasks, indx-1);
    }
    else if(list == Doing) {
        cout << "DOING TASKS\n\n";
        printVector(doingTasks);
        cout << "choose task: ";
        int indx;
        cin >> indx;
        deleteTask(doingTasks, indx-1);
    }
    else{
        cout << "DONE TASKS\n\n";
        printVector(doneTasks);
        cout << "choose task: ";
        int indx;
        cin >> indx;
        deleteTask(doneTasks, indx-1);
    }
    cout << "Task deleted successfully, Do you want to delete another one [y or n] ? ";
    cin >> cont;
    }while(cont == 'y');
    system("pause");
}

void clsTask::file(deque<string> &v, fstream& data, string op, string fileName) {
    if(op == "save") {
        data.open(fileName, ios::trunc | ios::out);
        
        if(data.is_open()) {
            for(auto& i : v)
                data << i << endl;
        }
        data.close();
    }
    else {
        data.open(fileName, ios::in);
        if(data.is_open()) {
            string task;
            while(getline(data, task)) {
                if(!task.empty())
                v.push_back(task);
            }
        }
        data.close();
    }
}



void clsTask::setBody(string body)
{
    _body = body;
}
void clsTask::addTask(pair<string, int> task) {
    if(task.second == Do)
    doTasks.push_front(task.first);
    else if(task.second == Doing)
    doingTasks.push_front(task.first);
    else 
    doneTasks.push_front(task.first);
}