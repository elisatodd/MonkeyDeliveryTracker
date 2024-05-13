#pragma once
#include <queue>
#include "TrackerEvent.h"

class Serializer;

class Persistence {
public:

    Persistence(Serializer* serializer)
    {
        serializer = serializer;
    };

    void Send(TrackerEvent* tEvent)
    {
        eventQueue.push(tEvent);
    };

    void SendFlush()
    {
    };

    void Close()
    {
        SendFlush();
    };

    void Open(int updateMilliseconds)
    {
        updateFrequenceInMiliseconds = updateMilliseconds;

        // TODO : crear directorios
        /*if (!Directory.Exists(path))
        {
            Directory.CreateDirectory(path);
        }*/
    }

private:
    const std::string path = "./TrackerOutputs/";
    std::queue<TrackerEvent*> eventQueue;
    Serializer* serializer;

    int updateFrequenceInMiliseconds = 3000;

};