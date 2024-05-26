
#include "2048.h"

#ifdef __linux__
int getch() {
  struct termios oldt, newt;
  int ch;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  return ch;
}
#endif

void clear_screen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

int main() {
  main_game();

  return 0;
}

void main_game() {
  init_map();

  int gameshouldclose = 0;

  while (!gameshouldclose) {
    clear_screen();
    print_map();
    int key = getch();
    if (key == 224)
      key = getch();
    if (key == 27 || key == 101)
      break;
    else if (key == 72 || key == 119)
      up();
    else if (key == 80 || key == 115)
      down();
    else if (key == 75 || key == 97)
      left();
    else if (key == 77 || key == 100)
      right();
    else if (key == 114)
      reset();
    else
      continue;

    int res = check();
    if (res == 0)
      random_map();
    else if (res == -1)
      gameshouldclose = gameover();
  }
}
int gameover() {
  printf("FINAL SCORE: %d\n", score);
  printf("PRESS R TO PLAY ANGIN\nPRESS E TO EXIT\n");
  while (1) {
    int key2 = getch();
    if (key2 == 224)
      key2 = getch();
    if (key2 == 114) {
      reset();
      return 0;
    } else if (key2 == 27 || key2 == 101)
      return 1;
  }
  return -1;
}
void init_map() {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      map[i][j] = 0;
    }
  }
  random_map();
}
void random_map() {
  int i, j;
  srand(time(NULL));
  do {
    i = rand() % size;
    j = rand() % size;
  } while (map[i][j] != 0);
  map[i][j] = 2;
}
void print_map() {
  printf(" SCORE: %d\n", score);
  for (int i = 0; i < size; i++) {
    printf("+----+----+----+----+\n");
    printf("|");
    for (int j = 0; j < size; j++) {
      if (map[i][j] < 10) {
        printf("  %d ", map[i][j]);
      } else if (map[i][j] < 100) {
        printf(" %d ", map[i][j]);
      } else if (map[i][j] < 1000) {
        printf(" %d", map[i][j]);
      } else {
        printf("%d", map[i][j]);
      }
      printf("|");
    }
    printf("\n");
  }
  printf("+----+----+----+----+\n");
}
//平移->合并->平移
void up() {
  for (int j = 0; j < size; j++) {
    for (int i = 0; i < size; i++) {
      if (map[i][j] == 0) {
        for (int k = i + 1; k < size; k++) {
          if (map[k][j] != 0) {
            int temp = map[k][j];
            map[k][j] = map[i][j];
            map[i][j] = temp;
            break;
          }
        }
      }
    }
    for (int i = 1; i < size; i++) {
      if (map[i - 1][j] == map[i][j]) {
        map[i - 1][j] *= 2;
        score += map[i - 1][j];
        map[i][j] = 0;
      }
    }
    for (int i = 0; i < size; i++) {
      if (map[i][j] == 0) {
        for (int k = i + 1; k < size; k++) {
          if (map[k][j] != 0) {
            int temp = map[k][j];
            map[k][j] = map[i][j];
            map[i][j] = temp;
            break;
          }
        }
      }
    }
  }
}
void down() {
  for (int j = 0; j < size; j++) {
    for (int i = size - 1; i > -1; i--) {
      if (map[i][j] == 0) {
        for (int k = i - 1; k > -1; k--) {
          if (map[k][j] != 0) {
            int temp = map[k][j];
            map[k][j] = map[i][j];
            map[i][j] = temp;
            break;
          }
        }
      }
    }
    for (int i = size - 2; i > -1; i--) {
      if (map[i + 1][j] == map[i][j]) {
        map[i + 1][j] *= 2;
        score += map[i + 1][j];
        map[i][j] = 0;
      }
    }
    for (int i = size - 1; i > -1; i--) {
      if (map[i][j] == 0) {
        for (int k = i - 1; k > -1; k--) {
          if (map[k][j] != 0) {
            int temp = map[k][j];
            map[k][j] = map[i][j];
            map[i][j] = temp;
            break;
          }
        }
      }
    }
  }
}
void left() {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (map[i][j] == 0) {
        for (int l = j + 1; l < size; l++) {
          if (map[i][l] != 0) {
            int temp = map[i][l];
            map[i][l] = map[i][j];
            map[i][j] = temp;
            break;
          }
        }
      }
    }
    for (int j = 1; j < size; j++) {
      if (map[i][j - 1] == map[i][j]) {
        map[i][j - 1] *= 2;
        score += map[i][j - 1];
        map[i][j] = 0;
      }
    }
    for (int j = 0; j < size; j++) {
      if (map[i][j] == 0) {
        for (int l = j + 1; l < size; l++) {
          if (map[i][l] != 0) {
            int temp = map[i][l];
            map[i][l] = map[i][j];
            map[i][j] = temp;
            break;
          }
        }
      }
    }
  }
}
void right() {
  for (int i = 0; i < size; i++) {
    for (int j = size - 1; j > -1; j--) {
      if (map[i][j] == 0) {
        for (int l = j - 1; l > -1; l--) {
          if (map[i][l] != 0) {
            int temp = map[i][l];
            map[i][l] = map[i][j];
            map[i][j] = temp;
            break;
          }
        }
      }
    }
    for (int j = size - 2; j > -1; j--) {
      if (map[i][j + 1] == map[i][j]) {
        map[i][j + 1] *= 2;
        score += map[i][j + 1];
        map[i][j] = 0;
      }
    }
    for (int j = 0; j < size; j++) {
      if (map[i][j] == 0) {
        for (int l = j - 1; l > -1; l--) {
          if (map[i][l] != 0) {
            int temp = map[i][l];
            map[i][l] = map[i][j];
            map[i][j] = temp;
            break;
          }
        }
      }
    }
  }
}
void reset() {
  init_map();
  score = 0;
}
int check() {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (map[i][j] == 0)
        return 0;
    }
  }
  for (int i = 1; i < size; i++) {
    for (int j = 1; j < size; j++) {
      if ((map[i][j] == map[i - 1][j]) || (map[i][j] == map[i][j - 1]))
        return 1;
    }
  }
  return -1;
}