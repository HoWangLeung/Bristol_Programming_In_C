#include "Functions/nlab.h"
// #define BIGSTR 1000
 
       
int main(int argc, char *argv[])
{ 
    if (argc != 2)
    {
        fprintf(stderr, "Usage : %s <path/file.nlb> \n", argv[0]);
        exit(EXIT_FAILURE);
    }
    Program *p = ncalloc(1, sizeof(Program));
    FILE *file_pointer = h_open(argv[1]);
    // printf("GET POINTER\n");
    read_file(file_pointer, p);
    PROG(p);
    fclose(file_pointer);
    clean_up(p);
    return 0;
}
