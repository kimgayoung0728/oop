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

// Display battle page
void displayBattlePage(const Pokemon& p1, const Pokemon& p2, const string& latestSkill1, const string& latestSkill2, const string& effectiveness1, const string& effectiveness2, bool isPlayer1Turn) {
    cout << "+-------------------------------------------------------------+\n";
    cout << "| 2024-02 Object-Oriented Programming Pokemon Master          |\n";
    cout << "+------------------------------+------------------------------+\n";
    cout << "| " << setw(29) << left << p1.name + (isPlayer1Turn ? " (*)" : "")
         << "| " << setw(29) << left << p2.name + (!isPlayer1Turn ? " (*)" : "") << "|\n";
    cout << "| Type: " << setw(23) << left << p1.type
         << "| Type: " << setw(23) << left << p2.type << "|\n";
    cout << "| HP: " << setw(25) << left << p1.currentHP
         << "| HP: " << setw(25) << left << p2.currentHP << "|\n";
    cout << "+------------------------------+------------------------------+\n";
    cout << "| Latest Skill: " << setw(15) << left << latestSkill1
         << "| Latest Skill: " << setw(15) << left << latestSkill2 << "|\n";
    cout << "| " << setw(29) << left << effectiveness1
         << "| " << setw(29) << left << effectiveness2 << "|\n";
    cout << "+------------------------------+------------------------------+\n";
    for (int i = 0; i < 4; ++i) {
        cout << "| (" << i << ") " << setw(25) << left << p1.skills[i].name
             << "| (" << i << ") " << setw(25) << left << p2.skills[i].name << "|\n";
        cout << "|     - Type: " << setw(17) << left << p1.skills[i].type
             << "|     - Type: " << setw(17) << left << p2.skills[i].type << "|\n";
        cout << "|     - Damage: " << setw(15) << left << p1.skills[i].damage
             << "|     - Damage: " << setw(15) << left << p2.skills[i].damage << "|\n";
        cout << "|     - Count: " << setw(16) << left << (to_string(p1.skills[i].remainingTry) + "(" + to_string(p1.skills[i].maxTry) + ")")
             << "|     - Count: " << setw(16) << left << (to_string(p2.skills[i].remainingTry) + "(" + to_string(p2.skills[i].maxTry) + ")") << "|\n";
        
    
    }
    cout << "+------------------------------+------------------------------+\n";
}

// Choose a Pokémon
pair<Pokemon, Pokemon> choosePokemon(const vector<Pokemon>& pokemons) {
    int choice1, choice2;
    cout << "Choose a Pokemon(0~4): ";
    cin >> choice1;
    cout << "Choose a Pokemon(0~4): ";
    cin >> choice2;

    if (choice1 == choice2) {
        cout << "You have to choose Pokemons different from each other." << endl;
        exit(0);
    }

    return {pokemons[choice1], pokemons[choice2]};
}

// Choose a skill
int chooseSkill(const Pokemon& pokemon) {
    int choice;
    do {
        cout << "Choose a skill (0~3): ";
        cin >> choice;
        if (pokemon.skills[choice].remainingTry == 0) {
            cout << pokemon.name << " failed to perform " << pokemon.skills[choice].name << ".\n";
            cout<< "\n";
            return -1; // Skill cannot be used, skip turn
        }
    } while (choice < 0 || choice > 3);

    return choice;
}

// Battle logic
void battle(Pokemon& p1, Pokemon& p2) {
    string latestSkill1 = "-", latestSkill2 = "-";
    string effectiveness1 = "", effectiveness2 = "";
    bool isPlayer1Turn = true;

    while (p1.currentHP > 0 && p2.currentHP > 0) {
        // Display battle page
        displayBattlePage(p1, p2, latestSkill1, latestSkill2, effectiveness1, effectiveness2, isPlayer1Turn);

        if (isPlayer1Turn) {
            // Player 1's turn
            int choice = chooseSkill(p1);
            if (choice != -1) {
                Skill& skill = p1.skills[choice];
                int effectiveness = getEffectiveness(skill.type, p2.type);
                int damage = skill.damage;
                if (effectiveness == 5) {
                    damage += 5;
                } else if (effectiveness == -3) {
                    damage -= 3;
                }
                p2.currentHP = max(0, p2.currentHP - damage);
                skill.remainingTry--;
                latestSkill1 = skill.name;
                effectiveness1 = (effectiveness == 5) ? "It was super effective." : (effectiveness == -3) ? "It was not very effective." : "It was effective.";
                cout << p1.name << " used " << skill.name << ".\n";
                cout << effectiveness1 << "\n";
                cout << "\n";
            }
        } 