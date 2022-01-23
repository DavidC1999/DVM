#include "Assembler.h"

#include <sstream>
#include <stdexcept>
#include <array>
#include <iostream>
#include "tokens/WordToken.h"
#include "tokens/NumberToken.h"
#include "tokens/RegisterToken.h"
#include "tokens/InstructionToken.h"
#include "tokens/LabelToken.h"
#include "tokens/CommaToken.h"

void Assembler::expect_more_tokens(const token_list_t::iterator &it, uint8_t amt) {
    token_list_t::iterator it_cpy = it;
    for (uint8_t i = 0; i < amt; ++i) {
        ++it_cpy;
        if (it_cpy == m_tokens.end()) {
            std::stringstream error_msg;
            error_msg << "Expected " << (int) amt << " more tokens for instruction, found " << (int) i;
            panic(error_msg.str(), **it);
        }
    }
}

template<class T>
void Assembler::expect_token_type(const Token &token) {
    if (token.get_type_id() != T::TYPE_ID) {
        std::stringstream error_msg;
        error_msg << "expected " << T::DEBUG_NAME << " token, found " << token << " instead";
        panic(error_msg.str(), token);
    }
}

// Big-endian
std::vector<uint8_t> Assembler::num_to_bytes(uint64_t num) {
    std::vector<uint8_t> output(8);

    for (int8_t i = 7; i >= 0; --i) {
        uint8_t masked = num & 0xFF;
        output[i] = masked;
        num >>= 8;
    }

    return output;
}

program_t Assembler::assemble() {
    auto it = m_tokens.begin();

    while (it != m_tokens.end()) {

        switch ((*it)->get_type_id()) {
            case InstructionToken::TYPE_ID: {
                parse_instruction(it);
                break;
            }
            case LabelToken::TYPE_ID: {
                uint64_t addr = 0;
                for (const auto &bytes : m_program) {
                    addr += bytes.get_byte_amt();
                }
                LabelToken label_token = *(LabelToken *) (*it).get();
                m_symbol_table.insert(std::make_pair(label_token.get_name(), addr));
                ++it;
                break;
            }

            default: {
                std::stringstream error_msg;
                error_msg << "Unexpected token: " << (**it);
                panic(error_msg.str(), **it);
            }

        }
    }

    std::cout << "------------------" << std::endl;
    std::cout << "Symbol table: " << std::endl;
    for (auto const& [symbol_name, symbol_value] : m_symbol_table) {
        std::cout << "    " << symbol_name << ": " << symbol_value << std::endl;
    }
    std::cout << "------------------" << std::endl;

    // fill in the blanks:
    program_t program;
    for (const AssemblerBytes &bytes : m_program) {
        if (bytes.is_unknown()) {
            if (m_symbol_table.contains(bytes.get_name())) {
                std::vector<uint8_t> to_insert = num_to_bytes(m_symbol_table[bytes.get_name()]);
                program.insert(program.end(), to_insert.begin(), to_insert.end());
                continue;
            }
            std::stringstream error_msg;
            error_msg << "Unresolved word: " << bytes.get_name();
            panic(error_msg.str(), bytes.get_line_num());
        }
        std::vector<uint8_t> to_insert = bytes.get_bytes();
        program.insert(program.end(), to_insert.begin(), to_insert.end());
    }

    return program;
}


