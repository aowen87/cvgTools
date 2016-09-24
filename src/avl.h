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
    void   DeepCopy(TreeData t);
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
                 Node();
                 Node(TreeData *d);
                 Node(Node const &copy);
                ~Node();
    bool         ExpandDataStart(int _start);
    bool         ExpandDataStop(int _stop);
    void         SetHeight(unsigned int h);
    void         SetLeftChild(Node *l);
    void         SetRightChild(Node *r);
    void         SetData(TreeData *d);
    TreeData    *GetData();
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
    Node        *root;    
    enum         BalanceCase { LEFTLEFT, RIGHTRIGHT, LEFTRIGHT, RIGHTLEFT }; 
    enum         SortTypes { Standard, Genic };
    enum         Equality { Lt, Gt, Eq };
    SortTypes    Sort;      
    Node        *DeletionSearch(Node *current, Node *target); 
    Node        *DeleteNode(Node *n);
    Node        *FindLeftmost(TreeData *originData, Node *searchNode);
    Equality     StandardCompare(Node *n1, Node *n2);
    Equality     GenicCompare(Node *n1, Node *n2);
    Node        *DoInsertion(Node *current, Node *n);
    void         InorderTraversal(Node *current);
    void         PreorderTraversal(Node *current);
    bool         DoSearch(Node *current, Node *target);
    Node        *FindMin(Node *current);
    void         SetHeight(Node *current);
    Node        *CheckBalance(Node *n);
    Node        *Rebalance(Node *n, int diff);
    BalanceCase  DetermineBalanceCase(Node *n, int diff);
    Node        *RotateRight(Node *n); 
    Node        *RotateLeft(Node *n);
    Node        *CaseLeftRight(Node *n);
    Node        *CaseRightLeft(Node *n);
    unsigned int GetNodeHeight(Node *n);
    void         DeleteTree(Node *n);

  public:
          AVLTree();
          AVLTree(char s);
         ~AVLTree();
    void  Insert(TreeData *d);
    void  Delete(TreeData *d);
    bool  Search(TreeData *d);
    void  InorderTraverse();
    void  PreorderTraverse();
    Node *GetMin();
};

#endif




