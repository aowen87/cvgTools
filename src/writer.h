/****************************************************
*    @author: Alister Maguire
*    @version: 1.0 8/28/16
*****************************************************/

#ifndef WRITER_H
#define WRITER_H
#include <sink.h>


/***
* @author: Alister Maguire
*
* A basic construct for a file writer. 
***/
class Writer : public Sink
{
  public:
    virtual void Write(const char *filename) = 0;
};

#endif
