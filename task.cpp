#include <iostream>
#include <vector>
#pragma once
using namespace std;
class Task
{
public:
   int mips;
   vector<Task> prev;
   vector<Task> next;

   Task(int mips)
   {
      this->mips=mips;
   }

   void display()
   {
      cout << "Mips: " << mips << "\n";
      cout << "Parents: " << prev.size() << "\n";
      cout << "Children: " << next.size() << "\n" ;
   }
};
