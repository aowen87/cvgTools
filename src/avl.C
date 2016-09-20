/****************************************************
*    @author: Alister Maguire
*    @version: 1.0 8/28/16
*****************************************************/

#include <avl.h>


/***
*
***/
Node::Node(TreeData *d)
{
    tData = d;//Should this be a deep copy?
}


/***
*
***/
bool Node::ExpandDataStart(int _start)
{
    if (_start < tData->GetStart())
    {
        tData->SetStart(_start);
        return true;
    }
    return false;
}


/***
*
***/
bool Node::ExpandDataStop(int _stop)
{
    if (_stop > tData->GetStop())
    {
        tData->SetStop(_stop);
        return true;
    }
    return false;
}
