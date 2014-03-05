#include "ngram.hpp"
#include  <iostream>
#include <fstream>
int main(int argc, const char *argv[])
{
    std::ifstream fin(argv[1]);
    ngram_score fitness(fin);
#if 0
    for(auto i : fitness.ngrams)
    {
        std::cout << i.first << " : " << i.second.freq << "," << i.second.weight<< std::endl;
    }
#endif
    std::cout << fitness.n << std::endl;
    std::cout << fitness.ngrams["TION"].weight << std::endl;
    std::cout << fitness.score("HELLO") << std::endl;
    
    return 0;
}
