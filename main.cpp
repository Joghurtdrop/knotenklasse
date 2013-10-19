#include "sknoten.h"

int main()
{
using namespace std;
int input = 1;
int iptemp = 0;
bool rtemp = 0;
string temp;
string temp2;
Knoten Kleeblatt;
while(input != 0){
cout  << "Was wollen Sie tun:\n" 
      << "(1) Knoten eingeben \n"
      << "(2) R1 Zug \n"
      << "(3) R2 Zug \n"
      << "(4) R3 Zug \n"
      << "(5) Infos zum Knoten anzeigen \n"
      << "(0) exit" << endl;

cin >> input;
if(input == 1)
{
  cout << "Bitte geben Sie ihren Knoten ein: ";
  cin >> temp;
  const char * c = temp.c_str();
  Kleeblatt = c;
}
else if(input == 2)
{
  cout << "(1) hinzufuegen oder (2) entfernen?";
  cin >> iptemp; 
  if(iptemp == 1)
  {
  cout << "\nAuf welcher Strecke soll der R1 gemacht werden? (zB Ab)\n";
  Kleeblatt.p();
  cin >> temp;
  Kleeblatt.doR1(temp);
  }
  else if(iptemp == 2)
  {
  cout << "\nWelcher Strecke soll entfernt werden? (zB Aa)\n";
  Kleeblatt.p();
  cin >> temp;
  Kleeblatt.undoR1(temp);
  }
}
else if(input == 3)
{
  cout << "(1) hinzufuegen oder (2) entfernen?";
  cin >> iptemp;
  if (iptemp == 1)
  {
  cout << "Sind die Strecken gleichgerichtet (0) oder entgegengesetzt (1)" << endl;
  cin >> rtemp;
  Kleeblatt.p();
  cout << "Welche Strecke soll drueber liegen?" << endl;
  cin >> temp;
  cout << "Welche Strecke soll darunter liegen?" << endl;
  cin >> temp2;
  Kleeblatt.doR2(temp,temp2,rtemp);
  }
  else if(iptemp == 2)
  {
  cout << "Bitte die 2 Knoten eingeben.\n";
  Kleeblatt.p();
  cin >> temp;
  Kleeblatt.undoR2(temp);
  }
}
else if(input == 4)
{
Kleeblatt.p();
cout << "Geben Sie zuerst die zu \"ziehende\" Strecke ein: ";
cin >> temp;
cout << "Nun den Punkt ueber den gezogen wird: ";
cin >> temp2;
Kleeblatt.doR3(temp,temp2);
}
else if(input == 5)
 Kleeblatt.Print();

else input = 0;
}

}
