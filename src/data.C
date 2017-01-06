/****************************************************
*    @author: Alister Maguire
*    @version: 1.0 8/28/16
*****************************************************/

#include <data.h>
#include <iostream>
#include <stdlib.h>
using std::cerr;
using std::endl;
using std::swap;

/***
* @author: Alister Maguire
*
* Paramaterized constructor for the DataLine.
* 
* @param: _chrom -> the chromosome name.
*         _start -> the chromosome start position. 
*         _stop  -> the chromosome stop position. 
*         _val   -> the value associated with this chromosome. 
***/
DataLine::DataLine(string _chrom, unsigned int _start, 
                   unsigned int _stop, int _val)
{
    chrom = _chrom;
    start = _start;
    stop  = _stop;
    val   = _val;
}


/***
* @author: Alister Maguire
*
* Default constructor for DataLine. 
***/
DataLine::DataLine()
{
    chrom = "";
    start = 0;
    stop  = 0;
    val   = -1;
}


/***
* @author: Alister Maguire
*
* Destructor for DataLine.
***/
DataLine::~DataLine()
{
}


/***
* @author: Alister Maguire
*
* Set all the members of DataLine.
*
* @param: _chrom -> the chromosome name.
*         _start -> the chromosome start position. 
*         _stop  -> the chromosome stop position. 
*         _val   -> the value associated with this chromosome. 
***/
void DataLine::SetData(string _chrom, unsigned int _start, 
                       unsigned int _stop, int _val)
{
    chrom    = _chrom;
    start    = _start;
    stop     = _stop;
    val      = _val;
}


/***
* @author: Alister Maguire
*
* Set the diff value. 
* 
* @param: d -> the input diff value. 
***/
void DataLine::SetBaseDiff(double d) { diff = d; }


/***
* @author: Alister Maguire
* 
* Get the diff value. 
*
* @returns: diff
***/
double DataLine::GetBaseDiff() {return diff; }


/***
* @author: Alister Maguire
*
* Get the chromosome from a line. 
*
* @returns: chrom -> the name of the chromosome. 
***/
string DataLine::GetChrom() { return chrom; }


/***
* @author: Alister Maguire
*
* Get the start position for a chromosome. 
* 
* @returns: start -> a chromosome start position. 
***/
unsigned int DataLine::GetStart() { return start; }


/***
* @author: Alister Maguire
*
* Get the stop position for a chromosome. 
*
* @returns: stop -> a chromosome stop position.
***/
unsigned int DataLine::GetStop() { return stop; }


/***
* @author: Alister Maguire
*
*
* Get the stop position for a chromosome. 
* 
* @returns: stop -> a chromosome start position. 
***/
double DataLine::GetVal() { return val; }


/***
* @author: Alister Maguire
*
* Default constructor for Data. 
***/
Data::Data()
{
    data       = NULL;
    dataSize   = 0.0;
    valAverage = 0;
    diffSet    = false;
}


/***
* @author: Alister Maguire
*
* Parameterized constructor for Data. Initialize data upon
* construction. data is deleted in the destructor. 
*
* @param: size  -> the max capacity for data (number of lines). 
*         _data -> the collection of data lines to be stored
*                  within data. 
***/
Data::Data(int size, DataLine *_data)
{
    if (data != NULL)
        delete [] data;
    dataSize   = size;
    data       = new DataLine[dataSize];
    data       = _data;
    valAverage = 0;
    diffSet    = false;
}


/***
* @author: Alister Maguire
*
* Copy constructor for Data. 
* data is allocated new memory and given the data from
* that being copied from. data is deleted in the destructor. 
* Note: diff values are not copied over.
*
* @param: copy -> a Data object to be copied from. 
***/
Data::Data(Data const &copy)
{
    dataSize   = copy.dataSize;
    valAverage = copy.valAverage;
    data       = new DataLine[dataSize];
    std::copy(&copy.data[0], &copy.data[dataSize], data);
    diffSet = false;
}


/***
* @author: Alister Maguire
*
* Swap all of the data from one Data object with 
* the data fro this Data object. 
*
* @param: s -> the address of a Data object. 
***/
void Data::DataSwap(Data &s)
{
    swap(this->dataSize, s.dataSize); 
    swap(this->valAverage, s.valAverage);
    DataLine *tmp  = s.data;
    s.data         = this->data;
    this->data     = tmp;
}


/***
* @author: Alister Maguire
*
* Destructor for Data. 
***/
Data::~Data()
{
    if (data != NULL)
        delete [] data;
}


/***
* @author: Alister Maguire
*
* Set the dataSize to the number of lines in the 
* data set. 
*
* @param: size -> the max capacity for data. 
***/
void Data::SetDataSize(unsigned long int size)
{
    dataSize = size;
}


