#ifndef FLEET_H
#define FLEET_H

#include<iostream>
#include<stdexcept>
#include<string>
#include<vector>
#include "spaceship.h"

using namespace std;

class Fleet {
    string fl_name;
    Faction fl_faction;
    vector<Spaceship> fl_ships;
public:
    Fleet(const string&, const Faction&, const vector<Spaceship>&);
    bool add(const vector<Spaceship>&);
    vector<int> extremes() const;
    vector<Spaceship> elite(Fleet&);
    ostream& print(ostream&) const;
};

ostream& operator<<(ostream&, const Fleet&);

#endif