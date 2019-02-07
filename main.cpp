#include<iostream>
#include<string>
#include<vector>
#include<stdexcept>
#include"spaceship.h"
#include"fleet.h"

using namespace std;

/* vordefiniert in spaceship.h
enum class Faction{Empire, Rebels};
const std::vector<std::string> faction_names{"Empire", "Rebels"};

enum class Type{Squadron=10,Small=50,Medium=100,Big=200};
string to_string(Type);
*/
/* vordefiniert in spaceship.cpp
string to_string(Type t) {
	switch (t) {
	case Type::Squadron: return "Squadron";
	case Type::Small: return "Small";
	case Type::Medium: return "Medium";
	case Type::Big: return "Big";
	default: throw runtime_error("Illegal Type");
	}
}
*/

int main(){
//Basisfunktionalität Beginn
  try{
    cout << Spaceship{"",Faction::Empire};
  }catch(runtime_error& e){
    cout << "Error1\n";
  }
  // Rebel Ships
  const Spaceship xwing{"X-Wing",Faction::Rebels};
  const Spaceship ywing{"Y-Wing",Faction::Rebels};
  const Spaceship awing{"A-Wing",Faction::Rebels};
  const Spaceship mc80{"MC-80",Faction::Rebels,Type::Big};
  const Spaceship mc30{"MC-30",Faction::Rebels,Type::Small};
  const Spaceship cr90{"CR-90",Faction::Rebels,Type::Small};
  const Spaceship neb{"Nebulon-B",Faction::Rebels,Type::Medium};
  
  // Empire Ships
  const Spaceship tie{"Tie-Hunter",Faction::Empire};
  const Spaceship tiei{"Tie-Interceptor",Faction::Empire};
  const Spaceship tieb{"Tie-Bomber",Faction::Empire};
  const Spaceship issd{"Imperial Super Star Destroyer",Faction::Empire,Type::Big};
  const Spaceship isd{"Imperial Star Destroyer",Faction::Empire,Type::Big};
  const Spaceship dictor{"Interdictor Star Destroyer",Faction::Empire,Type::Medium};
  const Spaceship raider{"Raider Corvette",Faction::Empire,Type::Small};
  
  // get_value()
  cout << xwing.get_value() << '\n';   
  cout << ywing.get_value() << '\n';   
  cout << awing.get_value() << '\n';   
  cout << neb.get_value() << '\n';   
  cout << tie.get_value() << '\n';   
  cout << tiei.get_value() << '\n';   
  cout << issd.get_value() << '\n';   
  cout << dictor.get_value() << '\n';   

  // operator< 
  cout << (xwing<ywing) << (xwing<mc80) << (xwing<tie) << (tie<xwing) << '\n';
  cout << (neb<mc30) << (issd<raider) << (isd < dictor) << (tieb<awing) << '\n';
  
  // same_faction
  const vector<Spaceship> rebels{xwing,xwing,ywing,mc80,cr90,mc30,mc30};
  const vector<Spaceship> empire{tie,tie,tiei,tieb,issd,isd,isd,dictor,raider};
  
  const vector<Spaceship> mixed1{xwing,tie};
  const vector<Spaceship> mixed2{isd,issd,raider,xwing,awing,tiei};
  const vector<Spaceship> mixed3{xwing,awing,tiei,mc80};
  try{
    Spaceship::same_faction({},Faction::Rebels);
  }catch(runtime_error& e){
    cout << "Error2\n";
  }
  cout << Spaceship::same_faction(rebels,Faction::Rebels);
  cout << Spaceship::same_faction(rebels,Faction::Empire);
  cout << Spaceship::same_faction(empire,Faction::Empire);
  cout << Spaceship::same_faction(empire,Faction::Rebels);
  cout << '\n';
  cout << Spaceship::same_faction(mixed1,Faction::Empire);
  cout << Spaceship::same_faction(mixed1,Faction::Rebels);
  cout << Spaceship::same_faction(mixed2,Faction::Empire);
  cout << Spaceship::same_faction(mixed2,Faction::Rebels);
  cout << Spaceship::same_faction(mixed3,Faction::Empire);
  cout << Spaceship::same_faction(mixed3,Faction::Rebels);
  cout << '\n';

  // operator<<
  cout << xwing << '\n';
  cout << ywing << '\n';
  cerr << isd << '\n';
  cout << tie << '\n';
  cerr << tiei << '\n';


  // Fleet
  try{
    cout << Fleet{"",Faction::Rebels,{}};
  }catch(runtime_error& e){
    cout << "Error3\n";
  }
  try{
    cout << Fleet{"Coruscant Defense Fleet",Faction::Rebels,{}};
  }catch(runtime_error& e){
    cout << "Error4\n";
  }
  try{
    cout << Fleet{"Enterprise",Faction::Rebels,mixed1};
  }catch(runtime_error& e){
    cout << "Error5\n";
  }

  try{
    cout << Fleet{"Imperial Fleet",Faction::Rebels,empire};
  }catch(runtime_error& e){
    cout << "Error6\n";
  }
  try{
    cout << Fleet{"Rebel Fleet",Faction::Empire,empire};
  }catch(runtime_error& e){
    cout << "Error7\n";
  }

  // add
  Fleet rebel_fleet{"Rebel Fleet",Faction::Rebels,rebels}; 
  Fleet imp_fleet{"Imperial Fleet",Faction::Empire,empire}; 

  cout << rebel_fleet.add({xwing,ywing});
  cout << rebel_fleet.add(mixed1);
  cout << rebel_fleet.add(empire);
  cout << '\n';
  cout << rebel_fleet << '\n';
  cout << imp_fleet.add({tiei,issd});
  cout << imp_fleet.add(mixed1);
  cout << imp_fleet.add(rebels);
  cout << '\n';
  cout << imp_fleet << '\n';

  try{
    imp_fleet.add({});
  }catch(runtime_error& e){
    cout << "Error8\n";
  }

  Fleet cpy{imp_fleet};
  const Fleet ccpy{cpy};
  cout << cpy << '\n';
  cout << ccpy << '\n';

  // operator<<
  cout << cpy << '\n';
  cout << rebel_fleet << '\n';
  cerr << rebel_fleet << '\n';
  cout << imp_fleet << '\n';

  //Basisfunktionalität Ende

  //Zusatz für 10 Punkte
  
  cout << "\n\nZusatz 10 Punkte" << '\n';
  {
    try{
      Fleet{"Temp",Faction::Empire,{}}.extremes();
    }catch(runtime_error& e){
      cout << "Error9\n";
    }
    vector<int> vi{rebel_fleet.extremes()};
    cout << vi[0] << '\n' << vi[1] << '\n';
    vi = Fleet{"Temp",Faction::Rebels,{xwing}}.extremes();
    cout << vi[0] << '\n' << vi[1] << '\n';
    vi = Fleet{"Temp",Faction::Rebels,{ywing, ywing, ywing}}.extremes();
    cout << vi[0] << '\n' << vi[1] << '\n';
    vi = imp_fleet.extremes();
    cout << vi[0] << '\n' << vi[1] << '\n';
  }
  


  //Zusatz für 15 Punkte
  
  cout << "\n\nZusatz 15 Punkte" << "\n";
  {
    try{
      rebel_fleet.elite(cpy);
    }catch(runtime_error& e){
      cout << "Error10\n";
    }
    try{
      imp_fleet.elite(rebel_fleet);
    }catch(runtime_error& e){
      cout << "Error11\n";
    }
    Fleet f{"Weak Fleet",Faction::Rebels,{xwing,xwing,xwing,xwing}};
    Fleet e{"Strong Fleet",Faction::Rebels,{mc80,neb,mc30,awing}};
    cout << f << '\n' << e << '\n';
    cout << Fleet{"out",Faction::Rebels,f.elite(e)} << '\n';
    cout << f << '\n' << e << '\n';
    cout <<  Fleet{"out",Faction::Rebels,f.elite(e)} << '\n';
    cout << f << '\n' << e << '\n';
    Fleet g{"Empirial Fleet",Faction::Empire,{tie,isd,dictor,raider}};
    try{
      g.elite(f);
    }catch(runtime_error& e){
      cout << "Error12\n";
    }

  }
  

  return 0;
}

