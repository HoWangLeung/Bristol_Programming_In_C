#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 6

struct rollarboard
{
    char arr[MAX][MAX];
    int parent_index;
};
typedef struct rollarboard rollarboard;
FILE *h_open(char filename[100]);
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
bool is_solution_found(rollarboard *board, int my, int mx);
void get_steps(rollarboard *list, int *count, int my, int mx, bool verbose);
bool BFS(rollarboard *list, rollarboard *initial_board, int *f, int my, int mx, int *count);
void copy_to_newboard(rollarboard *new_board, char temp_arr[MAX][MAX], int my, int mx);
void copy_to_temp_arr(rollarboard *new_board, char temp_arr[MAX][MAX], int my, int mx);
void is_board_valid(rollarboard initial_board, int my, int mx);
rollarboard create_child_board(rollarboard *list, int f);
void handle_new_board(rollarboard *list, int f, char temp_arr[MAX][MAX], int my, int mx, int *count);
bool check_is_solved(rollarboard *list, int my, int mx, int *count);
bool solve(rollarboard *list, int *f, char temp_arr[MAX][MAX], int my, int mx, int *count);
void handleCommandLine(char *argv[], char *filename, bool *verbose);

int main(int argc, char *argv[])
{
    (void)argc;
    int f = 0;
    int my = 0;
    int mx = 0;
    int count = 0;
    char *filename = argv[1];
    bool verbose = false;
    handleCommandLine(argv, filename, &verbose);

    FILE *file_pointer = h_open(filename);
    rollarboard initial_board;
    read_file(file_pointer, &initial_board, &my, &mx);
    is_board_valid(initial_board, my, mx);
    rollarboard *list = calloc(sizeof(initial_board), 300000);

    if (BFS(list, &initial_board, &f, my, mx, &count))
    {
        get_steps(list, &count, my, mx, verbose);
    }
    else
    {
        printf("No Solution?");
    }
    fclose(file_pointer);
    free(list);
    return 0;
}
void handleCommandLine(char *argv[], char *filename, bool *verbose)
{
    if (strcmp(argv[1], "-v") == 0)
    {
        *verbose = true;
        strcpy(filename, argv[2]);
    }
    else
    {
        strcpy(filename, argv[1]);
    }
}

void is_board_valid(rollarboard initial_board, int my, int mx)
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
            else
            {
                printf("Invalid characters found in the board");
                exit(EXIT_FAILURE);
            }
        }
    }
    if (num_of_one != mx)
    {
        printf("No Solution?\n");
        exit(EXIT_FAILURE);
    }

    if ((num_of_one + num_of_zero) != mx * my)
    {
        printf("Sum of '1' and '0' does not equal width*height \n");
        exit(EXIT_FAILURE);
    }
}

void copy_to_newboard(rollarboard *new_board, char temp_arr[MAX][MAX], int my, int mx)
{
    //  printf("copying y %d  x %d  \n", my, mx);
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
    bool found_soultion = is_solution_found(&list[*count - 1], my, mx);
    if (found_soultion)
    {

        printf("found solution\n");
        *count -= 1;
        //make sure the board is not modified unexpectedly
        //e.g. this should be invalid although first row has three '1'
        //     111
        //     110
        //     000
        is_board_valid(list[*count], my, mx);
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

bool BFS(rollarboard *list, rollarboard *initial_board, int *f, int my, int mx, int *count)
{

    initial_board->parent_index = -1;
    append_to_list(list, *initial_board, count, my, mx);
    rollarboard *board = &list[*f];
    char temp_arr[MAX][MAX];
    while (*f < *count)
    {
        board = &list[*f];
        for (int x = 0; x < mx; x++)
        {
            moveDown(board, x, temp_arr, my, mx);
            if (solve(list, f, temp_arr, my, mx, count))
            {
                return true;
            }

            moveUp(board, x, temp_arr, my, mx);
            if (solve(list, f, temp_arr, my, mx, count))
            {
                return true;
            }
        }
        for (int y = 0; y < my; y++)
        {
            moveRight(board, y, temp_arr, my, mx);
            if (solve(list, f, temp_arr, my, mx, count))
            {
                return true;
            }
            moveLeft(board, y, temp_arr, my, mx);
            if (solve(list, f, temp_arr, my, mx, count))
            {
                return true;
            }
        }
        *f += 1;
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
    for (int i = 0; i < mx; i++) //changed from y to x
    {
        temp_arr[y][i] = temp_arr[y][i + 1];
    }
    temp_arr[y][mx - 1] = temp;
}

bool is_solution_found(rollarboard *board, int my, int mx)
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
    printf("%d moves\n", t);
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
            printf("\n");
        }
        printf("%d:\n", step_count);
        print_board(&list[*count], my, mx);
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
    // return 0;
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
    for (int i = 0; i < my - 1; i++) //changed from max_x to max_y
    {
        // printf("%d %d\n",i,x);
        temp_arr[i][x] = temp_arr[i + 1][x];
    }
    temp_arr[my - 1][x] = temp;
}
void moveDown(rollarboard *board, int x, char temp_arr[MAX][MAX], int my, int mx)
{

    copy_to_temp_arr(board, temp_arr, my, mx);

    char temp = temp_arr[my - 1][x]; //x > x-1

    for (int y = my - 1; y > 0; y--)
    {
        temp_arr[y][x] = temp_arr[y - 1][x];
    }
    temp_arr[0][x] = temp;
}

FILE *h_open(char *filename)
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
    char buffer[MAX ];
    int line = 0;
    // int temp_mx = 0;
    // int temp_my = 0;
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
