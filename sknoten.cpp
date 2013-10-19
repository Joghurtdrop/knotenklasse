#include "sknoten.h"

/*  Knoten()
  {
    kzahl = 0;
    kfolge = "";
    kname = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  }
*/
  Knoten::Knoten( const char *folge )
  { 
    SetKnoten (folge);
  }

 
  void Knoten::SetKnoten( const char *folge )
  {
    kfolge = folge;
    kzahl = kfolge.length()/2;
    kname = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    for( int i=0; i < kfolge.length(); ++i)
    { 
      if(kfolge.find(kfolge[i]+32)==std::string::npos & kfolge.find(kfolge[i]-32)==std::string::npos)
      {
	std::cout << "Der Kreuzung \""<<kfolge[i]<<"\" fehlt der Partner!"<<std::endl;
	exit;	
      }
      if(checkused(kfolge[i]))
	{
	  std::cout<<"Kein gueltiger Knoten, \""<<kfolge[i]<<"\" ist schon vergeben!"<<std::endl;
	  exit;
	}
      std::string temp(1,kfolge[i]);
      setused(temp);
    }
  }
  
  // get next unused name for a knot
  std::string Knoten::getunused()
  {
    sort(kname.begin(),kname.end());
    std::string unused;
    unused.append(1,kname[0]);
    unused.append(1,kname[kname.length()/2]);
    return unused;
  }
  
  // check if name is allready in use
  bool Knoten::checkused(char s)
  {
    return (kname.find(s)==std::string::npos);
  }
  
  // check if string exist in knot 
  bool Knoten::checkinfolge(std::string s)
  {
    return (kfolge.find(s)!=std::string::npos);
  }

  // set string to unused
  void Knoten::setunused(std::string s)
  {
    for(int i = 1; i<=s.length(); ++i)
    {
      if(checkused(s[i-1]))
      {
	kname.append(1,s[i-1]);
      }
    }
    sort(kname.begin(),kname.end());
  }

  // set string to used
  void Knoten::setused(std::string s)
  {  
    for(int j = 1; j<=s.length(); ++j)
    { 
      if(!checkused(s[j-1]))
      {
	kname.erase(kname.find(s[j-1]),1);
      }
    }
    sort(kname.begin(),kname.end());
  }


  void Knoten::doR1(std::string strecke )
  {
    if (strecke.length()!=2)
    {
      std::cout << "Bitte nur 2 Buchstaben eingeben." << std::endl;
      return;
    }

    if (!checkinfolge(strecke))
    {
      std::cout << "Diese Strecke wurde nicht gefunden!" << std::endl;
      return;
    }

    kzahl +=1;
    std::string temps = getunused();
    kfolge.insert( kfolge.find(strecke)+1,temps );
    setused(temps);
  }

  void Knoten::undoR1( std::string strecke )
  {
    if(strecke.length()!=2)
    {
      std::cout<<"R1 geht nur auf einen Knoten (zB Aa)!"<<std::endl;
      return;
    }

    if(strecke[0]+32!=strecke[1] & strecke[0]-32!=strecke[1])
    {
      std::cout<<"R1 geht nur auf einen Knoten (zB Aa)!"<<std::endl;
      return;
    }

    if( kfolge.find(strecke)==std::string::npos)
    {
      std::cout << "Diese Strecke wurde nicht gefunden!"<<std::endl;
      return;
    }
    kzahl -=1;
    kfolge.erase(kfolge.find(strecke),strecke.length());
    setunused(strecke);

  }

  void Knoten::doR2(std::string s,std::string k, bool r)
  {
    if(s.length() !=2 & k.length() != 2)
    {
      std::cout << "Je Strecke nur 2 Buchstaben." << std::endl;
      return;
    }

    if (!checkinfolge(s) | !checkinfolge(k))
    {
      std::cout << "Mindestens eine Strecke nicht gefunden!" << std::endl;
      return;
    }

    std::string neueins = getunused();
    setused(neueins);
    std::string neu (neueins) ;
    std::string neuzwei  = getunused();
    setused(neuzwei);
    neu.append(neuzwei);
    sort(neu.begin(),neu.end());

    if (!r)
    {
      kfolge.insert(kfolge.find(s)+1,neu,0,2);
      kfolge.insert(kfolge.find(k)+1,neu,2,2);
    } 
    else if (r)
    {
      kfolge.insert(kfolge.find(s)+1,neu,0,2);
      std::string rneu = std::string(neu.rbegin(),neu.rend());
      kfolge.insert(kfolge.find(r)+1,rneu,0,2);
    }
    else std::cout << "Fehler!" << std::endl;

    
  }

  void Knoten::undoR2(std::string s)
  {
    sort(s.begin(),s.end());
    std::string k = std::string(s.rbegin(),s.rend());
    if( s.length()!=4)
    {
      std::cout << "Bitte 2 komplette Knoten eingeben.\n";
      return;
    }
    for (int i = 0; i<s.length(); ++i)
    {
      if (!checkused(s[i]))
      {
        std::cout << "R2 hier nicht moeglich!" << std::endl;
        return;
      }
    }
    if (checkinfolge(s.substr(0,2)))
    {  
      kfolge.erase(kfolge.find(s.substr(0,2)),2);
      setunused(s.substr(0,2));
    }
    else if (checkinfolge(k.substr(2,2)))
    {
      kfolge.erase(kfolge.find(k.substr(2,2)),2);
      setunused(k.substr(2,2));
    }
    
    if (checkinfolge(s.substr(2,2)))
    {
      kfolge.erase(kfolge.find(s.substr(2,2)),2);
      setunused(s.substr(2,2));
    }
    else if (checkinfolge(k.substr(0,2)))
    {
      kfolge.erase(kfolge.find(k.substr(0.2)));
      setunused(k.substr(0,2));
    }
    kzahl -=2;

  }

  void Knoten::doR3(std::string zweipunkte, std::string punkt)
  {
    sort(zweipunkte.begin(),zweipunkte.end());
    sort(punkt.begin(),punkt.end());
    std::string rzweipunkte = std::string(zweipunkte.rbegin(),zweipunkte.rend());
    std::string temp = "";

    // entweder die strecke liegt unter
    if(checkinfolge(zweipunkte.substr(0,2)) | checkinfolge(rzweipunkte.substr(2,2)))
    {
      std::size_t foundone = kfolge.find(punkt[0]);
      std::size_t foundtwo = kfolge.find(punkt[1]);

      if(kfolge[foundone-1]==zweipunkte[2])
      {
	foundone -= 1;
	kfolge[foundone]=zweipunkte[3];
      }
      else if(kfolge[foundone-1]==zweipunkte[3])
      {
	foundone -=1;
	kfolge[foundone]=zweipunkte[2];
      }
      else if(kfolge[foundone+1]==zweipunkte[2])
      {
	kfolge[foundone+1]=zweipunkte[3];
      }
      else if(kfolge[foundone+1]==zweipunkte[3])
      {
	kfolge[foundone+1]=zweipunkte[2];
      }
      else std::cout << "Fehler" << std::endl;
      
      if(kfolge[foundtwo-1]==zweipunkte[2])
      {
	foundtwo -= 1;
	kfolge[foundtwo]=zweipunkte[3];
      }
      else if(kfolge[foundtwo-1]==zweipunkte[3])
      {
	foundtwo -=1;
	kfolge[foundtwo]=zweipunkte[2];
      }
      else if(kfolge[foundtwo+1]==zweipunkte[2])
      {
	kfolge[foundtwo+1]=zweipunkte[3];
      }
      else if(kfolge[foundtwo+1]==zweipunkte[3])
      {
	kfolge[foundtwo+1]=zweipunkte[2];
      }
      else std::cout << "Fehler" << std::endl;
      
      reverse(kfolge.begin()+foundone,kfolge.begin()+foundone+2);
      reverse(kfolge.begin()+foundtwo,kfolge.begin()+foundtwo+2);

    }
    //oder ueber dem punkt
    else if(checkinfolge(zweipunkte.substr(2,2)) | checkinfolge(rzweipunkte.substr(0,2)))
    {
      std::size_t foundone = kfolge.find(punkt[0]);
      std::size_t foundtwo = kfolge.find(punkt[1]);

      if(kfolge[foundone-1]==zweipunkte[0])
      {
	foundone -= 1;
	kfolge[foundone]=zweipunkte[1];
      }
      else if(kfolge[foundone-1]==zweipunkte[1])
      {
	foundone -=1;
	kfolge[foundone]=zweipunkte[0];
      }
      else if(kfolge[foundone+1]==zweipunkte[0])
      {
	kfolge[foundone+1]=zweipunkte[1];
      }
      else if(kfolge[foundone+1]==zweipunkte[1])
      {
	kfolge[foundone+1]=zweipunkte[0];
      }
      else std::cout << "Fehler" << std::endl;
      
      if(kfolge[foundtwo-1]==zweipunkte[0])
      {
	foundtwo -= 1;
	kfolge[foundtwo]=zweipunkte[1];
      }
      else if(kfolge[foundtwo-1]==zweipunkte[1])
      {
	foundtwo -=1;
	kfolge[foundtwo]=zweipunkte[0];
      }
      else if(kfolge[foundtwo+1]==zweipunkte[0])
      {
	kfolge[foundtwo+1]=zweipunkte[1];
      }
      else if(kfolge[foundtwo+1]==zweipunkte[1])
      {
	kfolge[foundtwo+1]=zweipunkte[0];
      }
      else std::cout << "Fehler" << std::endl;
      
      reverse(kfolge.begin()+foundone,kfolge.begin()+foundone+2);
      reverse(kfolge.begin()+foundtwo,kfolge.begin()+foundtwo+2);


    }
    else std::cout << "Nicht gefunden!" << std::endl;
  }


  void Knoten::p()
  {
  std::cout << kfolge << std::endl;
  }

  void Knoten::Print()
  {
   std::cout << "Anzahl an Knoten: " << kzahl << std::endl;
   std::cout << "Knotenfolge: " << kfolge << std::endl;
   std::cout << "noch moegliche Knoten: " << kname << std::endl;
  }