/* Erwartete Ausgabe
Error1
20
20
20
200
30
30
600
300
0110
0000
1010
000000
[X-Wing, Rebels, Squadron, 20]
[Y-Wing, Rebels, Squadron, 20]
[Imperial Star Destroyer, Empire, Big, 600]
[Tie-Hunter, Empire, Squadron, 30]
[Tie-Interceptor, Empire, Squadron, 30]
Error3
[Coruscant Defense Fleet, Rebels, {}]Error5
Error6
[Rebel Fleet, Empire, {[Tie-Hunter, Empire, Squadron, 30], [Tie-Hunter, Empire, Squadron, 30], [Tie-Interceptor, Empire, Squadron, 30], [Tie-Bomber, Empire, Squadron, 30], [Imperial Super Star Destroyer, Empire, Big, 600], [Imperial Star Destroyer, Empire, Big, 600], [Imperial Star Destroyer, Empire, Big, 600], [Interdictor Star Destroyer, Empire, Medium, 300], [Raider Corvette, Empire, Small, 150]}]100
[Rebel Fleet, Rebels, {[X-Wing, Rebels, Squadron, 20], [Y-Wing, Rebels, Squadron, 20], [X-Wing, Rebels, Squadron, 20], [X-Wing, Rebels, Squadron, 20], [Y-Wing, Rebels, Squadron, 20], [MC-80, Rebels, Big, 400], [CR-90, Rebels, Small, 100], [MC-30, Rebels, Small, 100], [MC-30, Rebels, Small, 100]}]
100
[Imperial Fleet, Empire, {[Tie-Interceptor, Empire, Squadron, 30], [Imperial Super Star Destroyer, Empire, Big, 600], [Tie-Hunter, Empire, Squadron, 30], [Tie-Hunter, Empire, Squadron, 30], [Tie-Interceptor, Empire, Squadron, 30], [Tie-Bomber, Empire, Squadron, 30], [Imperial Super Star Destroyer, Empire, Big, 600], [Imperial Star Destroyer, Empire, Big, 600], [Imperial Star Destroyer, Empire, Big, 600], [Interdictor Star Destroyer, Empire, Medium, 300], [Raider Corvette, Empire, Small, 150]}]
Error8
[Imperial Fleet, Empire, {[Tie-Interceptor, Empire, Squadron, 30], [Imperial Super Star Destroyer, Empire, Big, 600], [Tie-Hunter, Empire, Squadron, 30], [Tie-Hunter, Empire, Squadron, 30], [Tie-Interceptor, Empire, Squadron, 30], [Tie-Bomber, Empire, Squadron, 30], [Imperial Super Star Destroyer, Empire, Big, 600], [Imperial Star Destroyer, Empire, Big, 600], [Imperial Star Destroyer, Empire, Big, 600], [Interdictor Star Destroyer, Empire, Medium, 300], [Raider Corvette, Empire, Small, 150]}]
[Imperial Fleet, Empire, {[Tie-Interceptor, Empire, Squadron, 30], [Imperial Super Star Destroyer, Empire, Big, 600], [Tie-Hunter, Empire, Squadron, 30], [Tie-Hunter, Empire, Squadron, 30], [Tie-Interceptor, Empire, Squadron, 30], [Tie-Bomber, Empire, Squadron, 30], [Imperial Super Star Destroyer, Empire, Big, 600], [Imperial Star Destroyer, Empire, Big, 600], [Imperial Star Destroyer, Empire, Big, 600], [Interdictor Star Destroyer, Empire, Medium, 300], [Raider Corvette, Empire, Small, 150]}]
[Imperial Fleet, Empire, {[Tie-Interceptor, Empire, Squadron, 30], [Imperial Super Star Destroyer, Empire, Big, 600], [Tie-Hunter, Empire, Squadron, 30], [Tie-Hunter, Empire, Squadron, 30], [Tie-Interceptor, Empire, Squadron, 30], [Tie-Bomber, Empire, Squadron, 30], [Imperial Super Star Destroyer, Empire, Big, 600], [Imperial Star Destroyer, Empire, Big, 600], [Imperial Star Destroyer, Empire, Big, 600], [Interdictor Star Destroyer, Empire, Medium, 300], [Raider Corvette, Empire, Small, 150]}]
[Rebel Fleet, Rebels, {[X-Wing, Rebels, Squadron, 20], [Y-Wing, Rebels, Squadron, 20], [X-Wing, Rebels, Squadron, 20], [X-Wing, Rebels, Squadron, 20], [Y-Wing, Rebels, Squadron, 20], [MC-80, Rebels, Big, 400], [CR-90, Rebels, Small, 100], [MC-30, Rebels, Small, 100], [MC-30, Rebels, Small, 100]}]
[Rebel Fleet, Rebels, {[X-Wing, Rebels, Squadron, 20], [Y-Wing, Rebels, Squadron, 20], [X-Wing, Rebels, Squadron, 20], [X-Wing, Rebels, Squadron, 20], [Y-Wing, Rebels, Squadron, 20], [MC-80, Rebels, Big, 400], [CR-90, Rebels, Small, 100], [MC-30, Rebels, Small, 100], [MC-30, Rebels, Small, 100]}]
[Imperial Fleet, Empire, {[Tie-Interceptor, Empire, Squadron, 30], [Imperial Super Star Destroyer, Empire, Big, 600], [Tie-Hunter, Empire, Squadron, 30], [Tie-Hunter, Empire, Squadron, 30], [Tie-Interceptor, Empire, Squadron, 30], [Tie-Bomber, Empire, Squadron, 30], [Imperial Super Star Destroyer, Empire, Big, 600], [Imperial Star Destroyer, Empire, Big, 600], [Imperial Star Destroyer, Empire, Big, 600], [Interdictor Star Destroyer, Empire, Medium, 300], [Raider Corvette, Empire, Small, 150]}]


Zusatz 10 Punkte
Error9
20
400
20
20
20
20
30
600


Zusatz 15 Punkte
Error10
Error11
[Weak Fleet, Rebels, {[X-Wing, Rebels, Squadron, 20], [X-Wing, Rebels, Squadron, 20], [X-Wing, Rebels, Squadron, 20], [X-Wing, Rebels, Squadron, 20]}]
[Strong Fleet, Rebels, {[MC-80, Rebels, Big, 400], [Nebulon-B, Rebels, Medium, 200], [MC-30, Rebels, Small, 100], [A-Wing, Rebels, Squadron, 20]}]
[out, Rebels, {[MC-30, Rebels, Small, 100], [Nebulon-B, Rebels, Medium, 200], [MC-80, Rebels, Big, 400]}]
[Weak Fleet, Rebels, {[MC-80, Rebels, Big, 400], [Nebulon-B, Rebels, Medium, 200], [MC-30, Rebels, Small, 100], [X-Wing, Rebels, Squadron, 20]}]
[Strong Fleet, Rebels, {[X-Wing, Rebels, Squadron, 20], [X-Wing, Rebels, Squadron, 20], [X-Wing, Rebels, Squadron, 20], [A-Wing, Rebels, Squadron, 20]}]
[out, Rebels, {}]
[Weak Fleet, Rebels, {[MC-80, Rebels, Big, 400], [Nebulon-B, Rebels, Medium, 200], [MC-30, Rebels, Small, 100], [X-Wing, Rebels, Squadron, 20]}]
[Strong Fleet, Rebels, {[X-Wing, Rebels, Squadron, 20], [X-Wing, Rebels, Squadron, 20], [X-Wing, Rebels, Squadron, 20], [A-Wing, Rebels, Squadron, 20]}]
Error12
*/