#include "TrackerEvent.h"
#include"Persistence.h"

Persistence::Persistence(Serializer* serializer)
{
    serializer = serializer;
}

void Persistence::Send(TrackerEvent* tEvent)
{
    eventQueue.push(tEvent);
}

void Persistence::SendFlush()
{
}

void Persistence::Close()
{
    SendFlush();
}

void Persistence::Open(int updateMilliseconds)
{
    
    updateFrequenceInMiliseconds = updateMilliseconds;

        // TODO : crear directorios
        /*if (!Directory.Exists(path))
        {
            Directory.CreateDirectory(path);
        }*/
    
}
