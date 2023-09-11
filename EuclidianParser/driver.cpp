
#include "./code/EuclidianArithmetic.hpp"
#include <iterator>
std::stack<coordinate *> MINSTACK;
double minim = INT_MAX;

void MIN(coordinate *coord, double distance, std::stack<coordinate *> stck) {
  if (distance < minim) {
    minim = distance;
    stck.push(coord);
  }
}

void swap(coordinate *a, coordinate *b) {
  coordinate temp = *b;
  *b = *a;
  *a = temp;
}

void sort1D(vector<coordinate *> arr) {
  // consider x1 as 0 for all coordinates and sort only based on x0
  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 16; j++) {
      if (arr[i] != 0x0 && arr[j] != 0x0) {
        if (arr[i]->x0() > arr[j]->x0() && i != j) {
          swap(arr[i], arr[j]);
        }
      }
    }
  }
}

// in progress
// vector forms the rows of the two-dimensional euclidian plane
// coordinate ** represents a single line in the euclidian plane from left to
// right to look up or down, observe the respective row of nums and compare to
// MIN()
void closestdistance(vector<coordinate *> nums) {
  // take distance between all pairs using described algorithm splitting list
  // into left and right after origin sort furthest distance should be between
  // points on opposite end of splitted array
  coordinate *temp;
  coordinate *p = 0x0;
#pragma omp parallel for
  for (unsigned x = 1; x < nums.size(); x++) {
    p = nums[x];
    if (nums[x + 1] == 0x0) {
      return;
    }
    if (p != 0x0) {
      p->distance(nums[x + 1]) < minim ? minim = p->distance(nums[x + 1])
                                       : minim = minim;
      p->distance(nums[x - 1]) < minim ? minim = p->distance(nums[x - 1])
                                       : minim = minim;
    }
  }
}
// temp used for nearest pair of points
// return the pair as nums
// sort nums
// should now be sorted in terms of euclidian plane
// split nums into left and right halves using algorithm

void empty(void) {
  while (!MINSTACK.empty()) {
    MINSTACK.pop();
  }
}

void printplane(vector<coordinate *> R) {
  for (int i = 0; i < R.size(); i++) {
    R[i]->printcoords();
  }
}
int main(int argc, char **argv) {
  PlaneArithmetic *inst = new PlaneArithmetic();
  char **t = argv;
  if (t[1] != nullptr) {
    vector<coordinate *> array = inst->filein(t[1]);
    if (array.empty()) {
      cout << "EMPTY" << endl;
      return -1;
    } else {
      sort1D(array);
      printplane(array);
      // printplane(array);
      closestdistance(array);
      cout << minim << " is shortest distance" << endl;
      cout << "=END=" << endl;
      empty();
      return 1;
    }
  } else {
    cout << "INVALID FILENAME" << endl;
    return -1;
  }
  //  array set to array of points, now design sort below
  //  fix below
  /*
    printplane(array);
  coordinate *ans = closestpair(array);
  */

  // array of numbers is now set, now for sorting and
  // good parse
}
