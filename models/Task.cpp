#include <string>
#include <filesystem>
#include <iostream>
#include <fstream>
#include "../helpers/id.cpp"

namespace fs = std::filesystem;

class Task
{
public:
    std::string name;
    std::string stage;

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
            std::string stage = "closed";
            break;
        }
        }

    }

    struct User
    {
        std::string name;
        std::string mail;
    };

private:
    User getUser()
    {
        const fs::path localConfigFile = fs::current_path() / ".pit" / "pitconfig";
        if (fs::exists(localConfigFile))
        {
            std::ifstream infile(localConfigFile);
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
                std::cout << "File read successfully." << std::endl;
                return user;
            }
            else
            {
                std::cerr << "Error: Unable to open file." << std::endl;
                User user = {"unknown","unknown"};
                return user;
            }
        }else{
            std::cerr << "developing with global " << std::endl;
            User user = {"unknown","unknown"};
            return user;
        }
    }
public:
    void setTask(){
        fs::path pitFolder = fs::current_path() / ".pit";
        if(fs::exists(pitFolder)){
            fs::path filePath = pitFolder / "tasks" / stage;
            std::ofstream outfile(filePath,std::ios::app);
            User user = getUser();
            if(outfile.is_open()){
                outfile <<  generateUniqueId() << "~" << name << "~" << user.name << "~" << user.mail<<"\n";
                outfile.close();
            }
        }else{
            //TODO : correct error msg ;
        }
    }
};