#include "filemanager.h"
#include "iostream"






std::list<std::string> FILEMANAGER::openFileRead(std::string name)
{
    std::string line;
    std::ifstream myfile (name);
    std::list <std::string> result;
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            if (!line.empty())
            {
                std::string::iterator end_pos = std::remove(line.begin(), line.end(), ' ');
                line.erase(end_pos, line.end());
                result.push_back(line);
            }
        }
        myfile.close();
        return result;
    }
    else
    {
        std::cout << "Неверное имя файла" <<std::endl <<std::endl;
        return result;
    }
}

void FILEMANAGER::openFileWrite(std::string name,  std::list<std::string> data)

{

    std::ofstream out(name);
    for (auto str : data)
    {
        out << str <<std::endl;
    }
    out.close();
}
