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
#include "boost/program_options.hpp"
using std::string;
using std::cout;
using std::endl;
using std::cerr;
using std::vector;

static string FileName(string const &f);
static bool IsValidCommand(string command, vector<string> validCommands);
static const char *commands [] = {"ToWig", "NaturalWinAvg", "GeneAvg",
                            "GenicWindows", "BaseDiff", "WindowDiff"};


int main(int argc, char *argv[])
{
    vector<string> input;
    vector<string> options;
    vector<bedCovPerBaseReader> bedCovReaders;
    string transcriptsFile;
    string command;
    string in_type;
    vector<string> validCommands (commands, commands+6);

    try 
    {
        namespace po = boost::program_options;
        po::options_description desc("Options");
        desc.add_options()
            ("help", "dislpaly usage")
            ("input_type", po::value<string>(&in_type)->required(), "input file type")
            ("input", po::value<vector<string> >(&input)->required(), "input files")
            ("command", po::value<string>(&command)->required(), "command to be run")
            ("transcripts", po::value<string>(&transcriptsFile), "transcripts file")
            ("options", po::value<vector<string> >(&options), "additional options");

        po::variables_map vm;

        try
        {
            po::store(po::parse_command_line(argc, argv, desc), vm);

            if (vm.count("help"))
            {
                cerr << "Usage: " << argv[0] << " --command=<command> "
                     << "--input_type=<type> --input=<file_1> --out=<file_a> "
                     << "--options=<option_a> --transcripts=<t_file>" << endl;
                return 0;
            }

            po::notify(vm);
        }

        catch(po::error &e)
        {
            cerr << "ERROR: " << e.what() << endl;
            cerr << desc << endl;
            return 1;
        }

    }

    catch(std::exception &e)
    {
        cerr << "UNHANDLED ERROR: " << e.what() << endl;
        return 1;
    }

    if (IsValidCommand(command, validCommands))
    {
        int in_size = input.size();                                           
        if (in_type == "c")
        {
            bedCovReaders.reserve(in_size); //TODO: if command doesn't need 
                                           //       transcripts, just ignore them. 

            if (transcriptsFile != "\0")
            {
                for (int i = 0; i < in_size; ++i)    
                {
                    const char *file = input[i].c_str();
                    bedCovPerBaseReader reader(file, transcriptsFile);
                    bedCovReaders[i] = reader;
                }
            }

            else
            {
                for (int i = 0; i < in_size; ++i)    
                {
                    const char *file = input[i].c_str();
                    bedCovPerBaseReader reader(file);
                    bedCovReaders[i] = reader;
                }
            }

            if (command == "toWig")
            {
                for (int i = 0; i < in_size; +i)
                {
                    WigWriter writer;
                    writer.SetSinkData(bedCovReaders[i].GetData());
                    string out_f_str = FileName(input[i]) +/*i to string*/ + ".wig";
                    const char *out_f_pt = out_f_str.c_str();
                    writer.Write(out_f_pt);
                }            
            }
        }
    }

    else
    {
        cerr << "ERROR: Invalid command entered: " << command << endl;
        return 1;
    }

    return 0;
}


static bool IsValidCommand(string command, vector<string> validCommands)
{
    if (std::find(validCommands.begin(), validCommands.end(), command) 
        != validCommands.end())
        return true;
    return false;  
}


static string FileName(string const &f)
{
    string::size_type pos = f.find('.');
    if (pos != string::npos)
        return f.substr(0, pos);
    return f;
}

