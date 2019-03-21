#include "bubbleSort.h"

void bubbleSort(int data[], int len) {
  int i, swapped;
  do for(swapped=i=0; i<len-1; ++i)
    if(data[i] > data[i+1]) {
      data[i] = data[i] ^ data[i+1];
      data[i+1] = data[i+1] ^ data[i];
      data[i] = data[i] ^ data[i+1];
      swapped = 1;
    }
  while(swapped);
}
