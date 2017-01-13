#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int GEN_PROC_RABBITS;
int GEN_PROC_FOXES;
int GEN_FOOD_FOXES;
int N_GEN;
int R;
int C;
int N;
char **world;

void print_world() {
  int x,y;
  for(y = 0; y < R; y++) {
    for(x = 0; x < C; x++) {
      printf("%c ", world[y][x]);
    }
    printf("\n");
  }
}

void fill_world(){
  int i, x, y;
  char object[6], label;
  for(i = 0; i < N; i++) {
    scanf("%s %d %d", object, &x, &y);
    if(strcmp(object, "RABBIT") == 0)
      label = 'R';
    else if(strcmp(object, "FOX") == 0)
      label = 'F';
    else if(strcmp(object, "ROCK") == 0)
      label = '*';
    world[y][x] = label;
  }
}

int main() {
  scanf("%d", &GEN_PROC_RABBITS);
  scanf("%d", &GEN_PROC_FOXES);
  scanf("%d", &GEN_FOOD_FOXES);
  scanf("%d", &N_GEN);
  scanf("%d", &R);
  scanf("%d", &C);
  scanf("%d", &N);
  world = (char **)malloc(sizeof(char*) * R);
  int i;
  for(i = 0; i < R; i++) {
    world[i] = (char *)calloc(C, sizeof(char));
  }
  fill_world();
  print_world();
}
