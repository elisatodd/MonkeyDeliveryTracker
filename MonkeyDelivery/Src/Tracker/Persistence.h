#pragma once
#include <queue>
#include <fstream>
#include <mutex>
class Serializer;
class TrackerEvent;
class Persistence {
public:

    Persistence(Serializer* serializer);
    ~Persistence();

    void Send(TrackerEvent* tEvent);
    
    void SendFlush();
    void Flush();
   
    void Close();
    void CloseFile();
   
    void OpenFile();
    void Open(int updateMilliseconds);
   

private:
    const std::string path = "./TrackerOutputs/";
    Serializer* serializer;
    int updateFrequencyInMilliseconds = 3000;

    std::ofstream file;

    std::queue<TrackerEvent*> eventQueue;
    std::queue<TrackerEvent*> copyQueue;
    std::mutex queueMutex;
    std::atomic<bool> threadRunning = false;
    std::atomic<bool> mustFlush = false;

    std::thread* thread_ = nullptr;
    void ThreadRun();
};