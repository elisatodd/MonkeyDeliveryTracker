#pragma once
#include <queue>
#include <fstream>
class Serializer;
class TrackerEvent;
class Persistence {
public:

    Persistence(Serializer* serializer);

    void Send(TrackerEvent* tEvent);
    
    void SendFlush();
   

    void Close();
   
    void OpenFile();
    void Open(int updateMilliseconds);
   

private:
    const std::string path = "./TrackerOutputs/";
    std::queue<TrackerEvent*> eventQueue;
    Serializer* serializer;
    void Flush();
    int updateFrequenceInMiliseconds = 3000;
    std::ofstream file;
};