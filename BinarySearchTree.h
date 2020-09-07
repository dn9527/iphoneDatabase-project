// Binary Search Tree ADT
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Angela Chen
 
#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{   
private:
	// internal insert node: insert newNode in nodePtr subtree
	BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);

   
	// internal remove node: locate and delete target node under nodePtr subtree
	BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool & success);
   
	// delete target node from tree, called by internal remove node
	BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);
   
	// remove the leftmost node in the left subtree of nodePtr
	BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor);
   
	// search for target node
	BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, const ItemType & target) const;
   
public:  
	// insert a node at the correct location
    bool insert(const ItemType & newEntry);
	// remove a node if found
	bool remove(const ItemType & anEntry);
	// find a target node
	bool getEntry(const ItemType & target, ItemType & returnedItem) const;
    
    
    // find minum item content in the tree
    bool  findMin(ItemType & target);
    // find maxmum item content in the tree
    bool  findMax(ItemType & target);
 
};


///////////////////////// public function definitions ///////////////////////////
/****Implementation for insert function--to insert a node to a tree *********/
template<class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType & newEntry)
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
	this->rootPtr = _insert(this->rootPtr, newNodePtr);
	return true;
}  
/****Implementation for remove function--to remove node from the ree ********/
template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType & target)
{
	bool isSuccessful = false;
	this->rootPtr = _remove(this->rootPtr, target, isSuccessful);
	return isSuccessful; 
}  

/****Implementation for getEntry function--to find a node in a tree ********/
template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry, ItemType & returnedItem) const
{
    BinaryNode<ItemType>* nodePtr;
    nodePtr = findNode(this->rootPtr, anEntry);
    if (nodePtr)
    {
        returnedItem=nodePtr->getItem();
        return true;
    }
    else
        return false;
}  



//////////////////////////// private functions ////////////////////////////////////////////

/****Implementation for insert private function--to insert a node in a tree ********/
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,
                                                          BinaryNode<ItemType>* newNodePtr)
{
    if (nodePtr == nullptr)
    {
        return newNodePtr;
    }
    else
    {
        if (nodePtr->getItem() > newNodePtr->getItem())
        {
            newNodePtr->setLevel(newNodePtr->getLevel()+1);
            nodePtr->setLeftPtr(_insert(nodePtr->getLeftPtr(), newNodePtr));
        }
        else
        {
            newNodePtr->setLevel(newNodePtr->getLevel()+1);
            nodePtr->setRightPtr(_insert(nodePtr->getRightPtr(), newNodePtr));
        }
        return nodePtr;
       
    }
    
}

/****Implementation for remove private function--to remove a target node in a tree ********/
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr,
                                                          const ItemType target,
                                                          bool & success)
{
	if (!nodePtr )
	{
		success = false;
		return 0;
	}
	if (nodePtr->getItem() > target)		 
		nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
	else if (nodePtr->getItem() < target)	 
		nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
	else		
	{
		nodePtr = deleteNode(nodePtr);
		success = true;
	}      
	return nodePtr;   
}  
/****Implementation for delete private function--to delete a leaf node in a 
 tree( three cases) ********/

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr->isALeaf())				
	{
		delete nodePtr;
		nodePtr = 0;
		return nodePtr;
	}
	else if (nodePtr->getLeftPtr() == 0)  
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else if (nodePtr->getRightPtr() == 0) 
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;      
	}
	else                                  
	{
		ItemType newNodeValue;
		nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
		nodePtr->setItem(newNodeValue);
		return nodePtr;
	}  
}  
/****Implementation for removeLeftmostNode private function--to remove the  removeLeftmostNode in a
 tree( three cases) ********/

template<class ItemType> 
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
                                                                     ItemType & successor)
{
	if (nodePtr->getLeftPtr() == 0)
	{
		successor = nodePtr->getItem();
		return deleteNode(nodePtr);
	}
	else 
	{
		nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
		return nodePtr;
	}       
}
/****Implementation for findNode private function--find a node in a
 tree( three cases) ********/

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* nodePtr,
                                                           const ItemType & target) const 
{
    // Uses a binary search
    if (nodePtr == nullptr)
        return nodePtr;                        // Not found
    else if (nodePtr->getItem() == target)
        return nodePtr;                     // Found
    else if (nodePtr->getItem() > target)
        // Search left subtree
        return findNode(nodePtr->getLeftPtr(), target);
    else
        // Search right subtree
        return findNode(nodePtr->getRightPtr(), target);
}

// find minum item content in the tree
template<class ItemType>
bool BinarySearchTree<ItemType>::findMin(ItemType & target)
{
    if( this->rootPtr)
    {
        //target= this->findLeftmost(this->getLeftPtr() )-> getItem();
        target= this->findLeftmost();
        return true;
    }
    return false;
}
// find maxmum item content in the tree
template<class ItemType>
bool BinarySearchTree<ItemType>::findMax(ItemType & target)
{
    if( this->rootPtr)
    {
         // target= this->findRightmost(this->getRightPtr() )->getItem();
        target= this->findRightmost();
        return true;
    }
    return false;
}
#endif
