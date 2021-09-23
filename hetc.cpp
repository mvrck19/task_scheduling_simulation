#include <iostream>
#include <vector>
#include "task.cpp"
#include "workflow.cpp"
#include "broker.cpp"

using namespace std;

vector<Vm> create_vms()
{
    vector<Vm> vms;
    for (int i = 0; i < 10; i++)
    {
        vms.push_back(Vm(100));
    }

    return vms;
}

int main(int argc, char const *argv[])
{
    vector<Vm> vms = create_vms();
    Task t0 = Task(100);
    Task t1 = Task(200);
    Workflow w = Workflow();
    w.add_task(t0);
    w.add_task(t1);
    w.add_edge(0, 1);
    // w.display();
    Broker broker = Broker(vms, w);
    broker.display();
    return 0;
}
