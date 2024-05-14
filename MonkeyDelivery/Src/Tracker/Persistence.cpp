#include "TrackerEvent.h"
#include"Persistence.h"
#include"Serializer.h"
#include <iostream>
#include <filesystem>
#include <chrono>

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
    file << serializer->EndFileFormat();
    file.close();
}

void Persistence::OpenFile()
{
    auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    std::string fileName = std::to_string(timestamp) + serializer->GetFileExtension();

    
    std::string filePath = path + fileName;

    file.open(filePath);


    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo " << filePath << " para escritura." << std::endl;
    }
    else {

        file << serializer->InitFileFormat();
    }
    
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

void Persistence::Flush()
{
  
   

    while (eventQueue.size() > 0)
    {
      
        TrackerEvent* tEvent = eventQueue.front();
        eventQueue.pop();
        if (tEvent != nullptr) {
            file << serializer->serialize(tEvent);
    
            delete tEvent;
            tEvent = nullptr;
        }
   
        
    }
}