/***
* @author: Alister Maguire
*
* Set lines as a collection of DataLines.  
* If lines has already been allocated memory, delete that
* memory and allocated new memory for the new DataLine objects. 
* All DataLine objects are deep copied; no further memory 
* management is needed. 
* 
* @param: size -> the number of DataLine objects to be copied
*             over. 
*         lines -> a collection of DataLine objects. 
***/
void Data::SetData(unsigned long int size, DataLine *lines)
{
    if (data != NULL)
        delete [] data;
    if (dataSize != size)
        dataSize = size;
    data = new DataLine[dataSize];
    for (unsigned int i = 0; i < dataSize; i++)
    {
        DataLine curLine = lines[i];
        DataLine newLine(curLine.GetChrom(), curLine.GetStart(), curLine.GetStop(), curLine.GetVal());
        data[i] = newLine;
    }
}


/***
* @author: Alister Maguire
*
* Set the valAverage.
* 
* @param: avg -> the value to set valAverage to. 
***/
void Data::SetValAvg(double avg)
{
    valAverage = avg;
}


/***
* @author: Alister Maguire
*
* Get the size of lines (number of DataLine objects within lines).
*
* @returns: dataSize -> the max capacity for data. 
***/
unsigned long int Data::GetDataSize() { return dataSize; }


/***
* @author: Alister Maguire
*
* Allocated memory for data based on a given size. 
* If data has already been allocated memory, this memory
* is first deleted. 
*
* @param: size -> the max capacity for data. 
***/
void Data::InitData(unsigned long int size)
{
    SetDataSize(size);
    if (data != NULL)
        delete [] data;
    data = new DataLine[dataSize];
}


/***
* @author: Alister Maguire
*
* Compute the average value within data => (sum of values)/(number of values) 
*
***/
void Data::ComputeValAvg()
{
    if (data != NULL)
    {
        double total    = 0;
        DataLine *lines = GetLines();
        for (unsigned int i = 0; i < dataSize; i++)
        {
            total += lines[i].GetVal();
        }
        valAverage = total/dataSize;
    }
}


/***
* @author: Alister Maguire
*
* Get the average value from data. If the value has not 
* yet been computed, call ComputeValAvg(). 
*
* @returns: valAverage -> the average value from data. 
***/
double Data::GetValAvg()
{
    if (valAverage < 0)
    {
        ComputeValAvg();
    }
    return valAverage;
}


/***
* @author: Alister Maguire
*
* Get a pointer to data. 
*
* @returns data -> a pointer to data. 
***/
DataLine *Data::GetLines() { return data; }


/***
* @author: Alister Maguire
*
* Check to see if the diff value has 
* been set within data. 
*
* @returns: diffSet
***/
bool Data::IsBaseDiffSet() { return diffSet; }


/***
* @author: Alister Maguire
*
* Set the diffSet. 
*
* @param: set -> true if diff has been set. 
*             False otherwise. 
***/
void Data::BaseDiffSet(bool set) { diffSet = set; }

/***
* @author: Alister Maguire
*
* Default constructor for Window.
*
***/
Window::Window() 
{
    start        = 0;
    stop         = 0;
    valAverage   = -1;
    title        = "";
    data         = NULL;
}


/***
* @author: Alister Maguire
*
* Parameterized constructor for Window. Allocated memory 
* for data. 
*
* @param: size -> the max capacity for data. 
*
***/
Window::Window(unsigned long int size) 
{
    start        = 0;
    stop         = 0;
    valAverage   = -1;
    title        = "";
    data         = new DataLine[size];
}


/***
* @author: Alister Maguire
*
* Parameterized constructor for Window. Set all members and initialize
* data. 
*
* @param: _title  -> window title.
*         size    -> the max capacity for data. 
*         _start  -> the start position of the window. 
*         _stop   -> the stop position of the window. 
*         _avgVal -> the average value for the window. 
*         *lines  -> a pointer to a collection of DataLine objects. 
*          
***/
Window::Window(string _title, unsigned long int size, int _start, int _stop, double _avgVal, DataLine *lines)
{
    data         = NULL;
    SetData(size, lines);
    start        = _start;
    stop         = _stop;
    valAverage   = _avgVal;
    title        = _title;
}


/***
* @author: Alister Maguire
*
* Set the basic data members for Window. 
*
* @param: _title  -> window title.
*         _start  -> the start position of the window. 
*         _stop   -> the stop position of the window. 
*         _avgVal -> the average value for the window. 
***/
void Window::SetAtts(string _title, int _start, int _stop, double _avg)
{
    title      = _title;
    start      = _start;
    stop       = _stop;
    valAverage = _avg;
}


/***
* @author: Alister Maguire
*
* Set the window title. 
*
* @param: _title -> window title. 
***/
void Window::SetTitle(string _title) { title = _title; }


/***
* @author: Alister Maguire
*
* Set the value of diff to d.
*
* @param: d -> a diff value.
***/
void Window::SetWindowDiff(double d) { diff = d; }


/***
* @author: Alister Maguire
*
* Get the diff value.
*
* @returns: diff -> diff value. 
***/
double Window::GetDiff() { return diff; }


