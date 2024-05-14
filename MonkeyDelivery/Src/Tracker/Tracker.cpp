#include"Tracker.h"
#include"TrackerEvent.h"
#include <windows.h>
#include <rpc.h>
#include <iostream>
#include <string>

#pragma comment(lib, "rpcrt4.lib")
bool Tracker::Init(PersistenceType persistenceType, SerializationType serializationType, int updateMilliseconds)
{
    assert(instance == nullptr);

    instance = new Tracker();

    instance->eventFactory = new EventFactory();
    instance->ChooseSerializationStrategy(serializationType);
    instance->ChoosePersistenceStrategy(persistenceType);

    instance->persistenceStrategy->Open(updateMilliseconds);

    // Decidir el ID de sesión único 
    instance->GenerateUniqueID();

    // Evento de inicio de sesión
    instance->SendSessionStartEvent();

    return true;
}

bool Tracker::End()
{
    assert(instance != nullptr);

    // Finalizar la sesión
    instance->SendSessionEndEvent();

    delete instance;
    instance = nullptr;
    return true;
}

void Tracker::TrackEvent(TrackerEvent* tEvent)
{
    // Rellenar timestamp, event_ID, session_ID... del evento antes de enviarlo a la cola

    tEvent->session_ID = sessionID;

    // TODO : guid
    //tEvent->Event_ID = Guid.NewGuid().ToString();

    // TODO: tiempo. quizas pedir a la clase Timer
   /* DateTimeOffset now = DateTimeOffset.Now;
    tEvent->Timestamp = now.ToUnixTimeSeconds();*/

    persistenceStrategy->Send(tEvent);
}

void Tracker::FlushEvents()
{
    persistenceStrategy->SendFlush();
}

EventFactory* Tracker::GetEventFactory()
{
    return eventFactory;
}

void Tracker::ChoosePersistenceStrategy(PersistenceType pType)
{
    switch (pType)
    {
    case PersistenceType::FILE:
        persistenceStrategy = new Persistence(serializationStrategy);
        break;
    default:
        break;
    }
}

void Tracker::ChooseSerializationStrategy(SerializationType sType)
{
    switch (sType)
    {
    case SerializationType::JSON:
        serializationStrategy = new Serializer();
        break;
    default:
        break;
    }
}

void Tracker::GenerateUniqueID()
{
    UUID uuid;
    // Generar el UUID
    if (UuidCreate(&uuid) != RPC_S_OK) {
        // Manejar el error
        std::cerr << "Error al generar UUID" << std::endl;
        return;
    }

    // Convertir el UUID a cadena
    RPC_CSTR uuidString;
    if (UuidToStringA(&uuid, &uuidString) != RPC_S_OK) {
        // Manejar el error
        std::cerr << "Error al convertir UUID a cadena" << std::endl;
        return;
    }

    // Convertir RPC_CSTR a std::string
    sessionID = reinterpret_cast<char*>(uuidString);

    // Liberar memoria asignada por UuidToStringA
    RpcStringFreeA(&uuidString);

    // Para demostrar, imprimimos el UUID generado
    std::cout << "Generated UUID: " << sessionID << std::endl;
  
        // sessionID = Guid.NewGuid().ToString();
        // TODO : crear el GUID
   
}

void Tracker::SendSessionStartEvent()
{
    // TrackEvent(new SessionStartEvent());
}
