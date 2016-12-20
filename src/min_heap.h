/****************************************************
*    @author: Alister Maguire
*    @version: 1.0 8/28/16
*****************************************************/
#ifndef MIN_HEAP_H
#define MIN_HEAP_H
#include <string>
#include <data.h>
using std::string;

#define MAX_SIZE 100000000

class MinHeap
{
  private:
    TranscriptLine **dataHeap;
    long    heapSize; 
    long    Parent(long idx);
    long    RightChild(long idx);
    long    LeftChild(long idx);
    void             Swap(long idx1, long idx2);
    void             UpHeapBubble(long idx);
    void             DownHeapBubble(long idx);
    void             SingleChildDownHeap(long parentIdx, 
                                         long childIdx);
    void             DoubleChildDownHeap(long parentIdx, 
                                         long leftIdx,
                                         long rightIdx);

  public:
                    MinHeap();
                   ~MinHeap();
    void            Insert(TranscriptLine *line);
    TranscriptLine *RemoveMin();
    bool            IsEmpty();
    void            DisplayHeap(); //For testing purposes    

};


#endif