/***
* @author: Alister Maguire
*
* Get the window title. 
* 
* @returns: title -> The window title. 
***/
string Window::GetTitle() { return title; }


/***
* @author: Alister Maguire
*
* Get the start position of the window. 
*
* @returns: start -> the start position of the window. 
***/
unsigned int Window::GetStart() { return start; }


/***
* @author: Alister Maguire
*
* Get the stop position for the window. 
*
* @returns: stop -> the stop position of the window. 
***/
unsigned int Window::GetStop() { return stop; }


/***
* @author: Alister Maguire
*
* Default WindowBlock constructor. 
*
***/
WindowBlock::WindowBlock() 
{
    windows    = NULL;
    numWindows = 0;
    diffSet    = false;
}


/***
* @author: Alister Maguire
*
* Copy constructor for WindowBlock. 
*
* @param: &copy -> the address of a WindowBlock object
*             to be copied over into the current block. 
***/
WindowBlock::WindowBlock(WindowBlock const &copy)
{
    numWindows = copy.numWindows;
    windows = new Window[numWindows];
    std::copy(&copy.windows[0], &copy.windows[numWindows], windows);
    diffSet = false;
}


/***
* @author: Alister Maguire
*
* Swap all of the members of one WindowBlock object
* with those of the current WindowBlock. 
*
* @param: &s -> The address of a WindowBlock to perform 
*             swap with. 
***/
void WindowBlock::WindowBlockSwap(WindowBlock &s)
{
    Window *tmp   = s.windows;
    s.windows     = this->windows;
    this->windows = tmp;
    swap(this->numWindows, s.numWindows);
}


/***
* @author: Alister Maguire
*
* Destructor for WindowBlock. 
***/
WindowBlock::~WindowBlock()
{
    if (windows != NULL)
    {
        delete [] windows;
    }
}


/***
* @author: Alister Maguire
*
* Populate windows. 
*
* @param: winCount -> the number of windows to be added
*             to windows. 
*         _windows -> the window objects to be (deep) copied
*             into windows. 
***/
void WindowBlock::SetWindows(unsigned long int winCount, Window *_windows)
{
    if (windows != NULL)
    {
        delete [] windows;
    }
    if (winCount != numWindows)
    {
        numWindows = winCount;
    }
    windows = new Window[winCount];
    for (unsigned int i = 0; i < winCount; i++)
    {
        Window curWin = _windows[i];
        Window newWindow(curWin.GetTitle(), curWin.GetDataSize(), curWin.GetStart(), curWin.GetStop(), curWin.GetValAvg(), curWin.GetLines());
        windows[i] = newWindow;
    }
}


/***
* @author: Alister Maguire
*
* Set the numWindows to equal the capacity of 
* windows. 
* 
* @param: winCount -> the capacity for the number of 
*             windows to be contained within windows. 
***/
void WindowBlock::SetNumWindows(unsigned long int winCount) { numWindows = winCount; }


/***
* @author: Alister Maguire
*
* Set diffSet to reflect whether or not the diff value
* has been set.
*
* @param: set -> bool: true if set, false otherwise. 
***/
void WindowBlock::WindowDiffSet(bool set) { diffSet = set; }


/***
* @author: Alister Maguire
*
* Get the value of diffSet.
*
* @returns: diffSet -> bool determining 
*            whether or not window diff has been
*            set. 
***/
bool WindowBlock::IsWindowDiffSet() { return diffSet; }


/***
* @author: Alister Maguire
*
* Get a window from this WindowBlock. 
*
* @param: idx -> an index for the Window object to 
*             be retrieved from windows. 
* @returns: The window located at windows[idx] iff windows
*           is not NULL. Otherwise, return a scrap Window. 
***/
Window WindowBlock::GetWindow(unsigned int idx) 
{
    if (windows != NULL && idx < numWindows && idx >= 0)
        return windows[idx];
    if (windows == NULL)
        cerr << "windows is NULL" << endl; 
    Window trash;
    cerr << "Invalid attempt to get window" << endl;
    return trash;
}


/***
* @author: Alister Maguire
*
* Get a pointer to particular window. 
*
* @param: idx -> an index for the Window object to 
*             be retrieved from windows. 
* @returns: A pointer to the window located at windows[idx]
*           iff windows is not NULL. Otherwise, return a 
*           pointer to a scrap window. 
***/
Window *WindowBlock::GetWindowPtr(unsigned int idx) 
{
    if (windows != NULL && idx < numWindows && idx >= 0)
        return &windows[idx];
    if (windows == NULL)
        cerr << "windows is NULL" << endl; 
    Window *trash;
    trash = NULL;
    cerr << "Invalid attempt to get window" << endl;
    return trash;
}

/***
* @author: Alister Maguire
*
* Get a pointer to windows. 
*
* @returns: windows -> a pointer to windows. 
***/
Window *WindowBlock::GetWindows() { return windows; }


