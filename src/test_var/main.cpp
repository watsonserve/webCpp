#include <iostream>
#include "var.hpp"

int main()
{
    Var json;
    Var sa[] = {"123", "456"};

    json.setArray(sa, 2);

    std::cout << json.toString() << std::endl;

    json = "true";
    std::cout << json.toString() << std::endl;

    return 0;
}
