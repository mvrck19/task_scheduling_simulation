#include <iostream>
#include <string>
#include "workflow.cpp"
using namespace std;

class test
{
public:
    Workflow work;
    test(Workflow w)
    {

        work.tasks = w.tasks;
        work.tasks.at(0)->mips = 320;
    };
    test(Task &bull)
    {
        bull.mips = 12;
    }
    void prnt()
    {
        cout << work.tasks.at(0)->mips;
    }
};

int main(int argc, char const *argv[])
{
    Task t0 = Task(100);
    Task t1 = Task(100);
    Task t2 = Task(100);
    Task t3 = Task(100);

    Workflow w = Workflow();

    w.add_task(t0);
    w.add_task(t1);
    w.add_task(t2);
    // w.add_task(t3);
    test b = test(w);
    w.display();
    b.prnt();

    return 0;
}
