#include <iostream>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "incorrect usage " << std::endl;
        std::cout << "usage: <script.honey> " << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << argv[1] << std::endl;
    return EXIT_SUCCESS;
}
