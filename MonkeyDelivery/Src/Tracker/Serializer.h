#pragma once
#include <string>

class TrackerEvent;  // Adelanto de la clase TrackerEvent

class Serializer {
public:
    std::string EndFileFormat();
    std::string GetFileExtension();
    std::string InitFileFormat();
    std::string serialize(TrackerEvent* trackerEvent);
};
