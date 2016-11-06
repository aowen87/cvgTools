/****************************************************
* @author: Alister Maguire
* @version: 1.0 8/28/16
*****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <readers.h>
#include <reader.h>
#include <source.h>
#include <sink.h>
#include <writers.h>
#include <iostream>
#include <string.h>
#include <avl.h>
using std::string;
using std::cout;
using std::endl;
using std::cerr;


/***
* The main driver for cvgTools. 
***/
int main(int argc, char *argv[])
{

    if (!argv[1])
    {   //TODO: need to change the way args are handled (need room for multiple input and output)
        cerr << "Usage: " << argv[0] << " <command> -<input_format> <input_file> " 
             << "<output_file> -<option> <optional_files> " << endl;
        exit(EXIT_FAILURE);
    }
    string inputFormat = argv[2];
    string command     = argv[1];
    string option      = "";
    if (argv[5])
         option = argv[5];
        

    if (inputFormat == "-c")
    {
        if (option == "-t")
        {
            bedCovPerBaseReader reader(argv[3], argv[6]);
            reader.Execute();
        
            if (command == "toWig")
            {
                WigWriter writer;
                writer.SetSinkData(reader.GetData()); 
                writer.Write(argv[4]);
            }
 
            else if (command == "NaturalWinAvg")
            {
                WindowAvgWriter writer;
                reader.SetNaturalWindows();
                writer.SetSinkWindowBlock(reader.GetWindowBlock()); 
                writer.Write(argv[4]); 
            }
        
            else if (command == "GeneAvg")
            {
                WindowAvgWriter writer;
                reader.SetGenicWindows();
                writer.SetSinkWindowBlock(reader.GetWindowBlock()); 
                writer.Write(argv[4]); 
            }

            else if (command == "GenicWindows")
            { 
                WindowWigWriter writer;
                reader.SetGenicWindows();
                writer.SetSinkWindowBlock(reader.GetWindowBlock());
                writer.Write(argv[4]); 
            }

            else if (command == "BaseDiff")
            {
                cerr << "Diff doesn't currently support transcript files" << endl;
            }

            else if (command == "WindowDiff")
            { 
                //FIXME: testing
                bedCovPerBaseReader reader2(argv[4], argv[6]);
                reader2.Execute();

                WindowAvgWriter writer;
                reader.SetGenicWindows();
                reader2.SetGenicWindows();
                writer.SetSinkWindowBlock(reader.GetWindowBlock()); 
                writer.WindowDiff(reader2.GetWindowBlock());
                char o1[] = "WindowDiffs";
                writer.Write(o1); 
            }
   
   
            else
            {
                cout << "ERROR: invalid command provided" << endl;
                exit(EXIT_FAILURE);
            }
        }
        else 
        {
            bedCovPerBaseReader reader(argv[3]);
            reader.Execute();
            
            if (command == "toWig")
            {
                WigWriter writer;
                writer.SetSinkData(reader.GetData()); 
                writer.Write(argv[4]);
            }
 
            else if (command == "NaturalWinAvg")
            {
                WindowAvgWriter writer;
                reader.SetNaturalWindows();
                writer.SetSinkWindowBlock(reader.GetWindowBlock()); 
                writer.Write(argv[4]); 
            }
        
            else if (command == "GeneAvg")
            {
                cerr << "ERROR: transcripts are needed for this command" << endl;
                exit(EXIT_FAILURE);
            }

            else if (command == "GenicWindows")
            { 
                cerr << "ERROR: transcripts are needed for this command" << endl;
                exit(EXIT_FAILURE);
            }

            else if (command == "BaseDiff")
            { 
                //FIXME: testing
                bedCovPerBaseReader reader2(argv[4]);
                reader2.Execute();
                WigWriter w1;
                w1.SetSinkData(reader.GetData());
                w1.BaseDiff(reader2.GetData());
                char o1[] = "out1";
                w1.Write(o1);
            }

            else
            {
                cout << "ERROR: invalid command provided" << endl;
                exit(EXIT_FAILURE);
            }
        }
    }
    
    else if (inputFormat == "-b")
    {
        if (option == "-t")
        {
            bedReader reader(argv[3], argv[6]);
            reader.Execute();
            
            if (command == "toWig")
            {
                WigWriter writer;
                writer.SetSinkData(reader.GetData()); 
                writer.Write(argv[4]);
            }
 
            else if (command == "NaturalWinAvg")
            {
                //TODO: Currently unsuported for bed files. 
                //WindowAvgWriter writer;
                //reader.SetNaturalWindows();
                //writer.SetSinkWindowBlock(reader.GetWindowBlock()); 
                //writer.Write(argv[4]); 
                cerr << "ERROR: the NatualWinAvg command only accepts bed coverage" << 
                         "counts files at this time" << endl;
            }
        
            else if (command == "GeneAvg")
            {
                //TODO: Currently unsuported for bed files. 
                //WindowAvgWriter writer;
                //reader.SetGenicWindows();
                //writer.SetSinkWindowBlock(reader.GetWindowBlock()); 
                //writer.Write(argv[4]); 
                cerr << "ERROR: the GeneAvg command only accepts bed coverage" << 
                         "counts files at this time" << endl;
            }

            else if (command == "GenicWindows")
            { 
                //TODO: Currently unsuported for bed files. 
                //WindowWigWriter writer;
                //reader.SetGenicWindows();
                //writer.SetSinkWindowBlock(reader.GetWindowBlock()); 
                //writer.Write(argv[4]); 
                cerr << "ERROR: the GenicWindows command only accepts bed coverage" << 
                         "counts files at this time" << endl;
            }
   
            else
            {
                cout << "ERROR: invalid command provided" << endl;
                exit(EXIT_FAILURE);
            }
        }

        else 
        {
            bedReader reader(argv[3]);
            reader.Execute();
            if (command == "toWig")
            {
                WigWriter writer;
                writer.SetSinkData(reader.GetData()); 
                writer.Write(argv[4]);
            }
 
            else if (command == "NaturalWinAvg")
            {
                //TODO: Currently unsuported for bed files. 
                //WindowAvgWriter writer;
                //reader.SetNaturalWindows();
                //writer.SetSinkWindowBlock(reader.GetWindowBlock()); 
                //writer.Write(argv[4]); 
                cerr << "ERROR: the NatualWinAvg command only accepts bed coverage" << 
                         "counts files at this time" << endl;
            }
        
            else if (command == "GeneAvg")
            {
                cerr << "ERROR: transcripts are needed for this command" << endl;
                exit(EXIT_FAILURE);
            }

            else if (command == "GenicWindows")
            { 
                cerr << "ERROR: transcripts are needed for this command" << endl;
                exit(EXIT_FAILURE);
            }
   
            else
            {
                cout << "ERROR: invalid command provided" << endl;
                exit(EXIT_FAILURE);
            }
        }
    }
 
    else
    {
        cerr << "ERROR: invalid input file type." << endl;
        exit(EXIT_FAILURE);
    }

}


