#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <atomic>

using namespace std;

class Alcohol {
public:
    string name;
    int stabilityLoss;

    Alcohol(string n, int loss) : name(n), stabilityLoss(loss) {}
};

class Shop {
public:
    Alcohol drinks[4] = {
        Alcohol("Pirinsko", 5),
        Alcohol("Vodka Platinum", 9),
        Alcohol("Rakiq", 13),
        Alcohol("Geiger Meister", 18)
    };
    int selectedDrinkIndex = -1;

    void showDrinks() {
        cout << "\n=============== SHOP ===============\n";
        for (int i = 0; i < 4; i++) {
            cout << (i + 1) << ". " << drinks[i].name << " | Stability Loss: " << drinks[i].stabilityLoss << "\n";
        }
        cout << "5. Back to Main Menu\n";
        cout << "=========================================\n";
        cout << "Please choose a drink: ";
    }

    void selectDrink(int index) {
        selectedDrinkIndex = index;
        cout << "You have selected " << drinks[selectedDrinkIndex].name << ".\n";
    }

    Alcohol& getSelectedDrink() {
        return drinks[selectedDrinkIndex];
    }
};

class Skill {
public:
    int drinking;
    int stability; 
    int maxStability; 
    int skillpoint;
    bool recoveryActive;

    Skill() : drinking(0), stability(100), maxStability(100), skillpoint(0), recoveryActive(false) {}

    void displaySkills() const {
        cout << "Drinking: " << drinking << "/10\n";
        cout << "Stability: " << stability << "/" << maxStability << "\n";
    }

    void upgradeDrinking() {
        if (drinking < 10 && skillpoint > 0) {
            drinking++;
            skillpoint--;
            cout << "Drinking skill increased!\n";
        } else {
            cout << "Drinking skill is already at maximum or no skill points available.\n";
        }
    }

    void upgradeStability() {
        if (skillpoint > 0) {
            maxStability += 25;
            skillpoint--;
            cout << "Max stability increased!\n";
        } else {
            cout << "No skill points available.\n";
        }
    }

    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            file << drinking << " " << stability << " " << maxStability << " " << skillpoint; 
            file.close();
            cout << "Skills saved successfully!" << endl;
        }
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            file >> drinking >> stability >> maxStability >> skillpoint; 
            if (stability < 0) {
                stability = 0; 
            }
            file.close();
            cout << "Skills loaded successfully!" << endl;
        } else {
            cout << "No previous skill data found. Starting fresh." << endl;
        }
    }
};

class Level {
public:
    int levels;
    double levelpoints;

    Level() : levels(0), levelpoints(0) {}

    void level_up() {
        while (levelpoints >= 100) {
            levels++;
            levelpoints -= 100;
        }
    }

    void displayLevel() const {
        cout << "Your Level: " << levels << " | Entry points: " << levelpoints << "/100\n";
    }

    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            file << levels << " " << levelpoints;
            file.close();
            cout << "Level data saved successfully!" << endl;
        }
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            file >> levels >> levelpoints;
            file.close();
            cout << "Level data loaded successfully!" << endl;
        } else {
            cout << "No previous level data found. Starting fresh." << endl;
        }
    }
};

class Game {
public:
    bool gameOver = false;
    int a = 3; // Начална стойност на a

    void startGame(Skill &skillsystem, Level &levelsystem, Alcohol &drink) {
        cout << "Starting the game... You need to drink " << drink.name << " to increase your drinking skill!\n";

        while (!gameOver) {
            cout << "Press Enter to drink " << drink.name << "...";
            cin.ignore();
            cin.get();

            skillsystem.stability -= drink.stabilityLoss; // Вземане на стабилност
            cout << "You drank " << drink.name << "! Stability decreased to: " << skillsystem.stability << "/" << skillsystem.maxStability << "\n";

            if (skillsystem.stability <= 0) {
                skillsystem.stability = 0;
                cout << "You have lost all stability! Game over.\n";
                gameOver = true;
            } else {
                a *= (1 << skillsystem.drinking); // Увеличава a в зависимост от нивото на пиене
                levelsystem.levelpoints += a; // Увеличаване на точки за ниво
                levelsystem.level_up();
                levelsystem.displayLevel();
                skillsystem.displaySkills();
            }
        }
    }
};

