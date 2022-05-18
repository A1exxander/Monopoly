
#include <iostream>
#include <array>
#include <vector>
#include <list>
#include <random>

class Player {
private:
    enum class playerTypes { // We wouldnt use inheritance since the only thing that changes is the playerType, the functionality will remain identical, maybe enum is not a good idea either since availible players can change, it is not fixed
        tinHat,
        thimble,
        iron,
        shoe,
        battleship,
        cannon
    };

    playerTypes playerType{};
    int money{};
    int currentPosition{};
    bool convict{}; // No need to keep track of how long you will be in jail for, since you will be imprisoned and then when its your turn, you will get skipped but also released right after skip

public:

    Player() {

        money = 2500;

    }

    std::string getPlayerType() {

        switch (playerType) {
        case playerTypes::tinHat:
            return "TinHat";
        case playerTypes::thimble:
            return "Thimble";
        case playerTypes::iron:
            return "Iron";
        case playerTypes::shoe:
            return "Shoe";
        case playerTypes::battleship:
            return "Battleship";
        case playerTypes::cannon:
            return "Cannon";

        }
    }

    void setPlayerType(int number) {

        playerType = static_cast<playerTypes>(number);

    }

    void selectPlayerType(const std::vector<Player>& takenPlayers) {

        constexpr int maxPlayerCount{ 6 };

        if (takenPlayers.size() >= maxPlayerCount) {

            std::cout << "\nNo availible players!";

        }
        else { // This code is kinda bad, doesnt work atm
            std::vector<std::string> availiblePlayers{ "TinHat", "Thimble",  "Iron", "Shoe", "Battleship", "Cannon" };
            int choice{};

            /*for (auto i{ 0 }; i < availiblePlayers.size(); ++i) {

                for (auto j{ 0 }; i < takenPlayers.size(); ++j) {

                    if (takenPlayers[j].getPlayerType() == availiblePlayers[i]) {

                        availiblePlayers.erase(availbilePlayers.begin() + i);

                    }

                }

            }*/

            std::cout << "\nSelect a player by entering a number from 1 - " << availiblePlayers.size() << " : ";

            for (auto i{ 0 }; i < availiblePlayers.size(); ++i) {

                std::cout << i + 1 << availiblePlayers[i] << " ";

            }
            std::cin >> choice;

            while (choice > availiblePlayers.size()) {

                std::cout << "\nError! Please enter a number from 0 - " << availiblePlayers.size() << " : ";
                std::cin >> choice;

            }

            --choice;

            setPlayerType(choice);

        }
    }

    void modifyMoney(int amount) {

        money += amount;

    }

    int getPlayerMoney() {
    
        return money;

    }

    int getCurrentPosition() {
    
        return currentPosition;

    }

    void moveCurrentPosition(int roll) {
    
        currentPosition += roll;
        currentPosition % 5; // Or size of board passed thru

    }

    void imprision() {
    
        convict = true;

    }

    void release() {
    
        convict = false;

    }

    bool isConvict() {

        return convict;

    }

};

class Monopoly {
private:
    
    struct tile { // Thought of making a class called tile to use as a base for PrisonTile & PlayerTile, but realized that you wouldnt be able to upcast it as the datamembers and function you would need would be apart of the derived class
        Player* owner{ nullptr };
        std::string tileName{ "" };
        int costToBuy{};
        int landingPayment{};
    };
    std::array<tile, 5> board{}; 
    // std::array<void*, 5> testboard{}; Maybe we could have an array of void pointers to classes that inherit base Tile then check if getTittleName returns "Prison", then we call prison related methods, else we call playerTittle related methods?
    std::vector<Player> Players{};
public:

    void addPlayers(int num) {

        for (auto i{ 0 }; i < num; ++i){

            Player current{};
            
            current.selectPlayerType(Players);

            Players.push_back(current);

        }
    }
    
    int rollDice(){
        static std::mt19937 rand; // Will always be used once initilized + yields more random results due to seed not being the same default, therefore better to make static
        int roll{ rand() % 6 };

        return roll;

    }

    void game() {
    
        addPlayers(5);

        while (Players.size() > 1) {
             
        
            for (auto i{ 0 }; i < Players.size(); ++i) {

                if (Players[i].isConvict()) {
                
                    std::cout << "\nIn prision for 1 more round!";
                    Players[i].release();
                    ++i;

                }

                int roll{ rollDice() };

                std::cout << "\n Rolled " << roll;
            
                Players[i].moveCurrentPosition(roll);

                if (board[i].owner == nullptr && board[i].tileName != "Prison") {
                    if (Players[i].getPlayerMoney() > board[i].landingPayment) {

                        Players[i].modifyMoney(-board[i].landingPayment);
                        board[i].owner->modifyMoney(board[i].landingPayment);

                    }

                    else {
                    
                        board[i].owner->modifyMoney(Players[i].getPlayerMoney());

                        std::cout << "\nPlayer " << Players[i].getPlayerType() << " has been eliminated! ";

                        Players.erase(Players.begin() + i);

                    }

                }
                else if (board[i].owner->getPlayerType() == Players[i].getPlayerType()){

                    std::cout << "\nLanded on your tile " << Players[i].getCurrentPosition();
                    
                }

                else if (board[i].tileName == "Prison") {
                
                    Players[i].imprision();
                    std::cout << "\nInprisoned for 2 rounds";

                }

                else {
                
                    std::cout << "\nError! Invalid move! Reverted position ";
                    Players[i].moveCurrentPosition(-roll);

                }

            }

        }

    }


};

int main()
{
    

}


