#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct object_{
    char type;
    int num_gen;
    int num_food;
}object;

typedef struct pos_ {
  int x,y;
}pos;

int GEN_PROC_RABBITS;
int GEN_PROC_FOXES;
int GEN_FOOD_FOXES;
int N_GEN;
int R;
int C;
int N;
object **world;
object **new_world;
int current_gen;


void print_world() {
  int x,y;
  for(x = 0; x < R; x++) {
    for(y = 0; y < C; y++) {
      printf("%c", world[x][y].type);
    }
    printf("\n");
  }
}

void fill_world(){
  int i, x, y;
  char name[6];
  for(i = 0; i < N; i++) {
    scanf("%s %d %d", &name, &x, &y);
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
void move_rabbit(int x, int y) {
  object current = world[x][y], new;
  int p = 0, new_pos_index;
  pos free_pos[4], new_pos;
  //North
  if(world[x][y - 1].type == ' ') {
    free_pos[p].x = x;
    free_pos[p].y = y - 1;
    p++;
  }
  //East
  if(world[x + 1][y].type == ' ') {
    free_pos[p].x = x + 1;
    free_pos[p].y = y;
    p++;
  }
  //South
  if(world[x][y+1].type == ' ') {
    free_pos[p].x = x;
    free_pos[p].y = y + 1;
    p++;
  }
  //West
  if(world[x - 1][y].type == ' ') {
    free_pos[p].x = x - 1;
    free_pos[p].y = y;
    p++;
  }
  if(p == 0){
    free_pos[0].x = x;
    free_pos[0].y = y;
    p = 1;
  }
  else {
    if(current.num_gen == 0) {
      new = new_world[x][y];
      if(new.type == 'F'){
	new.num_food = GEN_FOOD_FOXES;
      }
      else if(new.type == ' '){
	new.type = current.type;
	new.num_gen = GEN_PROC_RABBITS;
      }
      current.num_gen = GEN_PROC_RABBITS + 1;
    }
  }
  new_pos_index = (x + y + current_gen) % p;
  new_pos = free_pos[new_pos_index];
  new = new_world[new_pos.x][new_pos.y];
  if(new.type == 'F'){
    new.num_food = GEN_FOOD_FOXES;
  }
  else if(new.type == 'R'){
    if(current.num_gen - 1 < new.num_gen)
      new.num_gen = current.num_gen - 1;
  }
  else {
    new.type = current.type;
    new.num_gen = current.num_gen - 1;
  }
}

void move_fox(int x, int y) {
  object current = world[x][y], new;
  int p, new_pos_index;
  pos free_pos[4], new_pos;
  char counting = ' ';
  //North
  if(world[x][y - 1].type == 'R') {
    free_pos[p].x = x;
    free_pos[p].y = y - 1;
    p++;
  }
  //East
  if(world[x + 1][y].type == 'R') {
    free_pos[p].x = x + 1;
    free_pos[p].y = y;
    p++;
  }
  //South
  if(world[x][y+1].type == 'R') {
    free_pos[p].x = x;
    free_pos[p].y = y + 1;
    p++;
  }
  //West
  if(world[x - 1][y].type == 'R') {
    free_pos[p].x = x - 1;
    free_pos[p].y = y;
    p++;
  }
  if(p==0){
    //North
    if(world[x][y - 1].type == ' ') {
      free_pos[p].x = x;
      free_pos[p].y = y - 1;
      p++;
    }
    //East
    if(world[x + 1][y].type == ' ') {
      free_pos[p].x = x + 1;
      free_pos[p].y = y;
      p++;
    }
    //South
    if(world[x][y+1].type == ' ') {
      free_pos[p].x = x;
      free_pos[p].y = y + 1;
      p++;
    }
    //West
    if(world[x - 1][y].type == ' ') {
      free_pos[p].x = x - 1;
      free_pos[p].y = y;
      p++;
    }
  }
  if(p == 0){
    free_pos[0].x = x;
    free_pos[0].y = y;
    p = 1;
  }
  else {
    if(current.num_gen == 0) {
      new = new_world[x][y];
      new.type = current.type;
      new.num_food = GEN_FOOD_FOXES;
      current.num_gen = GEN_PROC_FOXES + 1;
    }
  }
  new_pos_index = (x + y + current_gen) % p;
  new_pos = free_pos[new_pos_index];
  new = new_world[new_pos.x][new_pos.y];
  if(new.type == 'R'){
    new.type = 'F';
    new.num_gen = current.num_gen;
    new.num_food = GEN_FOOD_FOXES;
  }
  else if(new.type == 'F'){
    if(current.num_gen - 1 < new.num_gen)
      new.num_gen = current.num_gen - 1;
    else if(current.num_gen - 1 == new.num_gen)
      if(current.num_food - 1 > new.num_food) {
	new.num_food = current.num_food - 1;
      }

  }
  else {
    new.type = current.type;
    new.num_food = current.num_food - 1;
    new.num_gen = current.num_gen - 1;
  }
}
void move(int x, int y) {
  if(world[x][y].type == 'R') {
    move_rabbit(x, y);
  }
  else if(world[x][y].type == 'F') {
    move_fox(x, y);
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
  current_gen = 0;
  world = (object **)malloc(sizeof(object*) * R);
  new_world = (object **)malloc(sizeof(object*) * R);
  int i;
  for(i = 0; i < R; i++) {
    world[i] = (object *)malloc(C * sizeof(object));
    new_world[i] = (object *)malloc(C * sizeof(object));
  }
  fill_world();
  int x,y;
  for(x = 0; x < R; x++) {
    for(y = 0; y < C; y++) {
      move(x,y);
    }
  }
  print_world();

}
