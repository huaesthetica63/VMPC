#ifndef VMPC_h
#define VMPC_h
#include <iostream>
#include <fstream>
#include <chrono>//замеры времени
#include <vector>
//прототипы используемых функций
long long getSizeFile(char*filename);//размер файла в байтах
bool VMPC(char*filename1,char*filename2,char*key);//сам алгоритм шифрования
void printBinaryFile(char*filename);//печать бинарного файла в виде нулей и единиц (для отладки)
void generateKey(char*filename, long long size);//генерация рандомного ключа заданного размера
#endif
