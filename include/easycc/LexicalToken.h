#ifndef EASYCC_CPP_LEXICALTOKEN_H
#define EASYCC_CPP_LEXICALTOKEN_H

#include <string>
#include <ostream>

namespace ecc {
    class LexicalToken {
    public:
        static const std::string END_OF_FILE;

        // Set the token types
        enum Type {
            ERROR_TOKEN,
            NORMAL_TOKEN,
            NORMAL_FINAL_TOKEN
        };

        LexicalToken(LexicalToken::Type type,std::string name, std::string value, int line, int column) :
                m_type(type), m_name(name), m_value(value), m_line(line), m_column(column),
                m_uid(LexicalToken::s_uid++){};

        /**
         * Get token name
         * @return token name
         */
        std::string getName() const {return this->m_name;}

        /**
         * Get token value
         * @return token value
         */
        std::string getValue() const {return this->m_value;}

        /**
         * Get token line
         * @return line
         */
        int getLine() const {return this->m_line;}

        /**
         * Get token column
         * @return column
         */
        int getColumn() const {return this->m_column;}

        /**
         * Get lexical token type
         * @return lexical token type
         */
        LexicalToken::Type getType() const {return this->m_type;}

        /**
         * Get a string representation of the lexical token
         */
        std::string getString();

        /**
         * Get a unique unsigned integer for a lexical token
         * across all compiled files
         */
        unsigned int getUID() {
            return m_uid;
        }

    private:
        std::string m_name;
        std::string m_value;
        int m_line;
        int m_column;
        static unsigned int s_uid;
        unsigned int m_uid;
        LexicalToken::Type m_type;
    };
}


#endif
