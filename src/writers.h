/****************************************************
*    @author: Alister Maguire
*    @version: 1.0 8/28/16
*****************************************************/

#ifndef WRITERS_H
#define WRITERS_H
#include <writer.h>
#include <string>

enum Features {Exons, Start_Codons, Stop_Codons, CDS };

/***
* @author: Alister Maguire
*
* A writer that outputs files in WIG format. 
***/
class WigWriter : public Writer
{
  public:
    void Write(const char *filename);
};


/***
* @author: Alister Maguire
*
* A writer that outputs windows and their average
* values.//TODO extend this description 
***/
class WindowAvgWriter : public Writer
{
  public:
    void Write(const char *filename);
};


/***
* @author: Alister Maguire
*
* A writer that outputs windows in WIG format.
***/
class WindowWigWriter : public Writer
{
  public:
    void Write(const char *filename);
};


/***
* @author: Alister Maguire
*
* A writer for gene averages. 
***/
class GeneAvgWriter : public Writer
{
  public:
    void Write(const char *filename);
};



/***
* @author: Alister Maguire
*
* A writer for gene feature averages.
***/
class GeneFeatureAvgWriter : public Writer
{
  private:
    Features feature;

  public:
         GeneFeatureAvgWriter(std::string f);
    void Write(const char *filename);
};


/***
* @author: Alister Maguire
*
* A writer that outputs genes in WIG format.
***/
class GeneWigWriter : public Writer
{
  public:
    void Write(const char *filename);
};
#endif
