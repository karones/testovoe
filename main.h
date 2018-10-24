#ifndef MAIN_H
#define MAIN_H
#include "filemanager.h"
#include "calc.h"
#include <list>
#include <algorithm>



CALC * check;
std::string request = " Выберите тип действия:\n\
1. Прочитать задание из файла \n\
2. Записать строку в файл \n\
Либо введите команды. Пустая строка останавливает ввод\n";

std::string const readFile = "Введите имя файла для чтения";
std::string const  writeFile = "Введите имя файла для записи";
std::string const writeFileString = "Введите строку";
std::string const errorComand = "Неверная команда";

enum commandType {
    ReadFile = 1,
    WriteFile = 2
};

#endif // MAIN_H
