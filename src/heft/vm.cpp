#include <vector>

#include "task.cpp"

using namespace std;

enum vm_state
{
    IDLE,
    USED
};

enum type
{
    T2_SMALL,
    T2_MEDIUM,
    T2_LARGE,
    T2_XLARGE,
    M5_XLARGE,
    M5_2XLARGE,
    R4_LARGE,
    R4_XLARGE,
    R4_2XLARGE,
};

enum pricing
{
    ON_DEMAND,
    SPOT
};

class Vm
{
  public:
    int id;
    int mips_capacity;
    double price;
    double execution_time;
    vm_state state = IDLE;
    // all the tasks that are assigned to this vm are stored here
    vector<Task> exec;

    Vm(int id, int capacity)
    {
        this->id             = id;
        this->mips_capacity  = capacity;
        this->execution_time = 0;
    }

    Vm(int id, type t, pricing p)
    {
        this->id             = id;
        this->execution_time = 0;
        this->state          = IDLE;
        this->exec.clear();
        // todo add network and storage info oir other related info
        switch (p)
        {
        case ON_DEMAND:
            switch (t)
            {
            case T2_SMALL:
                this->mips_capacity = 1000;
                this->price         = 0.023;
                break;
            case T2_MEDIUM:
                this->mips_capacity = 2000;
                this->price         = 0.0464;
                break;
            case T2_LARGE:
                this->mips_capacity = 2000;
                this->price         = 0.0928;
                break;
            case T2_XLARGE:
                this->mips_capacity = 4000;
                this->price         = 0.1856;
                break;
            case M5_XLARGE:
                this->mips_capacity = 4000;
                this->price         = 0.192;
                break;
            case M5_2XLARGE:
                this->mips_capacity = 8000;
                this->price         = 0.384;
                break;
            case R4_LARGE:
                this->mips_capacity = 2000;
                this->price         = 0.133;
                break;
            case R4_XLARGE:
                this->mips_capacity = 4000;
                this->price         = 0.266;
                break;
            case R4_2XLARGE:
                this->mips_capacity = 8000;
                this->price         = 0.532;
                break;
            }
            break;
        case SPOT:
            switch (t)
            {
            case T2_SMALL:
                this->mips_capacity = 1000;
                this->price         = 0.0069;
                break;
            case T2_MEDIUM:
                this->mips_capacity = 2000;
                this->price         = 0.0139;
                break;
            case T2_LARGE:
                this->mips_capacity = 2000;
                this->price         = 0.0278;
                break;
            case T2_XLARGE:
                this->mips_capacity = 4000;
                this->price         = 0.0557;
                break;
            case M5_XLARGE:
                this->mips_capacity = 4000;
                this->price         = 0.0399;
                break;
            case M5_2XLARGE:
                this->mips_capacity = 8000;
                this->price         = 0.0849;
                break;
            case R4_LARGE:
                this->mips_capacity = 2000;
                this->price         = 0.0199;
                break;
            case R4_XLARGE:
                this->mips_capacity = 4000;
                this->price         = 0.0398;
                break;
            case R4_2XLARGE:
                this->mips_capacity = 8000;
                this->price         = 0.0816;
                break;
            }
            break;
        }
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
