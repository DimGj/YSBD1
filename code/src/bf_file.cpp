#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bf.h"
#include "hash_file.h"


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
