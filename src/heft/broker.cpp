#include <algorithm>
#include <cfloat>
#include <cstdlib>
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
    int clock = 0;

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
        while (all_done() == false)
        {
            for (auto&& task : w.tasks)
            {
                double min_eft = DBL_MAX;
                int min_vm_id  = 0;
                for (auto&& vm : vms)
                {
                    if (min_eft > eft(task, vm))
                    {
                        min_eft   = eft(task, vm);
                        min_vm_id = vm.id;
                    }
                }
                assign(vms.at(min_vm_id), task);
                cout << execution_times();
            }
        }
    }

    // finds ready tasks and changes their state to ready
    void ready_tasks()
    {
        for (auto&& task : w.tasks)
        {
            task.state = READY;
        }
    }

    // checks if all tasks are finnished
    bool all_done()
    {
        bool done = true;
        for (auto&& task : w.tasks)
        {
            if (task.state != FINNISHED)
            {
                done = false;
                break;
            }
        }
        return done;
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

    bool idle_vm_available()
    {
        bool available = false;
        for (auto&& vm : vms)
        {
            if (vm.get_state() == IDLE)
            {
                available = true;
                break;
            }
        }
        return available;
    }

    int find_idle_vm()
    {
        int index = 0;
        for (int i = 0; i < vms.size(); i++)
        {
            if (vms.at(i).get_state() == IDLE)
            {
                index = i;
                break;
            }
        }
        return index;
    }

    // returns the cost of running the task on the vm
    int get_cost(int vm_id, int task_id)
    {
        return comp_costs[vm_id][task_id];
    }

    // TODO
    // add transfer time
    void assign(Vm& vm, Task& task)
    {
        task.vm_id        = vm.id;
        task.aft          = eft(task, vm);
        task.state        = FINNISHED;
        task.ast          = est(task, vm);
        vm.execution_time = task.aft;
        vm.exec.push_back(task);
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
    static bool same_vm(Task task)
    {
        bool same = true;
        for (int i = 0; i < task.prev.size(); i++)
        {
            if (task.prev[i].get().vm_id != task.vm_id)
                same = false;
        }
        return same;
    }

    // prints the assigned vms of all tasks
    void assigned_vms()
    {
        cout << endl;
        cout << "Vm "
             << "Task" << endl;
        for (auto&& task : w.tasks)
        {
            cout << task.vm_id << ": " << task.id << endl;
        }
    }

    // prints the ast and aft of all tasks
    void details()
    {
        for (auto&& task : w.tasks)
        {
            cout << "Task: " << task.id + 1;
            cout << " \tRANK: " << task.up_rank;
            cout << " \tVM: " << task.vm_id + 1;
            cout << " \tAST: " << task.ast;
            cout << " \tAFT: " << task.aft << endl;
        }
    }

    // returns a string that contains the task currently running on each vm
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

    // prints the tasks and their predecessors
    void print_task_pred()
    {
        for (auto&& task : w.tasks)
        {
            cout << "------------------\n";
            cout << "Task id : " << task.id << "\n------------------\n";
            for (auto&& task : task.prev)
            {
                cout << "Prev id: " << task.get().id << " ";
            }
            cout << "\n";
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
            temp        = temp + task.comm_cost_out[i];
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

    // returns earliest finish time
    double eft(Task task, Vm vm)
    {
        double temp = est(task, vm) + get_cost(vm.id, task.id);
        return temp;
    }

    // returns earliest start time
    double est(Task task, Vm vm)
    {
        double available = available_time(vm);
        double ready     = ready_time(task, vm);
        double est       = max(available, ready);
        return est;
    }

    // the time when the vm is next available for execution
    // TODO check correctness
    double available_time(Vm vm)
    {
        return vm.execution_time;
    }
    // returns task ready time
    double ready_time(Task task, Vm vm)
    {
        auto temp_max = 0;
        for (auto&& prev : task.prev)
        {
            double temp = prev.get().aft;
            if (prev.get().vm_id != vm.id)
                temp += comm_cost(task, prev);
            if (temp > temp_max)
                temp_max = temp;
        }
        return temp_max;
    }
    // returns the communication cost between two tasks
    double comm_cost(Task task, Task prev)
    {
        int id           = prev.id;
        double comm_cost = 0;
        for (auto&& thing : task.thing_in)
        {
            if (get<0>(thing).id == id)
                comm_cost = get<1>(thing);
        }
        return comm_cost;
    }
};
