#include "../../models/Task.cpp"

void addTask(std::string taskName, int stage)
{
    if (stage == 1)
    {
        if (taskName.find('~') != std::string::npos || taskName.find('/') != std::string::npos || taskName.find('[') != std::string::npos || taskName.find(']') != std::string::npos || taskName.find('\\') != std::string::npos)
        {
            std::cout << "Task name does not contain '|','[',']','/','\\' " << std::endl;
            exit(0);
        }
        else
        {
            Task task(taskName, stage,false);
            task.setTask();
        }
    }
    else
    {
        if (taskName.find('~') != std::string::npos || taskName.find('/') == std::string::npos || taskName.find('[') != std::string::npos || taskName.find(']') != std::string::npos || taskName.find('\\') != std::string::npos)
        {
            Task task(taskName, stage,true);
            task.setTask();
        }
    }
}