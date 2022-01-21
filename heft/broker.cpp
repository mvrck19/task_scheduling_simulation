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
                // add task dependancy time
                transfer_task(task);
                assign(vms.at(find_least_execution_time(task)), task);
            }
        }
        cout << execution_times();
    }

    void transfer_task(Task task)
    {
        // for task dependancies
        //      find largest time dependancy && add time to execution of task

        // auto largest = sort(task.prev.begin,task.prev.end,dep_comp).execution_time;
        auto largest = max_element(task.prev.begin(), task.prev.end(), dep_comp);
    }

    // comparrison function for sorting dependancy tasks
    static bool dep_comp(const Task a, const Task b)
    {
        return (a.execution_time > b.execution_time);
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

    int get_cost(int vm_id, int task_id)
    {
        return comp_costs[vm_id][task_id];
    }

    void assign(Vm& vm, Task& task)
    {
        // vm.execution_time += task.comm_cost + comp_costs[vm.id][task.id];
        vm.execution_time += comp_costs[vm.id][task.id];
        // -----expiramental-----
        task.execution_time += comp_costs[vm.id][task.id];
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

    // not used
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
        double rank      = 0;
        double mean_comp = mean_computation(task);
        if (task.next.empty())
        {
            rank = mean_comp;
        }
        else
        {
            rank = (mean_comp + maxNext(task));
        }
        return rank;
    }

    double maxNext(Task task)
    {
        double maximum = 0;
        for (int i = 0; i < task.next.size(); i++)
        {
            double temp = upward_rank(task.next[i]);
            temp        = temp + task.next[i].get().comm_cost[i];
            if ((temp) > maximum)
                maximum = temp;
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
    
    // not used
    double mean_communication()
    {
        return 0;
    }
};
