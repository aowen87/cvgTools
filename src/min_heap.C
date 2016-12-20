
#include <min_heap.h>
#include <helpers.h>
#include <iostream>
#include <stdlib.h>

using std::cerr;
using std::endl;

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
    if ( (heapSize + 1) == MAX_SIZE)
    {
        cerr << "ERROR: heap size limit exceeded! Exiting..\n" << endl;
        exit(EXIT_FAILURE);
    }

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
   
    TranscriptLine *child   = dataHeap[idx];
    TranscriptLine *parent = dataHeap[Parent(idx)];
    double childChromNum   = HPR::ExtractNumFromString(child->GetChrom());
    double parentChromNum  = HPR::ExtractNumFromString(parent->GetChrom());

    if (parentChromNum == childChromNum)
    {
        int childStart   = child->GetStart();
        int parentStart  = parent->GetStart();

        if (childStart == parentStart)
        {
            if (parent->GetStop() > child->GetStop())
            {
                Swap(Parent(idx), idx);
                UpHeapBubble(Parent(idx)); 
            } 
        }

        else if (parentStart > childStart)
        {
            Swap(Parent(idx), idx);
            UpHeapBubble(Parent(idx)); 
        }
    }

    else if (parentChromNum > childChromNum)
    {
        Swap(Parent(idx), idx);
        UpHeapBubble(Parent(idx)); 
    }

/*
    else if (dataHeap[Parent(idx)] > dataHeap[idx])
    {
        Swap(Parent(idx), idx);
        UpHeapBubble(Parent(idx)); 
    }    
*/
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
    TranscriptLine *left   = dataHeap[leftIdx];
    TranscriptLine *right  = dataHeap[rightIdx];
    TranscriptLine *parent = dataHeap[parentIdx];
    double leftChromNum    = HPR::ExtractNumFromString(left->GetChrom());
    double rightChromNum   = HPR::ExtractNumFromString(right->GetChrom());
    double parentChromNum  = HPR::ExtractNumFromString(parent->GetChrom());

    //check if parent is less than both children
    if ( (parentChromNum < leftChromNum) && 
         ((parentChromNum < rightChromNum)))
        return;

    else if ( (parentChromNum == leftChromNum) && 
              (parentChromNum == rightChromNum))
    {
        int rightStart  = right->GetStart();
        int leftStart   = left->GetStart();
        int parentStart = parent->GetStart();

        if ( (parent->GetStart() < leftStart) &&
             (parent->GetStart() < rightStart))
            return;

        //else if (leftStart == rightStart)
        else if ( (parentStart == leftStart) &&
                  (parentStart == rightStart))
        {
            int rightStop  = right->GetStop();
            int leftStop   = left->GetStop();
            int parentStop = parent->GetStop();

            if ( (parentStop < leftStop) &&
                 (parentStop < rightStop))
                return;            

            else if ( (parentStop == leftStop) &&
                      (parentStop == rightStop))
            {
                cerr << "equal input found in MinHeap. This may be an error..." <<
                        " line: " << __LINE__ << endl;
                return; 
            }

            else if (rightStop <= leftStop)
            {
                Swap(parentIdx, rightIdx);
                DownHeapBubble(rightIdx);
            }
 
            else if (leftStop < rightStop)
            {
                Swap(parentIdx, leftIdx);
                DownHeapBubble(leftIdx);
            }

            else
            {
                cerr << "ERROR: unknown heap condition; line " << 
                        __LINE__ << endl;
                exit(EXIT_FAILURE);
            }
        }

        else if (rightStart <= leftStart)
        {
            Swap(parentIdx, rightIdx);
            DownHeapBubble(rightIdx);
        }

        else if (leftStart < rightStart)
        {
            Swap(parentIdx, leftIdx);
            DownHeapBubble(leftIdx);
        }

        else
        {
            cerr << "ERROR: unknown heap condition; line " << 
                    __LINE__ << endl;
            exit(EXIT_FAILURE);
        }
    }

    else if (rightChromNum <= leftChromNum)
    {
        Swap(parentIdx, rightIdx);
        DownHeapBubble(rightIdx);
    }

    else if (leftChromNum < rightChromNum)
    {
        Swap(parentIdx, leftIdx);
        DownHeapBubble(leftIdx);
    }

    else
    {
        cerr << "ERROR: unknown heap condition; line " << 
                __LINE__ << endl;
        exit(EXIT_FAILURE);
    }
/*
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
    TranscriptLine *child  = dataHeap[childIdx];
    TranscriptLine *parent = dataHeap[parentIdx];
    double childChromNum   = HPR::ExtractNumFromString(child->GetChrom());
    double parentChromNum  = HPR::ExtractNumFromString(parent->GetChrom());

    if (parentChromNum == childChromNum)
    {
        int childStart   = child->GetStart();
        int parentStart  = parent->GetStart();

        if (childStart == parentStart)
        {
            if (parent->GetStop() > child->GetStop())
                Swap(parentIdx, childIdx);
        }

        else if (parentStart > childStart)
            Swap(parentIdx, childIdx);
    }

    else if (parentChromNum > childChromNum)
        Swap(parentIdx, childIdx);
    //if (dataHeap[parentIdx] > dataHeap[childIdx])
    //    Swap(parentIdx, childIdx);
}



