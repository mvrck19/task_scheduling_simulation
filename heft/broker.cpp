#include <stdlib.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "workflow.cpp"

using namespace std;
class Broker
{
  public:
    vector<Vm> vms;
    Workflow w;

    Broker(vector<Vm>& vms, Workflow& w)
    {
        this->vms = move(vms);
        this->w   = move(w);
        create_rank();
        rank_sort();
    };

    void give_comp_to_tasks(){
        
    };

    void run()
    {
        for (auto&& task : w.tasks)
        {
            cout << execution_times();
            if (task.dependancies_done())
            {
                vms.at(find_least_execution_time(task)).assign(task);
            }
        }
        cout << execution_times();
    }

    // Find the vm on which the exececution of the task will have the least time if assigned
    int find_least_execution_time(Task& task)
    {
        int index = 0;
        int min   = vms.at(0).get_execution_time() + vms.at(0).task_execution_time(task);

        for (int i = 1; i < vms.size(); i++)
        {
            if (vms.at(i).task_execution_time(task) + vms.at(i).get_execution_time() < min)
                index = i;
        }
        return index;
    }

    int comp_costs[3][10] = {{14, 13, 11, 13, 12, 13, 7, 5, 18, 21},
                             {16, 19, 13, 8, 13, 16, 15, 11, 12, 7},
                             {9, 18, 19, 17, 10, 9, 11, 14, 20, 16}};

    string execution_times()
    {
        string ret;
        for (auto&& vm : vms)
        {
            ret.append(to_string(vm.execution_time));
            if (vm.execution_time != 0)
            {
                // TODO if its not the first time
                ret.append(" - ");
                ret.append(vm.exec.back().toString());
            }
            ret.append("\t|");
        }
        ret.append("\n");
        return ret;
    }

    void display()
    {
        for (auto&& task : w.tasks)
        {
            cout << task.up_rank << "\n";
        }
    }

  private:
    void rank_sort()
    {
        sort(w.tasks.begin(), w.tasks.end(), comp);
    }

    static bool comp(const Task a, const Task b)
    {
        return (a.up_rank > b.up_rank);
    }

    void create_rank()
    {
        for (auto&& task : w.tasks)
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
            // Is this usefull? I doubt it. Maybe? Leave it for now. If there are
            // any problems with calculations this might be it
            // vector<Task> next = task.next;
            return (mean_comp + maxNext(task.next));
        }

        // return rand() % 10 + 1;
    }
    double maxNext(vector<reference_wrapper<Task>> next)
    {
        double maximum = 0;
        for (auto&& task : next)
        {
            if (upward_rank(task) > maximum)
                maximum = upward_rank(task);
        }
        return maximum;
    }

    double mean_computation()
    {
        double sum = 0;
        for (auto&& vm : vms)
        {
            for (auto&& task : w.tasks)
            {
                sum = sum + (task.mips / vm.mips_capacity);
            }
        }
        return sum / vms.size();
        // test
        // return 5;
    }
    // TODO implement later if needed
    // Returns the numerical value of the mean communication of the tasks inside
    // the workflow
    double mean_communication()
    {
        return 0;
    }
};