/***
* @author: Alister Maguire
*
* Get the number of windows contained within windows (this is 
* actually capacity, which does not neccessarily reflect actual
* count. 
*
* @returns: numWindows -> the capacity for the number of windows 
*               within windows. 
***/
unsigned long int WindowBlock::GetNumWindows() { return numWindows; }


/***
* @author: Alister Maguire
*
* Get a pointer to numWindows. This is primarily used when 
* reading in data. It isn't ideal to have pointer access to
* this member, but it works for now. 
* 
* @returns: &numWindows -> the address to numWindows. 
unsigned long int *WindowBlock::GetNumWindowsPtr() { return &numWindows; }

***/

/***
* @author: Alister Maguire
*
* Default constructor for TranscriptLine. 
*
***/
TranscriptLine::TranscriptLine()
{
    chrom        = "";
    geneId       = "";
    transcriptId = "";
    feature      = "";
    frame        = 'X';
    start        = 0;
    stop         = 0;
    strand       = 'X';
}


/***
* @author: Alister Maguire
*
* Parameterized constructor for TranscriptLine. 
*
* @param: _chrom        -> a chromosome name for this line. 
*         _geneId       -> the gene id. 
*         _transcriptId -> the transcript ID.
*         _feature      -> gene feature
*         _frame        -> defined here: http://www.ensembl.org/info/website/upload/gff.html
*         _start        -> starting position. 
*         _stop         -> stop position. 
*         _strand       -> strand direction. 
***/
TranscriptLine::TranscriptLine(string _chrom, string _geneId, string _transcriptId, 
                               string _feature, char _frame, int _start, int _stop, char _strand)
{
    chrom        = _chrom;
    geneId       = _geneId;
    transcriptId = _transcriptId;
    feature      = _feature;
    frame        = _frame;
    start        = _start;
    stop         = _stop;
    strand       = _strand;
}


/***
* @author: Alister Maguire
*
* Deep copy of a TranscriptLine. 
*
* @param: line -> a transcript line to copy from. 
***/
void TranscriptLine::DeepCopy(TranscriptLine line)
{
    chrom        = line.chrom;
    geneId       = line.geneId;
    transcriptId = line.transcriptId;
    feature      = line.feature;
    frame        = line.frame;
    start        = line.start;
    stop         = line.stop;
    strand       = line.strand;
}


/***
* @author: Alister Maguire
*
* Set chrom to equal a chromosome name. 
* 
* @param: _chrom -> a chromosome name. 
***/
void TranscriptLine::SetChrom(string _chrom) { chrom = _chrom; }


/***
* @author: Alister Maguire
*
* Set geneId to equal a gene ID. 
* 
* @param: _geneId -> a gened ID.
***/
void TranscriptLine::SetGeneId(string _geneId) { geneId = _geneId; }


/***
* @author: Alister Maguire
*
* Set transcirptId. 
*
* @param: _transcriptId -> a transcript ID. 
***/
void TranscriptLine::SetTranscriptId(string _transcriptId) { transcriptId = _transcriptId; }


/***
* @author: Alister Maguire
*
* Set the start position.  
*
* @param: _start -> the start position for this transcript line. 
***/
void TranscriptLine::SetStart(int _start) { start = _start; }


/***
* @author: Alister Maguire
*
* Set the stop position. 
*
* @param: _stop -> the stop position for this transcript line.  
***/
void TranscriptLine::SetStop(int _stop) { stop = _stop; }


/***
* @author: Alister Maguire
*
* Set the strand direction (+ or -)
*
* @param: _strand -> the strand direction for this transcript line. 
***/
void TranscriptLine::SetStrand(char _strand) { strand = _strand; }


/***
* @author: Alister Maguire
*
* Set the feature value as defined by UCSC Genome Browser. 
*
* @param: _feature -> the feature value for this transcript. 
***/
void TranscriptLine::SetThickEnd(string _feature) { feature = _feature; }


/***
* @author: Alister Maguire
*
* Set the frame value for this transcript line. 
*
* @param _frame -> the frame value for this transcript line. 
***/
void TranscriptLine::SetRGB(char _frame) { frame = _frame; }


/***
* @author: Alister Maguire
*
* Get the chromosome name of this transcript line. 
*
* @returns: chrom -> the chromosome name for this transcript line. 
***/
string TranscriptLine::GetChrom() { return chrom; }


/***
* @author: Alister Maguire
*
* Get the gene Id for this transcript line. 
*
* @returns: geneId -> the gene ID.
***/
string TranscriptLine::GetGeneId() { return geneId; }


/***
* @author: Alister Maguire
*
* Get the transcript Id for this transcript line. 
*
* @returns: transcriptId -> the transcript ID.
***/
string TranscriptLine::GetTranscriptId() { return transcriptId; }


/***
* @author: Alister Maguire
*
* Get the feature value for this transcript line as
* defined by UCSC Genome Browser. 
*
* @returns feature
***/
string TranscriptLine::GetFeature() { return feature; }


