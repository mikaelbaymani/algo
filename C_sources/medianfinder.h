#ifndef MEDIANFINDER_H
#define MEDIANFINDER_H

typedef struct _MedianFinder MedianFinder;

MedianFinder* medianFinderCreate();

void medianFinderFree(MedianFinder* obj);

void medianFinderAddNum(MedianFinder* obj, int num);

double medianFinderFindMedian(MedianFinder* obj);

#endif
