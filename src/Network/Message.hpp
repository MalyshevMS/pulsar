#pragma once
#pragma voice

#include "../lib/json.hpp"
#include "Datetime.hpp"

#include <string>
#include <chrono>

#ifndef PULSAR_CURRENT_USERNAME
#   define PULSAR_CURRENT_USERNAME
#   error "PULSAR_CURRENT_USERNAME is not defined"
#endif

using Json = nlohmann::json;

class Message {
private:
    std::string dest; // Destination username (or id)
    std::string targ = *PULSAR_CURRENT_USERNAME; // Target username (or id)

    std::string msg; // Message text
    Datetime date; // Date and time of the message
public:
    Message(const std::string& text, const std::string& destination) {
        msg = text;
        dest = destination;
        date = Datetime::now();
    }

    Json toJson() const {
        return Json({
            {"dest", dest},
            {"targ", targ},
            {"msg", msg},
            {"date", date.toTime()}
        });
    }

    std::string toString() const {
        auto json = toJson();
        std::stringstream ss;
        ss << json;
        return ss.str();
    }
};