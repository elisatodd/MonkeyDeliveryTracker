#include "EventFactory.h"

EventFactory::EventFactory()
{
}

EventFactory::~EventFactory()
{
}

MissionStartEvent* EventFactory::getMissionStartEvent()
{
	return new MissionStartEvent();
}

MissionEndEvent* EventFactory::getMissionEndEvent()
{
	return new MissionEndEvent();
}
