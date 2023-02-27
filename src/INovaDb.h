#pragma once

#include <nova_db_types.h>

#include <vector>

class INovaDB
{
public:
    virtual ~INovaDB() = default;

    /**
    * @brief Set interface pointers
    */
    virtual void init_db() = 0;

    /**
    * @brief Set interface pointers
    */
    virtual int get_total_novaLocker() const = 0;

    /**
    * @brief Set interface pointers
    */
    virtual NovaLocker get_novaLocker_info(int p_id) const = 0;

    /**
    * @brief Set interface pointers
    */
    virtual std::vector<NovaLocker> get_all_novaLockers() const = 0;
};
