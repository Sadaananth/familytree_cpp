#pragma once

#include "json.hpp"
#include <optional>
#include <map>

namespace utils {

template<typename type>
void updateOnDiff(const type& input, type& output)
{
    if(input != output) {
        output = input;
    }
}

template<typename MapType>
std::optional<typename MapType::mapped_type> getFromMapOrOptional(const MapType& map, typename MapType::key_type key)
{
    if(auto itr = map.find(key); itr != map.end()) {
        return std::make_optional(itr->second);
    }

    return std::nullopt;
}

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
