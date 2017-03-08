#include <iostream>
#include <methods.h>
#include <iomanip>

using namespace std;

template<typename T>
using matrix = vector<vector<T>>;

matrix<int> GetSomeMatrixByIndex(const unsigned short int);     //выдает тестовую матрицу смежности графа (1-6)
void ShowMatrixToMonitor(const matrix<int>&) noexcept;          //выводит матрицу на экран
void AnalysSystem(const matrix<int>& m);                        //выполняет анализ системы по матрице смежности

int main()
{

    matrix<int> m = GetSomeMatrixByIndex(6);
    cout<<endl;

    AnalysSystem(m);
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
    cout<<endl;
    for(unsigned int row =0;row<a.size();row++)
    {
        for(unsigned int cell =0;cell<a[row].size();cell++)
            cout<<setw(3)<<a[row][cell];
        cout<<endl;
    }

}

void AnalysSystem(const matrix<int>& m)
{
    using namespace islMethods;

    unsigned int N = m.size();      //количество вершин

    double ks = Svaznost(m);        //Коофициент связности
    double R = Izbitochnost(m);     //Коофициент ихбыточности
    bool ksb = (ks>=N-1);           //показатель связности

    cout<<"Sistema:"<<endl;
    ShowMatrixToMonitor(m);
    cout<<"H-ki sistemy"<<endl;

    cout<<"Kooficient svyaznosti K = "<<ks<<'.'<<endl;
    cout<<"Struktura "<<((ksb)?"svyaznaya":"ne svyaznaya")<<'.'<<endl<<endl;

    cout<<"Kooficient izbytochnosti R = "<<R<<'.'<<endl;
    if(R==0)
        cout<<"Struktura svyazno-minimal'na"<<'.'<<endl;

    if(R<0)
        cout<<"Struktura svyazno-izbytochna"<<'.'<<endl;
    cout<<endl;

    if(ksb)
    {
        double sko = 0;            //Равномерность распределения связей
        double diamStr = 0;        //Диаметр структуры
        double structCompact = 0;  //Структурная компактность(относительная)
        double stepCentr = 0;      //Степень централизации
        vector<double> rank3;      //ранги элементов длинной 3
        vector<double> rank4;      //ранги элементов длинной 4

        sko = Ravnomernost(m);
        cout<<"Kvadratnoe otklonenie zadannogo raspredeleniya stepeni vershin E^2 = "<<sko<<'.'<<endl;
        cout<<"Struktura "<<((sko==0)?"ravnomernaya":"neravnomernaya")<<'.'<<endl<<endl;

        diamStr = DiamStruct(m);
        structCompact = StructCompactOtn(m);
        cout<<"Diametr struktury = "<<diamStr<<'.'<<endl;
        cout<<"Qotn = "<<structCompact<<'.'<<endl;

        if((structCompact>=0) & (structCompact<=1))
            cout<<"0 <= Qotn <= 1"<<endl;
        if(structCompact==0)
            cout<<"Struktura kompaktnaya."<<endl;
        if(structCompact==1)
            cout<<"Struktura nekompaktnaya."<<endl;
        cout<<endl;

        stepCentr = StepenCentr(m);
        cout<<"Indeks centralizacii b = "<<stepCentr<<'.'<<endl;

        rank3 = RangElements3(m);
        cout<<"Rangi elementov dlya k=3:"<<endl;
        for(unsigned int i = 0;i<rank3.size();i++)
            cout<<setw(4)<<rank3[i]<<'|';
        cout<<endl<<endl;


        rank4 = RangElements4(m);
        cout<<"Rangi elementov dlya k=4:"<<endl;
        for(unsigned int i = 0;i<rank4.size();i++)
            cout<<setw(4)<<rank4[i]<<'|';
        cout<<endl<<endl;

    }

}
