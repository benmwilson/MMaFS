<h1 align="center">
  Memory Management and File Systems
</h1>
<p align="center">
  
</p>

<p align="center">
This project has two parts, one on memory management and one on file systems. The first component of the project takes a sequence of virtual addresses and extract the page number and offset for each address using bit-wise operations. The second component is a simple UNIX-like file system that resides on a disk that is 128KB in size.
  
</p> 

<p align="center">
  🚧
 This code was developed for the COSC 315 Operating Systems course at the University of British Columbia Okanagan.
  🚧
</p>

<br><br>

## Table of Contents

- [Project Outline](#project-outline)
- [Design Choices](#design-choices)
- [How To Run](#how-to-run)
- [Contributors](#contributors)

### Project Outline

Part I: Memory management & Paging 

The purpose of this component is to implement a portion of the 
virtual to physical address translation in a pure paging based scheme. The goal is to 
write a program that takes a sequence of virtual addresses and extract the page number 
and offset for each address using bit-wise operations.

Part II: File Systems 

The goal of this component is to write a simple UNIX-like file system. The file system must follow these assumptions: 
 - The file system resides on a disk that is 128KB in size.
 - There is only one root directory. No subdirectories are allowed.
 - The file system supports a maximum of 16 files.
 - The maximum size of a file is 8 blocks; each block is 1KB in size.
 - Each file has a unique name, the file name can be no longer than 8 characters.

### Design Choices

Part I: Memory management & Paging 
  - Create a text file that contains the number of paging and offset bits and test input virtual addresses
  - main function reads in the text file, parsing line by line 
  - function that converts virtual address to physical address has both a page mask and offset mask that keep track of the upper and lower bound of a 16 bit number respectively in order to get the correct "offest" for both the correct binary number for page and offset
  - calculate the page by binary AND operator on the virtual address with the page mask then shifting the bits to the right  
  - calculate the offset by binary AND operator on the virtual address with the offset mask

### How To Run
 Navigate to the part1 folder on the branch part1, then:

    - compile c file
        - $ gcc paging.c -o p 
    - run program
        - $ ./p
 

### Contributors
 - [Ben Wilson](https://github.com/benmwilson)
 - [Eric Shanks](https://github.com/EricShanks68) 
 - [Richardo Brown](https://github.com/Buttertoastt)

