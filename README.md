cvgTools 
========
#### version alpha 1

Authors and contact:
 * Alister Maguire
 * [linkedin][1]
 * alisterowen87@gmail.com

Advisors:
 * John Conery, Professor at the UO
 * Vince Bicocca, Postdoctoral Fellow at the UO


## Table of Contents

1. [**Introduction**](#Intro)
2. [**Installation**](#Install)
3. [**Basic Usage**](#BU)
4. [**Command Usage**](#command)
5. [**Extras**](#extras)


## Introduction <a name="Intro"></a>

**cvgTools** was created as a collaborative research project at the University of Oregon 
to help with DNA analysis being conducted in the department of molecular biology. The 
primary goals of this project are as follows:

 *  Provide some basic functionality, mainly in analyzing coverage 
    over genes and genic features. 
 *  Provide a modular framework that can easily be extended upon
    for future development. 

 **Note for the user**

 * It should be noted that the primary developer of cvgTools is a computer scientist with
   only a basic background in molecular biology. Regardless of the support provided by 
   faculty in handling molecular data, this tool should be used with scrutiny and tested
   extensively.  


## Installation

  **Dependencies**
   * C++
   * gcc version 5.4.0 or greater
   * boost (only boost/program\_options are used)

  **Steps to Installation**

 * 1. First, you must retrieve the project from github. It is recommended that you
      clone the repo, which requires a github account and allows you to retrieve updates
      to the project as they occur. However, if you do not wish to create a github account,
      you can also download the project as a zip file directly from the repo page. 

      For cloning, use the following command:
 
      ```
      git clone https://github.com/aowen87/cvgTools.git
      ```


 * 2. From within a terminal, cd into cvgTools/src/
      Once here, type the following command:

      ```
      make
      ```

 * 3. **for bash users**:
      Assuming no errors have occured in either of the previous steps, cd into the 
      test directory located at cvgTools/tests/ and type 

      ```
      bash runtests
      ```

      You should see some text of the form "test n passed" for n = 1, 2, 3, ...
      followed by "TESTS END". As long as you don't see any failures, you've had
      a successful install!


## Basic Usage <a name="BU"></a>

 **Overview**

 After building cvgTools, you should find an executable file named "cvgTools" within
 cvgTools/src/

 To run the program, simply type 

 ```
 ./cvgTools
 ```

 within a terminal. If you run this command without any options added, then you will 
 see an error message and a description regarding options for this tool. In general, 
 the tool is used as follows:

 ```
 ./cvgTools --option_1=alpha --option_2=beta ... --option_n=gamma
 ```

 where '...' represnts any number of acceptable options that one might want or need
 to run a particular command.  

 For a quick help guide to using this tool, you can type

 ```
 ./cvgTools --help
 ```

 **Available Options**

 ```
 --help                dislpaly usage
 --input_type arg      input file type
 --input arg           input files
 --out_path arg        optional path for output files
 --command arg         command to be run
 --transcripts arg     transcripts file
 --options arg         additional options
 ```

**Supported Input Type**

 * Bed files 
 * Bed coverage files (per base) **see below for important details** 


**Available Commands**

 * [ToWig](#ToWig)
 * [NaturalWinAvg](#NaturalWinAvg)
 * [GeneAvg](#GeneAvg)
 * [GenicWindows](#GenicWindows)
 * [WindowDiff](#WindowDiff)
 * [PeakAvg](#PeakAvg)
 * [BaseDiff](#BaseDiff)



## Command Usage <a name="command"></a>

 This section defines how to use each of the available commands and gives 
 basic examples of usage. 

 For starters, each command requires the following arguments:

 * --input/_type: the type of input file. Acceptable types are
     bed files, denoted as "b", and bed [coverage files](#bc_files), 
     denoted as "c". It is important to note, however, that most of the
     available commands only accept bed coverage files at the moment. 

 * --input: the path to the actual input file. 

 You also have the option of deciding which directory the output file 
 will be written to. By default, this file is written to the current
 directory, and will be named in the following manner:
 
     NameOfInputFile_COMMAND_count.txt

 To change the output path, use the following command:

 * --out/_path


* **ToWig:** <a name="ToWig"></a>

  ToWig is a basic command that allows conversion from bed files and bed coverage files
  to wig format. The command is run like so:

  ``
  ./cvgTools --command=ToWig --input_type=c --input=path/_to/_input/_file
  ``

  This is the one command that currently accepts both bed files and bed coverage files as
  input. 


* **NaturalWinAvg** <a name="NaturalWinAvg"></a>

* **GeneAvg** <a name="GeneAvg"></a>

* **GenicWindows** <a name="GenicWindows"></a>

* **WindowDiff** <a name="WindowDiff"></a>

* **PeakAvg** <a name="PeakAvg"></a>

* **BaseDiff** <a name="BaseDiff"></a>



##Extras <a name="extras"></a>



* **Bed Coverage Files:** <a name="bc_files"><a/>
  




[1]: https://www.linkedin.com/in/alister-maguire-0a075991/
