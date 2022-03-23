#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// Returns a string like xYGGx
// x -- wrong letter
// Y -- right letter wrong spot
// G -- right letter right spot
std::string colour_guess(const std::string &guess, const std::string &answer) {
  std::unordered_map<char, int> count;
  for (auto l : answer)
    ++count[l];

  // So we can mutate the string
  std::vector<char> response(5, 'x');

  for (int i = 0; i < guess.size(); ++i) {
    if (guess[i] == answer[i]) {
      --count[answer[i]];
      response[i] = 'G';
    }
  }

  for (int i = 0; i < guess.size(); ++i) {
    if (response[i] == 'G')
      continue;

    if (count.find(guess[i]) != count.end() && count[guess[i]]) {
      --count[guess[i]];
      response[i] = 'Y';
    }
  }

  return std::string(response.begin(), response.end());
}

bool valid_solution(const std::vector<std::string> &words,
                    const std::vector<std::string> &answers) {
  std::unordered_map<std::string, std::string> responses;
  // Generate responses
  for (auto ans : answers) {
    std::string acc;
    for (auto word : words) {
      acc += colour_guess(word, ans);
    }

    if (responses.count(acc)) {
      std::cout << "Duplicate: " << ans << " and " << responses[acc] << " ("
                << acc << ")" << std::endl;
      return false;
    }

    responses[acc] = ans;
  }

  return true;
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
  assert(colour_guess("FEAST", "NASTY") == "xxYYY");
  assert(colour_guess("TREAT", "TASTY") == "GxxYY");
  assert(colour_guess("NASTY", "TASTY") == "xGGGG");
  assert(colour_guess("TREAT", "BUTTE") == "YxYxY");
  assert(colour_guess("COMBO", "BOBBY") == "xGxGx");
  assert(colour_guess("COMBO", "BOOBY") == "xGxGY");
  assert(colour_guess("FATTY", "ZESTY") == "xxxGG");

  // Read in valid answers and guesses
  const std::vector<std::string> WORDS = read_words("words");
  const std::vector<std::string> ANSWERS = read_words("answers");

  assert(WORDS.size() == 12947);
  assert(ANSWERS.size() == 2309);

  assert(valid_solution({"combo", "fatty", "grrrl", "spuds", "venge", "whilk"},
                        ANSWERS));

  std::cout << "Hello world!" << std::endl;
  return 0;
}
