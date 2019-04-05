#include <stdio.h>

static inline int is_same(char a, char b, char c, char p) {
  return ( a != b ? 0 :
           b != c ? 0 :
           c != p ? 0 : 1 );
}

static int is_winner(char board[3][3], char player) {
  int row, col;

  // Check rows
  for(row = 0; row < 3; ++row) {
    if (is_same(board[row][0], board[row][1], board[row][2], player)) {
      return 1;
    }
  }

  // Check columns
  for(col = 0; col < 3; ++col) {
    if (is_same(board[0][col], board[1][col], board[2][col], player)) {
      return 1;
    }
  }

  // Check diag.
  if (is_same(board[0][0], board[1][1], board[2][2], player)) {
    return 1;
  }
  if (is_same(board[0][2], board[1][1], board[2][0], player)) {
    return 1;
  }

  return 0;
}

static int in_sync(char board[3][3], int diff)
{
  int row, col, sumX = 0, sumO = 0;
  for(row = 0; row < 3; ++row) {
    for(col = 0; col < 3; ++col) {
      if(board[row][col] == 'X') {
        sumX ++;
      }
      if(board[row][col] == 'O') {
        sumO ++;
      }
    }
  }
  return sumX - sumO == diff;
}

static int validTicTacToe(char board[3][3]) {
  if(in_sync(board, 0)) {
    return !is_winner(board, 'X');
  }

  else if (in_sync(board, 1))   {
    return !is_winner(board, 'O');
  }

  return 0;
}


int main(int argc, char* argv[])
{
  int row, col, value,player = 0;
  char board[3][3] = {"123",
                      "456",
                      "789"};

  while (validTicTacToe(board)) {
    printf("\n");
    printf(" %c | %c | %c\n", board[0][0], board[0][1], board[0][2]);
    printf(" ---------\n");
    printf(" %c | %c | %c\n", board[1][0], board[1][1], board[1][2]);
    printf(" ---------\n");
    printf(" %c | %c | %c\n", board[2][0], board[2][1], board[2][2]);
    printf("\n");
    do {
      printf("%c turn: ", player&1?'O':'X');
      scanf("%d", &value);
    } while ( !(value >=1 && value <= 9) );
    row = --value/3;
    col =   value%3;

    board[row][col] = player&1?'O':'X';

    if (is_winner(board, player&1?'O':'X')) {
      printf("%c wins!!!\n", player&1?'O':'X');
      break;
    }
    player++;
  }
  return 0;
}
