/****************************************************
* @author: Alister Maguire
* @version: 1.0 8/28/16
*****************************************************/
#ifndef BEDREADER_H
#define BEDREADER_H
#include <reader.h>

/***
* @author: Alister Maguire
*
* A class which reads data from a bed file. Currently, 
* the only data being saved is the the chromosome, start,
* stop, and score. Because bed format allows for the score
* to be be held in two different positions (depending on 
* how much data is contained within each file line), the 
* score index is computed and stored within scoreIdx.
* 
* IMPORTANT: All input files must be sorted beforehand. 
***/
class bedReader : public Reader
{
  private:
    int    scoreIdx;
    void   SetScoreIdx();
  
  public:
         bedReader() {};
         bedReader(const char *dataFileName, string transcriptsFileName="INVALID");
    int  GetScoreIdx();
    void Execute();
};


/***
* @author: Alister Maguire
*
* A class which reads genome coverage files in the format
* output by bedtools genomeCov (per-base). Eventually, this
* will be replaced by an internal base coverage tool. 
*
* IMPORTANT: All input files must be sorted beforehand. 
***/
class bedCovPerBaseReader : public Reader
{
  public:
         bedCovPerBaseReader() {};
         bedCovPerBaseReader(const char *dataFileName, string transcriptsFileName="INVALID");
    void Execute();        
};

#endif
