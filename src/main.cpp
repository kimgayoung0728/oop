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