#include <iostream>
#include <string>
#include <cstdlib>
#include <random>
#include <cmath>
#include <ncurses.h>
#include <fstream>


using namespace std;

class items{//took about 4 hours so far
    public:
    string sword_name = "Wooden Sword";
    int sword_strength = 2;
    char swordRarity = 'C';

    string armor_name = "Leather armor";
    int armor_strength = 2;
    char armor_Rarity = 'C';

    int potions = 0;
    
    void itemDrop(char rarity,int lvl){
        int seed= rand() % 100 + 1;
        if (seed >= 75){
            swordDrop(rarity,lvl);
        }
        else if (seed >= 50){
            armorDrop(rarity,lvl);
        }
        else{
            cout<<"no items were dropped"<<endl;
        }
    }
    void armorDrop(char rarity, int lvl){
        int newArmor;
        switch (rarity) {
        case 'C':
        newArmor = lvl*5;
        break;
        case 'U':
        newArmor = lvl*6;
        break;
        case 'R':
        newArmor = lvl*7;
        break;
        case 'E':
        newArmor = lvl*8;
        break;
        case 'L':
        newArmor = lvl*9;
        break;
        case 'M':
        newArmor = lvl*12;
        break;
        }
        if (newArmor>=armor_strength){
            armor_strength= newArmor;
            armor_Rarity=rarity;
            cout<<"new armor strength is "<<armor_strength<<endl;
            cout<<"new armor Rarity is "<<armor_Rarity<<endl;
        }
 
        }
    
    
    void swordDrop(char rarity, int lvl){
        int newSword;
        switch (rarity) {
        case 'C':
        newSword = lvl*5;
        break;
        case 'U':
        newSword = lvl*6;
        break;
        case 'R':
        newSword = lvl*7;
        break;
        case 'E':
        newSword = lvl*8;
        break;
        case 'L':
        newSword = lvl*9;
        break;
        case 'M':
        newSword = lvl*12;
        break;
        }
        if (newSword>=sword_strength){
            sword_strength= newSword;
            swordRarity=rarity;
            cout<<"new sword strength is "<<sword_strength<<endl;
            cout<<"new sword Rarity is "<<swordRarity<<endl;
        }
    }
    

};

class Tile {// with map took 5 hours
public:
    char type;
    char rarity;

    Tile() {
        
        int seed= rand() % 100 + 1;
        if (seed >= 50) {
            type = '_';
            rarity = 'C';
        } 
        else if (seed >= 25) {
            type = 'E';
            rarity = rarity_init();
        } 
        else if (seed >= 10) {
            type = 'H';
        } 
        else if (seed >= 5) {
            type = 'B';
            rarity = rarity_init();
        } 
        else {
            type = 'T';
            rarity = 'L';
        }
    }
    char rarity_init(){
        int chance= rand() % 100 + 1;
        if (chance>=50){
            return 'C';//common
        }
        else if(chance>=25){
            return 'U';//uncommon
        }
        else if(chance >=10){
            return 'R';//rare
        }
        else{
            return 'E';//epic
        }
    }
};



