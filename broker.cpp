#include <iostream>
#include <vector>
#include "task.cpp"
#include "vm.cpp"
#include "workflow.cpp"

using namespace std;
class broker
{
public:
    vector<Vm> vms;
    Workflow w;

    broker();
private:
    // TODO write upward rank function to calculate task priorities
    // Returns the numerical value of the upward rank of a task
    double upward_rank(Task task)
    {
        //use nodeweight function from sim3
        double mean_comp = mean_computation();
        if (task.next.empty()==true)
        {
            return mean_comp;
        }
        else
        {
            vector<Task> next = task.next;
            // return (mean_comp + maxNext())
        }
        
    }
    int exit_task()
    {
        for (int i = 0; i < w.tasks.size(); i++)
        {
            if (w.tasks.at(i).next.empty() == true)
            {
                return i;
            }
        }
    }

    // Returns the numerical value of the mean computation of the tasks inside the workflow
    double mean_computation()
    {
        double sum = 0;
        for (int i = 0; i < vms.size(); i++)
        {
            for (int j = 0; i < w.tasks.size(); j++)
            {
                sum = sum + (w.tasks.at(j).mips / vms.at(i).mips_capacity);
            }
        }
        return sum / vms.size();
    }
    //TODO implement later if needed 
    // Returns the numerical value of the mean communication of the tasks inside the workflow
    double mean_communication()
    {
        return 0;
    }
};
