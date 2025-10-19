#include <iostream>
#include <string>
using namespace std;

class Logistics{
    public:
        virtual void send() = 0;
        virtual ~Logistics() {}
};

class Road : public Logistics{
    public:
        void send() override{
            cout<<"Sending by road logic" << endl;
        }
};

class Air : public Logistics{
    public:
        void send() override{
            cout<<"Sending by air logic" << endl;
        }
};

class LogisticsFactory{
    public:
        static Logistics* getLogistics(const string& mode){
            if(mode == "Air"){
                return new Air();
            } else if(mode == "Road"){
                return new Road();
            }
            throw invalid_argument("Unknown logistics mode:" +  mode);
        }
};

class LogisticsService{
    public:
        void send(const string& mode){
            Logistics* logistics = LogisticsFactory::getLogistics(mode);
            logistics->send();
            delete logistics;
        }
};


int main(){
    LogisticsService service;
    service.send("Air");
    service.send("Road");
    return 0;
}