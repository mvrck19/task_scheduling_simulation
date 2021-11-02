#include <iostream>
#include <functional>
#include "workflow.cpp"
#include "task.cpp"
#include <vector>
using namespace std;

//test if dependancies done works
//redesign the broker run function

int main(int argc, char const *argv[])
{
    
    Task t0 = Task(100);
    // Task t1 = Task(100);

    // Workflow w = Workflow();
    // w.add_task(t0);
    // w.add_task(t1);

    // w.add_edge(0, 1);
    // w.tasks.at(0).next.at(0).done=true;

    vector<reference_wrapper<Task>> tasks;
    tasks.push_back(t0);
    t0.done=true;
    cout << tasks.at(0).get().done << endl;

    return 0;
}
