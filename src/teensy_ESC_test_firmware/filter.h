#ifndef _FILTER_H_
#define _FILTER_H_

class filter
{
public:
  filter(int size);
  ~filter();
  void push(int val);
  int getAvg();

private:
  int * buf;
  int index;
  int sum;
  int size;
};

#endif
