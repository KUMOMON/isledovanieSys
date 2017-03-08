#include <iostream>
#include <methods.h>
#include <iomanip>

using namespace std;

template<typename T>
using matrix = vector<vector<T>>;

matrix<int> GetSomeMatrixByIndex(const unsigned short int);
void ShowMatrixToMonitor(const matrix<int>&) noexcept;

int main()
{

    cout << "Hello World!" << endl;
    matrix<int> m = GetSomeMatrixByIndex(6);
    ShowMatrixToMonitor(m);

    return 0;
}

matrix<int> GetSomeMatrixByIndex(const unsigned short int index)
{
    matrix<int> _matrix;

    switch (index) {

    case 1://Последовательная структура
        _matrix = {{0,1,0,0,0},
                   {1,0,1,0,0},
                   {0,1,0,1,0},
                   {0,0,1,0,1},
                   {0,0,0,1,0}};break;

    case 2://Кольцевая структура
        _matrix = {{0,1,0,0,1},
                   {1,0,1,0,0},
                   {0,1,0,1,0},
                   {0,0,1,0,1},
                   {1,0,0,1,0}};break;

    case 3://Радиальная структура
        _matrix = {{0,1,1,1,1},
                   {1,0,0,0,0},
                   {1,0,0,0,0},
                   {1,0,0,0,0},
                   {1,0,0,0,0}};break;

    case 4://Древовидная структура
        _matrix = {{0,1,1,0,0},
                   {1,0,0,0,0},
                   {1,0,0,1,1},
                   {0,0,1,0,0},
                   {0,0,1,0,0}};break;

    case 5://Полный граф
        _matrix = {{0,1,1,1,1},
                   {1,0,1,1,1},
                   {1,1,0,1,1},
                   {1,1,1,0,1},
                   {1,1,1,1,0}}; break;

    case 6://Несвязный граф
        _matrix = {{0,1,0,0,0},
                   {1,0,0,0,0},
                   {0,0,0,1,1},
                   {0,0,1,0,0},
                   {0,0,1,0,0}};break;
    }
    return _matrix;
}

void ShowMatrixToMonitor(const matrix<int>& a) noexcept
{
    for(unsigned int row =0;row<a.size();row++)
    {
        for(unsigned int cell =0;cell<a[row].size();cell++)
            cout<<setw(3)<<a[row][cell];
        cout<<endl;
    }

}
