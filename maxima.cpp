// ************************************************************
// * (c) 2018 Alexander Pchelintsev, pchelintsev.an@yandex.ru *
// *      Реализация функций для работы с пакетом Maxima      *
// ************************************************************

// Implementation of functions for working with the Maxima package (a Computer Algebra System)

#include "maxima.h"

void GetStringValue(std::ifstream &f, std::string &res)
{
    res = "";
    char c;
    while(f.get(c))
        if(c == '=')
            break;
    if(c == EOF)
        return;
    while(f.get(c))
    {
        if(c == ',' || c == ']')
            break;
        if(c != '\n' && c != ' ')
            res += c;
    }
}

void ReadFromMaxima(std::fstream &f, std::string &res)
{
    std::string s;
    res = "";
    while(1)
    {
        f >> s;
        if(s[1] == '%' && s[2] == 'o')
        {
            while(1)
            {
                f >> s;
                if(s[1] == '%' && s[2] == 'i')
                    break;
                res += s;
            }
            break;
        }
    }
}
