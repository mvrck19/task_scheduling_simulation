#include <iostream>
#include <vector>
#include "task.cpp"
#include "workflow.cpp"
#include "broker.cpp"

using namespace std;

vector<Vm> create_vms()
{
    vector<Vm> vms;
    for (int i = 0; i < 1; i++)
    {
        Vm newVm = Vm(100);
        vms.push_back(newVm);
    }
    return vms;
}

int main(int argc, char const *argv[])
{
    vector<Vm> vms = create_vms();
    Task t0 = Task("t0",100);
    Task t1 = Task("t1",100);
    Task t2 = Task("t2",100);
    Task t3 = Task("t3",100);

    Workflow w = Workflow();
    w.add_task(t0);
    w.add_task(t1);
    w.add_task(t2);
    w.add_task(t3);

    w.add_edge(0, 1);
    w.add_edge(0, 2);
    w.add_edge(2, 3);
    w.add_edge(1, 3);

    // w.display();
    Broker broker = Broker(vms, w);
    // broker.display();
    broker.run();
    return 0;
}
