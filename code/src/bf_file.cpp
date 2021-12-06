#include <iostream>

#include "bf.h"
#include "hash_file.h"

using nanespace std;

typedef struct BF_Block {
    Record *Array;
    bool DirtyStatus;
    bool Pinned;
} BF_Block;

void BF_Block_Init(BF_Block **block) //When this function is called,the block arg will be a pointer to the block,hence the double pointer block variable
{
    *block = new BF_Block;
    (*block)->Array = new Record[10]; //the max bytes stored in a block are 512 and each record is 49
    (*block)->DirtyStatus = false; //Each new block isn't dirty
    (*block)->Pinned = false;
} 

void BF_Block_Destroy(BF_Block **block)
{
    delete[] (*block)->Array;               //delete first the array of records and then the whole block
    delete *block;
}

void BF_Block_SetDirty(BF_Block *block)
{
    block->DirtyStatus = true;
}

char* BF_Block_GetData(const BF_Block *block)
{
    char** Data = new char*[30];
    for(int i  = 0;i < 10 ; i++)
    {
        Data[i] = block->Array->city;
        Data[i+1] = block->Array->name;
        Data[i+2] = block->Array->surname;
    }
    return *Data;
}

int main()
{
    BF_Block *A;
    BF_Block_Init(&A);
    BF_Block_SetDirty(A);
    BF_Block_GetData(A);
    BF_Block_Destroy(&A);
    return 0;
}
