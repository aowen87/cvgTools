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
* @author: Alister Maguire
*
* Node constuctor.
*
***/
Node::Node()
{
    gene   = NULL;
    right  = NULL;
    left   = NULL;
    height = 0;
}


/***
*
* @author: Alister Maguire
*
* Parameterized constructor. 
*
* @param: g -> a Gene pointer. 
***/
Node::Node(Gene *g)
{
    gene   = g;
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
    gene  = new Gene();
    gene->DeepCopy(*(n.gene));
}


/***
*
***/
Node::~Node() 
{
    if (gene != NULL)
        delete gene;
}


/***
*
***/
bool Node::ExpandDataStart(int _start)
{
    if (_start < gene->GetStart())
    {
        gene->SetStart(_start);
        return true;
    }
    return false;
}


/***
*
***/
bool Node::ExpandDataStop(int _stop)
{
    if (_stop > gene->GetStop())
    {
        gene->SetStop(_stop);
        return true;
    }
    return false;
}


/***
*
***/
Gene *Node::GetGene() { return gene; }


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
    right = r;
}


/***
*
***/
void Node::SetGene(Gene *g)
{
    gene = g;
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
AVLTree::AVLTree()
{
    root = NULL;
    Sort = Standard;
    numNodes = 0;
}


/***
*
***/
AVLTree::AVLTree(char s) 
{ 
    root = NULL;       //FIXME: I'm not a fan of this method
    if (s == 'g')      //       for setting Sort. Let's change it.
        Sort = Genic;
    else if (s == 's')
        Sort = Standard;
    else
    {
        cerr << "Inavlid sort option: " << s << endl;
        exit(EXIT_FAILURE); 
    }
    numNodes = 0;
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
void AVLTree::Insert(Gene *g)
{
    Node *n = new Node(g);
    root    = CheckBalance(DoInsertion(root, n));
    delete n;
}


/***
*
***/
void AVLTree::Delete(Gene *g)
{
    Node *n = new Node(g);
    root    = DeletionSearch(root, n);
    delete n;
}


/***
*
***/
bool AVLTree::Search(Gene *g)
{
    Node *n    = new Node(g);
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
Gene *AVLTree::RemoveMin()
{
    if (root == NULL)
    {
        Gene *scrap = NULL;
        return scrap;
    }
    Gene *outData    = new Gene; 
    Gene *searchData = new Gene;
    Node *minNode    = FindMin(root);
    searchData->DeepCopy( *(minNode->GetGene()) );
    outData->DeepCopy( *(minNode->GetGene()) );
    Node *searchNode = new Node(searchData);
    root             = DeletionSearch(root, searchNode);
    delete searchNode;
    return outData;
}


/***
*
***/
Node *AVLTree::DeletionSearch(Node *current, Node *target)
{
    if (current == NULL)
        cerr << "Target node could not be deleted -> DNE in this tree." << endl;

    AVLTree::Equality e;

    switch (Sort)
    {
        case Standard:
            e = StandardCompare(target, current);            
            break;
        case Genic:
            e = GenicCompare(target, current);
            break;
        default:
            cerr << "ERROR: invalide case line: " << __LINE__ << endl;
            exit(EXIT_FAILURE);
    }

    switch (e)
    {
        case Eq:
            return CheckBalance(DeleteNode(current));
        case Lt:
            current->SetLeftChild(DeletionSearch(current->GetLeftChild(), target));
            SetHeight(current);
            break;
        case Gt:
            current->SetRightChild(DeletionSearch(current->GetRightChild(), target));
            SetHeight(current);
            break;
        default:
            cerr << "ERROR: invalid case line: " << __LINE__ << endl;
            break; 
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
    numNodes--;
    
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
   
    Gene *nData = n->GetGene(); 
    Node *origin    = new Node(nData);
    Node *leftmost  = FindLeftmost(nData, n->GetRightChild());
    n->SetGene(leftmost->GetGene());
    n->SetRightChild(DeletionSearch(n->GetRightChild(), origin));
    SetHeight(n->GetRightChild());
    SetHeight(n);     
    return NULL;
}


/***
*
***/
Node *AVLTree::FindLeftmost(Gene *originData, Node *searchNode)
{
    Node *leftmost;
    while (searchNode->GetLeftChild() != NULL)
    {
        searchNode = searchNode->GetLeftChild();
    }
    leftmost = new Node(searchNode->GetGene());
    searchNode->SetGene(originData);
    return leftmost; 
}


/***
*
***/
AVLTree::Equality AVLTree::StandardCompare(Node *n1, Node *n2)
{
    Gene *n1Data  = n1->GetGene();
    Gene *n2Data  = n2->GetGene();
    
    int result = HPR::GeneCompare(*n1Data, *n2Data);
    AVLTree::Equality e;
    
    switch(result)
    {
        case(0):
            e = Eq;
            return e; 
        case(1):
            e = Gt;
            return e;
        case(-1):
            e = Lt;
            return e;
        default:
            cerr << "ERROR: unknown case! line: " << __LINE__ << endl;
            cerr << "Exiting..." << endl;
            exit(EXIT_FAILURE);
    }
}


/***
*
***/
AVLTree::Equality AVLTree::GenicCompare(Node *n1, Node *n2)
{
    Gene *n1Data = n1->GetGene();
    Gene *n2Data = n2->GetGene();
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
        numNodes++;
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
                    current->ExpandDataStart(n->GetGene()->GetStart());
                    current->ExpandDataStop(n->GetGene()->GetStop());
                    current->GetGene()->AddExonVector(*(n->GetGene()->GetExons()));
                    current->GetGene()->AddStartCodonVector(*(n->GetGene()->GetStartCodons()));
                    current->GetGene()->AddStopCodonVector(*(n->GetGene()->GetStopCodons()));
                    current->GetGene()->AddCDSVector(*(n->GetGene()->GetCDS()));
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
    Gene *gene      = current->GetGene();
    
    if (left != NULL)
    {
        InorderTraversal(left);
    }

    cerr << gene->GetChrom() << "\t" << gene->GetStart() << "\t" << gene->GetStop()
         << "\t" << gene->GetGeneId() << "\t" << endl;

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
        Gene *gene = current->GetGene();
        cerr << gene->GetChrom() << "\t" << gene->GetStart() << "\t" << gene->GetStop()
             << "\t" << gene->GetGeneId() << endl;
    
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


/***
*
***/
bool AVLTree::IsEmpty()
{
    if (root == NULL)
       return true;
    return false;
}


/***
*
***/
unsigned long AVLTree::GetNumNodes() { return numNodes; }
