#include "task.cpp"
#include <vector>

using namespace std;
class Vm
{
public:
    int mips_capacity;
    int execution_time;
    vector<bool> exec;

    Vm(int capacity)
    {
        this->mips_capacity = capacity;
        this->execution_time = 0;
    };

    void assign(Task task)
    {
        // Calculate the execution time of the task on the vm
        // Plus the communication cost
        execution_time = execution_time + transfer_time();
        execution_time = execution_time + task.mips / mips_capacity;
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
};
