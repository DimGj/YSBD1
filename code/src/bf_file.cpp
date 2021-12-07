#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

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
    (*block)->Array = new Record[8]; //the max bytes stored in a block are 512 and each record is 49
    (*block)->DirtyStatus = false; //Each new block isn't dirty
    (*block)->Pinned = false; //each new block isn't yet pinned
}

void BF_Block_Destroy(BF_Block **block)
{
    delete[] (*block)->Array; //Delete the dynamically allocated array
    delete *block; //delete the whole block struct
}

void BF_Block_SetDirty(BF_Block *block)
{
    block->DirtyStatus = true;
}

char** BF_Block_GetData(const BF_Block *block)
{
    char** Data = new char*[24];
    for(int i  = 0;i < 8 ; i++)
    {
        Data[i] = block->Array->city;
        Data[i+1] = block->Array->name;
        Data[i+2] = block->Array->surname;
    }
    return Data;
}


BF_ErrorCode BF_CreateFile(const char* filename)
{
    ifstream Temp;
    Temp.open(filename);
    if(Temp)
    {
        cout<<"file with name "<<filename<<" already exists"<<endl;
        Temp.close();//temporary
        return BF_ErrorCode(4);
    }
    ofstream File(filename);
    File.close();//temporary
    return BF_ErrorCode(0);
}

BF_ErrorCode BF_OpenFile(const char* filename, int *file_desc)
{
    ifstream openfile;
    openfile.open(filename);
    if(openfile)
    {
        for(int i = 0; i < 20 ; i++)
        {
            if(FileArray->empty())
            {
                FileArray[i] = filename;
                *file_desc = i;
                cout<<"File with name "<<filename << " opened successfully"<<endl;
                return BF_ErrorCode(0);
            }
        }
    }
    cout<<"File with name "<<filename<<" can't be opened,because it doesn't exist"<<endl;
    return BF_ErrorCode(8);
}

BF_ErrorCode BF_CloseFile(const int file_desc)
{
    for(int i = 0;i < 20;i ++)
    {
        if(i == file_desc)
        {
            ifstream File(FileArray[i]);
            File.close();
        }
        if(i >= file_desc) //delete item from the array and resize the array somehow
        {
         //   FileArray[i] = FileArray[i + 1];
        }
    }

    return BF_ErrorCode(0);
}

int main()
{
    BF_Block *A;
    BF_Block_Init(&A);
    BF_Block_SetDirty(A);
    BF_Block_GetData(A);
    BF_Block_Destroy(&A);
    BF_CreateFile("spera.txt");
    int fileid;
    BF_OpenFile("spera.txt",&fileid);
    BF_CloseFile(fileid);
    return 0;
}