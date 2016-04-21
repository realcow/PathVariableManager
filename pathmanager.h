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
    bool deregisterPath(const std::string& name);
    boost::optional<std::string> getPathByName(const std::string& name);
    void enumerate(std::function<void(const std::string&, const std::vector<std::string>&)> callback);

private:
    struct Entry
    {
        std::string name;
        std::vector<std::string> pathes;
    };

    std::vector<Entry> entries_;
};