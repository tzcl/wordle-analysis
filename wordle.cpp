#include <algorithm>
#include <cassert>
#include <deque>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_set>

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
std::string process_guess(const std::string &guess, const std::string &word) {
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

int main() {
  assert(process_guess("FEAST", "NASTY") == "XXYYY");
  assert(process_guess("TREAT", "TASTY") == "GXXYY");
  assert(process_guess("NASTY", "TASTY") == "XGGGG");

  const std::string word = "TASTY";
  int guesses = 6;

  while (guesses > 0) {
    // Get guess
    std::string guess = get_guess();
    while (guess.length() != 5) {
      std::cout << "Guess was the wrong length!" << std::endl;
      guess = get_guess();
    }
    // Respond to guess
    std::string response = process_guess(guess, "TASTY");
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
