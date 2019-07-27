// ***************************************************************************
// * (c) 2019 Alexander Pchelintsev, pchelintsev.an@yandex.ru                *
// * Программа формирования системы уравнений относительно амплитуд гармоник *
// ***************************************************************************

// Program for the formation of a system of equations for the amplitudes of harmonics

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Функция std::to_string() описана в стандарте C++ 11,
// поэтому программа компилируется с опцией -std=gnu++11

// Выражение для суммы в свободном члене
inline string add0(int m, int num_func)
{
    string mm = to_string(m), nf = to_string(num_func);
    string res = "c1c" + mm + "*c" + nf + "c" + mm + "+s1c" + mm +
                 "*s" + nf + "c" + mm;
    return res;
}

// Выражение для слагаемых до суммы произведений в cos
inline string cos_add0(int i, int num_func)
{
    string ii = to_string(i), nf = to_string(num_func);
    string res = "x10*c" + nf + "c" + ii + "+c1c" + ii + "*x" + nf + "0";
    return res;
}

// Выражение для первого суммирования в cos
inline string cos_add1(int i, int m, int num_func)
{
    string ii = to_string(i), mm = to_string(m), mi = to_string(m+i),
           nf = to_string(num_func);
    string res = "c1c" + mm + "*c" + nf + "c" + mi + "+s1c" + mm +
                 "*s" + nf + "c" + mi;
    return res;
}

// Выражение для второго суммирования в cos
inline string cos_add2(int i, int m, int num_func)
{
    string ii = to_string(i), mm = to_string(m), mi = to_string(i-m),
           nf = to_string(num_func);
    string res = "c1c" + mm + "*c" + nf + "c" + mi + "-s1c" + mm +
                 "*s" + nf + "c" + mi;
    return res;
}

// Выражение для третьего суммирования в cos
inline string cos_add3(int i, int m, int num_func)
{
    string ii = to_string(i), mm = to_string(m), mi = to_string(m-i),
           nf = to_string(num_func);
    string res = "c1c" + mm + "*c" + nf + "c" + mi + "+s1c" + mm +
                 "*s" + nf + "c" + mi;
    return res;
}

// Выражение для слагаемых до суммы произведений в sin
inline string sin_add0(int i, int num_func)
{
    string ii = to_string(i), nf = to_string(num_func);
    string res = "x10*s" + nf + "c" + ii + "+s1c" + ii + "*x" + nf + "0";
    return res;
}

// Выражение для первого суммирования в sin
inline string sin_add1(int i, int m, int num_func)
{
    string ii = to_string(i), mm = to_string(m), mi = to_string(m+i),
           nf = to_string(num_func);
    string res = "c1c" + mm + "*s" + nf + "c" + mi + "-s1c" + mm +
                 "*c" + nf + "c" + mi;
    return res;
}

// Выражение для второго суммирования в sin
inline string sin_add2(int i, int m, int num_func)
{
    string ii = to_string(i), mm = to_string(m), mi = to_string(i-m),
           nf = to_string(num_func);
    string res = "c1c" + mm + "*s" + nf + "c" + mi + "+s1c" + mm +
                 "*c" + nf + "c" + mi;
    return res;
}

// Выражение для третьего суммирования в sin
inline string sin_add3(int i, int m, int num_func)
{
    string ii = to_string(i), mm = to_string(m), mi = to_string(m-i),
           nf = to_string(num_func);
    string res = "-c1c" + mm + "*s" + nf + "c" + mi + "+s1c" + mm +
                 "*c" + nf + "c" + mi;
    return res;
}

// Создание сумм произведений для cos
void create_cos_sums(ofstream &newton, int i, int harmonics, int num_func)
{
    // Первая сумма
    // The first sum
    string sum = "";
    bool flag_plus = true;
    for(int m = 1; m <= harmonics - i; m++)
    {
        if(!flag_plus)
            sum += "+";
        else
            flag_plus = false;
        sum += cos_add1(i, m, num_func);
    }
    if(sum != "")
        sum = "+(" + sum + ")/2";
    newton << sum;

    // Вторая сумма
    // The second sum
    sum = "";
    flag_plus = true;
    for(int m = 1; m <= i - 1; m++)
    {
        if(!flag_plus)
            sum += "+";
        else
            flag_plus = false;
        sum += cos_add2(i, m, num_func);
    }
    if(sum != "")
        sum = "+(" + sum + ")/2";
    newton << sum;

    // Третья сумма
    // The third sum
    sum = "";
    flag_plus = true;
    for(int m = i + 1; m <= harmonics; m++)
    {
        if(!flag_plus)
            sum += "+";
        else
            flag_plus = false;
        sum += cos_add3(i, m, num_func);
    }
    if(sum != "")
        sum = "+(" + sum + ")/2";
    newton << sum;
}

