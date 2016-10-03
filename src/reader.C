/****************************************************
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
#include <avl.h>
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
unsigned long int Reader::SetDataSize(char *fname)//FIXME: change to GetLineCount
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
void Reader::SetSrcTranscriptDataSize()
{
    srcTranscriptData.InitData(SetDataSize(tfname));  
}
***/


/***
* @author: Alister Maguire
*
* Read gene information from a transcripts file, and 
* populate srcTranscriptData with this information.  
*
* IMPORTANT: All input files must be sorted beforehand. 
***/
//TODO: make capable of reading different sections of the transcript (other than 
//      genic regions)
void Reader::ReadTranscripts()
{
    ifstream inFile (tfname);
    if (inFile.is_open())
    {
        AVLTree geneTree('g');
        AVLTree posTree('s');
        unsigned int gCount = 0;
        string rawLine;
        string chrom;
        string geneId;
        string transcriptId;
        string name;
        string thickStart;
        string thickEnd;
        string scrap;
        string prevName = "";
        char   rgb;
        int    start;
        int    stop;
        char   strand;
        while (std::getline(inFile, rawLine))
        {
            std::istringstream iss(rawLine);
            if (!(iss >> chrom >> start >> stop >> name >> scrap >> strand >> thickStart 
               >> thickEnd >> rgb >> scrap >> geneId >> scrap >> transcriptId))
                break;
            geneId.erase(0, 1);
            geneId.erase(geneId.length()-2, 2);
            transcriptId.erase(0, 1);
            transcriptId.erase(transcriptId.length()-2, 2);
            TranscriptLine *line = new TranscriptLine(chrom, geneId, transcriptId, 
                                       name, thickStart, thickEnd, rgb, start, stop, strand);
            geneTree.Insert(line);
            prevName = name;
        } 

        while (!geneTree.IsEmpty())
        {
            posTree.Insert(geneTree.RemoveMin());  
            gCount++;
        }
        srcTranscriptData.InitData(gCount);
        TranscriptLine *TranscriptLines = srcTranscriptData.GetLines();
        TranscriptLine *treeLine;
        int tCount = 0;
        while (!posTree.IsEmpty())
        {
            treeLine = posTree.RemoveMin();
            TranscriptLines[tCount] = *treeLine;
            delete treeLine;
            tCount++;
        }

        srcTranscriptData.SetGeneCount(gCount);
    }
    else
        cerr << "ERROR: Unable to open transcripts file" << endl; //TODO: error handling needed
}
