#include"../server/log.h"
#include"../server/config.h"
#include<yaml-cpp/yaml.h>

sylar::ConfigVar<int>::ptr g_int = sylar::Config::Lookup("system.port", 8080, "system port");

void print_yaml(const YAML::Node& node, int level)
{
    if (node.IsScalar())
    {
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << std::string(level*4, ' ')
            << node.Scalar() << " - " << node.Type() << " - " << level;
    }else if (node.IsNull())
    {
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << std::string(level*4, ' ')
            << "NULL - " << node.Type() << " - " << level;
    }else if (node.IsMap())
    {
        for (auto it = node.begin();
                it != node.end(); ++it)
        {
            SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << std::string(level*4, ' ')
                 << it->first << " - " << it->second.Type() << " - " << level;
            print_yaml(it->second, level + 1);
        }
    }else if (node.IsSequence())
    {
        for (size_t i = 0; i < node.size(); ++i)
        {
            SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << std::string(level*4, ' ')
                 << i << " - " << node[i].Type() << " - " << level;
            print_yaml(node[i], level + 1);
        }
    }
}

void test_yaml()
{
    YAML::Node root = YAML::LoadFile("/home/pointer/mryang/LinuxServer/bin/config/log.yml");
    print_yaml(root, 0);
}

void test_config()
{
    SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "before: " << g_int->getValue();
    std::cout << g_int << std::endl;
    YAML::Node root = YAML::LoadFile("/home/pointer/mryang/LinuxServer/bin/config/log.yml");
    sylar::Config::LoadFromYaml(root);
    SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "after: " << g_int->getValue();
}

int main()
{
//    test_yaml();
    test_config();
    return 0;
}
