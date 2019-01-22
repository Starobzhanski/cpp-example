#include <iostream>
#include <string>

using namespace std;

class Adres {
    
    string ulica;
    int numer;
    
    public:
    Adres(){
        numer = 0;
    }
    
    Adres(string _ulica, int _numer) {
        ulica = _ulica;
        numer = _numer;
    }
    
    friend ostream & operator <<(ostream & out, const Adres & adres) {
        out << "Ulica: " << adres.ulica << " nr: " << adres.numer;
        return out;
    }
    
    string& pobierzUlica() {
        return ulica;
    }
    
    const string& pobierzUlica() const {
        return ulica;
    }
    
    int& pobierzNumer() {
        return numer;
    }
    
    const int & pobierzNumer() const {
        return numer;
    }
};

class Pojazd {
    Adres * adres;
    string numer;
    int rozmiar;
    
    public:
    Pojazd() {
        adres = 0;
        rozmiar = 0;
    }
    
    Pojazd(string _numer, Adres _adres) {
        adres = new Adres[1];
        adres[0] = _adres;
        numer = _numer;
        rozmiar = 1;
    }
    
    Pojazd(Pojazd & pojazd) {
        rozmiar = pojazd.rozmiar;
        adres = new Adres[rozmiar];
        numer = pojazd.numer;

        for(int i = 0; i < rozmiar; i++) {
            adres[i] = pojazd.adres[i];
        }
    }
    
    friend ostream & operator <<(ostream & out, const Pojazd & pojazd) {
        out << "Numer rejestracyjny: " << pojazd.numer << endl;
        for(int i = 0; i < pojazd.rozmiar; i++) {
            out << pojazd.adres[i] << endl;
        }
        return out;
    }
    
    Pojazd & operator = (const Pojazd & pojazd) {
        rozmiar = pojazd.rozmiar;
        adres = new Adres[rozmiar];
        numer = pojazd.numer;

        for(int i = 0; i < rozmiar; i++) {
            adres[i] = pojazd.adres[i];
        }

        return *this;
    }
    
    void dodaj(Adres _adres) {
        if(rozmiar == 0) {
            adres = new Adres[1];
            adres[0] = _adres;
        }   
        else {
            Adres * temp = new Adres[rozmiar];
            temp = adres;
            adres = new Adres[rozmiar+1];

        for(int i = 0; i < rozmiar; i++) {
            adres[i] = temp[i];
        }
        
        adres[rozmiar] = _adres;
        delete [] temp;
        }
        rozmiar++;
    }
    
    Adres operator [](int i) {
        if(i > rozmiar || i < 0) {
            string wyjatek = "Nieprawidlowy indeks";
        throw wyjatek;
        }
        return adres[i];
    }
    
    string & pobierzNumer(){
        return numer;
    }
    
    const string & pobierzNumer() const{
        return numer;
    }
    
    int & pobierzRozmiar(){
        return rozmiar;
    }
    
    const int & pobierzRozmiar() const{
        return rozmiar;
    }
    
    ~Pojazd() {
        delete [] adres;
    }
};


class Samochod : public Pojazd {
    string marka;
    float * przebieg;
    
    public:
    Samochod():Pojazd() {
        przebieg = new float(0);
    }
    
    Samochod(string _marka, float _przebieg, string _numer, Adres _adres):Pojazd(_numer, _adres){
        marka = _marka;
        przebieg = new float(_przebieg);
    };
    
    Samochod(Samochod & samochod):Pojazd(samochod) {
        marka = samochod.marka;
        przebieg = new float(*samochod.przebieg);   
    }
    
    Samochod & operator=(const Samochod & samochod) {
        Pojazd::operator=(samochod);
        marka = samochod.marka;
        przebieg = new float(*samochod.przebieg);
        return *this;
    }
    
    friend ostream & operator <<(ostream & out, Samochod & samochod) {
        out << (Pojazd)samochod;
        out << "Marka: " << samochod.marka << endl;
        out << "Przebieg: " << *samochod.przebieg << endl;
        return out;
    }
    
    Samochod operator + (float _przebieg) {
        przebieg[0] = przebieg[0] + _przebieg;
        return *this;
    }
    
    ~Samochod() {
        delete przebieg;
    }
};

int main()
{
    Adres adres[] = {
        Adres("Dabrowskiego", 69),
        Adres("Jana Pawla II", 100)
    };
    
    cout<<"---- 1 ----"<<endl;
    cout<<adres[0]<<endl<<adres[1]<<endl;
    
    cout<<"---- 2 ----"<<endl;
    Pojazd p1("SC 12345", adres[0]);
    cout<<p1<<endl;
    
    cout<<"---- 3 ----"<<endl;
    p1.dodaj(adres[1]);
    cout<<p1<<endl;
    p1.dodaj(adres[1]);
    cout<<p1<<endl;
    
    cout<<"---- 4 ----"<<endl;
    Pojazd p2(p1);
    cout<<p2<<endl;
    
    cout<<"---- 5 ----"<<endl;
    cout<<p1<<endl;
    
    cout<<"---- 6 ----"<<endl;
    Pojazd p3;
    {
        Pojazd p4(p1);
        p3 = p4;
    }
    cout<<p3<<endl;
    
    cout<<"---- 7 ----"<<endl;
    try{
        cout<<p3[10]<<endl;
    }
    catch(...){
        cout<<"Wyjatek"<<endl;
    }
    
    cout<<"---- 8 ----"<<endl;
    Samochod s1("VW", 100000, "SC 12345", adres[0]);
    cout<<s1<<endl;
    
    cout<<"---- 9 ----"<<endl;
    s1.dodaj(adres[1]);
    cout<<s1<<endl;
    
    {
        cout<<"---- 10 ----"<<endl;
        Samochod s2(s1);
        cout<<s2<<endl;
    }
    
    cout<<"---- 11 ----"<<endl;
    cout<<s1<<endl;
    
    cout<<"---- 12 ----"<<endl;
    Samochod s3;
    {
        Samochod s4(s1);
        s4 = s3;
    }
    cout<<s3<<endl;
    
    cout<<"---- 13 ----"<<endl;
    s3 = s3 + 10000;
    cout<<s3<<endl;
    
    return 0;
}