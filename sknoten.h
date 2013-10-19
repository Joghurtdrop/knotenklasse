#ifndef KNOTEN_H
#define KNOTEN_H

#include <iostream>
#include <string>
#include <algorithm>

class Knoten
{
private:
  int kzahl;
  std::string kfolge;
  std::string kname;
  std::string getunused();
  bool checkinfolge(std::string s);
  bool checkused(char s);
  void setunused(std::string s);
  void setused(std::string s);

public:
  Knoten(const char *folge = "");
  void SetKnoten(const char *folge); 
  void doR1(std::string strecke );
  void undoR1(std::string strecke);
  void doR2(std::string s,std::string k, bool r);
  void undoR2(std::string s);
  void doR3(std::string zweipunkte, std::string punkt);
  void p();
  void Print();
};

#endif
