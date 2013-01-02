#include <iostream>
#include "../Xlib/heads/array.h"

using std::cout;
using std::endl;
using std::cin;
using Xlib::Array::Box;

#define MAX 10
#define X 0,
#define O 1,

#define MAXINT 0xFFFFFFFF
#define HIGH_X(v) (v >> 16)
#define LOW_Y(v) (v & 0x0000FFFF)
#define POINT(x, y) (x << 16 | y)


// map,  current pos, history pos, move sum
// return count route
int map_routes(const Box &map, int start_pos, int stop_pos);
int each_map(const Box &map, int start_pos, int stop_pos, Box &history, int sum);

void show_map(Box &map, int max_x, int max_y, int start = MAXINT, int stop = MAXINT);
void show_route(Box &map);

int main(int argc, char **argv, char **envp){

  int temp[MAX * MAX] = {
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

  Box map = Box(MAX, MAX);

  for (int i = 0; i < MAX; i++){
    for (int j = 0; j < MAX; j++) {
      map(j, i) = temp[i * MAX + j];
    }
  }

  int start = POINT(0, 5), stop = POINT(9, 0);

  cout<<"map: "<<endl;
  show_map(map, MAX, MAX, start, stop);

  cout<<"count routes: "<<map_routes(map, start, stop)<<endl;

  return 0;
}


int map_routes(const Box &map, int start_pos, int stop_pos) {
  // max x + y..
  Box history = Box(map.x() + map.y() + map.z());

  return each_map(map, start_pos, stop_pos, history, 0);
}

int each_map(const Box &map, int start_pos, int stop_pos, Box &history, int sum) {
  // pos
  int x = HIGH_X(start_pos), y = LOW_Y(start_pos);
  int s_x = HIGH_X(stop_pos), s_y = LOW_Y(stop_pos);
  int x_direction = s_x - x > 0 ? 1 : -1;
  int y_direction = s_y - y > 0 ? 1 : -1;

  // save route
  history(sum) = start_pos;
  int count = 0;

  // if end
  if (x == s_x && y == s_y) {
    // end identifier
    history(sum + 1) = MAXINT;

    // show route
    show_route(history);
    return 1;
  }

  //next direction
  int next_x = (x + x_direction);
  int next_y = (y + y_direction);

  // move x
  if (x != s_x && map(next_x, y)) {
    Box x_history = history;

    count += each_map(
      map, POINT(next_x, y), stop_pos, x_history, sum + 1
    );
  }

  // move y
  if (y != s_y && map(x, next_y)) {
    Box y_history = history;

    count += each_map(
      map, POINT(x, next_y), stop_pos, y_history, sum + 1
    );
  }

  // move x & y
  if ( x != s_x && y != s_y && map(next_x, next_y)) {
    Box xy_history = history;

    count += each_map(
      map, POINT(next_x, next_y), stop_pos, xy_history, sum + 1
    );
  }

  return count;
}

void init_box(Box &box, int sum, Box *route = NULL);

void show_route(Box &route){
  cout<<" --- route:  ---"<<endl;

  Box b = Box(MAX, MAX);
  init_box(b, MAX * MAX, &route);

  show_map(b, MAX, MAX);

  cout<<endl<<endl;
}

void init_box(Box &box, int sum, Box *route) {
  for (int i = 0; i < sum; i++) { box(i) = 0; }

  if ( !route ){ return ;}

  for (int i = 0; ; i++) {
    int pos = (*route)(i);

    if ( pos == MAXINT ) { break; }
    
    box(HIGH_X(pos), LOW_Y(pos)) = 1;
  }
}

void show_map(Box &map, int max_x, int max_y, int start, int stop) {
  int x = HIGH_X(start), y = LOW_Y(start);
  int s_x = HIGH_X(stop), s_y = LOW_Y(stop);

  for (int i = 0; i < max_y; i++) {
    for (int j = 0; j < max_x; j++) {
      if ( map(j, i) ) {
        if (i == y && j == x) {
          cout<<"S";
        } else if (i == s_y && j == s_x) {
          cout<<"E";
        } else {
          cout<<"O";
        }
      } else { cout<<"X"; }
      cout<<" ";
    }
    cout<<endl;
  }
}

