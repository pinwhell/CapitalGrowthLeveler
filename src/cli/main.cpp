#include <iostream>
#include <thread>
#include <chrono>
#include <CGL.h>

using namespace CGL;

int main() {
    double growthPercentage;
    std::cout << "Enter the per trade risk percentage: ";
    std::cin >> growthPercentage;

    int riskTimeToNextLevel;
    std::cout << "Enter the risk time to reach the next level (in multiples of n): ";
    std::cin >> riskTimeToNextLevel;

    CapitalGrowthLeveler leveler(Perc2Raw(growthPercentage), riskTimeToNextLevel);

    while (true) {
        double accountSize;

        std::cout << "Enter the account size: ";
        std::cin >> accountSize;

        double stopLossPerc;

        std::cout << "Enter stop loss Percentage: ";
        std::cin >> stopLossPerc;

        const double currLevel = CurrentLevelFind(leveler, accountSize);
        const double nextLevel = NextLevelGet(leveler, currLevel);

        const double currLevelPosSize = CurrentLevelPositionSize(leveler, accountSize, Perc2Raw(stopLossPerc));

        std::cout << "\nResults:\n";
        std::cout << "Current Level : " << currLevel << std::endl;
        std::cout << "Account Size  : " << accountSize << std::endl;
        std::cout << "Next Level    : " << nextLevel << std::endl;
        std::cout << "Position Size : " << currLevelPosSize << std::endl;

        char choice;
        std::cout << "\nDo you want to continue? (y/n): ";
        std::cin >> choice;

        if (choice != 'y' && choice != 'Y') {
            std::cout << "Exiting...\n";
            break;
        }
        else {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    return 0;
}