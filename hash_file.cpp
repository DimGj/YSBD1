#include <iostream>

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
typedef struct FileArray
{
  string Name;
  string Type;
  string GeneralInfo;
}FileArray;

FileArray* Array;

HT_ErrorCode HT_Init() {
  BF_Block *Block;
  Array = new FileArray[20];
  BF_Block_Init(&Block);
  return HT_OK;
}

HT_ErrorCode HT_CreateIndex(const char *filename, int depth) {
  CALL_BF(BF_CreateFile(filename));
  BF_Init(LRU);
  int StartingDepth = depth;
  //what else needs to happen here?
  //Where does depth go?
  return HT_OK;
}

HT_ErrorCode HT_OpenIndex(const char *fileName, int *indexDesc){
  CALL_BF(BF_OpenFile(fileName,indexDesc));
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

