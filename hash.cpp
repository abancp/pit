#include <iostream>
#include <string>

int hash(std::string name)
{
    int hashed = 0;
    if (name.length() > 2)
    {
        for (int i = 0; i < 3; i++)
        {
            hashed += int(name[i]);
        }
            return hashed%10; 
    }
    else
    {
        for (int i = 0; i < name.length(); i++)
        {
            hashed += int(name[i]);
        }
            return hashed%10;
    }
}
int main()
{
    std::cout << hash("!") << std::endl;
}