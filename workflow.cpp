#include <iostream>
#include <vector>
#include "task.cpp"
#include "vm.cpp"

using namespace std;
class Workflow
{
public:
    vector<Task> tasks;
    void add_edge(int t1, int t2)
    {
        tasks.at(t1).next.push_back(tasks.at(t2));
        tasks.at(t2).prev.push_back(tasks.at(t1));
    }

    void add_task(int mips)
    {
        tasks.push_back(Task(mips));
    }
    void add_task(Task t)
    {
        tasks.push_back(t);
    }
    void display()
    {
        for (int i = 0; i < tasks.size(); i++)
        {
            tasks.at(i).display();
        }
    }
    // TODO write upward rank function to calculate task priorities
private:
    void upward_rank(int task)
    {
    }
    int exit_task()
    {
        for (int i = 0; i < tasks.size(); i++)
        {
            if (tasks.at(i).next.empty() == true)
            {
                return i;
            }
        }
    }

    // TODO check that this works mathematically
    double mean_computation(vector<Vm> vms)
    {
        double sum;
        for (int i = 0; i < vms.size(); i++)
        {
            for (int j = 0; i < tasks.size(); j++)
            {
                sum = tasks.at(j).mips / vms.at(i).mips_capacity;
            }
        }
        return sum / vms.size();
    }
    // Average start up communication cost L can be neglected for now
    //TODO find how to calculate this, especially the data cost part, L can be neglected and B can be measured probably
    double mean_communication()
    {   

    }
};
