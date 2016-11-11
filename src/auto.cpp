#define CATCH_CONFIG_MAIN

#include <cassert>      // assert
#include <type_traits>  // std::is_same
#include <utility>      // std::move
#include <map>          // 

#include "catch.hpp"

/// test samples
template <typename T, typename U>
auto f(T a, U b)
{
  return a + b;
}


TEST_CASE("Type decuction examples", "[deduction]")
{
  // CHECK is the basic component of "catch" unit test framwork.
  // Is an assert-like macro used to check the validity of some expression.
  // For more info you can check @
  // https://github.com/philsquared/Catch/blob/master/docs/tutorial.md
  // A basic example:
  int one = 1;
  one ++;
  CHECK((one == 2));  

  // classic integer case (by value case)
  // std::is_same<typename T, typename U> if T and U name the same type with the
  // same const-volatile qualifications, provides the member constant value
  // equal to true. Otherwise  value is false.
  auto a = 1 + 2;
  CHECK((std::is_same<decltype(a), int>::value));

  // now and a const double (reference case)
  const auto &b = 1 + 1.2;
  CHECK((std::is_same<decltype(b), const double &>::value));

  // function return type deduction
  auto k = f(1, 1.2);
  CHECK((std::is_same<decltype(k), void>::value));

  // iterator cases
  typedef std::map<std::pair<unsigned long, std::string>, unsigned long> SomeMap;
  SomeMap some_map{{{2, "foo"}, 3}, {{3, "bar"}, 5}};
  auto itr = some_map.find(std::make_pair(2,"foo"));
  CHECK((std::is_same<decltype(itr), void>::value));
  auto first_element = itr->first;
  CHECK((std::is_same<decltype(first_element), SomeMap::key_type>::value));

  // pointer to reference example
  const auto &n = 5;
  const auto *np = &n;
  CHECK((std::is_same<decltype(np), const int *>::value));

  // try to force deduce rvalue but...
  auto &&nr = n;
  CHECK((std::is_same<decltype(nr), const int &>::value));

  // The rule to remember when dealing with references is that combining two
  // reference types mins the number of ampersands  between them.
  // & + & = & (of course)
  // & + && = &
  // && + & = &
  // && + && = &&

  // but this
  auto &&mv = 42;
  CHECK((std::is_same<decltype(mv), void>::value));
  // or
  auto &&mv2 = std::move(a);  // move is no more than a cast to &&
  CHECK((std::is_same<decltype(mv2), int &&>::value));

  // cv - qualifiers
  int i = 5;
  const auto &&mv3 = static_cast<const int&&>(i);
  CHECK((std::is_same<decltype(mv3), const int &&>::value));
}
