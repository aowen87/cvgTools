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


## Introduction

**cvgTools** was created as a collaborative research project at the University of Oregon 
to help with DNA analysis being conducted in the department of molecular biology. The 
primary goals of this project are as follows:

 * 1. Provide some basic functionality, mainly in analyzing coverage 
      over genes and genic features. 
 * 2. Provide a modular framework that can easily be extended upon
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



## Command Usage

 This section defines how to use each of the available commands and gives 
 basic examples of usage. 

## ToWig <a name="ToWig"></a>


## NaturalWinAvg


## GeneAvg


## GenicWindows


## WindowDiff


## PeakAvg


## BaseDiff









[1]: https://www.linkedin.com/in/alister-maguire-0a075991/
