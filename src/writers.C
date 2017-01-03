/****************************************************
*    @author: Alister Maguire
*    @version: 1.0 8/28/16
*****************************************************/
#include <writers.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
using std::cout;
using std::cerr;
using std::endl;
using std::ofstream;



/***
* @author: Alister Maguire
*
* Create a WIG file from snkData. 
* @param: filename -> the name of the file to be 
*         written to. 
*
***/
void WigWriter::Write(const char *filename)
{
    ofstream outfile (filename);
    if (outfile.is_open())
    { 
        string curChrom;
        string prevChrom = "";
        int    curStart;
        int    curStop;
        double curVal;
        bool   diff     = snkData->IsBaseDiffSet();
        int    len      = snkData->GetDataSize();
        DataLine *lines = snkData->GetLines();   
        DataLine curLine;
        for (int i = 0; i < len; i++)
        {
            curLine  = lines[i];
            curChrom = curLine.GetChrom();
            curStart = curLine.GetStart();
            curStop  = curLine.GetStop();
            curVal   = curLine.GetVal();
            if (curChrom != prevChrom)
            {
                prevChrom = curChrom;
                outfile << "variableStep\t" << "chrom=" << curChrom << "\n";
            }    
           
            if (diff)
            {
                while ((curStop - curStart) > 0)
                {
                    outfile << curStart+1 << "\t" << curVal << "\t" << curLine.GetBaseDiff() << "\n";
                    curStart++;
                }
            }
 
            else
            {
                while ((curStop - curStart) > 0)
                {
                    outfile << curStart+1 << "\t" << curVal << "\n";
                    curStart++;
                }
            }
        }      
        outfile.close();
    }
    else
        cerr << "Unable to open file for writing" << endl; //TODO: error handling needed.
}


/***
* @author: Alister Maguire
* 
* Write a file containing window averages. 
* Format is as follows, and all values are tab delimited:
*  <title> <window start> <window end> <window average>
*
* @param: filename -> the name of the file to be written
*         to. 
*
***/
void WindowAvgWriter::Write(const char *filename)
{
    ofstream outfile (filename);
    if (outfile.is_open())
    { 
        unsigned long int len = snkWindowBlock->GetNumWindows();
        bool diff = snkWindowBlock->IsWindowDiffSet();
        Window  curWindow; 
        if (snkWindowBlock->GetWindows() == NULL)
            cerr << "ERROR: cannot write windows -> windows are NULL" << endl;

        else
        {
  
            if (diff)
            {
                for (unsigned int i = 0; i < len; i++)
                {
                    curWindow = snkWindowBlock->GetWindow(i);
                    outfile << std::setprecision(3) << curWindow.GetTitle() << "\t"
                            << curWindow.GetStart() << "\t" << curWindow.GetStop() 
                            << "\t" << curWindow.GetValAvg() << "\t" << curWindow.GetDiff() 
                            << "\n";
                }
            }

            else 
            {
                for (unsigned int i = 0; i < len; i++)
                {
                    curWindow = snkWindowBlock->GetWindow(i);
                    outfile << std::setprecision(3) << curWindow.GetTitle() << "\t"  
                            << curWindow.GetStart() << "\t" << curWindow.GetStop() 
                            << "\t" << curWindow.GetValAvg() << "\n";
                }
            }
        }      
        outfile.close();
    }
    else
        cerr << "Unable to open file for writing" << endl; //TODO: error handling needed.
}


