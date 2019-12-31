#ifndef __SYLAR_CONFIG_H__
#define __SYLAR_CONFIG_H__

#include<memory>
#include<string>
#include<map>
#include<boost/lexical_cast.hpp>
#include"log.h"

namespace sylar{
class ConfigVarBase {
public:
    typedef std::shared_ptr<ConfigVarBase> ptr;
    ConfigVarBase(const std::string &name, const std::string &description)
        :m_name(name),
        m_description(description)
    {
    }
    virtual ~ConfigVarBase(){}
    std::string &getName() { return m_name; }
    std::string &getDescription() { return m_description; }
    virtual std::string toString() = 0;
    virtual bool fromString(const std::string &val) = 0;

protected:
    std::string m_name;
    std::string m_description;
};

template<class T>
class ConfigVar: public ConfigVarBase
{
public:
    typedef std::shared_ptr<ConfigVar> ptr;
    ConfigVar(const std::string &name,
              const T& default_value,
              const std::string &description = "")
        :ConfigVarBase(name, description),
         m_val(default_value)
    {
    }
    std::string toString() override
    {
        try {
            return boost::lexical_cast<std::string>(m_val);
        }
        catch (std::exception& e){
            SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "config: toString error " << e.what();            
        }
        return "";
    }
    bool fromString(const std::string &val) override
    {
        try{
            m_val = boost::lexical_cast<T>(m_val);
        }
        catch (std::exception& e){
            SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "config: fromString error " << e.what();
        }
        return true;
    }
    T getValue() { return m_val; }
private:
    T m_val;
};

class Config
{
public:
    typedef std::map<std::string, ConfigVarBase::ptr> ConfigVarMap;
    template<class T>
    static typename ConfigVar<T>::ptr Lookup(const std::string &name, const T& default_vale,
            const std::string &description = "")
    {
        auto tmp = Lookup<T>(name);
        if (tmp)
        {
            SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "config: lookup name exists " << name;
            return tmp;
        }
        if (name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ._0123456789")
                != std::string::npos)
        {
            SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "config: name invalid";
            throw std::invalid_argument(name);
        }
        typename ConfigVar<T>::ptr v(new ConfigVar<T>(name, default_vale, description));
        s_datas[name] = v;
        return v;
    }
    template<class T>
    static typename ConfigVar<T>::ptr Lookup(const std::string &name)
    {
        auto it = s_datas.find(name);
        if (it == s_datas.end())
        {
            return nullptr;

        }
        return std::dynamic_pointer_cast<ConfigVar<T>>(it->second);
    }
private:
    static ConfigVarMap s_datas;
};

};

#endif
