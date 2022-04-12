#include "filesystem.h"
#include <math.h>
#include <vector>
#include <iostream>
#include <signal.h>

using namespace std;

typedef struct idxNode idxNode;

myFileSystem::myFileSystem(char diskName[16])
{
  this->disk.open(diskName, ios::out | ios::in);
}

int myFileSystem::createFile(char fileName[8], int size)
{
  if (!this->disk.is_open()) // disk not open, error
    return -1;

  if (size > 8 || size < 1) // name too large, error
    return -1;

  if (strlen(fileName) > 8 || strlen(fileName) == 0) // invalid name, error
    return -1;

  cout << "[CREATE] Creating filename '" << fileName << "'" << endl;

  this->disk.sync();

  this->disk.seekg(0, disk.beg);
  char buffer[128];

  this->disk.read(buffer, 128); // read first 128 bytes yahoooooo

  vector<int> freeBlocks;

  for (int i = 1; i < 128; i++)
  {
    // scan list
    if (buffer[i] == 0)
      freeBlocks.push_back(i);
    if (freeBlocks.size() >= (size_t)size)
      break;
  }

  if (freeBlocks.size() == 0 || freeBlocks.size() < (size_t)size)
  {

    cout << "[Error] Insufficient free blocks available for file creation!\n";

    return -1; // scanned entire free list and theres no space, error!
  }

  idxNode foundNode;
  int nodePos = -1;

  for (int i = 0; i < 16; i++)
  {

    // begin the read in inode... best of luck

    char tempBuffer[48];
    this->disk.read(tempBuffer, 48);

    memcpy(&foundNode, tempBuffer, sizeof(foundNode));

    // end read in inode... we made it

    if (foundNode.used == 0)
    {
      nodePos = i;
      break;
    }
    else if (i == 15)
    {

      cout << "[Error] No free nodes to create a file\n";

      return -1; // no free inodes :( error
    }
  }

  if (nodePos == -1)
    return -1;

  foundNode.used = 1;
  strncpy(foundNode.name, fileName, 8); // copy the filename
  foundNode.size = size;                // don't forget to copy the file size

  for (int i = 0; i < size; i++)
  {
    foundNode.blockPointers[i] = freeBlocks[i];
    buffer[freeBlocks[i]] = 1;
  }

  this->disk.seekp(0, disk.beg);            // move the pointer to the start of the file
  this->disk.write(buffer, 128);            // write the free block list out to disk
  this->disk.seekp(48 * nodePos, disk.cur); // seek to inode

  char tempBuffer[48];
  memcpy(tempBuffer, &foundNode, sizeof(foundNode));

  this->disk.write(tempBuffer, 48); // write out inode to disk
  this->disk.flush();

  return 1;
}

int myFileSystem::deleteFile(char fileName[8])
{
  if (!this->disk.is_open()) // disk not open, error
    return -1;

  cout << "[DELETE] Deleting filename '" << fileName << "'" << endl;

  this->disk.sync();

  this->disk.seekg(128, disk.beg);

  idxNode foundNode;
  int nodePos = -1;

  for (int i = 0; i < 16; i++)
  {

    // begin read in inode

    char tempBuffer[48];
    this->disk.read(tempBuffer, 48);

    memcpy(&foundNode, tempBuffer, sizeof(foundNode));

    // end read in inode

    if (foundNode.used == 1 && strncmp(foundNode.name, fileName, 8) == 0 && i != 15)
    {
      nodePos = i;
      break;
    }
    else if (i == 15)
    {
      if (foundNode.used && strncmp(foundNode.name, fileName, 8) == 0)
      {
        nodePos = i; // reached end, found matching inode
        break;
      }
      else
      {

        cout << "[Error] No matching nodes to delete!\n";

        return -1; // could not find despite searching everywhere.... error
      }
    }
  }

  this->disk.seekg(0, disk.beg); // move zee pointer
  char buffer[128];

  this->disk.read(buffer, 128); // read first 128 bytes

  for (int i = 0; i < foundNode.size; i++)
  {
    buffer[foundNode.blockPointers[i]] = 0;
  }

  foundNode.used = 0;

  this->disk.seekp(0, disk.beg);
  this->disk.write(buffer, 128);
  this->disk.seekp(48 * nodePos, disk.cur);

  char tempBuffer[48];
  memcpy(tempBuffer, &foundNode, sizeof(foundNode));

  this->disk.write(tempBuffer, 48);
  this->disk.flush();
  return 1;
}

