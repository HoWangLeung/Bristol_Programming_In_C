#include "../../test.h"
void get_varname_data(Program *p, int test_number);
void get_varname_data(Program *p, int test_number)
{
        clear_previous_data(p);
        char test_instructions[ARR_RANGE][ARR_RANGE] = {
            //========================================
            //=====<testcase No.>:<description>=======
            //========================================
            {"$ABCDEFG"}, //0:Invalid
            {"$A"},       //1:Valid
            {"$B"},       //2:Valid
            {"$C"},       //3:Valid
            {"$D"},       //4:Valid
            {"$E"},       //5:Valid
            {"$F"},       //6:Valid
            {"$G"},       //7:Valid
            {"$H"},       //8:Valid
            {"$I"},       //9:Valid
            {"$J"},       //10:Valid
            {"$K"},       //11:Valid
            {"$L"},       //12:Valid
            {"$M"},       //13:Valid
            {"$N"},       //14:Valid
            {"$O"},       //15:Valid
            {"$P"},       //16:Valid
            {"$Q"},       //17:Valid
            {"$R"},       //18:Valid
            {"$S"},       //19:Valid
            {"$T"},       //20:Valid
            {"$U"},       //21:Valid
            {"$V"},       //22:Valid
            {"$W"},       //23:Valid
            {"$X"},       //24:Valid
            {"$Y"},       //25:Valid
            {"$Z"},       //26:Valid
            {"$1"},       //27: invalid: not A-Z
            {"$@"},       //28: invalid: not A-Z
            {"$!"},       //29: invalid: not A-Z
            {"*1"},       //30: invalid: expected '$' but received '*'
            {"*@"},       //31: invalid: expected '$' but received '*'
            {"1"},        //32: invalid: missing '$'
        };
        copy_test_data(p, test_instructions, test_number);
}
void test_varname(Program *p)
{
        get_varname_data(p, 0);
        assert(!VARNAME(p));

        get_varname_data(p, 1);
        assert(VARNAME(p));

        get_varname_data(p, 2);
        assert(VARNAME(p));

        get_varname_data(p, 3);
        assert(VARNAME(p));

        get_varname_data(p, 4);
        assert(VARNAME(p));

        get_varname_data(p, 5);
        assert(VARNAME(p));

        get_varname_data(p, 6);
        assert(VARNAME(p));

        get_varname_data(p, 7);
        assert(VARNAME(p));

        get_varname_data(p, 8);
        assert(VARNAME(p));

        get_varname_data(p, 9);
        assert(VARNAME(p));

        get_varname_data(p, 10);
        assert(VARNAME(p));

        get_varname_data(p, 11);
        assert(VARNAME(p));

        get_varname_data(p, 12);
        assert(VARNAME(p));

        get_varname_data(p, 13);
        assert(VARNAME(p));

        get_varname_data(p, 14);
        assert(VARNAME(p));

        get_varname_data(p, 15);
        assert(VARNAME(p));

        get_varname_data(p, 16);
        assert(VARNAME(p));

        get_varname_data(p, 17);
        assert(VARNAME(p));

        get_varname_data(p, 18);
        assert(VARNAME(p));

        get_varname_data(p, 19);
        assert(VARNAME(p));

        get_varname_data(p, 20);
        assert(VARNAME(p));

        get_varname_data(p, 21);
        assert(VARNAME(p));

        get_varname_data(p, 22);
        assert(VARNAME(p));

        get_varname_data(p, 23);
        assert(VARNAME(p));

        get_varname_data(p, 24);
        assert(VARNAME(p));

        get_varname_data(p, 25);
        assert(VARNAME(p));

        get_varname_data(p, 26);
        assert(VARNAME(p));

        get_varname_data(p, 27);
        assert(!VARNAME(p));

        get_varname_data(p, 28);
        assert(!VARNAME(p));

        get_varname_data(p, 29);
        assert(!VARNAME(p));

        get_varname_data(p, 30);
        assert(!VARNAME(p));

        get_varname_data(p, 31);
        assert(!VARNAME(p));

        get_varname_data(p, 32);
        assert(!VARNAME(p));
}
