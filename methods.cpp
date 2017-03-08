#include <vector>   //модуль расширяемых массивов
#include <math.h> //модуль математических функций

namespace islMethods {

using namespace std;

////////////////////////////////////////////////////////////////

template<typename T>
using matrix = vector<vector<T>>;

using indexer = unsigned int;

//Возвращает все степени матрицы смежности
vector<matrix<int>> GetSteps(const matrix<int>&);

//структурная близость Q
int StructProximity(const matrix<int>&);

//Умножает одну матрицу на другую
matrix<int> MxM(const matrix<int>&,const matrix<int>&);

//складывает одну матрицу с другой
matrix<int> MplusM(const matrix<int>&, const matrix<int>&);

//Возвращает матрицы минимальных путей из I в J
matrix<int> minPaths(const matrix<int>& m);

//Ранги элементов системы с длинной N
//Расм. рерсурсы в системе в порядке их значимости
vector<double> RangElementsN(const matrix<int>&,const unsigned int);

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
        for(indexer cell=0;cell<N;cell++)
            qi[point] += m[point][cell];
    }

    //среднее квадрватичное отклонение
    double sko=0;
    for(indexer point =0; point<N;point++)
        sko+=pow((qi[point]-qsr),2);

    return sko;

}

double DiamStruct(const matrix<int>& m)
{

    indexer N = m.size();        //кол-во вершин
    matrix<int> D = minPaths(m); //Получение матрицы минимальных путей


    int diametr =0;             //диаметр структуры
    for(indexer pointI=0;pointI<N;pointI++)
        for(indexer pointJ=0;pointJ<N;pointJ++)
            if(diametr<D[pointI][pointJ]) diametr = D[pointI][pointJ];

    return diametr;
}

double StructCompactOtn(const matrix<int>& m)
{
    double Q_otn=0;             //Относительная структурная близость

    indexer N = m.size();       //кол-во вершин
    int Q = StructProximity(m); //структурная близость
    int Qmin = N*(N-1);         //Минимальная структурная близость

    Q_otn = static_cast<double>(Q)/static_cast<double>(Qmin)-1;

    return Q_otn;
}

double StepenCentr(const matrix<int>& m)
{

    indexer N = m.size();               //кол-во вершин
    auto matrixMinPaths = minPaths(m);  //матрица минимальных путей
    int Q = StructProximity(m);         //структурная близость
    vector<double> t(N);                //
    double indexCentr = 0;              //индекс централизации

    //Оценка централизации каждой точки
    for(indexer pointI=0;pointI<N;pointI++)
    {
        t[pointI]=0;
        for(indexer pointJ=0;pointJ<N;pointJ++)
            if(pointI!=pointJ)
                t[pointI]+=matrixMinPaths[pointI][pointJ];
        t[pointI] = static_cast<double>(1)/t[pointI] ;
        t[pointI]*=Q/2;
    }

    double tmax = 0;

    for(indexer point=0;point<N;point++)
        if(tmax<t[point]) tmax = t[point];

    indexCentr = (N-1)*(2*tmax-N)*(1/(tmax*(N-2)));
    return indexCentr;
}

vector<double> RangElements3(const matrix<int>& m)
{
    return RangElementsN(m,3);
}

vector<double> RangElements4(const matrix<int>& m)
{
    return RangElementsN(m,4);
}

////////////////////////////////////////////////////////////////

vector<double> RangElementsN(const matrix<int>& m,const unsigned int n)
{
    indexer N = m.size();          //кол-во вершин
    auto _matrix = GetSteps(m);    //Получение всех степеней

    vector<double> elementsRank(N);

    //elementsRank[i]=top/down;

    int down=0;
    for(indexer i=0; i<N;i++)
        for(indexer j=0; j<N;j++)
            down+=_matrix[n][i][j];


    for(indexer i=0;i<N;i++)
    {
        int top =0;
        for(indexer j=0;j<N;j++)
            top+=_matrix[n][i][j];

        elementsRank[i] = static_cast<double>(top)/down;
    }
    return elementsRank;
}

int StructProximity(const matrix<int>& m)
{
    //кол-во вершин
    indexer N = m.size();

    //Создание копии матрицы
    matrix<int> D = minPaths(m);

    int Q = 0;              //структурная близость
    for(indexer pointI=0;pointI<N;pointI++)
        for(indexer pointJ=0;pointJ<N;pointJ++)
            if(pointI!=pointJ) Q+=D[pointI][pointJ];

    return Q;
}

matrix<int> minPaths(const matrix<int>& m)
{
    //кол-во вершин
    indexer N = m.size();
    //Создание копии матрицы
    matrix<int> D(m);
    //Получение всех степеней этой матрицы
    vector<matrix<int>> PN = GetSteps(m);

    //Формирование матрицы минимальных путей
    for(indexer stepen=0;stepen<N;stepen++)
        for(indexer row=0;row<N;row++)
            for(indexer coll=0;coll<N;coll++)
                if((D[row][coll]==0)&(PN[stepen][row][coll]>0))
                    D[row][coll] = stepen+1;
    return D;
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

vector<matrix<int>> GetSteps(const matrix<int>& m)
{
    indexer N = m.size();

    vector<matrix<int>> rez;
    matrix<int> _step(m);

    for(indexer step = 0;step<N;step++)
    {
        rez.push_back(_step);
        _step = MxM(_step,m);
    }

    return rez;
}

}
