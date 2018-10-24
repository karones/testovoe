#include <iostream>
#include <string>
#include "main.h"

using namespace std;

void printResult()
{
    std::map<string, double> result = check->getResult();
    if (!result.empty())
    {
        cout <<"Результаты вычислений:"<<endl;
        for(auto& item : result)
        {
            cout << item.first << " : " << item.second << endl; //Вывод ключей и значений
        }
    }
}

 list<string> inputData(string command = NULL, int count = 2)
 {
     list<string> temp;
     if (!command.empty())
         temp.push_back(command);
     string data;
     cout<< count <<": ";
     std::getline(std::cin, data);
     while (!data.empty())
     {
         count ++;
         temp.push_back(data);
         cout<< count <<": ";
         std::getline(std::cin, data);

     }
     return temp;
 }

int main()
{
    cout << "Добро пожаловать в калькулятор!" << endl;
    string command;
    string name;

    check = new CALC();
    while (1)
    {
        cout << request << endl;
        std::getline(std::cin >> std::ws, command);

        std::string::iterator end_pos = std::remove(command.begin(), command.end(), ' ');
        command.erase(end_pos, command.end());

        if (command.length() == 1) //считаем что это простое действие
        {
            switch (stoi(command))
            {
            case ReadFile:
            {
                cout << readFile << endl;
                cin >> name;
                list<string> task = FILEMANAGER::instance()->openFileRead(name);
                check ->analyze(task);
                printResult();
                continue;
            }
            case WriteFile:
            {
                cout << writeFile << endl;
                cin >> name;
                cin.ignore();
                list<string> task = inputData("", 1);
                FILEMANAGER::instance()->openFileWrite(name, task);
                continue;       
            }

            default:
                cout <<errorComand<<endl;
                continue;   
            }

        }
        list<string> temp = inputData(command);
        check ->analyze(temp);
        printResult();

    }
    return 0;
}
