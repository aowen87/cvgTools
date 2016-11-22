
#include <min_heap.h>
#include <helpers.h>


/***
*
***/
MinHeap::MinHeap()
{
    dataHeap = new TranscriptLine*[MAX_SIZE];
    heapSize = 0;
}


/***
*
***/
MinHeap::~MinHeap()
{
    if (dataHeap != NULL)
        delete [] dataHeap;
}


/***
*
***/
void MinHeap::Insert(TranscriptLine *line)
{
    if (heapSize == 0)
    {
        dataHeap[0] = line;
        heapSize++;
    }

    else
    {
        dataHeap[heapSize] = line;
        UpHeapBubble(heapSize);
        heapSize++;
    }
}


/***
*
***/
TranscriptLine *MinHeap::RemoveMin()
{
    if (heapSize == 0)
        return NULL;
    
    TranscriptLine *min = dataHeap[0];
    dataHeap[0] = NULL;
    heapSize--;
    Swap(0, heapSize);
    DownHeapBubble(0);
    return min; 
}


/***
*
***/
bool MinHeap::IsEmpty()
{
    return (heapSize == 0) ? true : false;
}


/***
*
***/
long MinHeap::Parent(long idx)
{
    return (idx == 0) ? -1 : ( (idx-1)/2 );
}


/***
*
***/
long MinHeap::RightChild(long idx)
{
    long rightChild = 2*idx + 2;
    return (rightChild < heapSize) ? rightChild : -1;
}


/***
*
***/
long MinHeap::LeftChild(long idx)
{
    long leftChild = 2*idx + 1;
    return (leftChild < heapSize) ? leftChild : -1;
}


/***
*
***/
void MinHeap::Swap(long idx1, long idx2)
{
    TranscriptLine *tmp = dataHeap[idx1];
    dataHeap[idx1] = dataHeap[idx2];
    dataHeap[idx2] = tmp;
}



/***
*
***/
void MinHeap::UpHeapBubble(long idx)
{
    if (idx == 0)
        return;
    else if (dataHeap[Parent(idx)] > dataHeap[idx])
    {
        Swap(Parent(idx), idx);
        UpHeapBubble(Parent(idx)); 
    }    
}


/***
*
***/
void MinHeap::DownHeapBubble(long idx)
{
    long left  = LeftChild(idx);
    long right = RightChild(idx);    
    
    if (left < 0 && right < 0)
        return;
    else if (left < 0)
        SingleChildDownHeap(idx, right);
    else if (right < 0)
        SingleChildDownHeap(idx, left);
    else
        DoubleChildDownHeap(idx, left, right);
}


/***
*
***/
void MinHeap::DoubleChildDownHeap(long parentIdx, 
                                  long leftIdx, 
                                  long rightIdx)
{
// change this old comparison to work with 
// TranscriptLine objects.
/*
    long left  = dataHeap[leftIdx];
    long right = dataHeap[rightIdx];
    
    if (dataHeap[parentIdx] < left && dataHeap[parentIdx] < right)
        return;

    else if (right <= left)
    {
        Swap(parentIdx, rightIdx);
        DownHeapBubble(rightIdx);
    }

    else if (left < right)
    {
        Swap(parentIdx, leftIdx);
        DownHeapBubble(leftIdx);
    }
*/
}


/***
*
***/
void MinHeap::SingleChildDownHeap(long parentIdx, 
                                  long childIdx)
{
    if (dataHeap[parentIdx] > dataHeap[childIdx])
        Swap(parentIdx, childIdx);
}



