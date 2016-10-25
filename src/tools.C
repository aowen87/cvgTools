/****************************************************
*    @author: Alister Maguire
*    @version: 1.0 8/28/16
*****************************************************/
#include <stdlib.h>
#include <tools.h>
#include <stdio.h>
#include <iostream>

using std::cerr;
using std::endl;



/***
*FIXME: testing needed 
***/
void Diff::BasePairDiff(Data *d1, Data *d2)
{
    unsigned long int d1Size;
    unsigned long int d2Size;
    d1Size = d1->GetDataSize();
    d2Size = d2->GetDataSize();

    if (d1Size != d2Size)
    {
        cerr << "ERROR: cannot diff datasets of different size!" << endl;
        exit(EXIT_FAILURE);
    }
    
    double diff; //d2 - d1
    DataLine *d1Lines;
    DataLine *d2Lines;
    DataLine d1Line;
    DataLine d2Line;
    d1Lines = d1->GetLines();
    d2Lines = d2->GetLines();
    
    if (d1Lines == NULL || d2Lines == NULL)
    {
        cerr << "ERROR: trying to diff NULL lines!" << endl;
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < d1Size; ++i)
    {
        d1Line = d1Lines[i]; 
        d2Line = d2Lines[i]; 

        diff = d2Line.GetVal() - d2Line.GetVal();
        d2Lines[i].SetDiff(diff);
        diff *= -1;
        d2Lines[i].SetDiff(diff);
        diff = 0.0;
    }
}