/***
* @author: Alister Maguire
*
* Get the start position for this transcript line. 
*
* @returns: start -> the start position of this transcript line. 
***/
int TranscriptLine::GetStart() { return start; }


/***
* @author: Alister Maguire
*
* Get the stop position for this transcript line. 
*
* @returns: stop -> the stop position of this transcript line. 
***/
int TranscriptLine::GetStop() { return stop; }


/***
* @author: Alister Maguire
*
* Get the strand direction for this transcript line. 
*
* @returns: strand -> the strand direction. 
***/
char TranscriptLine::GetStrand() { return strand; }


/***
* @author: Alister Maguire
*
* Get the frame value for this transcript line. 
* 
* @returns: frame -> the frame value for this transcript line. 
***/
char TranscriptLine::GetFrame() { return frame; }


/***
* @author: Alister Maguire
*
* Default constructor for TranscriptData. 
***/
TranscriptData::TranscriptData()
{
    dataSize    = 0.0;
    geneCount   = 0;
    transcripts = NULL;
}


/***
* @author: Alister Maguire
*
* Parameterized constructor for TranscriptData. 
* Initialize data. Allocated memory is deleted in the
* destructor. 
*
* @param: size   -> the maximum capacity for data. 
*         *data  -> the data to be copied (deep) over into this
*             TranscriptData's data. 
*         gCount -> the number of genes in *data.  
***/
TranscriptData::TranscriptData(unsigned long int size, TranscriptLine *data, unsigned int gCount)
{
    geneCount = gCount;
    SetData(size, data);
}


/***
* @author: Alister Maguire
*
* Destructor for TranscriptData. 
***/
TranscriptData::~TranscriptData()
{
    if (transcripts != NULL)
        delete [] transcripts;
}


/***
* @author: Alister Maguire
*
* Copy constructor for TransriptData. 
*
* @param: &copy -> the address of another instance of 
*             TranscriptData. 
***/
TranscriptData::TranscriptData(TranscriptData const &copy)
{
    dataSize  = copy.dataSize;
    geneCount = copy.geneCount;
    transcripts = new TranscriptLine[dataSize];
    std::copy(&copy.transcripts[0], &copy.transcripts[dataSize], transcripts);
}


/***
* @author: Alister Maguire
*
* Swap all data members with another instance of 
* TranscriptData. 
*
* @param: &s -> an address to another instance of TranscriptData. 
***/
void TranscriptData::TranscriptDataSwap(TranscriptData &s)
{
    TranscriptLine *tmp = s.transcripts;
    s.transcripts       = this->transcripts;
    this->transcripts   = tmp;
    swap(this->dataSize, s.dataSize);
    swap(this->geneCount, s.geneCount);
}


/***
* @author: Alister Maguire
*
* Set dataSize to the max capacity for transcripts. 
*
* @param: size -> the max capacity for transcripts. 
***/
void TranscriptData::SetDataSize(unsigned long int size) { dataSize = size; }


/***
* @author: Alister Maguire
*
* Populate data with TranscriptLines. 
*
* @param: size  -> the max capacity for transcripts. 
*         *data -> the data to be copied (deep) into transcripts. 
***/
void TranscriptData::SetData(unsigned long int size, TranscriptLine *data)
{
    if (transcripts != NULL)
        delete [] transcripts;
    if (dataSize != size)
        dataSize = size;
    transcripts = new TranscriptLine[size];
    for (unsigned int i = 0; i < size; i++)
    {
        TranscriptLine curLine = data[i];
        TranscriptLine newLine(curLine.GetChrom(), curLine.GetGeneId(), curLine.GetTranscriptId(),
                               curLine.GetFeature(), curLine.GetFrame(), curLine.GetStart(), 
                               curLine.GetStop(), curLine.GetStrand());
        transcripts[i] = newLine;
    }
}


/***
* @author: Alister Maguire
*
* Set the gene count for this TranscriptData. 
*
* @param: gCount -> gene count. 
***/
void TranscriptData::SetGeneCount(unsigned int gCount) { geneCount = gCount; }


/***
* @author: Alister Maguire
*
* Get TranscriptLines.
*
* @returns: transcripts -> a collection of TranscriptLine objects. 
***/
TranscriptLine *TranscriptData::GetLines() { return transcripts; }


/***
* @author: Alister Maguire
*
* Get the max capacity for transcripts. 
*
* @returns: dataSize -> the max capacity for transcripts. 
***/
unsigned long int TranscriptData::GetDataSize() { return dataSize; }


/***
* @author: Alister Maguire
*
* Get the gene count for transcripts. 
*
* @returns: geneCount -> the number of gene found within transcripts. 
***/
unsigned int TranscriptData::GetGeneCount() { return geneCount; }


