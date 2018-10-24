#ifndef CALC_H
#define CALC_H
#include <iostream>
#include <list>
#include <string>
#include <map>
#include <stack>
#include <math.h>
#include <exception>
#include <algorithm>
#include <sstream>
#include <vector>
#include <iterator>

class CALC
{
public:
    CALC();
    void analyze(std::list <std::string> task);
    std::map <std::string, double> getResult();
private:
    double calculation(std::string str, std::string fullString);
    double getValueFromMemmory(std::string str);
    bool setName(std::string &CALCstr);

    std::map <std::string, double> data;
    std::list <char> operation ;
    std::list <char> digit ;
    std::stack <char> operationStack;
    std::stack <double> dataStack;
    bool canPop(char op1);
    void popFunction();
    int getPriority(char p);
    bool isOperation (const char c);
    bool isDigit (const char c);
};

#endif // CALC_H
