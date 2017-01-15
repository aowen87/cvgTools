/****************************************************
*    @author: Alister Maguire
*    @version: 1.0 8/28/16
*****************************************************/

#ifndef DATA_H
#define DATA_H
#include <string>
#include <vector>
using std::string;
using std::vector;


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
    string       chrom;
    unsigned int start;
    unsigned int stop; 
    double       val; 
    double       diff;

  public:
                 DataLine(string _chrom, unsigned int _start, 
                          unsigned int _stop, int _val);
                 DataLine();
                ~DataLine();
    void         SetData(string _chrom, unsigned int _start, 
                         unsigned int _stop, int _val);
    void         SetBaseDiff(double d);
    double       GetBaseDiff();
    unsigned int GetStart();
    unsigned int GetStop();
    double       GetVal();
    string       GetChrom();
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
    bool      diffSet;
    double    valAverage;
    double    highVal;
    double    lowVal;
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
    bool      IsBaseDiffSet();     
    void      BaseDiffSet(bool set);
    void      SetData(unsigned long int size, DataLine *lines);
    void      SetValAvg(double avg);
    void      SetHighVal(double high);
    void      SetLowVal(double low);
    void      InitData(unsigned long int size);
    double    GetValAvg();
    double    GetHighVal();
    double    GetLowVal();
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
    string         title;
    unsigned int   start;
    unsigned int   stop;
    double         diff;//TODO: implement this

  public:
                   Window();
                   Window(unsigned long int size);
                   Window(string _title, unsigned long int size, int _start, 
                          int _stop, double _avgVal, DataLine *lines);
    void           SetTitle(string _title);
    void           SetAtts(string _title, int _start, int _stop, double _avg);
    void           SetWindowDiff(double d);
    double         GetDiff();
    string         GetTitle();
    unsigned int   GetStart();
    unsigned int   GetStop();
    void           SetAvgVal(double val);
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
    bool     diffSet;
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
    void      WindowDiffSet(bool set);//TODO: this name sucks
    bool      IsWindowDiffSet();
    Window    GetWindow(unsigned int idx);
    Window   *GetWindowPtr(unsigned int idx);
    Window   *GetWindows();
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
    string feature;
   
  protected:
    string       chrom;
    string       geneId;
    string       transcriptId;
    char         frame;
    unsigned int start;
    unsigned int stop;
    char         strand;
        
  public:
           TranscriptLine();
           TranscriptLine(string _chrom, string _geneId, string _transcriptId,  
                          string _feature, char _frame, int _start, int _stop, 
                          char _strand);
    void   DeepCopy(TranscriptLine line);
    void   SetChrom(string _chrom);
    void   SetGeneId(string id);
    void   SetTranscriptId(string transcriptId);
    void   SetStart(int _start);
    void   SetStop(int _stop);
    void   SetStrand(char _strand);
    void   SetThickEnd(string _feature);
    void   SetRGB(char _frame);
    string GetChrom();
    string GetGeneId();
    string GetTranscriptId();
    string GetFeature();
    int    GetStart();
    int    GetStop();
    char   GetStrand();
    char   GetFrame();
    
};


/***
* @author: Alister Maguire
*
* A collection of transcript lines to be interpreted
* as a collection of transcript/gene information. 
***/
class TranscriptData
{
  protected:
    TranscriptLine   *transcripts;
    unsigned long int dataSize;
    unsigned int      geneCount;

  public:
                    TranscriptData();
                    TranscriptData(unsigned long int size, TranscriptLine *data, 
                                   unsigned int gCount);
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
    void            SetGeneCount(unsigned int gCount);
    TranscriptLine *GetLines();
    void            InitData(unsigned long int size);
    TranscriptLine  GetTranscriptLine(unsigned int idx);
    unsigned int    GetGeneCount();
    unsigned long int GetDataSize();
};


/***
* @author: Alister Maguire
*
* A gene feature (codon, exon, etc.).
***/
class GeneFeature
{
  private:
    string name;
    unsigned int start;
    unsigned int stop;
    double       avgVal;
    double       diff; 

  public:
           GeneFeature();
           GeneFeature(string _name, unsigned int _start, 
                       unsigned int _stop);
    
          ~GeneFeature();
    string GetName();
    int    GetStart();
    int    GetStop();
    double GetValAvg();
    double GetDiff(); 
    void   SetValAvg(double avg);
    void   SetName(string _name);
    void   SetStart(unsigned int _start);
    void   SetStop(unsigned int _stop);
};


/***
* @author: Alister Maguire
*
* A gene representation. The gene inherits 
* the attributes of the TranscriptLine, but it
* also contains more complex feature representations. 
***/
class Gene : public TranscriptLine, public Data
{
  private:
    double diff;
    bool   diffSet;
    vector<GeneFeature> exons;
    vector<GeneFeature> startCodons;
    vector<GeneFeature> stopCodons;
    vector<GeneFeature> CDS;
    void                ConcatFeatureVectors(vector<GeneFeature> *base,
                                             vector<GeneFeature> add);

  public:
                        Gene();
                        Gene(string _chrom, string _geneId, string _transcriptId,  
                             char _frame, unsigned int _start, unsigned int _stop,
                             char _strand);
                        Gene(string _chrom, string _geneId, string _transcriptId,  
                             char _frame, unsigned int _start, unsigned int _stop, 
                             char _strand, vector<GeneFeature> ex, vector<GeneFeature> startC, 
                             vector<GeneFeature> stopC, vector<GeneFeature> _cds);
    void                GeneSwap(Gene &s);
    void                AddExon(GeneFeature e); 
    void                AddStartCodon(GeneFeature sc); 
    void                AddStopCodon(GeneFeature sc); 
    void                AddCDS(GeneFeature cds); 
    void                AddExonVector(vector<GeneFeature> eVec);
    void                AddStartCodonVector(vector<GeneFeature> scVec);
    void                AddStopCodonVector(vector<GeneFeature> scVec);
    void                AddCDSVector(vector<GeneFeature> cdsVec);
    void                DeepCopy(Gene g);
    bool                IsDiffSet();
    void                SetDiff(double d);
    double              GetDiff(); 
    vector<GeneFeature> *GetExons(); 
    vector<GeneFeature> *GetStartCodons(); 
    vector<GeneFeature> *GetStopCodons(); 
    vector<GeneFeature> *GetCDS();
};


/***
* @author: Alister Maguire
*
* A collection of genes. 
***/
class GeneData 
{
  private:
    Gene         *genes;  
    unsigned int  geneCount;
    bool          diffSet;

  public:
                 GeneData(); 
                 GeneData(Gene *_genes, unsigned int gCount);
                 GeneData(GeneData const &copy);
                ~GeneData();
    void         GeneDataSwap(GeneData &s);
                 GeneData &operator=(GeneData rhs)
                 {
                     rhs.GeneDataSwap(*this);
                     return *this;
                 } 
    void         SetGenes(unsigned int gCount,  Gene *_genes);
    void         SetGeneCount(unsigned int gCount);
    Gene        *GetGenes();
    void         InitGenes(unsigned int gCount);
    Gene         GetGene(unsigned int idx);
    unsigned int GetGeneCount();
    bool         IsDiffSet();
};

#endif