/***
* @author: Alister Maguire
*
* Output windows to a file in wig format. 
*
* @param: filename -> the name of the file to be written
*         to. 
***/
void WindowWigWriter::Write(const char *filename)
{
    ofstream outfile (filename);
    if (outfile.is_open())
    { 
        unsigned long int numWin = snkWindowBlock->GetNumWindows();
        Window  curWindow; 
        Window *windows = snkWindowBlock->GetWindows();
        if (windows == NULL)
        {
            cerr << "ERROR: cannot write windows -> windows are NULL" << endl;
            exit(EXIT_FAILURE);
        }
        else
        {
            unsigned long int numLines;
            DataLine    *lines;
            DataLine     curLine;
            string       curChrom; 
            string       prevChrom;
            unsigned int curStart;
            unsigned int curStop;
            unsigned int prevStop = 0;
            double       curVal;
            prevChrom = "";

            for (unsigned int i = 0; i < numWin; i++)
            {
                curWindow = snkWindowBlock->GetWindow(i);
                lines     = curWindow.GetLines();
                numLines  = curWindow.GetDataSize();
                if (lines == NULL)
                {
                    cerr << "ERROR: cannot write windows -> NULL data found" << endl;
                    exit(EXIT_FAILURE);
                } 
                else
                {
                    for (unsigned int j = 0; j < numLines; j++)
                    {

                        curLine  = lines[j];
                        curChrom = curLine.GetChrom();
                        curStart = curLine.GetStart();
                        curStop  = curLine.GetStop();
                        curVal   = curLine.GetVal();

                        if (curChrom != prevChrom)
                        {
                            prevChrom = curChrom;
                            prevStop  = 0;
                            outfile << "variableStep\t" << "chrom=" << curChrom << "\n";
                        }    

                        while (curStart < prevStop)
                        {
                           curStart++;
                        }

                        if (curStart > curStop)
                        {
                            continue;
                        }

                        while ((curStop - curStart) > 0)
                        {
                            outfile << curStart+1 << "\t" << curVal << "\n";
                            curStart++;
                        }
                        prevStop = curStop;
                    }
                }
            }
        }      
        outfile.close();
    }
    else
        cerr << "Unable to open file for writing" << endl; //TODO: error handling needed.
}


/***
* @author: Alister Maguire
* 
* Write a file containing gene averages. 
* Format is as follows, and all values are tab delimited:
*  <gene ID> <gene start> <gene end> <gene average>
*
* @param: filename -> the name of the file to be written
*         to. 
*
***/
void GeneAvgWriter::Write(const char *filename)
{
    ofstream outfile (filename);
    if (outfile.is_open())
    { 
        unsigned int len = snkGeneData->GetGeneCount();
        Gene  curGene; 
        if (snkGeneData->GetGenes() == NULL)
            cerr << "ERROR: cannot write windows -> windows are NULL" << endl;

        else
        {
            if (snkGeneData->IsDiffSet())
            {
                for (unsigned int i = 0; i < len; i++)
                {
                    curGene = snkGeneData->GetGene(i);
                    outfile << std::setprecision(3) << curGene.GetGeneId() << "\t"  
                            << curGene.GetStart() << "\t" << curGene.GetStop() 
                            << "\t" << curGene.GetValAvg() << "\t" << curGene.GetDiff() 
                            << "\n";
                }
            }
            else 
            {
                for (unsigned int i = 0; i < len; i++)
                {
                    curGene = snkGeneData->GetGene(i);
                    outfile << std::setprecision(3) << curGene.GetGeneId() << "\t"  
                            << curGene.GetStart() << "\t" << curGene.GetStop() 
                            << "\t" << curGene.GetValAvg() << "\t" << "\n";
                }
            }
        }      
        outfile.close();
    }
    else
        cerr << "Unable to open file for writing" << endl; //TODO: error handling needed.
}


/***
* @author: Alister Maguire
*
* Parameterized constructor for GeneFeatureAvgWriter. A string
* input denoting the desired feature output is required. 
*
* @param: f -> a string of the feature desired. 
***/
GeneFeatureAvgWriter::GeneFeatureAvgWriter(std::string f)
{
    if (f == "exons")
        feature = Exons;
    else if (f == "start_codons")
        feature = Start_Codons;
    else if (f == "stop_codons")
        feature = Stop_Codons;
    else if (f == "cds")
        feature = CDS;
    else
    {
        cerr << "ERROR: Invalid feature entered. Line: " << __LINE__ << endl;
        cerr << "Exiting..." << endl;
        exit(EXIT_FAILURE);
    }
}


