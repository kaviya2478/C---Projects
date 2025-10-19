#include <iostream>
#include <string>
using namespace std;

class SupportHandler{
    protected:
    SupportHandler* nextHandler = nullptr;
    public:
     void setNextHandler(SupportHandler* nextHandler){
        this->nextHandler = nextHandler;
     }

     virtual void handleRequest(string requestType) = 0;
};

class GeneralSupport : public SupportHandler{
    public:
    void handleRequest(string requestType) override {
        if(requestType == "general"){
            cout << "General Support: Handling general inquiry." << endl;
        }
        else if(nextHandler){
            nextHandler->handleRequest(requestType);
        }
        else{
            cout << "General Support: No handler available for this request." << endl;
        }
    }
};

class BillingSupport : public SupportHandler{
    public:
    void handleRequest(string requestType) override {
        if(requestType == "billing"){
            cout << "Billing Support: Handling billing issue." << endl;
        }
        else if(nextHandler){
            nextHandler->handleRequest(requestType);
        }
        else{
            cout << "Billing Support: No handler available for this request." << endl;
        }
    }
};

class TechnicalSupport : public SupportHandler{
    public:
    void handleRequest(string requestType) override {
        if(requestType == "technical"){
            cout << "Technical Support: Handling technical problem." << endl;
        }
        else if(nextHandler){
            nextHandler->handleRequest(requestType);
        }
        else{
            cout << "Technical Support: No handler available for this request." << endl;
        }
    }
};

class DeliverySupport : public SupportHandler{
    public:
    void handleRequest(string requestType) override {
        if(requestType == "delivery"){
            cout << "Delivery Support: Handling delivery question." << endl;
        }
        else if(nextHandler){
            nextHandler->handleRequest(requestType);
        }
        else{
            cout << "Delivery Support: No handler available for this request." << endl;
        }
    }
};

int main(){
    GeneralSupport generalSupport;
    BillingSupport billingSupport;
    TechnicalSupport technicalSupport;
    DeliverySupport deliverySupport;

    generalSupport.setNextHandler(&billingSupport);
    billingSupport.setNextHandler(&technicalSupport);
    technicalSupport.setNextHandler(&deliverySupport);

    string requests[] = {"general", "billing", "technical", "delivery", "unknown"};

    for(const string& request : requests){
        cout << "Client Request: " << request << endl;
        generalSupport.handleRequest(request);
        cout << "--------------------------" << endl;
    }

    return 0;
}

