#include"Tracker.h"
#include"TrackerEvent.h"
#include "SessionStartEvent.h"
#include "SessionEndEvent.h"

#include <windows.h>
#include <rpc.h>
#include <iostream>
#include <string>
#include <ctime>

#pragma comment(lib, "rpcrt4.lib")

Tracker* Tracker::instance = nullptr;

bool Tracker::Init(PersistenceType persistenceType, SerializationType serializationType, int updateMilliseconds)
{
    assert(!instance);

    instance = new Tracker();

    instance->eventFactory = new EventFactory();
    instance->ChooseSerializationStrategy(serializationType);
    instance->ChoosePersistenceStrategy(persistenceType);

    instance->persistenceStrategy->Open(updateMilliseconds);

    //while (true) {
    //    instance->persistenceStrategy->Send(eventoo);
    //    std::this_thread::sleep_for(std::chrono::seconds(1));
    //}

    // Decidir el ID de sesi�n �nico 
    instance->GenerateUniqueID();

    // Evento de inicio de sesi�n
    instance->SendSessionStartEvent();

    return true;
}

bool Tracker::End()
{
    assert(instance);

    // Finalizar la sesi�n
    instance->SendSessionEndEvent();

    delete instance->persistenceStrategy;
    delete instance->serializationStrategy;

    delete instance->eventFactory;

    delete instance;
    instance = nullptr;
    return true;
}

void Tracker::TrackEvent(TrackerEvent* tEvent)
{
    // Rellenar timestamp, event_ID, session_ID... del evento antes de enviarlo a la cola

    tEvent->session_ID = sessionID;

    tEvent->event_ID = GenerateUniqueID();

    // Obtener el tiempo actual
    time_t currentTime = std::time(nullptr);

    if (currentTime == -1) {
        std::cout << "Error al obtener el tiempo actual.\n";
    }
    tEvent->Timestamp = currentTime;

    persistenceStrategy->Send(tEvent);
}

void Tracker::FlushEvents()
{
    persistenceStrategy->Flush();
}

EventFactory* Tracker::GetEventFactory()
{
    return eventFactory;
}

Tracker::~Tracker()
{
}

void Tracker::ChoosePersistenceStrategy(PersistenceType pType)
{
    switch (pType)
    {
    case PersistenceType::TO_FILE:
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

std::string Tracker::GenerateUniqueID()
{
    std::string s;

    UUID uuid;
    // Generar el UUID
    if (UuidCreate(&uuid) != RPC_S_OK) {
        // Manejar el error
        std::cerr << "Error al generar UUID" << std::endl;
        return "";
    }

    // Convertir el UUID a cadena
    RPC_CSTR uuidString;
    if (UuidToStringA(&uuid, &uuidString) != RPC_S_OK) {
        // Manejar el error
        std::cerr << "Error al convertir UUID a cadena" << std::endl;
    }

    // Convertir RPC_CSTR a std::string
    s = reinterpret_cast<char*>(uuidString);

    // Liberar memoria asignada por UuidToStringA
    RpcStringFreeA(&uuidString);

    // Para demostrar, imprimimos el UUID generado
    std::cout << "Generated UUID: " << s << std::endl;

    return s;
}

void Tracker::GenerateSessionID()
{
    sessionID = GenerateUniqueID();
}

void Tracker::SendSessionStartEvent()
{
    TrackEvent(new SessionStartEvent());
}

void Tracker::SendSessionEndEvent()

{
    TrackEvent(new SessionEndEvent());

    // Volcado de los datos restantes
    FlushEvents();

    // Cierre de la posible hebra 
    persistenceStrategy->Close();
}
