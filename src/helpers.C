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

    for (int i = (bCount-1); i >= 0; i--)
    {
        for (int j = 0; j < i; j++)
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


/***
* @author: Alister Maguire
*
* Combine two windows and return the result. NOTE: Memory
* is allocated and is not deleted within this method. This 
* memory will be deleted when the object goes out of scope. 
*
* @param: w1 -> the first window to be copied over. 
*         w2 -> the second window to be copied over. 
* @returns: cData -> a new window which consists of 
*               w1's data followed by w2's data. 
*           If one or both of the entered windows contain
*           DataLines which are null, a scrap Data object is 
*           returned. 
Window HPR::CombineWindows(Window w1, Window w2)
{
    DataLine *w1Lines    = w1.GetLines();
    DataLine *w2Lines    = w2.GetLines();
    if (w1Lines == NULL || w2Lines == NULL)
    {
        cerr << "ERROR: cannot combine null data!\n" << endl;
        Window scrap;
        return scrap;
    }

    else
    {
        unsigned long int w1Size = w1.GetDataSize();
        unsigned long int w2Size = w2.GetDataSize();
        unsigned long int totalSize = w1Size + w2Size;
        DataLine *cDataLines = new DataLine[totalSize];
        
        for (int i = 0; i < w1Size; i++)
        {
            DataLine curLine = w1Lines[i];
            DataLine newLine(curLine.GetChrom(), curLine.GetStart(), curLine.GetStop(), curLine.GetVal());
            cDataLines[i] = newLine;
        }

        for (int j = w1Size; j < totalSize; j++)
        {
            DataLine curLine = w2Lines[j-w1Size];
            DataLine newLine(curLine.GetChrom(), curLine.GetStart(), curLine.GetStop(), curLine.GetVal());
            cDataLines[j] = newLine; 
        } 
       
         
        double newAvg = (w1.GetValAvg() + w2.GetValAvg()) / 2;
        Window cWindow(w1.GetTitle, totalSize, w1.GetStart(), w2.GetStop(), newAvg, cDataLines);
        return cWindow;
    }
}

***/
