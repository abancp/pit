#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include "../models/FileStructure.cpp"

namespace fs = std::filesystem;

void init(){
    const fs::path cwd = fs::current_path();
    if(fs::exists(cwd/".pit")){
        std::cout << "Already have a repo here" << std::endl;
    }else{
        
        FileStructure pitFS = FileStructure();
        pitFS.makeFile();

        if(pitFS.checkAllExist()){
            std::cout<< "pit initialised empty repo"<<std::endl;
        }else{
            std::cout << "error while initialising empty repo" << std::endl;
        }

    }

}