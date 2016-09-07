/****************************************************
*    TODO: License
*    @author: Alister Maguire
*    @version: 1.0 8/28/16
*****************************************************/

#include <sink.h>

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
