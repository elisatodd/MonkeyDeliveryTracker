#include "TrackerEvent.h"

TrackerEvent::TrackerEvent() : type(EventType::ProgressionEvent), event_ID("EVENT_ID"), session_ID("SESSION_ID"), event_type("ProgressionEvent") 
{
}

std::string TrackerEvent::ToJson() const
{
	// TO_DO: Implement JSON serialization
	return ""; // Placeholder for JSON serialization
}

