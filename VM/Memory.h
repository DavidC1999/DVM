#pragma once

#include <map>
#include <cstdint>

#include "../general.h"


class Memory {
public:
    void load_program(const program_t& program);

    uint8_t get_value(uint64_t addr);
    uint64_t get_value_64(uint64_t addr);

    void set_value(uint64_t addr, uint8_t value);
    void set_value_64(uint64_t addr, uint64_t value);

    void print_contents();
private:
    std::map<uint64_t, uint64_t> m_contents;
};
