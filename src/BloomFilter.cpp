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