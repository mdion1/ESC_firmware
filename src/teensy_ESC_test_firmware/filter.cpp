#include "filter.h"

filter::filter(int _size)
{
  size = _size;
  buf = new int[size];
  for (int i = 0; i < size; i++)
    buf[i] = 0;
  index = 0;
  sum = 0;
}

filter::~filter()
{
  delete[] buf;
}

void filter::push(int val)
{
  sum += val - buf[index];
  buf[index] = val;
  index++;
  index %= size;
}

int filter::getAvg()
{
  return sum / size;
}