class Hero{ //should rename to a stats class, since this class mainly consists of all of the stats used within the game
    public: // also this class took about 7 hours
        items heroItems;
        int pMaxHealth = 10;
        int pHealth = pMaxHealth;
        int pAttack = 5;
        int pLevel = 1;
        int exp = 0;
    void printStats(){
        cout<<"current health is "<<pHealth<<"/"<<pMaxHealth<<endl<<
        "attack: "<<pAttack<<endl<<
        "level: "<<pLevel<<endl<<
        "exp: "<<exp<<"/"<<pow(2,pLevel)<<endl<<
        "You have: "<<heroItems.potions<<" potions"<<endl<<
        "sword added base damage is "<<heroItems.sword_strength<<" and rarity is "<<heroItems.swordRarity<<endl<<
        "Armor added base Protection is "<<heroItems.armor_strength<<" and rarity is "<<heroItems.armor_Rarity<<endl;
    }
    int enemyLvlInit(){
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> distribution(0, pLevel-1);
        int enemyLevel = distribution(gen);
        return enemyLevel;
    }
    int enemyHealthInit(int elvl){
        int eHealth = 12*elvl + 3;
        return eHealth; 
    }
    int enemyAttackInit (int elvl){
        int eAttack = 4*elvl +2;
        return eAttack;
    }
    int bossHealthInit(int lvl){
        return (15*lvl+5);
    }
    int bossAttackInit(int lvl){
        return (6*lvl+1);
    }
    int getAttack(){
        int choice;
        int damage= heroItems.sword_strength;
        int chance;
        cout<<
        "Your choices for attack are:"<<endl<<
        "enter 1 for: Safe swing, 100% accuracy, deals 1x your attack :"<<pAttack<<" damage"<<endl<<
        "enter 2 for: Fast swing, 80% accuracy 1.5x attack: "<<pAttack*1.5<<" damage"<<endl<<
        "enter 3 for: Dangerous swing, 50% accuracy 4x damage, but you also lose 25% of your health(eve if it does not hit)"<<pAttack*4<<" damage"<<endl<<
        "enter 4 for: heal, deal no damage, if there is a potion, you go to full health"<<endl;
    
        cin>>choice;
        switch (choice) {
        case 1:
            cout << "You chose safe swing" <<endl;
            damage += pAttack;
            cout<<"your attack hit for "<<damage<<" damage"<<endl;

            break;
        case 2:
            cout << "You chose fast swing" <<endl;
            chance= rand() % 100 + 1;
            if (chance>=20){
                damage += pAttack*1.5;
                cout<<"your attack hit for "<<damage<<" damage"<<endl;
            }
            else{
                cout<<"attack missed"<<endl;
                damage += 0;
            }

            break;
        case 3:
            cout << "You chose dangerous swing" << endl;
            chance= rand() % 100 + 1;
            if (chance>=50){
                damage += pAttack*4;
                pHealth = pHealth*.75;
                cout<<"your attack hit for "<<damage<<" damage"<<endl;
            }
            else{
                cout<<"attack missed"<<endl;
                damage = 0;
            }

            break;
        case 4:
                if (heroItems.potions>=1){
                    pHealth = pMaxHealth;
                    heroItems.potions--;
                    
                }
                else{
                    cout<<"you have no more potions"<<endl;
                }
                damage = 0;

                break;
        default:
            cout << "Invalid choice" << endl;
            damage = 0;
            break;
    
    }
    return damage;
    }
    void battleEnemy(char rarity){
        int enemyLvl = enemyLvlInit();
        int enemyAttack = enemyAttackInit(enemyLvl);
        int enemyHealth = enemyHealthInit(enemyLvl);
        int chance;
        system("clear");
        cout<<"you have confronted a level: "<<enemyLvl<<" enemy! \nYou must battle it to continue."<<endl;
        while (enemyHealth >0 && pHealth >0){
            printStats();
            cout<<
            "enemyHealth: "<<enemyHealth;
            enemyHealth = enemyHealth - getAttack();
            if (enemyHealth> 0){
                random_device rd;
                mt19937 gen(rd());
                uniform_int_distribution<int> distribution(0, 100);
                chance= distribution(gen);
                if (chance<=25){
                    cout<<"enemy attack missed"<<endl;
                }
                else{
                    if (enemyAttack> heroItems.armor_strength){
                    cout<<"enemy hit for "<<enemyAttack<<" damage"<<endl;
                    pHealth -=enemyAttack-heroItems.armor_strength;
                    }
                    else{
                        cout<<"the enemy was not strong enough to deal damage to you";
                    }
                }
            }
        }
        aliveCheck();
        exp += enemyLvl * 4+2;
        cout<<"you gained "<<enemyLvl * 4+2<<" exp!"<<endl;
        levelUpCheck();
        heroItems.itemDrop(rarity, pLevel);
    }
    void battleBoss(char rarity){
        int bossLvl=pLevel;
        int bossAttack =bossAttackInit(bossLvl);
        int bossHealth = bossHealthInit(bossLvl);
        int chance;
        system("clear");
        cout<<"you have confronted a level: "<<bossLvl<<" boss! \nYou must battle it to continue."<<endl;
        while (bossHealth >0 && pHealth >0){
            printStats();
            cout<<"the boss's stats are: "<<endl<<"Attack: "<<bossAttack<<endl<<
            "Health: "<<bossHealth;
            bossHealth = bossHealth - getAttack();
            if (bossHealth> 0){
                random_device rd;
                mt19937 gen(rd());
                uniform_int_distribution<int> distribution(0, 100);
                chance = distribution(gen);
                    pHealth-=bossAttack*(chance+1)-heroItems.armor_strength ;// there is a possible bug where you could heal from a bosses attack but I assume this is very unlikely to happen since you should not be able to get strong enough armor to do that
                }
            }
        
        aliveCheck();
        exp += bossLvl * 4+2;
        cout<<"you gained "<<bossLvl * 4+2<<" exp!"<<endl;
        levelUpCheck();
        heroItems.itemDrop(rarity, pLevel);
    }
    void levelUpCheck(){
        if (exp >= pow(2,pLevel)){
            levelUp();
        }
    }
    void levelUp(){
        exp -= pow(2,pLevel);
        pAttack += 3;
        pMaxHealth +=5;
        pLevel +=1;
        cout<<"you leveled up!"<<endl<<"your new attack is: "<<pAttack<<endl<<"your new max health is: "<<pMaxHealth<<endl;
        levelUpCheck();
    }
    void aliveCheck(){
        if (pHealth<=0){
            cout<<"you died in battle"<<endl;
            exit(1
            );
        }
    }
    void treasure(){//work on more later
        int chance= rand() % 100 + 1;
        if (chance>=75){
            battleEnemy('L');
        }
        else if(chance>=50){
            battleBoss('M');
        }
        else{
            cout<<"empty treasure room!";
            heroItems.itemDrop('M', pLevel);
        }
    }

};

