#pragma once

#include "json.hpp"

#include <string>
#include <vector>

class Person
{
public:
    Person() {}
    Person(const std::string& line);
    ~Person() {}


    void to_json(nlohmann::json& j);
    void from_json(const nlohmann::json& j);

    void update_person(std::shared_ptr<Person>& person);
    void update_parent(const std::string& parent);
    void update_child(const std::string& child);
    void update_spouse(const std::string& spouse);

    void set_family_name(const std::string& family_name);

    const std::string& name() const;

    void display() const;

    bool has_parents() const;
    bool has_spouse() const;
    bool has_children() const;

    std::vector<std::string> parent_list() const;
    std::vector<std::string> spouse_list() const;
    std::vector<std::string> children_list() const;

    bool is_visited() const;
    void visited(bool visited);

private:
    uint32_t m_id;
    std::string m_name;
    std::string m_sex;
    std::string m_familyname;
    std::string m_villagename;
    bool m_visited{false};

    std::vector<std::string> m_parents_list;
    std::vector<std::string> m_children_list;
    std::vector<std::string> m_spouse_list;
};
