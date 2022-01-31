#include "Token.h"

#include "Tokens.h"
#include "../Macro.h"

std::ostream& operator<<(std::ostream& os, const Token& token) {
    // os << token.get_name();

    int type_id = token.get_type_id();
    os << "<";
    if (type_id == WordToken::TYPE_ID) {
        const auto *word_token = dynamic_cast<const WordToken*>(&token);
        os << "WORD: " << word_token->get_word();
    } else if (type_id == RegisterToken::TYPE_ID) {
        const auto *register_token = dynamic_cast<const RegisterToken*>(&token);
        os << "REGISTER: " << register_token->get_reg();
    } else if (type_id == NumberToken::TYPE_ID) {
        const auto *number_token = dynamic_cast<const NumberToken*>(&token);
        os << "NUMBER: " << number_token->get_num();
    } else if (type_id == InstructionToken::TYPE_ID) {
        const auto *instruction_token = dynamic_cast<const InstructionToken*>(&token);
        os << "INSTRUCTION: " << instruction_token->get_instr_name();
    } else if (type_id == LabelToken::TYPE_ID) {
        const auto *label_token = dynamic_cast<const LabelToken*>(&token);
        os << "LABEL: " << label_token->get_name();
    } else if (type_id == CommaToken::TYPE_ID) {
        os << "COMMA";
    } else {
        os << "?";
    }
    os << ">";
    return os;
}