class Map {
public:
    vector<vector<Tile>> tileGrid;
    int playerX=0;
    int playerY=0;


    Hero hero;
    Map(int rows, int cols) {
        for (int i = 0; i < rows; i++) {
            vector<Tile> row;
            for (int j = 0; j < cols; j++) {
                row.push_back(Tile());
            }
            tileGrid.push_back(row);
        }
    }
    void printBoard(){
    system("clear");
    for (const auto& row : tileGrid) {
        for (const Tile& tile : row) {
            if (tile.type == 'P'){
                cout<<"ඞ"<< " ";
            }
            else{
            cout << tile.type << ' ';
            }
        }
        cout << endl;
        
    }
    }
   bool isValidMove(int x, int y) {
        return x >= 0 && x < tileGrid[0].size() && y >= 0 && y < tileGrid.size();
    }

    void move(char direction) {
        int dx = 0, dy = 0;
        cout<<direction<<endl;
        switch (direction) {
            case 'W':
            case 'w':
                dy = -1;
                break;
            case 'S':
            case 's':
                dy = 1;
                break;
            case 'A':
            case 'a':
                dx = -1;
                break;//thanks to my friend angelo who told me i am mhs!!
            case 'D':
            case 'd':
                dx = 1;
                break;
            case 'H'://doesn;t work idk why
            case 'h':
                cout<<"nuts";
                if (hero.heroItems.potions>1){
                    hero.pHealth = hero.pMaxHealth;
                    hero.heroItems.potions--;
                    
                }
                else{
                    cout<<"you have no more potions"<<endl;
                }
                break;
            default:
                return;
        }
        int newX = playerX + dx;
        int newY = playerY + dy;

        if (isValidMove(newX, newY)) {

            tileGrid[playerY][playerX].type = '_';

            playerX = newX;
            playerY = newY;
            if (tileGrid[playerY][playerX].type!='_'){
                colision(playerX, playerY);
            }
            tileGrid[playerY][playerX].type = 'P';
        }
    }
    void colision(int x, int y){
        string filler;
        switch (tileGrid[y][x].type){
            case 'E':
            system("clear");
            hero.battleEnemy(tileGrid[y][x].rarity);
            cout<<"you successfully slayed the enemy \nenter anything to continue"<<endl;
            cin>>filler;
            break;

            case 'H':
            system("clear");
            hero.pHealth = hero.pMaxHealth;
            hero.heroItems.potions+=1;
            cout<<"you successfully healed yourself \nenter anything to continue"<<endl;
            break;
        
            case 'B':
            system("clear");
            hero.battleBoss(tileGrid[y][x].rarity);
            cout<<"you successfully defeated the boss \nenter anything to continue"<<endl;
            cin>>filler;
            break;
        
            case 'T':
            system("clear");
            hero.treasure();
            cout<<"treasure room cleared \nenter anything to continue";
            cin>>filler;
            break;

            
        
        }
    }

};
void saveDataToFile(int health, int maxHealth, int level, int attack,int playerX, int playerY, 
int armorStat, char armorRare, string armorName,
int swordStat, char swordRare, string swordName
){
    ofstream outFile("saveFile.txt");
    if (outFile.is_open()) {
        // Write data to the file
        outFile << health << endl<<maxHealth<<endl<<level<<endl<<attack<<endl<<
        playerX<<endl<<playerY<<endl<<
        armorStat<<endl<<armorRare<<endl<<armorName<<endl<<
        swordStat<<endl<<swordRare<<endl<<swordName<<endl;

        // Close the file
        outFile.close();
        exit(0);
        cout << "Data saved to " << "saveFile.txt" << " successfully." <<endl;
    } else {
        cout << "Unable to open the file: " << "saveFile.txt" <<endl;
    }
}



