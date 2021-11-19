#include <functional>
#include <iostream>
#include <vector>

#include "task.cpp"
#include "workflow.cpp"
using namespace std;

// test if dependancies done works
// redesign the broker run function

int main(int argc, char const* argv[])
{
    Task t0 = Task("t0", 100);

    cout << t0.toString() << endl;
    return 0;
}
