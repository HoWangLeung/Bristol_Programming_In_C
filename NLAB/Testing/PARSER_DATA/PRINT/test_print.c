#include "../../test.h"

void get_print_data(Program *p, int test_number);
void get_print_data(Program *p, int test_number)
{
        clear_previous_data(p);
        char test_instructions[ARR_RANGE][ARR_RANGE] = {
            //========================================
            //=====<testcase No.>:<description>=======
            //========================================
            {"PRINT $A"},           //0:Valid
            {"PRINT \"WORD\""},     //1:Valid
            {"PRINT \"WORD"},       //2:invalid
            {"PRINT $@"},           //3:invalid
            {"PRINT \"!@#^^^^!\""}, //4:Valid
            {"PRINT \"12345\""},    //5:Valid
            {"PRINT \"1@3!5\""},    //6:Valid
            {"PRINT $B"},           //7:Valid
            {"PRINT $C"},           //9:Valid
            {"PRINT $D"},           //10:Valid
            {"PRINT $E"},           //11:Valid
            {"PRINT $F"},           //12:Valid
            {"PRINT $G"},           //13:Valid
            {"PRINT $H"},           //14:Valid
            {"PRINT $I"},           //15:Valid
            {"PRINT $J"},           //16:Valid
            {"PRINT $K"},           //17:Valid
            {"PRINT $L"},           //18:Valid
            {"PRINT $M"},           //19:Valid
            {"PRINT $N"},           //20:Valid
            {"PRINT $O"},           //21:Valid
            {"PRINT $P"},           //22:Valid
            {"PRINT $Q"},           //23:Valid
            {"PRINT $R"},           //24:Valid
            {"PRINT $S"},           //25:Valid
            {"PRINT $T"},           //26:Valid
            {"PRINT $U"},           //27:Valid
            {"PRINT $V"},           //28:Valid
            {"PRINT $W"},           //29:Valid
            {"PRINT $X"},           //30:Valid
            {"PRINT $Y"},           //31:Valid
            {"PRINT $Z"},           //32:Valid
            {"PRINT A"},            //32:InValid
        };

        copy_test_data(p, test_instructions, test_number);
}
void test_print(Program *p)
{
        get_print_data(p, 0);
        assert(PRINT(p));

        get_print_data(p, 1);
        assert(PRINT(p));

        get_print_data(p, 2);
        assert(!PRINT(p));

        get_print_data(p, 3);
        assert(!PRINT(p));

        get_print_data(p, 4);
        assert(PRINT(p));

        get_print_data(p, 5);
        assert(PRINT(p));

        get_print_data(p, 6);
        assert(PRINT(p));

        get_print_data(p, 7);
        assert(PRINT(p));

        get_print_data(p, 8);
        assert(PRINT(p));

        get_print_data(p, 9);
        assert(PRINT(p));

        get_print_data(p, 10);
        assert(PRINT(p));

        get_print_data(p, 11);
        assert(PRINT(p));

        get_print_data(p, 12);
        assert(PRINT(p));

        get_print_data(p, 13);
        assert(PRINT(p));

        get_print_data(p, 14);
        assert(PRINT(p));

        get_print_data(p, 15);
        assert(PRINT(p));

        get_print_data(p, 16);
        assert(PRINT(p));

        get_print_data(p, 17);
        assert(PRINT(p));

        get_print_data(p, 18);
        assert(PRINT(p));

        get_print_data(p, 19);
        assert(PRINT(p));

        get_print_data(p, 20);
        assert(PRINT(p));

        get_print_data(p, 21);
        assert(PRINT(p));

        get_print_data(p, 22);
        assert(PRINT(p));

        get_print_data(p, 23);
        assert(PRINT(p));

        get_print_data(p, 24);
        assert(PRINT(p));

        get_print_data(p, 25);
        assert(PRINT(p));

        get_print_data(p, 26);
        assert(PRINT(p));

        get_print_data(p, 27);
        assert(PRINT(p));

        get_print_data(p, 28);
        assert(PRINT(p));

        get_print_data(p, 29);
        assert(PRINT(p));

        get_print_data(p, 30);
        assert(PRINT(p));

        get_print_data(p, 31);
        assert(PRINT(p));

        get_print_data(p, 32);
        assert(!PRINT(p));
}