/***
* @author: Alister Maguire
*
* Allocate memory for transcripts. If transcripts has already
* been allocated memory, this memory is deleted before the new
* allocataion. 
* 
* @param: size -> the max capacity for transcripts. 
***/
void TranscriptData::InitData(unsigned long int size)
{
    SetDataSize(size);
    if (transcripts != NULL)
        delete [] transcripts;
    transcripts = new TranscriptLine[dataSize];
}


/***
* @author: Alister Maguire
*
* Get a TranscriptLine from transcripts. 
*
* @param: idx -> the index to a TranscriptLine located within
*             transcripts. 
* @returns: The TranscriptLine located at transcripts[idx] iff
*           transcripts is not NULL. Otherwise, a scrap TranscriptLine
*           is returned. 
***/
TranscriptLine TranscriptData::GetTranscriptLine(unsigned int idx) 
{
    if (transcripts != NULL && idx < dataSize && idx >= 0)
        return transcripts[idx];
    if (transcripts == NULL)
        cerr << "transcripts is NULL" << endl;
    TranscriptLine trash;
    cerr << "Invalid attempt to get transcripts" << endl;
    return trash;
}


/***
* @author: Alister Maguire
*
* Default constructor.
***/
GeneFeature::GeneFeature()
{
    name   = "";
    start  = 0;
    stop   = 0;
    avgVal = 0.0;
    diff   = 0.0;
}


/***
* @author: Alister Maguire
*
* Parameterized constructor; set values. 
*
* @param: name -> the gene name. 
*         start -> the start position. 
*         stop -> the stop position. 
***/
GeneFeature::GeneFeature(string _name, unsigned int _start, unsigned int _stop)
{
    name   = _name;
    start  = _start;
    stop   = _stop;
    avgVal = 0.0;
    diff   = 0.0;
}


/***
* @author: Alister Maguire
*
* Empty destructor. 
***/
GeneFeature::~GeneFeature() {}


/***
* @author: Alister Maguire
*
* Get the gene name. 
*
* @returns: name -> the name of the gene. 
***/
string GeneFeature::GetName() { return name; }


/***
* @author: Alister Maguire
*
* Get the start position for the gene. 
*
* @returns: start -> the gene's start position. 
***/
int GeneFeature::GetStart() { return start; }


/***
* @author: Alister Maguire
*
* Get the stop position for the gene. 
*
* @returns: the gene's stop position. 
***/
int GeneFeature::GetStop() { return stop; }


/***
* @author: Alister Maguire
*
* Get the diff value. 
*
* @returns: diff
***/
double GeneFeature::GetDiff() { return diff; }


/***
* @author: Alister Maguire
*
* Set the average value for this feature. 
*
* @param: avg -> the average value. 
***/
void GeneFeature::SetValAvg(double avg) { avgVal = avg; }


/***
* @author: Alister Maguire
*
* Get the average value for this feature. 
*
* @returns: avgVal
***/
double GeneFeature::GetValAvg() { return avgVal; }


/***
* @author: Alister Maguire
*
* Set the gene's name. 
*
* @param: _name -> the name of the gene. 
***/
void GeneFeature::SetName(string _name) { name = _name; }


/***
* @author: Alister Maguire
*
* Set the start position for the gene. 
*
* @param: _start -> the start position. 
***/
void GeneFeature::SetStart(unsigned int _start) { start = _start; }


/***
* @author: Alister Maguire
*
* Set the stop position for the gene. 
*
* @param: _stop -> the gene's stop position. 
***/
void GeneFeature::SetStop(unsigned int _stop) { stop = _stop; }


/***
* @author: Alister Maguire
*
* Default constructor. 
***/
Gene::Gene()
{
    chrom        = "";
    geneId       = "";
    transcriptId = "";
    frame        = 'X';
    start        = 0;
    stop         = 0;
    strand       = 'X';
    diffSet      = false;
    diff         = 0;
}



/***
* @author: Alister Maguire
*
* Parameterized constructor.
*
* @param: _chrom        -> a chromosome name for this line. 
*         _geneId       -> the gene id. 
*         _transcriptId -> the transcript ID.
*         _frame        -> defined here: http://www.ensembl.org/info/website/upload/gff.html
*         _start        -> starting position. 
*         _stop         -> stop position. 
*         _strand       -> strand direction. 
*         ex            -> the exons. 
***/
Gene::Gene(string _chrom, string _geneId, string _transcriptId,
           char _frame, unsigned int _start, unsigned int _stop, 
           char _strand)
{
    chrom        = _chrom;
    geneId       = _geneId;
    transcriptId = _transcriptId;
    frame        = _frame;
    start        = _start;
    stop         = _stop;
    strand       = _strand;
    diffSet      = false;
    diff         = 0;
}


