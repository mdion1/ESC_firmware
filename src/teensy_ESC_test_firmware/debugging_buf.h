#ifndef _DEBUGGING_BUF_H_
#define _DEBUGGING_BUF_H_

#include <Arduino.h>

class debugging_buf
{
public:
  debugging_buf(int size);
  ~debugging_buf();
  void push(int val1, int val2);
  void printAll();

private:
  int * buf1;
  int * buf2;
  int index;
  int size;
};

#endif
