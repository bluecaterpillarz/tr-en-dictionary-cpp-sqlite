#include "MyDictionary.h"

MyDictionary::MyDictionary()
{
    gelen_p       = &gelen;
    donustur_p    = &donustur;
    donustur_tr_p = &donustur_tr;
    donustur_en_p = &donustur_en;
    ilkiki_p      = &ilkiki;
    goster_p      = &goster;
    secilen_p     = &secilen;

    if (sqlite3_open("veritabani.db", &veritabani) != SQLITE_OK)
    {
        std::cerr << "Dosya acilamadi!" << std::endl;
        throw std::runtime_error("Dosya acilamadi!");
    }
}

MyDictionary::~MyDictionary()
{
    if (veritabani != nullptr)
    {
        sqlite3_close(veritabani);
        std::cout << "Veritabani baglantisi kapatildi." << std::endl;
    }
}

void MyDictionary::tr_en()
{
    veriler.clear();
    std::cout << "TR:";
    std::cin >> *gelen_p;
    *ilkiki_p = gelen_p->substr(0, 2);
    std::string selectSQL = "SELECT * FROM kelimeler WHERE tr LIKE '" + (*ilkiki_p) + "%';";
    sqlite3_stmt* listele;

    if (sqlite3_prepare_v2(veritabani, selectSQL.c_str(), -1, &listele, NULL) != SQLITE_OK)
    {
        std::cerr << "Sorgu hazirlanamadi: " << sqlite3_errmsg(veritabani) << std::endl;
        sqlite3_finalize(listele);
        sqlite3_close(veritabani);
        return;
    }
    else
    {
        int sayac = 0;
        int* sayac_p = &sayac;
        while (sqlite3_step(listele) == SQLITE_ROW)
        {
            turkce          = sqlite3_column_text(listele, 1);
            ingilizce       = sqlite3_column_text(listele, 2);
            turkce_cumle    = sqlite3_column_text(listele, 3);
            ingilizce_cumle = sqlite3_column_text(listele, 4);

            if (turkce_cumle == nullptr || strlen(reinterpret_cast<const char*>(turkce_cumle)) == 0)
                turkce_cumle = reinterpret_cast<const unsigned char*>("türkçe cümlesi yok");
            if (ingilizce_cumle == nullptr || strlen(reinterpret_cast<const char*>(ingilizce_cumle)) == 0)
                ingilizce_cumle = reinterpret_cast<const unsigned char*>("ingilizce cümlesi yok");
            if (turkce == nullptr || strlen(reinterpret_cast<const char*>(turkce)) == 0)
                turkce = reinterpret_cast<const unsigned char*>("türkçe kelimesi yok");
            if (ingilizce == nullptr || strlen(reinterpret_cast<const char*>(ingilizce)) == 0)
                ingilizce = reinterpret_cast<const unsigned char*>("ingilizce kelimesi yok");

            *donustur_p    = reinterpret_cast<const char*>(turkce);
            *donustur_tr_p = reinterpret_cast<const char*>(turkce_cumle);
            *donustur_en_p = reinterpret_cast<const char*>(ingilizce_cumle);

            std::cout << turkce << " " << *sayac_p << " ->Bunu mu demek istedin? \n";
            veriler.push_back({std::to_string(*sayac_p), *donustur_p, *donustur_tr_p, *donustur_en_p});
            *sayac_p = (*sayac_p) + 1;
        }

        std::cout << "Seçiminizi yapınız:";
        std::cin >> *gelen_p;

        if (veriler.at(std::stoi(*gelen_p)).at(0) == (*gelen_p))
        {
            std::cout << veriler.at(std::stoi(*gelen_p)).at(1) << std::endl;
            std::cout << veriler.at(std::stoi(*gelen_p)).at(2) << std::endl;
            std::cout << veriler.at(std::stoi(*gelen_p)).at(3) << std::endl;

            std::cout << "Bu kelimeyi öğrendiniz mi? Silmek için 1, devam için 0: ";
            int silme;
            int* silme_p = &silme;
            std::cin >> *silme_p;
            if (*silme_p == 1)
            {
                std::string silSQL = "DELETE FROM kelimeler WHERE tr = '" + veriler.at(std::stoi(*gelen_p)).at(1) + "';";
                char* hatamesaji;
                if (sqlite3_exec(veritabani, silSQL.c_str(), NULL, NULL, &hatamesaji) != SQLITE_OK)
                {
                    std::cerr << "Silme hatasi: " << hatamesaji << std::endl;
                    sqlite3_free(hatamesaji);
                }
                else
                    std::cout << "Kelime başarıyla silindi!" << std::endl;
            }
        }
    }
    sqlite3_reset(listele);
}

