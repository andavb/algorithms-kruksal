#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;

int vel,stPov, sprejetePovezave=0;
struct povezava {
  int p;
  int q;
  double cena;
};

void beri(povezava p[], string f)
{
  fstream dat(f.c_str(), fstream::in);
  dat >> vel;
  int i=0;
  while(!dat.eof())
  {
    dat >> p[i].p >> p[i].q >> p[i].cena;
    i++;
  }
  stPov=i;
  dat.close();
}
void Zamenjaj(povezava a[], int prvi, int drugi){
    povezava pomozna;

    pomozna = a[prvi];
    a[prvi] = a[drugi];
    a[drugi] = pomozna;
}
int Deli(povezava a[], int dno, int vrh)
{
    int desni, levi, mediana;
    double pe;

    mediana = (dno+vrh)/2;
    Zamenjaj(a, dno, mediana);

    pe = a[dno].cena;

    desni = vrh;
    levi = dno;

    while(levi < desni)
    {
        while((a[levi].cena <= pe) && (levi < vrh)){
            levi++;
        }
        while((a[desni].cena >= pe) && (desni > dno)){
            desni--;
        }

        if(levi < desni){
            Zamenjaj(a, levi, desni);
        }
        else{
            Zamenjaj(a, dno, desni);
        }
    }
    return(desni);
}
void HitroUredi(povezava a[], int dno, int vrh){

    int j;
    if(dno < vrh)
    {
        j = Deli(a, dno, vrh);
        HitroUredi(a, dno, j-1);
        HitroUredi(a, j+1, vrh);
    }
}
int Meni() {
    int i;
    do {
        cout << "----------------------------------" << endl;
        cout << "| Kruskalov algoritem - izbira:  |" << endl;
        cout << "|                                |"<<endl;
        cout << "| 1. Preberi graf iz datoteke    |" << endl;
        cout << "| 2. Generiraj nakljuci graf     |" << endl;
        cout << "| 3. Pozeni                      |" << endl;
        cout << "| 4. Izpis sprejetih povezav     |" << endl;
        cout << "| 5. Konec                       |" << endl;
        cout << "----------------------------------" << endl;
        cout << "Vasa izbira: ";
        cin >> i;
        cout<<"\n";
    } while (i > 5 || i < 1);

    return i;
}
void Nakljucni(povezava P[]){
    do{
        cout<<"Vnesite stevilo vozlisc: ";
        cin>>vel;
    }while(vel>1500 || vel<0);

    for(int i=0; i<(vel*(vel-1)/2); i++){
        P[i].p = rand()%1501;
        P[i].q = rand()%1501;
        P[i].cena = rand()%1501;
    }
    stPov = (vel*(vel-1)/2);
}
void Kruksal(povezava P[], povezava R[])
{
     int S[1500] ={0};
     int S1;
     int S2;
     bool koncano = false;
     int i = 1;
     int mnozica=1;
     int zacasna;
     sprejetePovezave = 0;

     HitroUredi(P, 0, stPov-1);

     for(int j=0; j<vel; j++){
         R[i].p = 0;
         R[i].q = 0;
         R[i].cena = 0;
     }

    while(!koncano){

         S1 = P[i].p;
         S2 = P[i].q;

         if((S[S1] != S[S2]) || (S[S1] == 0 && S[S2] == 0)){
             if((S[S1]!=0 && S[S2]!=0) && (S[S1] != S[S2])){
                    R[sprejetePovezave] = P[i];
                    sprejetePovezave += 1;
                    zacasna = S[S2];
                    for(int y=1; y<=vel; y++)
                    {
                        if(S[y] == zacasna){
                            S[y] = S[S1];
                        }
                    }
             }
             else if((S[S1] != 0 && S[S2] == 0) || (S[S1] == 0 && S[S2] != 0)){
                 R[sprejetePovezave] = P[i];
                 sprejetePovezave += 1;
                 if(S[S1] != 0 && S[S2] == 0){
                     S[S2] = S[S1];
                 }
                 else
                     S[S1] = S[S2];
             }
             else if(S[S1] == 0 && S[S2] == 0){
                 R[sprejetePovezave] = P[i];
                 sprejetePovezave += 1;
                 S[S1]=mnozica;
                 S[S2]=mnozica;
                 mnozica++;
             }
         }
         if(sprejetePovezave == vel-1){
             koncano = true;
         }
         else{
             i++;
         }
     }
}
int main()
{
  srand( time(NULL));
  clock_t zacetek, konec;
  povezava *p = new povezava[1124250]; //<-- (1500(1500-1)/2) = 1124250
  povezava r[1499]; //<-- sprejete povezave stVozlisc-1 == (1500-1 = 1499)
  int izbira;

  do{
      izbira = Meni();

      if(izbira == 1){
          beri(p,"graf.txt");
      }
      else if(izbira == 2){
          Nakljucni(p);
      }
      else if(izbira == 3){

          zacetek = clock();
          Kruksal(p, r);
          konec = clock();

          cout << "Stevilo povezav: " << stPov << endl;
          cout << "Stevilo vozlisc: " << vel << endl;
          cout << "Stevilo sprejetih povezav: " << sprejetePovezave << endl;
          cout<<"Cas izvajanj algoritma: "<<(double)(konec-zacetek)/CLOCKS_PER_SEC<<endl;
      }
      else if(izbira == 4){
          for(int i=0;i<sprejetePovezave;i++)
            cout << "V1: " << r[i].p << " V2: " << r[i].q << " Cena: " << r[i].cena << endl;
      }
  }while(izbira != 5);

  return 0;
}
