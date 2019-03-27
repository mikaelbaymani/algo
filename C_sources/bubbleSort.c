#include "bubbleSort.h"

void bubbleSort(int data[], int len) {
  int i, j=0, swapped;
  do for(swapped=i=0; i<len-1-j; ++i)
    if(data[i] > data[i+1]) {
      data[i] = data[i] ^ data[i+1];
      data[i+1] = data[i+1] ^ data[i];
      data[i] = data[i] ^ data[i+1];
      swapped = 1;
    }
  while(swapped && ++j);
}
