#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
enum bool
{
    false,
    true
};
typedef enum bool bool;
typedef struct RandStart
{
    int x;
    int y;
} RandStart;
#define R 50
#define C 50
#define TR 7
#define TC 2
#define MAX_LEN 100

void simulate(int a[R][C]);
void set_player_board(char board[R][C], char *p1_file, char *p2_file);
void fillArrWithZero(char board[R][C]);
void printBoard(char board[R][C]);
void getFileData(char tmp[TR][TC], char *target_file);
void fillBoard(char board[R][C], char tmp[TR][TC], RandStart randStart, bool isPlayer1);
void simulate5000(char board[R][C]);
bool checkIsOverlap(char board[R][C]);

int main(int argc, char **argv)
{
    srand(time(NULL));
    if (argc != 3)
    {
        printf("INCORRECT USAGE \n");
        exit(1);
    }
    char *file1 = argv[1];
    char *file2 = argv[2];
    char board[R][C];
    set_player_board(board, file1, file2);

    simulate5000(board)
  
    return 0;
}

void set_player_board(char board[R][C], char *p1_file, char *p2_file)
{

    //bool isPlayer1 = strstr(target_file, "player1") != NULL ? true : false;

    RandStart randStart;
    char tmp1[TR][TC];
    char tmp2[TR][TC];
    fillArrWithZero(board);
    while (checkIsOverlap(board))
    {
        fillArrWithZero(board);
        getFileData(tmp1, p1_file);
        getFileData(tmp2, p2_file);
        randStart.x = rand() % ((R + 1) - 0) + 0;
        randStart.y = rand() % ((C + 1) - 0) + 0;
        printf("fill board 1");
        fillBoard(board, tmp1, randStart, 1);
        randStart.x = rand() % ((R + 1) - 0) + 0;
        randStart.y = rand() % ((C + 1) - 0) + 0;
        fillBoard(board, tmp2, randStart, 0);
    }
}

bool checkIsOverlap(char board[R][C])
{
    printf("get checking\n");
    int p1_sum = 0;
    int p2_sum = 0;
    for (int r = 0; r < R; r++)
    {
        for (int c = 0; c < C; c++)
        {
            if (board[r][c] == '+')
            {
                p1_sum++;
            }
            else if (board[r][c] == '!')
            {
                p2_sum++;
            }
        }
    }
    if (p1_sum == 0 && p2_sum == 0)
    {
        return true;
    }

    if ((p1_sum != 0 && p2_sum != 0) && p1_sum != p2_sum)
    {
        printf("found overlap\n");
        return true;
    }
    else
    {
        printf("no overlap\n");
    }
    return false;
}

void fillBoard(char board[R][C], char tmp[TR][TC], RandStart randStart, bool isPlayer1)
{
    printf("start fill board");
    // printf("%d %d\n",randStart.x,randStart.y);
    for (int i = 0; i < TR; i++)
    {
        //printf("rand_y = %d , rand_x = %d\n", randStart.y, randStart.x);
        int wrapped_y = (randStart.y + tmp[i][0] + C) % C;
        int wrapped_x = (randStart.x + tmp[i][1] + R) % R;
        // printf("wrapped_y = %d , wrapped_x =%d \nfinal_y =%d, final_x=%d\n\n", wrapped_y, wrapped_x, wrapped_y + tmp[i][0], wrapped_x + tmp[i][1]);
        board[wrapped_y][wrapped_x] = isPlayer1 ? '+' : '!';
        //board[wrapped_y][1] = tmp[i][1];
    }
}

void getFileData(char tmp[TR][TC], char *target_file)
{
    printf("f= %s\n", target_file);
    FILE *fp;
    fp = fopen(target_file, "r");
    if (fp == NULL)
    {
        perror("Failed: ");
        exit(1);
    }
    char buffer[MAX_LEN];
    char init[7][2];
    int i = 0;
    while (fgets(buffer, MAX_LEN - 1, fp))
    {

        if (buffer[0] == '#')
        {
            continue;
        };
        //printf("%c\n", buffer[0]);
        init[i][0] = buffer[0];
        init[i][1] = buffer[2];
        i++;
    }

   // memcpy(tmp, init, sizeof(char) * TR * TC);
   for (int r = 0; r < TR; r++)
   {
      for (int c = 0; c < TC; c++)
      {
          tmp[r][c] = init[r][c];
      }
      
   }
   

    fclose(fp);
    printf("finished get file\n");
}

void fillArrWithZero(char board[R][C])
{
    for (int r = 0; r < R; r++)
    {
        for (int c = 0; c < C; c++)
        {
            board[r][c] = '0';
        }
    }
    printf("finished fill zero\n");
}
void printBoard(char board[R][C])
{
    for (int r = 0; r < R; r++)
    {
        for (int c = 0; c < C; c++)
        {
            printf("%c", board[r][c]);
        }
        printf("\n");
    }
}

void simulate5000(int a[R][C])
{
    int b[R][C];
    for (int r = 0; r < R; r++)
    {
        for (int c = 0; c < C; c++)
        {
            b[r][c] = a[r][c];
        }
    }

    int inhabited_neighbour = 0;
    for (int r = 0; r < R; r++)
    {
        for (int c = 0; c < C; c++)
        {
                if (a[r - 1][c - 1] == '+' || a[r - 1][c - 1] == '!')
                {
                    inhabited_neighbour++;
                }
                if (a[r - 1][c] == '+' || a[r - 1][c] == '!' )
                {
                    inhabited_neighbour++;
                }
                if (a[r - 1][c + 1] == '+' || a[r - 1][c + 1] == '!' )
                {
                    inhabited_neighbour++;
                }
                if (a[r][c - 1] == '+' || a[r][c - 1] =='!')
                {
                    inhabited_neighbour++;
                }
                if (a[r][c + 1] == '+' || a[r][c + 1] == '!')
                {
                    inhabited_neighbour++;
                }
                if (a[r + 1][c - 1] == '+'||a[r + 1][c - 1] == '!')
                {
                    inhabited_neighbour++;
                }
                if (a[r + 1][c] == '+'||a[r + 1][c] =='!')
                {
                    inhabited_neighbour++;
                }
                if (a[r + 1][c + 1] == '+' || a[r + 1][c + 1] == '!')
                {
                    inhabited_neighbour++;
                }

                if (a[r][c] == 1 && (inhabited_neighbour == 2 || inhabited_neighbour == 3))
                {
                    b[r][c] = 1;
                }
                else if (a[r][c] == 0 && inhabited_neighbour == 3)
                {
                    b[r][c] = 1;
                }
                else
                {
                    b[r][c] = 0;
                }
        }

      
    }

 
    for (int r = 0; r < R; r++)
    {
        for (int c = 0; c < C; c++)
        {
            a[r][c] = b[r][c];
        }
    }
}
