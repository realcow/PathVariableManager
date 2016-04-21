#include "pathmanager.h"
#include "yaml-cpp\yaml.h"
#include <fstream>

using namespace std;

bool PathManager::load(const std::string& filename)
{
    ifstream fin(filename);
    if (!fin.is_open())
    {
        return false;
    }
    YAML::Node doc = YAML::Load(fin);
    entries_.clear();
    for (auto& entryNode : doc["entries"])
    {
        Entry entry;
        entry.name = entryNode["name"].as<string>();
        for (auto& path : entryNode["pathes"])
        {
            string v = path.as<string>();
            entry.pathes.push_back(v);
        }
        entries_.push_back(entry);
    }
    return true;
}

void PathManager::save(const std::string& filename)
{
    YAML::Node doc;
    for (auto& entry : entries_)
    {
        YAML::Node entryNode;
        entryNode["name"] = entry.name;

        YAML::Node pathesNode;
        for (auto& e : entry.pathes)
        {
            pathesNode.push_back(e);
        }
        entryNode["pathes"] = pathesNode;

        doc["entries"].push_back(entryNode);
    }

    std::ofstream fout(filename);
    fout << doc;
}

bool PathManager::registerPath(const std::string& name, const std::string& path)
{
    for (auto& e : entries_)
    {
        if (e.name == name)
        {
            return false;
        }
    }
    entries_.push_back({name, {path}});
    return true;
}

boost::optional<std::string> PathManager::getPathByName(const std::string & name)
{
    for (auto& e : entries_)
    {
        if (e.name == name)
        {
            string s;
            for (string& path : e.pathes)
            {
                s += path + ";";
            }
            s.pop_back();
            return s;
        }
    }
    return{};
}
