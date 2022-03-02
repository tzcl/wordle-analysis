#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>

std::string get_guess() {
  std::string guess; // TODO: validate 5 letters (and need to check dictionary)
  std::cout << "Please enter your guess: ";
  std::cin >> guess;
  std::transform(guess.begin(), guess.end(), guess.begin(), ::toupper);

  return guess;
}

// Returns a string like .YGG.
// . -- wrong letter
// Y -- right letter wrong spot
// G -- right letter right spot
std::string process_guess(const std::string &guess, const std::string &word) {
  // Naive algorithm: loop over the word and colour first instance of each
  // letter in guess
  std::string response;
  std::string append;

  for (int i = 0; i < guess.size(); ++i) {
    append = ".";
    for (int j = 0; j < word.size(); ++j) {
      if (guess[i] == word[j]) {
        i == j ? append = "G" : append = "Y";
        break;
      }
    }
    response += append;
  }

  return response;
}

int main() {
  const std::string word = "NASTY";
  int guesses = 6;

  while (guesses > 0) {
    // Get guess
    std::string guess = get_guess();
    while (guess.length() != 5) {
      std::cout << "Guess was the wrong length!" << std::endl;
      guess = get_guess();
    }
    // Respond to guess
    std::string response = process_guess(guess, word);
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
