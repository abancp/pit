#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

class FileStructure
{

private:
  fs::path cwd = fs::current_path();
  fs::path pit = cwd / ".pit";
  fs::path versions = pit / "versions";
  fs::path upcoming = versions / "upcoming";
  fs::path released = versions / "released";
  fs::path refs = pit / "refs";
  fs::path HEAD = refs / "HEAD";

public:
  void makeFile()
  {
    fs::path taskFiles[5] = {pit, versions, upcoming, released, refs};
    for (int i = 0; i < 5; i++)
    {
      fs::create_directories(taskFiles[i]);
    }
    std::ofstream HEADFile(HEAD, std::ios::out);
    if (HEADFile.is_open())
    {
      HEADFile << "0.0.1";
    }
    else
    {
      std::cout << "something went wrong! , cant create file";
      exit(1);
    }
  }

  bool checkAllExist()
  {
    return true;
  }
};
