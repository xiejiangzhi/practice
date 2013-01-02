#include <iostream>
#include "../Xlib/heads/array.h"

using std::cout;
using std::endl;
using std::cin;
using Xlib::Array::Box;

#define MAX 10
#define X 0,
#define O 1,

#define START POINT(0, 0)
#define TARGET POINT(9, 9)

#define HIGH_X(v) (v >> 16)
#define LOW_Y(v) (v & 0x0000FFFF)
#define POINT(x, y) (x << 16 | y)


// map,  current pos, history pos, move sum
// return count route
int map_routes(Box &maps, int start_pos, int stop_pos);
int each_maps(Box &maps, int point, Box &history, int sum);

void show_maps(Box &maps, int max_x, int max_y);
void show_route(Box &maps);

int main(int argc, char **argv, char **envp){

  int maps[MAX * MAX] = {
    O O O O O O O O O O
    O O X X X O X X X O
    O O X X X O X X X O
    O X O X X O O O O O
    O X X O X X X X O O
    O X X X O X X X X O
    O O O X X O X X X O
    O X X O X X O X X O
    O X X X O X X O X O
    O O O O O O O O O O
  };

  Box *m = new Box(MAX, MAX);
  Box *history = new Box(MAX, MAX);

  for (int i = 0; i < MAX * MAX; i++){
    (*m)(i) = maps[i];
  }

  cout<<"map: "<<endl;
  show_maps(*m, MAX, MAX);

  cout<<"count routes: "<<each_maps(*m, START, *history, 0)<<endl;

  delete history;
  delete m;

  return 0;
}


int map_routes(Box &maps, int start_pos, int stop_pos) {

}

int each_maps(Box &maps, int p, Box &history, int sum) {
  // save current pos
  int x = HIGH_X(p), y = LOW_Y(p);
  history(sum) = POINT(x, y);
  int count = 0;

  // if end
  if (x == HIGH_X(TARGET) && y == LOW_Y(TARGET)) {
    // end identifier
    history(sum + 1) = 0xFFFFFFFF;

    // show route
    show_route(history);
    return 1;
  }


  // move x
  if ((x + 1) < MAX && maps(x + 1, y)) {
    Box x_history = history;

    count += each_maps(maps, POINT(x + 1, y), x_history, sum + 1);
  }

  // move y
  if ((y + 1) < MAX && maps(x, y + 1)) {
    Box y_history = history;

    count += each_maps(maps, POINT(x, y + 1), y_history, sum + 1);
  }

  if ( (x + 1) < MAX && (y + 1) < MAX && maps(x + 1, y + 1)) {
    Box xy_history = history;

    count += each_maps(maps, POINT(x + 1, y + 1), xy_history, sum + 1);
  }

  return count;
}

void init_box(Box &box, int sum, Box *route = NULL);

void show_route(Box &maps){
  cout<<" --- route:  ---"<<endl;

  Box b = Box(MAX, MAX);
  init_box(b, MAX * MAX, &maps);

  show_maps(b, MAX, MAX);

  cout<<endl<<endl;
}

void init_box(Box &box, int sum, Box *route) {
  for (int i = 0; i < sum; i++) { box(i) = 0; }

  if ( !route ){ return ;}

  for (int i = 0; ; i++) {
    int pos = (*route)(i);

    if ( pos == 0xFFFFFFFF ) { break; }
    
    box(HIGH_X(pos), LOW_Y(pos)) = 1;
  }
}

void show_maps(Box &maps, int max_x, int max_y) {
  for (int i = 0; i < max_y; i++) {
    for (int j = 0; j < max_x; j++) {
      cout<<( maps(i, j) ? "O" : "X" )<<" ";
    }
    cout<<endl;
  }
}

