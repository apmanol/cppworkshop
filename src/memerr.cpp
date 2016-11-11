#include <cstring>
#include <memory>
#include <iostream>

// uncomment for individual errors
//#define DO_ERROR_ADDRESS_SANITIZER
//#define DO_ERROR_STACK_PROTECTOR
//#define DO_ERROR_FORTIFY_SOURCE

#define STR "deadbeefdeadbeefdeadbeefdeadbeef"

int* fetch_mem()
{
  int* array = new int[100];
  delete[] array;
  return array;
}

void err_asan()
{
#ifdef DO_ERROR_ADDRESS_SANITIZER
  // buffer overflow
  std::unique_ptr<int[]> buf{new int[2]};
  buf[10] = 42;

  // use after free
  int *k = fetch_mem();
  k[5] = 10;

  // // double free
  int *l = new int[3];
  l[2] = 2;
  delete[] l;
  delete[] l;

  // memory loss
  int *m = new int[1024];
  m[3] = 1;
#endif // DO_ERROR_ADDRESS_SANITIZER
}

void err_stack_protect(const char* str)
{
#ifdef DO_ERROR_STACK_PROTECTOR
  char buf[16];
  std::strcpy(buf, str);
  std::cout << buf << std::endl;
#endif // DO_ERROR_STACK_PROTECTOR
}

void err_fortify_source()
{
#ifdef DO_ERROR_FORTIFY_SOURCE
  char buf[16];
  std::strcpy(buf, STR);
  std::cout << buf << std::endl;
#endif // DO_ERROR_FORTIFY_SOURCE
}

int main(int argc, char* argv[])
{
  err_asan();
  err_stack_protect(STR);
  err_fortify_source();
  return 0;
}
