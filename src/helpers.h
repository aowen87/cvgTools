/****************************************************
*    @author: Alister Maguire
*    @version: 1.0 8/28/16
*****************************************************/
#ifndef HELPERS_H
#define HELPERS_H
#include <string>
#include <data.h>
using std::string;

namespace HPR 
{
    bool   CharIsDigit(char c);
    int    CharToInt(char c);
    double ExtractNumFromString(string s);
    void   GeneQuickSort(Gene **genes, int low, int high);
    int    GeneCompare(Gene gene1, Gene gene2);
}
#endif