void MyDictionary::en_tr()
{
    veriler.clear();
    std::cout << "En:";
    std::cin >> *gelen_p;
    *ilkiki_p = gelen_p->substr(0, 2);
    std::string selectSQL = "SELECT * FROM kelimeler WHERE en LIKE '" + (*ilkiki_p) + "%';";
    sqlite3_stmt* listele;

    if (sqlite3_prepare_v2(veritabani, selectSQL.c_str(), -1, &listele, NULL) != SQLITE_OK)
    {
        std::cerr << "Sorgu hazirlanamadi: " << sqlite3_errmsg(veritabani) << std::endl;
        sqlite3_finalize(listele);
        sqlite3_close(veritabani);
        return;
    }
    else
    {
        int sayac = 0;
        int* sayac_p = &sayac;
        while (sqlite3_step(listele) == SQLITE_ROW)
        {
            turkce          = sqlite3_column_text(listele, 1);
            ingilizce       = sqlite3_column_text(listele, 2);
            turkce_cumle    = sqlite3_column_text(listele, 3);
            ingilizce_cumle = sqlite3_column_text(listele, 4);

            if (turkce_cumle == nullptr || strlen(reinterpret_cast<const char*>(turkce_cumle)) == 0)
                turkce_cumle = reinterpret_cast<const unsigned char*>("türkçe cümlesi yok");
            if (ingilizce_cumle == nullptr || strlen(reinterpret_cast<const char*>(ingilizce_cumle)) == 0)
                ingilizce_cumle = reinterpret_cast<const unsigned char*>("ingilizce cümlesi yok");
            if (turkce == nullptr || strlen(reinterpret_cast<const char*>(turkce)) == 0)
                turkce = reinterpret_cast<const unsigned char*>("türkçe kelimesi yok");
            if (ingilizce == nullptr || strlen(reinterpret_cast<const char*>(ingilizce)) == 0)
                ingilizce = reinterpret_cast<const unsigned char*>("ingilizce kelimesi yok");

            *donustur_p    = reinterpret_cast<const char*>(ingilizce);
            *donustur_tr_p = reinterpret_cast<const char*>(turkce_cumle);
            *donustur_en_p = reinterpret_cast<const char*>(ingilizce_cumle);

            std::cout << ingilizce << " " << *sayac_p << " ->Bunu mu demek istedin? \n";
            veriler.push_back({std::to_string(*sayac_p), *donustur_p, *donustur_tr_p, *donustur_en_p});
            *sayac_p = (*sayac_p) + 1;
        }

        std::cout << "Seçiminizi yapınız:";
        std::cin >> *gelen_p;

        if (veriler.at(std::stoi(*gelen_p)).at(0) == (*gelen_p))
        {
            std::cout << veriler.at(std::stoi(*gelen_p)).at(1) << std::endl;
            std::cout << veriler.at(std::stoi(*gelen_p)).at(2) << std::endl;
            std::cout << veriler.at(std::stoi(*gelen_p)).at(3) << std::endl;

            std::cout << "Bu kelimeyi öğrendiniz mi? Silmek için 1, devam için 0: ";
            int silme;
            int* silme_p = &silme;
            std::cin >> *silme_p;
            if (*silme_p == 1)
            {
                std::string silSQL = "DELETE FROM kelimeler WHERE en = '" + veriler.at(std::stoi(*gelen_p)).at(1) + "';";
                char* hatamesaji;
                if (sqlite3_exec(veritabani, silSQL.c_str(), NULL, NULL, &hatamesaji) != SQLITE_OK)
                {
                    std::cerr << "Silme hatasi: " << hatamesaji << std::endl;
                    sqlite3_free(hatamesaji);
                }
                else
                    std::cout << "Kelime başarıyla silindi!" << std::endl;
            }
        }
        sqlite3_reset(listele);
    }
}

