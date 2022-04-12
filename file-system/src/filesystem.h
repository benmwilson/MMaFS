#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>

using namespace std;

#define block_size 1024

// structure for the inode
struct idxNode
{
  char name[8];         // file name
  int size;             // file size (in number of blocks)
  int blockPointers[8]; // direct block pointers
  int used;             // 0 => inode is free; 1 => in use
};

class myFileSystem
{
private:
  fstream disk;

public:
  myFileSystem(char diskName[16]);

  int createFile(char name[8], int size);
  int deleteFile(char name[8]);
  int listFiles();
  int readFromBlock(char name[8], int blockNum, char buf[1024]);
  int writeToBlock(char name[8], int blockNum, char buf[1024]);
  int closeDisk();
};
