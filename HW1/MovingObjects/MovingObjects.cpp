#include <iostream>
#include <vector>

template <class T>
void move_vectors(std::vector<T>& vec_one, std::vector<T>& vec_two) {
    vec_two = std::move(vec_one);
}

int main() {

    std::vector <std::string> one = { "test_string1", "test_string2" };
    std::vector <std::string> two;
    move_vectors(one, two);

    if (one.empty())
    {
        std::cout << "Vector is one empty" << '\n';
    }
    std::cout << "Move elements: ";
    for (const auto& v : two) {
        std::cout << v << " ";
    }
    return 0;
};