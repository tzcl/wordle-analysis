#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// Returns a string like XYGGX
// X -- wrong letter
// Y -- right letter wrong spot
// G -- right letter right spot
std::string process_guess(const std::string &guess, const std::string &word) {
  std::unordered_map<char, int> letters;
  for (auto l : word) {
    ++letters[l];
  }

  std::string response;
  for (int i = 0; i < guess.size(); ++i) {
    if (guess[i] == word[i]) {
      response += 'G';
      continue;
    }

    if (letters.count(guess[i])) {
      if (letters[guess[i]] > 0) {
        --letters[guess[i]];
        response += 'Y';
      }
      continue;
    }

    response += 'X';
  }

  return response;
}

std::vector<std::string> read_words(std::string filename) {
  std::vector<std::string> result;
  std::ifstream fs(filename);
  std::string word;

  while (std::getline(fs, word)) {
    result.push_back(word);
  }

  return result;
}

int main() {

  // Test cases
  assert(process_guess("FEAST", "NASTY") == "XXYYY");
  assert(process_guess("TREAT", "TASTY") == "GXXYY");
  assert(process_guess("TREAT", "BUTTE") == "YXYXY");
  assert(process_guess("NASTY", "TASTY") == "XGGGG");

  // Read in valid answers and guesses
  const std::vector<std::string> ANSWERS = read_words("answers");
  const std::vector<std::string> GUESSES = read_words("guesses");

  assert(ANSWERS.size() == 2309);
  assert(GUESSES.size() == 10638);

  std::cout << "Hello world!" << std::endl;
  return 0;
}
