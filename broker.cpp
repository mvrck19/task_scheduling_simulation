#include <iostream>
#include <vector>
#include "workflow.cpp"
#include <algorithm>

using namespace std;
class Broker
{
public:
    vector<Vm> vms;
    Workflow w;

    Broker(vector<Vm> vms, Workflow w)
    {
        this->vms = vms;
        this->w = w;
        create_rank();
        rank_sort();
    };

    void run()
    {
        for (auto &&task : w.tasks)
        {
            if (task.dependancies_done())
            {
                Vm found_vm = find_vm(task);
                found_vm.assign(task);
            }
        }
    }

    // Finds the vm to which if a task is added the total execution
    // time of the workflow will be the minimum possible one
    Vm find_vm(Task task)
    {
        double min = task.execution_time(vms.at(0))+vms.at(0).execution_time;
        Vm minimum = vms.at(0);
        for (auto &&vm : vms)
        {
            if(task.execution_time(vm)+vm.execution_time<min) minimum = vm;
        }
        return minimum;
    }

    void display()
    {
        for (auto &&task : w.tasks)
        {
            cout << task.up_rank << "\n";
        }
    }

private:
    void rank_sort()
    {
        sort(w.tasks.begin(), w.tasks.end(), comp);
    }

    static bool comp(Task a, Task b)
    {
        return (a.up_rank > b.up_rank);
    }

    void create_rank()
    {
        for (auto &&task : w.tasks)
        {
            task.up_rank = upward_rank(task);
        }
    }

    // Returns the numerical value of the upward rank of a task
    double upward_rank(Task task)
    {
        double mean_comp = mean_computation();
        if (task.next.empty())
        {
            return mean_comp;
        }
        else
        {
            vector<Task> next = task.next;
            return (mean_comp + maxNext(task.next));
        }
    }
    double maxNext(vector<Task> next)
    {
        double maximum = 0;
        for (auto &&task : next)
        {
            if (upward_rank(task) > maximum)
                maximum = upward_rank(task);
        }
        return maximum;
    }
    int exit_task()
    {
        for (int i = 0; i < w.tasks.size(); i++)
        {
            if (w.tasks.at(i).next.empty())
            {
                return i;
            }
        }
    }
    // Returns the numerical value of the mean computation of the tasks inside the workflow
    double mean_computation()
    {
        double sum = 0;
        for (auto &&vm : vms)
        {
            for (auto &&task : w.tasks)
            {
                sum = sum + (task.mips / vm.mips_capacity);
            }
        }
        return sum / vms.size();
        // return 5;
    }
    // TODO implement later if needed
    // Returns the numerical value of the mean communication of the tasks inside the workflow
    double mean_communication()
    {
        return 0;
    }
};
