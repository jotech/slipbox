#include <string>
#include <cstring>

int str_ccmp(const char *s1, const char *s2)
{
    for (;;) {
        if (*s1 != *s2) {
            int c1 = toupper((unsigned char)*s1);
            int c2 = toupper((unsigned char)*s2);

            if (c2 != c1) 
                return c2 > c1 ? -1 : 1;
            } 
        else {
            if (*s1 == '\0') 
                return 0;
        }
        ++s1;
        ++s2;
    }
}

struct InsensitiveCompare { 
    bool operator() (const std::string& a, const std::string& b) const {
        return str_ccmp(a.c_str(), b.c_str()) < 0;
    }   
};
