#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define GRID 6
#define BIG 128
#define START_SIZE 36

struct rollarboard
{
    char arr[GRID][GRID];
    int max_y;
    int max_x;
    int parent_index;
};
typedef struct rollarboard rollarboard;

FILE *h_open(char filename[100]);
void read_file(FILE *file_pointer, rollarboard *board);
void print_board(rollarboard *board);
void print_temp_board(rollarboard *board, char **temp_board);
void free_list(char **words_list);
char **moveUp(rollarboard *board, int x);
char **moveRight(rollarboard *board, int y);
char **moveLeft(rollarboard *board, int y);
char **moveDown(rollarboard *board, int x);
void free_list(char **arr);
void append_to_list(rollarboard *list, rollarboard *newBoard, int *count);
bool isSeen(rollarboard *list, rollarboard *board, const int count);
bool isSameBoard(rollarboard *prev_board, rollarboard *new_board);
bool is_solution_found(rollarboard *board);
int *get_steps(rollarboard *list, int *count);
void get_result(rollarboard *list, int *count);
int count_number_of_one(rollarboard *board);
void BFS(rollarboard *list, rollarboard *initial_board, int *f);
rollarboard *initialize_new_board(int *f, rollarboard *prev_board);
void copy_to_newboard(rollarboard *new_board, char **result);
void is_board_valid(rollarboard initial_board);

int main(int argc, char *argv[])
{
    (void)argc;
    char *filename = argv[1];
    // bool print_step = false;
    // if (strcmp(argv[1], "-v") == 0)
    // {
    //     printf("ffffff\n");
    //     print_step = true;
    //     filename = argv[2];
    // }
    // else
    // {
    //     filename = argv[1];
    // }

    // sprintf(filename, "%s", argv[1]);

    FILE *file_pointer = h_open(filename);
    rollarboard initial_board;
    read_file(file_pointer, &initial_board);
    printf("my = %d, mx=%d\n", initial_board.max_y, initial_board.max_x);
    fclose(file_pointer);
    is_board_valid(initial_board);
    rollarboard *list = calloc(sizeof(initial_board), 200000);
    int f = 0;
    BFS(list, &initial_board, &f);
    //free(list);

    return 0;
}
void is_board_valid(rollarboard initial_board)
{
    int num_of_one = 0;
    for (int y = 0; y < initial_board.max_y; y++)
    {
        for (int x = 0; x < initial_board.max_x; x++)
        {
            if (initial_board.arr[y][x] == '1')
            {
                num_of_one++;
            }
        }
    }
    if (num_of_one != initial_board.max_x)
    {
        printf("No Solution?\n");
        exit(EXIT_FAILURE);
    }
}
int count_number_of_one(rollarboard *board)
{
    int c = 0;
    for (int y = 0; y < board->max_y; y++)
    {
        for (int x = 0; x < board->max_x; x++)
        {
            if (board->arr[y][x] == '1')
            {
                c += 1;
            }
        }
    }
    printf("number of 1 = %d\n", c);

    return c;
}
rollarboard *initialize_new_board(int *f, rollarboard *prev_board)
{
    //printf("ff = %d\n", *f);

    rollarboard *newBoard = NULL;
    newBoard = malloc(sizeof(*prev_board));
    newBoard->max_x = prev_board->max_x;
    newBoard->max_y = prev_board->max_y;
    //parent_index
    newBoard->parent_index = *f;
    return newBoard;
}
void copy_to_newboard(rollarboard *new_board, char **result)
{
    for (int y = 0; y < new_board->max_y; y++)
    {
        for (int x = 0; x < new_board->max_x; x++)
        {

            new_board->arr[y][x] = result[y][x];
        }
    }
}
void BFS(rollarboard *list, rollarboard *initial_board, int *f)
{
    printf("size of sizeof(*board) =%lu , max y = %d, max x = %d \n", sizeof(*initial_board), initial_board->max_y, initial_board->max_x);
    int count = 0;
    initial_board->parent_index = -1;
    list[0] = *initial_board;
    count += 1;
    rollarboard *board = &list[*f];

    while (*f < count)
    {
        board = &list[*f];
        for (int y = 0; y < board->max_y; y++)
        {
            char **result = moveRight(board, y);
            rollarboard *newBoard = initialize_new_board(f, board);
            copy_to_newboard(newBoard, result);
            //printf("move right , ");
            // if(count_number_of_one(newBoard)!=5){
            //     print_board(newBoard);
            // }

            append_to_list(list, newBoard, &count);
            free(newBoard);
            free_list(result);
        }

        for (int x = 0; x < board->max_x; x++)
        {
            char **result = moveDown(board, x);

            rollarboard *newBoard = initialize_new_board(f, board);
            copy_to_newboard(newBoard, result);
            //  printf("move down , ");
            //  if(count_number_of_one(newBoard)!=5){
            //     print_board(newBoard);
            // }
            //print_board(newBoard);
            append_to_list(list, newBoard, &count);
            free(newBoard);
            free_list(result);
        }
        for (int y = 0; y < board->max_y; y++)
        {
            char **result = result = moveLeft(board, y);
            rollarboard *newBoard = initialize_new_board(f, board);

            copy_to_newboard(newBoard, result);
            //printf("move left , ");
            //if(count_number_of_one(newBoard)!=5){
            //print_board(newBoard);
            // }
            //print_board(newBoard);
            append_to_list(list, newBoard, &count);
            free(newBoard);
            free_list(result);
        }
        for (int x = 0; x < board->max_x; x++)
        {
            char **result = moveUp(board, x);

            rollarboard *newBoard = initialize_new_board(f, board);
            copy_to_newboard(newBoard, result);
            //printf("move Up , ");
            //  if(count_number_of_one(newBoard)!=5){
            //     print_board(newBoard);
            // }
            //print_board(newBoard);
            append_to_list(list, newBoard, &count);
            free(newBoard);
            free_list(result);
        }
        //print every
        // for (int i = 0; i < *f; i++)
        // {
        //     for (int y = 0; y < board->max_y; y++)
        //     {
        //         for (int x = 0; x < board->max_x; x++)
        //         {
        //             printf("%c", list[i].arr[y][x]);
        //         }
        //         printf("\n");
        //     }

        //     printf("\n");
        // }

        *f += 1;
    }
    free(list);
}

