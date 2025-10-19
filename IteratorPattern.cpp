#include <iostream>
#include <vector>
using namespace std;

class Video{
    string title;
public:
    Video(const string& t): title(t) {}
    string getTitle() const { return title; }
};

class YouTubePlaylist{
    vector<Video> videos;
public:
    void addVideo(const Video& video) {
        videos.push_back(video);
    }

    vector<Video>& getVideos() {
        return videos;
    }   
};

class PlaylistIterator{
    public:
    virtual bool hasNext() = 0;
    virtual Video* next() = 0;
    virtual ~PlaylistIterator() = default;
};

class YouTubePlaylistIterator : public PlaylistIterator{
    vector<Video>& videos;
    size_t position;
public:
    YouTubePlaylistIterator(vector<Video>& vids) : videos(vids), position(0) {}
    
    bool hasNext() override {
        return position < videos.size();
    }
    
    Video* next() override {
        return hasNext() ? &videos[position++] : nullptr;
    }
};

int main() {
    YouTubePlaylist playlist;
    playlist.addVideo(Video("C++ Tutorial"));
    playlist.addVideo(Video("Design Patterns in C++"));
    playlist.addVideo(Video("Iterator Pattern Explained"));

    YouTubePlaylistIterator iterator(playlist.getVideos());

    while (iterator.hasNext()) {
        Video* video = iterator.next();
        if (video) {
            cout << "Video Title: " << video->getTitle() << endl;
        }
    }

    return 0;
}

