#include "task.cpp"

class Vm
{
public:

    //TODO add a time array

    int mips_capacity;
    Vm(int capacity){
        this->mips_capacity=capacity;
    };
    
    void assign(Task task){
        this->array_of_time.give(task);
    }
    
};

