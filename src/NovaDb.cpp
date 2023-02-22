#include "NovaDb.h"

#include <cassert>
#include <iostream>
#include <string>

NovaDb::NovaDb(const std::string &p_filename)
    : m_filename{p_filename},
      m_ifs{m_filename, std::ios_base::in},
      m_novaLockers{},
      m_total_novaLockers{0}
{
    if(!m_ifs.is_open())
    {
        throw std::runtime_error{"Cannot open the json file: " + m_filename};
    }

    if ( this->read() ) {
        if ( m_ifs.is_open() ) {
            m_ifs.close();
        }
    }
}

int NovaDb::get_total_novaLocker() const
{
    return m_total_novaLockers;
}

NovaLocker NovaDb::get_novaLocker_info(int p_id) const
{
    return m_novaLockers[p_id - 1];
}

std::vector<NovaLocker> NovaDb::get_all_novaLockers() const
{
    return m_novaLockers;
}


int NovaDb::read()
{
    // The stream should be open by now!
    assert(this->m_ifs.is_open());

    Json::Value root;
    m_ifs >> root;

    const Json::Value novaLockers = root["NovaLockers"];

    m_total_novaLockers = novaLockers.size();

    for(auto index {0}; index < static_cast<int>(m_total_novaLockers); index++)
    {
        NovaLocker tmp {};
        std::string st;

        try {
            tmp.id = novaLockers[index]["Id"].asInt();
            tmp.locked = novaLockers[index]["Locked"].asBool();
            tmp.type = novaLockers[index]["Type"].asString();
            tmp.pinNumber = novaLockers[index]["PinNumber"].asInt();
        }  catch (std::exception& e) {
            std::cout << " a standard exception was caught, with message '"
                      << e.what() << "'\n";

            return 1;
        }

        m_novaLockers.push_back(tmp);
    }
    return 0;
}
