#include "slipbox.h"


using namespace std;

slipbox::slipbox(char* inputfile){
    cout << "reading bibtex entrys from: " << inputfile << endl; 

    ifstream source(inputfile);

    string s;
    entry e;
    while(source){
        getline(source, s, '\n');

        size_t found;
        
        
        if(s.compare("}") == 0){
            entry tmp;
            tmp.author = e.author;
            tmp.title = e.title;
            tmp.year = e.year;
            tmp.publisher = e.publisher;
            entries.push_back(tmp);
        }

        found = s.find("title");
        if (found != string::npos){
            string_clean(s);
            e.title = s;
        }
        else{
            found = s.find("author");
            if (found != string::npos){
                string_clean(s);
                e.author = s;
            }
            else{
                found = s.find("publisher");
                if (found != string::npos){
                    string_clean(s);
                    e.publisher = s;
                }
                else{
                    found = s.find("year");
                    if (found != string::npos){
                        string_clean(s);
                        e.year = s;
                    }
                
                }
            }
        }
    }
}

void slipbox::string_clean(string &s){
    size_t found;
    
    //delete chars until '=' 
    found = s.find("=");
    if (found != string::npos) s.erase(0, found + 1);

    char c;
    bool cont = true;
    while(s.size() != 0 && cont){
        cont = false;
        if(s[0] == ',' || s[0] == ' ' || s[0] == '{' || s[0] == '}') {
            s.erase(0, 1);
            cont = true;
        }
        if(s[s.size() - 1] == ',' || s[s.size() - 1] == ' ' || s[s.size() - 1] == '{' || s[s.size() - 1] == '}') {
            s.erase(s.size() - 1, 1);
            cont = true;
        }
    }
    
}

void slipbox::print_entries(){
    list<entry>::iterator it;

    cout << "print all entries: " << entries.size() << endl;
    for(it = entries.begin(); it != entries.end(); ++it){
        cout << it->author << '\t' << it->title << '\t' << it->year << '\t' << it->publisher << endl;
    }
}

int main(int argc, char *argv[]){

    slipbox sb(argv[1]);
    sb.print_entries();
}
