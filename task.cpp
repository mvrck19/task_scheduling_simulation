#include <iostream>
#include <vector>
#include <functional>
#include <string>
#pragma once
using namespace std;
class Task
{
public:
   string name="";
   int id;
   int mips;
   double up_rank; //May need to remove later
   bool done = false;
   vector<reference_wrapper<Task>> prev;
   vector<reference_wrapper<Task>> next;

   Task(string name, int mips)
   {
      this->name = name;
      this->mips = mips;
      this->done = false;
   }

   string toString(){
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
