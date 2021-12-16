#include <vector>

#include "task.cpp"

using namespace std;
class Vm
{
  public:
    int id;
    int mips_capacity;
    int execution_time;
    vector<Task> exec;

    Vm(int id, int capacity)
    {
        this->id             = id;
        this->mips_capacity  = capacity;
        this->execution_time = 0;
    }

    Vm()
    {
        this->execution_time = 0;
    };

    Vm(int id)
    {
        this->id             = id;
        this->execution_time = 0;
    };

    int get_execution_time()
    {
        return execution_time;
    }
};
