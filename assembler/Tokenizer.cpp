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

        if (*it == ';') {
            while (it != m_text.end() && *it != '\n') {
                ++it;
            }
        } else if (*it == '/') { // multi-line comments
            ++it;
            if (*it == '*') {
                bool about_to_end = false;
                while (true) {
                    ++it;
                    if (it == m_text.end()) {
                        break;
                    } else if (*it == '*') {
                        about_to_end = true;
                    } else if (about_to_end && *it == '/') {
                        ++it;
                        break;
                    } else {
                        about_to_end = false;
                    }
                }
            } else {
                std::stringstream error_msg;
                error_msg << "Unexpected character: " << *it << " (" << (int) (*it) << ")";
                panic(error_msg.str());
            }
        } else if (*it == ',') {
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
            if (*it == ':') {
                m_tokens.push_back(std::make_unique<LabelToken>(word, m_curr_line));
                ++it;
                continue; // we're done here
            }

            // check if it is a macro
            if(m_macro_table.find(word) != m_macro_table.end()) {
                Macro macro = std::move(m_macro_table.at(word));
                expand_macro(m_tokens.end(), macro);
                continue;
            }

            // it is not an instruction, register, or a label so just add it as a word
            m_tokens.push_back(std::make_unique<WordToken>(word, m_curr_line));

        } else if (*it == '@') {
            ++it;
            std::string word = get_word(it);
            if (word == "macro") {
                if (*it != ' ')
                    panic("Expected space after \"@macro\"");
                ++it; // consume space
                define_macro(it);
            }
        } else {
            std::stringstream error_msg;
            error_msg << "Unexpected character: " << *it << " (" << (int) (*it) << ")";
            panic(error_msg.str());
        }
    }

    std::cout << "Done tokenizing" << std::endl;

    return std::move(m_tokens);
}

std::string Tokenizer::get_word(std::string::iterator &it) {
    std::stringstream acc;

    while (is_alphanum(*it)) {
        acc << *it;
        ++it;
    }

    return acc.str();
}

std::string Tokenizer::get_digits(std::string::iterator &it) {
    std::stringstream acc;

    while (is_digit(*it)) {
        acc << *it;
        ++it;
    }

    return acc.str();
}


// if not the end, does not modify the iterator
// if it is the end, moves iterator past the end
bool Tokenizer::is_end_macro(std::string::iterator &it) {
    std::string to_compare = "@end";

    for (uint8_t i = 0; i < to_compare.size(); ++i) {
        if ((it + i) == m_text.end()) {
            panic("Macro definition has no end");
        }

        if (*(it + i) != to_compare[i]) return false;
    }

    it += (int) to_compare.size();
    return true;
}

void Tokenizer::define_macro(std::string::iterator &it) {
    std::string name = get_word(it);

    // parse optional arguments:
    // commented out because of complexity before meat of macros are implemeted.
    // implement macro body first
//    std::vector<std::string> args;
//    if (*it == '(') {
//        if (*(it + 1) != ')') { // if any arguments are given
//            do {
//                ++it;
//                std::string word = get_word(it); // get argument name
//                if (word.empty()) { // if no word was found, throw error
//                    std::stringstream error_msg;
//                    error_msg << "Unexpected character: " << *it;
//                    panic(error_msg.str());
//                }
//                args.emplace_back(word); // if a word was found, add it to the argument list
//            } while (*it == ','); // find next argument if there are more
//
//            if (*it != ')') {
//                panic("Expected ')' at the end of a macro argument list");
//            }
//            ++it;
//        } else {
//            it += 2;
//        }
//    }

    if (*it != ':') {
        std::stringstream error_msg;
        error_msg << "Unexpected character: " << *it << " (" << (int) (*it) << ")";
        panic(error_msg.str());
    }
    ++it;

    token_list_t body;

    std::stringstream acc;
    while (!is_end_macro(it)) {
        acc << *it;
        ++it;
    }

    Tokenizer macro_tokenizer(acc.str());
    try {
        body = macro_tokenizer.tokenize();
    } catch (std::exception &e) {
        std::stringstream error_msg;
        error_msg << "Error in macro body: " << std::endl;
        error_msg << "    " << e.what();
        panic(error_msg.str());
    }

    m_macro_table.insert(std::make_pair(name, Macro(name, std::move(body), m_curr_line)));
}

void Tokenizer::expand_macro(token_list_t::iterator macro_start, Macro &macro) {

    // if expanding on word token, remove the word token first:
    if(macro_start != m_tokens.end()) {
        if((*macro_start)->get_type_id() != WordToken::TYPE_ID) {
            panic("Trying to expand macro on non-word token. This is a bug in the Tokenizer.");
        }

        macro_start = m_tokens.erase(macro_start);
    }

    // get the macro body, and insert it to the token list
    token_list_t macro_body = std::move(macro.get_body());
    size_t macro_body_size = macro_body.size();
    m_tokens.splice(macro_start, macro_body);
    macro_start = std::prev(macro_start, (int)macro_body_size); // splice moves the iterator, move it back


    // loop through the inserted tokens, and see if there are more macros to expand:
    auto curr_token = macro_start;
    auto end_token = std::next(macro_start, (int)macro_body_size);
    while(curr_token != end_token) {
        if((**curr_token).get_type_id() == WordToken::TYPE_ID) {
            const WordToken *word_token = (WordToken*)((*curr_token).get());
            std::string word = word_token->get_word();

            if(m_macro_table.find(word) != m_macro_table.end()) {
                Macro submacro = std::move(m_macro_table.at(word));
                expand_macro(curr_token, submacro);
                ++curr_token;
                continue;
            }
        }

        ++curr_token;
    }
}

void Tokenizer::panic(const std::string &message) const {
    std::cerr << "Panic in tokenizer on line " << m_curr_line << ": " << message << std::endl;
    std::exit(1);
}
