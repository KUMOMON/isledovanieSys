#include <methods.h>
#include <vector>

using namespace std;


template<typename T>
using matrix = vector<vector<T>>;

using indexer = unsigned int;

double Svaznost(const matrix<int>& m)
{
    double rez=0;
    for(indexer row=0;row<m.size();row++)
        for(indexer cell=0;cell<m[row].size();cell++)
            rez+=m[row][cell];
    rez/=2;
    return rez;
}

double Izbitochnost(const matrix<int>& m)
{
    double rez=0;
    for(indexer row=0;row<m.size();row++)
        for(indexer cell=0;cell<m[row].size();cell++)
            rez+=m[row][cell];

    rez/=(2*m.size()-2);
    return rez;
}

double Ravnomernost(const matrix<int> &);
//{
//    int VershinyCount = m.size();

//}


