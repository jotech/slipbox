#ifndef SLIPBOX
#define SLIPBOX

#include <list>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <iostream>
#include <cmath>
#include <fstream>
#include "util.cc"
    

class slipbox{
    
    public:
    //constructor
    slipbox(char* inputfile);

    void string_clean(std::string &s);
    void print_entries();
    void print_keywords();
   
      


    typedef struct en
    {
        std::string author;
        std::string title;
        std::string year;
        std::string publisher;
        std::string bibkey;
        std::string typ;
    }entry;

    private:

    std::list<entry> entries;
    std::map<std::string, std::set<std::string>, InsensitiveCompare> keywords;
};
#endif
