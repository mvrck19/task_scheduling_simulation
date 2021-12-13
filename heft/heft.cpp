#include <iostream>
#include <vector>

#include "broker.cpp"
#include "task.cpp"
#include "workflow.cpp"

using namespace std;

// TODO make it run so that when there are more than one vms it switches to the one with less time on it
// TODO make it run so that when there are two dependancies it waits for them
// TODO make it use the name of tasks instead of the number, so it finds the exact task and not mistaken for then on
// given in order of creation in the workflow and also to throw errors
// TODO check that the results match the results from the paper
// TODO work on transfer cost

vector<Vm> create_vms()
{
    vector<Vm> vms;
    for (int i = 0; i < 2; i++)
    {
        Vm newVm = Vm(i + 1); // i+1 cause of the paper
        vms.push_back(newVm);
    }
    return vms;
}

vector<Task> create_tasks()
{
    vector<Task> tasks;
    for (int i = 0; i < 5; i++)
    {
        Task newTask = Task(i + 1, 100); // i+1 cause of the paper
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
    w.add_edge(2, 3);
    w.add_edge(1, 3);
    w.add_edge(2, 4);

    vector<Vm> vms = create_vms();
    Broker broker  = Broker(vms, w);
    broker.run();
    return 0;
}
