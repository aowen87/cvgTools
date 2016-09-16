/****************************************************
*    @author: Alister Maguire
*    @version: 1.0 8/28/16
*****************************************************/

#ifndef READER_H
#define READER_H
#include <source.h>

/***
* @author: Alister Maguire
*
* A basic structure for a file reader. The Reader
* contains two filenames, one of which is for sequenced
* data, and the other of which is for the transcript/gene
* information associated with the sequenced data. 
* Transcripts files must be in bed format. 
***/
class Reader : public Source
{
  protected:
    char *dfname;
    char *tfname;

  public:
                      Reader();
                     ~Reader();
    unsigned long int SetDataSize(char *fname);
    void              SetSrcDataSize();
    void              SetSrcTranscriptDataSize();
    void              ReadTranscripts();
    virtual void      Execute() = 0;
};

#endif
