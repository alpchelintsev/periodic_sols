// ************************************************************
// * (c) 2018 Alexander Pchelintsev, pchelintsev.an@yandex.ru *
// *          Функции для работы с пакетом Maxima             *
// ************************************************************

// The functions for working with the Maxima package (a Computer Algebra System)

#ifndef _MAXIMA_H_INCLUDED_
#define _MAXIMA_H_INCLUDED_

#include <cstdio>
#include <fstream>
#include <string>

// Читает строковое значение переменной из текстового файла пакета Maxima после знака =
// The function reads the string value of variable from the Maxima package text file after =
void GetStringValue(std::ifstream &f, std::string &res);

// Читает результат выполнения команды пакета
// The function reads the result of execution of the package command
void ReadFromMaxima(std::fstream &f, std::string &res);

#endif //_MAXIMA_H_INCLUDED_
