// Dat Nguyen
#ifndef ENTRY_H
#define ENTRY_H
#include "iPhone.h"

class entry
{
private:
    iPhone* bucket[3];
    int count;

public:
    // Constructor
    entry()
    {
        for(int i=0; i<3; i++) bucket[i] = nullptr;
        count = 0;
    }

    /// getters
    iPhone* getBucket(int i)
    {
        return bucket[i];
    }

    int getCount()
    {
        return count;
    }

    /// setters
    void setBucket(int i, iPhone* ptr)
    {
        bucket[i] = ptr;
    }

    void increaseCount()
    {
        count++;
    }

    void decreaseCount()
    {
        count--;
    }
};

#endif
