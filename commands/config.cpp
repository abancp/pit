#include "../helpers/config/setUser.cpp"
#include <string>

void config(int argc,const char** argv){
    if(argc == 4){

        std::string subCommand1 = argv[2];
        std::string subCommand2 = argv[3];

        if(subCommand1 == "user" || subCommand2 == "user"){
            for (int i = 1 ;i <= argc ; i++){
                std::string flagG = argv[i];
                if( flagG == "-g" ){
                    // configuration globally
                    setUser(true);
                    return;
                }
            }
            setUser(false);
        }else{
            //TODO : Usage
        }
    }else if(argc == 3){

        std::string subCommand1 = argv[2];
        if(subCommand1 == "user"){
            setUser(false);
        }else{
            //TODO : Usage
        }

    }
}