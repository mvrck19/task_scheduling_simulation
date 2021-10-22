#include <iostream>
#include <string>
#include "vm.cpp"
using namespace std;


// It might be a problem with the default bool value of done in a task

void something(Task task){
    task.done=true;
}



int main(int argc, char const *argv[])
{
    Vm vm=Vm(100);
    Task task = Task(100);
    vm.assign(task);
    cout << vm.execution_time << " | " << task.getDone() << "\n";
    return 0;
}
