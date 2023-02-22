#include "NovaDb.h"

#include <cassert>
#include <iostream>
#include <string>

void NovaDB::init_db()
{
    const std::string filename = "db.json";
    m_ifs.open(filename, std::ios_base::in);

    if(!m_ifs.is_open())
    {
        throw std::runtime_error{"Cannot open the json file: " + filename};
    }

    if ( this->read() ) {
        if ( m_ifs.is_open() ) {
            m_ifs.close();
        }
    }
}

int NovaDB::get_total_novaLocker() const
{
    return m_total_novaLockers;
}

NovaLocker NovaDB::get_novaLocker_info(int p_id) const
{
    return m_novaLockers[p_id - 1];
}

std::vector<NovaLocker> NovaDB::get_all_novaLockers() const
{
    return m_novaLockers;
}


int NovaDB::read()
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
