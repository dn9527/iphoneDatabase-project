/// BianryNode class
/// Dat Nguyen

#ifndef BINARY_NODE_H
#define BINARY_NODE_H

template<class ItemType>
class BinaryNode
{
private:
    ItemType item;
    int      level; /// Vera added
    BinaryNode<ItemType>* leftPtr;	  /// Pointer to left
    BinaryNode<ItemType>* rightPtr;	 /// Pointer to right

public:
    /// constructors
    //BinaryNode(): leftPtr(nullptr), rightPtr(nullptr) {} /// default constructor
    //BinaryNode(BinaryNode<ItemType>* left, BinaryNode<ItemType>* right): leftPtr(left), rightPtr(right) {}
    BinaryNode(const ItemType & anItem){item = anItem; leftPtr = 0; rightPtr = 0; level = 1;}
    BinaryNode(const ItemType & anItem, BinaryNode<ItemType>* left, BinaryNode<ItemType>* right){item = anItem; leftPtr = left; rightPtr = right;}

    /// accessors
    void setItem(const ItemType & anItem) { item = anItem;} /// Vera added
    void setLeftPtr(BinaryNode<ItemType>* left) { leftPtr = left;}
    void setRightPtr(BinaryNode<ItemType>* right) { rightPtr = right;}
    void setLevel(int depth) { level = depth;} /// Vera added

    /// mutators
    ItemType getItem() const { return item;} /// Vera added
    int getLevel() { return level;}
    BinaryNode<ItemType>* getLeftPtr() const { return leftPtr;}
    BinaryNode<ItemType>* getRightPtr() const { return rightPtr;}

    /// check if it is a leaf
    bool isALeaf() const {return (leftPtr == 0 && rightPtr == 0);}
};

#endif
