#include<iostream>
#include<string>
using namespace std;

class OrderState{
    public:
    virtual void next(class OrderContext* order) = 0;
    virtual void cancel(class OrderContext* order) = 0;
    virtual string getStateName() = 0;
};

class OrderContext;


class OrderPlacedState : public OrderState{
    public:
    void next(OrderContext* context) override;
    void cancel(OrderContext* context) override;
    string getStateName() override;
};

class PreparingState : public OrderState{
    public:
    void next(OrderContext* context) override;
    void cancel(OrderContext* context) override;
    string getStateName() override;
};

class OutForDeliveryState : public OrderState{
    public:
    void next(OrderContext* context) override;
    void cancel(OrderContext* context) override;
    string getStateName() override;
};

class DeliveredState : public OrderState{
    public:
    void next(OrderContext* context) override;
    void cancel(OrderContext* context) override;
    string getStateName() override;
};

class CancelledState : public OrderState{
    public:
    void next(OrderContext* context) override;
    void cancel(OrderContext* context) override;
    string getStateName() override;
};

class OrderContext{
    private:
    OrderState* currentState;
    public:
    OrderContext();

    void setState(OrderState* state);

    void next();

    void cancel();

    string getCurrentState();
};

OrderContext::OrderContext(){
    currentState = new OrderPlacedState();
}

void OrderContext::setState(OrderState* state){
    currentState = state;
}

void OrderContext::next(){
    currentState->next(this);
}

void OrderContext::cancel(){
    currentState->cancel(this);
}

string OrderContext::getCurrentState(){
    return currentState->getStateName();
}

void OrderPlacedState::next(OrderContext* context){
    cout << "Order is now being prepared." << endl;
    context->setState(new PreparingState());
}

void OrderPlacedState::cancel(OrderContext* context){
    cout << "Order has been cancelled." << endl;
    context->setState(new CancelledState());
}

string OrderPlacedState::getStateName(){
    return "Order Placed";
}

void PreparingState::next(OrderContext* context){
    cout << "Order is out for delivery." << endl;
    context->setState(new OutForDeliveryState());
}

void PreparingState::cancel(OrderContext* context){
    cout << "Order has been cancelled." << endl;
    context->setState(new CancelledState());
}

string PreparingState::getStateName(){
    return "Preparing";
}


void OutForDeliveryState::next(OrderContext* context){
    cout << "Order has been delivered." << endl;
    context->setState(new DeliveredState());
}

void OutForDeliveryState::cancel(OrderContext* context){
    cout << "Order cannot be cancelled at this stage." << endl;
}

string OutForDeliveryState::getStateName(){
    return "Out for Delivery";
}

void DeliveredState::next(OrderContext* context){
    cout << "Order is already delivered." << endl;
}

void DeliveredState::cancel(OrderContext* context){
    cout << "Order cannot be cancelled as it is already delivered." << endl;
}

string DeliveredState::getStateName(){
    return "Delivered";
}

void CancelledState::next(OrderContext* context){
    cout << "Order is cancelled and cannot proceed further." << endl;
}

void CancelledState::cancel(OrderContext* context){
    cout << "Order is already cancelled." << endl;
}

string CancelledState::getStateName(){
    return "Cancelled";
}

int main() {
    OrderContext order;

    cout << "Current State: " << order.getCurrentState() << endl;
    order.next();
    cout << "Current State: " << order.getCurrentState() << endl;
    order.next();
    cout << "Current State: " << order.getCurrentState() << endl;
    order.cancel();
    cout << "Current State: " << order.getCurrentState() << endl;
    order.next();
    cout << "Current State: " << order.getCurrentState() << endl;

    return 0;
}

