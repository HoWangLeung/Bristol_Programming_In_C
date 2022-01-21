#include "../../test.h"

void get_polishlist_data(Program *p, int test_number);
void get_polishlist_data(Program *p, int test_number)
{
        clear_previous_data(p);
        char test_instructions[ARR_RANGE][ARR_RANGE] = {
            //========================================
            //=====<testcase No.>:<description>=======
            //========================================
            {";"},              //0:Valid
            {"$A ;"},           //1:Valid
            {"5 ;"},            //2:Valid
            {"B-ADD ;"},        //3:Valid
            {"B-AND ;"},        //4:Valid
            {"B-OR ;"},         //5:Valid
            {"B-GREATER ;"},    //6:Valid
            {"B-LESS ;"},       //7:Valid
            {"B-EQUALS ;"},     //8:Valid
            {"U-NOT ;"},        //9:Valid
            {"U-EIGHTCOUNT ;"}, //10:Valid
            {"B-EIGHTCOUNT ;"}, //11:Invalid
            {"B-NOT ;"},        //12:Invalid
            {"U-ADD ;"},        //13:Invalid
            {"U-AND ;"},        //14:Invalid
            {"U-OR ;"},         //15:Invalid
            {"U-GREATER ;"},    //16:Invalid
            {"U-LESS ;"},       //17:Invalid
            {"U-EQUALS ;"},     //18:Invalid
            {"$AB ;"},          //19:Invalid
            {"-20 ;"},          //20:Invalid, positive number only
        };
        copy_test_data(p, test_instructions, test_number);
}

void test_polishlist(Program *p)
{
        get_polishlist_data(p, 0);
        assert(POLISHLIST(p));

        get_polishlist_data(p, 1);
        assert(POLISHLIST(p));

        get_polishlist_data(p, 2);
        assert(POLISHLIST(p));

        get_polishlist_data(p, 3);
        assert(POLISHLIST(p));

        get_polishlist_data(p, 4);
        assert(POLISHLIST(p));

        get_polishlist_data(p, 5);
        assert(POLISHLIST(p));

        get_polishlist_data(p, 6);
        assert(POLISHLIST(p));

        get_polishlist_data(p, 7);
        assert(POLISHLIST(p));

        get_polishlist_data(p, 8);
        assert(POLISHLIST(p));

        get_polishlist_data(p, 9);
        assert(POLISHLIST(p));

        get_polishlist_data(p, 10);
        assert(POLISHLIST(p));

        get_polishlist_data(p, 11);
        assert(!POLISHLIST(p));

        get_polishlist_data(p, 12);
        assert(!POLISHLIST(p));

        get_polishlist_data(p, 13);
        assert(!POLISHLIST(p));

        get_polishlist_data(p, 14);
        assert(!POLISHLIST(p));

        get_polishlist_data(p, 15);
        assert(!POLISHLIST(p));

        get_polishlist_data(p, 16);
        assert(!POLISHLIST(p));

        get_polishlist_data(p, 17);
        assert(!POLISHLIST(p));

        get_polishlist_data(p, 18);
        assert(!POLISHLIST(p));

        get_polishlist_data(p, 19);
        assert(!POLISHLIST(p));

        get_polishlist_data(p, 20);
        assert(!POLISHLIST(p));
}
