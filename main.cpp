#include "Tensor.hpp"

int main() {
    Tensor t({3, 3});
    t[0] = 1;
    t[1] = 2;
    t[2] = 3;
    t[3] = 4;
    t[4] = 5;
    t[5] = 6;
    t[6] = 8;

  


    t.at({0, 0}) = 10;


    t.reshape({1, 9});

    for (int i = 0; i < t.size; i++) {
        std::cout << t.data[i] << " ";
    }

    return 0;
}
