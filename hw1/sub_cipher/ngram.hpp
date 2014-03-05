#include <map>
#include <istream>
#include <string>
#include <ctgmath>
#include <iostream>
struct ngram_score 
{
    struct ngram_datum {
        int freq;
        double weight;
    };
    std::map<std::string, ngram_datum> ngrams;
    double floor;
    size_t l;
    size_t n{0};
    ngram_score(std::istream& in)
    {
        std::string line;
        while(in)
        {
            std::string ngram;
            int freq;
            in >> ngram;
            in >> freq;
            ngrams[ngram].freq = freq;
            n += freq;
        }

        for(auto& i : ngrams)
        {
            i.second.weight = std::log10((double)(i.second.freq)/n);
        }
        floor = std::log10(0.01/n);
        l = 4; //for quadgrams.
    }

    double score(std::string text)
    {
        double score{0};
        auto c = std::begin(text);
        auto e = std::end(text);
        for(; c+l-1 != e; ++c)
        {
            //Get a string of correct length
            std::string ngram(c, c+l);
            auto it=ngrams.find(ngram);
            if(it != ngrams.end())
                score += it->second.weight;
            else
                score += floor;
        }
        return score;
    }
};
