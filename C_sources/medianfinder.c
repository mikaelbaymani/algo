#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include "medianfinder.h"

struct _MedianFinder {
  heap* lo;
  heap* hi;
};

/** initialize your data structure here. */
MedianFinder* medianFinderCreate() {
  MedianFinder* obj = malloc(sizeof *obj);
  obj->lo = Heap(MAX, 100);
  obj->hi = Heap(MIN, 100);
  return obj;
}

void medianFinderFree(MedianFinder* obj) {
  Delete(&obj->lo);
  Delete(&obj->hi);
  free(obj);
}

void medianFinderAddNum(MedianFinder* obj, int num) {
  if (empty(obj->lo)) {
    insert(obj->lo, num);
  }

  else if (empty(obj->hi)) {
    int tmp;
    (void)peek(obj->lo, &tmp);
    if (tmp <= num) {
      insert(obj->hi, num);
    }

    else {
      pop(obj->lo);
      insert(obj->hi, tmp);
      insert(obj->lo, num);
    }
  }

  else {
    int high, low, _case;
    peek(obj->lo, &low);
    peek(obj->hi, &high);
    pop(obj->lo);
    pop(obj->hi);

    if (high < num)
      _case = 1;

    else if (low < num)
      _case = 2;

    else
      _case = 3;

    if (size(obj->lo) == size(obj->hi)) {
      if (_case == 1) {
        insert(obj->hi, num);
      }

      else {
        insert(obj->lo, num);
      }
    }

    else if (size(obj->lo) > size(obj->hi)) {
      if (_case == 3) {
        num = num ^ low;
        low = low ^ num;
        num = num ^ low;
      }
      insert(obj->hi, num);
    }

    else {
      if (_case == 1) {
        num = num ^ high;
        high = high ^ num;
        num = num ^ high;
      }
      insert(obj->lo, num);
    }

    insert(obj->lo, low);
    insert(obj->hi, high);
  }
}

double medianFinderFindMedian(MedianFinder* obj) {
  if (size(obj->hi) > size(obj->lo)) {
    int high;
    peek(obj->hi, &high);
    return high;
  }

  else if (size(obj->hi) < size(obj->lo)) {
    int low;
    peek(obj->lo, &low);
    return low;
  }

  else {
    int low, high;
    peek(obj->lo, &low);
    peek(obj->hi, &high);
    return (double)(high + low) / 2.;
  }
}
