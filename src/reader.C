/****************************************************
*    @author: Alister Maguire
*    @version: 1.0 8/28/16
*****************************************************/

#include <reader.h>
#include <sstream>
#include <data.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <avl.h>
#include <helpers.h>
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
void Reader::ReadTranscripts()
{
    ifstream inFile (tfname);
    if (inFile.is_open())
    {
        AVLTree geneTree('g');
        unsigned int gCount = 0;
        string rawLine;
        string chrom;
        string geneId;
        string transcriptId;
        string featureName;
        string scrap;
        char   frame;
        int    start;
        int    stop;
        char   strand;
        while (std::getline(inFile, rawLine))
        {
            std::istringstream iss(rawLine);
            if (!(iss >> chrom >> start >> stop >> scrap >> scrap >> strand >> scrap 
               >> featureName >> frame >> scrap >> geneId >> scrap >> transcriptId))
                break;
            geneId.erase(0, 1);
            geneId.erase(geneId.length()-2, 2);
            transcriptId.erase(0, 1);
            transcriptId.erase(transcriptId.length()-2, 2);
            Gene *gene = new Gene(chrom, geneId, transcriptId, 
                                  frame, start, stop, strand);
                 
            GeneFeature feature(featureName, start, stop); 
            if (featureName.compare("exon") == 0)
                gene->AddExon(feature);
            else if (featureName.compare("start_codon") == 0)
                gene->AddStartCodon(feature);
            else if (featureName.compare("stop_codon") == 0)
                gene->AddStopCodon(feature);
            else if (featureName.compare("cds") == 0)
                gene->AddCDS(feature);
            else
            {
                cerr << "ERROR: Unknown gene feature found! feature: "
                     << featureName << " line: "
                     << __LINE__ << endl;
                cerr << "Exiting program..." << endl;
                exit(EXIT_FAILURE);
            }
            geneTree.Insert(gene);
        } 

        gCount = geneTree.GetNumNodes();
        srcGeneData.InitGenes(gCount);
        Gene *genes = srcGeneData.GetGenes();
        Gene *treeGene;
        unsigned int tCount = 0;
        while (!geneTree.IsEmpty())
        {
            treeGene = geneTree.RemoveMin();
            genes[tCount] = *treeGene;
            delete treeGene;
            tCount++;
        }
        srcGeneData.SetGeneCount(gCount);
        HPR::GeneQuickSort(&genes, 0, gCount-1);
    }
    else
        cerr << "ERROR: Unable to open transcripts file" << endl; //TODO: error handling needed
}
