#include <string>
#include <iostream>
#include <ostream>
#include <map>
#include <string>
#include <fstream>
#include <streambuf>
#include <algorithm>
#include <random>
#include <locale>
#include "ngram.hpp"
#include <stdexcept>

namespace pystring {

    std::string translate( const std::string & str, const std::string & table)
    {
        std::string s(str);
        std::string::size_type len = str.size();

        if ( table.size() != 256 )
        {
            throw std::runtime_error("Improper table size. Size must be 256 chars");
        }
        
        for ( std::string::size_type i = 0; i < len; ++i )
        {
            s[i] = table[ s[i] ];
        }
        return s;
    }

    std::string maketrans(std::string key)
    {
        char t1data[256];
        std::iota(std::begin(t1data), std::end(t1data), 0);
        size_t i = 'A';
        size_t d = 'a' - 'A';

        for(auto k = std::begin(key); k != std::end(key); ++i, ++k)
        {
            t1data[i] = *k;
            t1data[i+d] = std::tolower(*k);
        }
        return std::string(t1data, 256);
    }

}

struct cipher {
    std::string key;
    double score;
    std::string plaintext;
    friend std::ostream& operator<<(std::ostream& os, cipher const & c);
};

std::ostream& operator<<(std::ostream& os, cipher const & c)
{
    os << "score:" << c.score << '\n';
    os << "\tkey: " << c.key << '\n';
    os << "\tplaintext: " << c.plaintext << '\n';
    return os;
}

std::random_device rd;
std::mt19937 g(rd());
std::ifstream fin("../quadgrams.txt");
ngram_score fitness(fin);

std::string substitute(std::string text, std::string key)
{
    auto t1 = pystring::maketrans(key);
    return pystring::translate(text, t1);
}


cipher break_substitution(std::string cipher_text, std::string skey)
{
    std::transform(std::begin(cipher_text), std::end(cipher_text), std::begin(cipher_text), ::toupper);
    std::uniform_int_distribution<int> distribution(0,25); 
    
    cipher p;
    p.key = skey;
    p.plaintext = substitute(cipher_text, p.key);
    p.score = fitness.score(p.plaintext); 
    for(size_t i = 0; i < 1000; ++i)
    {
        cipher c(p);
        auto a = distribution(g);
        auto b = distribution(g);
        std::iter_swap(std::begin(c.key)+a, std::begin(c.key)+b);
        c.plaintext = substitute(cipher_text, c.key);
        c.score = fitness.score(c.plaintext); 
        if(c.score > p.score)
        {
            p = c; //update the parent
            i = 0; //We've made an improvement
        }
    }
    return p;
}


int main(int argc, const char *argv[])
{
    std::ifstream t("../1.4.txt");
    std::string cipher_text((std::istreambuf_iterator<char>(t)),
            std::istreambuf_iterator<char>());
    cipher best;
    best.score = -99e99;
    best.key = "";
    for(size_t i = 0; 1 ; ++i)
    {
        auto c = break_substitution(cipher_text, "QWERTYUIOPASDFGHJKLZXCVBNM");
        if(c.score > best.score)
        {
            best = c;
            std::cout << c;
        }
    }
    return 0;
}
