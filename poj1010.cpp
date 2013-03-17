#include <iostream>
#include <algorithm>

using std::cout;  using std::cin;  using std::endl;

#define MAX_TYPES         25
#define MAX_SELL_STAMPS   4

// 存放4张邮票在这里
class StampsGroup {
public:
  // 初始为－1表示没存放邮票
  StampsGroup(){
    count = 0;
    result_count = 1;
    result_type = 0;
    max_used_index = -1;
    for (int i = 0; i < MAX_SELL_STAMPS; i++) {
      stamps[i] = -1;
    }
  }

  StampsGroup(const StampsGroup & sg) {
    *this = sg;
  }

  StampsGroup & operator=(const StampsGroup & sg) {
    for (int i = 0; i < MAX_SELL_STAMPS; i++) {
      stamps[i] = sg.stamps[i];
    }
    count = sg.count;
    result_count = sg.result_count;
    result_type = sg.result_type;
    max_used_index = sg.max_used_index;

    return *this;
  }

  // 为了方便取stamps。。。
  int & operator[](const int i) {
    if (i > max_used_index) { max_used_index = i; }
    return stamps[i];
  }

  // 邮票的比较，本来是重载<的，后来思想凌乱为了返回是比较到哪里就返回了int。。。。
  int compare(const StampsGroup & sg) {
    int tc = types_count(), sgtc = sg.types_count();

    if (tc < sgtc) {
      return -1;
    } else if (tc == sgtc) {
      if (max_used_index < 0) { return 0; }
      if (stamps[max_used_index] > sg.stamps[sg.max_used_index]) {
        return 11;
      } else if (stamps[max_used_index] < sg.stamps[sg.max_used_index]) {
        return -11;
      } else {
        if (stamps[0] < sg.stamps[0]) {
          return 21;
        } else if (stamps[0] > sg.stamps[0]) {
          return -21;
        }
      }
      return 0;
    } else {
      return 1;
    }
  }


  // 计算一共有多少种类型的屶村，主要是排除相同的
  int types_count() const {
    int tmp = 4;

    if (stamps[0] < 0) { return 0; }

    for (int i = MAX_SELL_STAMPS - 1; i > 0; i--) {
      if (stamps[i] < 0) {
        tmp -= 1;
        continue;
      } else if (stamps[i] == stamps[i - 1]) {
        tmp -= 1;
      }
    }

    return tmp;
  }

  
  int count;
  int result_count;
  int result_type;
  int max_used_index;

private:
  int stamps[MAX_SELL_STAMPS];
};



// 这个类的实例主要是用来输入邮票和计算结果
class Stamps {
public:
  Stamps(){
    reset();
  }


  // 增加一种邮票，就这个大于4张的不再输入，前提是排序好的，呃懒的改了
  void add_type(int stamp){
    if (last_type != stamp) {
      last_type = stamp;
      last_type_count = 1;
    } else {
      last_type_count += 1;
      if (last_type_count > MAX_SELL_STAMPS) { return; }
    }
    
    types[types_count++] = stamp;
  }


  // 完成了输入，在这里排序一下。。。
  void completed_input() {
    std::sort(types, types + types_count);
  }


  // 计算最佳选择
  void customer_best(int value) {
    cout<<value;

    StampsGroup sg = best_result(value, MAX_SELL_STAMPS, StampsGroup());

    if (sg.count != value) {
      cout<<" ---- none\n";
    } else {
      cout<<" ("<<sg.types_count()<<"): ";

      show_stamps_group(sg);
    }
  }


  // 这个递归就是计算用的
  StampsGroup best_result(int value, int lack, StampsGroup result, int index = 0) {
    int tmp_result_count = result.count;
    int compare_result;
    StampsGroup best, tmp_sg;

    for (int i = index; i < types_count; i++) {
      result[MAX_SELL_STAMPS - lack] = i;
      result.count = tmp_result_count + types[i];

      if (result.count > value) { continue; }

      if (result.count < value && lack > 1) {
        tmp_sg = best_result(value, lack - 1, result, i);
      } else {
        tmp_sg = result;
      }

      if (tmp_sg.count == value) {
        compare_result = tmp_sg.compare(best);

        if (compare_result == 0) {
          best.result_count += 1;
        } else if (compare_result > 0) {
          best = tmp_sg;
          best.result_type = compare_result;
        }
      }
    }

    return best;
  }



  // 把这个实例重置，用来接收新的邮票数据
  void reset() {
    types_count = 0;
    last_type = -1;
    last_type_count = 0;
  }


private:
  int types[MAX_TYPES];
  int types_count;

  int last_type;
  int last_type_count;


  // 显示结果
  void show_stamps_group(StampsGroup & sg) {
    if (sg.result_count > 1) {
      cout<<"tie\n";
      return ;
    }

    for (int i = 0; i < MAX_SELL_STAMPS; i++) {
      if (sg[i] < 0) { break; }
      cout<<types[sg[i]]<<" ";
    }
    cout<<endl;
  }
};




int main() {
  Stamps stamps;
  int tmp;

  while (cin>>tmp) {
    // 输入所有邮票
    while (tmp) {
      stamps.add_type(tmp);
      cin>>tmp;
    }

    // 完成输入了
    stamps.completed_input();

    // 接收输入的客户，然后输出结果
    while (cin>>tmp && tmp) { stamps.customer_best(tmp); }

    // 完成了，重围邮票计算对象
    stamps.reset();
  }

  return 0;
}
