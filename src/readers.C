/****************************************************
* @author: Alister Maguire
* @version: 1.0 8/28/16
*****************************************************/

#include <stdio.h>
#include <sstream>
#include <readers.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <data.h>
#include <cmath>
using std::cerr;
using std::endl;
using std::ifstream;
using std::string;
using std::abs;


/***
* @author: Alister Maguire
* 
* Constructor for the bedReader.
* set dfname to the name of the file containing the 
* sequenced data, call SetScoreIdx() and
* SetSrcDataSize(). If a transcripts file is 
* included, set tfname to this file name,
* and call SetSrcTranscriptDataSize(). 
* 
* @param: dataFileName -> the name of the bed file containing the 
*             sequenced data.
*         transcriptsFileName (optional) -> the name of the bed file 
*             containing the transcripts information
*
* IMPORTANT: All input files must be sorted beforehand. 
***/
bedReader::bedReader(const char *dataFileName, string transcriptsFileName)
{
    int size  = strlen(dataFileName) + 1;
    dfname    = new char[size];
    strcpy(dfname, dataFileName);
    SetScoreIdx();
    SetSrcDataSize();
   
    if (transcriptsFileName != "INVALID")
    {
        size       = transcriptsFileName.size() + 1;
        int strLen = transcriptsFileName.length();
        tfname     = new char[size];
        for (int i = 0; i < strLen; i++)
        {
            tfname[i] = transcriptsFileName[i];
        } 
        tfname[size-1] = '\0';
    }
}


/***
* @author: Alister Maguire
*
* Find the line index that includes the score
* within the given bed file, and store this 
* index within scoreIdx.
*
***/
void bedReader::SetScoreIdx()
{
    ifstream inFile (dfname);
    if (inFile.is_open())
    {
        string line;
        string delim = "\t";
        int count    = 0;
     
        getline(inFile, line);
        size_t pos = 0;
    
        while ((pos = line.find(delim)) != string::npos)
        {
            count += 1;
            line.erase(0, pos + delim.length());
        }
    
        if (count == 3)
            scoreIdx = 3;
        else if (count > 3)
            scoreIdx = 4;
        else
            cerr << "ERROR: Invalid bed format" << endl; 
    }
    else
        cerr << "ERROR: Unable to open data file" << endl; 
}


/***
* @author: Alister Maguire
*
* @returns: scoreIdx
***/
int bedReader::GetScoreIdx() { return scoreIdx; }
 

/***
* @author: Alister Maguire
* 
* Execute the reader => read the bedfile containing
* sequenced data. If a transcripts file was input, call
* ReadTranscripts().  
***/
void bedReader::Execute()
{
    ifstream inFile (dfname);
    if (inFile.is_open())
    {
        string rawLine;
        string name;            //TODO: change name and prevName to chrom and prevChrom
        string prevName;
        int start;
        int stop;
        int prevStop;
        int score;
        int prevScore = 0;
        unsigned int count = 0;
        unsigned long int limit = srcData.GetDataSize()-1; 
        DataLine *dataSet = srcData.GetLines();
        switch (scoreIdx)
        {
            case 3:
            {
                std::getline(inFile, rawLine);
                std::istringstream iss(rawLine);
                if (!(iss >> prevName >> prevStop >> stop >> score))//Set prevStop and prevName
                    break;
                inFile.clear();
                inFile.seekg(0, std::ios::beg);
                while (std::getline(inFile, rawLine))
                {
                    std::istringstream iss(rawLine);
                    if (!(iss >> name >> start >> stop >> score))
                        break;
                    if (score > srcData.GetHighVal())
                        srcData.SetHighVal(score);
                    if (score < srcData.GetLowVal())
                        srcData.SetLowVal(score);
                    DataLine line(name, start, stop, score);
                    dataSet[count] = line; 
                    if (count == limit && score == 0.0)
                        break; 

                    if ( ((std::abs(start - prevStop) > 0 ) && prevScore != 0.0 && 
                         score != 0.0 && prevName == name) || 
                         (score == 0.0 && prevScore != 0.0 && prevName == name) || 
                         (prevName != name && prevScore != 0))
                        natWinCount++; 
                    prevStop  = stop;
                    prevScore = score;
                    prevName  = name;
                    count++;
                } 
                if (score != 0)
                    natWinCount++;//Account for the last window
                break;
            }

            case 4:
            {
                string scrap;
                std::getline(inFile, rawLine);
                std::istringstream iss(rawLine);
                if (!(iss >> prevName >> prevStop >> stop >> scrap >> score))//Set prevStop and prevName
                        break;
                inFile.clear();
                inFile.seekg(0, std::ios::beg);
                while (std::getline(inFile, rawLine))
                {
                    std::istringstream iss(rawLine);
                    if (!(iss >> name >> start >> stop >> scrap >> score))
                        break;
                    if (score > srcData.GetHighVal())
                        srcData.SetHighVal(score);
                    if (score < srcData.GetLowVal())
                        srcData.SetLowVal(score);
                    DataLine line(name, start, stop, score);
                    dataSet[count] = line; 
                    if (count == limit && score == 0.0)
                        break; 
                    if ( (((start - prevStop) > 0 ) && prevScore != 0.0 && score != 0.0 && prevName == name) || 
                    (score == 0.0 && prevScore != 0.0 && prevName == name) || 
                    (prevName != name && prevScore != 0))
                       natWinCount++; 
                    count++;
                    prevStop  = stop;
                    prevScore = score;
                    prevName  = name;
                } 
                if (score != 0)
                    natWinCount++;//Account for the last window
                break;
             }
        }

        if (tfname != NULL)
        {
            ReadTranscripts(); 
        }
    }
    else
        cerr << "ERROR: Unable to open data file" << endl; 
}



