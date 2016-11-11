#include <algorithm> // std::sort()
#include <chrono> // std::chrono
#include <deque> // std::deque
#include <functional> // std::ref()
#include <iostream> // std::cout
#include <limits> // std::numeric_limits
#include <random> // std::random_device etc
#include <vector> // std::vector

/**
 * @brief Return a container with randomly initialized values.
 *
 * @tparam Cont Container type.
 * @param count Number of container elements.
 *
 * @return Initialized container.
 */
template <typename Cont>
static Cont container(std::size_t count)
{
  using T = typename Cont::value_type;
  static std::random_device rd;
  static std::default_random_engine dre{rd()};
  static std::uniform_int_distribution<T> prob_dist{
    0, std::numeric_limits<T>::max()};
  Cont container(count);
  for (auto& elem : container)
    elem = prob_dist(dre);
  return container;
}

/**
 * @brief Execute a function and output its duration to standard output.
 *
 * @tparam F Type of function.
 * @tparam Args Type of function arguments.
 * @param fn Function.
 * @param args Function arguments.
 */
template <typename F, typename... Args>
static void timed_exec(const F& fn, Args&&... args)
{
  using namespace std::chrono;
  auto now = steady_clock::now();
  fn(std::forward<Args>(args)...);
  auto elapsed = steady_clock::now() - now;
  auto msec = duration_cast<milliseconds>(elapsed);
  std::cout << "duration: " << msec.count() << " msec\n";
}

void task(std::vector<int>& vec, std::deque<int>& deq)
{
  std::sort(vec.begin(), vec.end());
  std::sort(deq.begin(), deq.end());
}


int main(int argc, char* argv[])
{
  constexpr std::size_t size = 1'000'000;
  auto vec = container<std::vector<int>>(size);
  auto deq = container<std::deque<int>>(size);
  timed_exec(task, std::ref(vec), std::ref(deq));
  
  return 0;
}
