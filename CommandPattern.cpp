#include <iostream>
#include <stack>
#include <string>
using namespace std;

class Light{
    public:
    void on(){
        cout << "The light is ON" << endl;
    }
    void off(){
        cout << "The light is OFF" << endl;
    }
};

class AC{
    public:
    void on(){
        cout << "The AC is ON" << endl;
    }
    void off(){
        cout << "The AC is OFF" << endl;
    }
};


class Command{
    public:
    virtual void execute() = 0;
    virtual void undo() = 0;
};


class LightOnCommand : public Command{
    private:
    Light* light;
    public:
    LightOnCommand(Light* light){
        this->light = light;
    }
    void execute() override {
        light->on();
    }
    void undo() override {
        light->off();
    }
};

class LightOffCommand : public Command{
    private:
    Light* light;
    public:
    LightOffCommand(Light* light){
        this->light = light;
    }
    void execute() override {
        light->off();
    }
    void undo() override {
        light->on();
    }
};

class ACOnCommand : public Command{
    private:
    AC* ac;
    public:
    ACOnCommand(AC* ac){
        this->ac = ac;
    }
    void execute() override {
        ac->on();
    }
    void undo() override {
        ac->off();
    }
};

class ACOffCommand : public Command{
    private:
    AC* ac;
    public:
    ACOffCommand(AC* ac){
        this->ac = ac;
    }
    void execute() override {
        ac->off();
    }
    void undo() override {
        ac->on();
    }
};

class RemoteControl{
    private:
    Command* buttons[4];
    stack<Command*> commandHistory;

    public:

    void setCommand(int slot, Command* command){
        if(slot >=0 && slot < 4){
            buttons[slot] = command;
        }
    }

    void pressButton(int slot){
        if(slot >=0 && slot < 4 && buttons[slot]){
            buttons[slot]->execute();
            commandHistory.push(buttons[slot]);
        }
        else{
            cout << "No command assigned to this button." << endl;
        }
    }

    void pressUndo(){
        if(!commandHistory.empty()){
            Command* lastCommand = commandHistory.top();
            lastCommand->undo();
            commandHistory.pop();
        }
        else{
            cout << "No commands to undo." << endl;
        }
    }
};

int main(){
    Light light;
    AC ac;

    Command* lightOn = new LightOnCommand(&light);
    Command* lightOff = new LightOffCommand(&light);
    Command* acOn = new ACOnCommand(&ac);
    Command* acOff = new ACOffCommand(&ac);

    RemoteControl remote;
    remote.setCommand(0, lightOn);
    remote.setCommand(1, lightOff);
    remote.setCommand(2, acOn);
    remote.setCommand(3, acOff);

    remote.pressButton(0); // Light ON
    remote.pressButton(2); // AC ON
    remote.pressUndo();    // AC OFF
    remote.pressButton(1); // Light OFF
    remote.pressUndo();    // Light ON
    remote.pressButton(3); // AC OFF
    remote.pressUndo();    // AC ON


    delete lightOn;
    delete lightOff;
    delete acOn;
    delete acOff;
    return 0;
}