#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <string>
#include <fstream>
#include <list>
#include <algorithm>

class FILEMANAGER
{
public:
    static FILEMANAGER* instance() {
         static FILEMANAGER inst;
         return &inst;
      }
    static std::list<std::string> openFileRead(std::string name);
    void openFileWrite(std::string name,  std::list<std::string> data);

private:

    FILEMANAGER() {}
    FILEMANAGER( const FILEMANAGER&);
    FILEMANAGER& operator=( FILEMANAGER& );
};

#endif // FILEMANAGER_H
