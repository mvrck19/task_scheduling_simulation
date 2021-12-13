#include <vector>

#include "task.cpp"

using namespace std;
class Vm
{
  public:
    int mips_capacity;
    int execution_time;
    vector<Task> exec;

    Vm(int capacity)
    {
        this->mips_capacity  = capacity;
        this->execution_time = 0;
    };

    void assign(Task& task)
    {
        // Calculate the execution time of the task on the vm
        // Plus the communication cost
        // TODO see if this works
        if(task.prev.size() == 0)
            execution_time = execution_time + transfer_time();
        execution_time = execution_time + task.mips / mips_capacity;
        exec.push_back(task);

        // TODO dependancies must be done in this part of the code
        task.setDone(true);
    }

    // TODO implement later if needed
    int transfer_time()
    {
        return 1;
    }

    int get_execution_time()
    {
        return execution_time;
    }

    double task_execution_time(Task task)
    {
        return task.mips / this->mips_capacity;
    }
};
