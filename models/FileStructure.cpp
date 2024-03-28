#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

class FileStructure
{
    //.pit
      //Tasks
        //active
        //working
        //closed
      //Devs
private:
    fs::path cwd = fs::current_path();
    fs::path dotpit = cwd / ".pit";
    fs::path tasks = cwd / ".pit" / "tasks";
    fs::path active = cwd / ".pit" / "tasks" / "active";
    fs::path working = cwd / ".pit" / "tasks" / "working";
    fs::path closed = cwd / ".pit" / "tasks" / "closed";

public:

  void makeFile(){
    fs::create_directory(dotpit);
    fs::create_directory(tasks);
    fs::path taskFiles[3] = {active,working,closed};
    for(int i = 0 ; i < 3 ; i++){
      std::ofstream outFile(taskFiles[i]);
      if (outFile.is_open()) {
          outFile.close();
      }else{
          std::cout << "can't create file" << std::endl;
      }
    }
    
  }

  bool checkAllExist(){

    if(fs::exists(dotpit) && fs::exists(tasks)){
      fs::path taskFiles[3] = {active,working,closed};
      for(int i = 0 ; i < 3 ; i++){
        if(!fs::exists(taskFiles[i])){
          return false;
        }
      }
    }else{
      return false;
    }

    return true;
    
  }
    
};
