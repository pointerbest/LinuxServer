#include"config.h"

namespace sylar{
Config::ConfigVarMap Config::s_datas;

ConfigVarBase::ptr Config::LookupBase(const std::string &name)
{
    auto it = s_datas.find(name);
    return it == s_datas.end() ? nullptr : it->second;
}

static void ListAllMember(const std::string &prefix, const YAML::Node& node,
                            std::list<std::pair<std::string, const YAML::Node>> &output)
{
    if (prefix.find_first_not_of("abcdefghijklmnopqrstuvwxyz.0123456789") != std::string::npos)
    {
        SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "config: invalid name";
        return;
    }
    output.push_back(std::make_pair(prefix, node));
    if (node.IsMap())
    {
        for (auto it = node.begin(); it != node.end(); ++it)
        {
            ListAllMember(prefix.empty() ? it->first.Scalar():prefix+"."+it->first.Scalar(),
                    it->second, output);
        }
    }
}

void Config::LoadFromYaml(const YAML::Node& node)
{
    std::list<std::pair<std::string, const YAML::Node>> all_nodes;
    ListAllMember("", node, all_nodes);

    for (auto& i : all_nodes)
    {
        std::string key = i.first;
        if (key.empty())
        {
            continue;
        }
        std::transform(key.begin(), key.end(), key.begin(), ::tolower);

        ConfigVarBase::ptr var = LookupBase(key);
        if (var)
        {
            std::cout << key << std::endl;
            if (i.second.IsScalar())
            {
                var->fromString(i.second.Scalar());
                std::cout << var << std::endl;
            }
            else
            {
                std::stringstream ss;
                ss << i.second;
//                std::cout << ss.str();
                var->fromString(ss.str());
            }
        }
    }
}

};
