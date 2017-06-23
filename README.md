cvgTools 
========
#### version alpha 1

Authors and contact:
 * Alister Maguire
 * [linkedin][1]
 * alisterowen87@gmail.com

Advisors:
 * John Conery, Professor at the University of Oregon
 * Vince Bicocca, Postdoctoral Fellow at the University of Oregon


## Table of Contents

1. [**Introduction**](#Intro)
2. [**Installation**](#Install)
3. [**Basic Usage**](#BU)
4. [**Command Usage**](#COMMAND)
5. [**Extras**](#extras)

<a name="Intro"></a>
## Introduction 

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

<a name="Install"></a>
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

<a name="BU"></a>
## Basic Usage 

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
 --input_type=arg      input file type
 --input=arg           input files
 --out_path=arg        optional path for output files
 --command=arg         command to be run
 --transcripts=arg     transcripts file
 --options=arg         additional options
 ```

**Supported Input Type**

 * Bed files 
 * Genome coverage files (per base) 
   **IMPORTANT: genome coverage files must be**
   **per base. See [below](#bcFiles) for instructions** 
   **on creating per-base genome coverage files**
                                   


**Available Commands**

 * [ToWig](#ToWig)
 * [NaturalWinAvg](#NaturalWinAvg)
 * [GeneAvg](#GeneAvg)
 * [GenicWindows](#GenicWindows)
 * [WindowDiff](#WindowDiff)
 * [PeakAvg](#PeakAvg)
 * [BaseDiff](#BaseDiff)


<a name="COMMAND"></a>
## Command Usage 

 This section defines how to use each of the available commands and gives 
 basic examples of usage. 

 For starters, each command requires the following arguments:

 * --input\_type: the type of input file. Acceptable types are
     bed files, denoted as "b", and genome [coverage files](#bcFiles), 
     denoted as "c". It is important to note, however, that most of the
     available commands only accept genome coverage files at the moment. 

 * --input: the path to the actual input file. 

 You also have the option of deciding which directory the output file 
 will be written to. By default, this file is written to the current
 directory, and will be named in the following manner:
 
     NameOfInputFile_COMMAND_n.txt

 Where n is an integer between 0 and the number of output files for the last
 command run. 
 
 To change the output path, use the **--out\_path** command:
  
### Commands:
  
<a name="ToWig"></a>
* **ToWig:** 

  ToWig is a basic command that allows conversion from bed files and genome coverage files
  to wig format. 

  **Required input**:
  * per-base genome coverage file or basic bed file.

  The command is run like so:

  ``
  ./cvgTools --command=ToWig --input_type=c --input=path_to_input_file
  ``

  This is the one command that currently accepts both bed files and genome coverage files as
  input. 
  
  
  
* **NaturalWinAvg:** <a name="NaturalWinAvg"></a>

  NaturalWinAvg is a command that finds the "natural windows" within a genome coverage file.
  A natural window is being define as a region of consecutive base pairs that meets the 
  following criteria:

    a.) All base pairs share the same chromosome  
    b.) All base pairs have a coverage score > 0.0

  For each natural window, an output will be created noting the range and mean value for
  this window. 

  For instance, if given the following input,

  ```
  chrom1  1435    8
  chrom1  1436    8
  chrom1  1437    9
  chrom1  1438    0
  chrom2  1987    4
  chrom2  1988    5
  chrom2  1989    8
  chrom3  4451    9
  chrom3  4452    1
  chrom3  4453    2
  ```

  the output will be like so:

  ```
  chrom1  1434    1437    8.33
  chrom2  1986    1989    5.67
  chrom3  4450    4453    4
  ```

  **Required input**:
  * per-base genome coverage file containing read counts. 

  The command is run like so:

  ```
  ./cvgTools --command=NaturalWinAvg --input_type=c --input=input_path --out_path=output_path
  ```

  Genome coverage files are the only supported input type for NaturalWinAvg.  
  
  
  
* **GeneAvg:** <a name="GeneAvg"></a>

  The GeneAvg command computes the mean coverage scores for each gene within a per-base genome
  coverage file. It also has the ability to compute the mean coverage scores for the following
  gene features:

    * exons
    * start codons
    * stop codons

  **Required input**:
  * per-base genome coverage file containing read counts. 
  * transcripts file in bed format

  The basic command is run like so:

  ```
  ./cvgTools --command=GeneAvg --input_type=c --input=input_path --out_path=output_path --transcripts=transcripts_path 
  ```

  The above command only computes the mean coverage scores for the genes, but you can easily
  compute the scores for any of the available features by adding in an options parameter. For
  instance, if you wanted to compute the mean scores for the exons, you would add the following
  option to your basic command above:

  ```
  --options=exons
  ```

  Below is an example of computing the mean scores for genes, exons, start codons, and 
  stop codons in one run:

  ```
  ./cvgTools --command=GeneAvg --input_type=c --input=input_path --out_path=output_path --transcripts=transcripts_path --options=exons --options=start_codons --options=stop_codons
  ```

  A single output file will be generated for the mean gene scores, which will be formated 
  as follows:

  ```
  Chromosome    start    stop    mean
  ```

  Additionally, a separate file will be generated for every feature mean that is requested. 
  For instance, if you asked for exons, start codons, and stop codons, then you would end 
  up with 4 files in total. 
  The feature mean files are formated as follows:

  ```
  Chromosome    feature    start    stop    mean
  ```

  The feature files will all have the feature name in their title for easy identification. 
  
  
  
<a name="GenicWindows"></a>
* **GenicWindows:** 

  As the name implies, the GenicWindows command outputs genic regions (windows) found within
  an input genome coverage file. 

  **Required input**:
  * per-base genome coverage file containing read counts. 
  * transcripts file in bed format

  The command is run like so:

  ```
  ./cvgTools --command=GenicWindows --input_type=c --input=input_path --out_path=output_path --transcripts=transcripts_path
  ```
  
  
  
 <a name="WindowDiff"></a>
* **WindowDiff:**
  
  **IMPORTANT**: the WindowDiff command has not been thoroughly tested. 

  The WindowDiff command is used to find the differences between two files, each
  containing the exact same windows (regions of defined base coverage averages) 
  with potentially different window values. 

  Documentation will be updated when testing is completed. 
  
  
<a name="PeakAvg"></a>
* **PeakAvg:** 

  **IMPORTANT**: the PeakAvg command has not been thoroughly tested nor has it been 
  updated to take in the variable peak limits from users. 

  Currently, the PeakAvg command will compute "peaks" within a per-base genome coverage
  file. These peaks are defined as regions that have a coverage value no less than 
  a specified peak limit. At the moment, the peak limit is defaulted to .5 for testing
  purposes. However, the command is built such that users can enter their own peak
  limits, but this feature has not yet been implemented into the interface. 

  
  Documentation will be updated when testing is completed. 
  
  
 <a name="BaseDiff"></a>
* **BaseDiff:**

  **IMPORTANT**: the BaseDiff command has not been thoroughly tested. Documentation
  will be updated when testing has been completed. 

  
  
<a name="extras"></a>
## Extras 


<a name="bcFiles"><a/>
* **Genome Coverage Files:** 

  All but one of the currently implemented commands requires a very specific type of 
  input file: the per-base genome coverage file. This file can be generated by using
  the genomecov command within bedTools. **IMPORTANT**: you must used the -d option
  in order to create a per-base coverage file. 
  Documentation covering the genomecov command and how to use bedTools can be found
  here: [http://bedtools.readthedocs.io/en/latest/content/tools/genomecov.html?highlight=coverage][2]
  




[1]: https://www.linkedin.com/in/alister-maguire-0a075991/
[2]: http://bedtools.readthedocs.io/en/latest/content/tools/genomecov.html?highlight=coverage
