#include <iostream>
#include "Memory.h"

void Memory::load_program(const program_t &program) {
    if (!m_contents.empty()) {
        throw std::logic_error("Trying to load program while other memory has already been written");
    }
    uint64_t addr = 0;
    for (uint8_t byte : program) {
        m_contents.emplace(std::make_pair(addr, byte));
        ++addr;
    }
}

uint8_t Memory::get_value(uint64_t addr) {
    auto it = m_contents.find(addr);
    if (it == m_contents.end()) return 0;

    uint8_t value = (*it).second;
    return value;
}

uint64_t Memory::get_value_64(uint64_t addr) {
    uint64_t output = 0;
    for (int i = 0; i < 8; ++i) {
        output <<= 8;
        output |= get_value(addr + i);
    }
    return output;
}

void Memory::set_value(uint64_t addr, uint8_t value) {
    if (m_contents.find(addr) == m_contents.end()) {
        m_contents.emplace(std::make_pair(addr, value));
    } else {
        m_contents[addr] = value;
    }
}

void Memory::set_value_64(uint64_t addr, uint64_t value) {
    for(int8_t i = 7; i >= 0; --i) {
        uint8_t byte = value & 0xFF;
        value >>= 8;
        if (m_contents.find(addr + i) == m_contents.end()) {
            m_contents.emplace(std::make_pair(addr + i, byte));
        } else {
            m_contents[addr + i] = byte;
        }
    }
}

void Memory::print_contents() {
    std::cout << "------------------" << std::endl;
    std::cout << "Memory contents: " << std::endl;
    for (auto const& [address, value] : m_contents) {
        std::cout << "    " << address << ": " << value << std::endl;
    }
    std::cout << "------------------" << std::endl;
}
