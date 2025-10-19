#include <string>
#include <iostream>
#include <unordered_map>
using namespace std;

class EmailTemplate{
    public:
        virtual EmailTemplate* clone() const = 0;
        virtual void setContent(const string& content) = 0;
        virtual void send(const string& to) const = 0;
        virtual ~EmailTemplate() {}
};

class WelcomeEmail : public EmailTemplate{
    private:
        string subject;
        string content;
    public:
        WelcomeEmail(){
            subject = "Welcome to Our Service!";
            content = "Hello, thank you for joining us.";
        }

        WelcomeEmail(const WelcomeEmail& other){
            subject = other.subject;
            content = other.content;
        }

        EmailTemplate* clone() const override{
            return new WelcomeEmail(*this);
        }

        void setContent(const string& content) override{
            this->content = content;
        }

        void send(const string& to) const override{
            cout << "Sending to " << to << " with subject: " << subject << " and content: " << content << endl;
        }
};

class EmailTemplateRegistry{
    private:
        static unordered_map<string, EmailTemplate*> templates;

    public:
        static void init(){
            templates["WelcomeEmail"] = new WelcomeEmail();
        }

        static EmailTemplate* getTemplate(const string& type){
            return templates[type]->clone();
        }

        static void cleanup(){
            for(auto& pair : templates){
                delete pair.second;
            }
        }
};

unordered_map<string, EmailTemplate*> EmailTemplateRegistry::templates;

int main(){
    EmailTemplateRegistry::init();

    EmailTemplate* welcomeEmail = EmailTemplateRegistry::getTemplate("WelcomeEmail");
    welcomeEmail->setContent("Hello John, welcome to our awesome platform!");
    welcomeEmail->send("alice@example.com");

    delete welcomeEmail;
    EmailTemplateRegistry::cleanup();
    return 0;
}

