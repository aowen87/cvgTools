/****************************************************
*    @author: Alister Maguire
*    @version: 1.0 8/28/16
*****************************************************/
#ifndef AVL_H
#define AVL_H
#include <string>
using std::string;


class Node;


/***
*
***/
class TreeData
{
  private:
    int    start;
    int    stop;
    char   strand;
    string chrom;
    string geneId;
    string transcriptId;
  
  public:
           TreeData();
          ~TreeData();
           TreeData(int _start, int _stop, char _strand, string _chrom, string _geneId, string _transrciptId);
    void   SetStart(int _start);
    void   SetStop(int _stop);
    void   SetStrand(char _strand);
    void   SetChrom(string _chrom);
    void   SetGeneId(string _geneId);   
    void   SetTranscriptId(string _transcriptId);
    int    GetStart();
    int    GetStop();
    char   GetStrand();
    string GetChrom();
    string GetGeneId();
    string GetTranscriptId();
};


/***
*
***/
class Node
{
  private:
    Node        *left;
    Node        *right; 
    unsigned int height;
    TreeData    *tData;

  public:
                 Node(TreeData *d);
                ~Node();
    bool         ExpandDataStart(int _start);
    bool         ExpandDataStop(int _stop);
    TreeData     GetData();
    void         SetLeft(Node *l);
    void         SetRight(Node *r);
    Node        *GetLeftChild();
    Node        *GetRightChild();
    unsigned int GetHeight();
};


/***
*
***/
class AVLTree
{
  private:
    Node       *root;    
    enum        BalanceCase { LEFTLEFT, RIGHTRIGHT, LEFTRIGHT, RIGHTLEFT }; 
    enum        Sort { Standard, Genic };
    Node       *DeletionSearch(Node *current, Node *n); 
    Node       *DeleteNode(Node *n);
    Node       *FindLeftmost(TreeData *originKey, Node *searchNode);
    Node        DoInsertion(TreeData *current, Node *n);
    void        InorderTraversal(Node *current);
    void        PreorderTraversal(Node *current);
    bool        DoSearch(Node *current, Node *target);
    Node       *FindMin(Node *current);
    void        SetHeight(Node *current);
    Node       *CheckBalance(Node *n);
    Node       *Rebalance(Node *n, int diff);
    BalanceCase DetermineBalanceCase(Node *n, int diff);
    Node       *RotateRight(Node *n); 
    Node       *RotateLeft(Node *n);
    Node       *CaseLeftRight(Node *n);
    Node       *CaseRightLeft(Node *n);
    int        *GetNodeHeight(Node *n);

  public:
         AVLTree();
        ~AVLTree();
    void Insert(TreeData *d);
    void Delete(TreeData *d);
    bool Search(TreeData *d);
    void Traverse();
    Node GetMin();
};

#endif




