#include <functional>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "task.cpp"

using namespace std;

// bool IdMatch(Task task){
//     if (task.id==id)
//     {
//         return true;
//     }
//     return false;
// }
 
int main()
{
    std::vector<Task> v;
    int n = 12;
     
    // auto result = std::find(begin(v), end(v), n);
   
    vector<Task>::iterator it = std::find_if(v.begin(), v.end(), IdMatch);
    // cout << v[it - v.begin()]<< endl;
    
}