char **moveLeft(rollarboard *board, int y)
{
    char **temp_arr = (char **)calloc((board->max_x * board->max_y), sizeof(char *));
    for (int i = 0; i < board->max_y; i++)
    {
        temp_arr[i] = (char *)calloc(board->max_x + 1, sizeof(char));
        memcpy(temp_arr[i], board->arr[i], board->max_x);
    }

    char temp = temp_arr[y][0];
    for (int i = 0; i < board->max_x; i++) //changed from y to x
    {
        temp_arr[y][i] = temp_arr[y][i + 1];
    }
    temp_arr[y][board->max_x - 1] = temp;

    return temp_arr;
}

bool is_solution_found(rollarboard *board)
{

    char *first_row = board->arr[0];
    for (int x = 0; x < board->max_x; x++)
    {
        if (first_row[x] != '1')
        {
            return false;
        }
    }

    return true;
}

int *get_steps(rollarboard *list, int *count)
{

    int *steps = (int *)calloc(10000, sizeof(int));
    ;
    int t = 0;
    // printf("current = %d\n",*count);
    // printf("p1 = %d\n",list[*count].parent_index);
    // printf("p2 = %d\n",list[list[*count].parent_index].parent_index);

    int i = *count;
    while (i > 0)
    {
        int step = list[i].parent_index;
        steps[t++] = step;
        i = list[step].parent_index;
        steps[t++] = i;
    }
    //printf("t= %d\n",t);
    for (int i = 0; i < t; i++)
    {
        printf("step = %d\n", steps[i]);
    }

    int max_y = list[0].max_y;
    int max_x = list[0].max_x;
    for (int i = t - 1; i >= 0; i--)
    {
        //printf("ss = %d\n", steps[i]);
        for (int y = 0; y < max_y; y++)
        {
            for (int x = 0; x < max_x; x++)
            {
                if (steps[i] != -1)
                    printf("%c", list[steps[i]].arr[y][x]);
            }
            printf("\n");
        }
        printf("\n");
    }
    print_board(&list[*count]);

    return steps;
}

