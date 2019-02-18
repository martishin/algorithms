#include <iostream>
#include <vector>

std::vector<int> sieveOfEratosthenes(int number) {
    std::vector<bool> primeNumbers(number + 1, true);
    std::vector<int> result;

    for (int currentNumber = 2; currentNumber * currentNumber <= number; ++currentNumber) {
        if (primeNumbers[currentNumber] == true) {
            for (int  mulNumber = currentNumber * 2; mulNumber <= number; mulNumber += currentNumber) {
                primeNumbers[mulNumber] = false;
            }
        }
    }

    for (std::size_t i = 2; i < primeNumbers.size(); ++i) {
        if (primeNumbers[i] == true) {
            result.push_back(i);
        }
    }

    return result;
}

int main() {
    int number;
    std::cin >> number;

    auto primeNumbers = sieveOfEratosthenes(number);

    for (const auto &pn: primeNumbers) {
        std::cout << pn << ' ';
    }
    std::cout << std::endl;
}
