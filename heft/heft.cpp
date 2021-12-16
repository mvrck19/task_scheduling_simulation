#include <iostream>
#include <vector>

#include "broker.cpp"
#include "task.cpp"
#include "workflow.cpp"

using namespace std;

vector<Vm> create_vms()
{
    vector<Vm> vms;
    for (int i = 0; i < 3; i++)
    {
        Vm newVm = Vm(i); // i+1 cause of the paper
        vms.push_back(newVm);
    }
    return vms;
}

vector<Task> create_tasks()
{
    vector<Task> tasks;
    for (int i = 0; i < 3; i++)
    {
        Task newTask = Task(i, 100); // i+1 cause of the paper
        tasks.push_back(newTask);
    }
    return tasks;
}

int main(int argc, char const* argv[])
{
    Workflow w = Workflow();

    w.add_tasks(create_tasks());

    w.add_edge(0, 1);
    w.add_edge(0, 2);
    // w.add_edge(2, 3);
    // w.add_edge(1, 3);
    // w.add_edge(2, 4);

    vector<Vm> vms = create_vms();
    Broker broker  = Broker(vms, w);
    broker.run();
    return 0;
}
