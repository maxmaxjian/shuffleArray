#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

class solution {
public:
  solution(const vector<int> & nums) : vec(nums) {
  }

  solution(const solution & other) {
    if (this != &other)
      vec = other.vec;
  }

  solution & operator=(const solution & other) {
    if (this != &other)
      vec = other.vec;
    return *this;
  }

  vector<int> shuffle() {
    // back = backup();
    std::next_permutation(vec.begin(), vec.end());
    return vec;
  }

  void print() {
    std::for_each(vec.begin(), vec.end(), [](int i){std::cout << i << " ";});
    std::cout << std::endl;
  }

  solution * clone() {
    return new solution(*this);
  }

private:
  vector<int> vec;
  
public:
  class memento {
  public:
    const solution * originator;
    const solution * backup;
    
    memento(solution * a_soln) {
      originator = a_soln;
      backup = a_soln->clone();
    }
  };

// private:
//   memento * back;

  memento * backup() {
    return new memento(this);
  }

  void restore(memento * a_memento) {
    if (a_memento->originator == this)
      *this = *(a_memento->backup);
  }

  vector<int> reset(memento * a_memento) {
    restore(a_memento);
    return vec;
  }
};


int main() {
  vector<int> nums{1,2,3};

  solution soln(nums);
  std::cout << "current vector:" << std::endl;
  soln.print();
  
  solution::memento * a_memento = soln.backup();
  auto shuffle = soln.shuffle();
  std::cout << "first shuffle" << std::endl;
  std::for_each(shuffle.begin(), shuffle.end(), [](int i){std::cout << i << " ";});
  std::cout << std::endl;
  
  auto reset = soln.reset(a_memento);
  std::cout << "after reset" << std::endl;
  std::for_each(reset.begin(), reset.end(), [](int i){std::cout << i << " ";});
  std::cout << std::endl;

  shuffle = soln.shuffle();
  std::cout << "second shuffle" << std::endl;
  std::for_each(shuffle.begin(), shuffle.end(), [](int i){std::cout << i << " ";});
  std::cout << std::endl;

  std::cout << "current vector:" << std::endl;
  soln.print();
}
