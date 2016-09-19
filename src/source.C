/****************************************************
*    @author: Alister Maguire
*    @version: 1.0 8/28/16
*****************************************************/

#include <stdlib.h>
#include <source.h>
#include <sstream>
#include <string>
#include <iostream>
#include <helpers.h>
using std::cerr;
using std::endl;


/***
* @author: Alister Maguire
*
* Empty contsructor for Source. 
***/
Source::Source()
{
    genicWindows = false;
    geneCount    = -1;
    natWinCount  = -1;
}


/***
* @author: Alister Maguire
*
* Empty destructor for Source.
***/
Source::~Source()
{
}


/***
* @author: Alister Maguire
*
* Retrieve a reference to srcData.
* @returns: &srcData.
***/
Data *Source::GetData() { return &srcData; }


/***
* @author: Alister Maguire
*
* Retrieve a reference to srcWindowBlock.
* @returns: &srcWindowBlock.
***/
WindowBlock *Source::GetWindowBlock() { return &srcWindowBlock; }


/***
* @author: Alister Maguire
*
* Retrieve a reference to srcNatrualWindows.
* @returns: &srcNatrualWindows.
***/
WindowBlock *Source::GetNaturalWindows() { return &srcNaturalWindows; }


/***
* @author: Alister Maguire
*
* Retreive a reference to srcTranscriptData.
* @returns: &srcTranscriptData.
***/
TranscriptData *Source::GetTranscriptData() { return &srcTranscriptData; }


/***
* @author: Alister Maguire
*
* Get the number of natural windows.
*
* @returns: natWinCount 
***/
long int Source::GetNatWinCount() { return natWinCount; }


/***
* @author: Alister Maguire
*
* Get the number of genes. 
*
* @returns: geneCount;
***/
long int Source::GetGeneCount() { return geneCount; }


/***
* @author: Alister Maguire
*
* Set the geneCount.
*
* @param: count
***/
void Source::SetGeneCount(long int count)
{
    geneCount = count;
}


/***
* @author: Alister Maguire
*
* Find the natural windows contained within srcData, and 
* create instances of windows containing copies of these
* natural windows of data to be contained within 
* srcNaturalWindows. 
* Notes:
*    There are several instances of memory allocation within
*    this method, and all allocations are deleted before 
*    exiting.  
*    
***/
void Source::SetNaturalWindows()
{
    //NOTE: unfortunately, the number of windows is not known
    //      until after walking through all windows. This means
    //      that we need two iterations through all the data, one
    //      for the count, and one for the set.  
    DataLine *lines = srcData.GetLines();
    if (lines != NULL)
    {
 
        unsigned long int size = srcData.GetDataSize();
        DataLine *sparseLines  = new DataLine[size];
        Window *curWindows = new Window[natWinCount];
        int windowIdx      = 0;
        int counter        = 0;
        int sparseCount    = 0;
        int windowStart    = 0;
        double curValTotal = 0;
        bool getStart      = true;
        int i = 0;
        string prevChrom;
        string curChrom;
        int prevStop;
       
        for (int j = 0; j < size; j++)//create data excluding all 0 values
        {
            DataLine line = lines[j];
            if (line.GetVal() != 0.0)
            {
                sparseLines[sparseCount] = line;
                sparseCount++;
            }
        } 
        prevChrom = sparseLines[0].GetChrom();
        prevStop  = sparseLines[0].GetStart();
        while (i < sparseCount)
        {
            curChrom = sparseLines[i].GetChrom();
            if ( ((sparseLines[i].GetStart() - prevStop) > 0) || prevChrom != curChrom)
            {
                //create new window
                DataLine *windowLines = new DataLine[counter];
                DataLine curLine;
                for (int j = 0; j < counter; j++)
                {
                    curLine        = sparseLines[(i-counter) + j];
                    curValTotal   += curLine.GetVal();
                    windowLines[j] = curLine;
                }
                curChrom = curLine.GetChrom();
                Window newWindow(curChrom, counter, windowStart, prevStop, curValTotal/counter, windowLines);
                curWindows[windowIdx] = newWindow;
                counter     = 0;
                curValTotal = 0;
                getStart    = true;
                windowIdx++;
                delete [] windowLines;
                prevStop = sparseLines[i].GetStop();
            }
            if (getStart) //FIXME: is there a better way of doing this?
            {
                windowStart = sparseLines[i].GetStart();
                getStart    = false;
            }
            prevStop  = sparseLines[i].GetStop();
            prevChrom = sparseLines[i].GetChrom();
            i++;
            counter++;
        }
        DataLine *windowLines = new DataLine[counter];
        DataLine curLine;
        for (int j = 0; j < counter; j++)
        {
            curLine = sparseLines[(i-counter) + j];
            curValTotal += curLine.GetVal();
            windowLines[j] = curLine;
        }
        curChrom = curLine.GetChrom();
        Window newWindow(curChrom, counter, windowStart, prevStop, curValTotal/counter, windowLines);
        curWindows[windowIdx] = newWindow;
        srcNaturalWindows.SetWindows(natWinCount, curWindows);
        delete [] windowLines;
        delete [] curWindows;
        delete [] sparseLines;
    }
    
    else
        cerr << "ERROR: Cannot set natural windows because data is NULL" << endl;
}


