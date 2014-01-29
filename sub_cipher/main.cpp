#include <string>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <streambuf>
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
}



int main(int argc, const char *argv[])
{
    std::ifstream t("../1.4.txt");
    std::string cipher_text((std::istreambuf_iterator<char>(t)),
            std::istreambuf_iterator<char>());
    std::map<char, char> m = {
        {'A', 'o'},
        {'B', 'o'},
        {'C', 'o'},
        {'D', 'o'},
        {'E', 'o'},
        {'F', 'o'},
        {'G', 'o'},
        {'H', 'o'},
        {'I', 'o'},
        {'J', 'o'},
        {'K', 'o'},
        {'L', 'o'},
        {'M', 'o'},
        {'N', 'o'},
        {'O', 'o'},
        {'P', 'o'},
        {'Q', 'o'},
        {'R', 'o'},
        {'S', 'o'},
        {'T', 'o'},
        {'U', 'o'},
        {'V', 'o'},
        {'W', 'o'},
        {'X', 'o'},
        {'Y', 'o'},
        {'Z', 'o'},
    };
    auto t1 = pystring::maketrans(m);
    std::string s1 = pystring::translate(cipher_text, t1);
    std::cout << s1 <<  std::endl;
    return 0;
}
