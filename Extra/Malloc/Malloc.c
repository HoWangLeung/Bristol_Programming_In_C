#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 5
#define START_SIZE 2
#define SCALE_FACTOR 3
/* A program to read the contents of a file into a dynamically allocated array */
// Open the file 'filename' to read and return corresponding pointer
FILE *h_open(char *filename);
// Returns contents of file associated with 'file_pointer' in the form of an array of strings
char **read_file(FILE *file_pointer);
// Returns a malloc'd array of size START_SIZE after checking for null pointer
char **init_words_list(void);
// Returns a pointer to a strings array with the same contents of 'words_list' or size 'newsize' after checking for null pointer
char **h_realloc(char **words_list, int newsize);
// Returns pointer to 'size' amount of space after checking for null pointer
void *h_malloc(int size);
// Prints each string in the given array one per line
void print_words(char **words_list);
// Frees all char*'s in the given array and then the array pointer
void free_list(char **words_list);

int main(void)
{
    char *filename = "34words.txt";
    FILE *file_pointer = h_open(filename);
    char **words_list = read_file(file_pointer);
    print_words(words_list);
    free_list(words_list);
    fclose(file_pointer);
    return 0;
}

FILE *h_open(char *filename)
{
    FILE *file_pointer = fopen(filename, "r");
    if (!file_pointer)
    {
        perror("Couldn't dopen file\n");
    }
    return file_pointer;
}

char **read_file(FILE *file_pointer)
{
    // Buffer is a 1D array of chars we use to store each string from the file in turn
    char buffer[BUFF_SIZE];
    // Words_list is where we store the file contents in memory
    char **words_list = init_words_list();
    // Ned to keep track of how many words we have stored to prevent overflowing the array
    int word_count = 0;
    // Need to keep track of how big the array is
    int storage_space = START_SIZE;
    // Not strictly necessary variable, but useful in writing clear code
    int newsize;

    // Loop thorugh file reading one string at a time into the buffer, overwriting the buffer each time
    while (fscanf(file_pointer, "%s", buffer) != EOF)
    {
        // have we run out of space?

        if (word_count >= storage_space - 1)
        {
            // printf("buffer = %s\n", buffer);
            // printf("word count = %d\n", word_count);
            // printf("storage_space = %d\n", storage_space);
            // printf("*************************************");
            // Get value for new size by multiplying the current size by a SCALEFACTOR
            newsize = storage_space * SCALE_FACTOR;
            // Allocate space for more words and keep the words we've saved
            words_list = h_realloc(words_list, newsize);
            // Update the storage space available
            storage_space = newsize;
        }
        // Allocate space for the string we've just read into the buffer
        words_list[word_count] = (char *)h_malloc(sizeof(char) * strlen(buffer) + 1);
        // Copy value from buffer into the words_list
        strcpy(words_list[word_count], buffer);
        // Increment the counter
        word_count++;
    }

    // print_words() and free_list() rely on void pointers to break the loop
    // If array is full then no void pointers. Need to allocate one more space
    if (word_count == storage_space)
    {
        words_list = h_realloc(words_list, ++storage_space);
    }
    return words_list;
}

char **init_words_list(void)
{
    char **words_list = (char **)malloc(sizeof(char *) * START_SIZE);
    if (!words_list)
    {
        perror("Couldn't initialise the words list array.");
    }
    return words_list;
}

char **h_realloc(char **words_list, int newsize)
{
    char **new_words_list = realloc(words_list, sizeof(char *) * newsize);
    if (!new_words_list)
    {
        perror("Couldn't allocate space for words list.");
    }
    return new_words_list;
}

void *h_malloc(int size)
{
    void *ptr = malloc(size);
    if (!ptr)
    {
        perror("Couldn't allocate space");
    }
    return ptr;
}

void print_words(char **words_list)
{
    int i = 0;
    while (words_list[i])
    {
        // printf("%s\n", words_list[i++]);
    }
}

void free_list(char **words_list)
{
    int i = 0;
    while (words_list[i])
    {
        free(words_list[i++]);
    }
    free(words_list);
}
