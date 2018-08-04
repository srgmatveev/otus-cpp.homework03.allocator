#include <iostream>
#include <vector>
#include <iterator>
#include <numeric>

int main() {
    int k{}, n{};

    std::vector<int> a{};

    std::cin >> k >> n;

    std::copy(std::istream_iterator<int>(std::cin),
              std::istream_iterator<int>(),
              std::back_inserter(a));


    int quantity{};

    for ( int i = 0; i < n; i++ ) {

        if (a.at(i) + quantity > k)
        {
            quantity = (a.at(i) + quantity - k);
        }
        else
        {
            quantity = 0;
        }
    }


    std::cout << quantity << std::endl;
    return 0;
}