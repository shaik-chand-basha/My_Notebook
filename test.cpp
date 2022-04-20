#include <iostream>
#include <string>
#include <windows.h>
using namespace std;
int main()
{
    string a = "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";
    char p[a.length()];
    strcpy(p, a.c_str());
    for (int i = 0; i < a.length(); i++)
    {
        if ((i + 1) % 78 == 0)
        {
            cout << endl;
        }
        cout<<p[i];
    }
}