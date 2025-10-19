#include <iostream>
#include <string>
using namespace std;

class MatchingStrategy{
    public:
    virtual void match(const string& riderLocation) = 0;
    virtual ~MatchingStrategy() {}
};

class NearestDriverStrategy : public MatchingStrategy{
    public:
    void match(const string& riderLocation) override {
        cout << "Matching rider at " << riderLocation << " with the nearest driver." << endl;
    }
};

class AirportQueueStrategy : public MatchingStrategy{
    public:
    void match(const string& riderLocation) override {
        cout << "Matching rider at " << riderLocation << " with drivers in the airport queue." << endl;
    }
};

class SurgePriorityStrategy : public MatchingStrategy{
    public:
    void match(const string& riderLocation) override {
        cout << "Matching rider at " << riderLocation << " with drivers in surge pricing areas." << endl;
    }
};

class RideMatchingService{
    private:
    MatchingStrategy* strategy;
    public:
    RideMatchingService(MatchingStrategy* strategy){
        this->strategy = strategy;
    }

    void setStrategy(MatchingStrategy* strategy){
        this->strategy = strategy;
    }

    void matchRider(const string& location){
        strategy->match(location);
    }
};

int main() {
    NearestDriverStrategy nearestStrategy;
    AirportQueueStrategy airportStrategy;
    SurgePriorityStrategy surgeStrategy;

    RideMatchingService rideService(&nearestStrategy);
    rideService.matchRider("Downtown");

    rideService.setStrategy(&airportStrategy);
    rideService.matchRider("Airport");

    rideService.setStrategy(&surgeStrategy);
    rideService.matchRider("City Center during peak hours");

    return 0;
}   