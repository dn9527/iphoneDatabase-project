// Binary tree abstract base class
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Angela Chen

#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
#include "Queue.h"

template<class ItemType>
class BinaryTree
{
protected:
    BinaryNode<ItemType>* rootPtr;		// ptr to root node
    int count;// number of nodes in tree
    
    // find leftmost and rightmost
    BinaryNode<ItemType>* _findLeftmost( BinaryNode<ItemType>* nodePtr) const;
    BinaryNode<ItemType>* _findRightmost( BinaryNode<ItemType>* nodePtr) const;
    
private:
    // delete all nodes from the tree
    void destroyTree(BinaryNode<ItemType>* nodePtr);
    
    // copy from the tree rooted at nodePtr and returns a pointer to the copy
    BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* nodePtr);
    
    // internal traverse
    void _preorder(void visit(), BinaryNode<ItemType>* nodePtr) const;
    void _inorder(void visit(), BinaryNode<ItemType>* nodePtr) const;
    void _postorder(void visit(), BinaryNode<ItemType>* nodePtr) const;
    void _breadthFirst (void visit(ItemType &, int),BinaryNode<ItemType>* nodePtr ) const;
    void _neworder (void visit(),BinaryNode<ItemType>* nodePtr ) const;
    
public:
    ItemType findLeftmost()const { return _findLeftmost(rootPtr)->getItem(); }
    ItemType findRightmost()const { return _findRightmost(rootPtr)->getItem(); }
    
    // "admin" functions, constructor
    BinaryTree()
    {rootPtr = 0; count = 0;}
    
    BinaryTree(const BinaryTree<ItemType> & tree){ }
    
    BinaryTree & operator = (const BinaryTree & sourceTree);
    
    // common functions for all binary trees
    bool isEmpty() const	{return count == 0;}
    int size() const	    {return count;}
    
    // see below function impementation.
    void preOrder(void visit()) const
    {_preorder(visit, rootPtr);}
    
    // see below function impementation.
    void inOrder(void visit()) const
    {_inorder(visit, rootPtr);}
    
    // see below function impementation.
    void postOrder(void visit()) const
    {_postorder(visit, rootPtr);}
    
    void newOrder(void visit()) const
    {_neworder(visit, rootPtr);}

    
    
    void breadthFirst (void visit(ItemType &, int)) const
    { _breadthFirst(visit, rootPtr);}
    
    // abstract functions to be implemented by derived class.
    // all virtual functions are pure virtual so that derived class can redefine them.
    virtual bool insert(const ItemType & newData) = 0;
    virtual bool remove(const ItemType & data) = 0;
    virtual bool getEntry(const ItemType & anEntry, ItemType & returnedItem) const = 0;
    void clear()			{destroyTree(rootPtr); rootPtr = 0; count = 0;}
    virtual ~BinaryTree() { }
    
    
    
};

/*******************************************************************************
   copytree function copy a tree
 ******************************************************************************/

template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::copyTree(const BinaryNode<ItemType>* nodePtr)
{
    BinaryNode<ItemType>* newNodePtr = 0;
    
    
    // Copy tree nodes during a preorder traversal
    if (nodePtr != nullptr)
    {
        // Copy node
        
        newNodePtr = BinaryNode<ItemType>(nodePtr->getItem(), nullptr, nullptr);
        newNodePtr->setLeftChildPtr(copyTree(nodePtr->getLeftChildPtr()));
        newNodePtr->setRightChildPtr(copyTree(nodePtr->getRightChildPtr()));
        
        return newNodePtr;
    }
}
/********************************************************************************************
  destroyTree function destroy a tree
 *********************************************************************************************/
template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
    if( nodePtr)
    {
        if(nodePtr->getLeftPtr())
            destroyTree(nodePtr->getLeftPtr());
        if(nodePtr->getRightPtr())
            destroyTree(nodePtr->getRightPtr());
        delete nodePtr;
    }
    
}
/********************************************************************************************
 The proder member function displays the values in the subtree pointed by nodePetr, via
 preorder traversa l
 *********************************************************************************************/
template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr != 0)
    {
        ItemType item = nodePtr->getItem();
        visit();
        
        _preorder(visit, nodePtr->getLeftPtr());
        _preorder(visit, nodePtr->getRightPtr());
    }
}

/********************************************************************************************
 The proder member function displays the values in the subtree pointed by nodePetr, via
 inorder traversal
 *********************************************************************************************/
template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr != 0)
    {
        _inorder(visit, nodePtr->getLeftPtr());
        
        ItemType item = nodePtr->getItem();
        visit();
        
        _inorder(visit, nodePtr->getRightPtr());
    }
}
/********************************************************************************************
 _postorder function tranverse the tree in post order
 *********************************************************************************************/
template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr != 0)
    {
        
        _postorder(visit, nodePtr->getLeftPtr());
        _postorder(visit, nodePtr->getRightPtr());
        
        ItemType item = nodePtr->getItem();
        visit(item,nodePtr->getLevel());
        
    }
}

/********************************************************************************************
 _postorder function tranverse the tree in root-right-left order
 *********************************************************************************************/
template<class ItemType>
void BinaryTree<ItemType>::_neworder(void visit(), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr != 0)
    {
        ItemType item = nodePtr->getItem();
        visit();
        
        _neworder(visit, nodePtr->getRightPtr());
        _neworder(visit, nodePtr->getLeftPtr());
        
        
    }
}


/********************************************************************************************
 overload _operator used to copy tree
 *********************************************************************************************/
template<class ItemType>
BinaryTree<ItemType> & BinaryTree<ItemType>::operator=(const BinaryTree<ItemType> & sourceTree)
{
    if (!isEmpty())
        clear();
    this = copyTree(& sourceTree);
    return *this;
    
}
/********************************************************************************************
 The proder member function displays the values in the subtree pointed by nodePetr, via
 postorder traversal
 *********************************************************************************************/
template<class ItemType>
void BinaryTree<ItemType>:: _breadthFirst (void visit(ItemType &, int level),BinaryNode<ItemType>* nodePtr ) const
{
    
    if (nodePtr==0)
    {
        return;
    }
    Queue<BinaryNode<ItemType>*> q;
    q.enqueue(nodePtr);
    
    while (!q.isEmpty())
    {
        q.dequeue(nodePtr);
        ItemType item = nodePtr->getItem();
        visit(item,nodePtr->getLevel());
        
        
        if (nodePtr->getLeftPtr())
        {
            q.enqueue(nodePtr->getLeftPtr());
        }
        
        if (nodePtr->getRightPtr() )
        {
            q.enqueue(nodePtr->getRightPtr());
        }
    }
    
}

/********************************************************************************************
 The Findleftmost and Findrightmost function find the leftmost or the rightmost node in the tree ****************************************************************************************/
template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::_findLeftmost( BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr->getLeftPtr())
        //nodePtr =_findLeftmost(nodePtr->getLeftPtr()); nodePtr is const, could not initialize value
        return  _findLeftmost(nodePtr->getLeftPtr());
    return nodePtr;
}

template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::_findRightmost( BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr->getRightPtr())
        return _findRightmost(nodePtr->getRightPtr());
    return nodePtr;
}

#endif

