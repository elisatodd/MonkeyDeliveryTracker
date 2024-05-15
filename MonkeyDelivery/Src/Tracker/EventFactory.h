#pragma once
#include "MissionStartEvent.h"
#include "MissionEndEvent.h"

class EventFactory {
public:
	EventFactory();
	~EventFactory();

	MissionStartEvent* getMissionStartEvent();
	MissionEndEvent* getMissionEndEvent();
};