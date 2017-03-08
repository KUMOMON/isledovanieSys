#include <vector>   //модуль расширяемых массивов
#include <math.h> //модуль математических функций



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
    indexer N = m.size();
    for(indexer row=0;row<N;row++)
        for(indexer cell=0;cell<N;cell++)
            rez+=m[row][cell];

    rez=(rez/(2*(N-1)))-1;
    return rez;
}

double Ravnomernost(const matrix<int> & m)
{
    //вершины
    indexer N = m.size();
    //ребра
    indexer M=0;

    //расчет количества дуг
    for(indexer row=0;row<N;row++)
        for(indexer cell = row;cell<N;cell++)
            M+=m[row][cell];
    //ро
    int qsr=2*M/N;

    //вектор с кол-вом дуг исхода(i - точка исхода)
    //инициализация вектора с размерностью N
    vector<int> qi(N);

    for(indexer point=0;point<N;point++)
    {
        qi[point] = 0;

        //проход по столбцам матрицы смежности
        //для опред. точки графа
        //для определения коли-ва дуг исхода
        for(int cell=0;cell<N;cell++)
            qi[point] += m[point][cell];
    }

    //среднее квадрватичное отклонение
    int sko=0;
    for(indexer point =0; point<N;point++)
        sko+=(qi[point]-qsr)(qi[point]);

    return sko;

}


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
