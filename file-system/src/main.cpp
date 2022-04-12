#include "filesystem.h"

int main(int argc, char *argv[])
{

  // incorrect syntax catch
  if (argc == 1)
  {
    fprintf(stderr, "[Error] Improper Syntax: %s <testfile name> \n", argv[0]);
    exit(0);
  }

  char eachLine[100]; // each line from textfile
  char *cmd[3];       // command
  int cmdCounter;     // count for command
  char *cmdParts;     // each part of command
  char buffer[1024];

  for (int i = 0; i < 1024; i++)
  {
    buffer[i] = '1';
  }

  ifstream inputfile(argv[1]);

  myFileSystem f((char *)"disk0"); // create the disk object

  if (inputfile.is_open())
  {
    while (inputfile.getline(eachLine, 100))
    {
      cmdCounter = 0;
      cmdParts = strtok(eachLine, " ");
      while (cmdParts != NULL)
      {
        cmd[cmdCounter] = cmdParts;
        cmdCounter++;
        cmdParts = strtok(NULL, " ");
      }

      // select correct operator for each parsed out command
      switch (*cmd[0])
      {
      case 'C':
      {
        f.createFile((char *)cmd[1], atoi(cmd[2]));
        // printf("Create called");
        break;
      }
      case 'D':
      {
        f.deleteFile((char *)cmd[1]);
        // printf("Delete called");
        break;
      }
      case 'L':
      {
        f.listFiles();
        // printf("List called");
        break;
      }
      case 'R':
      {
        f.readFromBlock((char *)cmd[1], atoi(cmd[2]), buffer);
        // printf("Read called");
        break;
      }
      case 'W':
      {
        f.writeToBlock((char *)cmd[1], atoi(cmd[2]), buffer);
        // printf("Write called");
        break;
      }
      default:
      {
        printf("%s\n", cmd[0]);
        break;
      }
      }
    }
  }
  f.closeDisk();
  return 0;
}
