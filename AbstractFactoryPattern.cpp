#include<iostream>
#include<string>
using namespace std;

class PaymentGateway{
    public:
        virtual void processPayment(double amount) = 0;
        virtual ~PaymentGateway() {}
};

class Invoice{
    public:
        virtual void generateInvoice() =0;
        virtual ~Invoice() {}
};

class RazorpayPayment : public PaymentGateway{
    public:
        void processPayment(double amount) override{
            cout<<"Processing INR payment via Razorpay:" << amount<< endl;
        }
};

class PayUGateway : public PaymentGateway{
    public:
        void processPayment(double amount) override{
            cout<<"Processing INR payment via PayU:" << amount<< endl;
        }
};

class GSTInvoice : public Invoice{
    public:
        void generateInvoice() override{
            cout<<"Generating GST Invoice for India."<< endl;
        }
};


class PayPalGateway : public PaymentGateway{
    public:
        void processPayment(double amount) override{
            cout<<"Processing USD payment via PayPal:" << amount<< endl;
        }
};

class StripeGateway : public PaymentGateway{
    public:
        void processPayment(double amount) override{
            cout<<"Processing USD payment via Stripe:" << amount<< endl;
        }
};

class USInvoice : public Invoice{
    public:
        void generateInvoice() override{
            cout<<"Generating Standard Invoice for USA."<< endl;
        }
};


class RegionFactory{
    public:
        virtual PaymentGateway* createPaymentGateway(string gatewayType) =0;
        virtual Invoice* createInvoice() =0;
        virtual ~RegionFactory() {}
};

class IndiaFactory : public RegionFactory{
    public:
        PaymentGateway* createPaymentGateway(string gatewayType) override{
            if(gatewayType == "Razorpay"){
                return new RazorpayPayment();
            } else if(gatewayType == "PayU"){
                return new PayUGateway();
            }
            throw invalid_argument("Unknown gateway type for India: " + gatewayType);
        }

        Invoice* createInvoice() override{
            return new GSTInvoice();
        }
};

class USAFactory : public RegionFactory{
    public:
        PaymentGateway* createPaymentGateway(string gatewayType) override{
            if(gatewayType == "PayPal"){
                return new PayPalGateway();
            } else if(gatewayType == "Stripe"){
                return new StripeGateway();
            }
            throw invalid_argument("Unknown gateway type for USA: " + gatewayType);
        }

        Invoice* createInvoice() override{
            return new USInvoice();
        }
};

class CheckoutService{
    private:
        PaymentGateway* paymentGateway;
        Invoice* invoice;

    public:
        CheckoutService(RegionFactory* factory, string gatewayType){
            paymentGateway = factory->createPaymentGateway(gatewayType);
            invoice = factory->createInvoice();
        }

        void completeOrder(double amount){
            paymentGateway->processPayment(amount);
            invoice->generateInvoice();
        }

        ~CheckoutService(){
            delete paymentGateway;
            delete invoice;
        }
};

int main(){
    CheckoutService indiaCheckout(new IndiaFactory(), "Razorpay");
    indiaCheckout.completeOrder(1500.0);
    cout<<"---"<<endl;

    CheckoutService usaCheckout(new USAFactory(), "PayPal");
    usaCheckout.completeOrder(50.0);
    return 0;
}