#include <iostream>
#include <cstdlib>

#define MAX_LINES   1000

using std::cout; using std::cin; using std::endl;

struct RLE {
  unsigned char value;
  int count;
};

class Image {
public:
  Image(int _width){
    width = _width;
    rle_len = 0;
    pixels = 0;
    abs_pixel = -1;
    abs_count = 0;
  }

  void write(int pixel, long long count) {
    rle[rle_len].value = pixel;
    rle[rle_len].count = count;
    rle_len += 1;
    pixels += count;
  }

  
  void end() {
    columns = pixels / width;
    if (pixels % width > 0) { columns += 1; }
    long long pos = 0;
    int rle_count, rle_row;

    for (int i = 0; i < rle_len; i++) {
      if (pixels <= width && rle[i].count > 2) {
        pos = count_diff(pos, 1, i);

        add_abs_pixel(0, rle[i].count - 2);
        pos += rle[i].count - 2;

        pos = count_diff(pos, 1, i);
      } else {
        pos = count_diff(pos, rle[i].count, i);
      }
    }

    add_abs_pixel(-1);
  }

  long long count_diff(long long pos, long long count, short rle_pos) {
    int min_count_row = width + 1;

    if ( count > min_count_row * 2 ) {
      int no_count = count - min_count_row * 2;

      count_diff(pos, min_count_row, rle_pos);
      count -= min_count_row; pos += min_count_row;

      add_abs_pixel(0, no_count);
      count -= no_count; pos += no_count;
    } else if (same_rle(rle_pos, min_count_row)) {
      if (count > min_count_row) {
        int before = count - min_count_row;

        add_abs_pixel(max_diff(pos), before);
        pos += before; count -= before * 2;

        for (int i = 0; i < count; i++, pos++) {
          add_abs_pixel(max_diff(pos));
        }
        count = before;
      }

      add_abs_pixel(max_diff(pos), count);
        
      return (pos + count);
    }

    for (int i = 0; i < count; i++, pos++) {
      add_abs_pixel(max_diff(pos));
    }

    return pos;
  }

private:
  RLE rle[MAX_LINES];
  long long width;
  long long rle_len;
  long long pixels;
  int columns;

  int abs_pixel;
  long long abs_count;

  bool same_rle(long long rle_pos, int min_count_row) { 
    return (rle_pos == 0 || rle[rle_pos - 1].count >= min_count_row) &&
    (rle_pos - 1 == rle_len || rle[rle_pos + 1].count >= min_count_row);
  }

  unsigned char get(long long pos) {
    long long tmp = 0;

    for (int i = 0; i < rle_len; i++) {
      tmp += rle[i].count;

      if (pos < tmp) { return rle[i].value; }
    }

    return 0;
  }

  int max_diff(long long pos) {
    int tmp, max = 0;
    int x, y, ox = pos % width, oy = pos / width;
    long long tpos;

    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
        if (i == 0 && j == 0) { continue; }
        tpos = pos + j * width + i;
        x = ox + i; y = oy + j;

        if (tpos < 0 || tpos >= pixels || x < 0 ||
          x >= width || y < 0 || y >= columns) { continue; }

        tmp = abs(get(pos) - get(tpos));
        if (tmp > max) { max = tmp; }
      }
    }

    return max;
  }

  void add_abs_pixel(int pixel, int count = 1) {
    if (abs_pixel != pixel) {
      if (abs_pixel != -1) { out_rle(); }
      abs_pixel = pixel;
      abs_count = count;
    } else {
      abs_count += count;
    }
  }

  void out_rle() {
    cout<<abs_pixel<<" "<<abs_count<<endl;
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

      if (count > 0) { img.write(pixel, count); }
    }
  }

  return 0;
}
