#include <iostream>
#include <fstream>
#include <filesystem>
#include "../../models/Task.cpp"

namespace fs = std::filesystem;


void addTask(std::string taskName){

    Task task(taskName,1);
    task.setTask();
    
}