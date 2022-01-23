#pragma once

//#include "shared.h"
//#include "../general_types.h"

#include <string>
#include <cstdint>
#include <array>
#include <utility>
#include <vector>

// the assembler constructs the program with instances of this class
// this is done to allow for placeholder values which will be filled in later
class AssemblerBytes {
public:

    // for known bytes
    explicit AssemblerBytes(uint8_t byte)
            : m_bytes(std::vector{byte}), m_byte_amt(1), m_unknown(false), m_line_num(0) {}

    explicit AssemblerBytes(std::vector<uint8_t> bytes)
            : m_bytes(std::move(bytes)), m_byte_amt(m_bytes.size()), m_unknown(false), m_line_num(0) {}

    // for unknown words
    AssemblerBytes(std::string name, uint8_t byte_amt, uint64_t line_num)
            : m_byte_amt(byte_amt), m_unknown(true), m_name(std::move(name)), m_line_num(line_num) {}

    [[nodiscard]] const std::vector<uint8_t> &get_bytes() const {
        return m_bytes;
    }

    [[nodiscard]] bool is_unknown() const {
        return m_unknown;
    }

    [[nodiscard]] const std::string &get_name() const {
        return m_name;
    }

    [[nodiscard]] uint8_t get_byte_amt() const {
        return m_byte_amt;
    }

    [[nodiscard]] uint64_t get_line_num() const {
        return m_line_num;
    }

private:
    std::vector<uint8_t> m_bytes; // if the bytes are known, they are stored here
    uint8_t m_byte_amt;           // stores the byte amount, placeholder or not

    bool m_unknown;               // stores if the value is unknown (meaning it is a placeholder)
    std::string m_name;           // if the value is unknown, stores the associated word
    uint64_t m_line_num;          // if the value is unknown, stores the line number of the placeholder
};