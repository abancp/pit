#include <string>
#include <filesystem>
#include <iostream>
#include <pwd.h>
#include <unistd.h>
#include <fstream>
#include <vector>
#include "../helpers/utils/id.cpp"
#include "../helpers/utils/split.cpp"
#include "../helpers/utils/removeLine.cpp"

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

    std::vector<int> checkExist(std::string taskName)
    {
        std::vector<int> lineArray;
        std::stringstream string;
        string << hashToOneDigit(taskName);
        std::string hashed = string.str();
        std::string stages[3] = {"active", "working", "closed"};
        for (const std::string fileStage : stages)
        {

            fs::path filePath = fs::current_path() / ".pit" / "tasks" / fileStage / hashed;

            std::ifstream infile(filePath);
            int lineNo = 0;
            if (infile.is_open())
            {
                std::string line;
                while (std::getline(infile, line))
                {
                    lineNo++;
                    std::string lineHash = line.substr(0, 3);
                    if (lineHash == hash(name))
                    {
                        std::vector taskProps = splitString(line, '~');
                        if (name == taskProps[1])
                        {
                            infile.close();
                            if (stage == "active")
                            {
                                std::cout << " Task already " << fileStage << " . 'pit task' to see all tasks " << std::endl;
                                return lineArray;
                            }
                            if (fileStage == "active")
                            {
                                lineArray.push_back(1);
                                lineArray.push_back(lineNo);
                                return lineArray;
                            }
                            else if (fileStage == "working")
                            {
                                lineArray.push_back(2);
                                lineArray.push_back(lineNo);
                                return lineArray;
                            }
                            else
                            {
                                lineArray.push_back(3);
                                lineArray.push_back(lineNo);
                                return lineArray;
                            }
                        }
                    }
                }
                infile.close();
            }
            else
            {
                std::cout << "Unexpected error while opening files" << std::endl;
            }
        }
        lineArray.push_back(0);
        return lineArray;
    }

    int writeTaskToFile(fs::path pitFolder, std::string hashed)
    {
        
        fs::path filePath = pitFolder / "tasks" / stage / hashed;
        std::ofstream outfile(filePath, std::ios::app);
        User user = getUser();
        if (outfile.is_open())
        {
            outfile << generateTUID(name) << "~" << name << "~" << user.name << "~" << user.mail << "\n";
            outfile.close();
            return 0;
        }
        else
        {
            std::cout << "Unexpected error while opening files" << std::endl;
            return 1;
        }
    }

public:
    void setTask()
    {
        fs::path pitFolder = fs::current_path() / ".pit";
        if (fs::exists(pitFolder))
        {
            std::vector<int> existCode = checkExist(name);

            std::stringstream string;
            string << hashToOneDigit(name);
            std::string hashed = string.str();

            if (existCode[0] == 0 && stage == "active")
            {
                writeTaskToFile(pitFolder, hashed);
                return;
            }
            std::cout << existCode[0] << stage << std::endl;
            if (existCode[0] == 1 && stage == "working")
            {
                std::string removeFilePath = pitFolder / "tasks" / "active" / hashed;
                removeLine(removeFilePath,existCode[1]);
                std::cout << "/* message */" << std::endl;
                writeTaskToFile(pitFolder, hashed);
                return;
            }
            if (existCode[0] == 2 && stage == "closed")
            {
                std::string removeFilePath = pitFolder / "tasks" / "working" / hashed;
                removeLine(removeFilePath, existCode[1]);
                writeTaskToFile(pitFolder, hashed);
                return;
            }
            if ((existCode[0] == 0 || existCode[0] == 1) && stage == "closed")
            {
                std::cout << "task is not in working , only working tasks can close" << std::endl;
                return;
            }
            if (existCode[0] == 0 && stage == "working")
            {
                std::cout << "Task not in active , only active tasks can work" << std::endl;
                return;
            }
            if (existCode[0] == 3 && stage == "working")
            {
                std::cout << "Task already closed" << std::endl;
                return;
            }
        }
        else
        {
            // TODO : correct error msg ;
        }
    }
};
