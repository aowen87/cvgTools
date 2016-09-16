/****************************************************
*    @author: Alister Maguire
*    @version: 1.0 8/28/16
*****************************************************/

#ifndef SINK_H
#define SINK_H
#include <data.h>

/***
* @author: Alister Maguire
*
* A "sink" container. This container holds data that 
* does not come directly from a file. That is, the data
* contained within the sink references data that has already
* been read and exists elsewhere. Sinks are used for writing 
* output files and may also be used for data manipulation.  
***/
class Sink
{
  protected:
    Data           *snkData;
    WindowBlock    *snkWindowBlock;
    TranscriptData *snkTranscriptData;
  public:
    void SetSinkData(Data *data);
    void SetSinkWindowBlock(WindowBlock *block);
    void SetSinkTranscriptData(TranscriptData *tData);
};

#endif
