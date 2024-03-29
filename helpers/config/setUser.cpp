#include <string>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

void setUser(bool globally)
{
    std::string username = "";
    std::string email = "";
    std::cout << "username :";
    std::cin >> username;
    std::cout << "email :";
    std::cin >> email;

    if (globally)
    {
        struct passwd *pw = getpwuid(getuid());
        if ((pw != nullptr))
        {
            fs::path configPath = pw->pw_dir;
            configPath = configPath / ".pitconfig";
            std::ofstream configFile(configPath);
            if (configFile.is_open())
            {
                configFile << "(user)\n username=" << username << "\n email=" << email;
                configFile.close();
            }
            else
            {
                std::cerr << "unexpected error while config globally" << std::endl;
            }
        }
        else
        {
            std::cerr << "unexpected error while config globally" << std::endl;
        }
    }
    else
    {
        fs::path configPath = fs::current_path() / ".pit" / "pitconfig";
        std::ofstream configFile(configPath);
        if (configFile.is_open())
        {
            configFile << "(user)\n username=" << username << "\n email=" << email;
            configFile.close();
        }
        else
        {
            std::cerr << "unexpected error while config locally" << std::endl;
        }
    }
}
