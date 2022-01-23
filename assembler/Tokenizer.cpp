#include "Tokenizer.h"

#include <cctype>
#include <cstdint>
#include <iostream>
#include <memory>
#include <regex>

bool Tokenizer::is_alphanum(char c) {
    return (c >= 'A' && c <= 'z') || (c >= '0' && c <= '9');
}

bool Tokenizer::is_digit(char c) {
    return c >= '0' && c <= '9';
}



std::string Tokenizer::str_tolower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return s;
}

token_list_t Tokenizer::tokenize() {
    auto it = m_text.begin();

    // regex used to decide if a word is a register token
    std::regex register_regex("^r(\\d+)$", std::regex_constants::icase);

    while (it != m_text.end()) {
        switch (*it) {
            case '\n':
                ++m_curr_line;
                __attribute__ ((fallthrough));
            case ' ':
                __attribute__ ((fallthrough));
            case '\r':
                ++it;
                continue;
        }

        if(*it == ';') {
            while(it != m_text.end() && *it != '\n') {
                ++it;
            }
        } else if(*it == '/') { // multi-line comments
            ++it;
            if(*it == '*') {
                bool about_to_end = false;
                while(true) {
                    ++it;
                    if(it == m_text.end()) {
                        break;
                    } else if(*it == '*') {
                        about_to_end = true;
                    } else if(about_to_end && *it == '/') {
                        ++it;
                        break;
                    } else {
                        about_to_end = false;
                    }
                }
            } else {
                std::stringstream error_msg;
                error_msg << "Unexpected character: " << *it << " (" << (int)(*it) << ")";
                panic(error_msg.str());
            }
        } else if(*it == ',') {
            m_tokens.push_back(std::make_unique<CommaToken>(m_curr_line));
            ++it;
        } else if (is_digit(*it)) {
            std::string digits = get_digits(it);
            uint64_t num = std::stoi(digits);

            m_tokens.push_back(std::make_unique<NumberToken>(num, m_curr_line));
        } else if (is_alphanum(*it)) {
            std::string word = get_word(it);

            std::smatch match;
            // check if it is a register
            if (std::regex_match(word, match, register_regex)) {
                uint8_t reg_num = std::stoi(match.str(1));
                if (reg_num > 15) {
                    panic("Registers go up to 15");
                }
                m_tokens.push_back(std::make_unique<RegisterToken>(reg_num, m_curr_line));
                continue;  // we're done here
            }
            
            // check if it is an instruction
            std::string word_lower = str_tolower(word);
            if (instructions.find(word_lower) != instructions.end()) {
                m_tokens.push_back(std::make_unique<InstructionToken>(instructions[word_lower], word, m_curr_line));
                continue;  // we're done here
            }

            // check if it is a label:
            if(*it == ':') {
                m_tokens.push_back(std::make_unique<LabelToken>(word, m_curr_line));
                ++it;
                continue;
            }

            // it is not an instruction, register, or a label so just add it as a word
            m_tokens.push_back(std::make_unique<WordToken>(word, m_curr_line));

        } else {
            std::stringstream error_msg;
            error_msg << "Unexpected character: " << *it << " (" << (int)(*it) << ")";
            panic(error_msg.str());
        }
    }

    std::cout << "Done tokenizing" << std::endl;

    return std::move(m_tokens);
}

std::string Tokenizer::get_word(std::string::iterator& it) {
    std::stringstream acc;

    while (is_alphanum(*it)) {
        acc << *it;
        ++it;
    }

    return acc.str();
}

std::string Tokenizer::get_digits(std::string::iterator& it) {
    std::stringstream acc;

    while (is_digit(*it)) {
        acc << *it;
        ++it;
    }

    return acc.str();
}

// void Tokenizer::panic(const char* message) {
//     panic(std::string(message));
// }

void Tokenizer::panic(const std::string &message) const {
    std::cerr << "Panic in tokenizer on line " << m_curr_line << ": " << message << std::endl;
    std::exit(1);
}