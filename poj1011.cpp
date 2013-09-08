#include <iostream>
#include <algorithm>

using std::cout;
using std::cin;

class Sticks {
public:
  Sticks() {
    sticks = NULL;
    used_sticks = NULL;
  }

  ~Sticks() {
    delete [] sticks;
    delete [] used_sticks;
  }


  void reset(int size) {
    if (sticks) { delete [] sticks; }
    if (used_sticks) { delete [] used_sticks; }

    sum_len = 0;
    sticks = new int[size];
    used_sticks = new bool[size];
    used = 0;
  }


  bool push(int len) {
    sticks[used] = len;
    sum_len += len;
    used += 1;

    return true;
  }

  
  // 计算最小原长度
  int min_original_len() {
    std::sort(sticks, sticks + used);

    // 从最大段开始
    // 如果原长度不能被总长度整除则跳过
    for (int i = sticks[used - 1]; i < sum_len; i++) {
      if (sum_len % i != 0) { continue; }
      for (int j = 0; j < used; j++) { used_sticks[j] = false; }

      // 使用指定长度去尝试建立原段
      if (build(i, sum_len, 0, used - 1)) { return i; }
    }
    
    return sum_len;
  }


private:
  int *sticks;
  int sum_len;
  int used;
  bool *used_sticks;



  // 四个参数分别为要还原的长度， 所有段总长度， 当前段还原长度， 当前尝试还原的起始段索引
  bool build(int original_len, int sticks_len, int len, int start) {
    int t, next_start;

    for (int i = start; i >= 0; i--) {
      // 已经被使用过的段，直接跳过
      if (used_sticks[i]) { continue; }

      t = i + 1;
      // 如果上一段没有被使用，而且当前段长度等于上一段的长度，那么也跳过
      if (t < used && sticks[i] == sticks[t] && used_sticks[t] == false) {
        continue;
      }

      t = len + sticks[i];
      // 超长直接跳过
      if (t > original_len) {
        continue;
      } else {
        used_sticks[i] = true;

        // 同一段拼接中不往回搜索
        next_start = i - 1;

        // 完成一段后，剩下段长度等于当前段长度，成功，返回; 否则完成当前匹配，开始另一段
        if (t == original_len) {
          if (sticks_len == sticks[i]) {
            return true;
          } else {
            t = 0;
            next_start = used - 1;
          }
        }

        // 所有都完成了就返回，否则设置当前段为未使用并重新查找
        if (build(original_len, sticks_len - sticks[i], t, next_start)) {
          return true; 

        // 如果一个新的匹配开始时，最大的子段不能成功还原，那么后面所有不可能成功
        // 这一个判断很重要，如果没有，会造成大量的计算
        } else if (len == 0) {
          used_sticks[i] = false;
          return false;
        } else {
          used_sticks[i] = false;
          continue;
        }
      }
    }

    return false;
  }
};


int main(){
  int t; Sticks s;

  while (cin>>t) {
    if (t == 0) { break; }

    s.reset(t);
    
    for (int i = t; i > 0; i--) {
      cin>>t;
      s.push(t);
    }

    cout<<s.min_original_len()<<"\n";
  }

  return 0;
}

