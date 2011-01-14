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
            tmp.bibkey = e.bibkey;
            tmp.typ = e.typ;
            entries.push_back(tmp);
        }

        
        found = s.find("@");
        if (found != string::npos){
            string_clean(s);
            size_t ter = s.find("{");
            string t = s.substr(found + 1, ter - found - 1);
            string k = s.substr(ter + 1, s.find(",") - ter - 1);
            e.typ = t;
            e.bibkey = k;
        }
        else{
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
                        else{
                            found = s.find("keywords");
                            if (found != string::npos){
                                string_clean(s);
                                
                                //keywords are seperated by '/' try to get them single
                                size_t from, until;
                                string key;
                                from = s.find("/");
                                while(from != string::npos){
                                    until = s.find("/", from + 1);
                                    if (until == string::npos)
                                        key = s.substr(from + 1, s.size() - from - 1);
                                    else key = s.substr(from + 1, until - from - 1);
                                    string_clean(key);
                                    set<string> bibkeys;
                                    if(keywords.find(key) != keywords.end())
                                        keywords[key].insert(e.bibkey);
                                    else{
                                        bibkeys.insert(e.bibkey);
                                        keywords.insert(pair <string, set<string> >(key, bibkeys));
                                    }

                                    from = until;
                                }
                            }
                        }
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
        cout << it->typ << '\t' << it->bibkey << '\t' << it->author << '\t' << it->title << '\t' << it->year << '\t' << it->publisher << endl;
    }
}


void slipbox::print_keywords(){
    map<string, set<string> >::iterator it;
    set<string>::iterator it_str;

    cout << "print all keywords: " << keywords.size() << endl;
    for(it = keywords.begin(); it != keywords.end(); ++it){
        cout << it->first;
        cout << " --> ";
        for(it_str = it->second.begin(); it_str != it->second.end(); ++it_str)
            cout << *it_str << " ";
        cout << endl;
    }
}


int main(int argc, char *argv[]){

    slipbox sb(argv[1]);
    sb.print_entries();
    sb.print_keywords();
}
