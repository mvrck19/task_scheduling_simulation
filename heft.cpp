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
        Vm newVm = Vm(100);
        vms.push_back(newVm);
    }
    return vms;
}

int main(int argc, char const* argv[])
{
    vector<Vm> vms = create_vms();
    vms.push_back(Vm(200));

    Task t0 = Task("t0", 100);
    Task t1 = Task("t1", 100);
    Task t2 = Task("t2", 100);
    Task t3 = Task("t3", 100);
    Task t4 = Task("t4", 100);

    Workflow w = Workflow();
    w.add_task(t0);
    w.add_task(t1);
    w.add_task(t2);
    w.add_task(t3);
    w.add_task(t4);

    w.add_edge(0, 1);
    w.add_edge(0, 2);
    w.add_edge(2, 3);
    w.add_edge(1, 3);
    w.add_edge(2, 4);

    // w.display();
    Broker broker = Broker(vms, w);
    // broker.display();
    broker.run();
    return 0;
}
