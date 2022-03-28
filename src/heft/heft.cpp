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
        Vm newVm = Vm(i); 
        vms.push_back(newVm);
    }
    return vms;
}

vector<Task> create_tasks()
{
    vector<Task> tasks;
    for (int i = 0; i < 10; i++)
    {
        Task newTask = Task(i, 100); 
        tasks.push_back(newTask);
    }
    return tasks;
}

int main(int argc, char const* argv[])
{
    Workflow w = Workflow();

    w.add_tasks(create_tasks());

    w.add_edge(0, 1,18);
    w.add_edge(0, 2,12);
    w.add_edge(0, 3,9);
    w.add_edge(0, 4,11);
    w.add_edge(0, 5,14);
    w.add_edge(1,7,19);
    w.add_edge(1,8,16);
    w.add_edge(2,6,23);
    w.add_edge(3,7,27);
    w.add_edge(3,8,23);
    w.add_edge(4,8,13);
    w.add_edge(5,7,15);
    w.add_edge(6,9,17);
    w.add_edge(7,9,11);
    w.add_edge(8,9,13);

    vector<Vm> vms = create_vms();
    Broker broker  = Broker(vms, w);

    broker.run();
    cout << endl;
    broker.details();

    return 0;
}
