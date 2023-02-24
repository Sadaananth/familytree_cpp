#pragma once

#include "inc/json.hpp"

namespace utils {

template<typename fieldType>
void fillFromJson(nlohmann::json json, const std::string& key, fieldType& field)
{
    if(json.contains(key)) {
        json.at(key).get_to<fieldType>(field);
    }
}


template<typename fieldType>
void fillFromJson(nlohmann::json json, const std::string& key, fieldType& field, fieldType defaultValue)
{
    if(json.contains(key)) {
        json.at(key).get_to<fieldType>(field);
    } else {
        field = defaultValue;
    }
}

}
