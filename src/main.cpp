#include <iostream>
#include <limits>
#include "WiFi4Simulator.h"
#include "WiFi5Simulator.h"
#include "WiFi6Simulator.h"

void choice_menu()
{
    std::cout << "--------------------------------------\n";
    std::cout << "--------------------------------------\n";
    std::cout << "--------------------------------------\n";
    std::cout << "   Simulator For Wifi Communication\n";
    std::cout << "--------------------------------------\n";
    std::cout << "--------------------------------------\n";
    std::cout << "--------------------------------------\n";
    std::cout << "Select a Communication Type:\n";
    std::cout << "press 1. WiFi4 \n";
    std::cout << "press 2. WiFi5 \n";
    std::cout << "press 3. WiFi6 \n";
    std::cout << "0. Exit\n";
    std::cout << "*-------------------------------------\n";
    std::cout << "--------------------------------------\n";
    std::cout << "--------------------------------------\n";
    std::cout << "Your Choice: ";
}

// Validated integer input
int getUserInput(const std::string &prompt, int min = 0, int max = std::numeric_limits<int>::max())
{
    int value;
    while (true)
    {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail() || value < min || value > max)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Enter a number b/w " << min << " and " << max << ".\n";
        }
        else
        {
            break;
        }
    }
    return value;
}

int main()
{
    int choice = -1;

    while (choice != 0)
    {
        choice_menu();
        choice = getUserInput("", 0, 3);

        if (choice == 0)
        {
            std::cout << "[Exit] exitt\n";
            break;
        }

        int total_connected_Users = getUserInput("Enter many Users : ", 1); 
        int bandwidth = 20; 

        switch (choice)
        {
        case 1:
            std::cout << "[Start] Initializing WiFi 4...\n\n";
            try
            {
                WiFi4Simulator wifi4Simulator(total_connected_Users, bandwidth);
                wifi4Simulator.executeTest();
            }
            catch (const std::exception &e)
            {
                std::cerr << "[Simulation for Wifi4 : " << e.what() << "\n";
            }
            break;

        case 2:
            std::cout << "[Start]:- Initializing WiFi5 Simulation...\n";
            try
            {
                WiFi5Simulator wifi5Simulator(total_connected_Users, bandwidth);
                wifi5Simulator.executeTest();
            }
            catch (const std::exception &e)
            {
                std::cerr << "[Error]:- WiFi5 Simulation is failed: " << e.what() << "\n";
            }
            break;

        case 3:
            std::cout << "[Start]:-Initializing WiFi6 Simulation\n";
            try
            {
                WiFi6Simulator wifi6Simulator(total_connected_Users, bandwidth);
                wifi6Simulator.executeTest();
            }
            catch (const std::exception &e)
            {
                std::cerr << "[Error]:-WiFi6 Simulation is failed: " << e.what() << "\n";
            }
            break;

        default:
            std::cerr << "Unexpected input.\n";
        }

        std::cout << "------------------------\n";
    }

    return 0;
}
