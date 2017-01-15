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


void ComputeFeatureAvg(unsigned int dataIdx, DataLine *dataLines, 
                       vector<GeneFeature> *features);

/***
* @author: Alister Maguire
*
* Empty contsructor for Source. 
***/
Source::Source()
{
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
* Retreive a reference to srcGeneData.
* @returns: &srcGeneData.
***/
GeneData *Source::GetGeneData() { return &srcGeneData; }


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
       
        for (unsigned int j = 0; j < size; j++)//create data excluding all 0 values
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
            if (getStart) //TODO: is there a better way of doing this?
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
//NOTE: Currently, it is assumed that all genic regions will be 
//      accounted for, and thus the computations will only be completed
//      if all genes are discovered within the data. This method was made
//      specifically for coverage counts that account for all base pairs, 
//      so this makes sense. In the future, we may want to use this method
//      on data taken from bed files, and this approach may need to change.
//      Either that or we change the way we read in bed files.  

    Gene *genes         = srcGeneData.GetGenes();    
    DataLine *dataLines = srcData.GetLines();

    if (genes == NULL)
    {
        cerr << "ERROR: genes have not been loaded -> cannot compute gene windows" << endl;
        exit(EXIT_FAILURE);
    }
    else if (dataLines == NULL)
    {
        cerr << "ERROR: data has not been loaded -> cannot compute gene windows" << endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        
        unsigned long int dataSize = srcData.GetDataSize();
        unsigned long int gCount   = srcGeneData.GetGeneCount();
        unsigned int windowIdx     = 0;
        unsigned int pos           = 0;
        unsigned int dataIdx       = 0;
        unsigned int prevDataIdx   = 0;
        int span                   = 0;
        double curValTotal         = 0.0; 
        Gene *curGene;
        Gene nxtGene;
        string geneChrom;
        double chromNum;
        unsigned int geneStart;
        unsigned int geneStop;
        unsigned int prevGeneStop = 0;
        unsigned int prevGeneStart;
        for (unsigned int i = 0; i < gCount; i++)
        {
            curGene = &genes[i];
            geneChrom = curGene->GetChrom();
            geneStart = curGene->GetStart();
            geneStop  = curGene->GetStop();
            prevDataIdx = dataIdx;

            //Note: because the chromosome names contain a string of letters followed
            //      by some number, we need to extract that number in order to compare
            //      chromosome names. 
            chromNum  = HPR::ExtractNumFromString(geneChrom);        

            //Check for overlap. If it exists, 
            //see if we can start looking for the 
            //gene from the previous start. If not,
            //look from the beginning.
            if (geneStart < prevGeneStop)
            {
                if (geneStart < prevGeneStart)
                    dataIdx = 0;
                else
                    dataIdx = prevDataIdx;
            } 

            span = geneStop - geneStart;

            //search for the gene within our data
            while (HPR::ExtractNumFromString(dataLines[dataIdx].GetChrom()) < chromNum && dataIdx < dataSize)
                dataIdx++;

            if (HPR::ExtractNumFromString(dataLines[dataIdx].GetChrom()) > chromNum)
            {
                cerr << "Gene not found: " << curGene->GetGeneId() << " "
                     << curGene->GetStart() << " " << curGene->GetStop() << endl;
                cerr << "line: " << __LINE__ << endl;
                exit(EXIT_FAILURE);
            }

            while (dataLines[dataIdx].GetStart() < geneStart && dataIdx < dataSize)
                dataIdx++; 

            if (dataLines[dataIdx].GetStart() > geneStart)
            {
                cerr << "Gene not found: " << curGene->GetGeneId() << " " 
                     << curGene->GetStart() << " " << curGene->GetStop() << endl;
                cerr << "line: " << __LINE__ << endl;
                exit(EXIT_FAILURE);
            }
            else if (geneStop == dataLines[dataIdx+span-1].GetStop() && 
                     geneChrom == dataLines[dataIdx+span-1].GetChrom())
            {
                DataLine *windowLines = new DataLine[span];
                DataLine curLine;
               
                for (unsigned int j = dataIdx; j < (dataIdx+span); j++)
                {
                    curLine          = dataLines[j];
                    curValTotal     += curLine.GetVal();
                    windowLines[pos] = curLine;
                    pos++;
                }

                //Compute feature regions
                vector<GeneFeature> *exons     = (curGene->GetExons()); 
                vector<GeneFeature> *startCdns = (curGene->GetStartCodons()); 
                vector<GeneFeature> *stopCdns  = (curGene->GetStopCodons()); 
                vector<GeneFeature> *cds       = (curGene->GetCDS()); 

                ComputeFeatureAvg(dataIdx, dataLines, exons);
                ComputeFeatureAvg(dataIdx, dataLines, startCdns);
                ComputeFeatureAvg(dataIdx, dataLines, stopCdns);
                ComputeFeatureAvg(dataIdx, dataLines, cds);

                // Set values for entire gene
                curGene->SetData(span, windowLines);
                curGene->SetValAvg(curValTotal/span);

                prevGeneStart = geneStart;
                prevGeneStop  = geneStop;
                pos           = 0;
                curValTotal   = 0.0;
                windowIdx++;
                delete [] windowLines;
            }
            else
            {
                cerr << "Gene not found: " << curGene->GetGeneId() << " " 
                     << curGene->GetStart() << " " << curGene->GetStop() << endl;
                cerr << "line: " << __LINE__ << endl;
                exit(EXIT_FAILURE);
            }
        }
    }
}


