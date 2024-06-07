#include <iostream>
#include <time.h>
#include <iomanip>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

enum Windows {
    ShowCosts = 1,
    ShowAdds = 2,
    Cost = 3,
    Add = 4,
    Exit = 5
};

struct stOperation{
    string Body;
    string Date;
    int Money;
    
};
class clsWallet {
    private:
    int money = 0;
    fstream Costs, Adds;
    vector<stOperation> costs, adds;
    time_t now;
    string dt;
    public:
    void file(vector<stOperation>& v, fstream& data, string op, string fileName);
    clsWallet() {
        //cout << costs.size() << endl;
        file(costs, Costs, "load", "costs.txt");
        file(adds, Adds, "load", "adds.txt");
        for(auto& i : costs) {
            money += i.Money;
        }
        for(auto& i : adds) {
            money += i.Money;
        }
        if(money < 0 ) money = 0;
    }
    void start();
    void history(string op);
    void add();
    void cost();
    ~clsWallet() {
        file(costs, Costs, "save", "costs.txt");
        file(adds, Adds, "save", "adds.txt");
    }
};
int main() {
    system("cls");
    clsWallet prog;
    
    prog.start(); 
}

void clsWallet::file(vector<stOperation> &v, fstream& data, string op, string fileName) {
    if(op == "save") {
        data.open(fileName, ios::trunc | ios::out);
        
        if(data.is_open()) {
            for(auto& i : v)
                data << i.Body << endl << i.Date << endl<< to_string(i.Money) << endl;
        }
        data.close();
    }
    else {
        data.open(fileName, ios::in);
        if(data.is_open()) {
            string task;
            int count = 0;
            while(getline(data, task)) {
                if(!task.empty())
                {
                   if(count % 3 == 0)
                    v.push_back({task});
                    else if(count % 3 == 1) {
                        v.back().Date = task;
                    }
                    else
                        v.back().Money = stoi(task);
                }
                count++;
            }
        }
        data.close();
    }
}

void clsWallet::start()
{
    char cont = 'y';
    do
    {
    system("cls");
    cout << "---------------------\n";
    cout << money << "\t\tEGP |\n";
    cout << "---------------------\n\n";
    cout << "[1] SHOW COSTS.\n";
    cout << "[2] SHOW ADDS.\n";
    cout << "[3] COST.\n";
    cout << "[4] ADD.\n";
    cout << "[5] Exit.\n";
    cout << "\nChoose window: ";
    int window;
    cin >> window;
    switch (window)
    {
    case ShowCosts:
        history("costs");
        break;
    case ShowAdds:
        history("adds");
        break;
    case Cost:
        cost();
        break;
    case Add:   
        add();
        break;
    default:
        cont = 'n';
        break;
    }
    } while (cont == 'y');
    
}

void clsWallet::history(string op) {
    system("cls");
        cout << "-----------------------\n";
        cout << "       History...     |\n";
        cout << "-----------------------\n";
    //cout << setw(20) << "COST" << setw(20) << "|" << setw(20) << "ADD";
    //int size = max(costs.size(), adds.size());
    //cout << "\n--------------------------------------------------------------------\n\n";
    cout << endl;
    if(op == "costs") {
    for(auto& i : costs) {
        cout << i.Body << endl << i.Date  << endl<< i.Money << endl;
        cout << "-----------------------\n";
    }
    }
    else {
    for(auto& i : adds) {
        cout << i.Body << endl << i.Date << endl << i.Money << endl;
        cout << "-----------------------\n";
    }

    }
    system("pause");
}

void clsWallet::add() {
    char cont;
    do {
        system("cls");
        cout << "-----------------------\n";
        cout << "ADD MONEY...\n";
        cout << "-----------------------\n";
        cout << "Source?  ";
        string body;
        cin.ignore(1, '\n');
        getline(cin, body);
        cout << "How much?  ";
        int moneyToAdd;
        cin >> moneyToAdd;
        now = time(0);
        dt = ctime(&now);
        dt.pop_back();
        adds.push_back({body, dt, moneyToAdd});
        money += moneyToAdd;
        cout << "\nmoney added successfully!\n";
        cout << "\nDo you want add more money? [y or n]  ";
        cin >> cont;
    }while(cont == 'y');
    system("pause");
}

void clsWallet::cost() {
    char cont;
    do {
        system("cls");
        cout << "-----------------------\n";
        cout << "Spent MONEY...\n";
        cout << "-----------------------\n";
        cout << "why?  ";
        string body;
        cin.ignore(1, '\n');
        getline(cin, body);
        cout << "How much?  ";
        int moneyToShrink;
        cin >> moneyToShrink;
        now = time(0);
        dt = ctime(&now);
        dt.pop_back();
        costs.push_back({body, dt, -1 * moneyToShrink});
        money -= moneyToShrink;
        if(money < 0 ) money = 0;
        cout << "\nmoney spent successfully!\n";
        cout << "\nDo you want spent more money? [y or n]  ";
        cin >> cont;
    }while(cont == 'y');
    system("pause");
}