int main() {
    int maxX=40;
    int maxY=40;
    char userInput;
    
    Map map(maxX, maxY);
    map.tileGrid[0][0].type = 'P';
    map.tileGrid[maxY-1][maxX-1].type= 'S';
    cout<<"if you already have a save file input y";
    cin>>userInput;
    if (userInput == 'y'){
        ifstream inputFile("saveFile.txt"); 

        if (!inputFile.is_open()) {
            cerr << "Error opening file." << endl;
        }

    
    // Read and assign values
    while (inputFile >> map.hero.pHealth >> map.hero.pMaxHealth >> map.hero.pLevel >> map.hero.pAttack >> 
    map.playerX >> map.playerY >> map.hero.heroItems.armor_strength >> map.hero.heroItems.armor_Rarity>>map.hero.heroItems.armor_name>>
    map.hero.heroItems.sword_strength>>map.hero.heroItems.swordRarity>>map.hero.heroItems.sword_name); {
        map.tileGrid[0][0].type = '_';
        map.tileGrid[map.playerY][map.playerX].type = 'P';
    }
        
    }
    
    map.printBoard();
    map.hero.printStats();

    while (true) {
        cin >> userInput;
        if (userInput == 'o'){
            saveDataToFile(map.hero.pHealth, map.hero.pMaxHealth,map.hero.pLevel,map.hero.pAttack,
            map.playerX,map.playerY,map.hero.heroItems.armor_strength,map.hero.heroItems.armor_Rarity, map.hero.heroItems.armor_name,
            map.hero.heroItems.sword_strength,map.hero.heroItems.swordRarity,map.hero.heroItems.sword_name);}
        map.move(userInput);
        map.printBoard();
        map.hero.printStats();
    }

    return 0;
}