void append_to_list(rollarboard *list, rollarboard *newBoard, int *count)
{
    bool seen = isSeen(list, newBoard, *count);
    if (!seen)
    {
        list[*count] = *newBoard;
        get_result(list, count);
        *count += 1;
    }
}
void get_result(rollarboard *list, int *count)
{
    bool found_soultion = is_solution_found(&list[*count]);
    if (found_soultion)
    {
        printf("found solution\n");
        int *steps = get_steps(list, count);
        if (steps)
        {
            free(list);
            free(steps);
            exit(0);
        }
    }
}
bool isSameBoard(rollarboard *prev_board, rollarboard *new_board)
{
    // bool isSame =true;
    for (int y = 0; y < prev_board->max_y; y++)
    {
        for (int x = 0; x < prev_board->max_x; x++)
        {
            if (prev_board->arr[y][x] != new_board->arr[y][x])
            {
                return false;
            }
        }
    }

    return true;
}
bool isSeen(rollarboard *list, rollarboard *board, const int count)
{

    for (int i = 0; i < count; i++)
    {
        bool isSame = isSameBoard(&list[i], board);
        if (isSame)
        {
            return true;
        }
    }

    return false;
}

char **moveRight(rollarboard *board, int y)
{
    //  printf("moving right, y= %d\n", y);
    char **temp_arr = (char **)calloc(sizeof(char *), (board->max_x * board->max_y));
    for (int i = 0; i < board->max_y; i++)
    {
        temp_arr[i] = (char *)calloc(sizeof(char), board->max_x + 1);
        memcpy(temp_arr[i], board->arr[i], board->max_x);
    }
    char temp = temp_arr[y][board->max_x - 1];
    for (int i = board->max_x - 1; i > 0; i--)
    {
        temp_arr[y][i] = temp_arr[y][i - 1];
    }
    temp_arr[y][0] = temp;

    return temp_arr;
}
char **moveUp(rollarboard *board, int x)
{

    char **temp_arr = (char **)calloc((board->max_x * board->max_y), sizeof(char *));
    for (int i = 0; i < board->max_y; i++)
    {
        temp_arr[i] = (char *)calloc(board->max_x + 1, sizeof(char));
        memcpy(temp_arr[i], board->arr[i], board->max_x);
    }

    char temp = temp_arr[0][x];
    // printf("move up , mx = %d, x= %d\n",board->max_x,x);
    for (int i = 0; i < board->max_y - 1; i++) //changed from max_x to max_y
    {
        // printf("%d %d\n",i,x);
        temp_arr[i][x] = temp_arr[i + 1][x];
    }

    temp_arr[board->max_y - 1][x] = temp;

    return temp_arr;
}
char **moveDown(rollarboard *board, int x)
{
    // printf("x %d, y %d\n",board->max_x ,board->max_y);
    char **temp_arr = (char **)calloc((board->max_x * board->max_y), sizeof(char *));
    for (int i = 0; i < board->max_y; i++)
    {
        // words_list[word_count] = (char *)h_malloc(sizeof(char) * strlen(buffer) + 1);
        temp_arr[i] = (char *)calloc(board->max_x, sizeof(char));
        memcpy(temp_arr[i], board->arr[i], board->max_x);
    }
    char temp = temp_arr[board->max_y - 1][x];
    for (int y = board->max_y - 1; y > 0; y--)
    {
        temp_arr[y][x] = temp_arr[y - 1][x];
    }
    // printf("\n now x = %d\n",x);
    // printf("\n now temp = %c\n",temp);
    temp_arr[0][x] = temp;
    // free(temp_arr);

    return temp_arr;
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

void read_file(FILE *file_pointer, rollarboard *board)
{
    char buffer[GRID + 2];
    int line = 0;
    while (fscanf(file_pointer, "%s", buffer) != EOF)
    {

        if (line == 0)
        {

            board->max_y = atoi(buffer);
        }
        else if (line == 1)
        {
            //printf("x = %d\n", atoi(buffer));
            board->max_x = atoi(buffer);
        }
        else if (line <= GRID)
        {
            strcpy(board->arr[line - 2], buffer);
        }
        line++;
    }
}

void print_board(rollarboard *board)
{
    //printf("Prinsting %d\n", board->max_y);
    for (int y = 0; y < board->max_y; y++)
    {
        for (int x = 0; x < board->max_x; x++)
        {
            printf("%c", board->arr[y][x]);
        }
        printf("\n");
    }
    printf("\n");
}
void print_temp_board(rollarboard *board, char **temp_arr)
{

    // printf("print_temp_board\n");
    for (int y = 0; y < board->max_y; y++)
    {
        for (int x = 0; x < board->max_x; x++)
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
