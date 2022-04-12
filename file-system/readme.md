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

I decided to implement this problem using C++ over C.

## Sample Outputs

View a sample output [here](sampleoutput) 

### References

- https://makefiletutorial.com/

