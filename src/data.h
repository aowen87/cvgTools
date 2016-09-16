/****************************************************
*    @author: Alister Maguire
*    @version: 1.0 8/28/16
*****************************************************/

#ifndef DATA_H
#define DATA_H
#include <string>
using std::string;


/***
* @author: Alister Maguire
*
* A basic line of dna data containing the chromosome, 
* start position, stop position, and a value associated 
* with this region. 
***/
class DataLine
{
  private:
    string  chrom;
    int     start;
    int     stop; 
    double  val; 
  public:
           DataLine(string _chrom, int _start, int _stop, int _val);
           DataLine();
          ~DataLine();
    void   SetData(string _chrom, int _start, int _stop, int _val);
    int    GetStart();
    int    GetStop();
    double GetVal();
    string GetChrom();
};


/***
* @author: Alister Maguire
*
* A collection of dataLine objects. This often represents 
* a sequenced genome.   
***/
class Data
{
  protected:
    DataLine *data;
    double    valAverage;
    void      SetDataSize(unsigned long int size);
    void      ComputeValAvg();
    unsigned long int dataSize;
  public:
              Data(int size, DataLine *_data);
              Data();
              Data(Data const &copy);
    void      DataSwap(Data &s);
              Data &operator=(Data rhs)
              {
                  rhs.DataSwap(*this);
                  return *this;
              } 
             ~Data();
    DataLine *GetLines();
    void      SetData(unsigned long int size, DataLine *lines);
    void      InitData(unsigned long int size);
    double    GetValAvg();
    unsigned long int GetDataSize();
};


/***
* @author: Alister Maguire
*
* A window of data. The definition of a window can vary depending
* on the situation, but the basic facts are that the window has 
* a title, a start potition, and a stop position. 
***/
class Window : public Data
{
  private:
    string    title;
    int       start;//TODO: check to make sure these can hold enough data for the ranges required
    int       stop;
  public:
              Window();
              Window(unsigned long int size);
              Window(string _title, unsigned long int size, int _start, int _stop, double _avgVal, DataLine *lines);
    void      SetTitle(string _title);
    void      SetAtts(string _title, int _start, int _stop, double _avg);
    string    GetTitle();
    int       GetStart();
    int       GetStop();
    void      SetAvgVal(double val);
};


/***
* @author: Alister Maguire
*
* A collection (or block) of windows. 
***/
class WindowBlock
{
  private:
    Window  *windows;
    unsigned long int numWindows;
  public:
              WindowBlock();
             ~WindowBlock(); 
              WindowBlock(WindowBlock const &copy);
    void      WindowBlockSwap(WindowBlock &s);
              WindowBlock &operator=(WindowBlock rhs)
              {
                  rhs.WindowBlockSwap(*this);
                  return *this;
              } 
    void      SetWindows(unsigned long int winCount, Window *_windows);
    void      SetNumWindows(unsigned long int winCount);
    Window    GetWindow(int idx);
    Window   *GetWindowPtr(int idx);//FIXME: do I really want to do this?
    Window   *GetWindows();
    unsigned long int *GetNumWindowsPtr();
    unsigned long int  GetNumWindows();
};


/***
* @author: Alister Maguire
*
* A line of data containing transcript information. All values are 
* following the format specified by UCSC Genome Browser 
* (https://genome.ucsc.edu/FAQ/FAQformat.html#format1), and all data
* members are following the naming conventions specified at the above
* link.  
***/
class TranscriptLine
{
  private:
    string chrom;
    string geneId;
    string transcriptId;
    string name;
    string thickStart;
    string thickEnd;
    char   rgb;
    int    start;
    int    stop;
    char   strand;
        
  public:
           TranscriptLine();
           TranscriptLine(string _chrom, string _geneId, string _transcriptId, string _name,  
           string _thickStart, string _thickEnd, char _rgb, int _start, int _stop, char _strand);
    void   SetChrom(string _chrom);
    void   SetGeneId(string id);
    void   SetTranscriptId(string transcriptId);
    void   SetStart(int _start);
    void   SetStop(int _stop);
    void   SetStrand(char _strand);
    void   SetName(string _name);
    void   SetThickStart(string _thickStart);
    void   SetThickEnd(string _thickEnd);
    void   SetRGB(char _rgb);
    string GetChrom();
    string GetGeneId();
    string GetTranscriptId();
    string GetName();
    string GetThickStart();
    string GetThickEnd();
    int    GetStart();
    int    GetStop();
    char   GetStrand();
    char   GetRGB();
    
};


/***
* @author: Alister Maguire
*
* A collection of transcript lines to be interpreted
* as a collection of transcript/gene information. 
***/
class TranscriptData
{
  private:
    TranscriptLine   *transcripts;
    unsigned long int dataSize;
    unsigned int      exonCount;

  public:
                    TranscriptData();
                    TranscriptData(unsigned long int size, TranscriptLine *data, unsigned int eCount);
                   ~TranscriptData();
                    TranscriptData(TranscriptData const &copy);
    void            TranscriptDataSwap(TranscriptData &s);
                    TranscriptData &operator=(TranscriptData rhs)
                    {
                        rhs.TranscriptDataSwap(*this);
                        return *this;
                    } 
    void            SetData(unsigned long int size, TranscriptLine *data);
    void            SetDataSize(unsigned long int);
    void            SetExonCount(unsigned int eCount);
    TranscriptLine *GetLines();
    void            InitData(unsigned long int size);
    TranscriptLine  GetTranscriptLine(int idx);
    unsigned int    GetExonCount();
    unsigned long int GetDataSize();
};

#endif
