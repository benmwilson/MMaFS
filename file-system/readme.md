# UNIX-like File System Implementation

Implementation coded by Ben Wilson


## How to Compile

Some tools are required to compile and executre this file system. Please refer to your system package manager, or each tool's website, in order to install.

- The latest version of GCC/G++
- Makefile (see details below)

### Makefile
You must use the provided Makefile to compile the source code. Navigate to the root directory and open a terminal, type `make.exe` to compile the source code.

You will now have `create_fs.exe` and `filesystem.exe` which you can use to run the implementation.

More information on Makefiles can be viewed [here](https://makefiletutorial.com/).

## How to Run the Code

Navigate to the root directory and open a new terminal. Inside this terminal, type `create_fs.exe disk0` to generate a disk.

Type `filesystem.exe <testfilenmame>`, where testfilename is the name of your testfile, to execute its instructions on the disk.

Example: `filesystem.exe sampleinput`

## Implementation

I decided to implement this problem using C++ over C for various reasons, mainly ease and memory management. The files created in the file system are maintained on a digital "disk" file that is 128KB in size. This file system has no subdirectories, just a root directory and supports a maximum of 16 files with the size of a file being 8 blocks; each block being 1KB in size. File names created can be no longer than 8 characters in length.

The first 1KB block is known as the super block, it stores the free block list and index nodes (inode) for each file. The remaining 127 1KB blocks store data blocks of the files on your file system.

The first 128 bytes stores the free block list. Each entry in this list indicates whether the corresponding block is free or in use (if the i-th byte is 0, it indicates that the block is free, else it is in use). Intially all blocks except the super block are free.

Immediately following the free block list are the 16 index nodes, one for each file that is allowed in the file system. Initially, all inode are free.

Each inode stores the following information:
 - char name[8];            //file name
 - int32 size;              // file size (in number of blocks)
 - int32 blockPointers[8];  // direct block pointers
 - int32 used;              // 0 => inode is free; 1 => in us

## Sample Outputs

View a sample output [here](sampleoutput) 

### References

- https://makefiletutorial.com/

