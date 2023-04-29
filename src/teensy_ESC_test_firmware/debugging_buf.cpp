#include "debugging_buf.h"

debugging_buf::debugging_buf(int _size)
{
  size = _size;
  buf1 = new int[size];
  buf2 = new int[size];
  for (int i = 0; i < size; i++){
    buf1[i] = 0;
    buf2[i] = 0;
  }
  index = 0;
}

debugging_buf::~debugging_buf()
{
  delete[] buf1;
  delete[] buf2;
}

void debugging_buf::push(int val1, int val2)
{
  buf1[index] = val1;
  buf2[index] = val2;
  index++;
  index %= size;
}

void debugging_buf::printAll()
{
  int i = index;
  do
  {
    Serial.print(buf1[i]);
    Serial.print('\t');
    Serial.println(buf2[i]);
    i++;
    i %= size;
  }while (i != index);
}
