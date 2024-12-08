#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

struct Skill {
    string name;
    string type;
    int damage;
    int maxTry;
    int remainingTry;
};

struct Pokemon {
    string name;
    string type;
    int maxHP;
    int currentHP;
    vector<Skill> skills;
};

// Type effectiveness chart
int getEffectiveness(const string& attackType, const string& defenderType) {
    if ((attackType == "Ground" && defenderType == "Electric") ||
        (attackType == "Ground" && defenderType == "Fire") ||
        (attackType == "Electric" && defenderType == "Water") ||
        (attackType == "Water" && defenderType == "Ground") ||
        (attackType == "Water" && defenderType == "Fire") ||
        (attackType == "Fire" && defenderType == "Grass") ||
        (attackType == "Grass" && defenderType == "Water")) {
        return 5; // Super effective
    } else if ((attackType == "Ground" && defenderType == "Grass") ||
               (attackType == "Electric" && defenderType == "Ground") ||
               (attackType == "Electric" && defenderType == "Electric") ||
               (attackType == "Electric" && defenderType == "Grass") ||
               (attackType == "Water" && defenderType == "Water") ||
               (attackType == "Water" && defenderType == "Grass") ||
               (attackType == "Fire" && defenderType == "Water") ||
               (attackType == "Fire" && defenderType == "Fire") ||
               (attackType == "Grass" && defenderType == "Ground") ||
               (attackType == "Grass" && defenderType == "Grass") ||
               (attackType == "Grass" && defenderType == "Fire")) {
        return -3; // Not very effective
    }
    return 0; // Effective
}