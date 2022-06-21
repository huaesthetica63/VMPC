#include "VMPC.h"
using namespace std;
bool VMPC(char*filename1,char*filename2,char*key){//VMPC-поточный шифр, модификация RC4
    //так же состоит из инициализации s-блока и формирования псевдослучайного слова на каждый байт текста
    ifstream file(filename1, ios::binary|ios::in);//исходный файл
    ofstream cipherfile(filename2,ios::binary|ios::out);//шифротекст
    ifstream keyfile(key, ios::binary|ios::in);//файл с ключом
    if((!file.is_open())||(!cipherfile.is_open())||(!keyfile.is_open()))
        return false;
    vector<short>s(256);//s-блок
    for(int i=0; i<256;i++){
        s[i]=i;//начальная инициализация s-блока
    }
    int i, j=0;
    vector<short>keyarr(256);//массив ключа
    short keybyte;
    int ind=0;
    while(keyfile.read((char *)&keybyte,sizeof(short))&&ind<256){
        //считываем ключ в массив
        keyarr[ind++]=keybyte;
    }
    int p =0;
    for(i=0;i<767;i++)//тасуем s-блок (продолжение инициализации)
    {
        j=i % 256;//делим по модулю i на 256, чтобы не выходить за пределы массива
        p = s[(p+s[j]+keyarr[i % 256])%256];//получаем индекс элемента, который мы поменяем местами с j-тым
        swap(s[j],s[p]);//меняем местами два байта s-блока
    }
    i=j=0;
    short byte;//вторая часть алгоритма - формирование псевдослучайного слова для побайтного шифрования
    while(file.read((char *)&byte,sizeof(short))){
        p = s[(p+s[i])%256];//вспомогательный индекс для выбора байта - псевдослучайного слова
        short symb = s[(s[s[p]]+1)%256];//байт (псевдослучайное слово)
        swap(s[i],s[p]);//тасуем байты в s-блоке
        i = (i+1)%256;//делим на 256 по модулю, чтобы не выходить за границы массива
        short resbyte = symb^byte;//xor'им байт из s-блока с байтом исходного текста
        cipherfile.write((char *)&resbyte, sizeof(short));//результат записываем в шифротекст
    }
  
    file.close();
    cipherfile.close();
    keyfile.close();
    return true;
}
long long getSizeFile(char*filename){//вычисляем размер файла в байтах
    ifstream file(filename, ios::binary);
    file.seekg(0,file.end);//ставим файловый указатель в конец
    long long res = file.tellg();//считываем размер
    file.seekg(0,file.beg);//обратно ставим указатель в начало
    file.close();
    return res;
}
void printBinaryFile(char*filename){//печать бинарного файла в виде последовательности битов
    ifstream file(filename, ios::binary);
    short byte;
    while(file.read((char *)&byte,sizeof(short))){
        cout<<bitset<8>(byte)<<" ";
    }
    file.close();
}
void generateKey(char*filename, long long size){//генерация случайного ключа заданной длины
    ofstream keyfile(filename,ios::binary|ios::out);
    while(size>0){
        short byte = rand()%256;
        keyfile.write((char *)&byte, sizeof(short));
        size--;
    }
    keyfile.close();
}
