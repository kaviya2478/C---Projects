#include <iostream>
#include <vector>
using namespace std;

class NotificationSender{
    public:
     void send(string to, string rawmessage){
        rateLimitCheck(to);
        validateRecipient(to);
        string formatted = formatMessage(rawmessage);
        preSendAuditLog(to, formatted);

        string composedMessage = composeMessage(formatted);
        sendMessage(to, composedMessage);

        postSendAnalytics(to);
     }

     void rateLimitCheck(string to){
        cout << "Rate limit check for " << to << endl;
     }

        void validateRecipient(string to){
            cout << "Validating recipient: " << to << endl;
        }

        string formatMessage(string message){
            return message.substr(0, message.find_last_not_of(" \t\n\r\f\v") + 1);
        }

        void preSendAuditLog(string to, string formatted){
            cout << "Audit log before sending to " << to << ": " << formatted << endl;
        }

        virtual string composeMessage(string formatted) = 0;
        virtual void sendMessage(string to, string composedMessage) = 0;
        virtual void postSendAnalytics(string to){
            cout << "Analytics updated to:" +to << endl;
}

};

class EmailNotification : public NotificationSender{
    public:
    string composeMessage(string formatted) override {
        return "Email Body: " + formatted;
    }

    void sendMessage(string to, string composedMessage) override {
        cout << "Sending Email to " << to << ": " << composedMessage << endl;
    }
};

class SMSNotification : public NotificationSender{
    public:
    string composeMessage(string formatted) override {
        return "SMS Text: " + formatted;
    }

    void sendMessage(string to, string composedMessage) override {
        cout << "Sending SMS to " << to << ": " << composedMessage << endl;
    }

    void postSendAnalytics(string to) override {
        cout << "SMS-specific analytics updated for " << to << endl;
    }
};

int main(){
    NotificationSender* emailNotif = new EmailNotification();
    emailNotif->send("john@example.com", " Hello John!   ");
    cout << endl;
    NotificationSender* smsNotif = new SMSNotification();
    smsNotif->send("+1234567890", " Hi there!   ");
    return 0;
}

