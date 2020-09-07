//Dat Nguyen
#ifndef HASH_ENTRY_H
#define HASH_ENTRY_H
#include "entry.h"
#include "node.h"

class  hashEntry
{
private:
    int tableSize;
    entry* hashTable;
    Node* headList;

public:
    hashEntry(const int tableSizeIn);
    ~hashEntry();
    int Hash(string& key) const;
    void insertNode(iPhone* ptrIn);
    void insertEntry(string& key, iPhone* ptrIn);
    void printEntry() const;
    iPhone* searchEntry(string key) const;
    bool removeEntry(string key);
    void deleteTable();
    float loadedFactor1() const;
    float loadedFactor2() const;
    
    void writeFile() const;
};

hashEntry::hashEntry(const int tableSizeIn)
{
    tableSize = tableSizeIn;
    hashTable = new entry[tableSize];
    headList = new Node(nullptr);
}

hashEntry::~hashEntry()
{
    deleteTable();
}


int hashEntry::Hash(string& key) const
{
    int sum = 0;
    for(unsigned int i=0; i < key.length(); i++)
    {
        sum += key[i] - '0';
    }
    return sum*sum%tableSize;
}

void hashEntry::insertNode(iPhone* ptrIn)
{
    Node* ptr = headList;
    Node* newNode = new Node(ptrIn);

    /// Skip all nodes until the last node
    while (ptr->getNext())
        ptr = ptr->getNext();

    /// Update links to insert the new node
    ptr->setNext(newNode);
}

void hashEntry::insertEntry(string& key, iPhone* ptrIn)
{
    int index = Hash(key);
    if(hashTable[index].getCount() < 3)
    {
        hashTable[index].setBucket(hashTable[index].getCount(), ptrIn);
        hashTable[index].increaseCount();
    }
    else insertNode(ptrIn);
}

void hashEntry::printEntry() const
{
    for(int i=0; i< tableSize; i++)
    {
        if(hashTable[i].getCount() > 0)
        {
            for(int j=0; j< hashTable[i].getCount(); j++)
            {
                std::cout << "Index " << i << " bucket " << j << ": "
                          << hashTable[i].getBucket(j)->getIMEI() << " "
                          << hashTable[i].getBucket(j)->getCapacity() << "Gb "
                          << hashTable[i].getBucket(j)->getSerial() << " "
                          << hashTable[i].getBucket(j)->getModel() << " "
                          << hashTable[i].getBucket(j)->getCountry() << std::endl;
            }
        }
        else std::cout << "Index " << i << " are empty" << std::endl;
    }

    if(headList->getNext() == nullptr) return;
    Node* ptr = headList->getNext();
    std::cout << "-------------------------------" << std::endl;
    std::cout << "Overflow area: " << std::endl;

    while(ptr->getNext())
    {
        std::cout << ptr->getData()->getIMEI() << " "
                  << ptr->getData()->getCapacity() << "Gb "
                  << ptr->getData()->getSerial() << " "
                  << ptr->getData()->getModel() << " "
                  << ptr->getData()->getCountry() << std::endl;

        ptr = ptr->getNext();
    }
}

iPhone* hashEntry::searchEntry(string key) const
{
    int index = Hash(key);

    /// Case 1: buckets contain items
    if(hashTable[index].getCount() > 0)
    {
        ///Check the buckets
        for(int i=0; i< hashTable[index].getCount(); i++)
        {
            if(hashTable[index].getBucket(i)->getIMEI() == key)
            {
                std::cout << "Index " << index << " bucket " << i << ": "
                          << hashTable[index].getBucket(i)->getIMEI() << " "
                          << hashTable[index].getBucket(i)->getCapacity() << "Gb "
                          << hashTable[index].getBucket(i)->getSerial() << " "
                          << hashTable[index].getBucket(i)->getModel() << " "
                          << hashTable[index].getBucket(i)->getCountry() << std::endl;
                return hashTable[index].getBucket(i);
            }
        }
        /// Check overflow area
        Node* ptr = headList->getNext();
        int n = 1;
        while(ptr && ptr->getData()->getIMEI() != key)
        {
            ptr = ptr->getNext();
            n++;
        }

        /// overflow area doesn't have the item
        if(!ptr)
        {
            std::cout << "Item " << key << " was not found" << std::endl;
            return nullptr;
        }
        else
        {
            std::cout << "Overflow node " << n << ": "
                      << ptr->getData()->getIMEI() << " "
                      << ptr->getData()->getCapacity() << "Gb "
                      << ptr->getData()->getSerial() << " "
                      << ptr->getData()->getModel() << " "
                      << ptr->getData()->getCountry() << std::endl;
            return ptr->getData();
        }
    }

    ///case 0: buckets are empty
    std::cout << "Item " << key << " was not found" << std::endl;
    return 0;
}

