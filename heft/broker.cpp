#include <stdlib.h>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "workflow.cpp"

using namespace std;
class Broker
{
  public:
    vector<Vm> vms;
    Workflow w;

    const int comp_costs[3][10] = {{14, 13, 11, 13, 12, 13, 7, 5, 18, 21},
                                   {16, 19, 13, 8, 13, 16, 15, 11, 12, 7},
                                   {9, 18, 19, 17, 10, 9, 11, 14, 20, 16}};

    Broker(vector<Vm>& vms, Workflow& w)
    {
        this->vms = move(vms);
        this->w   = move(w);
        create_rank();
        rank_sort();
    };

    void run()
    {
        for (auto&& task : w.tasks)
        {
            cout << execution_times();
            if (task.dependancies_done())
            {
                assign(vms.at(find_least_execution_time(task)), task);
            }
        }
        cout << execution_times();
    }

    // Find the vm on which the exececution of the task will have the least time if assigned
    int find_least_execution_time(Task& task)
    {
        int index = 0;
        int min   = vms.at(0).get_execution_time() + get_cost(vms.at(0).id, task.id);

        for (int i = 1; i < vms.size(); i++)
        {
            if (get_cost(vms.at(i).id, task.id) + vms.at(i).get_execution_time() < min)
                index = i;
        }
        return index;
    }

    // Returns the id of the vm on which the exececution of the task will have the least time if assigned
    // Duplicate
    // int least_execution_time(Task& task)
    // {
    //     int id  = vms.at(0).id;
    //     int min = vms.at(0).get_execution_time() + get_cost(vms.at(0).id, task.id);

    //     for (int i = 1; i < vms.size(); i++)
    //     {
    //         if (get_cost(vms.at(i).id, task.id) + vms.at(i).get_execution_time() < min)
    //             id = vms.at(i).id;
    //     }
    //     return id;
    // }

    int get_cost(int vm_id, int task_id)
    {
        return comp_costs[vm_id][task_id];
    }

    void assign(Vm& vm, Task& task)
    {
        // vm.execution_time += task.comm_cost + comp_costs[vm.id][task.id];
        vm.execution_time +=  comp_costs[vm.id][task.id];

        vm.exec.push_back(task);

        task.setDone(true);
    }

    // get vm by id
    Vm& get_vm(int id)
    {
        return vms.at(id);
    }

    // get task by id
    Task& get_task(int id)
    {
        return w.tasks[id];
    }

    int transfer_time(Task task)
    {
        // int transfer = 0;
        // for (auto&& t : task.prev)
        // {
        //     if (t.vm_id != task.vm_id)
        //         transfer += get_comm_cost(t.vm_id, task.id);
        // }
        // return task.comm_cost;
        return 0;
    }

    string execution_times()
    {
        string ret;
        for (auto&& vm : vms)
        {
            ret.append(to_string(vm.execution_time));
            if (vm.execution_time != 0)
            {
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
        double mean_comp = mean_computation(task);
        if (task.next.empty())
        {
            return mean_comp;
        }
        else
        {
            return (mean_comp + maxNext(task.next));
        }
    }

    double maxNext(vector<reference_wrapper<Task>> next)
    {
        double maximum = 0;
        // old code
        // for (auto&& task : next)
        // {   // Find communication cost of the current task (which is it)
        //     // do the loop in i form and get the comm_cost elemnt for free
        //     if ((upward_rank(task)+task.get().comm_cost_in[0]) > maximum)
        //         maximum = upward_rank(task);
        // }

        for (int i = 0; i < next.size(); i++)
        {
            if ((upward_rank(next[i])+next[i].get().comm_cost[i]) > maximum)
                maximum = upward_rank(next[i]);
        }

        return maximum;
    }

    double mean_computation(Task task)
    {
        double sum = 0;
        for (auto&& vm : vms)
        {
            sum = sum + comp_costs[vm.id][task.id];
        }
        return sum / vms.size();
    }

    double mean_communication()
    {
        // double sum = 0;

        // for (auto&& task : w.tasks)
        // {
        //     sum = sum + task.comm_cost;
        // }
        // return sum / w.tasks.size();

        return 0;
    }
};
