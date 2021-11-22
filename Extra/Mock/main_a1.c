/*
   Returns a Boolean, depending upon whether the
   string s1 is composed entirely from characters that
   occur in s2 or not.
*/

#include "common.h"

bool struses(const char* s1, const char* s2);

int main(void)
{

   /* What words can you make using only the
      Top line of a traditional qwerty keyboard ?*/
   assert(struses("perpetuity", "qwertyuiop"));
   assert(struses("PERPETUITY", "QWERTYUIOP"));
   assert(struses("typewriter", "qwertyuiop"));
   assert(struses("", "qwertyuiop"));

   //printf("res = %d\n ",struses("printers", "qwertyuiop"));

    assert(!struses("printers", "qwertyuiop"));
   assert(!struses("typist", "qwertyuiop"));
   assert(!struses("typist", "qwertyuiop"));

   // /* Middle Line */
   assert(struses("alfalfas", "asdfghjkl"));
   assert(struses("galahads", "asdfghjkl"));

   assert(!struses("goldilocks", "asdfghjkl"));
   assert(!struses("darkness", "asdfghjkl"));

   assert(!struses("sdm,nc,ncd|SDFKSKO$$W", ""));

   return 0;
}

