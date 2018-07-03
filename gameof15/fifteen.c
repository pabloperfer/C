/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];



// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(400000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    // if the size is even i use a for to assign the values, for odd another.
//   int z=d;
//   int board[z][z];   
   int tilevalue=d*d-1;
   if (d%2 != 0){
    for (int i=0; i<d;i++){
            for (int j=0; j<d; j++) {
                    board[i][j]=tilevalue;
                    tilevalue--;
                      }
                    }
                 }
       else {
         for (int i=0; i<d;i++){
             for (int j=0; j<d; j++) {
                     if (tilevalue==2) {
                        board[i][j]=1;
                            }
                     else if (tilevalue==1){
                        board[i][j]=2;
                           }
                     else {
                       board[i][j]=tilevalue;
                          }
                     tilevalue--;
                                  }
                }
          }
    }

/**
 * Prints the board in its current state.
 */
void draw(void)
{
for (int i=0; i<d;i++){
    for (int j=0; j<d; j++) {
        if (board[i][j] < 1){
              printf (" _");
               }
        else {
          printf("%2d ",board[i][j]);
              }
                  }
           printf("\n");
                }
    usleep(1000000);
  }

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
   // printf ("tiles is %d \n",tile);
    int blank_row;
    int blank_col;
    int tile_row;
    int tile_col;
    //in the next 2 iterations i store the tile and the blank positions.I also create variables for the positions of each dimension to compare them later
    //
 for (int i=0; i<d;i++){
     for (int j=0; j<d; j++) {
         if (board[i][j]==0){
               blank_row=i;
               blank_col=j;
                            }
                      }
              }
for (int h=0; h<d;h++){
      for (int p=0; p<d; p++) {
          if (board[h][p]==tile){
              tile_row=h;
              tile_col=p;
                             }
                       }
               }
//now we compare both positions to verify the movement is legal
int temp_row;
int temp_col;
  if ((tile_row - blank_row == 1 || tile_row - blank_row == -1 ||tile_row - blank_row==0 ) && (tile_col - blank_col ==1 || tile_col - blank_col == -1|| tile_col -blank_col==0)&&(tile_row == blank_row || tile_col == blank_col)){
          printf("legal move\n");
          temp_row=blank_row;
          temp_col=blank_col;
          blank_row=tile_row;
          blank_col=tile_col;
          tile_row=temp_row;
          tile_col=temp_col;
          board[temp_row][temp_col]=tile;
          //printf("tile is in row %d  in col %d with value  %d ", temp_row,temp_col, board[temp_row][temp_col]);
          board[blank_row][blank_col]=0;
          //printf("blank is in row %d  in col %d with value  %d ",blank_row,blank_col, board[blank_row][blank_col]);
          usleep (1000000);
          return true;
                        }
            
     return false;

}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
int check=1;
int total =d*d;
  for (int i=0; i<d;i++){
      for (int j=0; j<d; j++) {
          if ((check==total)&&(board[i][j]==0)){
                  return true;
                  }
          if  (board[i][j]!=check) {
                return false;
                             }
           check++;
                       }
               }

    return true;
}

