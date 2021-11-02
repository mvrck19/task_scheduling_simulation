#include <iostream>
#include <vector>
#include <functional>
#pragma once
using namespace std;
class Task
{
public:
   int id;
   int mips;
   double up_rank; //May need to remove later
   bool done = false;
   vector<reference_wrapper<Task>> prev;
   vector<reference_wrapper<Task>> next;

   Task(int mips)
   {
      this->mips = mips;
      this->done = false;
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
      for (auto &&task : prev)
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
