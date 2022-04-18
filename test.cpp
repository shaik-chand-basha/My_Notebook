#include <iostream>
#include <conio.h>
#include <vector>
#include <sstream>
int main()
{
    char choice;
    std::string s = "";
    while (true)
    {
        choice=getch();
        if (choice == 13)
            break;
        std::cout<<choice;
        s = s + choice;
    }
    std::cout << std::endl
              << s;
}