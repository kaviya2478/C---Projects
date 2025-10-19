#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Item{
    public:
    virtual void accept(class ItemVisitor* visitor) = 0;
    virtual ~Item() {}
};

class PhysicalProduct : public Item {
    public:
    string name;
    double weight;

    PhysicalProduct(const string& name, double weight) : name(name), weight(weight) {}
    void accept(ItemVisitor* visitor) override;
};

class DigitalProduct : public Item {
    public:
    string name;
    double fileSize;

    DigitalProduct(const string& name, double fileSize) : name(name), fileSize(fileSize) {}
    void accept(ItemVisitor* visitor) override;
};

class GiftCard : public Item {
    public:
    string code;
    double amount;

    GiftCard(const string& code, double amount) : code(code), amount(amount) {}
    void accept(ItemVisitor* visitor) override;
};

class ItemVisitor{
    public:
    virtual void visit(PhysicalProduct* product) = 0;
    virtual void visit(DigitalProduct* product) = 0;
    virtual void visit(GiftCard* giftCard) = 0;
    virtual ~ItemVisitor() {}
};

class InvoiceVisitor : public ItemVisitor{
    public:
    void visit(PhysicalProduct* product) override {
        cout << "Invoicing Physical Product: " << product->name << ", Weight: " << product->weight << "kg" << endl;
    }

    void visit(DigitalProduct* product) override {
        cout << "Invoicing Digital Product: " << product->name << ", File Size: " << product->fileSize << "MB" << endl;
    }

    void visit(GiftCard* giftCard) override {
        cout << "Invoicing Gift Card: Code " << giftCard->code << ", Amount: $" << giftCard->amount << endl;
    }
};

class ShippingCostVisitor : public ItemVisitor{
    public:
    void visit(PhysicalProduct* product) override {
        double cost = product->weight * 5.0; // $5 per kg
        cout << "Shipping Cost for Physical Product: " << product->name << " is $" << cost << endl;
    }

    void visit(DigitalProduct* product) override {
        cout << "No Shipping Cost for Digital Product: " << product->name << endl;
    }

    void visit(GiftCard* giftCard) override {
        cout << "No Shipping Cost for Gift Card: Code " << giftCard->code << endl;
    }
};

void PhysicalProduct::accept(ItemVisitor* visitor) {
    visitor->visit(this);
}

void DigitalProduct::accept(ItemVisitor* visitor) {
    visitor->visit(this);
}

void GiftCard::accept(ItemVisitor* visitor) {
    visitor->visit(this);
}

int main() {
    vector<Item*> items;
    items.push_back(new PhysicalProduct("Laptop", 2.5));
    items.push_back(new DigitalProduct("E-Book", 15.0));
    items.push_back(new GiftCard("GFT12345", 100.0));

    InvoiceVisitor invoiceVisitor;
    ShippingCostVisitor shippingVisitor;

    for(auto item : items){
        item->accept(&invoiceVisitor);
        item->accept(&shippingVisitor);
        cout << "------------------------" << endl;
    }

    for(auto item : items){
        delete item;
    }

    return 0;
}