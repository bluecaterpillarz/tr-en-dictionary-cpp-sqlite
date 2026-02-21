#ifndef MYDICTIONARY_H
#define MYDICTIONARY_H

#include <iostream>
#include <sqlite3.h>
#include <string>
#include <windows.h>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>

class MyDictionary
{
private:
    sqlite3* veritabani;
    std::vector<std::vector<std::string>> veriler;
    std::vector<std::string> veriler2;
    std::string gelen;
    std::string* gelen_p;
    const unsigned char* turkce;
    const unsigned char* ingilizce;
    const unsigned char* turkce_cumle;
    const unsigned char* ingilizce_cumle;
    std::string donustur;
    std::string* donustur_p;
    std::string donustur_tr;
    std::string* donustur_tr_p;
    std::string donustur_en;
    std::string* donustur_en_p;
    std::string ilkiki;
    std::string* ilkiki_p;
    std::string dosya_adi="oncekiler.csv";
    int goster=1;
    int* goster_p=&goster;
    std::vector<std::string> secilen;
    std::vector<std::string>* secilen_p = &secilen;

public:
    MyDictionary();
    ~MyDictionary();
    void tr_en();
    void en_tr();
    void secim();
    std::vector<std::string> secim2();
    void word_of_day();
};

#endif // MYDICTIONARY_H
