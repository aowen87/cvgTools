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



int main(int argc, char *argv[])
{
    vector<string> input; 
    vector<string> output;
    vector<string> options;
    string transcriptsFile;
    string command;
    string in_type;
    

    try 
    {
        namespace po = boos::program_options;
        po::options_description desc("Options");
        desc.add_options()
            ("help", "dislpaly usage")
            ("input_type", po::value<string>(&in_type), "input file type")
            ("input", pos::value<vector<string> >(&input), "input files")
            ("command", pos::value<string>(&command), "command to be run")
            ("out", pos::value<vector<string> >(&output), "output file names")
            ("transcripts", pos::value<string>(&transcriptsFile), "transcripts file")
            ("options", pos::value<vector<string> >(&options), "additional options");

        po::variables_map vm;

        try
        {
            po::store(po::parse_command_line(argc, argv, desc), vm);

            if (vm.count("help")
            {
                cerr << "Usage: " << argv[0] << "--command=<command> "
                     << "--input_type=<type> --input=<file_1> --out=<file_a> "
                     << "--options=<option_a> --transcripts=<t_file>" << endl;
                return 0;
            }

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
        cerr << "Unhandled exception " << e.what() << endl;
        return 1;
    }


    return 0;
}

