#pragma once
#include <cassert>
#include <string>

#include "Persistence.h"
#include "Serializer.h"
#include "EventFactory.h"

using namespace std;

enum PersistenceType
{
    TO_FILE = 0
};

enum SerializationType
{
    JSON = 0
};
class TrackerEvent;

class Tracker {
public:

    static Tracker* Instance() 
    {
        assert(instance);
        return instance;
    };

    Persistence* persistenceStrategy;
    Serializer* serializationStrategy;

    EventFactory* eventFactory;

    string sessionID;

    static bool Init(PersistenceType persistenceType, SerializationType serializationType, int updateMilliseconds);
   
    static bool End();
  
    void TrackEvent(TrackerEvent* tEvent);
   

    // Envia todos los eventos almacenados en la cola
    void FlushEvents();


    EventFactory* GetEventFactory();

private:
    static Tracker* instance; // revisar singleton en C++ (static)

    Tracker() { }; // Ocultar el constructor
    ~Tracker();
    Tracker(Tracker& other) = delete; // Copy Constructor
    void operator = (const Tracker&) = delete; //Assignement operator

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