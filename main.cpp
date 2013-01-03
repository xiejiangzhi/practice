#include <iostream>
#include "../JZlib/heads/array.h"

using std::cout;
using std::endl;
using std::cin;
using JZlib::Array::Box;

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

  int start = POINT(4, 5), stop = POINT(0, 0);

  cout<<"map: "<<endl;
  show_map(map, MAX, MAX, start, stop);

  cout<<"count routes: "<<map_routes(map, start, stop)<<endl;

  return 0;
}


int map_routes(const Box &map, int start_pos, int stop_pos) {
  // max x + y..
  Box history = map.size();

  return each_map(map, start_pos, stop_pos, history, 0);
}

int each_map(const Box &map, int start_pos, int stop_pos, Box &history, int sum) {
  // pos
  int x = HIGH_X(start_pos), y = LOW_Y(start_pos);
  int e_x = HIGH_X(stop_pos), e_y = LOW_Y(stop_pos);

  // save route
  history(sum) = start_pos;

  // if end
  if (start_pos == stop_pos) {
    cout<<"show"<<endl;
    // end identifier
    history(sum + 1) = MAXINT;

    // show route
    show_route(history);
    return 1;
  }

  int count = 0;
  // -1 and 1
  for (int i = -1; i < 2; i += 2) {
    // next pos
    int next_x = (x + i);
    int next_y = (y + i);
    int points[][2] = {
      {next_x, y}, {next_x, next_y}, {x, next_y}
    };

    for (int j = 0; j < (sizeof(points) / sizeof(points[0])); j++) {
      int px = points[j][0], py = points[j][1];
      int point = POINT(px, py);

      if ( map.between(px, py) && map(px, py) && history.find(point, sum) < 0 ) {
        Box h = history;

        count += each_map(map, point, stop_pos, h, sum + 1);
      }
    }

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
    
    int status;

    box(HIGH_X(pos), LOW_Y(pos)) = 1;
  }
}

void show_map(Box &map, int max_x, int max_y, int start, int stop) {
  int x = HIGH_X(start), y = LOW_Y(start);
  int s_x = HIGH_X(stop), s_y = LOW_Y(stop);

  for (int i = 0; i < max_y; i++) {
    for (int j = 0; j < max_x; j++) {
      int val = map(j, i);

      if ( val ) {
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

