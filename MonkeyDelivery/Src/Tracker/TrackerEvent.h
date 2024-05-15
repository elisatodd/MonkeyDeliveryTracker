#pragma once

#include <string>

enum class EventType {
    ProgressionEvent,
    ResourceEvent,
    SessionStartEvent,
    SessionEndEvent,
    InitLevelEvent,
    EndLevelEvent
};

class TrackerEvent {
public:
    EventType type;

    TrackerEvent();
   
    virtual ~TrackerEvent() = default;

    // Common attributes for all events, tracker should fill these in TrackEvent()
    long Timestamp = 0;
    std::string event_ID = "EVENT_ID";
    std::string session_ID = "SESSION_ID";
    std::string event_type = "ProgressionEvent";

    std::string ToJson() const;

private:
    std::string EventTypeToString(EventType type) const;
    const std::string separator = ";";
};