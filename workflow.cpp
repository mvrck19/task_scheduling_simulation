#include <iostream>
#include <vector>
#include "task.cpp"
#include "vm.cpp"
#pragma once

using namespace std;
class Workflow
{
public:
    vector<Task *> tasks;  
    // Add edge between tasks on the workflow.
    // (Tasks must already be in the workflow to add edge between them)
    void add_edge(int t1, int t2)
    {
        tasks.at(t1)->next.push_back(tasks.at(t2));
        tasks.at(t2)->prev.push_back(tasks.at(t1));
    }
    // Create task and add it to the workflow
    void add_task(int mips)
    {
        Task newTask = Task(mips);
        tasks.push_back(&newTask);
    }
    // Add already existing task to the workflow
    void add_task(Task t)
    {
        tasks.push_back(&t);
    }
    // Display the properties of each task on the workflow
    void display()
    {
        for (int i = 0; i < tasks.size(); i++)
        {
            tasks.at(i)->display();
        }
    }
};
