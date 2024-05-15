#include "TrackerEvent.h"
#include"Persistence.h"
#include"Serializer.h"
#include <iostream>
#include <filesystem>
#include <chrono>

Persistence::Persistence(Serializer* serializer)
{
    this->serializer = serializer;
}

Persistence::~Persistence()
{
}

void Persistence::Send(TrackerEvent* tEvent)
{
    std::lock_guard<std::mutex> lock(queueMutex);
    eventQueue.push(tEvent);
}

void Persistence::SendFlush()
{
    mustFlush = true;
}

void Persistence::Close()
{
    SendFlush();
    threadRunning = false;

    if (thread_->joinable())
        thread_->join();

    delete thread_;
    thread_ = nullptr;
}

void Persistence::CloseFile()
{
    if (file.is_open()) {
        std::string s = serializer->EndFileFormat();
        file << s;
        file.close();
    }
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
    
    updateFrequencyInMilliseconds = updateMilliseconds;
   
    // TODO : crear directorios
    /*if (!Directory.Exists(path))
    {
        Directory.CreateDirectory(path);
    }*/

   
    threadRunning = true;
    
    thread_ = new std::thread(&Persistence::ThreadRun, this);
    //thread_->detach();
}

void Persistence::ThreadRun()
{
    OpenFile();
    auto lastFlushTime = std::chrono::steady_clock::now();

    while (threadRunning) {

        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastFlushTime).count();

        if (elapsedTime >= updateFrequencyInMilliseconds || mustFlush) {
            lastFlushTime = currentTime;
            Flush();
        }
    }

    CloseFile();
}

void Persistence::Flush()
{
    mustFlush = false;

    std::unique_lock<std::mutex> lock(queueMutex);
    while (eventQueue.size() > 0) {
        TrackerEvent* e = eventQueue.front();
        copyQueue.push(e);
        eventQueue.pop();
    }
    lock.unlock(); // se libera el bloqueo del mutex

    while (copyQueue.size() > 0)
    {
        TrackerEvent* tEvent = copyQueue.front();
        copyQueue.pop();

        if (tEvent != nullptr) {
            file << serializer->serialize(tEvent);
    
            delete tEvent;
            tEvent = nullptr;
        }
    }
}
