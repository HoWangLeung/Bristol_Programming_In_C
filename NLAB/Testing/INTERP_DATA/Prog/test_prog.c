#include "../../test.h"
void get_interp_prog_data(Program *p, int test_number);
void get_interp_prog_data(Program *p, int test_number)
{
    clear_previous_data(p);
    char test_instructions[ARR_RANGE][ARR_RANGE] = {
        {"BEGIN { \
            SET $A := 5 ;\
         PRINT $A }"},                                             //0: valid
        {"BEGIN { \
            PRINT $A }"},                                          //1: Invalid, $A is undefined
        {"BEGIN }"},                                               //2: Invalid , missing {
        {"BEGIN { SET $Z := 9 ; }"},                               //3: valid
        {"BEGIN { SET $A := 5 ; PRINT $B }"},                      //4: Invalid, $A is set but $B is undefined
        {"BEGIN {  PRINT $C SET $C := 5 ; }"},                     //5: Invalid, print $C before $C is set
        {"BEGIN {  ONES 3 5 $A   PRINT \"ARRAY:\"  PRINT $A  } "}, //6: valid
        {"BEGIN {  READ \"Data/lglider.arr\" $A  PRINT $A  } "},   //7: valid
        {"BEGIN { SET $B := 9 U-NOT ; }"},                         //8: Valid, U-NOT test
        {"BEGIN { SET $C := 1 U-EIGHTCOUNT ; }"},                  //9: Valid, U-EIGHTCOUNT test
        {"BEGIN { SET $D := 1 ; SET $D := $D 1 B-ADD ; }"},        //10: Valid, B-ADD test
        {"BEGIN { SET $E := 2 ; SET $E := $E 3 B-TIMES ; }"},      //11: Valid, B-TIMES test
        {"BEGIN { SET $F := 2 ; SET $F := $F 2 B-EQUALS ; }"},     //12: Valid, B-EQUALS test
        {"BEGIN { SET $G := 2 ; SET $G := $G 3 B-EQUALS ; }"},     //13: Valid, B-EQUALS test, not equal
        {"BEGIN { SET $H := 4 ; SET $H := $H 3 B-LESS ; }"},       //14: Valid, B-LESS test,true
        {"BEGIN { SET $I := 2 ; SET $I := $I 3 B-LESS ; }"},       //15: Valid, B-LESS test,false
        {"BEGIN { SET $J := 3 ; SET $J := $J 3 B-LESS ; }"},       //16: Valid, B-LESS test,equal case
        {"BEGIN { SET $K := 4 ; SET $K := $K 3 B-GREATER ; }"},    //17: Valid, B-GREATER test,true
        {"BEGIN { SET $L := 2 ; SET $L := $L 3 B-GREATER ; }"},    //18: Valid, B-GREATER test,false
        {"BEGIN { SET $M := 3 ; SET $M := $M 3 B-GREATER ; }"},    //19: Valid, B-GREATER test,equal case
        {"BEGIN { SET $N := 3 ; SET $N := $N 3 B-AND ; }"},        //20: Valid, B-AND test,equal case
        {"BEGIN { SET $O := 5 ; SET $O := $O 120 B-AND ; }"},      //21: Valid, B-AND test,equal case
        {"BEGIN { SET $P := 5 ; SET $P := $P 55 B-AND ; }"},       //22: Valid, B-AND test,equal case
        {"BEGIN { SET $Q := 5 ; SET $Q := $Q 3 B-OR ; }"},         //23: Valid, B-OR test,equal case
        {"BEGIN { SET $R := 5 ; SET $R := $R 120 B-OR ; }"},       //24: Valid, B-OR test,equal case
        {"BEGIN { SET $S := 5 ; SET $S := $S 55 B-OR ; }"},        //25: Valid, B-OR test,equal case
        {"BEGIN { SET $T := 100 ; SET $T := $T 200 B-ADD ; }"},    //26: Valid, B-ADD test
        {"BEGIN { SET $U := 1000 ; SET $U := $U 2000 B-ADD ; }"},  //27: Valid, B-ADD test
        {"BEGIN { SET $V := 20 ; SET $V := $V 30 B-TIMES ; }"},    //28: Valid, B-TIMES test
        {"BEGIN { SET $W := 200 ; SET $W := $W 30 B-TIMES ; }"},   //29: Valid, B-TIMES test
        {"BEGIN { READ \"Data/lglider.arr\" $A \
         SET $X := $A 2 B-ADD ; }"},                               //30: Valid, B-ADD test
        {"BEGIN { READ \"Data/lblock.arr\" $A \
         SET $Y := $A 200 B-ADD ; }"},                             //31: Valid, B-ADD test
        {"BEGIN { READ \"Data/ltoad.arr\" $A \
         SET $Z := $A 50 B-ADD ; }"},                              //32: Valid, B-ADD test
        {"BEGIN { READ \"Data/lglider.arr\" $A \
         SET $X := $A 2 B-TIMES ; }"},                             //33: Valid, B-TIMES test
        {"BEGIN { READ \"Data/lblock.arr\" $A \
         SET $Y := $A 200 B-TIMES ; }"},                           //34: Valid, B-TIMES test
        {"BEGIN { READ \"Data/ltoad.arr\" $A \
         SET $Z := $A 50 B-TIMES ; }"},                            //35: Valid, B-TIMES test

        {"BEGIN { READ \"Data/lglider.arr\" $A \
         SET $X := $A 1 B-EQUALS ; }"}, //36: Valid, B-EQUALS test
        {"BEGIN { READ \"Data/lblock.arr\" $A \
         SET $Y := $A 1 B-EQUALS ; }"}, //37: Valid, B-EQUALS test
        {"BEGIN { READ \"Data/ltoad.arr\" $A \
         SET $Z := $A 1 B-EQUALS ; }"}, //38: Valid, B-EQUALS test

        {"BEGIN { READ \"Data/lglider.arr\" $A \
         SET $X := $A 1 B-LESS ; }"}, //39: Valid, B-LESS test
        {"BEGIN { READ \"Data/lblock.arr\" $A \
         SET $Y := $A 1 B-LESS ; }"}, //40: Valid, B-LESS test
        {"BEGIN { READ \"Data/ltoad.arr\" $A \
         SET $Z := $A 1 B-LESS ; }"}, //41: Valid, B-LESS test

        {"BEGIN { READ \"Data/lglider.arr\" $A \
         SET $X := $A 1 B-GREATER ; }"}, //42: Valid, B-GREATER test
        {"BEGIN { READ \"Data/lblock.arr\" $A \
         SET $Y := $A 1 B-GREATER ; }"}, //43: Valid, B-GREATER test
        {"BEGIN { READ \"Data/ltoad.arr\" $A \
         SET $Z := $A 1 B-GREATER ; }"}, //44: Valid, B-GREATER test

        {"BEGIN { READ \"Data/lglider.arr\" $A \
         SET $X := $A 12 B-AND ; }"}, //45: Valid, B-AND test
        {"BEGIN { READ \"Data/lblock.arr\" $A \
         SET $Y := $A 12 B-AND ; }"}, //46: Valid, B-AND test
        {"BEGIN { READ \"Data/ltoad.arr\" $A \
         SET $Z := $A 12 B-AND ; }"}, //47: Valid, B-AND test

    };
    copy_test_data(p, test_instructions, test_number);
}
void test_interp_prog(Program *p)
{
    printf("ASSERTIN*\n");
    get_interp_prog_data(p, 0);
    assert(PROG(p));
    assert(p->variables[0].num[0][0] == 5);

    free_struct(p);

    get_interp_prog_data(p, 1);
    assert(!PROG(p));

    get_interp_prog_data(p, 2);
    assert(!PROG(p));

    get_interp_prog_data(p, 3);
    assert(PROG(p));
    free_struct(p);

    get_interp_prog_data(p, 4);
    assert(!PROG(p));
    free_struct(p);

    get_interp_prog_data(p, 5);
    assert(!PROG(p));

    get_interp_prog_data(p, 6);
    assert(PROG(p));
    free_struct(p);

    get_interp_prog_data(p, 7);
    assert(PROG(p));
    free_struct(p);

    get_interp_prog_data(p, 8);
    assert(PROG(p));
    assert(p->variables[1].num[0][0] == -10); //9 U-NOT = -10
    free_struct(p);

    get_interp_prog_data(p, 9);
    assert(PROG(p));
    assert(p->variables[2].num[0][0] == 0); //1 U-EIGHTCOUNT = 0
    free_struct(p);

    get_interp_prog_data(p, 10);
    assert(PROG(p));
    assert(p->variables[3].num[0][0] == 2); //1 U B-ADD = 2
    free_struct(p);

    get_interp_prog_data(p, 11);
    assert(PROG(p));
    assert(p->variables[4].num[0][0] == 6); // B-TIMES = 6
    free_struct(p);

    get_interp_prog_data(p, 12);
    assert(PROG(p));
    assert(p->variables[5].num[0][0] == 1); // B-EQUALS = 1
    free_struct(p);

    get_interp_prog_data(p, 13);
    assert(PROG(p));
    assert(p->variables[6].num[0][0] == 0); // B-EQUALS = 1
    free_struct(p);

    get_interp_prog_data(p, 14);
    assert(PROG(p));
    assert(p->variables[7].num[0][0] == 0); // B-LESS = 1
    free_struct(p);

    get_interp_prog_data(p, 15);
    assert(PROG(p));
    assert(p->variables[8].num[0][0] == 1); // B-LESS = 0
    free_struct(p);

    get_interp_prog_data(p, 16);
    assert(PROG(p));
    assert(p->variables[9].num[0][0] == 0); // B-LESS = 0
    free_struct(p);

    get_interp_prog_data(p, 17);
    assert(PROG(p));
    assert(p->variables[10].num[0][0] == 1); // B-LESS = 0
    free_struct(p);

    get_interp_prog_data(p, 18);
    assert(PROG(p));
    assert(p->variables[11].num[0][0] == 0); // B-LESS = 0
    free_struct(p);

    get_interp_prog_data(p, 19);
    assert(PROG(p));
    assert(p->variables[12].num[0][0] == 0); // B-LESS = 0
    free_struct(p);

    get_interp_prog_data(p, 20);
    assert(PROG(p));
    assert(p->variables[13].num[0][0] == 3); // B-LESS = 0
    free_struct(p);

    get_interp_prog_data(p, 21);
    assert(PROG(p));
    assert(p->variables[14].num[0][0] == 0); // B-AND = 0
    free_struct(p);

    get_interp_prog_data(p, 22);
    assert(PROG(p));
    assert(p->variables[15].num[0][0] == 5); // B-AND = 0
    free_struct(p);

    get_interp_prog_data(p, 23);
    assert(PROG(p));
    assert(p->variables[16].num[0][0] == 7); // B-OR = 0
    free_struct(p);

    get_interp_prog_data(p, 24);
    assert(PROG(p));
    assert(p->variables[17].num[0][0] == 125); // B-OR = 0
    free_struct(p);

    get_interp_prog_data(p, 25);
    assert(PROG(p));
    assert(p->variables[18].num[0][0] == 55); // B-OR = 0
    free_struct(p);

    get_interp_prog_data(p, 26);
    assert(PROG(p));
    assert(p->variables[19].num[0][0] == 300); // B-OR = 0
    free_struct(p);

    get_interp_prog_data(p, 27);
    assert(PROG(p));
    assert(p->variables[20].num[0][0] == 3000); // B-OR = 0
    free_struct(p);

    get_interp_prog_data(p, 28);
    assert(PROG(p));
    assert(p->variables[21].num[0][0] == 600); // B-OR = 0
    free_struct(p);

    get_interp_prog_data(p, 29);
    assert(PROG(p));
    assert(p->variables[22].num[0][0] == 6000); // B-OR = 0
    free_struct(p);

    get_interp_prog_data(p, 30);
    assert(PROG(p));
    //======================================================
    //==========TEST B-ADD with lglider.arr ================
    //======================================================
    for (int y = 0; y < p->variables[0].y; y++)
    {
        for (int x = 0; x < p->variables[0].x; x++)
        {
            assert(p->variables[23].num[y][x] == p->variables[0].num[y][x] + 2);
        }
    }
    free_struct(p);

    get_interp_prog_data(p, 31);
    assert(PROG(p));
    //======================================================
    //==========TEST B-ADD with lglider.arr ================
    //======================================================
    for (int y = 0; y < p->variables[0].y; y++)
    {
        for (int x = 0; x < p->variables[0].x; x++)
        {
            assert(p->variables[24].num[y][x] == p->variables[0].num[y][x] + 200);
        }
    }
    free_struct(p);

    get_interp_prog_data(p, 32);
    assert(PROG(p));
    //======================================================
    //==========TEST B-ADD with lglider.arr ================
    //======================================================
    for (int y = 0; y < p->variables[0].y; y++)
    {
        for (int x = 0; x < p->variables[0].x; x++)
        {
            assert(p->variables[25].num[y][x] == p->variables[0].num[y][x] + 50);
        }
    }
    free_struct(p);

    get_interp_prog_data(p, 33);
    assert(PROG(p));
    //======================================================
    //==========TEST B-ADD with lglider.arr ================
    //======================================================
    for (int y = 0; y < p->variables[0].y; y++)
    {
        for (int x = 0; x < p->variables[0].x; x++)
        {
            assert(p->variables[23].num[y][x] == p->variables[0].num[y][x] * 2);
        }
    }
    free_struct(p);

    get_interp_prog_data(p, 34);
    assert(PROG(p));
    //======================================================
    //==========TEST B-ADD with lglider.arr ================
    //======================================================
    for (int y = 0; y < p->variables[0].y; y++)
    {
        for (int x = 0; x < p->variables[0].x; x++)
        {
            assert(p->variables[24].num[y][x] == p->variables[0].num[y][x] * 200);
        }
    }
    free_struct(p);

    get_interp_prog_data(p, 35);
    assert(PROG(p));
    //======================================================
    //==========TEST B-ADD with lglider.arr ================
    //======================================================
    for (int y = 0; y < p->variables[0].y; y++)
    {
        for (int x = 0; x < p->variables[0].x; x++)
        {
            assert(p->variables[25].num[y][x] == p->variables[0].num[y][x] * 50);
        }
    }
    free_struct(p);

    get_interp_prog_data(p, 36);
    assert(PROG(p));
    //======================================================
    //==========TEST B-ADD with lglider.arr ================
    //======================================================
    for (int y = 0; y < p->variables[0].y; y++)
    {
        for (int x = 0; x < p->variables[0].x; x++)
        {
            assert(p->variables[23].num[y][x] == (p->variables[0].num[y][x] == 1));
        }
    }
    free_struct(p);

    get_interp_prog_data(p, 37);
    assert(PROG(p));
    //======================================================
    //==========TEST B-ADD with lglider.arr ================
    //======================================================
    for (int y = 0; y < p->variables[0].y; y++)
    {
        for (int x = 0; x < p->variables[0].x; x++)
        {
            assert(p->variables[24].num[y][x] == (p->variables[0].num[y][x] == 1));
        }
    }
    free_struct(p);

    get_interp_prog_data(p, 38);
    assert(PROG(p));
    //======================================================
    //==========TEST B-ADD with lglider.arr ================
    //======================================================
    for (int y = 0; y < p->variables[0].y; y++)
    {
        for (int x = 0; x < p->variables[0].x; x++)
        {
            assert(p->variables[25].num[y][x] == (p->variables[0].num[y][x] == 1));
        }
    }
    free_struct(p);

    get_interp_prog_data(p, 39);
    assert(PROG(p));
    //======================================================
    //==========TEST B-ADD with lglider.arr ================
    //======================================================
    for (int y = 0; y < p->variables[0].y; y++)
    {
        for (int x = 0; x < p->variables[0].x; x++)
        {
            assert(p->variables[23].num[y][x] == (p->variables[0].num[y][x] < 1));
        }
    }
    free_struct(p);

    get_interp_prog_data(p, 40);
    assert(PROG(p));
    //======================================================
    //==========TEST B-ADD with lglider.arr ================
    //======================================================
    for (int y = 0; y < p->variables[0].y; y++)
    {
        for (int x = 0; x < p->variables[0].x; x++)
        {
            assert(p->variables[24].num[y][x] == (p->variables[0].num[y][x] < 1));
        }
    }
    free_struct(p);

    get_interp_prog_data(p, 41);
    assert(PROG(p));
    //======================================================
    //==========TEST B-ADD with lglider.arr ================
    //======================================================
    for (int y = 0; y < p->variables[0].y; y++)
    {
        for (int x = 0; x < p->variables[0].x; x++)
        {
            assert(p->variables[25].num[y][x] == (p->variables[0].num[y][x] < 1));
        }
    }
    free_struct(p);

    get_interp_prog_data(p, 42);
    assert(PROG(p));
    //======================================================
    //==========TEST B-ADD with lglider.arr ================
    //======================================================
    for (int y = 0; y < p->variables[0].y; y++)
    {
        for (int x = 0; x < p->variables[0].x; x++)
        {
            assert(p->variables[23].num[y][x] == (p->variables[0].num[y][x] > 1));
        }
    }
    free_struct(p);

    get_interp_prog_data(p, 43);
    assert(PROG(p));
    //======================================================
    //==========TEST B-ADD with lglider.arr ================
    //======================================================
    for (int y = 0; y < p->variables[0].y; y++)
    {
        for (int x = 0; x < p->variables[0].x; x++)
        {
            assert(p->variables[24].num[y][x] == (p->variables[0].num[y][x] > 1));
        }
    }
    free_struct(p);

    get_interp_prog_data(p, 44);
    assert(PROG(p));
    //======================================================
    //==========TEST B-ADD with lglider.arr ================
    //======================================================
    for (int y = 0; y < p->variables[0].y; y++)
    {
        for (int x = 0; x < p->variables[0].x; x++)
        {
            assert(p->variables[25].num[y][x] == (p->variables[0].num[y][x] > 1));
        }
    }
    free_struct(p);

    get_interp_prog_data(p, 45);
    assert(PROG(p));
    //======================================================
    //==========TEST B-ADD with lglider.arr ================
    //======================================================
    for (int y = 0; y < p->variables[0].y; y++)
    {
        for (int x = 0; x < p->variables[0].x; x++)
        {
            assert(p->variables[23].num[y][x] == (p->variables[0].num[y][x] & 12));
        }
    }
    free_struct(p);

    get_interp_prog_data(p, 46);
    assert(PROG(p));
    //======================================================
    //==========TEST B-ADD with lglider.arr ================
    //======================================================
    for (int y = 0; y < p->variables[0].y; y++)
    {
        for (int x = 0; x < p->variables[0].x; x++)
        {
            assert(p->variables[24].num[y][x] == (p->variables[0].num[y][x] & 12));
        }
    }
    free_struct(p);

    get_interp_prog_data(p, 47);
    assert(PROG(p));
    //======================================================
    //==========TEST B-ADD with lglider.arr ================
    //======================================================
    for (int y = 0; y < p->variables[0].y; y++)
    {
        for (int x = 0; x < p->variables[0].x; x++)
        {
            assert(p->variables[25].num[y][x] == (p->variables[0].num[y][x] & 12));
        }
    }
    free_struct(p);

    printf("RUN_INTERP_TEST PROG\n");
    free(p);
}

// }
