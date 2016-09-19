/****************************************************
*    @author: Alister Maguire
*    @version: 1.0 8/28/16
*****************************************************/

#include <helpers.h>
#include <iostream>
using std::cerr;
using std::endl;

/***
* @author: Alister Maguire
*
* Determine if a character is a digit. 
*
* @param: c -> a character. 
* @returns: true if c is a digit. False otherwise. 
***/
bool HPR::CharIsDigit(char c)
{
    return (c >= '0' && c <= '9');
}


/***
* @author: Alister Maguire
*
* Convert a character to an integer. 
*
* @param: c -> a character. 
* @returns: the integer form of c. 
***/
int HPR::CharToInt(char c)
{
    return c - '0';
}


/***
* @author: Alister Maguire
*
* Extract a number from a string.
* For example, using IAte543.332Pies as input 
* would result in 543.332 being returned. This function
* was built with the intention of grabbing double values
* from strings of the following format:
* <(string)(double)>
* This function has not been tested for use in other, 
* more complicated scenarios.  
*
* @param: s -> a string.
* @returns: a double found within the given string. 
***/
double HPR::ExtractNumFromString(string s)
{
    unsigned int len = s.length();
    char beforeDc[1024];
    char afterDc[1024];
    bool whole  = true;
    int  bCount = 0;
    int  aCount = 0;
    char cur;
    double total = 0.0;
    double multiplier;
    int cNum;

    multiplier = 1;
    
    for (int i = 0; i < len; i++)
    { 
        cur = s[i];
        if (cur == '.')
        {
            whole = false;
            continue;
        }
        if (CharIsDigit(cur))
        {
            if (whole)
            {
                beforeDc[bCount] = cur;
                bCount++;    
            }
            else
            {
                afterDc[aCount] = cur;
                aCount++;
            }
        }
    }

    for (int i = 0; i < bCount; i++)
    {
        for (int j = i; j < (bCount-1); j++)
        {
            multiplier *= 10;
        }
        cNum = CharToInt(beforeDc[i]); 
        total += cNum * multiplier;
        multiplier = 1;
    } 

    multiplier = .1;

    for (int i = (aCount-1); i >= 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            multiplier = multiplier / 10;
        }
        cNum = CharToInt(afterDc[i]); 
        total += cNum * multiplier;
        multiplier = .1;
    }
    return total;
}


