#include <iostream>
#include "../../Math/MathUtils.h"

void Update() {
    float x = -5.5f;
    std::cout << "absf(-5.5) = " << absf(x) << std::endl;
}

int main() {
    std::cout << "Proyecto Prueba1 iniciado!" << std::endl;
    while (true) {
        Update();
    }
    return 0;
}
