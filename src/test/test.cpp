#include "fmt/core.h"
#include <algorithm>
#include <fmt/core.h>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>
// #include <format>

using namespace std;
static bool eqten(int i)
{
    if (i == 10)
        return true;
    else
        return false;
}

int main()
{
    vector v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    if (find_if(v.begin(), v.end(), eqten) != v.end())
    {
        cout << "Found 10" << endl;
    }
    else
    {
        cout << "Not found 10" << endl;
    }
}