#pragma once

#include <vector>
#include "Person.hpp"

class Family
{
public:
    Family();
    ~Family() {}

    void from_json(const nlohmann::json& j, std::map<std::string, std::shared_ptr<Person>>& persons_map);

private:
    std::shared_ptr<Person> create_or_update_person(const nlohmann::json& person_json, const std::string& family_name, std::map<std::string, std::shared_ptr<Person>>& persons_map);
};
