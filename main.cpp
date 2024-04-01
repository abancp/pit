#include <iostream>
#include <string>
#include <iostream>
#include <unordered_map>
#include "usage/printUsage.cpp"
#include "commands/task.cpp"
#include "commands/init.cpp"
#include "commands/config.cpp"



int main(int argc, const char **argv)
{
    std::unordered_map<std::string,int>  commandsMap  = {
        {"task",1},
        {"config",2},
        {"init",3},
    };

    if (argc > 1){
        std::string command = argv[1];
        switch(commandsMap[command]){
            case 1 :{
                task(argc,argv);
                break;
            }
            case 2 :{
                config(argc,argv);
                break;
            }
            case 3 :{
                init();
                break;
            }
        }
    }else{
        printUsage();
    }
}