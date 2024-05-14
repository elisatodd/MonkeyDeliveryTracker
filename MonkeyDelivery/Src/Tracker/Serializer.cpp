
#include "Serializer.h"
#include "TrackerEvent.h"

// Asegúrate de usar std::string en todas partes
std::string Serializer::EndFileFormat()
{
    return "{}]}";
}

std::string Serializer::GetFileExtension()
{
    return ".json";
}

std::string Serializer::InitFileFormat()
{
    return "{\n \"Events\": [\n";
}

std::string Serializer::serialize(TrackerEvent* trackerEvent)
{
    // Asumiendo que TrackerEvent tiene un método ToJson()
    return trackerEvent->ToJson() + ",\n";
}
