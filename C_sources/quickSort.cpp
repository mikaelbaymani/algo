#include<iostream>
#include<vector>
#include<fstream>
#include<iterator>
using namespace std;

int partition(vector<int>& vec, int first, int end)
{
  int pivot_elm = vec[first];
  int i = first + 1;
  for (int j = first + 1; j < end; ++j)
    if (vec[j] < pivot_elm)
      iter_swap(vec.begin()+j, vec.begin()+i++);

  iter_swap(vec.begin()+first, vec.begin()+i-1);
  return i-1;
}

void quickSort(vector<int>& vec, int end, int first=0)
{
  if (first < end)
  {
    int q = partition(vec, first, end);
    quickSort(vec, q, first);
    quickSort(vec, end, q+1);
  }
}

int main(int argc, char* argv[])
{
  ifstream datafile("quickSort.txt");
  istream_iterator<int> start(datafile), end;
  vector<int> data(start, end);

  quickSort(data, data.size());

  for (vector<int>::iterator it = data.end()-10;
       it != data.end();
       ++it)
    cout << *it << endl;

  return 0;
}