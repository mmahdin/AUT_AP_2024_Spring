#include "BloomFilter.h"

template <std::size_t N>
BloomFilter<N>::BloomFilter(unsigned int num_hashes) : num_hashes{num_hashes} {
  for (std::size_t i{}; i < 100; seeds.push_back(i), i++)
    ;
}

template <std::size_t N>
BloomFilter<N>::BloomFilter(const BloomFilter& other) {}

template <std::size_t N>
BloomFilter<N>::BloomFilter(BloomFilter&& other) noexcept {}

template <std::size_t N>
BloomFilter<N>::~BloomFilter() {}

template <std::size_t N>
void BloomFilter<N>::add(const std::string& item) {
  std::size_t hashed;
  std::size_t mod;
  for (std::size_t i{}; i < N; i++) {
    hashed = hash(item, seeds[i]);
    mod = hashed % N;
    bits.set(mod, true);
    server->addWord(item);
  }
}

template <std::size_t N>
void BloomFilter<N>::add(
    std::string&& file_name = "../Resource/Word_DataSet_1.txt") {
  std::ifstream file(file_name);
  if (!file.is_open()) {
    std::cerr << "Error: Unable to open the file." << std::endl;
  }
  std::string word;
  while (file >> word) {
    add(word);
  }
  file.close();
}

template <std::size_t N>
bool BloomFilter<N>::possiblyContains(const std::string& item) const {
  std::size_t hashed;
  std::size_t mod;
  for (std::size_t i{}; i < N; i++) {
    hashed = hash(item, seeds[i]);
    mod = hashed % N;
    if (!bits.test(mod)) return 0;
  }
  return 1;
}

template <std::size_t N>
bool BloomFilter<N>::possiblyContains(std::string&& item) const {
  return possiblyContains(item);
}

template <std::size_t N>
bool BloomFilter<N>::certainlyContains(const std::string& item) const {
  return server->checkWord(item);
}

template <std::size_t N>
bool BloomFilter<N>::certainlyContains(std::string&& item) const {
  return certainlyContains(item);
}

template <std::size_t N>
void BloomFilter<N>::reset() {
  std::bitset<N> new_bits;
  bits = new_bits;
}

template <std::size_t N>
BloomFilter<N>& BloomFilter<N>::operator&(const BloomFilter<N>& other) {
  std::bitset<N> result_and{bits & other.bits};
  return *this;
}

template <std::size_t N>
BloomFilter<N>& BloomFilter<N>::operator|(const BloomFilter& other) {
  std::bitset<N> result_and{bits | other.bits};
  return *this;
}

template <std::size_t N>
bool BloomFilter<N>::operator()(const std::string& item) const {
  return possiblyContains(item);
}

template <std::size_t N>
std::ostream& operator<<(std::ostream& os, const BloomFilter<N>& bloom_filter) {
  os << "num_hashes: " << bloom_filter.num_hashes << "\t"
     << "num bits: " << N << std::endl
     << bloom_filter.bits;
  return os;
}

template <std::size_t N>
std::istream& operator>>(std::istream& is, BloomFilter<N>& bloom_filter) {
  std::string line;
  std::getline(is, line);

  std::istringstream iss(line);
  std::string word;
  while (iss >> word) {
    add(word);
  }

  return is;
}