#include <iostream>
#include <vector>
#include "workflow.cpp"
#include <algorithm>
#include <string>

using namespace std;
class Broker
{
public:
    vector<Vm*> vms;
    Workflow w;

    Broker(vector<Vm*> vms, Workflow w)
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
        cout << execution_times();
            if (task->dependancies_done())
            {
                Vm found_vm = find_vm(*task);
                found_vm.assign(*task);
            }
        }

    }

    string execution_times(){
        string ret;
        for (auto &&vm : vms)
        {
            ret.append(to_string(vm->execution_time));
            ret.append(" | ");
        }
        ret.append("\n");
        return ret;
    }

    // Finds the vm to which if a task is added the total execution
    // time of the workflow will be the minimum possible one
    Vm find_vm(Task task)
    {
        double min = vms.at(0)->task_execution_time(task) + vms.at(0)->get_execution_time();
        Vm minimum = *vms.at(0);
        for (auto &&vm : vms)
        {
            if (vm->task_execution_time(task) + vm->get_execution_time() < min)
                minimum = *vm;
        }
        return minimum;
    }

    void display()
    {
        for (auto &&task : w.tasks)
        {
            cout << task->up_rank << "\n";
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
            task->up_rank = upward_rank(*task);
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
            // Is this usefull? I doubt it. Maybe? Leave it for now. If there are any problems with calculations this might be it
            // vector<Task> next = task.next;
            return (mean_comp + maxNext(task.next));
        }
    }
    double maxNext(vector<Task*> next)
    {
        double maximum = 0;
        for (auto &&task : next)
        {
            if (upward_rank(*task) > maximum)
                maximum = upward_rank(*task);
        }
        return maximum;
    }

    // TODO add a return statement for each case, if the function is needed 
    int exit_task()
    {
        for (int i = 0; i < w.tasks.size(); i++)
        {
            if (w.tasks.at(i)->next.empty())
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
                sum = sum + (task->mips / vm->mips_capacity);
            }
        }
        return sum / vms.size();
        // test
        // return 5;
    }
    // TODO implement later if needed
    // Returns the numerical value of the mean communication of the tasks inside the workflow
    double mean_communication()
    {
        return 0;
    }
};
