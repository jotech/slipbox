#ifndef SLIPBOX
#define SLIPBOX

#include <list>
#include <string>
#include <cstring>
#include <iostream>
#include <cmath>
#include <fstream>

class slipbox{
    
    public:
    //constructor
    slipbox(char* inputfile);

    void string_clean(std::string &s);
    void print_entries();
    
    typedef struct en
    {
        std::string author;
        std::string title;
        std::string year;
        std::string publisher;
    }entry;

    private:

    std::list<entry> entries;
};
#endif
