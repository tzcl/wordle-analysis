#include <cassert>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> read_words(std::string filename) {
  std::vector<std::string> result;
  std::ifstream fs(filename);
  std::string word;

  while (std::getline(fs, word)) {
    result.push_back(word);
  }

  return result;
}

void generate_table(const std::vector<std::string> &words,
                    const std::vector<std::string> &answers) {
  f
}

int main() {
  // Read in valid words and answers
  const std::vector<std::string> WORDS = read_words("words");
  const std::vector<std::string> ANSWERS = read_words("answers");

  assert(WORDS.size() == 12947);
  assert(ANSWERS.size() == 2309);
}