/***
* @author: Alister Maguire
*
* Find the genic windows contained within srcData, and 
* create instances of windows containing copies of these
* genic windows of data to be contained within 
* srcGenicWindows. 
* Notes:
*     Computing genic winodws depends on srcTranscriptData being 
*     initialized. 
*     If a gene within the transcripts is not able to be located
*     in srcData, the operation is aborted. 
***/
void Source::SetGenicWindows()
{
//TODO: Currently, it is assumed that all genic regions will be 
//      accounted for, and thus the computations will only be completed
//      if all genes are discovered within the data. This method was made
//      specifically for coverage counts that account for all base pairs, 
//      so this makes sense. In the future, we may want to use this method
//      on data taken from bed files, and this approach may need to change.
//      Either that or we change the way we read in bed files.  

    TranscriptLine *transcripts = srcTranscriptData.GetLines();
    DataLine *dataLines         = srcData.GetLines();
    if (transcripts == NULL)
        cerr << "ERROR: transcripts have not been loaded -> cannot compute gene windows" << endl;
    else if (dataLines == NULL)
        cerr << "ERROR: data has not been loaded -> cannot compute gene windows" << endl;
    else
    {
        
        unsigned long int dataSize = srcData.GetDataSize();
        unsigned long int tranSize = srcTranscriptData.GetDataSize();
        unsigned int geneCount     = srcTranscriptData.GetGeneCount();
        Window *curWindows         = new Window[geneCount];
        unsigned int windowIdx     = 0;
        unsigned int pos           = 0;
        unsigned int m             = 0;
        int span                   = 0;
        double curValTotal         = 0.0; 
        bool missingGene           = false;
        TranscriptLine curTranscript;
        TranscriptLine nxtTranscript;
        string geneChrom;
        string nextChrom;
        double chromNum;
        unsigned int geneStart;
        unsigned int geneStop;
        for (int i = 0; i < tranSize; i++)
        {
            curTranscript = transcripts[i];
            if (curTranscript.GetThickEnd() == "exon")//TODO: I could also store all exons when reading in.
            {
                geneChrom = curTranscript.GetChrom();
                geneStart = curTranscript.GetStart();
                geneStop  = curTranscript.GetStop();
                nextChrom = geneChrom;
                //Note: because the chromosome names contain a string of letters followed
                //      by some number, we need to extract that number in order to compare
                //      chromosome names. 
                chromNum  = HPR::ExtractNumFromString(geneChrom);        

                //We want to "compress" genic windows so that they don't 
                //contain gaps => we need to find the full gene span. 
                while (i < (tranSize - 2) && geneChrom == nextChrom)
                {
                    i++;
                    nxtTranscript = transcripts[i];
                    if (nxtTranscript.GetThickEnd() == "exon")
                    {
                        nextChrom = nxtTranscript.GetChrom(); 
                        if (nextChrom == geneChrom && geneStop < nxtTranscript.GetStop())
                        {
                            geneStop  = nxtTranscript.GetStop();
                        }
                    }
                }
                span = geneStop - geneStart;

                while (HPR::ExtractNumFromString(dataLines[m].GetChrom()) < chromNum && m < dataSize)
                    m++;

                if (HPR::ExtractNumFromString(dataLines[m].GetChrom()) > chromNum)
                {
                    cerr << "Gene not found: " << curTranscript.GetGeneId() << " "
                         << curTranscript.GetStart() << " " << curTranscript.GetStop() << endl;
                    missingGene = true;
                    break;
                }

                while (dataLines[m].GetStart() < geneStart && m < dataSize)
                    m++; 


                if (dataLines[m].GetStart() > geneStart)
                {
                    cerr << "Gene not found: " << curTranscript.GetGeneId() << " " 
                         << curTranscript.GetStart() << " " << curTranscript.GetStop() << endl;
                    missingGene = true;
                    break;
                }
                else if (geneStop == dataLines[m+span-1].GetStop() && geneChrom == dataLines[m+span-1].GetChrom())
                {
                    DataLine *windowLines = new DataLine[span];
                    DataLine curLine;
                    for (int j = m; j < (m+span); j++)
                    {
                        curLine          = dataLines[j];
                        curValTotal     += curLine.GetVal();
                        windowLines[pos] = curLine;
                        pos++;
                    }
                    Window newWindow(curTranscript.GetGeneId(), span, geneStart, 
                                     geneStop, curValTotal/span, windowLines);
                    curWindows[windowIdx] = newWindow;                 
                    pos         = 0;
                    curValTotal = 0.0;
                    windowIdx++;
                    delete [] windowLines;
                }
                else
                {
                    cerr << "Gene not found: " << curTranscript.GetGeneId() << " " 
                         << curTranscript.GetStart() << " " << curTranscript.GetStop() << endl;
                    missingGene = true;
                    break;
                }
            } 
        }
        if (!missingGene)
        {
            srcWindowBlock.SetWindows(geneCount, curWindows);
            genicWindows = true;
        }
        delete [] curWindows;                
    }
}

