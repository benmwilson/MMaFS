## Part I: Memory management & Paging 

The purpose of this component is to implement a portion of the 
virtual to physical address translation in a pure paging based scheme. The goal is to 
write a program that takes a sequence of virtual addresses and extract the page number 
and offset for each address using bit-wise operations.

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

### Resources
  - https://www.cprogramming.com/tutorial/bitwise_operators.html
  - https://www.learn-c.org/en/Bitmasks
  - https://solarianprogrammer.com/2019/04/03/c-programming-read-file-lines-fgets-getline-implement-portable-getline/

