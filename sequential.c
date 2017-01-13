#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct object_{
    char type;
    int num_gen;
    int num_food;
}object;

int GEN_PROC_RABBITS;
int GEN_PROC_FOXES;
int GEN_FOOD_FOXES;
int N_GEN;
int R;
int C;
int N;
object **world;


void print_world() {
  int x,y;
  for(y = 0; y < R; y++) {
    for(x = 0; x < C; x++) {
      printf("%c", world[y][x].type);
    }
    printf("\n");
  }
}

void fill_world(){
  int i, x, y;
  char name[6];
  for(i = 0; i < N; i++) {
    scanf("%s %d %d", name, &x, &y);
    object new_addition;
    if(strcmp(name, "RABBIT") == 0){
      new_addition.type='R';
      new_addition.num_gen=GEN_PROC_RABBITS;
    }else if(strcmp(name, "FOX") == 0){
      new_addition.type='F';
      new_addition.num_gen=GEN_PROC_FOXES;
      new_addition.num_food=GEN_FOOD_FOXES;
    }else if(strcmp(name, "ROCK") == 0){
      new_addition.type='*';
    }
    world[x][y] = new_addition;
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
  world = (object **)malloc(sizeof(object*) * R);
  int i;
  for(i = 0; i < R; i++) {
    world[i] = (object *)malloc(C * sizeof(object));
  }
  fill_world();
  print_world();
}
