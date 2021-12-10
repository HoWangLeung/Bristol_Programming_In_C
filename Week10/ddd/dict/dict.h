#pragma once

#include "general.h"

typedef struct dict dict;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>

/* The maximum number of words we will want to input.
   Exact : Hashtable will be twice this size
   Approx : Hashtable will be (e.g.) 20 times this size
*/
dict* dict_init(unsigned int maxwords);

/* Add string to dictionary
   Exact : A deep-copy is stored in the hashtable only if the word
           has not already been added to the table.
   Approx : Multiple hashes (e.g. 11) are computed and corresponding
            Boolean flags set in the Bloom hashtable. 
*/
bool dict_add(dict* x,  const char* s);

/* Returns true if the word is already in the dictionary,
   false otherwise.
*/
bool dict_spelling(dict* x, const char* s);

/* Frees all space used */
void dict_free(dict* x);
