#include <iostream>
#include <vector>

#include "task.cpp"
#include "vm.cpp"
#pragma once

using namespace std;
class Workflow
{
  public:
    vector<Task> tasks;
    // Add edge between tasks on the workflow.
    void add_edge(int t1, int t2, int comm_cost)
    {
        if(t1 >= tasks.size() || t2 >= tasks.size())
            throw "Task index out of bounds";
        tasks[t1].next.push_back(tasks[t2]);
        tasks[t2].prev.push_back(tasks[t1]);
        tasks[t1].comm_cost_out.push_back(comm_cost);
        tasks[t2].comm_cost_in.push_back(comm_cost);
        // todo: see if this works
        tasks[t1].thing_out.push_back(make_tuple(tasks[t2], comm_cost));
        tasks[t2].thing_in.push_back(make_tuple(tasks[t1], comm_cost));
    }
    // Add already existing task to the workflow
    void add_task(Task t)
    {
        tasks.push_back(t);
    }
    // Add tasks to the workflow
    void add_tasks(vector<Task> ts)
    {
        for (Task t : ts)
        {
            tasks.push_back(t);
        }
    }
    // Display the properties of each task on the workflow
    void display()
    {
        for (int i = 0; i < tasks.size(); i++)
        {
            tasks[i].display();
        }
    }
};