bool hashEntry::removeEntry(string key)
{
    int index = Hash(key);
    iPhone* delPtr;

    /// case 1: buckets contain items
    if(hashTable[index].getCount() > 0)
    {
        /// case 1.1: item in the last available bucket
        if(hashTable[index].getBucket(hashTable[index].getCount()-1)->getIMEI() == key)
        {
            delPtr = hashTable[index].getBucket(hashTable[index].getCount()-1);
            hashTable[index].setBucket(hashTable[index].getCount()-1, nullptr);
            delete delPtr;
            hashTable[index].decreaseCount();
            std::cout << "Item " << key << " has been deleted." << std::endl;
            return true;
        }

        /// case 1.2: item not in the last
        else
        {
            for(int i=0; i< hashTable[index].getCount(); i++)
            {
                if(hashTable[index].getBucket(i)->getIMEI() == key)
                {
                    delPtr = hashTable[index].getBucket(i);
                    hashTable[index].setBucket(i, hashTable[index].getBucket(hashTable[index].getCount()-1));
                    hashTable[index].setBucket(hashTable[index].getCount()-1, nullptr);
                    delete delPtr;
                    hashTable[index].decreaseCount();
                    std::cout << "Item " << key << " has been removed." << std::endl;
                    return true;
                }
            }
        }

        /// case 2: item in overflow area
        Node* ptr = headList->getNext();
        Node* prePtr = headList;
        while(ptr && ptr->getData()->getIMEI() != key)
        {
            prePtr = ptr;
            ptr = ptr->getNext();
        }

        /// case 2.1: overflow area doesn't have the item
        if(!ptr)
        {
            std::cout << "Item " << key << " was not found" << std::endl;
            return false;
        }
        ///case 2.2: overflow has the item
        else
            delPtr = ptr->getData();
        prePtr->setNext(ptr->getNext());
        delete delPtr;
        delete ptr;
        std::cout << "Item " << key << " has been removed." << std::endl;
        return true;
    }

    ///case 0: buckets are empty
    std::cout << "Item " << key << " was not found" << std::endl;
    return false;
}

void hashEntry::deleteTable()
{
    iPhone* delPtr;
    ///delete hash table
    for(int i=0; i < tableSize; i++)
    {
        if(hashTable[i].getCount() > 0)
        {
            for(int j=0; j < hashTable[i].getCount(); j++)
            {
                delPtr = hashTable[i].getBucket(j);
                //delete delPtr;
            }
        }
    }

    delete hashTable;

    ///delete overflow area
    Node* ptr = headList;
    Node* nextPtr;
    while (ptr != NULL)
    {
        delPtr = ptr->getData();
        nextPtr = ptr->getNext();
        //delete delPtr;
        delete ptr;
        ptr = nextPtr;
    }
}

float hashEntry::loadedFactor1() const
{
    float n = 0;
    for(int i=0; i < tableSize; i++)
        if(hashTable[i].getCount()) n++;

    return n/tableSize*100;
}

float hashEntry::loadedFactor2() const
{
    float n = 0;
    for(int i=0; i < tableSize; i++)
        n += hashTable[i].getCount();

    return n/(tableSize*3)*100;
}
//Maria
void hashEntry::writeFile() const
{
    string outFilename = "UpdatediPhones.txt";
    ofstream outputFile; //open the output file
    outputFile.open(outFilename.c_str());
    
    float n = 0;
    for(int i=0; i < tableSize; i++)
        if(hashTable[i].getCount()) n++;

    
    outputFile << n << endl;
    
    
    for(int i=0; i < tableSize; i++)
    {
        if(hashTable[i].getCount() > 0)
        {
            for(int j=0; j< hashTable[i].getCount(); j++)
            {
                outputFile<< hashTable[i].getBucket(j)->getIMEI() << " "
                << hashTable[i].getBucket(j)->getCapacity() << " "
                << hashTable[i].getBucket(j)->getSerial() << " "
                << hashTable[i].getBucket(j)->getModel() << " "
                << hashTable[i].getBucket(j)->getCountry() << std::endl;
            }
        }
    }
    
    if(headList->getNext() == nullptr) return;
    Node* ptr = headList->getNext();
    while(ptr->getNext())
    {
        outputFile << ptr->getData()->getIMEI() << " "
        << ptr->getData()->getCapacity() << " "
        << ptr->getData()->getSerial() << " "
        << ptr->getData()->getModel() << " "
        << ptr->getData()->getCountry() << std::endl;
        
        ptr = ptr->getNext();
    }
       outputFile.close();//close the output file
}
#endif
