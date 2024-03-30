#include <string>
#include <filesystem>
#include <iostream>
#include <pwd.h>
#include <unistd.h>
#include <fstream>
#include "../helpers/id.cpp"
#include "../helpers/split.cpp"

namespace fs = std::filesystem;
class Task
{
public:
    std::string name;
    std::string stage;
    struct User
    {
        std::string name;
        std::string mail;
    };

    Task(std::string taskName, int type)
    {
        name = taskName;
        stage;

        switch (type)
        {
        case 1:
        {
            stage = "active";
            break;
        }
        case 2:
        {
            stage = "working";
            break;
        }
        case 3:
        {
            stage = "closed";
            break;
        }
        }
    }

private:
    User getUser()
    {
        fs::path configFile;
        if (fs::exists(fs::current_path() / ".pit" / "pitconfig"))
        {
            configFile = fs::current_path() / ".pit" / "pitconfig";
        }
        else
        {
            struct passwd *pw = getpwuid(getuid());
            if ((pw != nullptr))
            {
                fs::path tempConfigFile = pw->pw_dir;
                tempConfigFile = tempConfigFile / ".pitconfig";
                if (fs::exists(tempConfigFile))
                {
                    configFile = tempConfigFile;
                }
                else
                {
                    // TODO :
                }
            }
            else
            {
                // TODO
            }
        }

        std::ifstream infile(configFile);

        if (infile.is_open())
        {
            std::string line;
            std::string username;
            std::string usermail;
            int lineNo = 0;
            while (std::getline(infile, line))
            {
                if (lineNo == 1)
                {
                    username = line.substr(10);
                }
                if (lineNo == 2)
                {
                    usermail = line.substr(7);
                }
                lineNo++;
            }
            infile.close();
            User user = {username, usermail};
            return user;
        }
        else
        {
            std::cerr << "Error: Unable to open file." << std::endl;
            User user = {"unknown", "unknown"};
            return user;
        }
    }

    int hashToOneDigit(std::string taskStr)
    {
        int hashed = 0;
        if (taskStr.length() > 2)
        {
            for (int i = 0; i < 3; i++)
            {
                hashed += int(taskStr[i]);
            }
            return hashed % 10;
        }
        else
        {
            for (int i = 0; i < taskStr.length(); i++)
            {
                hashed += int(taskStr[i]);
            }
            return hashed % 10;
        }
    }

    bool checkExist(std::string taskName)
    {
        std::stringstream string;
        string << hashToOneDigit(taskName);
        std::string hashed = string.str();
        fs::path filePath = fs::current_path() / ".pit" / "tasks" / "active" / hashed;

        std::ifstream infile(filePath);

        if (infile.is_open())
        {
            std::string line;
            while (std::getline(infile, line))
            {
                std::string lineHash = line.substr(0, 3);
                if (lineHash == hash(name))
                {
                    std::vector taskProps = splitString(line, '~');
                    if (name == taskProps[1])
                    {
                        return true;
                    }
                }
            }
            infile.close();
        }
        return false;
    }

public:
    void setTask()
    {
        fs::path pitFolder = fs::current_path() / ".pit";
        if (fs::exists(pitFolder))
        {
            if (checkExist(name))
            {
                std::cout << "task already active \nuse ' pit task ' to see all tasks" << std::endl;
            }
            else
            {
                std::stringstream string;
                string << hashToOneDigit(name);
                std::string hashed = string.str();
                fs::path filePath = pitFolder / "tasks" / stage / hashed;
                std::ofstream outfile(filePath, std::ios::app);
                User user = getUser();
                if (outfile.is_open())
                {
                    outfile << generateTUID(name) << "~" << name << "~" << user.name << "~" << user.mail << "\n";
                    outfile.close();
                }
            }
        }
        else
        {
            // TODO : correct error msg ;
        }
    }
};
