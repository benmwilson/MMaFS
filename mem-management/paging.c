
#include <stdio.h>       
#include <stdlib.h> 
#include <time.h>

//compute the page number and offset
void get_offset_and_page( int offset, int page_number, unsigned int virtual_address, int virtual_adress_i ) {


    int i = virtual_adress_i - 1;
    //mask for both page and offset act as a kind of "offset"
    int page_mask = 65535; //65535
    int offset_mask = 255; //255

    int ex_off; int ex_page;
    
    //calculate page number and offset number
    ex_page = (virtual_address & page_mask) >> page_number;
    ex_off = (virtual_address & offset_mask) ;
    printf("virtual address %d is in page: %d and offset: %d \n", i, ex_page, ex_off);
}

int main(int argc, char* argv[])
{

    int address_array[20];
   FILE *file;
   char output[255];

   file = fopen("input.txt", "r");

    int line_number = 0;

int n;
int m;

//16bit unsigned between 256- 65535
unsigned int addr = 2356;
    
    //read file line by line where first 2 lines are page and offset bits, and rest are virtual addresses
    while (fgets(output, sizeof(output), file) !=NULL) {

        // printf("%d\n", atoi(output));
        if(line_number == 0){
            n = atoi(output);
        } else if(line_number == 1){
            m = atoi(output);
        } else{
            addr = atoi(output);
            get_offset_and_page(n,m,addr,line_number);
        }
         
         line_number++;
    }
    
    fclose(file);

return 0;
}