void Assembler::parse_instruction(token_list_t::iterator &it) {
    AbstractInstruction instruction = ((InstructionToken *) (*it).get())->get_instr();

    switch (instruction) {
        case ABSTR_INSTR_MOV: {
            parse_binary_reg_instruction(INSTR_MOV_IMM, INSTR_MOV_REG, it);
            break;
        }
        case ABSTR_INSTR_LD: {
            parse_binary_reg_instruction(INSTR_LD_IMM, INSTR_LD_REG, it);
            break;
        }
        case ABSTR_INSTR_ST: {
            parse_binary_reg_instruction(INSTR_ST_IMM, INSTR_ST_REG, it);
            break;
        }
        case ABSTR_INSTR_ADD: {
            parse_binary_reg_instruction(INSTR_ADD_IMM, INSTR_ADD_REG, it);
            break;
        }
        case ABSTR_INSTR_SUB: {
            parse_binary_reg_instruction(INSTR_SUB_IMM, INSTR_SUB_REG, it);
            break;
        }
        case ABSTR_INSTR_MUL: {
            parse_binary_reg_instruction(INSTR_MUL_IMM, INSTR_MUL_REG, it);
            break;
        }
        case ABSTR_INSTR_DIV: {
            parse_binary_reg_instruction(INSTR_DIV_IMM, INSTR_DIV_REG, it);
            break;
        }
        case ABSTR_INSTR_OR: {
            parse_binary_reg_instruction(INSTR_OR_IMM, INSTR_OR_REG, it);
            break;
        }
        case ABSTR_INSTR_NOR: {
            parse_binary_reg_instruction(INSTR_NOR_IMM, INSTR_NOR_REG, it);
            break;
        }
        case ABSTR_INSTR_AND: {
            parse_binary_reg_instruction(INSTR_AND_IMM, INSTR_AND_REG, it);
            break;
        }
        case ABSTR_INSTR_NAND: {
            parse_binary_reg_instruction(INSTR_NAND_IMM, INSTR_NAND_REG, it);
            break;
        }
        case ABSTR_INSTR_XOR: {
            parse_binary_reg_instruction(INSTR_XOR_IMM, INSTR_XOR_REG, it);
            break;
        }
        case ABSTR_INSTR_XNOR: {
            parse_binary_reg_instruction(INSTR_XNOR_IMM, INSTR_XNOR_REG, it);
            break;
        }
        case ABSTR_INSTR_NOT: {
            expect_more_tokens(it, 1);
            ++it;
            expect_token_type<RegisterToken>(**it);
            RegisterToken register_token = *(RegisterToken *) ((*it).get());
            ++it;

            m_program.emplace_back(INSTR_NOT_REG);
            m_program.emplace_back(register_token.get_reg());

            break;
        }
        case ABSTR_INSTR_CMP: {
            parse_binary_reg_instruction(INSTR_CMP_IMM, INSTR_CMP_REG, it);
            break;
        }
        case ABSTR_INSTR_JMP: {
            parse_jmp_instruction(INSTR_JMP, it);
            break;
        }
        case ABSTR_INSTR_JMP_G: {
            parse_jmp_instruction(INSTR_JMP_G, it);
            break;
        }
        case ABSTR_INSTR_JMP_GE: {
            parse_jmp_instruction(INSTR_JMP_GE, it);
            break;
        }
        case ABSTR_INSTR_JMP_L: {
            parse_jmp_instruction(INSTR_JMP_L, it);
            break;
        }
        case ABSTR_INSTR_JMP_LE: {
            parse_jmp_instruction(INSTR_JMP_LE, it);
            break;
        }
        case ABSTR_INSTR_JMP_E: {
            parse_jmp_instruction(INSTR_JMP_E, it);
            break;
        }
        case ABSTR_INSTR_JMP_NE: {
            parse_jmp_instruction(INSTR_JMP_NE, it);
            break;
        }
        case ABSTR_INSTR_OUT: {
            parse_unary_reg_instruction(INSTR_OUT_IMM, INSTR_OUT_REG, it);
//            expect_more_tokens(it, 1);
//            ++it;
//
//
//            uint16_t type_id = (*it)->get_type_id();
//            if (type_id == RegisterToken::TYPE_ID) {
//                m_program.emplace_back(INSTR_OUT_REG);
//                RegisterToken register_token = *(RegisterToken *) ((*it).get());
//                m_program.emplace_back(register_token.get_reg());
//            } else if (type_id == NumberToken::TYPE_ID) {
//                m_program.emplace_back(INSTR_OUT_IMM);
//                NumberToken number = *(NumberToken *) ((*it).get());
//                std::vector<uint8_t> bytes = num_to_bytes(number.get_num());
//                m_program.emplace_back(bytes);
//            } else if (type_id == WordToken::TYPE_ID) {
//                m_program.emplace_back(INSTR_OUT_IMM);
//
//                // add a placeholder:
//                WordToken word_token = *(WordToken *) (*it).get();
//                m_program.emplace_back(word_token.get_word(), 8, word_token.get_line());
//            } else {
//                std::stringstream error_msg;
//                error_msg << "Expected register, word, or number token, but found " << **it << " instead";
//                panic(error_msg.str(), **it);
//            }
//            ++it;

            break;
        }
        case ABSTR_INSTR_PUSH: {
            parse_unary_reg_instruction(INSTR_PUSH_IMM, INSTR_PUSH_REG, it);
            break;
        }
        case ABSTR_INSTR_POP: {
            expect_more_tokens(it, 1);
            ++it;
            expect_token_type<RegisterToken>(**it);
            const RegisterToken *register_token = (RegisterToken *) ((*it).get());
            ++it;
            m_program.emplace_back(INSTR_POP);
            m_program.emplace_back(register_token->get_reg());
            break;
        }
        case ABSTR_INSTR_HALT: {
            m_program.emplace_back(INSTR_HALT);
            ++it;
            break;
        }
    }

}

