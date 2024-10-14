#include <vector>
#include <string>
#include <sstream>
#include <iostream>

int main()
{
    std::string str = "1.2;2;3;4;5;6\n";
    std::vector<int> vect;

    std::stringstream ss(str);

    for (float i; ss >> i;) {
        vect.push_back((int)(i * 1000));
        if (ss.peek() == ';')
            ss.ignore();
    }

    for (std::size_t i = 0; i < vect.size(); i++)
        std::cout << vect[i] << std::endl;
}