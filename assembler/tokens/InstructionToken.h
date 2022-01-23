#pragma once

#include <cstdint>

#include "../shared.h"
#include "Token.h"


class InstructionToken : public Token {
public:
    static const uint16_t TYPE_ID = __COUNTER__;
    SET_DEBUG_NAME(INSTRUCTION)

    InstructionToken(AbstractInstruction instr, std::string& instr_name, uint64_t line) :
        Token(TYPE_ID, line), m_instr(instr), m_instr_name(instr_name) {

    }

    [[nodiscard]] AbstractInstruction get_instr() const {
        return m_instr;
    }

    [[nodiscard]] const std::string &get_instr_name() const {
        return m_instr_name;
    }

private:
    AbstractInstruction m_instr;
    std::string m_instr_name;
};