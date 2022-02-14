#include <vector>

#include "task.cpp"

using namespace std;

enum vm_state {
    IDLE,
    USED
};

class Vm
{
  public:
    int id;
    int future = 0;
    int mips_capacity;
    double execution_time;
    vm_state state = IDLE;
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

    double get_execution_time()
    {
        return execution_time;
    }

    void set_state(vm_state state)
    {
        if (state == IDLE || state == USED)
            this->state = state;
    }

    vm_state get_state()
    {
        return state;
    }
};
