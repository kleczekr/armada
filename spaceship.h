#ifndef SPACESHIP_H
#define SPACESHIP_H

#include<iostream>
#include<string>
#include<vector>
#include<stdexcept>

using namespace std;

enum class Faction{Empire, Rebels};
const std::vector<std::string> faction_names{"Empire", "Rebels"};

enum class Type{Squadron=10,Small=50,Medium=100,Big=200};
string to_string(Type);

class Spaceship {
    string name;
    Faction faction;
    Type type;
public:
    Faction(const string&, const Faction&, const Type&);
    Faction(const string&, const Faction&);
    int get_value() const;
    bool operator<(const Spaceship&) const;
    static bool same_faction(const vector<Spaceship>&, Faction);
    ostream& print(ostream&) const;
};

ostream& operator<<(ostream&, const Spaceship&);

#endif