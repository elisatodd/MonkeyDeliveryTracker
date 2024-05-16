#include "TrackerEvent.h"
#include <sstream>
TrackerEvent::TrackerEvent() : type(EventType::SessionStartEvent), event_ID("EVENT_ID"), session_ID("SESSION_ID"), event_type("ProgressionEvent")
{
}
std::string TrackerEvent::EventTypeToString(EventType type) const {
    switch (type) {
    case EventType::SessionStartEvent: return "SessionStartEvent";
        
    default: return "UnknownEvent";
    }
}
std::string TrackerEvent::ToJson() const
{
    std::ostringstream oss;
  
    oss << "  \"Timestamp\": " << Timestamp << ",\n";
    oss << "  \"event_ID\": \"" << event_ID << "\",\n";
    oss << "  \"session_ID\": \"" << session_ID << "\",\n";
    oss << "  \"event_type\": \"" << event_type << "\",\n";
    oss << "  \"type\": \"" << EventTypeToString(type) << "\"\n";

    return oss.str();
}