/***
* @author: Alister Maguire
*
* Parameterized constructor.
*
* @param: _chrom        -> a chromosome name for this line. 
*         _geneId       -> the gene id. 
*         _transcriptId -> the transcript ID.
*         _frame        -> defined here: http://www.ensembl.org/info/website/upload/gff.html
*         _start        -> starting position. 
*         _stop         -> stop position. 
*         _strand       -> strand direction. 
*         ex            -> the exons. 
*         startC        -> the start codons. 
*         stopC         -> the stop codons. 
*         _cds          -> the cds features. 
***/
Gene::Gene(string _chrom, string _geneId, string _transcriptId,  
           char _frame, unsigned int _start, unsigned int _stop, 
           char _strand, std::vector<GeneFeature> ex, vector<GeneFeature> startC, 
           vector<GeneFeature> stopC, vector<GeneFeature> cds)
{
    chrom        = _chrom;
    geneId       = _geneId;
    transcriptId = _transcriptId;
    frame        = _frame;
    start        = _start;
    stop         = _stop;
    strand       = _strand;
    exons        = ex;
    startCodons  = startC;
    stopCodons   = stopC;
    CDS          = cds;
    diffSet      = false;
    diff         = 0;
}


/***
* @author: Alister Maguire
*
* Swap all elementes between this gene and an
* input gene. 
*
* @param: s -> a gene to swap values with. 
***/
void Gene::GeneSwap(Gene &s)
{
    swap(this->chrom, s.chrom);
    swap(this->geneId, s.geneId);
    swap(this->transcriptId, s.transcriptId);
    swap(this->frame, s.frame);
    swap(this->start, s.start);
    swap(this->stop, s.stop);
    swap(this->strand, s.strand);
    swap(this->exons, s.exons);
    swap(this->startCodons, s.startCodons);
    swap(this->stopCodons, s.stopCodons);
    swap(this->CDS, s.CDS);
}


/***
* @author: Alister Maguire
*
* Add an exon to the exon vector. 
*
* @param: e -> an exon GeneFeature. 
***/
void Gene::AddExon(GeneFeature e) { exons.push_back(e); }


/***
* @author: Alister Maguire
*
* Add a start codon to the start codon vector. 
*
* @param: sc -> a start codon GeneFeature. 
***/
void Gene::AddStartCodon(GeneFeature sc) { startCodons.push_back(sc); }


/***
* @author: Alister Maguire
*
* Add a stop codon to the stop codon vector. 
*
* @param: sc -> a stop codon GeneFeature. 
***/
void Gene::AddStopCodon(GeneFeature sc) { stopCodons.push_back(sc); }


/***
* @author: Alister Maguire
*
* Add a cds to the cds vector. 
*
* @param: cds -> a cds GeneFeature. 
***/
void Gene::AddCDS(GeneFeature cds) { CDS.push_back(cds); }


/***
* @author: Alister Maguire
*
* Add all elements from the GeneFeature vector "add"
* to the GeneFeature vector "base". 
*
* @param: base -> the base vector to have elements added.
*         add  -> the vector to retrieve the new elements 
*                 from. 
*
***/
void Gene::ConcatFeatureVectors(vector<GeneFeature> *base,
                                vector<GeneFeature> add)
{
    int size = add.size();
    for (int i = 0; i < size; ++i)
        base->push_back(add[i]);
}


/***
* @author: Alister Maguire
*
* Add all elements from a vector of GeneFeature
* objects to exons. 
*
* @param: eVec -> a vector of exons. 
***/
void Gene::AddExonVector(vector<GeneFeature> eVec)
{
    if (!eVec.empty())
        ConcatFeatureVectors(&exons, eVec);
}


/***
* @author: Alister Maguire
*
* Add all elements from a vector of GeneFeature
* objects to startCodons. 
*
* @param: scVec -> a vector of start codons. 
***/
void Gene::AddStartCodonVector(vector<GeneFeature> scVec)
{
    if (!scVec.empty())
        ConcatFeatureVectors(&startCodons, scVec);
}


/***
* @author: Alister Maguire
*
* Add all elements from a vector of GeneFeature
* objects to stopCodons. 
*
* @param: scVec -> a vector of stop codons. 
***/
void Gene::AddStopCodonVector(vector<GeneFeature> scVec)
{
    if (!scVec.empty())
        ConcatFeatureVectors(&stopCodons, scVec);
}


/***
* @author: Alister Maguire
*
* Add all elements from a vector of GeneFeature
* objects to CDS. 
*
* @param: cdsVec -> a vector of cds features. 
***/
void Gene::AddCDSVector(vector<GeneFeature> cdsVec)
{
    if (!cdsVec.empty())
        ConcatFeatureVectors(&CDS, cdsVec);
}


/***
* @author: Alister Maguire
*
* Deep copy of a Gene. 
*
* @param: g -> a gene to copy from. 
***/
void Gene::DeepCopy(Gene g)
{
    chrom        = g.chrom;
    geneId       = g.geneId;
    transcriptId = g.transcriptId;
    frame        = g.frame;
    start        = g.start;
    stop         = g.stop;
    strand       = g.strand;
    exons        = g.exons;
    startCodons  = g.startCodons;//FIXME: this is deep copy for vectors, right?
    stopCodons   = g.stopCodons;
    CDS          = g.CDS; 
}


