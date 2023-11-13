#include <iostream>
#include <vector>
#include <string>

struct Train {
    std::string departureTime;
    std::string returnTime;
    int totalPassengers;
    int totalMoney;
    bool isClosed;
};

int calculatePrice(int passengers) {
    int pricePerPassenger = 50; // $25 for up and $25 for down
    int freePassengers = passengers / 10; // every 10th passenger is free
    return (passengers - freePassengers) * pricePerPassenger;
}

void purchaseTickets(std::vector<Train>& trains, int trainIndex, int passengers) {
    if (trains[trainIndex].totalPassengers + passengers > 480) { // 6 coaches * 80 seats
        std::cout << "Sorry, not enough tickets available for this train.\n";
        return;
    }

    int price = calculatePrice(passengers);
    trains[trainIndex].totalPassengers += passengers;
    trains[trainIndex].totalMoney += price;

    if (trains[trainIndex].totalPassengers == 480) {
        trains[trainIndex].isClosed = true;
    }

    std::cout << "Tickets purchased successfully. Total price: $" << price << "\n";
}

void endOfDay(const std::vector<Train>& trains) {
    int totalPassengers = 0;
    int totalMoney = 0;
    int maxPassengers = 0;
    std::string busiestTrain;

    for (const auto& train : trains) {
        totalPassengers += train.totalPassengers;
        totalMoney += train.totalMoney;

        if (train.totalPassengers > maxPassengers) {
            maxPassengers = train.totalPassengers;
            busiestTrain = train.departureTime;
        }
    }

    std::cout << "Total passengers for the day: " << totalPassengers << "\n";
    std::cout << "Total money for the day: $" << totalMoney << "\n";
    std::cout << "The train with the most passengers was the " << busiestTrain << " train with " << maxPassengers << " passengers.\n";
}

int main() {
    std::vector<Train> trains;
    std::string departureTimes[] = { "09:00", "11:00", "13:00", "15:00" };
    std::string returnTimes[] = { "10:00", "12:00", "14:00", "16:00" };

    for (int i = 0; i < 4; i++) {
        trains.push_back({ departureTimes[i], returnTimes[i], 0, 0, false });
    }

    // Example of purchasing tickets
    int trainIndex, passengers;
    std::cout << "Enter train index (0-3) and number of passengers: ";
    std::cin >> trainIndex >> passengers;
    purchaseTickets(trains, trainIndex, passengers);

    // End of day calculations
    endOfDay(trains);

    return 0;
}
