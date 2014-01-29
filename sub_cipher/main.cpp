#include <string>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <streambuf>
#include <algorithm>
#include <random>
#include <locale>

namespace pystring {

    std::string translate( const std::string & str, const std::string & table, const std::string & deletechars ="")
    {
        std::string s;
        std::string::size_type len = str.size(), dellen = deletechars.size();

        if ( table.size() != 256 )
        {
            // TODO : raise exception instead
            return str;
        }

        //if nothing is deleted, use faster code
        if ( dellen == 0 )
        {
            s = str;
            for ( std::string::size_type i = 0; i < len; ++i )
            {
                s[i] = table[ s[i] ];
            }
            return s;
        }


        int trans_table[256];
        for ( int i = 0; i < 256; i++)
        {
            trans_table[i] = table[i];
        }

        for ( std::string::size_type i = 0; i < dellen; i++)
        {
            trans_table[(int) deletechars[i] ] = -1;
        }

        for ( std::string::size_type i = 0; i < len; ++i )
        {
            if ( trans_table[ (int) str[i] ] != -1 )
            {
                s += table[ str[i] ];
            }
        }

        return s;

    }

std::string maketrans(std::map<char, char> trans)
{
    char t1data[256];
    for(int i=0; i<256; ++i) t1data[i] = (char)i;
    
    for(auto& c : trans)
    {
        t1data[c.first] = c.second;
    }
    return std::string(t1data, 256);
}

std::string maketrans(std::string key)
{
    
    char t1data[256];
    std::iota(std::begin(t1data), std::end(t1data), 0);
    size_t i = 'A';
    size_t d = 'a' - 'A';
    auto k = std::begin(key);
    for(; k != std::end(key); ++i, ++k)
    {
        t1data[i] = *k;
        t1data[i+d] = std::tolower(*k);
    }
    return std::string(t1data, 256);
}

}


int main(int argc, const char *argv[])
{
    std::ifstream t("../1.4.txt");
    std::string cipher_text((std::istreambuf_iterator<char>(t)),
            std::istreambuf_iterator<char>());
    std::random_device rd;
    std::mt19937 g(rd());
    std::string key("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    std::shuffle(std::begin(key), std::end(key), g);
    std::cout << pystring::maketrans(key);

#if 0
    std::map<char, char> m = {{'A', 'A'},
        {'B', 'B'},
        {'C', 'C'},
        {'D', 'D'},
        {'E', 'E'},
        {'F', 'F'},
        {'G', 'G'},
        {'H', 'H'},
        {'I', 'I'},
        {'J', 'J'},
        {'K', 'K'},
        {'L', 'L'},
        {'M', 'M'},
        {'N', 'N'},
        {'O', 'O'},
        {'P', 'P'},
        {'Q', 'Q'},
        {'R', 'R'},
        {'S', 'S'},
        {'T', 'T'},
        {'U', 'U'},
        {'V', 'V'},
        {'W', 'W'},
        {'X', 'X'},
        {'Y', 'Y'},
        {'Z', 'Z'},
    };
    std::shuffle(std::begin(m), std::end(m), g);
    auto t1 = pystring::maketrans(m);
    std::string s1 = pystring::translate(cipher_text, t1);
    std::cout << s1 <<  std::endl;
#endif
    return 0;
}
