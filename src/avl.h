/****************************************************
*    @author: Alister Maguire
*    @version: 1.0 8/28/16
*****************************************************/
#ifndef AVL_H
#define AVL_H
#include <string>
#include <data.h>
using std::string;


class Node;


/***
*
***/
class Node
{
  private:
    Node           *left;
    Node           *right; 
    unsigned int    height;
    TranscriptLine *tData;

  public:
                    Node();
                    Node(TranscriptLine *d);
                    Node(Node const &copy);
                   ~Node();
    bool            ExpandDataStart(int _start);
    bool            ExpandDataStop(int _stop);
    void            SetHeight(unsigned int h);
    void            SetLeftChild(Node *l);
    void            SetRightChild(Node *r);
    void            SetData(TranscriptLine *d);
    TranscriptLine *GetData();
    Node           *GetLeftChild();
    Node           *GetRightChild();
    unsigned int    GetHeight();
};


/***
*
***/
class AVLTree
{
  private:
    Node           *root;    
    enum            BalanceCase { LEFTLEFT, RIGHTRIGHT, LEFTRIGHT, RIGHTLEFT }; 
    enum            SortTypes { Standard, Genic };
    enum            Equality { Lt, Gt, Eq };
    SortTypes       Sort;      
    Node           *DeletionSearch(Node *current, Node *target); 
    Node           *DeleteNode(Node *n);
    Node           *FindLeftmost(TranscriptLine *originData, Node *searchNode);
    Equality        StandardCompare(Node *n1, Node *n2);
    Equality        GenicCompare(Node *n1, Node *n2);
    Node           *DoInsertion(Node *current, Node *n);
    void            InorderTraversal(Node *current);
    void            PreorderTraversal(Node *current);
    bool            DoSearch(Node *current, Node *target);
    Node           *FindMin(Node *current);
    void            SetHeight(Node *current);
    Node           *CheckBalance(Node *n);
    Node           *Rebalance(Node *n, int diff);
    BalanceCase     DetermineBalanceCase(Node *n, int diff);
    Node           *RotateRight(Node *n); 
    Node           *RotateLeft(Node *n);
    Node           *CaseLeftRight(Node *n);
    Node           *CaseRightLeft(Node *n);
    unsigned int    GetNodeHeight(Node *n);
    void            DeleteTree(Node *n);

  public:
                    AVLTree();
                    AVLTree(char s);
                   ~AVLTree();
    void            Insert(TranscriptLine *d);
    void            Delete(TranscriptLine *d);
    bool            Search(TranscriptLine *d);
    void            InorderTraverse();
    void            PreorderTraverse();
    bool            IsEmpty();
    Node           *GetMin();
    TranscriptLine *RemoveMin();
};

#endif