/***
* @author: Alister Maguire
*
* Check to see if the diff value is set. 
*
* @returns: diffSet -> true if it's set. False otherwise. 
***/
bool Gene::IsDiffSet() { return diffSet; }


/***
* @author: Alister Maguire
*
* Set the diff value. 
*
* @param: d -> the diff value to set diff as. 
***/
void Gene::SetDiff(double d) { diff = d; }


/***
* @author: Alister Maguire
*
* Get the diff value. 
*
* @returns: diff -> the diff value. 
***/
double Gene::GetDiff() { return diff; }


/***
* @author: Alister Maguire
*
* Retrieve the exons. 
*
* @returns: exons 
***/
vector<GeneFeature> *Gene::GetExons() { return &exons; }


/***
* @author: Alister Maguire
*
* Retrieve the start codons. 
*
* @returns: startCodons 
***/
vector<GeneFeature> *Gene::GetStartCodons() { return &startCodons; }


/***
* @author: Alister Maguire
*
* Retrieve the stop codons. 
*
* @returns: stopCodons 
***/
vector<GeneFeature> *Gene::GetStopCodons() { return &stopCodons; }


/***
* @author: Alister Maguire
*
* Retrieve the cds features. 
*
* @returns: CDS 
***/
vector<GeneFeature> *Gene::GetCDS() { return &CDS; }


/***
* @author: Alister Maguire
*
* Empty constructor. 
***/
GeneData::GeneData() 
{
    geneCount = 0;
    genes     = NULL;
    diffSet   = false;
}


/***
* @author: Alister Maguire
*
* Parameterized constructor.
*
* @param: _genes -> the genes.
*         gCount -> the number of genes. 
***/
GeneData::GeneData(Gene *_genes, unsigned int gCount)
{
    geneCount = gCount;
    diffSet   = false;
    SetGenes(geneCount, _genes);
}


/***
* @author: Alister Maguire
*
* Destructor. 
***/
GeneData::~GeneData() 
{
    if (genes != NULL)
        delete [] genes;
}


/***
* @author: Alister Maguire
*
* Swap data members with another GeneData
* object. 
***/
void GeneData::GeneDataSwap(GeneData &s)
{
    cerr << "here" << endl;
    Gene *tmp   = s.genes;
    cerr << "past" << endl;
    s.genes     = this->genes;
    this->genes = tmp;
    swap(this->geneCount, s.geneCount);
}


/***
* @author: Alister Maguire
*
* Set the genes. 
*
* @param: gCount -> the number of genes. 
*         _genes -> the genes themselves. 
***/
void GeneData::SetGenes(unsigned int gCount, Gene *_genes)
{
    if (genes != NULL)
        delete [] genes;
    if (geneCount != gCount)
        geneCount = gCount;
    genes = new Gene[gCount];
    for (unsigned int i = 0; i < gCount; i++)
    {
        Gene curGene = genes[i];
        Gene newGene(curGene.GetChrom(), curGene.GetGeneId(), curGene.GetTranscriptId(),
                     curGene.GetFrame(), curGene.GetStart(), curGene.GetStop(), 
                     curGene.GetStrand(), *(curGene.GetExons()), *(curGene.GetStartCodons()), 
                     *(curGene.GetStopCodons()), *(curGene.GetCDS()));
        genes[i] = newGene;
    }

}


/***
* @author: Alister Maguire
*
* Set the gene count. 
*
* @param: gCount -> gene count. 
***/
void GeneData::SetGeneCount(unsigned int gCount) { geneCount = gCount; }


/***
* @author: Alister Maguire
*
* Retrieve the genes. 
*
* @returns: genes ->  the genes.
***/
Gene *GeneData::GetGenes() { return genes; }


/***
* @author: Alister Maguire
*
* Initialize the genes. 
*
* @param: gCount -> the number of genes. 
***/
void GeneData::InitGenes(unsigned int gCount)
{
    SetGeneCount(gCount);
    if (genes != NULL)
        delete [] genes;
    genes = new Gene[gCount];
}


/***
* @author: Alister Maguire
*
* Get a particular gene at a given index. 
*
* @param: idx -> the index to retrieve the 
*                target gene from. 
* @returns: if idx is a valid index and genes 
*           has been set, return the gene located 
*           at genes[idx]. Otherwise, return an
*           empty scrap gene. 
***/
Gene GeneData::GetGene(unsigned int idx)
{
    if (idx >= geneCount || idx < 0 || genes == NULL)
    {
        Gene scrap;
        return scrap;
    }    
    return genes[idx];
}


/***
* @author: Alister Maguire
*
* Retrieve the gene count. 
*
* @returns the gene count. 
***/
unsigned int GeneData::GetGeneCount() { return geneCount; }


/***
* @author: Alister Maguire
*
* Check to see if the diff values have 
* been set for the genes. 
*
* @returns diffSet -> true iff they've been set. 
***/
bool GeneData::IsDiffSet() { return diffSet; }

