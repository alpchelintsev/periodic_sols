// **************************************************************************************
// * (c) 2018 Alexander Pchelintsev, pchelintsev.an@yandex.ru                           *
// * Расширение начального приближения по результатам предыдущих вычислений             *
// * The expansion of the initial approximation on the results of previous calculations *
// **************************************************************************************

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "maxima.h"

int main()
{
    ifstream commondata("input.txt"), // Файл с общими входными данными - File with input data
             // Файл с командой для метода Ньютона - File with a command for Newton's method
             newton("newton.wxm"),
             // Результаты мет. Ньютона для меньшего числа гармоник
             // Results of Newton's method for a smaller number of harmonics
             res_prev_newton("res_newton.txt");
    if(!commondata || !newton || !res_prev_newton)
    {
        cout << "Error opening input files" << endl;
        return 1;
    }

    // Порядок системы и новое количество гармоник
    // The order of the system and the new number of harmonics
    int n, harmonics;
    commondata >> n >> harmonics;
    commondata.close();

    // Меньшее (предыдущее) число гармоник
    // The lower (previous) number of harmonics
    int prev_harmonics;
    res_prev_newton >> prev_harmonics;

    // Файл с новым начальным приближением для мет. Ньютона
    // File with a new initial approximation for Newton's method
    ofstream new_newton("new_newton.wxm");
    string s;
    // Копируем часть файла - We copy part of the file
    while(true)
    {
        getline(newton, s);
        new_newton << s << endl;
        if(!s.find("],"))
            break;
    }
    newton >> s; new_newton << s << endl; // [
    // Перечисление переменных начального приближения
    // Enumeration of initial approximation variables
    newton >> s; new_newton << s << endl;
    newton >> s; new_newton << s << endl; // ],
    newton >> s; new_newton << s << endl; // [
    newton.close();

    // Далее формируем строку со значением начального приближения
    // Next, we form a string with the value of the initial approximation
    GetStringValue(res_prev_newton, s); // Значение omega - Value of omega
    new_newton << s << ",";
    for(int i = 1; i <= n; i++)
    {
        GetStringValue(res_prev_newton, s);
        new_newton << s;
        if(i != n)
            new_newton << ",";
    }
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= prev_harmonics; j++)
        {
            GetStringValue(res_prev_newton, s);
            new_newton << "," << s;
            GetStringValue(res_prev_newton, s);
            new_newton << "," << s;
        }
        for(int j = prev_harmonics + 1; j <= harmonics; j++)
            new_newton << ",0,0";
    }
    res_prev_newton.close();
    new_newton << endl << "]" << endl << ");" << endl;
    new_newton << "/* [wxMaxima: input   end   ] */" << endl;
    new_newton.close();

    return 0;
}
