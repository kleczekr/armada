#include<iostream>
#include<string>
#include<vector>
#include<stdexcept>
#include "spaceship.h"

using namespace std;

// The to_string function was already provided in the file

string to_string(Type t) {
    switch (t) {
    case Type::Squadron: return "Squadron";
    case Type::Small: return "Small";
    case Type::Medium: return "Medium";
    case Type::Big: return "Big";
    default: throw runtime_error("Illegal Type");
    }
}

Spaceship::Spaceship(const string& a, const Faction& b, const Type& c):
        name{a}, faction{b}, type{c} {
    if (name.size() == 0) {
        throw runtime_error("Name is empty");
    }
}

Spaceship::Spaceship(const string& a, const Faction& b): name{a}, 
        faction{b}, type{Type::Squadron} {
    if (name.size() == 0) {
        throw runtime_error("Name is empty");
    }
}

int Spaceship::get_value() const {
    // getting the numeric value from the Type enumeration
    int value = static_cast<int>(type);
    // need to multiply the numeric value in accordance with the instructions
    if (faction == Faction::Rebels) {
        value *= 2;
    } else {
        value *= 3;
    }
    return value;
}


// I ended up spending an hour trying to debug this function because I forgot to
// include one "const" statement (the exact syntax is not given in the instructions).
// If you stumble on something like that, remember the lecture slides which
// are available during the exam. The most important slides for the exam are probably
// somewhere between slide 200 and 250.
bool Spaceship::operator<(const Spaceship& rightside_spaceship) const {
    return (this->get_value() < rightside_spaceship.get_value());
}

bool Spaceship::same_faction(const vector<Spaceship>& ships, Faction f) {
    for (int i = 0; i < ships.size(); ++i) {
        if (ships[i].faction != f) {
            return false;
        }
    }
    // if none of the ships in the "ships" vector will trigger the "return false"
    // (i.e. there are none which would be from a different faction than the one
    // given), then the function will return true
    return true;
}

ostream& Spaceship::print(ostream& o) const {
    // it is good to remember how to get the proper value from the vector
    // which lists the strings for the enum classes (here, the factions).
    // The type is returned by the predefined function to_string(type).
    // We also need to use the get_value() function to get proper values.
    o << "[" << name << ", " << faction_names.at(static_cast<size_t>(faction)) << 
        ", " << to_string(type) << ", " << this->get_value() << "]";
    return o;
}

ostream& operator<<(ostream& o, const Spaceship& s) {
    return s.print(o);
}

