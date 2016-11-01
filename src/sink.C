/****************************************************
*    @author: Alister Maguire
*    @version: 1.0 8/28/16
*****************************************************/

#include <sink.h>
#include <stdlib.h>
#include <iostream>

using std::cerr;
using std::endl;

/***
* @author: Alister Maguire
*
* Set the snkData to point to a given data object.
* @param: data -> pointer to a Data object. 
***/
void Sink::SetSinkData(Data *data)
{
    snkData = data;
}


/***
* @author: Alister Maguire
*
* Set the snkWindowBlock to point to a given WindowBlock. 
* @param: block -> pointer to a WindowBlock object.
***/
void Sink::SetSinkWindowBlock(WindowBlock *block)
{
   snkWindowBlock = block; 
}


/***
* @author: Alister Maguire
*
* Set the snkTranscriptData to point to a given TranscriptData.
* @param: tData -> pointer to a TranscriptData object.
***/
void Sink::SetSinkTranscriptData(TranscriptData *tData)
{
    snkTranscriptData = tData;
}


/***
* @author: Alister Maguire
*
*
* @param: d2 -> a Data object to act as a baseline to 
*           compare to. 
***/
void Sink::Diff(Data *d2)
{
    unsigned long int size = snkData->GetDataSize(); 
    if (size != d2->GetDataSize())
    {
        cerr << "ERROR: cannot diff datasets of different size!" << endl;
        exit(EXIT_FAILURE);
    }
    
    double diff; //d1 - d2
    DataLine *d1Lines;
    DataLine *d2Lines;
    DataLine  d1Line;
    DataLine  d2Line;
    d1Lines = snkData->GetLines();
    d2Lines = d2->GetLines();
    
    if (snkData == NULL || d2Lines == NULL)
    {
        cerr << "ERROR: trying to diff NULL lines!" << endl;
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; ++i)
    {
        d1Line = d1Lines[i]; 
        d2Line = d2Lines[i];
        diff   = d1Line.GetVal() - d2Line.GetVal();
        d1Lines[i].SetDiff(diff);
        diff = 0.0;
    }
    snkData->DiffSet(true);
}

