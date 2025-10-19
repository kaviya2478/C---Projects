#include <string>
#include <iostream>
#include <vector>
using namespace std;


class PaymentGateway{
    public:
        virtual void pay(string orderId, double amount) = 0;
        virtual ~PaymentGateway() {}
};

class PayUGateway : public PaymentGateway{
    public:
        void pay(string orderId, double amount) override{
            cout <<"Paid Rs."<<amount<<" for order "<<orderId<<" using PayU Gateway."<< endl;
        }
};

class RazorpayAPI{
    public:
        void makePayment(string invoiceId, double amountInRupees){
            cout<<"Paid Rs."<<amountInRupees<<" for invoice "<<invoiceId<<" using Razorpay API."<< endl;
        }
};

class RazorpayAdapter : public PaymentGateway{
    private:
        RazorpayAPI razorpayAPI;
    public:

        void pay(string orderId, double amount) override{
            razorpayAPI.makePayment(orderId, amount);
        }
};


class CheckoutService{
    private:
      PaymentGateway* paymentGateway;
    public:
        CheckoutService(PaymentGateway* paymentGateway){
            this->paymentGateway = paymentGateway;
        }

        void checkout(string orderId, double amount){
            paymentGateway->pay(orderId, amount);
        }
};

int main(){
    CheckoutService chekoutService(new RazorpayAdapter());
    chekoutService.checkout("ORDER123", 1500.0);
    return 0;
}
