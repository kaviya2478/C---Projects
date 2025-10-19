#include <iostream>
#include <string>
using namespace std;

class Pizza{
    public:
        virtual string getDescription() = 0;
        virtual double getCost() = 0;
        virtual ~Pizza() = default;
};

class PlainPizza : public Pizza{
    public:
        string getDescription() override{
            return "Plain Pizza";
        }

        double getCost() override{
            return 5.0;
        }
};

class MargheritaPizza : public Pizza{
    public:
        string getDescription() override{
            return "Margherita Pizza";
        }

        double getCost() override{
            return 7.0;
        }
};

class PizzaDecorator : public Pizza{
    protected:
        Pizza* pizza;
    public:
        PizzaDecorator(Pizza* pizza) : pizza(pizza) {}
        virtual ~PizzaDecorator(){
            delete pizza;
        }
};


class ExtraCheese : public PizzaDecorator{
    public:
        ExtraCheese(Pizza* pizza) : PizzaDecorator(pizza) {}

        string getDescription() override{
            return pizza->getDescription() + ", Extra Cheese";
        }

        double getCost() override{
            return pizza->getCost() + 1.5;
        }
};

class Olives : public PizzaDecorator{
    public:
        Olives(Pizza* pizza) : PizzaDecorator(pizza) {}

        string getDescription() override{
            return pizza->getDescription() + ", Olives";
        }

        double getCost() override{
            return pizza->getCost() + 1.0;
        }
};

class StuffedCrust : public PizzaDecorator{
    public:
        StuffedCrust(Pizza* pizza) : PizzaDecorator(pizza) {}

        string getDescription() override{
            return pizza->getDescription() + ", Stuffed Crust";
        }

        double getCost() override{
            return pizza->getCost() + 2.0;
        }
};

int main(){
    Pizza* myPizza = new MargheritaPizza();
    myPizza = new ExtraCheese(myPizza);
    myPizza = new Olives(myPizza);
    myPizza = new StuffedCrust(myPizza);

    cout << "Order Details: " << myPizza->getDescription() << endl;
    cout << "Total Cost: Rs." << myPizza->getCost() << endl;

    delete myPizza;
    return 0;
}