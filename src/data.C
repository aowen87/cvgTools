/****************************************************
*    @author: Alister Maguire
*    @version: 1.0 8/28/16
*****************************************************/

#include <data.h>
#include <iostream>
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
DataLine::DataLine(string _chrom, int _start, int _stop, int _val)
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
    start = -1;
    stop  = -1;
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
void DataLine::SetData(string _chrom, int _start, int _stop, int _val)
{
    chrom    = _chrom;
    start    = _start;
    stop     = _stop;
    val      = _val;
}


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
int DataLine::GetStart() { return start; }


/***
* @author: Alister Maguire
*
*
***/
int DataLine::GetStop() { return stop; }


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
    valAverage = -1;
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
    dataSize = size;
    data = new DataLine[dataSize];
    data = _data;
}


/***
* @author: Alister Maguire
*
* Copy constructor for Data. 
* data is allocated new memory and given the data from
* that being copied from. data is deleted in the destructor. 
*
* @param: copy -> a Data object to be copied from. 
***/
Data::Data(Data const &copy)
{
    dataSize   = copy.dataSize;
    valAverage = copy.valAverage;
    data       = new DataLine[dataSize];
    std::copy(&copy.data[0], &copy.data[dataSize], data);//TODO: make my own copy?
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
    swap(this->dataSize, s.dataSize); //TODO: use my own swap?
    swap(this->valAverage, s.valAverage);
    swap(this->data, s.data);
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
    for (int i = 0; i < dataSize; i++)
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
        for (int i = 0; i < dataSize; i++)
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
* Default constructor for Window.
*
***/
Window::Window() 
{
    start      = -1;
    stop       = -1;
    valAverage = -1;
    title      = "EMPTY";
    data       = NULL;
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
    start      = -1;
    stop       = -1;
    valAverage = -1;
    title      = "EMPTY";
    data       = new DataLine[size];
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
    data       = NULL;
    SetData(size, lines);
    start      = _start;
    stop       = _stop;
    valAverage = _avgVal;
    title      = _title;
}


/***
* @author: Alister Maguire
*
* Set the data members for Window. 
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
int Window::GetStart() { return start; }


/***
* @author: Alister Maguire
*
* Get the stop position for the window. 
*
* @returns: stop -> the stop position of the window. 
***/
int Window::GetStop() { return stop; }


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
    std::copy(&copy.windows[0], &copy.windows[numWindows], windows);//TODO: make my own copy?
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
    swap(this->windows, s.windows); //FIXME: use my own swap?
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
    for (int i = 0; i < winCount; i++)
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
* Get a window from this WindowBlock. 
*
* @param: idx -> an index for the Window object to 
*             be retrieved from windows. 
* @returns: The window located at windows[idx] iff windows
*           is not NULL. Otherwise, return a scrap Window. 
***/
Window WindowBlock::GetWindow(int idx) 
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
Window *WindowBlock::GetWindowPtr(int idx) 
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
    name         = "";
    thickStart   = "";
    thickEnd     = "";
    rgb          = 'X';
    start        = -1;
    stop         = -1;
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
*         _name         -> name of the bed line. 
*         _thickStart   -> as defined at UCSC Genome Browser. 
*         _thickEnd     -> as defined at UCSC Genome Browser. 
*         _rgb          -> an RGB value. 
*         _start        -> starting position. 
*         _stop         -> stop position. 
*         _strand       -> strand direction. 
***/
TranscriptLine::TranscriptLine(string _chrom, string _geneId, string _transcriptId, string _name,
           string _thickStart, string _thickEnd, char _rgb, int _start, int _stop, char _strand)
{
    chrom        = _chrom;
    geneId       = _geneId;
    transcriptId = _transcriptId;
    name         = _name;
    thickStart   = _thickStart;
    thickEnd     = _thickEnd;
    rgb          = _rgb;
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
    name         = line.name;
    thickStart   = line.thickStart;
    thickEnd     = line.thickEnd;
    rgb          = line.rgb;
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
* Set the name of this transcript line. 
*
* @param: _name -> the name of this transcript line. 
***/
void TranscriptLine::SetName(string _name) { name = _name; }


/***
* @author: Alister Maguire
*
* Set the thickStart value as defined by UCSC Genome Browser. 
*
* @param: _thickStart -> the thickStart value for this transcript. 
***/
void TranscriptLine::SetThickStart(string _thickStart) { thickStart = _thickStart; }


/***
* @author: Alister Maguire
*
* Set the thickEnd value as defined by UCSC Genome Browser. 
*
* @param: _thickEnd -> the thickEnd value for this transcript. 
***/
void TranscriptLine::SetThickEnd(string _thickEnd) { thickEnd = _thickEnd; }


/***
* @author: Alister Maguire
*
* Set the rgb value for this transcript line. 
*
* @param _rgb -> the rgb value for this transcript line. 
***/
void TranscriptLine::SetRGB(char _rgb) { rgb = _rgb; }


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
* Get the name for this transcript line. 
*
* @returns: name -> the name for this transcript line. 
***/
string TranscriptLine::GetName() { return name; }


/***
* @author: Alister Maguire
*
* Get the thickStart value for this transcript line as
* defined by UCSC Genome Browser. 
*
* @returns thickStart
***/
string TranscriptLine::GetThickStart() { return thickStart; }


/***
* @author: Alister Maguire
*
* Get the thickEnd value for this transcript line as
* defined by UCSC Genome Browser. 
*
* @returns thickEnd
***/
string TranscriptLine::GetThickEnd() { return thickEnd; }


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
* Get the rgb value for this transcript line. 
* 
* @returns: rgb -> the rgb value for this transcript line. 
***/
char TranscriptLine::GetRGB() { return rgb; }


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
    std::copy(&copy.transcripts[0], &copy.transcripts[dataSize], transcripts);//FIXME: make my own copy?
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
    swap(this->transcripts, s.transcripts); //FIXME: use my own swap?
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
    for (int i = 0; i < size; i++)
    {
        TranscriptLine curLine = data[i];
        TranscriptLine newLine(curLine.GetChrom(), curLine.GetGeneId(), curLine.GetTranscriptId(),
                               curLine.GetName(), curLine.GetThickStart(), curLine.GetThickEnd(), 
                               curLine.GetRGB(), curLine.GetStart(), curLine.GetStop(), 
                               curLine.GetStrand());
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
TranscriptLine TranscriptData::GetTranscriptLine(int idx) 
{
    if (transcripts != NULL && idx < dataSize && idx >= 0)
        return transcripts[idx];
    if (transcripts == NULL)
        cerr << "transcripts is NULL" << endl;
    TranscriptLine trash;
    cerr << "Invalid attempt to get transcripts" << endl;
    return trash;
}
