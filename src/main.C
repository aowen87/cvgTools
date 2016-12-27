/****************************************************
* @author: Alister Maguire
* @version: 1.0 8/28/16
*****************************************************/
#include <sstream>
#include <iomanip>
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
    string out_path;
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
            ("out_path", po::value<string>(&out_path), "optional path for output files")
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

        if (*out_path.rbegin() != '/')
            out_path = out_path + "/";
        
        int in_size = input.size();                                           
        if (in_type == "c")
        {
            bedCovPerBaseReader **bedCovReaders = new bedCovPerBaseReader*[in_size];
            //TODO: if command doesn't need 
           //       transcripts, just ignore them.

            if (!transcriptsFile.empty())
            {
                //TODO: create a means for one source to 
                //      get its transcript data from another
                //      source that has already loaded it into
                //      memory. 
                for (int i = 0; i < in_size; ++i)    
                {
                    const char *file = input[i].c_str();
                    bedCovPerBaseReader *reader = new bedCovPerBaseReader(file, transcriptsFile); 
                    reader->Execute();
                    bedCovReaders[i] = reader;
                }
            }

            else
            {
                for (int i = 0; i < in_size; ++i)    
                {
                    const char *file = input[i].c_str();
                    bedCovPerBaseReader *reader = new bedCovPerBaseReader(file); 
                    reader->Execute(); 
                    bedCovReaders[i] = reader;
                }
            }

            if (command == "ToWig")
            {
                for (int i = 0; i < in_size; ++i)
                {
                    WigWriter writer;
                    writer.SetSinkData(bedCovReaders[i]->GetData());
                    string s_i = static_cast<std::ostringstream*>
                                ( &(std::ostringstream() << i) )->str();
                    string out_f_str = out_path + FileName(input[i]) + "_" + s_i  + ".wig";
                    const char *out_f_pt = out_f_str.c_str();
                    writer.Write(out_f_pt);
                }            
            }

            else if (command == "NautralWinAvg")
            {
                for (int i = 0; i < in_size; ++i)
                {
                    WindowAvgWriter writer;
                    bedCovReaders[i]->SetNaturalWindows();
                    writer.SetSinkWindowBlock(bedCovReaders[i]->GetWindowBlock());
                    string s_i = static_cast<std::ostringstream*>
                                ( &(std::ostringstream() << i) )->str();
                    string out_f_str = out_path + FileName(input[i]) + "_" + s_i  + ".txt";
                    const char *out_f_pt = out_f_str.c_str();
                    writer.Write(out_f_pt);
                }
            }

            else if (command == "GeneAvg")
            {
                for (int i = 0; i < in_size; ++i)
                {
                    WindowAvgWriter writer;
                    bedCovReaders[i]->SetGenicWindows();
                    writer.SetSinkWindowBlock(bedCovReaders[i]->GetWindowBlock());
                    string s_i = static_cast<std::ostringstream*>
                                ( &(std::ostringstream() << i) )->str();
                    string out_f_str = out_path + FileName(input[i]) + "_GA_" + s_i  + ".txt";
                    const char *out_f_pt = out_f_str.c_str();
                    writer.Write(out_f_pt);
                }
            }

            else if (command == "GenicWindows")
            {
                for (int i = 0; i < in_size; ++i)
                {
                    WindowWigWriter writer;
                    bedCovReaders[i]->SetGenicWindows();
                    writer.SetSinkWindowBlock(bedCovReaders[i]->GetWindowBlock());
                    string s_i = static_cast<std::ostringstream*>
                                ( &(std::ostringstream() << i) )->str();
                    string out_f_str = out_path + FileName(input[i]) + "_GW_" + s_i  + ".wig";
                    const char *out_f_pt = out_f_str.c_str();
                    writer.Write(out_f_pt);
                }
            }

            else if (command == "WindowDiff")
            {
                if (in_size > 2)
                {
                    cerr << "ERROR: WindowDiff currently only supports 2 " 
                         << "files at a time.\n" << endl;
                    cerr << "The first two will be compared, but the remaining "
                         << "will be ignored.\n" << endl;
                }
                
                WindowAvgWriter writer;
                bedCovReaders[0]->SetGenicWindows();
                bedCovReaders[1]->SetGenicWindows();
                writer.SetSinkWindowBlock(bedCovReaders[0]->GetWindowBlock());
                writer.WindowDiff(bedCovReaders[1]->GetWindowBlock());
              
                string out_f_str = out_path + FileName(input[0]) + "_WindowDiff.txt";
                const char *out_f_pt = out_f_str.c_str();
                writer.Write(out_f_pt);
            }

            else if (command == "BaseDiff")
            {
                //FIXME: testing 
                if (in_size > 2)
                {
                    cerr << "ERROR: BaseDiff currently only supports 2 " 
                         << "files at a time.\n" << endl;
                    cerr << "The first two will be compared, but the remaining "
                         << "will be ignored.\n" << endl;
                }

                WigWriter writer;
                writer.SetSinkData(bedCovReaders[0]->GetData());
                writer.BaseDiff(bedCovReaders[1]->GetData());
               
                string out_f_str = out_path + FileName(input[0]) + "_BaseDiff.wig";
                const char *out_f_pt = out_f_str.c_str();
                writer.Write(out_f_pt);
            }
            
            for (int i = 0; i < in_size; ++i)
                delete bedCovReaders[i];
            delete [] bedCovReaders;

        }

        else if (in_type == "b")
        {
            if (command == "ToWig")
            {
                for (int i = 0; i < in_size; ++i)
                {
                    const char *file = input[i].c_str();
                    bedReader reader(file);
                    reader.Execute();
                    WigWriter writer;
                    writer.SetSinkData(reader.GetData());
                    string s_i = static_cast<std::ostringstream*>
                                ( &(std::ostringstream() << i) )->str();
                    string out_f_str = out_path + FileName(input[i]) + "_" + s_i  + ".wig";
                    const char *out_f_pt = out_f_str.c_str();
                    writer.Write(out_f_pt);
                }            
            }
 
            else 
            {
                cerr << "ERROR: the only currently supported command for " 
                     << "bed files input it ToWig\n" << endl;
                return 1;
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

    if ((unsigned)f[0] == (unsigned)string::npos)
        return f;

    std::size_t start = f.find_last_of("/\\");
    string fname      = f.substr(start + 1); 
    std::size_t end   = fname.find_last_of('.'); 
    if (end == string::npos)
        return fname; 
    return fname.substr(0, end);
}

