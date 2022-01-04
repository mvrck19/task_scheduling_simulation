#include <functional>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

 
int main()
{
    std::vector<int> v{12, 36, 28, 41};
    int n1 = 12;
     
    auto result = std::find(begin(v), end(v), n1);
   
    cout << v[result] << endl;
    
}