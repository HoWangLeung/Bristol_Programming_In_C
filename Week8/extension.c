#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#define MAX 6
#define FILENAME 100
struct rollarboard
{
    char arr[MAX][MAX];
    int parent_index;
};
typedef struct rollarboard rollarboard;
FILE *f_open(char *filename);
void read_file(FILE *file_pointer, rollarboard *board, int *my, int *mx);
void print_board(rollarboard *board, int my, int mx);
void print_temp_board(char temp_board[MAX][MAX], int my, int mx);
void moveUp(rollarboard *board, int x, char temp_arr[MAX][MAX], int my, int mx);
void moveRight(rollarboard *board, int y, char temp_arr[MAX][MAX], int my, int mx);
void moveLeft(rollarboard *board, int y, char temp_arr[MAX][MAX], int my, int mx);
void moveDown(rollarboard *board, int x, char temp_arr[MAX][MAX], int my, int mx);
void free_list(char **arr);
void append_to_list(rollarboard *list, rollarboard newBoard, int *count, int my, int mx);
bool isSeen(rollarboard *list, rollarboard *board, const int count, int my, int mx);
bool isSameBoard(rollarboard *prev_board, rollarboard *new_board, int my, int mx);
bool is_solution_found(rollarboard *board, int mx);
void get_steps(rollarboard *list, int *count, int my, int mx, bool verbose);
bool new_algo_search(rollarboard *list, rollarboard *initial_board, int *f, int my, int mx, int *count);
void copy_to_newboard(rollarboard *new_board, char temp_arr[MAX][MAX], int my, int mx);
void copy_to_temp_arr(rollarboard *new_board, char temp_arr[MAX][MAX], int my, int mx);
bool is_board_valid(rollarboard initial_board, int my, int mx);
rollarboard create_child_board(rollarboard *list, int f);
void handle_new_board(rollarboard *list, int f, char temp_arr[MAX][MAX], int my, int mx, int *count);
bool check_is_solved(rollarboard *list, int my, int mx, int *count);
bool solve(rollarboard *list, int *f, char temp_arr[MAX][MAX], int my, int mx, int *count);
void handle_command_line(int argc, char **argv, char **filename, bool *verbose);
void print_test_board(rollarboard testboard, int my, int mx);
void test();
bool is_same_2d_array(char arr_1[MAX][MAX], char arr_2[MAX][MAX], int my, int mx);
void create_test_board(rollarboard test_board, char test_board_arr[MAX][MAX], int my, int mx);
bool check_top_bottom_has_one(rollarboard board, int y, int x, int my);
void calculate_first_row(rollarboard board, int *num_1_on_left, int *num_1_on_right, int pos, int mx);
int main(int argc, char *argv[])
{
    int f = 0;
    int my = 0;
    int mx = 0;
    int count = 0;
    char *filename = NULL;
    bool verbose = false;
    handle_command_line(argc, argv, &filename, &verbose);
    FILE *file_pointer = f_open(filename);
    rollarboard initial_board;
    read_file(file_pointer, &initial_board, &my, &mx);
    if (!is_board_valid(initial_board, my, mx))
    {
        printf("not valid board\n");
        exit(EXIT_FAILURE);
    }
    rollarboard *list = calloc(sizeof(initial_board), 300000);
    if (new_algo_search(list, &initial_board, &f, my, mx, &count))
    {
        get_steps(list, &count, my, mx, verbose);
    }
    else
    {
        printf("No Solution?\n");
    }
    fclose(file_pointer);
    free(list);
    return 0;
}
bool new_algo_search(rollarboard *list, rollarboard *initial_board, int *f, int my, int mx, int *count)
{
    initial_board->parent_index = -1;
    append_to_list(list, *initial_board, count, my, mx);
    rollarboard *board = &list[*f];
    char temp_arr[MAX][MAX];
    int temp_y = 0;
    int temp_x = 0;
    while (*f < *count)
    {
        board = &list[*f];
        bool add_board = true;
        for (int y = 0; y < my; y++)
        {
            for (int x = 0; x < mx; x++)
            {
                if (y != 0 && board->arr[y][x] == '1')
                {
                    bool has_one = check_top_bottom_has_one(*board, y, x, my);
                    if (has_one && add_board)
                    {
                        int num_1_on_left = 0;
                        int num_1_on_right = 0;
                        int pos = 0;
                        calculate_first_row(*board, &num_1_on_left, &num_1_on_right, pos, mx);

                        if (num_1_on_left > num_1_on_right)
                        {
                            moveRight(board, y, temp_arr, my, mx);
                            handle_new_board(list, *f, temp_arr, my, mx, count);
                        }
                        else
                        {
                            moveLeft(board, y, temp_arr, my, mx);
                            handle_new_board(list, *f, temp_arr, my, mx, count);
                        }
                        add_board = false;
                    }
                    else if (!has_one && add_board == true)
                    {
                        temp_y = y;
                        temp_x = x;
                        //if the '1' is already near the bottom, then just move down
                        if (y > my / 2)
                        {
                            while (temp_y <= my)
                            {
                                moveDown(board, x, temp_arr, my, mx);
                                handle_new_board(list, *f, temp_arr, my, mx, count);
                                temp_y += 1;
                                if (check_is_solved(list, my, mx, count))
                                {
                                    return true;
                                }
                            }
                        }
                        else
                        {
                            while (temp_y > 0)
                            {
                                moveUp(board, x, temp_arr, my, mx);
                                handle_new_board(list, *f, temp_arr, my, mx, count);
                                temp_y -= 1;
                                if (check_is_solved(list, my, mx, count))
                                {
                                    return true;
                                }
                            }
                        }
                        add_board = false;
                    }
                }
            }
        }
        *f += 1;
    }
    return false;
}

