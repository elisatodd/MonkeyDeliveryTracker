#pragma once
#include <queue>
class Serializer;
class TrackerEvent;
class Persistence {
public:

    Persistence(Serializer* serializer);

    void Send(TrackerEvent* tEvent);
    
    void SendFlush();
   

    void Close();
   

    void Open(int updateMilliseconds);
 

private:
    const std::string path = "./TrackerOutputs/";
    std::queue<TrackerEvent*> eventQueue;
    Serializer* serializer;

    int updateFrequenceInMiliseconds = 3000;

};