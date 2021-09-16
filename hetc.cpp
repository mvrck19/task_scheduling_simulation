#include <iostream>
#include <vector>
#include "task.cpp"
#include "workflow.cpp"

using namespace std;

int main(int argc, char const *argv[])
{
    Task t0 = Task(100);
    Task t1 = Task(200);
    Workflow w = Workflow();
    w.add_task(t0);
    w.add_task(t1);
    w.add_edge(0,1);
    w.display();
    return 0;
}