int myFileSystem::listFiles()
{
  if (!this->disk.is_open())
    return -1;

  this->disk.sync();

  this->disk.seekg(128, disk.beg);

  cout << endl
       << endl
       << "[LIST] Listing Files..." << endl;

  for (int i = 0; i < 16; i++)
  {

    // begin read in inode
    idxNode foundNode;
    char tempBuffer[48];
    this->disk.read(tempBuffer, 48);

    memcpy(&foundNode, tempBuffer, sizeof(foundNode));

    // end read in inode

    if (foundNode.used == 1)
    {
      cout << foundNode.name << ", size: " << foundNode.size << endl;
    }
  }

  return 1;
};

int myFileSystem::readFromBlock(char fileName[8], int blockNum, char buf[1024])
{
  if (!this->disk.is_open())
    return -1;

  cout << "[READ] Reading filename '" << fileName << "', blockNum: " << blockNum << endl;

  this->disk.sync();

  this->disk.seekg(128, disk.beg);

  idxNode foundNode;
  int nodePos = -1;

  for (int i = 0; i < 16; i++)
  {

    char tempBuffer[48];
    this->disk.read(tempBuffer, 48);

    memcpy(&foundNode, tempBuffer, sizeof(foundNode));

    if (foundNode.used == 1 && strncmp(foundNode.name, fileName, 8) == 0 && i != 15)
    {
      nodePos = i;
      break;
    }
    else if (i == 15)
    {
      if (foundNode.used && strncmp(foundNode.name, fileName, 8) == 0)
      {
        nodePos = i; // reached end and found matching inode
        break;
      }
      else
      {

        cout << "[Error] No matching node to read!\n";

        return -1;
      }
    }
  }

  if (blockNum >= foundNode.size)
  {

    cout << "[Error] Blocknum exceeds size of node.\n";

    return -1;
  }

  int offset = foundNode.blockPointers[blockNum] * block_size;

  cout << "[READ] Read pointer: " << foundNode.blockPointers[blockNum] << ", offset: "
       << offset << endl;

  this->disk.seekg(offset, disk.beg);
  this->disk.read(buf, block_size);

  return 1;
}

int myFileSystem::writeToBlock(char fileName[8], int blockNum, char buf[1024])
{
  if (!this->disk.is_open())
    return -1;

  cout << "[READ] Reading filename '" << fileName << "', blockNum: " << blockNum << endl;

  this->disk.sync();

  this->disk.seekg(128, disk.beg);

  idxNode foundNode;
  int nodePos = -1;

  for (int i = 0; i < 16; i++)
  {

    char tempBuffer[48];
    this->disk.read(tempBuffer, 48);

    memcpy(&foundNode, tempBuffer, sizeof(foundNode));

    if (foundNode.used == 1 && strncmp(foundNode.name, fileName, 8) == 0 && i != 15)
    {
      nodePos = i;
      break;
    }
    else if (i == 15)
    {
      if (foundNode.used && strncmp(foundNode.name, fileName, 8) == 0)
      {
        nodePos = i;
        break;
      }
      else
      {

        cout << "[Error] No matching node to read\n";
        return -1;
      }
    }
  }

  if (blockNum >= foundNode.size)
  {

    cout << "[Error] Blocknum exceeds size of node.\n";

    return -1;
  }

  int offset = foundNode.blockPointers[blockNum] * block_size;

  cout << "[WRITE] Write pointer: " << foundNode.blockPointers[blockNum] << ", offset: "
       << offset << endl;

  this->disk.seekp(offset, disk.beg);
  this->disk.write(buf, block_size);

  this->disk.flush();

  return 1;
}

int myFileSystem::closeDisk()
{
  disk.close();
  return 1;
}
