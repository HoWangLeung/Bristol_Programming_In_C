#include "../test.h"
void get_binaryop_data(Program *p, int test_number);
void get_cols_data(Program *p, int test_number);


void get_parser_data(Program *p, int test_number, char *func_name)
{
  
    if (strcmp(func_name, "PROG") == 0)
    {
        // printf("IN PROG GET PARASE DATA\n");
     
    }

    if (strcmp(func_name, "INSTRCLIST") == 0)
    {
     
    }
    if (strcmp(func_name, "VARNAME") == 0)
    {
      
    }

    if (strcmp(func_name, "INTEGER") == 0)
    {
       
    }

    if (strcmp(func_name, "INSTRC") == 0)
    {
      
    }

    if (strcmp(func_name, "SET") == 0)
    {

       
    }

    if (strcmp(func_name, "PRINT") == 0)
    {

      
    }

    if (strcmp(func_name, "CREATE") == 0)
    {
printf("CREATEE>>>>>>>>\n");
        char test_instructions[ARR_RANGE][ARR_RANGE] = {
            {"ONES 6 5 $A"},             //0: valid
            {"ONES 6 5"},                //1: invalid, missing varname
            {"ONES 6 $A "},              //2: invalid, missing col or row
            {"READ \"Data/lglider.arr\" $A"}, //3: valid
            {"READ \"Data/lglider.arr\""},    //4: invalid, missing varname
            {"READ  $A"},                //5: invalid, missing filename
            {"PRINT \"Data/lglider.arr"},     //6: invalid,missing a double quote on the right
        };

        copy_test_data(p, test_instructions, test_number);
    }

    if (strcmp(func_name, "LOOP") == 0)
    {

     
    }

    if (strcmp(func_name, "POLISHLIST") == 0)
    {

        
    }

    if (strcmp(func_name, "POLISH") == 0)
    {

       
    }

    if (strcmp(func_name, "PUSHDOWN") == 0)
    {

   
    }

    if (strcmp(func_name, "UNARYOP") == 0)
    {

  
    }

    if (strcmp(func_name, "STRING") == 0)
    {

    
    }

    if (strcmp(func_name, "BINARYOP") == 0)
    {

       get_binaryop_data(p,test_number);
    }

    if (strcmp(func_name, "ROWS") == 0)
    {

        
    }

    if (strcmp(func_name, "COLS") == 0)
    {

       get_cols_data(p,test_number);
    }

    if (strcmp(func_name, "FILENAME") == 0)
    {

   
    }
}
