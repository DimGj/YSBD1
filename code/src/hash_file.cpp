#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;

#include "bf.h"
#include "hash_file.h"
#define MAX_OPEN_FILES 20

#define CALL_BF(call)       \
{                           \
  BF_ErrorCode code = call; \
  if (code != BF_OK) {       \
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
  int file_desc;BF_Block* Block;
  CALL_BF(BF_CreateFile(filename));
  CALL_BF(BF_OpenFile(filename,&file_desc)); //epistrfei to id sto file desc

  CALL_BF(BF_AllocateBlock(file_desc,Block)); //meta thelei unpin,epistrfei to block sth metavlith block
  int StartingDepth = depth;
  //what else needs to happen here?
  //Where does depth go?
  return HT_OK;
}

HT_ErrorCode HT_OpenIndex(const char *fileName, int *indexDesc){
  BF_Block* Block;
  char* ch;
  CALL_BF(BF_OpenFile(fileName,indexDesc));
  if(indexDesc < 0)
    return HT_ERROR;
  else{
    
  }
  //insert code here
  return HT_OK;
}

HT_ErrorCode HT_CloseFile(int indexDesc) { //check if Records in the file changed?
  //insert code here
  return HT_OK;
}

HT_ErrorCode HT_InsertEntry(int indexDesc, Record record) {
  //insert code here
  return HT_OK;
}

HT_ErrorCode HT_PrintAllEntries(int indexDesc, int *id) {
  //insert code here
  return HT_OK;
}
