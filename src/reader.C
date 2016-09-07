/****************************************************
*    TODO: License
*    @author: Alister Maguire
*    @version: 1.0 8/28/16
*****************************************************/

#include <reader.h>
#include <sstream>
#include <data.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
using std::cerr;
using std::endl;
using std::ifstream;

/***
* @author: Alister Maguire
*
* Default Reader constructor. Set the 
* filenames equal to NULL. 
***/
Reader::Reader()
{
    dfname = NULL;
    tfname = NULL;
}


/***
* @author: Alister Maguire
*
* Deconstructor for Reader. Delete filename pointers. 
***/
Reader::~Reader() 
{
    if (dfname != NULL)
        delete [] dfname;
    if (tfname != NULL)
        delete [] tfname;
}


/***
* @author: Alister Maguire
*
* Count the number of lines within a file. 
* @param:   fname -> the name of the file to be accessed.  
* @returns: size -> the number of lines within the 
*           accessed file.  
*
* IMPORTANT: All input files must be sorted beforehand. 
***/
 //TODO: Make sure the files are sorted
unsigned long int Reader::SetDataSize(char *fname)
{
    ifstream inFile (fname);
    unsigned long int size = 0;
    if (inFile.is_open())
    {
        string scrap;
        while (std::getline(inFile, scrap))
            size++;
    }
    else
        cerr << "ERROR: Unable to open file" << endl; //TODO: error handling needed
    return size;
}


/***
* @author: Alister Maguire
*
* Compute the size of the data file being used
* to create srcData, and initialize srcData. 
***/
void Reader::SetSrcDataSize()
{
    srcData.InitData(SetDataSize(dfname));
}


/***
* @author: Alister Maguire
*
* Compute the size of the data file being used
* to create srcTranscriptData, and initialize
* srcTranscriptData. 
***/
void Reader::SetSrcTranscriptDataSize()
{
    srcTranscriptData.InitData(SetDataSize(tfname));
}


/***
* @author: Alister Maguire
*
* Read gene information from a transcripts file, and 
* populate srcTranscriptData with this information.  
*
* IMPORTANT: All input files must be sorted beforehand. 
***/
//TODO: make sure the files are sorted
void Reader::ReadTranscripts()
{
    ifstream inFile (tfname);
    if (inFile.is_open())
    {
        unsigned int eCount = 0;
        string rawLine;
        string chrom;
        string geneId;
        string transcriptId;
        string name;
        string thickStart;
        string thickEnd;
        string scrap;
        char   rgb;
        int    start;
        int    stop;
        char   strand;
        TranscriptLine *TranscriptLines = srcTranscriptData.GetLines();
        int count = 0;
        while (std::getline(inFile, rawLine))
        {
            std::istringstream iss(rawLine);
            if (!(iss >> chrom >> start >> stop >> name >> scrap >> strand >> thickStart 
               >> thickEnd >> rgb >> scrap >> geneId >> scrap >> transcriptId))
                break;
            if (thickEnd == "exon")
                eCount++;
            geneId.erase(0, 1);
            geneId.erase(geneId.length()-2, 2);
            transcriptId.erase(0, 1);
            transcriptId.erase(transcriptId.length()-2, 2);
            TranscriptLine line(chrom, geneId, transcriptId, name, thickStart, thickEnd, rgb,
                                start, stop, strand);
            TranscriptLines[count] = line; 
            count++;
        } 
        srcTranscriptData.SetExonCount(eCount);
    }
    else
        cerr << "ERROR: Unable to open transcripts file" << endl; //TODO: error handling needed
}