class Menu {
public:
    void showMenu() {
        cout << "=============== GAME MENU ===============\n";
        cout << "1. Start Game\n";
        cout << "2. Settings\n";
        cout << "3. Shop\n";
        cout << "4. View Level and Skills\n";
        cout << "5. Upgrade Skills\n";
        cout << "6. Exit\n";
        cout << "=========================================\n";
        cout << "Please choose an option: ";
    }

    void showShop(Shop &shop) {
        shop.showDrinks();
    }

    void showSettings(Skill &skillsystem) {
        cout << "\n=============== SETTINGS ===============\n";
        cout << "1. Start Stability Recovery\n";
        cout << "2. Upgrade Max Stability\n";
        cout << "3. Back to Main Menu\n";
        cout << "=========================================\n";
        cout << "Please choose an option: ";
        
        int settingOption;
        cin >> settingOption;
        if (settingOption == 1) {
            skillsystem.recoveryActive = true;
            cout << "Stability recovery started. You will gain 1 stability per second.\n";
            // Може да добавите поток за възстановяване тук, ако желаете.
        } else if (settingOption == 2) {
            skillsystem.upgradeStability();
        }
    }
};

int main() {
    Level levelsystem;
    Skill skillsystem;
    Menu menu;
    Game game;
    Shop shop;

    // Зареждане на данни
    levelsystem.loadFromFile("level_data.txt");
    skillsystem.loadFromFile("skills_data.txt");

    int option;
    while (true) {
        menu.showMenu();
        cin >> option;

        switch (option) {
            case 1: {
                if (shop.selectedDrinkIndex != -1) {
                    game.startGame(skillsystem, levelsystem, shop.getSelectedDrink());
                } else {
                    cout << "Please select a drink from the shop first.\n";
                }
                break;
            }
            case 2: {
                menu.showSettings(skillsystem);
                break;
            }
            case 3: {
                menu.showShop(shop);
                int drinkOption;
                cin >> drinkOption;
                if (drinkOption >= 1 && drinkOption <= 4) {
                    shop.selectDrink(drinkOption - 1);
                } else {
                    cout << "Returning to main menu.\n";
                }
                break;
            }
            case 4:
                skillsystem.displaySkills();
                levelsystem.displayLevel();
                cout << "Press Enter to continue...\n";
                cin.ignore();
                cin.get();
                break;
            case 5: {
                if (skillsystem.skillpoint > 0) {
                    cout << "Choose skill to upgrade:\n1. Drinking\n2. Stability\n";
                    int skillOption;
                    cin >> skillOption;
                    if (skillOption == 1) {
                        skillsystem.upgradeDrinking();
                    } else if (skillOption == 2) {
                        skillsystem.upgradeStability();
                    } else {
                        cout << "Invalid option.\n";
                    }
                } else {
                    cout << "No skill points available.\n";
                }
                break;
            }
            case 6:
                skillsystem.saveToFile("skills_data.txt");
                levelsystem.saveToFile("level_data.txt");
                cout << "Exiting the game. Your progress has been saved.\n";
                return 0;
            default:
                cout << "Invalid option. Please try again.\n";
                break;
        }
    }
}


/*
Task
#1 Fix gaint stabilty at settings menu
#2 Chek if skill porint is fixed
#3 Fix starting stability form 100 to 0
#4 Check if there is another problem
#5 Boss in game. First Boss is Qnkata toi shte pie pirinsko negowoto pirisnko mu e 16 ot staminata a ne kato tebe 100 stabiliti .
#6 Naprawi pari w igrata i sus wseki pobeden boss da moje da  poluchawash nqkwi kinti neka da e neshto kato obloji da zalagash shte ima neshto kato goworene. I taka s tezi pari shte mojesh da si kopuwash nowi alkholi.
*/ 

               
