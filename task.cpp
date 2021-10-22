#include <iostream>
#include <vector>
#pragma once
using namespace std;
class Task
{
public:
   int id;
   int mips;
   double up_rank; //May need to remove later
   bool done=false;
   vector<Task*> prev;
   vector<Task*> next;

   Task(int mips)
   {
      this->mips = mips;
      this->done = false;
   }

   bool getDone(){
      return done;
   }

   void setDone(bool done){
      this->done=done;
   }

   bool dependancies_done()
   {
      bool done = true;
      for (auto &&task : prev)
      {
         if (task->done == false)
         {
            done = false;
            break;
         }
      }
      return done;
   }

   void display()
   {
      cout << "Mips: " << mips << "\n";
      cout << "Parents: " << prev.size() << "\n";
      cout << "Children: " << next.size() << "\n";
   }
};
