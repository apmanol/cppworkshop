#define CATCH_CONFIG_MAIN

#include <vector>                       // std::vector
#include <algorithm>                    // std::remove_if
#include <unordered_map>                // std::unordered_map
#include <map>                          // std::map
#include <string>                       // std::string
#include <sstream>                      
#include <chrono>                       // std::chrono::now
#include <cassert>                      // assert
#include <type_traits>  // std::is_same, std::is_atihmetic, std::is_integral

#include "catch.hpp"


/// Returns a vector filled with geometric sequence values
///
/// @tparam T type of the samples
/// @param[in] sample_number number of the samples
/// @param[in] common_ratio geometric common ratio
///
/// @return vector with the values
template <typename T>
std::vector<T> generate_geometric_samples(std::size_t sample_number,
                                          T common_ratio) {
  static_assert(std::is_arithmetic<T>::value, "not arithmetic type");
  std::vector<T> v(sample_number);
  return v;
}

/// Checks if all the elements of a vector area divisible by a number
///
/// @param[in] v the vector with the elements
/// @param[in] d the test factor
///
/// @return true if all elements are divisible.
///
bool is_divisible_by(std::vector<unsigned long> &v, unsigned long d) {
  bool result = false;
  return result;
}

TEST_CASE("Geometric samples are computed", "[geometric]") {
  std::vector<unsigned long> expected{3, 9, 27, 81, 243};
  REQUIRE(generate_geometric_samples<unsigned long>(5, 3) == expected);
  auto test_vector = generate_geometric_samples<unsigned long>(20, 3);
  REQUIRE(is_divisible_by(test_vector, 7) == true);
}


/// Removes even numbers from a vector
/// 
/// @tparam T arithmetic type 
/// @param[in,out] v vector with the elements 
///
template <typename T>
void remove_even_numbers(std::vector<T> &v)
{
  static_assert(std::is_integral<T>::value, "not integral type");

  auto erase_criteria = [](auto &i) {
    bool erased = false;  ///< flag indicating if is would be erased or not
    return erased;
  };

  /// Remove pattern
  /// remove_if doesn't perform resizing, but instead it just returns the
  /// iterator to the element that follows the last element not removed.
  /// This iterator should be used by the erase to do the clean up.
  v.erase(std::remove_if(std::begin(v), std::end(v), erase_criteria),
          std::end(v));
}

TEST_CASE("Remove from a sequence","[remove]"){
  std::vector<long> input = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
                    expected = {1, 3, 5, 7, 9};
  remove_even_numbers(input);
  REQUIRE(input == expected);
}




const static std::string readonly_text = R"(C++17 (also called C++1z) is the informal name for the future revision of the C++ ISO/IEC standard. The specification for the C++17 revision is under development and "nearly feature-complete"[1] to be finished in 2017.

Expected features
Addition of a default text message for static_assert
Addition of std::string_view, a non-owning reference to a character sequence or string-slice[3]
Removal of trigraphs[4][5]
Allow typename in a template template parameter

C++17 is rolling along at a fast pace. As of June 30, the proposed set of features for the language revision is complete. That was also the day the C++17 committee held its final features meeting in Oulu, Finland, the result of which includes changes that will be available as add-ons for compilers.

One of the biggest additions to the language is std:variant. This acts like a union, but it can tell you what it currently contains. It’s basically a type-safe union implementation, and in the future it will likely be used to build advanced capabilities, like pattern matching.

(Related: C++ makes the list of languages in high demand)

For developers working with templates, the new constexpr if function will allow them to write code that instantiated depending on a compile-time condition. This would allow code to be written, (for example, that can handle integers) to be coupled with code that can handle floating-point math. During compilation, either can be favored and the other not compiled, according to the needs of the numbers present at compile time.
)";

typedef std::unordered_map<std::string, std::size_t> CountUMap;
typedef std::map<std::string, std::size_t> CountMap;

/// Count the number of unique words in a string and returns a map with the
/// counted words
///
/// @param[in] input string input
///
/// @return map with the counted words
///
template <typename T>
T count_unique_words(const std::string &input) {
  T count_map;
  std::string word;
  std::istringstream iss(input);
  while (iss >> word) {
  }

  return count_map;
}

TEST_CASE("Count words", "[counting]")
{
  const auto counted_words = count_unique_words<CountUMap>(readonly_text);
  // should count some words
  REQUIRE(counted_words.size() > 0);
  // unordered map is not sorted
  REQUIRE(std::is_sorted(counted_words.cbegin(), counted_words.cend()) ==
          false);
  auto counted_template = counted_words.find("template");
  // word "template" exists 2 times
  REQUIRE(counted_template != counted_words.end());
  REQUIRE((*counted_template).second == 2);
}

/// Measure the time needed to find a key in a map with key string
///
/// @param data the map structure
/// @param key the key to look for
///
/// @return the std::chrono::duration<std::chrono::nanoseconds> of the time
/// needed
///
template <typename T>
auto time_find(const T &data, const std::string &key)
{
  static_assert(std::is_same<typename T::key_type, std::string>::value,
                "not string key");
  const auto start = std::chrono::steady_clock::now();
  auto iter = data.find(key);
  const auto end = std::chrono::steady_clock::now();
  assert(iter != data.cend());
  assert(start != end);
  return std::chrono::nanoseconds::zero;
}

TEST_CASE("Time word counting", "[timing]")
{
  const auto unordered_words = count_unique_words<CountUMap>(readonly_text);
  auto unordered_time = time_find(unordered_words, "template");
  const auto ordered_words = count_unique_words<CountMap>(readonly_text);
  auto ordered_time = time_find(ordered_words, "template");
  // based on theory the unordered must be faster
  REQUIRE(unordered_time < ordered_time);
}



