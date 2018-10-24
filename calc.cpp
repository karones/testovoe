#include "calc.h"

//Реализация через алгоритм обратной польской записи
using namespace std;

template<typename Out>
void split(const std::string &s, char delim, Out result)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}


CALC::CALC()
{

    operation.push_back('+');
    operation.push_back('-');
    operation.push_back('*');
    operation.push_back('/');
    operation.push_back('^');
    operation.push_back('(');
    operation.push_back(')');

    digit.push_back('0');
    digit.push_back('1');
    digit.push_back('2');
    digit.push_back('3');
    digit.push_back('4');
    digit.push_back('5');
    digit.push_back('6');
    digit.push_back('7');
    digit.push_back('8');
    digit.push_back('9');
    digit.push_back('.');
    digit.push_back(',');
}

int CALC::getPriority(char op)
{

    switch (op)
    {
    case '(':
        return -1; // не выталкивает сам и не дает вытолкнуть себя другим
    case '^':
        return 1;
    case '*': case '/':
        return 2;
    case '+': case '-':
        return 3;
    default:
       cout << "недопустимая операция" <<endl;
       //todo Добавить исключение.
    }
}

bool CALC::canPop(char op1)
{
    if (operationStack.empty())
        return false;
    int p1 = getPriority(op1);
    int p2 = getPriority(operationStack.top());

    return p1 >= 0 && p2 >= 0 && p1 >= p2;
}

bool CALC::isOperation (const char c)
{
    auto pos = find(operation.begin() , operation.end() , c);
    if(pos != operation.end() )
    {
        return true;
    }
    return false;

}
bool CALC::isDigit (const char c)
{
    auto pos = find(digit.begin() , digit.end() , c);
    if(pos != digit.end() )
    {
        return true;
    }
    return false;
}

std::map <std::string, double> CALC::getResult()
{
    return data;
}


string newName (string str)
{
    return "";
}

double CALC::getValueFromMemmory(string str)
{
    try{
        return data.at(str);
    }
    catch (const std::exception& ex)
    {
        cout <<"Ошибка разбора строки: Переменной " <<str<<" не существует"<<endl;
        return NULL;
    }
}

bool CALC::setName(string &name)
{
    double temporal =  getValueFromMemmory(name);

    if (temporal == NULL)
        return false;
    name.clear();
    dataStack.push(temporal);
    return true;
}
void CALC::popFunction()
{
    double B = dataStack.top();
    dataStack.pop();
    double A = dataStack.top();
    dataStack.pop();
    switch (operationStack.top())
    {
    case '+': dataStack.push(A + B);
        break;
    case '-': dataStack.push(A - B);
        break;
    case '*': dataStack.push(A * B);
        break;
    case '/': dataStack.push(A / B);
        break;
    case '^': dataStack.push(pow(A,B));
        break;
    }
    operationStack.pop();
}
double CALC::calculation(string str, string fullString)
{
    string name;
    string digit;
    while ( ! dataStack.empty() )
    {
        dataStack.pop();
    }
    while ( ! operationStack.empty() )
    {
        operationStack.pop();
    }

    bool firstChar = true; //используется для отличия переменной от числа
    bool isName = false;
    for (auto c : str)
    {
        if (firstChar == true)
        {
            if (c =='(')
            {
                operationStack.push(c);
                continue;
            }
            firstChar = false;

            if (!(isDigit(c) or isOperation(c)))
            {
                isName = true;

            }
            if (c =='-')
            {
                digit += c;
                continue;
            }
        }

        if (isOperation(c))
        {
            if (isName)
            {
                isName = false;
                if (c == '(')
                {
                    cout << "Ошибка в строке: "<<fullString << "после переменной "
                         << name << " символ ( идти не может" <<endl;
                    return NULL;
                }
                else{

                    //иначе добавляем значение в стек
                    firstChar = true;
                    if (!setName(name))
                    {
                        return NULL;
                    }
                }
            }
            else
            {
                //помещаем переменную в стек
                if (!digit.empty())
                    dataStack.push(atof(digit.c_str()));
                digit.clear();
                firstChar = true;
            }
            if (c == ')')
            {
                // Скобка - исключение из правил. выталкивает все операции до первой открывающейся
                while (!(operationStack.empty()) and operationStack.top() != '(')
                    popFunction();
                operationStack.pop(); // Удаляем саму скобку "("
                firstChar = true;
            }
            else
            {
                while(canPop(c))
                {
                    popFunction();
                }
                operationStack.push(c);
            }
            continue;
        }
        else
        {
            if (isName == true)
            {
                name +=c;
            }
            else
            {
                if (isDigit(c))
                {
                    digit += c;
                    continue;
                }
                else {
                    {
                        cout <<"Ошибка в строке: "<<fullString
                            << "Буквы могут встречаться только в названии переменной" <<endl;
                        return NULL;
                    }
                }
            }
        }
    }
    if (isName)
    {
        if (!setName(name))
        {
            return NULL;
        }
    }
    else
    {
        if (!digit.empty())
            dataStack.push(atof(digit.c_str()));
    }
    while (!operationStack.empty())
    {
        popFunction();

    }
    return dataStack.top();
}

void CALC::analyze(list <string> task)
{
    data.clear();
    for( list<string>::iterator i = task.begin(); i != task.end(); ++i ) {
        string workString = *i;

        cout <<workString<<endl;
        std::vector<std::string> items = split(workString, '=');
        string temp;
        if (items.size() >2)
        {
            cout << "Ошибка в строке " <<workString <<
                    " в строке не может быть больше 1 команды присваивания (=)" <<endl;

            return;
        }

        else if (items.size() ==2)
        {
            double result = calculation(items[1], workString); //добавить проверку имени переменной
            if (result != NULL)
            {
                data.insert( pair<string, double>(items[0], result));
            }
        }
        else
        {
            double result =calculation(workString, workString); //todo привести функцию к bool, result передавать ссылкой.
            if (result != NULL)
            {
                data.insert( pair<string, double>("result", result));
            }
        }
    }
}