// Создание сумм произведений для sin
void create_sin_sums(ofstream &newton, int i, int harmonics, int num_func)
{
    // Первая сумма
    // The first sum
    string sum = "";
    bool flag_plus = true;
    for(int m = 1; m <= harmonics - i; m++)
    {
        if(!flag_plus)
            sum += "+";
        else
            flag_plus = false;
        sum += sin_add1(i, m, num_func);
    }
    if(sum != "")
        sum = "+(" + sum + ")/2";
    newton << sum;

    // Вторая сумма
    // The second sum
    sum = "";
    flag_plus = true;
    for(int m = 1; m <= i - 1; m++)
    {
        if(!flag_plus)
            sum += "+";
        else
            flag_plus = false;
        sum += sin_add2(i, m, num_func);
    }
    if(sum != "")
        sum = "+(" + sum + ")/2";
    newton << sum;

    // Третья сумма
    // The third sum
    sum = "";
    flag_plus = true;
    for(int m = i + 1; m <= harmonics; m++)
    {
        if(!flag_plus)
            sum += "+";
        else
            flag_plus = false;
        sum += sin_add3(i, m, num_func);
    }
    if(sum != "")
        sum = "+(" + sum + ")/2";
    newton << sum;
}

// Создание свободного члена в нелинейной части
void create_constant_term(ofstream &newton, int harmonics, int num_func)
{
    string sum = "";
    bool flag_plus = true;
    for(int m = 1; m <= harmonics; m++)
    {
        if(!flag_plus)
                sum += "+";
            else
                flag_plus = false;
        sum += add0(m, num_func);
    }
    if(sum != "")
        sum = "+(" + sum + ")/2";
    newton << sum;
}

