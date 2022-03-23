#include <algorithm>
#include <cassert>
#include <deque>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

std::string get_guess() {
  std::string guess; // TODO: validate 5 letters (and need to check dictionary)
  std::cout << "Please enter your guess: ";
  std::cin >> guess;
  std::transform(guess.begin(), guess.end(), guess.begin(), ::toupper);

  return guess;
}

// Returns a string like XYGGX
// X -- wrong letter
// Y -- right letter wrong spot
// G -- right letter right spot
std::string colour_guess(const std::string &guess, const std::string &word) {
  std::unordered_multiset<char> letters(word.begin(), word.end());

  std::string response;
  for (int i = 0; i < guess.size(); ++i) {
    if (guess[i] == word[i]) {
      response += 'G';
      continue;
    }

    auto pos = letters.find(guess[i]);
    if (pos != letters.end()) {
      response += 'Y';
      letters.erase(pos);
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
  assert(colour_guess("FEAST", "NASTY") == "XXYYY");
  assert(colour_guess("TREAT", "TASTY") == "GXXYY");
  assert(colour_guess("NASTY", "TASTY") == "XGGGG");

  // Read in valid answers and guesses
  const std::vector<std::string> ANSWERS = read_words("answers");
  const std::vector<std::string> GUESSES = read_words("guesses");

  assert(ANSWERS.size() == 2309);
  assert(GUESSES.size() == 10638);

  std::random_device rd;
  std::mt19937 mt(rd());

  std::uniform_int_distribution<int> rand(0, ANSWERS.size() - 1);
  std::string word = ANSWERS[rand(mt)];
  std::transform(word.begin(), word.end(), word.begin(), ::toupper);
  std::cout << "The word is " << word << std::endl;

  int guesses = 6;

  while (guesses > 0) {
    // Get guess
    std::string guess = get_guess();
    while (guess.length() != 5 ||
           std::find(GUESSES.begin(), GUESSES.end(), guess) != GUESSES.end()) {
      std::cout << "Invalid guess!" << std::endl;
      guess = get_guess();
    }
    // Respond to guess
    std::string response = colour_guess(guess, word);
    if (response == "GGGGG") {
      std::stringstream result;
      result << "You won in ";
      result << 6 - guesses + 1;
      result << (guesses == 6 ? " guess" : " guesses") << "!";
      std::cout << result.str() << std::endl;
      return 0;
    }
    std::cout << response << std::endl;

    guesses--;
  }

  std::cout << "The word was: " << word << std::endl;

  return 0;
}
