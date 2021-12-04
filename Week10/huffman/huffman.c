// C program for Huffman Coding
#include <stdio.h>
#include <stdlib.h>

// This constant can be avoided by explicitly
// calculating height of Huffman Tree
#define MAX_TREE_HT 100;

struct MinHeapNode {
  
    // One of the input characters
    char data;
  
    // Frequency of the character
    unsigned freq;
  
    // Left and right child of this node
    struct MinHeapNode *left, *right;
};
  

void HuffmanCodes(char data[], int freq[], int size);

void HuffmanCodes(char data[], int freq[], int size)
{
   struct MinHeapNode* root
        = buildHuffmanTree(data, freq, size);

}

// Driver code
int main()
{

    char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freq[] = {5, 9, 12, 13, 16, 45};

    int size = sizeof(arr) / sizeof(arr[0]);

    HuffmanCodes(arr, freq, size);

    return 0;
}