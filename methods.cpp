#include <methods.h>
#include <vector>



namespace islMethods {

using namespace std;

////////////////////////////////////////////////////////////////

template<typename T>
using matrix = vector<vector<T>>;

using indexer = unsigned int;

////////////////////////////////////////////////////////////////


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


matrix<int> MplusM(const matrix<int> & a, const matrix<int> & b)
{
    matrix<int> rez;
    indexer N = a.size();


    rez.reserve(N);

    for(indexer row=0;row<N;row++)
    {
        rez[row].reserve(N);
        for(indexer cell=0;cell<N;cell++)
            rez[row][cell]=a[row][cell] + b[row][cell];
    }
    return rez;
}

matrix<int> MxM(const matrix<int> & a, const matrix<int> & b)
{
    indexer N = a.size();
    matrix<int> rez;
    rez.reserve(N);

    for(indexer row=0;row<a.size();row++)
        rez[row].reserve(N);

    //Спасибо MSDN
    for(indexer row=0;row<N;row++)
        for(indexer cell=0;cell<N;cell++)
            for(indexer inner = 0; inner<N-1;inner++)
                rez[row][cell]+=a[row][inner] + b[inner][cell];

    return rez;
}

}