void calculate_first_row(rollarboard board, int *num_1_on_left, int *num_1_on_right, int pos, int mx)
{
    while (pos <= mx / 2)
    {
        if (board.arr[0][pos] == '1')
        {
            *num_1_on_left += 1;
        }
        pos++;
    }
    pos = mx / 2;
    while (pos <= mx)
    {
        if (board.arr[0][pos] == '1')
        {
            *num_1_on_right += 1;
        }
        pos++;
    }
}
void handle_command_line(int argc, char **argv, char **filename, bool *verbose)
{
    if (argc > 3 || argc < 2)
    {
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "-v"))
        {
            *verbose = true;
            i++;
        }
        *filename = argv[i];
    }
}
bool is_board_valid(rollarboard initial_board, int my, int mx)
{
    int num_of_one = 0;
    int num_of_zero = 0;
    for (int y = 0; y < my; y++)
    {
        for (int x = 0; x < mx; x++)
        {
            if (initial_board.arr[y][x] == '1')
            {
                num_of_one++;
            }
            else if (initial_board.arr[y][x] == '0')
            {
                num_of_zero++;
            }
            else if (initial_board.arr[y][x] != '0')
            {
                return false;
            }
        }
    }
    if (num_of_one != mx)
    {
        return false;
    }
    if ((num_of_one + num_of_zero) != mx * my)
    {
        return false;
    }
    return true;
}
void copy_to_newboard(rollarboard *new_board, char temp_arr[MAX][MAX], int my, int mx)
{
    for (int y = 0; y < my; y++)
    {
        for (int x = 0; x < mx; x++)
        {
            new_board->arr[y][x] = temp_arr[y][x];
        }
    }
}
rollarboard create_child_board(rollarboard *list, int f)
{
    rollarboard newBoard;
    newBoard = list[f];
    newBoard.parent_index = f;
    return newBoard;
}
bool check_is_solved(rollarboard *list, int my, int mx, int *count)
{
    bool found_soultion = is_solution_found(&list[*count - 1], mx);
    if (found_soultion)
    {
        *count -= 1;
        if (!is_board_valid(list[*count], my, mx))
        {
            printf("No Solution?\n");
            exit(EXIT_FAILURE);
        }
        return true;
    }
    return false;
}
bool solve(rollarboard *list, int *f, char temp_arr[MAX][MAX], int my, int mx, int *count)
{
    handle_new_board(list, *f, temp_arr, my, mx, count);
    bool isSolved = check_is_solved(list, my, mx, count);
    return isSolved;
}
bool check_top_bottom_has_one(rollarboard board, int y, int x, int my)
{
    int tempy1 = y;
    int tempy2 = y;
    while (tempy1 + 1 < my)
    {
        if (board.arr[tempy1 + 1][x] == '1')
        {
            return true;
        }
        tempy1++;
    }
    while (tempy2 - 1 >= 0)
    {
        if (board.arr[tempy2 - 1][x] == '1')
        {
            return true;
        }
        tempy2--;
    }
    return false;
}
void handle_new_board(rollarboard *list, int f, char temp_arr[MAX][MAX], int my, int mx, int *count)
{
    rollarboard newBoard = create_child_board(list, f);
    copy_to_newboard(&newBoard, temp_arr, my, mx);
    append_to_list(list, newBoard, count, my, mx);
}
void moveLeft(rollarboard *board, int y, char temp_arr[MAX][MAX], int my, int mx)
{
    copy_to_temp_arr(board, temp_arr, my, mx);
    char temp = temp_arr[y][0];
    for (int i = 0; i < mx; i++)
    {
        temp_arr[y][i] = temp_arr[y][i + 1];
    }
    temp_arr[y][mx - 1] = temp;
}
bool is_solution_found(rollarboard *board, int mx)
{
    char *first_row = board->arr[0];
    int num_of_1 = 0;
    for (int x = 0; x < mx; x++)
    {
        if (first_row[x] == '1')
        {
            num_of_1 += 1;
        }
        if (first_row[x] != '1')
        {
            return false;
        }
    }
    if (num_of_1 != mx)
    {
        return false;
    }
    return true;
}
void get_steps(rollarboard *list, int *count, int my, int mx, bool verbose)
{
    int steps[1000];
    int t = 0;
    int i = *count;
    while (i > 0)
    {
        int step = list[i].parent_index;
        steps[t++] = step;
        i = list[step].parent_index;
        steps[t++] = i;
    }

    int step_count = 0;
    if (verbose)
    {
        for (int i = t - 1; i >= 0; i--)
        {
            if (steps[i] != -1)
            {
                printf("%d:\n", step_count++);
                print_board(&list[steps[i]], my, mx);
            }
        }
        printf("%d:\n", step_count);
        print_board(&list[*count], my, mx);
    }
    else
    {
        printf("%d moves\n", t);
    }
}
void append_to_list(rollarboard *list, rollarboard newBoard, int *count, int my, int mx)
{
    bool seen = isSeen(list, &newBoard, *count, my, mx);
    if (!seen)
    {
        list[*count] = newBoard;
        *count += 1;
    }
}
bool isSameBoard(rollarboard *prev_board, rollarboard *new_board, int my, int mx)
{
    for (int y = 0; y < my; y++)
    {
        for (int x = 0; x < mx; x++)
        {
            if (prev_board->arr[y][x] != new_board->arr[y][x])
            {
                return false;
            }
        }
    }
    return true;
}
bool isSeen(rollarboard *list, rollarboard *board, const int count, int my, int mx)
{
    for (int i = 0; i < count; i++)
    {
        bool isSame = isSameBoard(&list[i], board, my, mx);
        if (isSame)
        {
            return true;
        }
    }
    return false;
}
void moveRight(rollarboard *board, int y, char temp_arr[MAX][MAX], int my, int mx)
{
    copy_to_temp_arr(board, temp_arr, my, mx);
    char temp = temp_arr[y][mx - 1];
    for (int i = mx - 1; i > 0; i--)
    {
        temp_arr[y][i] = temp_arr[y][i - 1];
    }
    temp_arr[y][0] = temp;
}
void moveUp(rollarboard *board, int x, char temp_arr[MAX][MAX], int my, int mx)
{
    copy_to_temp_arr(board, temp_arr, my, mx);
    char temp = temp_arr[0][x];
    for (int i = 0; i < my - 1; i++)
    {
        temp_arr[i][x] = temp_arr[i + 1][x];
    }
    temp_arr[my - 1][x] = temp;
}
void moveDown(rollarboard *board, int x, char temp_arr[MAX][MAX], int my, int mx)
{
    copy_to_temp_arr(board, temp_arr, my, mx);
    char temp = temp_arr[my - 1][x];
    for (int y = my - 1; y > 0; y--)
    {
        temp_arr[y][x] = temp_arr[y - 1][x];
    }
    temp_arr[0][x] = temp;
}
FILE *f_open(char *filename)
{
    FILE *file_pointer = fopen(filename, "r");
    if (!file_pointer)
    {
        perror("Couldddnd't open file\n");
    }
    return file_pointer;
}
void read_file(FILE *file_pointer, rollarboard *board, int *my, int *mx)
{
    char buffer[MAX];
    int line = 0;
    while (fscanf(file_pointer, "%s", buffer) != EOF)
    {
        if (line == 0)
        {
            *my = atoi(buffer);
        }
        else if (line == 1)
        {
            *mx = atoi(buffer);
        }
        else
        {
            strcpy(board->arr[line - 2], buffer);
        }
        line++;
    }
}
void print_board(rollarboard *board, int my, int mx)
{
    for (int y = 0; y < my; y++)
    {
        for (int x = 0; x < mx; x++)
        {
            printf("%c", board->arr[y][x]);
        }
        printf("\n");
    }
        printf("\n");
}
void print_temp_board(char temp_arr[MAX][MAX], int my, int mx)
{
    for (int y = 0; y < my; y++)
    {
        for (int x = 0; x < mx; x++)
        {
            printf("%c", temp_arr[y][x]);
        }
        printf("\n");
    }
    printf("\n");
}
void free_list(char **arr)
{
    int i = 0;
    while (arr[i])
    {
        free(arr[i++]);
    }
    free(arr);
}
void copy_to_temp_arr(rollarboard *new_board, char temp_arr[MAX][MAX], int my, int mx)
{
    for (int y = 0; y < my; y++)
    {
        for (int x = 0; x < mx; x++)
        {
            temp_arr[y][x] = new_board->arr[y][x];
        }
    }
}
void print_test_board(rollarboard testboard, int my, int mx)
{
    for (int y = 0; y < my; y++)
    {
        for (int x = 0; x < mx; x++)
        {
            printf("%c", testboard.arr[y][x]);
        }
        printf("\n");
    }
}
bool is_same_2d_array(char arr_1[MAX][MAX], char arr_2[MAX][MAX], int my, int mx)
{
    for (int y = 0; y < my; y++)
    {
        for (int x = 0; x < mx; x++)
        {
            if (arr_1[y][x] != arr_2[y][x])
            {
                return false;
            }
        }
    }
    return true;
}
void create_test_board(rollarboard test_board, char test_board_arr[MAX][MAX], int my, int mx)
{
    for (int y = 0; y < my; y++)
    {
        for (int x = 0; x < mx; x++)
        {
            test_board.arr[y][x] = test_board_arr[y][x];
        }
    }
}
void test()
{
    int f = 0;
    int my = 3;
    int mx = 3;
    char initial_board_arr_1[MAX][MAX] = {{'0', '1', '0'},
                                          {'0', '1', '0'},
                                          {'0', '1', '0'}};
    char expected_result_1[MAX][MAX] = {{'0', '0', '1'},
                                        {'0', '1', '0'},
                                        {'0', '1', '0'}};
    char expected_result_2[MAX][MAX] = {{'0', '1', '0'},
                                        {'0', '0', '1'},
                                        {'0', '1', '0'}};
    char expected_result_3[MAX][MAX] = {{'0', '1', '0'},
                                        {'0', '1', '0'},
                                        {'0', '0', '1'}};
    char expected_result_4[MAX][MAX] = {{'1', '0', '0'},
                                        {'0', '1', '0'},
                                        {'0', '1', '0'}};
    char expected_result_5[MAX][MAX] = {{'0', '1', '0'},
                                        {'1', '0', '0'},
                                        {'0', '1', '0'}};
    char expected_result_6[MAX][MAX] = {{'0', '1', '0'},
                                        {'0', '1', '0'},
                                        {'1', '0', '0'}};
    char initial_board_arr_2[MAX][MAX] = {{'1', '0', '0', '0'},
                                          {'0', '0', '1', '1'},
                                          {'0', '1', '0', '0'}};
    char expected_result_7[MAX][MAX] = {{'0', '0', '0', '1'},
                                        {'0', '0', '1', '1'},
                                        {'0', '1', '0', '0'}};
    char expected_result_8[MAX][MAX] = {{'1', '0', '0', '0'},
                                        {'1', '0', '0', '1'},
                                        {'0', '1', '0', '0'}};
    char initial_board_arr_3[MAX][MAX] = {{'1', '0', '0', '1', '0'},
                                          {'0', '0', '1', '1', '0'},
                                          {'0', '1', '0', '0', '0'}};
    char expected_result_9[MAX][MAX] = {{'1', '0', '0', '1', '0'},
                                        {'0', '0', '1', '0', '0'},
                                        {'0', '1', '0', '1', '0'}};
    char expected_result_10[MAX][MAX] = {{'1', '1', '0', '1', '0'},
                                         {'0', '0', '1', '1', '0'},
                                         {'0', '0', '0', '0', '0'}};
    char invalid_arr_1[MAX][MAX] = {{'1', '1', '1', '1', '1'},
                                    {'1', '1', '1', '1', '1'},
                                    {'1', '1', '1', '1', '1'}};
    char invalid_arr_2[MAX][MAX] = {{'*', '*', 'X', '+', '@'},
                                    {'1', '1', '1', '1', '@'},
                                    {'0', '0', '0', '1', '@'}};
    char invalid_arr_3[MAX][MAX] = {{'0', '0', '0', '0', '0'},
                                    {'0', '0', '0', '0', '0'},
                                    {'0', '0', '0', '0', '0'}};
    rollarboard initial_board;
    for (int y = 0; y < my; y++)
    {
        for (int x = 0; x < mx; x++)
        {
            initial_board.arr[y][x] = initial_board_arr_1[y][x];
        }
    }
    rollarboard *testlist = calloc(sizeof(initial_board_arr_1), 100000);
    testlist[0] = initial_board;
    char temp_arr[MAX][MAX];
    rollarboard *board = &testlist[f];
    rollarboard test_board_1;
    for (int y = 0; y < my; y++)
    {
        for (int x = 0; x < mx; x++)
        {
            test_board_1.arr[y][x] = initial_board_arr_1[y][x];
        }
    }
    moveRight(board, 0, temp_arr, my, mx);
    assert(is_same_2d_array(temp_arr, expected_result_1, my, mx));
    assert(!is_same_2d_array(temp_arr, initial_board_arr_1, my, mx));
    moveRight(board, 1, temp_arr, my, mx);
    printf("======================> 1\n");
    assert(is_same_2d_array(temp_arr, expected_result_2, my, mx));
    assert(!is_same_2d_array(temp_arr, initial_board_arr_1, my, mx));
    moveRight(board, 2, temp_arr, my, mx);
    printf("======================> 2\n");
    assert(is_same_2d_array(temp_arr, expected_result_3, my, mx));
    assert(!is_same_2d_array(temp_arr, initial_board_arr_1, my, mx));
    printf("======================> 3\n");
    moveLeft(board, 0, temp_arr, my, mx);
    assert(is_same_2d_array(temp_arr, expected_result_4, my, mx));
    assert(!is_same_2d_array(temp_arr, initial_board_arr_1, my, mx));
    moveLeft(board, 1, temp_arr, my, mx);
    assert(is_same_2d_array(temp_arr, expected_result_5, my, mx));
    assert(!is_same_2d_array(temp_arr, initial_board_arr_1, my, mx));
    moveLeft(board, 2, temp_arr, my, mx);
    assert(is_same_2d_array(temp_arr, expected_result_6, my, mx));
    assert(!is_same_2d_array(temp_arr, initial_board_arr_1, my, mx));
    my = 4;
    mx = 4;
    printf("======================> 4\n");
    rollarboard test_board_2;
    for (int y = 0; y < my; y++)
    {
        for (int x = 0; x < mx; x++)
        {
            test_board_2.arr[y][x] = initial_board_arr_2[y][x];
        }
    }
    moveLeft(&test_board_2, 0, temp_arr, my, mx);
    assert(is_same_2d_array(temp_arr, expected_result_7, my, mx));
    assert(!is_same_2d_array(temp_arr, initial_board_arr_2, my, mx));
    moveRight(&test_board_2, 1, temp_arr, my, mx);
    assert(is_same_2d_array(temp_arr, expected_result_8, my, mx));
    assert(!is_same_2d_array(temp_arr, initial_board_arr_2, my, mx));
    my = 3;
    mx = 5;
    printf("======================> 5\n");
    rollarboard test_board_3;
    for (int y = 0; y < my; y++)
    {
        for (int x = 0; x < mx; x++)
        {
            test_board_3.arr[y][x] = initial_board_arr_3[y][x];
        }
    }
    moveUp(&test_board_3, 3, temp_arr, my, mx);
    assert(is_same_2d_array(temp_arr, expected_result_9, my, mx));
    assert(!is_same_2d_array(temp_arr, initial_board_arr_3, my, mx));
    moveDown(&test_board_3, 1, temp_arr, my, mx);
    assert(is_same_2d_array(temp_arr, expected_result_10, my, mx));
    assert(!is_same_2d_array(temp_arr, initial_board_arr_3, my, mx));
    mx = 5;
    my = 3;
    printf("======================> 6\n");
    rollarboard test_board_4;
    for (int y = 0; y < my; y++)
    {
        for (int x = 0; x < mx; x++)
        {
            test_board_4.arr[y][x] = invalid_arr_1[y][x];
        }
    }
    bool is_valid = is_board_valid(test_board_4, my, mx);
    assert(is_valid == false);
    mx = 5;
    my = 3;
    printf("======================> 6\n");
    rollarboard test_board_5;
    for (int y = 0; y < my; y++)
    {
        for (int x = 0; x < mx; x++)
        {
            test_board_5.arr[y][x] = invalid_arr_2[y][x];
        }
    }
    is_valid = is_board_valid(test_board_5, my, mx);
    assert(is_valid == false);
    mx = 5;
    my = 3;
    printf("======================> 6\n");
    rollarboard test_board_6;
    for (int y = 0; y < my; y++)
    {
        for (int x = 0; x < mx; x++)
        {
            test_board_6.arr[y][x] = invalid_arr_3[y][x];
        }
    }
    is_valid = is_board_valid(test_board_6, my, mx);
    assert(is_valid == false);
    free(testlist);
    printf("========> finished testing\n");
}