void Assembler::parse_binary_reg_instruction(Instruction instr_imm, Instruction instr_reg, token_list_t::iterator &it) {
    expect_more_tokens(it, 2);

    ++it;
    expect_token_type<RegisterToken>(**it);

    const RegisterToken *register_token_to = (RegisterToken *) ((*it).get());
    ++it;

    // optional comma token:
    if ((*it)->get_type_id() == CommaToken::TYPE_ID) {
        ++it;
    }

    if ((**it).get_type_id() == RegisterToken::TYPE_ID) {
        m_program.emplace_back(instr_reg);
        m_program.emplace_back(register_token_to->get_reg());

        RegisterToken register_token_from = *(RegisterToken *) ((*it).get());
        m_program.emplace_back(register_token_from.get_reg());
    } else if ((**it).get_type_id() == NumberToken::TYPE_ID) {
        m_program.emplace_back(instr_imm);
        m_program.emplace_back(register_token_to->get_reg());

        NumberToken number = *(NumberToken *) ((*it).get());
        std::vector<uint8_t> bytes = num_to_bytes(number.get_num());
        m_program.emplace_back(bytes);
    } else if ((**it).get_type_id() == WordToken::TYPE_ID) {
        m_program.emplace_back(instr_imm);
        m_program.emplace_back(register_token_to->get_reg());

        // add a placeholder:
        WordToken word_token = *(WordToken *) (*it).get();
        m_program.emplace_back(word_token.get_word(), 8, word_token.get_line());
    } else {
        std::stringstream error_msg;
        error_msg << "Expected token type register, number or word, found " << (**it) << " instead";
        panic(error_msg.str(), **it);
    }

    ++it;
}

void Assembler::parse_unary_reg_instruction(Instruction instr_imm, Instruction instr_reg, std::list<std::unique_ptr<Token>>::iterator &it) {
    expect_more_tokens(it, 1);
    ++it;

    uint16_t type_id = (*it)->get_type_id();
    if (type_id == RegisterToken::TYPE_ID) {
        m_program.emplace_back(instr_reg);
        RegisterToken register_token = *(RegisterToken *) ((*it).get());
        m_program.emplace_back(register_token.get_reg());
    } else if (type_id == NumberToken::TYPE_ID) {
        m_program.emplace_back(instr_imm);
        NumberToken number = *(NumberToken *) ((*it).get());
        std::vector<uint8_t> bytes = num_to_bytes(number.get_num());
        m_program.emplace_back(bytes);
    } else if (type_id == WordToken::TYPE_ID) {
        m_program.emplace_back(instr_imm);

        // add a placeholder:
        WordToken word_token = *(WordToken *) (*it).get();
        m_program.emplace_back(word_token.get_word(), 8, word_token.get_line());
    } else {
        std::stringstream error_msg;
        error_msg << "Expected register, word, or number token, but found " << **it << " instead";
        panic(error_msg.str(), **it);
    }
    ++it;
}


void Assembler::parse_jmp_instruction(Instruction jmp_instr, token_list_t::iterator &it) {
    expect_more_tokens(it, 1);
    ++it;

    m_program.emplace_back(jmp_instr);

    uint16_t type_id = (*it)->get_type_id();
    if (type_id == WordToken::TYPE_ID) {
        WordToken word = *(WordToken *) (*it).get();
        m_program.emplace_back(word.get_word(), 8, word.get_line());
    } else if (type_id == NumberToken::TYPE_ID) {
        NumberToken number = *(NumberToken *) ((*it).get());
        std::vector<uint8_t> bytes = num_to_bytes(number.get_num());
        m_program.emplace_back(bytes);
    } else {
        std::stringstream error_msg;
        error_msg << "Expected word token or number token, but found " << **it << " instead";
        panic(error_msg.str(), **it);
    }
    ++it;
}


void Assembler::panic(const std::string &message, const Token &token) {
    panic(message, token.get_line());
}

void Assembler::panic(const std::string &message, uint64_t line_num) {
    std::cerr << "Panic in assembler on line " << line_num << ": " << message << std::endl;
    std::exit(1);
}
