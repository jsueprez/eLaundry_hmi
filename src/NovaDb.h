#pragma once

#include <INovaDb.h>
#include <nova_db_types.h>

#include <string>
#include <vector>
#include <fstream>
#include <json/json.h>

class NovaDB : public INovaDB
{
public:
    NovaDB() = default;
    ~NovaDB() override = default;

    void set_interface(void *p_interface, const char *p_class) override final;
    void init_db() override final;

    int get_total_novaLocker() const override final;
    NovaLocker get_novaLocker_info(int p_id) const override final;
    std::vector<NovaLocker> get_all_novaLockers() const override final;

private:
    std::string m_filename;
    std::ifstream m_ifs;
    std::vector<NovaLocker> m_novaLockers;
    int m_total_novaLockers;

    int read();
};
