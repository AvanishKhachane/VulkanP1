#include <iostream>
#include <stdexcept>
#include <cstdlib>

#include "first_app.hpp"

int main() {

    system("compile.bat");

    ve::firstapp app;

    try {
        app.run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}