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
    int mips;
    double up_rank; // May need to remove later
    bool done = false;
    int comp_costs[3][10];
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
        return name;
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
