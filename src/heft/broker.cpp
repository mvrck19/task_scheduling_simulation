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

    // TODO
    void run()
    {
        cout << "Vm - Task \t|Vm - Task \t|Vm - Task" << endl;
        for (auto&& task : w.tasks)
        {
            cout << execution_times();
            if (task.dependancies_done())
            {
                // add task dependancy time

                // vms.at(dep_time(task));
                assign(vms.at(find_least_execution_time(task)), task);
            }
        }
        cout << execution_times();
    }

    // for task dependancies
    //      find largest time dependancy && add time to execution of task
    double dep_time(Task task)
    {
        auto max = max_element(task.prev.begin(), task.prev.end(), dep_comp);
        auto pos = distance(task.prev.begin(), max);
        return task.prev.empty() ? 0 : task.prev.at(pos).get().execution_time;
    }

    // comparrison function for sorting dependancy tasks
    static bool dep_comp(const Task a, const Task b)
    {
        return (a.execution_time > b.execution_time);
    }

    // Find the vm on which the exececution of the task will have the least time if assigned
    int find_least_execution_time(Task& task)
    {
        int index  = 0;
        double min = vms.at(0).get_execution_time() + get_cost(vms.at(0).id, task.id);

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

    // TODO
    // add transfer time
    void assign(Vm& vm, Task& task)
    {
        task.vm_id = vm.id;
        // Also add the transmission time and it should work
        auto tr_time = transfer_time(task);
        auto d_time  = dep_time(task);
        auto c_cost = get_cost(vm.id, task.id);

        vm.execution_time += tr_time;
        cout << tr_time << " - trasfer time" << endl;
        vm.execution_time += d_time;
        vm.execution_time += c_cost;
        // -----expiramental-----
        task.execution_time += tr_time;
        task.execution_time += d_time;
        task.execution_time += c_cost;
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

    // returns whether the task is scheduled on the same vm as one of its predecessors
    static bool same_vm(Task task){
        bool same = true;
        for (int i = 0; i < task.prev.size(); i++)
        {
            if (task.prev[i].get().vm_id != task.vm_id)
                same = false;
        }
        return same;
    }




    // returns the time it takes to transfer a task from one vm to another
    double transfer_time(Task task)
    {
        auto max = max_element(task.comm_cost_in.begin(), task.comm_cost_in.end());
        auto pos = distance(task.comm_cost_in.begin(), max);
        if (task.comm_cost_in.empty())
            return 0;
        // FIXME: check if task.vm_id is the same as task.prev.vm_id for any of the previeous tasks
        // else if (task.vm_id == task.id)
        else if (same_vm(task))
            return 0;
        else
            return task.comm_cost_in.at(pos);
    }

    void whatever()
    {
        cout << endl;

        cout << "Vm "
             << "Task" << endl;
        for (auto&& task : w.tasks)
        {
            cout << task.vm_id << ": " << task.id << endl;
        }
    }

    // TODO
    string execution_times()
    {
        string ret;
        for (auto&& vm : vms)
        {
            ret.append(to_string((int)vm.execution_time));
            if (vm.execution_time != 0)
            {
                ret.append(" - ");
                ret.append(vm.exec.back().toString());
            }
            ret.append("\t\t|");
        }
        ret.append("\n");
        return ret;
    }

    void display()
    {
        cout << endl;
        for (auto&& task : w.tasks)
        {
            cout << "Task id : " << task.id << "\tTask rank : " << task.up_rank << "\n";
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
            temp = temp + task.comm_cost_out[i];
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