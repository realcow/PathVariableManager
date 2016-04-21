#pragma once

#include <boost/optional.hpp>
#include <string>
#include <vector>

class PathManager
{
public:
    bool load(const std::string& filename);
    void save(const std::string& filename);
    bool registerPath(const std::string& name, const std::string& path);
    boost::optional<std::string> getPathByName(const std::string& name);

private:
    struct Entry
    {
        std::string name;
        std::vector<std::string> pathes;
    };

    std::vector<Entry> entries_;
};