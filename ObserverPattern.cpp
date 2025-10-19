#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Subscriber{
    public:
    virtual void update(const string& videoTitle) = 0;
    virtual ~Subscriber() {}
};

class EmailSubscriber : public Subscriber{
    private:
    string email;
    public:
    EmailSubscriber(const string& email){
        this->email = email;
    }

    void update(const string& videoTitle) override {
        cout << "Email to " << email << ": New video uploaded - " << videoTitle << endl;
    }
};

class MobileAppSubscriber : public Subscriber{
    private:
    string username;
    public:
    MobileAppSubscriber(const string& username){
        this->username = username;
    }

    void update(const string& videoTitle) override {
        cout << "Mobile App Notification to " << username << ": New video uploaded - " << videoTitle << endl;
    }
};

class Channel{
    public:
    virtual void subscribe(Subscriber* subscriber) = 0;
    virtual void unsubscribe(Subscriber* subscriber) = 0;
    virtual void notifySubscribers(const string& videoTitle) = 0;
    virtual ~Channel() {}
};

class YouTubeChannel : public Channel{
    private:
    vector<Subscriber*> subscribers;
    string channelName;
    public:
    YouTubeChannel(const string& channelName){
        this->channelName = channelName;
    }
    void subscribe(Subscriber* subscriber) override {
        subscribers.push_back(subscriber);
    }

    void unsubscribe(Subscriber* subscriber) override {
        subscribers.erase(remove(subscribers.begin(), subscribers.end(), subscriber), subscribers.end());
    }

    void notifySubscribers(const string& videoTitle) override {
        for(auto subscriber : subscribers){
            subscriber->update(videoTitle);
        }
    }

    void uploadVideo(const string& videoTitle) {
        cout << "Uploading video: " << videoTitle << endl;
        notifySubscribers(videoTitle);
    }
};

int main() {
    YouTubeChannel channel("Tech Tutorials");

    Subscriber* emailSub = new EmailSubscriber("rahul@example.com");
    Subscriber* appSub = new MobileAppSubscriber("rahul123");
    channel.subscribe(emailSub);
    channel.subscribe(appSub);
    channel.uploadVideo("Observer Pattern in C++");

    channel.unsubscribe(emailSub);
    channel.uploadVideo("Strategy Pattern in C++");
    delete emailSub;
    delete appSub;
    return 0;
}