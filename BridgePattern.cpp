#include <iostream> 
#include <string>
using namespace std;

class VideoQuality{
    public:
        virtual void load(const string& title) = 0;
        virtual ~VideoQuality() {}
};

class SDQuality : public VideoQuality{
    public:
        void load(const string& title) override{
            cout << "Loading " << title << " in Standard Definition (SD) quality." << endl;
        }
};

class HDQuality : public VideoQuality{
    public:
        void load(const string& title) override{
            cout << "Loading " << title << " in High Definition (HD) quality." << endl;
        }
};

class UltraHDQuality : public VideoQuality{
    public:
        void load(const string& title) override{
            cout << "Loading " << title << " in Ultra High Definition (UHD) quality." << endl;
        }
};


class VideoPlayer{
    protected:
        VideoQuality* quality;
    public:
        VideoPlayer(VideoQuality* quality) : quality(quality) {}
        virtual void play(const string& title) = 0;
        virtual ~VideoPlayer(){
            delete quality;
        }
};

class WebPlayer : public VideoPlayer{
    public:
        WebPlayer(VideoQuality* quality) : VideoPlayer(quality) {}

        void play(const string& title) override{
            cout << "Playing video on Web Player." << endl;
            quality->load(title);
        }
};

class MobilePlayer : public VideoPlayer{
    public:
        MobilePlayer(VideoQuality* quality) : VideoPlayer(quality) {}

        void play(const string& title) override{
            cout << "Playing video on Mobile Player." << endl;
            quality->load(title);
        }
};

int main(){
    VideoPlayer* player1 = new WebPlayer(new HDQuality());
    player1->play("Nature Documentary");

    VideoPlayer* player2 = new MobilePlayer(new UltraHDQuality());
    player2->play("Action Movie");

    delete player1;
    delete player2;
    return 0;
}