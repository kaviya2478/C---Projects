#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

class VideoDownloader{
    public:
        virtual string downloadVideo(string videoUrl) = 0;
        virtual ~VideoDownloader() = default;
};

class RealVideoDownloader : public VideoDownloader{
    public:
        string downloadVideo(string videoUrl) override{
            cout<< "Downloading video from "<<videoUrl<< endl;
            return "Video content from " + videoUrl;
        }
};


class CachedVideoDownloader : public VideoDownloader{
    private:
        RealVideoDownloader realDownloader;
        unordered_map<string, string> cache;
    public:
        string downloadVideo(string videoUrl) override{
            if(cache.find(videoUrl) != cache.end()){
                cout << "Fetching video from cache for URL: " << videoUrl << endl;
                return cache[videoUrl];
            }
            string videoContent = realDownloader.downloadVideo(videoUrl);
            cache[videoUrl] = videoContent;
            return videoContent;
        }
};

int main(){
    VideoDownloader* cacheVideoDownloader = new CachedVideoDownloader();
    cacheVideoDownloader->downloadVideo("http://example.com/video1");
    cacheVideoDownloader->downloadVideo("http://example.com/video1");
    delete cacheVideoDownloader;
    return 0;
}