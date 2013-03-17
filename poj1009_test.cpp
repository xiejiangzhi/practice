#include <iostream>
#include <cstdlib>

#define CACHE_LINE  3

using std::cout; using std::cin; using std::endl;

class Image {
public:
  Image(int _width){
    width = _width;
    image = new unsigned char*[CACHE_LINE];

    for (int i = 0; i < CACHE_LINE; i++) {
      image[i] = new unsigned char[width];
    }

    row = col = 0;
    pixel_abs = -1; abs_count = 0;
    first_line = true; pixels_count = 0;
  }

  ~Image(){
    for (int i = 0; i < CACHE_LINE; i++) {
      delete [] image[i];
    }

    delete image;
  }


  void draw_and_out(int pixel, long long count) {
    if (count >= (5 * width)) {
      count -= width * 3;
      draw_and_out(pixel, width * 3);

      count -= width * 2;
      abs_count += count;
      pixels_count += count;
      
      draw_and_out(pixel, width * 2);
      return ;
    }

    pixels_count += count;

    for (int i = 0; i < count; i++) {
      image[row][col++] = pixel;

      if (col >= width) { col = 0; row += 1; }
      if (first_line && row == CACHE_LINE - 1 && col == 0) {
        count_diff();
        first_line = false;
        continue;
      }

      if (row >= CACHE_LINE) { count_diff(); }
    }
  }

  
  void count_diff(bool end = false) {
    int count_row;

    if (first_line) { count_row = 0; }
    else if (end) { count_row = 2; }
    else { count_row = 1; }

    for (int i = 0; i < width; i++) {
      add_pixel(max_diff(i, count_row));
    }

    if ( count_row == 1) { line_up(); }
  }

  void end() {
    if (pixels_count >= width * CACHE_LINE) {
      unsigned char *tmp = image[2];

      image[2] = image[1];
      image[1] = image[0];
      image[0] = tmp;

      count_diff(true);
    } else if (pixels_count > 0) {
      count_diff();
    }
    
    add_pixel(-1);
  }


  void out() {
    cout<<pixel_abs<<" "<<abs_count<<endl;
  }

private:
  unsigned char **image;
  long long width;
  short row;
  int col;
  short pixel_abs;
  long long abs_count;
  long long pixels_count;
  bool first_line;

  void line_up() {
    unsigned char *tmp;

    for (int i = 0; i < 2; i++) {
      tmp = image[i];
      image[i] = image[i + 1];
      image[i + 1] = tmp;
    }

    row -= 1;
  }

  void add_pixel(short pixel) {
    if (pixel != pixel_abs) {
      if (pixel_abs >= 0) { out(); }

      pixel_abs = pixel;
      abs_count = 1;
    } else {
      abs_count += 1;
    }
  }

  short max_diff(int ox, int oy) {
    short tmp, max = 0;
    int x, y;

    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
        x = ox + j; y = oy + i;

        if (
          x < 0 || x >= width || y < 0
          || y >= CACHE_LINE || (i == 0 && j == 0)
          || y * width + x >= pixels_count
        ) { continue; }

        tmp = abs(image[oy][ox] - image[y][x]);
        if (tmp > max) { max = tmp; }
      }
    }

    return max;
  }
};


int main() {
  int width, pixel;
  long long count;

  while (cin>>width) {
    if (width == 0) { cout<<"0"<<endl; break; }

    cout<<width<<endl;
    Image img = Image(width);

    while (true) {
      cin>>pixel>>count;

      if (pixel == 0 && count == 0) {
        img.end();
        cout<<"0 0"<<endl;
        break;
      }

      img.draw_and_out(pixel, count);
    }
  }

  return 0;
}