/***
* @author: Alister Maguire
*
* Constructor for the bedCovPerBaseReader.
* Set dfname to the name of the file containing the
* sequenced data, and call SetSrcDataSize(). If a
* transcripts file was input, set tfname to the name 
* of the transcripts file and call SetSrcTranscriptDataSize(). 
*
* @param: dataFileName -> the name of the bed coverage file containing sequenced
*             data. This file MUST be in the format output from the bedtools genomeCov
*             module (per-base coverage). 
*         transcriptsFileName (optional) -> the name of the bed file containing the 
*             transcript data. 
*
* IMPORTANT: All input files must be sorted beforehand. 
***/
bedCovPerBaseReader::bedCovPerBaseReader(const char *dataFileName, string transcriptsFileName)
{
    int size = strlen(dataFileName) + 1;
    dfname   = new char[size];
    strcpy(dfname, dataFileName);
    SetSrcDataSize();
    
    if (transcriptsFileName != "INVALID")
    {
        size       = transcriptsFileName.size() + 1;
        int strLen = transcriptsFileName.length();
        tfname     = new char[size];
        for (int i = 0; i < strLen; i++)
        {
            tfname[i] = transcriptsFileName[i];
        } 
        tfname[size-1] = '\0';
    }
}



/***
* @author: Alister Maguire
*
* Execute the bedCovPerBaseReader => read the genome coverage
* file, and, if a transcripts file was included, call ReadTranscripts().
*
***/
void bedCovPerBaseReader::Execute()
{
    ifstream inFile (dfname);
    if (inFile.is_open())
    {
        string rawLine;
        string name;
        string prevName;
        int start;
        int prevStop;
        int score;
        int prevScore = 0;
        unsigned int count = 0;
        DataLine *dataSet  = srcData.GetLines();
        unsigned long int limit = srcData.GetDataSize()-1; 
        std::getline(inFile, rawLine);                                        
        std::istringstream iss(rawLine);
        if (!(iss >> prevName >> prevStop >> score))//Set prevStop and prevName
        prevName  = "NONE";
        prevStop  = -1;
        prevScore = -1;
        inFile.clear();
        inFile.seekg(0, std::ios::beg);
        while (std::getline(inFile, rawLine))
        {
            std::istringstream iss(rawLine);
            if (!(iss >> name >> start >> score))
                break;
            if (score > srcData.GetHighVal())
                srcData.SetHighVal(score);
            if (score < srcData.GetLowVal())
                srcData.SetLowVal(score);
            DataLine line(name, start-1, start, score);
            dataSet[count] = line; 
            if (count == limit && score == 0.0)
                break; 
            start--;

            if ( ((std::abs(start - prevStop) > 0 ) && prevScore != 0.0 
                && score != 0.0 && prevName == name) || 
               (score == 0.0 && prevScore != 0.0 && prevName == name) || 
               (prevName != name && prevScore != 0.0))
                natWinCount++; 
            count++;
            prevStop  = start + 1;
            prevScore = score;
            prevName  = name;
        } 

        if (score != 0.0)
            natWinCount++;//Account for the last window

        if (tfname != NULL)
        {
            ReadTranscripts();
        }
    }
    else
        cerr << "ERROR: Unable to open data file" << endl; 

}