/***
* @author: Alister Maguire
* 
* Write a file containing gene feature averages. 
* Format is as follows, and all values are tab delimited:
*  <gene ID> <gene feature> <feature start> <feature end> <feature average>
*
* @param: filename -> the name of the file to be written
*         to. 
*
***/
void GeneFeatureAvgWriter::Write(const char *filename)
{
    ofstream outfile (filename);
    if (outfile.is_open())
    { 
        unsigned int len = snkGeneData->GetGeneCount();
        Gene  curGene; 
        if (snkGeneData->GetGenes() == NULL)
            cerr << "ERROR: cannot write windows -> windows are NULL" << endl;

        else
        {
            if (snkGeneData->IsDiffSet())
            {
                switch (feature)
                {
                    case (Exons):
                    {
                        for (unsigned int i = 0; i < len; ++i)
                        {
                            curGene = snkGeneData->GetGene(i);
                            vector<GeneFeature> exons = curGene.GetExons();
                            unsigned int fSize = exons.size();
                            for (unsigned int j = 0; j < fSize; ++j)
                            {
                               //FIXME: finish all of this 

                            }
                        }

                    }    


                }
/*
                for (unsigned int i = 0; i < len; i++)
                {
                    curGene = snkGeneData->GetGene(i);
                    outfile << std::setprecision(3) << curGene.GetGeneId() << "\t"  
                            << curGene.GetStart() << "\t" << curGene.GetStop() 
                            << "\t" << curGene.GetValAvg() << "\t" << curGene.GetDiff() 
                            << "\n";
                }
*/
            }
            else 
            {
                for (unsigned int i = 0; i < len; i++)
                {
                    curGene = snkGeneData->GetGene(i);
                    outfile << std::setprecision(3) << curGene.GetGeneId() << "\t"  
                            << curGene.GetStart() << "\t" << curGene.GetStop() 
                            << "\t" << curGene.GetValAvg() << "\t" << "\n";
                }
            }
        }      
        outfile.close();
    }
    else
        cerr << "Unable to open file for writing" << endl; //TODO: error handling needed.
}


/***
* @author: Alister Maguire
*
* Output genes to a file in wig format. 
*
* @param: filename -> the name of the file to be written
*         to. 
***/
//FIXME: need to remove overlaps from genic windows
//       may also need to show all zero values (not sure yet)
void GeneWigWriter::Write(const char *filename)
{
    ofstream outfile (filename);
    if (outfile.is_open())
    { 
        unsigned int numGenes = snkGeneData->GetGeneCount();
        Gene curGene;
        Gene *genes = snkGeneData->GetGenes();
        if (genes == NULL)
        {
            cerr << "ERROR: cannot write genes -> genes are NULL" << endl;
            exit(EXIT_FAILURE);
        }
        else
        {
            unsigned long int numLines;
            DataLine    *lines;
            DataLine     curLine;
            string       curChrom; 
            string       prevChrom;
            unsigned int curStart;
            unsigned int curStop;
            unsigned int prevStop = 0;
            double       curVal;
            prevChrom = "";

            for (unsigned int i = 0; i < numGenes; i++)
            {
                curGene = snkGeneData->GetGene(i);
                lines     = curGene.GetLines();
                numLines  = curGene.GetDataSize();
                if (lines == NULL)
                {
                    cerr << "ERROR: cannot write genes -> NULL data found" << endl;
                    exit(EXIT_FAILURE);
                } 
                else
                {
                    for (unsigned int j = 0; j < numLines; j++)
                    {

                        curLine  = lines[j];
                        curChrom = curLine.GetChrom();
                        curStart = curLine.GetStart();
                        curStop  = curLine.GetStop();
                        curVal   = curLine.GetVal();

                        if (curChrom != prevChrom)
                        {
                            prevChrom = curChrom;
                            prevStop  = 0;
                            outfile << "variableStep\t" << "chrom=" << curChrom << "\n";
                        }    

                        while (curStart < prevStop)
                        {
                           curStart++;
                        }

                        if (curStart > curStop)
                        {
                            continue;
                        }

                        while ((curStop - curStart) > 0)
                        {
                            outfile << curStart+1 << "\t" << curVal << "\n";
                            curStart++;
                        }
                        prevStop = curStop;
                    }
                }
            }
        }      
        outfile.close();
    }
    else
        cerr << "Unable to open file for writing" << endl; //TODO: error handling needed.
}