void MyDictionary::secim()
{
    int secim1;
    int* secim1_p = &secim1;
    std::cout << "Turkce-İngilizce sözlük için 1, İngilizce-Türkçe sözlük için 2 giriniz: ";
    std::cin >> *secim1_p;
    if (*secim1_p == 1)
        tr_en();
    else if (*secim1_p == 2)
        en_tr();
    else
    {
        std::cout << "Yanlış seçim yaptınız\n";
        secim();
    }
}

std::vector<std::string> MyDictionary::secim2()
{
    std::string countSQL = "SELECT COUNT(*) FROM kelimeler;";
    sqlite3_stmt* stmt;
    int toplam = 0;

    if (sqlite3_prepare_v2(veritabani, countSQL.c_str(), -1, &stmt, NULL) == SQLITE_OK)
        if (sqlite3_step(stmt) == SQLITE_ROW)
            toplam = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);

    int randomID = (rand() % toplam) + 1;

    std::string secSQL = "SELECT tr, en FROM kelimeler WHERE id=" + std::to_string(randomID) + ";";
    sqlite3_stmt* stmt2;
    std::vector<std::string> sonuc = {"", ""};

    if (sqlite3_prepare_v2(veritabani, secSQL.c_str(), -1, &stmt2, NULL) == SQLITE_OK)
    {
        if (sqlite3_step(stmt2) == SQLITE_ROW)
        {
            const unsigned char* tr_kelime = sqlite3_column_text(stmt2, 0);
            const unsigned char* en_kelime = sqlite3_column_text(stmt2, 1);
            if (tr_kelime != nullptr) sonuc.at(0) = reinterpret_cast<const char*>(tr_kelime);
            if (en_kelime != nullptr) sonuc.at(1) = reinterpret_cast<const char*>(en_kelime);
        }
    }
    sqlite3_finalize(stmt2);

    return sonuc;
}

void MyDictionary::word_of_day()
{
    std::ifstream dosya_oku(dosya_adi);
    std::vector<std::string> veriler2;

    if (dosya_oku.is_open())
    {
        std::string veri_dos;
        while (getline(dosya_oku, veri_dos, ','))
        {
            if (!veri_dos.empty())
                veriler2.push_back(veri_dos);
        }
        dosya_oku.close();
    }

    *goster_p = 1;

    while (*goster_p)
    {
        *secilen_p = MyDictionary::secim2();

        bool zaten_gosterildi = false;
        for (int i = 0; i < (int)veriler2.size(); i++)
        {
            if ((*secilen_p).at(0) == veriler2.at(i))
            {
                zaten_gosterildi = true;
                break;
            }
        }

        if (!zaten_gosterildi)
        {
            std::cout << "Günün kelimesi: " << secilen_p->at(1) << " = " << secilen_p->at(0) << std::endl;

            std::ofstream dosya_yaz(dosya_adi, std::ios::app);
            if (dosya_yaz.is_open())
            {
                dosya_yaz << secilen_p->at(0) << ",";
                dosya_yaz.close();
            }
            else
                std::cerr << "CSV dosyasına yazılamadı!" << std::endl;

            *goster_p = 0;
        }
    }
}
