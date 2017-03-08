#include<vector>

/* About
 * Здесь представлен наобор методов
 * для исследования храрактеристик
 * систем
 */

/* Alert!
 * Методы MxM и MplusM
 * Не переживут использования
 * несоразмерных матриц(векторов векторов)
 * Не рекомендуется испытывать судьбу
 */



namespace islMethods {

using namespace std;

////////////////////////////////////////////////////////////////

template<typename T>
using matrix = vector<vector<T>>;

////////////////////////////////////////////////////////////////

//Возвращает коофициент связности по матрице смежности
double Svaznost(const matrix<int>&);

//Возвращает коофициент избыточности по матрице смежности
double Izbitochnost(const matrix<int>&);

//возвращает равномерность распределения связей по матрице смежности
//или недоиспользование структуры при достижении максимальной связности
double Ravnomernost(const matrix<int>&);

//Вычисляет диаметр структуры (х-ка относиться с структурной компактности)
double DiamStruct(const matrix<int>&);

//возвращает структурную компактность относительную (близость элементов между собой)
double StructCompactOtn(const matrix<int>&);

//Степень централизации в структуре
double StepenCentr(const matrix<int>&);

//Расм. рерсурсы в системе в порядке их значимости
double RangSyst(const matrix<int>&);

//Умножает одну матрицу на другую
matrix<int> MxM(const matrix<int>&,const matrix<int>&);

//складывает одну матрицу с другой
matrix<int> MplusM(const matrix<int>&, const matrix<int>&);

}



