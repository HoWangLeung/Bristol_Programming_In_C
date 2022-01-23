#include "Functions/nlab.h"
       
int main(int argc, char *argv[])
{ 
    if (argc != 2)
    {
        fprintf(stderr, "Usage : %s <path_to_file/file.nlb> \n", argv[0]);
        exit(EXIT_FAILURE);
    }
    Program *p = ncalloc(1, sizeof(Program));
    FILE *file_pointer = h_open(argv[1]);
    read_file(file_pointer, p);
    PROG(p);
    fclose(file_pointer);
    clean_up(p);
    return 0;
}
