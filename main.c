#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

char symbols[] = { ' ', 'X', 'O' };

int table[] = {
  0,

  0,
  0,
  0,

  0,
  0,
  0,

  0,
  0,
  0
};


void clear()
{
  system(CLEAR);
}

int get_int(char *message)
{
  int number;

  printf("%s", message);
  scanf("%d", &number);

  return number;
}

void print_table()
{
  int i = 1;

  printf("  --- --- ---\n");

  for (int y = 1; y <= 3; y++)
  {
    for (int x = 1; x <= 3; x++)
    {
      int player = table[i];
      char sym = symbols[player];

      printf(" | ");

      if (player == 0)
        printf("\033[2m%i\033[0m", i);
      else
        printf("\033[1;%sm%c\033[0m", (player == 1) ? "91" : "94", sym);

      i++;
    }

    printf(" |\n");
  }

  printf("  --- --- ---\n");
}

int check_winner() {

  char *wins[] = {
    "123",
    "456",
    "789",

    "159",
    "357",

    "147",
    "258",
    "369"
  };

  for (int i = 0; i < 8; i++)
  {
    char *str = wins[i];
    int moves_count[] = { 0, 0, 0 };

    for (int j = 0; j < 3; j++)
    {
      int idx = str[j] - '0';
      int player = table[idx];

      moves_count[player]++;
    }
    
    for (int player = 1; player <= 2; player++)
      if (moves_count[player] == 3)
        return player;
  }


  return 0;
}

int main()
{
  int index;
  int player = 1; // Start X
  int moves = 0;

  clear();
  print_table();

  while (1)
  {
    index = get_int("\n\nSelect a number: ");
    clear();

    if (index >= 1 && index <= 9 && table[index] == 0)
    {
      table[index] = player;
      player = (player == 1) ? 2 : 1;
      moves++;
    }

    int winner = check_winner();

    if (winner)
    {
      char sym = symbols[winner];

      printf("\033[1;%sm%c\033[0m", (winner == 1) ? "91" : "94", sym);

      printf("\033[1;32m");
      printf(" Won!\n");
      printf("\033[0m");
    }
    else if (moves >= 9)
    {
      printf("\033[1;33m");
      printf("Draw!\n");
      printf("\033[0m");
    }
    
    print_table();

    if (winner || moves >= 9)
    {
      for (int i = 0; i < 10; i++)
        table[i] = 0;
      moves = 0;

      return 0;
    }
  }
}
