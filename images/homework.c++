// Description: C++ homework
// Author: enoch omobolaji flourish
// Date: 03/06/2024
// student number: 220201722 


#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Character {
protected:
    string name;
    int level;
    int health;
    int experience;

public:
    Character(string name, int level, int health, int experience) 
        : name(name), level(level), health(health), experience(experience) {}

    virtual ~Character() {
        cout << "Destroying " << name << "..." << endl;
    };

    virtual void displayStats() {
        cout << "Name: " << name << endl;
        cout << "Level: " << level << endl;
        cout << "Health: " << health << endl;
        cout << "Experience: " << experience << endl;
    }

    virtual void attack() = 0;
    virtual void defend() = 0;

    void levelUp() {
        level++;
        health += 10;
        experience += 100;
   }
    const string& getName() const {
        return name;
    }

    int getHealth() const {
        return health;
    }

    void reduceHealth(int amount) {
        health -= amount;
    }
};

class Knight : public Character {
protected:
    int strength;
    int defense;

public:
    Knight(string name, int level, int health, int experience, int strength, int defense) 
        : Character(name, level, health, experience), strength(strength), defense(defense) {}

        void displayStats() {
            Character::displayStats();
            cout << "Strength: " << strength << endl;
            cout << "Defense: " << defense << endl;
        }

        void attack() {
            cout << name << " attacks with " << strength << " strength!" << endl;
        }

        void defend() {
            cout << name << " defends with " << defense << " defense!" << endl;
        }

        void shieldblock() {
            cout << name << " uses shieldblock!" << endl;
            defense += 10;
        }

        void displaySpecialAbility() {
            cout << "Special ability: " << name << " can increase defense by 10." << endl;
        }
    };

    class Archer : public Character {
    private:
        int strength;
        int defense;
        int stamina;
        int weaponSkill;

    public:
        Archer(string name, int level, int health, int experience, int strength, int defense, int stamina, int weaponSkill) 
            : Character(name, level, health, experience), strength(strength), defense(defense), stamina(stamina), weaponSkill(weaponSkill) {}

        void attack() {
            cout << name << " attacks with strength " << strength << " and weapon skill " << weaponSkill << "!" << endl;
        }

        void defend() {
            cout << name << " defends with defense " << defense << " and stamina " << stamina << "!" << endl;
        }

        void specialArrow() {
            cout << name << " uses special arrow!" << endl;
            defense += 5;
            stamina -= 1;
        }
    };

    class Assassin : public Character {
    private:
        int speed;
        int backstabDamage;
        int criticalHit;

    public:
        Assassin(string name, int level, int health, int experience, int speed, int backstabDamage, int criticalHit) 
            : Character(name, level, health, experience), speed(speed), backstabDamage(backstabDamage), criticalHit(criticalHit) {}

        void displayStats()  {
            Character::displayStats();
            cout << "Speed: " << speed << endl;
            cout << "Backstab Damage: " << backstabDamage << endl;
            cout << "Critical Hit: " << criticalHit << endl;
        }

        void attack () {
            cout << name << " attacks with speed " << speed << " and backstab damage " << backstabDamage << "!" << endl;
        }

        void defend() {
            cout << name << " defends with speed " << speed << " and critical hit " << criticalHit << "!" << endl;
        }

        void backstab() {
            cout << name << " uses backstab!" << endl;
        }
    };

    class Ranger : public Character {
    private:
        int agility;
        int accuracy;

    public:
        Ranger(string name, int level, int health, int experience, int agility, int accuracy) 
            : Character(name, level, health, experience), agility(agility), accuracy(accuracy) {}

        void attack() {
            cout << name << " attacks with accuracy " << accuracy << "!" << endl;
        }

        void defend() {
            cout << name << " defends with agility " << agility << "!" << endl;
        }

        void shootArrow() {
            cout << name << " shoots an arrow!" << endl;
        }

        void stealth() {
            cout << name << " enters stealth mode!" << endl;
        }
    };

    class CharacterManagementSystem {
    private:
        vector<shared_ptr<Character > > characters;

    public:
        void createCharacters() {
            characters.push_back(make_shared<Knight>("Knight", 1, 100, 0, 20, 10));
            characters.push_back(make_shared<Assassin>("Assassin", 1, 80, 0, 50, 30, 40));
            characters.push_back(make_shared<Ranger>("Ranger", 1, 90, 0, 30, 40));
            characters.push_back(make_shared<Archer>("Archer", 1, 90, 0, 25, 35, 30, 40));
        }

        void displayCharacters() {
          for (const auto& character : characters) { character->displayStats(); std::cout << "\n"; }
    }

     void simulateBattles() {
        for (size_t i = 0; i < characters.size(); ++i) {
            for (size_t j = i + 1; j < characters.size(); ++j) {
                std::cout << characters[i]->getName() << " vs " << characters[j]->getName() << ":\n";
                battle(*characters[i], *characters[j]);
                std::cout << "\n";
            }
        }
    }

    void battle(Character& char1, Character& char2) {
        while (char1.getHealth() > 0 && char2.getHealth() > 0) {
            char1.attack();
            char2.reduceHealth(10); 
            char2.defend();

            if (char2.getHealth() <= 0) {
                std::cout << char2.getName() << " has been defeated!\n";
                char1.levelUp();
                break;
            }

            char2.attack();
            char1.reduceHealth(10); 
            char1.defend();

            if (char1.getHealth() <= 0) {
                std::cout << char1.getName() << " has been defeated!\n";
                char2.levelUp();
                break;
            }
        }
    }
};

int main() {
    CharacterManagementSystem cms;
    cms.createCharacters();
    cms.displayCharacters();
    cout << "====================\n";
    cms.simulateBattles();

    return 0;
}
