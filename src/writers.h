/****************************************************
*    TODO: License
*    @author: Alister Maguire
*    @version: 1.0 8/28/16
*****************************************************/

#ifndef WRITERS_H
#define WRITERS_H
#include <writer.h>

/***
* @author: Alister Maguire
*
* A writer that outputs files in WIG format. 
***/
class WigWriter : public Writer
{
  public:
    void Write(char *filename);
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
    void Write(char *filename);
};


/***
* @author: Alister Maguire
*
* A writer that outputs windows in WIG format.
***/
class WindowWigWriter : public Writer
{
  public:
    void Write(char *filename);
};

#endif
