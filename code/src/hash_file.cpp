#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <cstring>

using namespace std;

#include "bf.h"
#include "hash_file.h"
#define MAX_OPEN_FILES 20

#define CALL_BF(call)       \
{                           \
  BF_ErrorCode code = call; \
  if (code != BF_OK) {         \
    BF_PrintError(code);    \
    return HT_ERROR;        \
  }                         \
}

typedef struct FileList
{
  int ID;
  string Name;
}FileList;

FileList* Array;

HT_ErrorCode HT_Init() {
  BF_Block* Block;
  BF_Block_Init(&Block);
  CALL_BF(BF_Init(LRU));
  Array = new FileList[20];
  return HT_OK;
}

HT_ErrorCode HT_CreateIndex(const char *filename, int depth) {
  int file_desc;BF_Block* Block;char* Data;
  CALL_BF(BF_CreateFile(filename));
  CALL_BF(BF_OpenFile(filename,&file_desc)); //epistrfei to id sto file desc
  CALL_BF(BF_AllocateBlock(file_desc,Block)); //meta thelei unpin,epistrfei to block sth metavlith block
  Data = BF_Block_GetData(Block);
 // memset(Data,depth,BF_BLOCK_SIZE);
  CALL_BF(BF_CloseFile(file_desc));
  CALL_BF(BF_UnpinBlock(Block));
  return HT_OK;
}

HT_ErrorCode HT_OpenIndex(const char *fileName, int *indexDesc){
  CALL_BF(BF_OpenFile(fileName,indexDesc));
  for(int i = 0;i < 20; i++)
  {
    if(Array[i].Name.empty())
    {
      Array[i].Name = fileName;
      Array[i].ID = *indexDesc;
      break;
    }
    else if(!Array[i].Name.empty() && i == 19)
      cout<<"The max number of open files has been reached!"<<endl;
  }
  return HT_OK;
}

HT_ErrorCode HT_CloseFile(int indexDesc){
  CALL_BF(BF_CloseFile(Array[indexDesc].ID));
  Array[indexDesc].Name.erase();
  Array[indexDesc].ID = NULL;
  return HT_OK;
}

void reverse_str(string& str)
{
    int n = str.length();
    for (int i = 0; i < n / 2; i++)
        swap(str[i], str[n - i - 1]);
}

string string_to_binary(string S)
{
    string bin = "";
  for(int i = 0;i < S.length(); i++)
  {
    int value = int(S[i]);
    while(value > 0)
    {
      if(value%2)
        bin.push_back('1');
     else
        bin.push_back('0');
      value /= 2;
    } 
  }
  reverse_str(bin);
  return bin;
}

string decimal_to_binary(int Decimal)
{
  string Binary;
  while(Decimal > 0)
  {
    Binary += to_string(Decimal  % 2);
    Decimal /= 2;
  }
  reverse_str(Binary);
  return Binary;
}

HT_ErrorCode HT_InsertEntry(int indexDesc, Record record) 
{
    string ID = decimal_to_binary(record.id);
    string City = string_to_binary(record.city);
    string Surname = string_to_binary(record.surname);
    string Name = string_to_binary(record.name);
    int GlobalDepth = 2;int LocalDepth = 2;
    int BlockCounter,NumRecsInBlock,CurBlockNum;
    bool found;
    char* Data;
    BF_Block *Block;
    NumRecsInBlock = 512 / 59; //blocksize/recsize
    CALL_BF(BF_GetBlockCounter(Array[indexDesc].ID,&BlockCounter));
    if(BlockCounter == 0)
      return HT_ERROR;
    else if(BlockCounter == 1)
    {
      CALL_BF(BF_AllocateBlock(Array[indexDesc].ID,Block)); //thelei unpin
      Data = BF_Block_GetData(Block);
      memset(Data,record.id,4); //proswrino
      memcpy(Data,record.name,15);
      memcpy(Data,record.surname,20);
      memcpy(Data,record.city,20);
      BF_Block_SetDirty(Block);
      CALL_BF(BF_UnpinBlock(Block)); //needs to be here?
    }
    else if(BlockCounter > 1)
    {
      CurBlockNum = BlockCounter - 1;
      CALL_BF(BF_GetBlock(Array[indexDesc].ID,CurBlockNum,Block));
      found = false;
      //how to check how many blocks are in here?
      Data = BF_Block_GetData(Block);
      for(int i = 0;i < NumRecsInBlock; i++)
      {
        if(Data[i*59] == NULL)
        {
          found = true;
          memset(Data,record.id,4); //proswrino
          memcpy(Data,record.name,15);
          memcpy(Data,record.surname,20);
          memcpy(Data,record.city,20);
          BF_Block_SetDirty(Block);
          CALL_BF(BF_UnpinBlock(Block)); //needs to be here?
          break;
        }
      }
      if(found == false) //last block is full
      {
        CALL_BF(BF_AllocateBlock(Array[indexDesc].ID,Block));
        Data = BF_Block_GetData(Block);
        memset(Data,record.id,4); //proswrino
        memcpy(Data,record.name,15);
        memcpy(Data,record.surname,20);
        memcpy(Data,record.city,20);
        BF_Block_SetDirty(Block);
        CALL_BF(BF_UnpinBlock(Block)); //needs to be here?
      }
    }
  return HT_OK;
}

HT_ErrorCode HT_PrintAllEntries(int indexDesc, int *id) {
  int j = 0;
  for(int i = 0;i < 20;i++)
  {
    if(!Array[i].Name.empty())
    {
      if(j == indexDesc)
      {
          int* BlockNum;
          CALL_BF(BF_GetBlockCounter(Array[j].ID,BlockNum));
          BF_Block* Block;
          for(int i = 0;i < *BlockNum; i++)
          {
            CALL_BF(BF_GetBlock(Array[j].ID,i,Block));//to kanei pin
            char* Data = BF_Block_GetData(Block);
            if(id == NULL)
            {
              cout<<"Records of Block : "<< i + 1<<" "<<*Data<<endl;
            }
            else
            {
              cout<<"spera"<<endl;
            }
            CALL_BF(BF_UnpinBlock(Block)); //needs to be here?
          }
      }
    }      
    j++;
  }
  return HT_OK;
}

void BinarySearch() //Kathe bucket einai ena Block?kai to hashing ginetai afou exoume valei to record sto arxeio?
{



}