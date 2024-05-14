#pragma once
#include <cassert>
#include <string>

#include "Persistence.h"
#include "Serializer.h"
#include "EventFactory.h"

using namespace std;

enum PersistenceType
{
    FILE = 0
};

enum SerializationType
{
    JSON = 0
};
class TrackerEvent;
class Tracker {
public:

    Tracker* instance = nullptr; // revisar singleton en C++ (static)

    Tracker* Instance() 
    {
        assert(instance != nullptr);
        return instance;
    };

    Persistence* persistenceStrategy;
    Serializer* serializationStrategy;

    EventFactory* eventFactory;

    string sessionID;

    bool Init(PersistenceType persistenceType, SerializationType serializationType, int updateMilliseconds);
   
    bool End();
  
    void TrackEvent(TrackerEvent* tEvent);
   

    // Envia todos los eventos almacenados en la cola
    void FlushEvents();


    EventFactory* GetEventFactory();

private:
    Tracker() { }; // Ocultar el constructor

    // Puede ser público si queremos habilitar que se cambie el tipo de persistencia a mitad del tracker
    void ChoosePersistenceStrategy(PersistenceType pType);
 
    void ChooseSerializationStrategy(SerializationType sType);
 

    void GenerateUniqueID();
   

    void SendSessionStartEvent();
    

    void SendSessionEndEvent()
    {
       // TrackEvent(new SessionEndEvent());

        // Volcado de los datos restantes
        FlushEvents();

        // Cierre de la posible hebra 
        persistenceStrategy->Close();
    };
};