// *************************************************************************
// * (c) 2018 Alexander Pchelintsev, pchelintsev.an@yandex.ru              *
// * Программа вычисления начального условия и периода цикла по гармоникам *
// *************************************************************************

// The program for calculating the initial condition and cycle period from harmonics

#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

#include "maxima.h"

int main()
{
    ifstream commondata("input.txt"),      // Файл с общими входными данными - File with input data
             res_newton("res_newton.txt"); // Результаты метода Ньютона - Results of Newton's method
    if(!commondata || !res_newton)
    {
        cout << "Error opening input files" << endl;
        return 1;
    }

    int n,      // Порядок системы - Order of the system
        fpprec; // Количество знаков после запятой - A number of simbols after comma
    commondata >> n;
    commondata >> fpprec; commondata >> fpprec;
    commondata.close();

    int harmonics; // Число гармоник - Number of harmonics
    res_newton >> harmonics;

    ofstream mip("maxima_init_point.wxm"); // Файл с командами для Maxima - File with commands for Maxima
    mip << "/* [wxMaxima batch file version 1] [ DO NOT EDIT BY HAND! ]*/" << endl;
    mip << "/* [wxMaxima: input   start ] */" << endl;
    mip << "display2d:false$" << endl;
    //mip << "fpprec:" << fpprec << "$" << endl;

    string s;
    GetStringValue(res_newton, s); // Значение omega - Value of omega
    mip << "bfloat(2*%pi/abs(" << s << "));" << endl;
    stringstream fm("");
    for(int i = 1; i <= n; i++)
    {
        GetStringValue(res_newton, s);
        fm << s << endl;
    }
    fm.seekg(0);
    for(int i = 1; i <= n; i++)
    {
        fm >> s;
        mip << "bfloat(" << s;
        for(int j = 1; j <= harmonics; j++)
        {
            GetStringValue(res_newton, s);
            if(s[0] == '-')
                mip << s;
            else
                mip << "+" << s;
            GetStringValue(res_newton, s); // Пропускаем sin(0) - We pass sin(0)
        }
        mip << ");" << endl;
    }
    res_newton.close();
    //mip << "quit();" << endl;
    mip << "/* [wxMaxima: input   end   ] */" << endl;
    mip.close();

    // Запускаем Maxima - Running Maxima
    system("maxima < maxima_init_point.wxm > res_period_maxima.txt");

    // Файл с результатами вычислений в пакете Maxima
    // File with the results of calculations in the Maxima package
    fstream outm("res_period_maxima.txt");
    ofstream init_point("init_point.txt");
    ReadFromMaxima(outm, s);
    init_point << "T = " << s << endl;
    for(int i = 1; i <= n; i++)
    {
        ReadFromMaxima(outm, s);
        init_point << "x" << i << "(0) = " << s << endl;
    }
    outm.close();
    init_point.close();

    return 0;
}
