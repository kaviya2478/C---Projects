#include <iostream>
using namespace std;

class PaymentService{
    public:
        void processPayment(const string& accountId, double amount){
            cout << "Processing payment of Rs." << amount << " for order " << accountId << endl;
        }
};

class SeatReservationService{
    public:
        void reserveSeat(string movieId, string seatNumber){
            cout << "Reserving seat " << seatNumber << " for movie " << movieId << endl;
        }
};

class NotificationService{
    public:
        void sendBookingConfirmation(string userEmail){
            cout << "Sending notification to user " << userEmail << " about booking confirmation." << endl;
        }
};

class LoyaltyPointsService{
    public:
        void addPoints(string accountId, int points){
            cout << "Adding " << points << " loyalty points to account " << accountId << endl;
        }
};

class TicketService{
    public:
    void addPoints(string accountId, int points){
            cout << "Adding " << points << " points to account " << accountId << endl;
        }
};

class MovieBookingFacade{
    private:
        PaymentService paymentService;
        SeatReservationService seatReservationService;
        NotificationService notificationService;
        LoyaltyPointsService loyaltyPointsService;

    public:
        MovieBookingFacade() {}

        void bookMovieTicket(string accountId, string movieId, string seatNumber, string userEmail, double amount){
            paymentService.processPayment(accountId, amount);
            seatReservationService.reserveSeat(movieId, seatNumber);
            notificationService.sendBookingConfirmation(userEmail);
            loyaltyPointsService.addPoints(accountId, 10);
        }
};

int main(){
    MovieBookingFacade movieBookingFacade;
    movieBookingFacade.bookMovieTicket("ACC123", "MOV456", "A10", "user@example.com", 250.0);
    return 0;
}