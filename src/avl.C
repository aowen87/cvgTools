/****************************************************
*    @author: Alister Maguire
*    @version: 1.0 8/28/16
*****************************************************/

#include <avl.h>
#include <helpers.h>
#include <iostream>
#include <stdlib.h>

using std::cerr;
using std::endl;


/***
*
***/
Node::Node()
{
    tData  = NULL;
    right  = NULL;
    left   = NULL;
    height = 0;
}


/***
*
***/
Node::Node(TreeData *d)
{
    tData  = d;
    right  = NULL;
    left   = NULL;
    height = 1;
}


/***
*
***/
Node::Node(Node const &n)
{
    left   = n.left;
    right  = n.right;
    height = n.height;
    tData  = new TreeData();
    tData->DeepCopy(*(n.tData));
}


/***
*
***/
Node::~Node() 
{
    if (tData != NULL)
        delete tData;
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


/***
*
***/
TreeData *Node::GetData() { return tData; }


/***
*
***/
void Node::SetHeight(unsigned int h)
{
    height = h;
}


/***
*
***/
void Node::SetLeftChild(Node *l) 
{
    //if (left != NULL)
    //    delete left;
    left = l;
}


/***
*
***/
void Node::SetRightChild(Node *r)
{
    //if (right != NULL)
    //    delete right;
    right = r;
}


/***
*
***/
void Node::SetData(TreeData *d)
{
    tData = d;
}


/***
*
***/
Node *Node::GetLeftChild() { return left; }


/***
*
***/
Node *Node::GetRightChild() { return right; }


/***
*
***/
unsigned int Node::GetHeight() { return height; }


/***
*
***/
TreeData::TreeData() 
{
    start        = -1;
    stop         = -1;
    strand       = 'X';
    chrom        = "";
    geneId       = "";
    transcriptId = "";
}


/***
*
***/
TreeData::TreeData(int _start, int _stop , char _strand, string _chrom, string _geneId, 
                   string _transcriptId)
{
    start        = _start;
    stop         = _stop;
    strand       = _strand;
    chrom        = _chrom;
    geneId       = _geneId;
    transcriptId = _transcriptId;
}


/***
*
***/
TreeData::~TreeData() {}


/***
*
***/
void TreeData::DeepCopy(TreeData t)
{
    start        = t.start;
    stop         = t.stop;
    strand       = t.strand;
    chrom        = t.chrom;
    geneId       = t.geneId;
    transcriptId = t.transcriptId;
}


/***
*
***/
void TreeData::SetStart(int _start)
{
    start = _start;
}


/***
*
***/
void TreeData::SetStop(int _stop)
{
    stop = _stop;
}


/***
*
***/
void TreeData::SetStrand(char _strand)
{
    strand = _strand;
}


/***
*
***/
void TreeData::SetChrom(string _chrom)
{
    chrom = _chrom;
}


/***
*
***/
void TreeData::SetGeneId(string _geneId)
{
    geneId = _geneId;
}


/***
*
***/
void TreeData::SetTranscriptId(string _transcriptId)
{
    transcriptId = _transcriptId;
}


/***
*
***/
int TreeData::GetStart() { return start; }


/***
*
***/
int TreeData::GetStop() { return stop; }


/***
*
***/
char TreeData::GetStrand() { return strand; }


/***
*
***/
string TreeData::GetChrom() { return chrom; }


/***
*
***/
string TreeData::GetGeneId() { return geneId; }


/***
*
***/
string TreeData::GetTranscriptId() { return transcriptId; }


/***
*
***/
AVLTree::AVLTree()
{
    root = NULL;
    Sort = Standard;
}



/***
*
***/
AVLTree::AVLTree(char s) 
{ 
    root = NULL; 
    if (s == 'g')
        Sort = Genic;
    else if (s == 's')
        Sort = Standard;
    else
    {
        cerr << "Inavlid sort option: " << s << endl;
        exit(EXIT_FAILURE); 
    }
}


/***
*
***/
AVLTree::~AVLTree() 
{
    if (root != NULL)
        DeleteTree(root);
}


/***
*
***/
void AVLTree::DeleteTree(Node *current)
{
    Node *left  = current->GetLeftChild();
    Node *right = current->GetRightChild();
     
    if (left != NULL)
        DeleteTree(left);
     
    if (right != NULL)
        DeleteTree(right);

    delete current;
}


/***
*
***/
void AVLTree::Insert(TreeData *d)
{
    Node *n = new Node(d);
    root    = CheckBalance(DoInsertion(root, n));
    delete n;
}


/***
*
***/
void AVLTree::Delete(TreeData *d)
{
    Node *n = new Node(d);
    root    = DeletionSearch(root, n);
    delete n;
}


/***
*
***/
bool AVLTree::Search(TreeData *d)
{
    Node *n    = new Node(d);
    bool found = DoSearch(root, n);
    delete n;
    return found;    
}


/***
*
***/
void AVLTree::InorderTraverse()
{
    if (root != NULL)
    {
        InorderTraversal(root);
        return;
    }
    
    cerr << "Tree is empty" << endl;
}


/***
*
***/
void AVLTree::PreorderTraverse()
{
    if (root != NULL)
    {
        PreorderTraversal(root);
        return;
    }
    
    cerr << "Tree is empty" << endl;
}


/***
*
***/
Node *AVLTree::GetMin()
{
    if (root == NULL)
    {
        Node *scrap = NULL;
        return scrap;
    }
    return FindMin(root);
}


/***
*
***/
Node *AVLTree::DeletionSearch(Node *current, Node *target)
{
    string targetId = target->GetData()->GetGeneId();
    string curId    = current->GetData()->GetGeneId();

    if (current == NULL)
    {
        cerr << "Target node could not be deleted -> DNE in this tree." << endl;
        
    } 

    else if (targetId == curId)
    {
        return CheckBalance(DeleteNode(current));
    }

    else if (targetId < curId)
    {
        current->SetLeftChild(DeletionSearch(current->GetLeftChild(), target));
        SetHeight(current);
    }

    else if (targetId > curId)
    {
        current->SetRightChild(DeletionSearch(current->GetRightChild(), target));
        SetHeight(current);
    }

    return CheckBalance(current);
}


/***
*
***/
Node *AVLTree::DeleteNode(Node *n)
{
    Node *left  = n->GetLeftChild();
    Node *right = n->GetRightChild();
    Node *scrap = NULL;
    
    if (left == NULL && right == NULL)
    {
        delete n;
        return scrap;//we just need to return a null valued Node
    }

    else if (left == NULL || right == NULL)
    {
        if (right == NULL)
        {
            delete n;
            return left;
        }
 
        if (left == NULL)
        {
            delete n;
            return right;
        }
    }
   
    TreeData *nData = n->GetData(); 
    Node *origin    = new Node(nData);
    Node *leftmost  = FindLeftmost(nData, n->GetRightChild());
    n->SetData(leftmost->GetData());
    n->SetRightChild(DeletionSearch(n->GetRightChild(), origin));
    SetHeight(n->GetRightChild());
    SetHeight(n);     
}


/***
*
***/
Node *AVLTree::FindLeftmost(TreeData *originData, Node *searchNode)
{
    Node *leftmost;
    while (searchNode->GetLeftChild() != NULL)
    {
        searchNode = searchNode->GetLeftChild();
    }
    leftmost = new Node(searchNode->GetData());
    searchNode->SetData(originData);
    return leftmost; 
}


/***
*
***/
AVLTree::Equality AVLTree::StandardCompare(Node *n1, Node *n2)
{
    TreeData *n1Data  = n1->GetData();
    TreeData *n2Data  = n2->GetData();
    double n1ChromNum = HPR::ExtractNumFromString(n1Data->GetChrom());    
    double n2ChromNum = HPR::ExtractNumFromString(n2Data->GetChrom());
    AVLTree::Equality e;
    
    if (n1ChromNum == n2ChromNum)
    {
        int n1Start = n1Data->GetStart();
        int n2Start = n2Data->GetStart();

        if (n1Start == n2Start)
        {
            int n1Stop = n1Data->GetStop();
            int n2Stop = n2Data->GetStop();
            
            if (n1Stop == n2Stop)
            {
                e = Eq;
                return e;                         
            }

            else if (n1Stop < n2Stop)
            {
                e = Lt;
                return e;
            }

            e = Gt;
            return e;
        }
    
        else if (n1Start < n2Start)
        {
            e = Lt;
            return e;
        }

        e = Gt;
        return e;
    }

    else if (n1ChromNum < n2ChromNum)
    {
        e = Lt;
        return Lt;
    }

    e = Gt;
    return e;
}


/***
*
***/
AVLTree::Equality AVLTree::GenicCompare(Node *n1, Node *n2)
{
    TreeData *n1Data = n1->GetData();
    TreeData *n2Data = n2->GetData();
    string n1GeneId  = n1Data->GetGeneId();
    string n2GeneId  = n2Data->GetGeneId();
    AVLTree::Equality e;  

    if (n1GeneId == n2GeneId)
    {
        e = Eq;
        return e;
    }

    else if (n1GeneId < n2GeneId)
    {
        e = Lt;
        return e;
    }

    e = Gt;
    return e;
}


/***
*
***/
Node *AVLTree::DoInsertion(Node *current, Node *n)
{
    
    if (current == NULL)
    {
        current = new Node(*n); 
        return CheckBalance(current);
    }

    AVLTree::Equality e;

    switch (Sort)
    {
        case Standard: 
            e = StandardCompare(n, current);
            switch (e)
            {
                case Eq:
                    current->SetLeftChild(DoInsertion(current->GetLeftChild(), n));
                    SetHeight(current);
                    break;
                case Lt:
                    current->SetLeftChild(DoInsertion(current->GetLeftChild(), n));
                    SetHeight(current);
                    break;
                case Gt:
                    current->SetRightChild(DoInsertion(current->GetRightChild(), n));
                    SetHeight(current);
                    break;
                default:
                    cerr << "ERROR: equality case not met. Line: " << __LINE__ << endl;
                    break;
            }
            break;

        case Genic:
            e = GenicCompare(n, current);
            switch (e)
            {
                case Eq:  //Merge the genes
                    current->ExpandDataStart(n->GetData()->GetStart());
                    current->ExpandDataStop(n->GetData()->GetStop());
                    break;
                case Lt:
                    current->SetLeftChild(DoInsertion(current->GetLeftChild(), n));
                    SetHeight(current);
                    break;
                case Gt:
                    current->SetRightChild(DoInsertion(current->GetRightChild(), n));
                    SetHeight(current);
                    break;
                default:
                    cerr << "ERROR: equality case not met. Line: " << __LINE__ << endl;
                    break;
            }            
    }
    Node *outNode = new Node(*current);
    delete current;
    return CheckBalance(outNode);
}


/***
*
***/
void AVLTree::InorderTraversal(Node *current)
{
    Node *left      = current->GetLeftChild();
    Node *right     = current->GetRightChild();
    TreeData *tData = current->GetData();
    
    if (left != NULL)
    {
        InorderTraversal(left);
    }

    cerr << tData->GetChrom() << "\t" << tData->GetStart() << "\t" << tData->GetStop()
         << "\t" << tData->GetGeneId() << "\t" << endl;

    if (right != NULL)
    {
        InorderTraversal(right);
    } 

}


/***
*
***/
void AVLTree::PreorderTraversal(Node *current)
{
    if (current != NULL)
    {
        TreeData *tData = current->GetData();
        cerr << tData->GetChrom() << "\t" << tData->GetStart() << "\t" << tData->GetStop()
             << "\t" << tData->GetGeneId() << endl;
    
        PreorderTraversal(current->GetLeftChild());
        PreorderTraversal(current->GetRightChild());
    }
}


/***
*
***/
bool AVLTree::DoSearch(Node *current, Node *target)
{
    
    if (current == NULL)
    {
        return false;
    }
    
    AVLTree::Equality e;
    
    switch (Sort)
    {
        case Standard:
            e = StandardCompare(target, current);
            break;
        case Genic:
            e = GenicCompare(target, current);
            break;
    }

    switch (e)
    {
        case Eq:
            return true;
        case Lt:
            return DoSearch(current->GetLeftChild(), target);
        case Gt:
            return DoSearch(current->GetRightChild(), target);
        default:
            cerr << "ERROR: equality case not met. Line: " << __LINE__ << endl;
            return false;
    }
}


/***
*
***/
Node *AVLTree::FindMin(Node *current)
{
    Node *left = current->GetLeftChild();
    
    if (left == NULL)
        return current;

    return FindMin(left);
}


/***
*
***/
void AVLTree::SetHeight(Node *current)
{
    if (current == NULL)
        return;
   
    Node *right = current->GetRightChild();
    Node *left  = current->GetLeftChild();

    if (left == NULL && right == NULL)
        current->SetHeight(1);

    else if (left == NULL)
        current->SetHeight(right->GetHeight() + 1);

    else if (right == NULL)
        current->SetHeight(left->GetHeight() + 1);

    else
    {
        //If right and left children exist, set height to the maximum
        //of the two. 
        unsigned int lTotal = left->GetHeight() + 1;
        unsigned int rTotal = right->GetHeight() + 1;
        current->SetHeight( (lTotal < rTotal) ? rTotal : lTotal );
    }
}


/***
*
***/
Node *AVLTree::CheckBalance(Node *n)
{
    if (n == NULL)
    {
        return n;
    }

    int diff     = GetNodeHeight(n->GetLeftChild()) - GetNodeHeight(n->GetRightChild());
    int absvDiff = (diff < 0) ? (diff * -1) : diff;

    if (absvDiff > 1)
    {
        Node *balanced = Rebalance(n, diff);
        SetHeight(balanced);
        return balanced;
    }
    return n;
}


/***
*
***/
Node *AVLTree::Rebalance(Node *n, int diff)
{
    AVLTree::BalanceCase nodeCase = DetermineBalanceCase(n, diff);
    switch (nodeCase)
    {
        case RIGHTRIGHT:
            return RotateLeft(n);
        case LEFTLEFT:
            return RotateRight(n);
        case RIGHTLEFT:
            return CaseRightLeft(n);
        case LEFTRIGHT:
            return CaseLeftRight(n);
        default:
            Node *scrap = NULL;
            cerr << "ERROR: invalid case line: " << __LINE__ << endl;
            return scrap;
    }
}


/***
*
***/
AVLTree::BalanceCase AVLTree::DetermineBalanceCase(Node *n, int diff)
{
    int grandChildDiff;
    AVLTree::BalanceCase c;
    if (diff > 0)
    {
        Node *leftChild = n->GetLeftChild();
        grandChildDiff  = GetNodeHeight(leftChild->GetLeftChild()) -
                         GetNodeHeight(leftChild->GetRightChild());
        if (grandChildDiff >= 0)
        {
            c = LEFTLEFT;
            return c;
        }
        c = LEFTRIGHT;
        return c;
    }
    
    Node *rightChild = n->GetRightChild();
    grandChildDiff   = GetNodeHeight(rightChild->GetLeftChild()) -
                       GetNodeHeight(rightChild->GetRightChild());
    if (grandChildDiff <= 0)
    {
        c = RIGHTRIGHT;
        return c;
    }
    c = RIGHTLEFT;
    return c;
}


/***
*
***/
Node *AVLTree::RotateRight(Node *n)
{
    Node *outNode = n->GetLeftChild();
    n->SetLeftChild(outNode->GetRightChild());
    outNode->SetRightChild(n);
    SetHeight(outNode->GetLeftChild());
    SetHeight(outNode->GetRightChild());
    return outNode;
}


/***
*
***/
Node *AVLTree::RotateLeft(Node *n)
{
    Node *outNode = n->GetRightChild();
    n->SetRightChild(outNode->GetLeftChild());
    outNode->SetLeftChild(n);
    SetHeight(outNode->GetLeftChild());
    SetHeight(outNode->GetRightChild());
    return outNode;
}


/***
*
***/
Node *AVLTree::CaseLeftRight(Node *n)
{
    n->SetLeftChild(RotateLeft(n->GetLeftChild()));
    n = RotateRight(n);
    return n;
}


/***
*
***/
Node *AVLTree::CaseRightLeft(Node *n)
{
    n->SetRightChild(RotateRight(n->GetRightChild()));
    n = RotateLeft(n);
    return n;
}


/***
*
***/
unsigned int AVLTree::GetNodeHeight(Node *n)
{
    if (n != NULL)
        return n->GetHeight();

    return 0;
}






