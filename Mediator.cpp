#include <iostream>
#include <string>
#include <vector>
using namespace std;

class User;

class DocumentSessionMediator{
    public:
    virtual void boardcastChange(const string& change, User* sender) = 0;
    virtual void join(User* user) = 0;
    virtual ~DocumentSessionMediator() {}
};

class User{
    protected:
     string name;
     DocumentSessionMediator* mediator;
    public:
       User(string name, DocumentSessionMediator* mediator): name(name), mediator(mediator) {}

       string getName() const { return name; }

       void makeChange(const string& change){
        cout << name << " made a change: " << change << endl;
        mediator->boardcastChange(change, this);
       }

       void receiveChange(const string& change){
        cout << name << " received change: " << change << endl;
       }
};

class CollaborativeDocument : public DocumentSessionMediator{
    private:
    vector<User*> users;
    public:
    void boardcastChange(const string& change, User* sender) override {
        for(auto user : users){
            if(user != sender){
                user->receiveChange(change);
            }
        }
    }

    void join(User* user) override {
        users.push_back(user);
        cout << user->getName() << " joined the document session." << endl;
    }
};

int main() {
    CollaborativeDocument docSession;

    User alice("Alice", &docSession);
    User bob("Bob", &docSession);
    User charlie("Charlie", &docSession);

    docSession.join(&alice);
    docSession.join(&bob);
    docSession.join(&charlie);

    alice.makeChange("Added introduction section.");
    bob.makeChange("Corrected typos in chapter 1.");
    charlie.makeChange("Updated conclusion.");

    return 0;
}