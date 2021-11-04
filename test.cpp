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
    Task t0 = Task("t0", 100);
   
    cout <<  t0.toString()<<endl;
    return 0;
}
