#include <array> // std::array
#include <cassert> // assert()
#include <cstddef> // std::size_t
#include <fstream> // std::ifstream
#include <iostream> // std::cout, std::cerr, std::noskipws
#include <stdexcept> // std::runtime_error
#include <string> // std::string
#include <utility> // std::move()

/**
 * @class Buffer
 *
 * @brief Wrapper around std::array with simplified API and recording of
 * copy/move operations.
 *
 * @tparam T Buffer value type.
 * @tparam N Buffer size.
 */
template <typename T, std::size_t N>
class Buffer
{
 public:
  Buffer(T value = T{}) { data_.fill(value); }
  Buffer(const Buffer& a)
      : data_{a.data_} { ++copies; }
  Buffer(Buffer&& a)
      : data_{std::move(a.data_)} { ++moves; }
  Buffer& operator=(const Buffer& a) = delete; // disable copy assignment
  Buffer& operator=(Buffer&& a) = delete; // disable move assignment
  T& operator[](std::size_t pos) { return data_[pos]; }
  const T& operator[](std::size_t pos) const { return data_[pos]; }
  constexpr std::size_t size() const { return data_.size(); }
  static std::size_t copies; ///< total copy operations of Buffer instances
  static std::size_t moves; ///< total move operations of Buffer instances

 private:
  std::array<T, N> data_{}; ///< array data
};

template <typename T, std::size_t N>
std::size_t Buffer<T, N>::copies = 0;

template <typename T, std::size_t N>
std::size_t Buffer<T, N>::moves = 0;

/**
 * @class File
 *
 * @brief Class holding the contents of a file.
 *
 * @tparam N Maximum file size.
 * @tparam T File character type.
 */
template <std::size_t N, typename T = char>
class File
{
 public:
  using BufferT = Buffer<T, N>;
  File(T value = T{}) : buf_{value} {}
  File(const std::string& path)
  {
    std::ifstream ifs{path};
    if (ifs.is_open() == false)
      throw std::runtime_error{"cannot open file"};
    ifs >> std::noskipws;
    for (T c; ifs >> c; ++size_)
      buf_[size_] = c;
  }
  File(const File& f)
      : size_{f.size_}, buf_{f.buf_} {}
  T& operator[](std::size_t pos) { return buf_[pos]; }
  const T& operator[](std::size_t pos) const { return buf_[pos]; }
  std::size_t size() const { return size_; }
  constexpr std::size_t capacity() const { return buf_.size(); }

 private:
  std::size_t size_{}; ///< file size
  BufferT buf_; ///< file contents
};

int main(int argc, char* argv[])
{
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " <pathname>\n";
    return 0;
  }
  try {
    constexpr std::size_t MaxSize{1'000'000};
    using FileT = File<MaxSize>;
    FileT src{argv[1]};
    const auto sz = src.size();
    FileT copy = src;
    FileT move = std::move(src);
    assert(FileT::BufferT::copies == 1);
    assert(FileT::BufferT::moves == 1);
    assert(src.size() == 0);
    assert(copy.size() == sz);
    assert(move.size() == sz);
  }
  catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return -1;
  }

  return 0;
}
