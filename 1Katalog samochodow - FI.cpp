#include<iostream>

using namespace std;

enum silnik{B,D,E,H};

class Samochod{
    string N_rejestracyjny_;
    int moc_;
    double waga_;
    silnik silnik_;
    int numer_;
     
    public:
        static int index_; 
    
        Samochod(){
            numer_ = index_++;
        }
        Samochod(string,int,double,silnik);
    
        int mocSamochod(){
            return moc_;
        }
        double wagaSamochod(){
            return  waga_;
        }
        string rejestracjaSamochodu(){
            return N_rejestracyjny_;
        }
        int indexSamochod(){
            return numer_;
        }
    
    
};
int Samochod::index_= 0;

Samochod::Samochod(string N_rejestracyjny,int moc,double waga,silnik silnik):
N_rejestracyjny_(N_rejestracyjny),moc_(moc),waga_(waga),silnik_(silnik){
}

class Katalog{
    public:
        static const int kmax_ = 1000;
        void insert(Samochod);
        void wyswietlanie();
        void usun(Samochod);
    
    private:
        int rkopca_;
        Samochod kopiec_[kmax_+1];
        int mindziecko(int);
        void usuwaniemin();
        Samochod zwrocmin(){
            return kopiec_[1];
        }
        public:
            Katalog(){rkopca_ = 0;}

};
void Katalog::usun(Samochod element){
    for(int i=1;i<=rkopca_;i++){
        if(element.indexSamochod() == kopiec_[i].indexSamochod() ){
            Samochod ostatniSamochod = kopiec_[rkopca_--];
            int y = mindziecko(i);
            while(y and kopiec_[y].mocSamochod() < ostatniSamochod.mocSamochod() ){
            kopiec_[i] = kopiec_[y];
            i=y;
            y= mindziecko(y);
    }
    kopiec_[i] = ostatniSamochod;
    break;
    }
    }
}


void Katalog::usuwaniemin(){
    Samochod ostatniSamochod = kopiec_[rkopca_--];
    int i = 1; 
    int y = mindziecko(1);
    while(y and (kopiec_[y].mocSamochod() < ostatniSamochod.mocSamochod()) 
		or (kopiec_[y].mocSamochod() == ostatniSamochod.mocSamochod() 
	and kopiec_[y].wagaSamochod() < ostatniSamochod.wagaSamochod() )){
        kopiec_[i] = kopiec_[y];
        i=y;
        y= mindziecko(y);
    }
    kopiec_[i] = ostatniSamochod;
    
}

int Katalog::mindziecko(int rodzic){
    int lewy = rodzic*2;
    int prawy = lewy+1;
    if(lewy > rkopca_)return 0;
    if (prawy > rkopca_ or kopiec_[lewy].mocSamochod() < kopiec_[prawy].mocSamochod() or (kopiec_[lewy].mocSamochod() == kopiec_[prawy].mocSamochod() 
and kopiec_[lewy].wagaSamochod() == kopiec_[prawy].wagaSamochod()))return lewy;
    return prawy;
    
}

void Katalog::insert(Samochod tenSamochod){
    int dziecko = ++rkopca_;
    int rodzic = dziecko/2;
    
    while(rodzic and (tenSamochod.mocSamochod() < kopiec_[rodzic].mocSamochod() or (tenSamochod.mocSamochod() == kopiec_[rodzic].mocSamochod() and tenSamochod.wagaSamochod() < kopiec_[rodzic].wagaSamochod() ))){
        kopiec_[dziecko] = kopiec_[rodzic];
        dziecko=rodzic;
        rodzic/=2;
    }
    kopiec_[dziecko] = tenSamochod;
    
}

void Katalog::wyswietlanie(){
   Katalog zapas;
        for(int i = 1;i<=rkopca_; i++){
            zapas.insert(kopiec_[i]);
        }
        for(int i = 1; i<= rkopca_;i++){
            cout<< zapas.zwrocmin().rejestracjaSamochodu()<<" "<<zapas.zwrocmin().mocSamochod()<<" ";
            zapas.usuwaniemin();
        }
}

silnik zwrocrodzaj(char wartosc){
    switch(wartosc){
        case'B': return B;
        break;
        case'D': return D;
        break;
        case'E': return E;
        break;
        case'H': return H;
        break;
    }
}
bool spr_n_rejestracyjnego(string n_rejestracyjny){
    if(n_rejestracyjny.size()!=4)return false;
        for(int i=0;i<4;i++){
            if(n_rejestracyjny[i] < 48 or (n_rejestracyjny[i] > 57 and n_rejestracyjny[i] < 65) or (n_rejestracyjny[i] > 90 and n_rejestracyjny[i] < 97) or n_rejestracyjny[i] > 122)
        return false;
            }
        return true;
}

int main()
{
    Katalog katalog;
    for(int i = 0;i < 6;i++){
        string  n_rejestracyjny;
        do{
            cin>>n_rejestracyjny;
        }while(!spr_n_rejestracyjnego(n_rejestracyjny));
        int moc;
        do{
            cin>>moc;
        }while(moc<=0);
        
        double waga;
        do{
            cin>>waga;
        }while(waga<=0);
        
        char wartosc;
        do{
            cin>>wartosc;
        }while(wartosc!= 'B' and wartosc!= 'D' and wartosc!= 'E' and wartosc != 'H');
        silnik slinikrodzaj = zwrocrodzaj(wartosc);
        
        Samochod nowySamochod(n_rejestracyjny,moc,waga,slinikrodzaj);
        katalog.insert(nowySamochod);
    }
    katalog.wyswietlanie();
    
    return 0;
}