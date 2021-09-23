#include <iostream>
#include <vector>
using namespace std;
int main(int argc, char const *argv[])
{
    vector<int> numbers={1,2,3};

    for (auto &&i : numbers)
    {
        cout << i;
    }
    

    return 0;
}
