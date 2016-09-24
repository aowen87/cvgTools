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


//FIXME: testing avl tree
/**
void AVLTest()
{
    TreeData *t1 = new TreeData(0, 5, '+', "supercontig12.5", "gene5", "");
    TreeData *t2 = new TreeData(6, 9, '+', "supercontig12.5", "gene1", "");
    TreeData *t3 = new TreeData(9, 12, '+', "supercontig12.5", "gene6", "");
    TreeData *t4 = new TreeData(20, 30, '+', "supercontig12.5", "gene5", "");
    TreeData *t5 = new TreeData(15, 25, '+', "supercontig12.5", "gene1", "");
    TreeData *t6 = new TreeData(12, 14, '+', "supercontig12.5", "gene4", "");
    TreeData *t7 = new TreeData(14, 16, '+', "supercontig12.5", "gene6", "");
    TreeData *t8 = new TreeData(9, 20, '-', "supercontig12.5", "gene3", "");
    TreeData *t9 = new TreeData(8, 33, '-', "supercontig12.5", "gene2", "");
    TreeData *t10 = new TreeData(8, 33, '-', "supercontig12.5", "gene9", "");

    //TreeData *d1 = new TreeData(8, 33, '-', "supercontig12.5", "gene5", "");
    TreeData *d2 = new TreeData(8, 33, '-', "supercontig12.5", "gene1", "");
   

    AVLTree tree('g');
    tree.Insert(t1);
    tree.Insert(t2);
    tree.Insert(t3);
    tree.Insert(t4);
    tree.Insert(t5);
    tree.Insert(t6);
    tree.Insert(t7);
    tree.Insert(t8);
    tree.Insert(t9);
    tree.Insert(t10);
    tree.InorderTraverse();
    tree.Delete(d2);
    cerr << "\n" << endl;
    tree.InorderTraverse();
}
**/


/***
* The main driver for cvgTools. 
***/
int main(int argc, char *argv[])
{

    //AVLTest();

    if (!argv[1])
    {
        cerr << "Usage: " << argv[0] << " <command> -<input_format> <input_file> " 
             << "<output_file> -t <transcripts_file> (if applicable)" << endl;
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
                //TODO: needs more rigorous testing 
                WindowWigWriter writer;
                reader.SetGenicWindows();
                writer.SetSinkWindowBlock(reader.GetWindowBlock()); 
                writer.Write(argv[4]); 
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


