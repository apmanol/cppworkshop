#include <iostream>
#include <future>
#include <thread>

#define CALL(FUNC) \
    do { \
      std::cout << "Calling " # FUNC "...\n"; \
      FUNC(); \
    } while(0)

const char* MSG = "Hello World++11!";

template <typename T>
struct incomplete; // debug only

#define DUMP_TYPE(OBJ) incomplete<decltype(OBJ)> type_of_##OBJ

static inline void test_async()
{
  // std::launch::async: enable asynchronous evaluation
  // std::launch::deferred: enable lazy evaluation
  // std::async() returns a std::future
  auto handle = std::async(std::launch::async, [](){
                           std::cout << MSG << "\n";
                           });
  handle.get();
}

static inline void test_packaged_task()
{
  using TaskType = std::string();
  std::packaged_task<TaskType> task{[](){ return MSG; }};
  auto fut = task.get_future();
  std::thread computer{[&task](){ task();}};
  std::thread printer{[&fut](){
    if (fut.valid())
      std::cout << fut.get() << "\n";
  }};
  computer.join();
  printer.join();
}

int main(int argc, char* argv[])
{
  CALL(test_async);
  CALL(test_packaged_task);
  return 0;
}