/***
* @author: Alister Maguire
*
* Set the peak windows for srcData. Peak windows
* are sections of data that are >= a determined base
* limit. The base is determined from the peakLimit
* input value. 
*
* @param: peakLimit ->  a value between 0 and 1
*         that indicates a percentage to determine
*         the lowest value to be considered for
*         the peak windows. .5 would indicate that
*         any value >= the mid value will be included. 
*         .9 would indicate the highest 90%, inclusive. 
***/
void Source::SetPeakWindows(double peakLimit)
{
    if ( (peakLimit < 0.0) || (peakLimit > 1.0) )
    {
        cerr << "ERROR: peak limit must be between 0.0 and 1.0, inclusive."
             << " Line: " << __LINE__ <<  endl;
        exit(EXIT_FAILURE); 
    }

    double low      = srcData.GetLowVal();
    double valLimit = low + ((srcData.GetHighVal() - low) 
                      * peakLimit);

    DataLine *lines = srcData.GetLines();
    if (lines != NULL)
    {
        unsigned long int size = srcData.GetDataSize();
        vector<Window> windows;
        unsigned int winCount  = 0; 
        unsigned int peakCount = 0;

        for (unsigned int i = 0; i < size; ++i)
        {
            double winTotal        = 0.0;
            unsigned int lineCount = 0;
            int winStart           = -1;
            unsigned int winStop   = 0;
            DataLine curLine;
            curLine = lines[i];
            string curChrom  = curLine.GetChrom();
            string prevChrom = curLine.GetChrom();

            while ((curLine.GetVal() >= valLimit) && (i < size)
                   && (curChrom.compare(prevChrom) == 0))
            {
                winTotal += curLine.GetVal();
                winStop   = curLine.GetStop();

                if (winStart == -1)
                    winStart = curLine.GetStart();
                lineCount++;
                
                if (i < (size-1))
                {
                    i++;
                    curLine   = lines[i];
                    prevChrom = curChrom;
                    curChrom  = curLine.GetChrom();

                }
                else
                    i++;
            }

            //if we actually compute a window, create it.  
            if (lineCount > 0)
            {
                DataLine *winLines = new DataLine[lineCount];
                DataLine curLine;
        
                for (unsigned int j = 0; j < lineCount; ++j)
                {
                    curLine     = lines[(i-lineCount) + j];
                    winLines[j] = curLine;
                }
 
                string c = static_cast<std::ostringstream*>
                           (&(std::ostringstream() << peakCount))
                           ->str();
                string title = prevChrom + "_peak_" + c; 
                Window w(title, lineCount, (unsigned int) winStart, 
                         winStop, winTotal/lineCount, winLines);
                windows.push_back(w);
                winCount++;
                peakCount++;
                if (prevChrom.compare(curChrom) != 0)
                {
                    //we're switching to a new chrom, so 
                    //set the new peak count, and decrement 
                    //i by one so that we can grab the start. 
                    peakCount = 0;
                    i--;
                }
            }
        }

        unsigned int numWindows = windows.size();
        Window *finalWindows    = new Window[numWindows];
        for (unsigned int i = 0; i < numWindows; ++i)
            finalWindows[i] = windows[i];

        srcWindowBlock.SetWindows(winCount, finalWindows);
        delete [] finalWindows;
    }
}


/***
* @author: Alister Maguire
*
* Compute the average values of features
* for a given vector of gene features. This is 
* a helper function to be used when computing 
* genic averages.  
* 
* @param: dataIdx -> the current index for the 
*                    gene data. 
*         dataLines -> the gene data. 
*         features  -> a vector of gene features. 
***/
void ComputeFeatureAvg(unsigned int dataIdx, DataLine *dataLines, 
                        vector<GeneFeature> *features)
{

    unsigned int numFeatures = features->size();
    for (unsigned int f = 0; f < numFeatures; ++f)
    {
        GeneFeature *feature = &(*features)[f]; 
        unsigned int fStart  = feature->GetStart();
        unsigned int fStop   = feature->GetStop();
        double baseCount     = 0;
        double featureTotal  = 0.0;

        unsigned int fIdx;
        for (fIdx = dataIdx; fStart > dataLines[fIdx].GetStart(); ++fIdx) 
        {}
        fStart++;

        for (;fStop >= dataLines[fIdx].GetStop(); ++fIdx)
        {
            featureTotal += dataLines[fIdx].GetVal(); 
            baseCount++; 
        }

        feature->SetValAvg(featureTotal/baseCount); 
    }
}
