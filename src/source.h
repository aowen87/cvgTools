/****************************************************
*    @author: Alister Maguire
*    @version: 1.0 8/28/16
*****************************************************/

#ifndef SOURCE_H
#define SOURCE_H
#include <data.h>


/***
* @author: Alister Maguire
*
* A "source" container for DNA data. This container holds data
* that is directly read in from various types of files.
* Notes: 
*    srcNaturalWindows is a WindowBlock that contains "natural windows". 
*    I'm defining a natural window as any section of consecutive base
*    pairs on a single chromosome that have a value greater than 0. This 
*    means that changes in chromosomes coincide with new windows. 
*   
***/
class Source
{
  protected:
    Data              srcData;
    WindowBlock       srcNaturalWindows;
    WindowBlock       srcWindowBlock;
    TranscriptData    srcTranscriptData;
    GeneData          srcGeneData;
    long int          natWinCount;
    long int          geneCount;
    bool              genicWindows;

  public:
                       Source();
                      ~Source();
    Data              *GetData();
    WindowBlock       *GetWindowBlock();
    WindowBlock       *GetNaturalWindows();
    TranscriptData    *GetTranscriptData();
    GeneData          *GetGeneData();
    long int           GetNatWinCount();
    long int           GetGeneCount();
    void               SetGeneCount(long int count);
    void               SetGenicWindows();
    void               SetNaturalWindows();
    virtual void       Execute() = 0;
    virtual unsigned long int SetDataSize(char *fname) = 0;
};

#endif
