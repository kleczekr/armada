#include<iostream>
#include<string>
#include<vector>
#include<stdexcept>
#include "fleet.h"

using namespace std;

Fleet::Fleet(const string& a, const Faction& b, const vector<Spaceship>& c): fl_name{a}, fl_faction{b}, fl_ships{c} {
    if (fl_name.size() == 0) {
        throw runtime_error("Name is empty");
    }
    for (int i = 0; i < fl_ships.size(); ++i) {
        // We use the "same faction" function from the spaceship to check the factions
        // of the individual ships.
        if (!Spaceship::same_faction(fl_ships, fl_faction)) {
            throw runtime_error("There is a ship of a different faction in the fleet");
        }
    }
}

bool Fleet::add(const vector<Spaceship>& ships) {
    if (ships.size() == 0) {
        throw runtime_error("The vector is empty.");
    }
    for (int i = 0; i < ships.size(); ++i) {
        // Again we use the same_faction function to check if there are ships of
        // a different faction in the vector of ships.
        if (!Spaceship::same_faction(ships, fl_faction)) {
            return false;
        } else {
            // I will use a temporary vector "temp", because the new ships
            // need to be added at the beginning of our vector of ships.
            // I initialize it already as an empty vector, so that I can
            // later simply push individual spaceships.
            vector<Spaceship> temp {};
            for (int i = 0; i < ships.size(); ++i) {
                temp.push_back(ships[i]);
            }
            // After putting the ships from the provided vector to the temp vector,
            // I put the ships from our base fl_ships vector
            for (int i = 0; i < fl_ships.size(); ++i) {
                temp.push_back(fl_ships[i]);
            }
            // Now, we can assign the value of the vector "temp" to our
            // fl_ships vector
            fl_ships = temp;
        }
    }
    // if nothing bad happens, the function will return true
    return true;
}

vector<int> Fleet::extremes() const {
    // we'll provide imaginary values for the "min" and "max" integers
    int min = 1000; // there are no '1000' values in the spaceships
    int max = 0;
    if (fl_ships.size() == 0) {
        throw runtime_error("The list is empty");
    }
    for (int i = 0; i < fl_ships.size(); ++i) {
        // Remember the "get_value()" function?
        if (fl_ships[i].get_value() < min) {
            min = fl_ships[i].get_value();
        }
        if (fl_ships[i].get_value() > max) {
            max = fl_ships[i].get_value();
        }
    }
    return vector<int>{min, max};
}

vector<Spaceship> Fleet::elite(Fleet& f) {
    // Check if both fleets belong to the same faction
    if (f.fl_faction != this->fl_faction) {
        throw runtime_error("Different factions");
    }
    // Check if both fleets have the same number of ships
    if (f.fl_ships.size() != this->fl_ships.size()) {
        throw runtime_error("Different fleet size");
    }
    // I know the function can be built with smaller number of helper vectors,
    // I did it this way for simplicity sake.
    vector<Spaceship> exchanged_ships {};
    // The output should be the exchanged ships in *reverse order*
    vector<Spaceship> exchanged_ships_reversed {};
    vector<Spaceship> temp_strong_fleet {};
    vector<Spaceship> temp_weak_fleet {};
    for (int i = 0; i < f.fl_ships.size(); ++i) {
        // If the ship in the other fleet is stronger...
        if (this->fl_ships[i].get_value() < f.fl_ships[i].get_value()) {
            temp_strong_fleet.push_back(f.fl_ships[i]);
            temp_weak_fleet.push_back(this->fl_ships[i]);
            // remember to update the "exchanged_ships" vector
            exchanged_ships.push_back(f.fl_ships[i]);
        } else { // otherwise...
            temp_strong_fleet.push_back(this->fl_ships[i]);
            temp_weak_fleet.push_back(f.fl_ships[i]);
            // Here, no need to update the "exchanged_ships", because
            // we do not exchange ships.
        }
    }
    // What is left to do is reversing the order of the exchanged ships list:
    for (int i = exchanged_ships.size()-1; i >= 0; --i) {
        exchanged_ships_reversed.push_back(exchanged_ships[i]);
    }

    // Assign the temp vectors to the original vectors:
    this->fl_ships = temp_strong_fleet;
    f.fl_ships = temp_weak_fleet;
    // And return the reversed vector of exchanged ships>
    return exchanged_ships_reversed;
}

ostream& Fleet::print(ostream& o) const {
    o << "[" << fl_name << ", " << 
        faction_names.at(static_cast<size_t>(fl_faction)) << ", {";
    for (int i = 0; i < fl_ships.size(); ++i) {
        if (i != fl_ships.size()-1) {
            o << fl_ships[i] << ", ";
        } else {
            o << fl_ships[i];
        }
    }
    o << "}]";
    return o;
}

ostream& operator<<(ostream& o, const Fleet& f) {
    return f.print(o);
}