int main()
{
    ifstream commondata("input.txt"), // Файл с общими входными данными - File with input data
             // Файл с правой частью системы диф. уравнений
             // The file with the right-hand side of the system of differential equations
             systema("system.txt");
    if(!systema || !commondata)
    {
        cout << "Error opening input files" << endl;
        return 1;
    }

    // Порядок системы и количество гармоник - The order of the system and the number of harmonics
    int n, harmonics,
        // Количество знаков после запятой - A number of simbols after comma
        fpprec,
        // Номер координаты для доп. уравнения - No. coordinate for the additional equation
        add_eq;
    string x0_eq;  // Начальное значение этой координаты - The initial value of this coordinate
    string omega0, // Начальное приближение по частоте - Initial frequency approximation
           // Начальное приближение по свободному члену - The initial approximation by the free term
           x00,
           // Начальное приближение по косинусам (по синусам берётся 0)
           // The initial approximation by cos (by sin is taken 0)
           c0;
    commondata >> n >> harmonics >> fpprec >> add_eq >> x0_eq >> omega0 >> x00 >> c0;
    commondata.close();

    // Файл с командой метода Ньютона - File with a command for Newton's method
    ofstream newton("newton.wxm");
    newton << "/* [wxMaxima batch file version 1] [ DO NOT EDIT BY HAND! ]*/" << endl;
    newton << "/* [wxMaxima: input   start ] */" << endl;
    newton << "display2d:false$" << endl;
    newton << "load(mnewton);" << endl;
    //newton << "(fpprec:" << fpprec << ",newtonepsilon:bfloat(10^(-fpprec+5)))$" << endl;
    newton << "mnewton(" << endl << "[" << endl;

    // === Линейные уравнения, соответствующие первому уравнению системы          ===
    // === The linear equations corresponding to the first equation of the system ===
    for(int i = 1; i <= harmonics; i++)
    {
        // = cos =
        newton << i << "*omega*s1c" << i << "-10*c2c" << i << "+10*c1c" << i << "," << endl;
        // = sin =
        newton << "-" << i << "*omega*c1c" << i << "-10*s2c" << i << "+10*s1c" << i << "," << endl;
    }
    // Свободный член
    // The constant term
    newton << "x10-x20," << endl;

    // === Уравнения, соответствующие второму уравнению системы             ===
    // === The equations corresponding to the second equation of the system ===
    for(int i = 1; i <= harmonics; i++)
    {
        // = cos =
        newton << i << "*omega*s2c" << i << "-28*c1c" << i << "+c2c" << i << "+" <<
                  cos_add0(i, 3);
        create_cos_sums(newton, i, harmonics, 3);
        newton << "," << endl;

        // = sin =
        newton << "-" << i << "*omega*c2c" << i << "-28*s1c" << i << "+s2c" << i << "+" <<
                  sin_add0(i, 3);
        create_sin_sums(newton, i, harmonics, 3);
        newton << "," << endl;
    }

    // Свободный член
    // The constant term
    newton << "-28*x10+x20+x10*x30";
    create_constant_term(newton, harmonics, 3);
    newton << "," << endl;

    // === Уравнения, соответствующие третьему уравнению системы           ===
    // === The equations corresponding to the third equation of the system ===
    for(int i = 1; i <= harmonics; i++)
    {
        // = cos =
        newton << i << "*omega*s3c" << i << "-(" << cos_add0(i, 2) << ")-(0";
        create_cos_sums(newton, i, harmonics, 2);
        newton << ")+8*c3c" << i << "/3," << endl;

        // = sin =
        newton << "-" << i << "*omega*c3c" << i << "-(" << sin_add0(i, 2) << ")-(0";
        create_sin_sums(newton, i, harmonics, 2);
        newton << ")+8*s3c" << i << "/3," << endl;
    }

    // Свободный член
    // The constant term
    newton << "-x10*x20-(0";
    create_constant_term(newton, harmonics, 2);
    newton << ")+8*x30/3," << endl;

    // Формирование дополнительного уравнения
    // Formation of the additional equation
    newton << "x30";
    for(int j = 1; j <= harmonics; j++)
        newton << "+c3c" << j;
    newton << "-27" << endl << "]," << endl;

    // Вектор неизвестных
    // Vector of unknown values
    newton << "[" << endl << "omega,";
    for(int i = 1; i <= n; i++)
    {
        newton << "x" << i << "0";
        if(i != n)
            newton << ",";
    }
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= harmonics; j++)
        {
            newton << ",c" << i << "c" << j << ",s" << i << "c" << j;
        }
    }
    newton << endl << "]," << endl;

    // Вектор начального приближения
    // Vector of initial approximation (IA)
    newton << "[" << endl << omega0 << ",";
    for(int i = 1; i <= n; i++)
    {
        newton << x00;
        if(i != n)
            newton << ",";
    }
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= harmonics; j++)
            newton << "," << c0 << ",0";
    newton << endl << "]" << endl << ");" << endl;
    newton << "/* [wxMaxima: input   end   ] */" << endl;
    /* For 5 harmonics: IA = [4,0,0,0,-1,0,-1,1,-1,0,-1,0,-1,0,-1,0,-1,0,-1,0,-1,0,-1,0,-1,0,-1,0,-1,0,-1,0,-1,0]
[omega=3.984915779315225,x10=−1.0530902294367658*10^−19,x20=−1.0530881614852344*10^−19,x30=23.17484126777741,c1c1=−5.734428599745011,s1c1=
8.700967706873966,c1c2=−6.138093735449742*10^−19,s1c2=−7.067744448310073*10^−19,c1c3=3.162874335852722,s1c3=2.061936729442591,c1c4=−
8.508602085510066*10^−19,s1c4=4.919292733689609*10^−19,c1c5=0.52386925730496,s1c5=−0.691987635106,c2c1=−2.267166248701582,s2c1=10.986089208122,c2c2
=−1.210034334833143*10^−18,s2c2=−2.9446719908213977*10^−19,c2c3=5.627867598584344,s2c3=−1.719199625236611,c2c4=−1.5456862362288386*10^−19,s2c4=
1.8698140641255985*10^−18,c2c5=−0.85488696580749,s2c5=−1.735775069972356,c3c1=−3.7684198038323303*10^−19,s3c1=5.912538126018782*10^−19,c3c2=
7.278395231560696,s3c2=−9.743072005078493,c3c3=1.1948255852955899*10^−18,s3c3=1.5220247348067592*10^−18,c3c4=−3.453236499338109,s3c4=−
1.496599920543623,c3c5=9.631785144362132*10^−19,s3c5=−1.061004305796761*10^−18]
       For 7 harmonics: IA = [4,0,0,20,-1,0,-1,1,-1,0,-1,0,-1,0,-1,0,-1,0,-1,0,-1,0,-1,0,-1,0,-1,0,-1,0,-1,0,-1,0,-1,0,-1,0,-1,0,-1,0,-1,0,-1,0]
[omega=−0.50499913164936,x10=−0.12591118497178,x20=−0.12591118497178,x30=6.351312723306374,c1c1=−0.63358287581819,s1c1=−0.96474143360012,
c1c2=−1.613687597600364,s1c2=−1.292127576358392,c1c3=−2.531006135781585,s1c3=−0.76113476534085,c1c4=−2.79910058286447,s1c4=0.29972978587068,
c1c5=−2.27519767792234,s1c5=1.266756753142784,c1c6=−1.304351063058896,s1c6=1.650338518779572,c1c7=−0.43101000425598,s1c7=1.390751622311487,
c2c1=−0.58486351719477,s2c1=−0.99673731381173,c2c2=−1.483182936792127,s2c2=−1.455109743466699,c2c3=−2.415694417112003,s2c3=−1.144581535571526,
c2c4=−2.859645895502129,s2c4=−0.26568755962762,c2c5=−2.595053208096376,s2c5=0.69227032730206,c2c6=−1.804402774405604,s2c6=1.255120826253172,
c2c7=−0.92263985738105,s2c7=1.238389847794466,c3c1=9.871676062431936,s3c1=−5.90552333250201,c3c2=4.293390680874789,s3c2=−7.620230221468945,
c3c3=0.25968248546516,s3c3=−5.271869274314445,c3c4=−0.39820338303397,s3c4=−1.960253583055055,c3c5=1.113645482346556,s3c5=−0.27693782701403,
c3c6=2.632765660214796,s3c6=−0.66080016845029,c3c7=2.87573028839436,s3c7=−2.009322200735098]
    */
    newton.close();

    return 0;
}
