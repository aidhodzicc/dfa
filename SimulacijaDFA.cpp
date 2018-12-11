#include <iostream>
#include<fstream>
#include<vector>
#include<string>

using namespace std;

vector<int> Pretvori(string unos){                                      //Pretvaranje unešenog stringa u vektor
        vector<int> unesenistring;
        for(unsigned int i(0);i<unos.size();i++){
            unesenistring.push_back(unos[i]-'0');
        }
        return unesenistring;
}

bool GlavnaFunkcija(char pocetno, char zavrsno, int brojstanja, string unos, char ponasanje[][3]){          //Funkcija koja ispituje da li je string prihvaæen ili ne
    vector<int> strvektor;                                                                                  //Vektor u koji æemo smjestiti unešeni string
    strvektor=Pretvori(unos);
    char trenutnostanje=pocetno;
    cout<<pocetno<<unos<<endl;
    for(unsigned int i(0);i<strvektor.size();i++){
            if(strvektor[i]==1){                                                                            //Šta automat radi ukoliko u stringu naiðe na 1
                for(int j(0);j<brojstanja;j++){
                    if(trenutnostanje==ponasanje[j][0]){
                        trenutnostanje=ponasanje[j][2];                                                     //Mijenjanje stanja
                        for(unsigned int k(0);k<strvektor.size();k++){                                      //Ispis stringa
                            if(k==i+1) cout<<trenutnostanje<<strvektor[k];
                            else cout<<strvektor[k];
                        }
                        if(i==strvektor.size()-1) cout<<trenutnostanje;
                        cout<<endl;
                        break;
                    }
                }
            }
            else if(strvektor[i]==0){                                                                       //Šta automat radi ukoliko u stringu naiðe na 0
                for(int l(0);l<brojstanja;l++){
                    if(ponasanje[l][0]==trenutnostanje){
                        trenutnostanje=ponasanje[l][1];                                                     //Mijenjanje stanja
                        for(unsigned int h(0);h<strvektor.size();h++){                                      //Ispis stringa
                            if(h==i+1) cout<<trenutnostanje<<strvektor[h];
                            else cout<<strvektor[h];
                        }
                        if(i==strvektor.size()-1) cout<<trenutnostanje;
                        cout<<endl;
                        break;
                    }
                }
            }
    }
    if(trenutnostanje==zavrsno) return true;
    return false;
}

int main(){

    ifstream Informacije;
    Informacije.open("dfa.txt");
    int brojstanja;
    Informacije>>brojstanja;
    char pocetno, zavrsno; //Varijable za poèetno i završno stanje
    Informacije>>pocetno>>zavrsno;
    char stanja[brojstanja];    //Ovdje smještamo sva stanja koja imamo
    for(int i(0);i<brojstanja;i++){
        Informacije>>stanja[i];
    }
    char ponasanje[brojstanja][3]; //Niz nizova za smještanje kako æe se koje stanje ponašati prilikom dolaska 0 ili 1
    for(int i(0);i<brojstanja;i++){
        for(int j(0);j<3;j++) Informacije>>ponasanje[i][j];
    }
    string unos;
    while(1){
        cout<<"Unesite string: "<<endl;
        getline(cin,unos);
        bool prihvacen=GlavnaFunkcija(pocetno,zavrsno,brojstanja,unos,ponasanje);
        if(prihvacen) cout<<"String je prihvacen"<<endl;
        else cout<<"String nije prihvacen"<<endl;
        cout<<"Da li zelite opet unijeti string? DA/NE"<<endl;
        string odgovor;
        getline(cin,odgovor);
        if(odgovor=="NE") break;
    }
    return 0;
}
