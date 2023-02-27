#pragma once

#include <vector>
#include "Person.hpp"

class Family
{
public:
    Family();
    ~Family() {}

    void from_json(const nlohmann::json& j, std::map<std::string, std::shared_ptr<Person>>& persons_map);
};
