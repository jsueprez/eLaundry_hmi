#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <json/json.h>

struct NovaLocker
{
    int id {};
    std::string type {};
    bool locked {};
    int pinNumber {};
    // ...
};

class NovaDb
{
public:
    NovaDb(const std::string &p_filesystem);
    ~NovaDb()
    {
        if(m_ifs.is_open()) { m_ifs.close();}
    }

    int get_total_novaLocker() const ;
    NovaLocker get_novaLocker_info(int p_id) const;

private:
    std::string m_filename;
    std::ifstream m_ifs;
    std::vector<NovaLocker> m_novaLockers;
    int m_total_novaLockers;

    int read();
};
