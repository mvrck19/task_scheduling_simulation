#include <functional>
#include <iostream>
#include <string>
#include <vector>

#pragma once
using namespace std;
class Task
{
  public:
    string name = "";
    int id;
    int vm_id;
    int mips;
    double up_rank;
    double total_time;
    double execution_time;
    bool done = false;
    vector<double> comm_cost_in;
    vector<double> comm_cost_out;
    vector<reference_wrapper<Task>> prev;
    vector<reference_wrapper<Task>> next;

    Task(int id, int mips)
    {
        this->id       = id;
        this->mips     = mips;
        this->done     = false;
        execution_time = 0;
    }

    Task(int id)
    {
        this->id       = id;
        this->done     = false;
        execution_time = 0;
    }

    // Returns id from the paper (so i might need to change it later)
    string toString()
    {
        return to_string(id + 1);
    }

    bool getDone()
    {
        return done;
    }

    void setDone(bool done)
    {
        this->done = done;
    }

    bool dependancies_done()
    {
        bool d = true;

        for (auto&& task : prev)
        {
            if (task.get().done == false)
            {
                d = false;
                break;
            }
        }
        return d;
    }

    void display()
    {
        cout << "Mips: " << mips << endl;
        cout << "Parents: " << prev.size() << endl;
        cout << "Children: " << next.size() << endl;
    }
};