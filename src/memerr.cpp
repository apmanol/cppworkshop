#include <cstring>
#include <memory>
#include <iostream>

// uncomment for individual errors
//#define DO_ERROR_ADDRESS_SANITIZER
//#define DO_ERROR_STACK_PROTECTOR
//#define DO_ERROR_FORTIFY_SOURCE

#define STR "deadbeefdeadbeefdeadbeefdeadbeef"

void err_asan()
{
#ifdef DO_ERROR_ADDRESS_SANITIZER
  std::unique_ptr<int[]> buf{new int[2]};
  buf[10] = 42;
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
