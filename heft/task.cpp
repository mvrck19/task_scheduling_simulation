#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <string>
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
    bool done = false;
    vector<double> comm_cost;
    vector<double> comm_cost_out;
    vector<reference_wrapper<Task>> prev;
    vector<reference_wrapper<Task>> next;

    Task(int id, int mips)
    {
        this->id   = id;
        this->mips = mips;
        this->done = false;
    }

    Task(int id)
    {
        this->id   = id;
        this->done = false;
    }

    string toString()
    {
        //Returns id from the papes (so i might need to change it later)
        // string t = "t";
        // return t.append(to_string(id+1));
        return to_string(id+1);
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
        cout << "Mips: " << mips << "\n";
        cout << "Parents: " << prev.size() << "\n";
        cout << "Children: " << next.size() << "\n";
    }
};
