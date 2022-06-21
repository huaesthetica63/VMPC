#include "VMPC.h"
using namespace std;
int main(){//главная функция с демонстрацией алгоритма шифрования и замерами времени
    srand(time(0));//инициализация рандомайзера
    long long sizeFile = getSizeFile((char*)"sample.pdf");//считываем размер исходного файла в байтах
    if(sizeFile==-1){
        cout<<"Error!"<<endl;
        return -1;
    }
    cout<<"Size of file: "<<sizeFile<<" bytes"<<endl;
    generateKey((char*)"key.bin", 256);//генерируем ключ длиной 256 байт
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    bool resOperation=VMPC((char*)"sample.pdf", (char*)"res.pdf", (char*)"key.bin");
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    if(resOperation)
        cout << "Time of encryption: " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " milliseconds" << endl;
    else{
        cout<<"Error!"<<endl;
        return -1;
    }
    begin = chrono::steady_clock::now();//отдельный замер времени для дешифрования
    resOperation=VMPC((char*)"res.pdf", (char*)"deciph_sample.pdf", (char*)"key.bin");
    end = chrono::steady_clock::now();
    if(resOperation)
        cout << "Time of decryption: " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " milliseconds" << endl;
    else{
        cout<<"Error!"<<endl;
        return -1;
    }
    return 0;
}
