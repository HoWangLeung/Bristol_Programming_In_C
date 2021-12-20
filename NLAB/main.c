

#include "Functions/nlab.h"
// #include "General/general.c"
#define BIGSTR 1000

// bool Prog(Program *p);

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        fprintf(stderr, "Usage : %s <file.nlb> \n", argv[0]);
        exit(EXIT_FAILURE);
    }

    Program *prog = ncalloc(1, sizeof(Program));
    printf("argv [1] = %s\n", argv[1]);
    FILE *file_pointer = h_open(argv[1]);
    read_file(file_pointer, prog);
    PROG(prog);
    printf("<<<<<<<>>>>>>>>> PARSED OK !\n");
    fclose(file_pointer);
    free(prog);

    return 0;
}
