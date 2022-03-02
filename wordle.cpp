#include <algorithm>
#include <cassert>
#include <deque>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>

using word_map = std::unordered_map<char, std::deque<int>>;

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
std::string process_guess(const std::string &guess, word_map letters) {
  std::string response;
  for (int i = 0; i < guess.size(); ++i) {
    if (letters.count(guess[i])) {
      if (letters[guess[i]].front() == i)
        response += "G";
      else
        response += "Y";
      letters[guess[i]].pop_front();
    } else {
      response += ".";
    }
  }

  return response;
}

int main() {
  const word_map NASTY{{'N', std::deque<int>{0}},
                       {'A', std::deque<int>{1}},
                       {'S', std::deque<int>{2}},
                       {'T', std::deque<int>{3}},
                       {'Y', std::deque<int>{4}}};

  const word_map TASTY{{'T', std::deque<int>{0, 3}},
                       {'A', std::deque<int>{1}},
                       {'S', std::deque<int>{2}},
                       {'Y', std::deque<int>{4}}};

  assert(process_guess("FEAST", NASTY) == "..YYY");
  assert(process_guess("TREAT", TASTY) == "G..YY");

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
    std::string response = process_guess(guess, TASTY);
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
