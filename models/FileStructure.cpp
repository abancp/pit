#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

class FileStructure
{

private:
    fs::path cwd = fs::current_path();
    fs::path dotpit = cwd / ".pit";
    fs::path tasks = cwd / ".pit" / "tasks";
    fs::path active = cwd / ".pit" / "tasks" / "active";
    fs::path working = cwd / ".pit" / "tasks" / "working";
    fs::path closed = cwd / ".pit" / "tasks" / "closed";

public:

  void makeFile(){
    fs::path taskFiles[5] = {dotpit,tasks,active,working,closed};
    for(int i = 0 ; i < 5 ; i++){
      fs::create_directories(taskFiles[i]);
    }
    for(int i = 2;i < 5;i++){
      for(int j = 0 ; j < 10;j++){
        std::ofstream outFile(taskFiles[i]/std::to_string(j));
        if (outFile.is_open()) {
          outFile.close();
        }else{
          std::cout << "can't create file" << std::endl;
        }
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
