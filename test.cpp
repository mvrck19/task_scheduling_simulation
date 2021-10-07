#include <iostream>
#include <vector>
using namespace std;
bool dependancies_done(vector<int> numbers)
{
    bool done = true;
    for (auto &&number : numbers)
    {
        cout << number << "\n";
        if (number == 2)
        {
            done = false;
            break;
        }
    }
    return done;
}
int main(int argc, char const *argv[])
{
    vector<int> numbers = {1, 2, 3};
    if (dependancies_done(numbers))
        cout << "True\n";
}
