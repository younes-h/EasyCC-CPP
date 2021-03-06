#include <easycc/SyntaxMessages.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/writer.h>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <sstream>

#include <iostream>

namespace ecc {

    std::shared_ptr<SyntaxMessages> SyntaxMessages::loadMessagesFromFile(std::string fileName) {
        std::ifstream ifs(fileName);
        rapidjson::IStreamWrapper isw(ifs);
        rapidjson::Document d;
        d.ParseStream(isw);
        return loadMessages(d);
    }

    std::shared_ptr<SyntaxMessages> SyntaxMessages::loadMessagesFromString(std::string data) {
        rapidjson::Document d;
        d.Parse(data.c_str());
        return loadMessages(d);
    }

    std::shared_ptr<SyntaxMessages> SyntaxMessages::loadMessages(rapidjson::Document &d) {

        // Configuration JSON format
        const char* ERROR_MESSAGES = "error_messages";
        const char* DEFAULT_MESSAGE = "default_message";
        const char* NON_TERMINAL = "non_terminal";
        const char* TERMINAL = "terminal";
        const char* MESSAGE = "message";

        // Prepare a new Config
        std::shared_ptr<SyntaxMessages> messages = std::make_shared<SyntaxMessages>();

        // Default message
        messages->m_defaultMessage = d[DEFAULT_MESSAGE].GetString();

        // Loop on all messages
        for(rapidjson::SizeType i=0; i < d[ERROR_MESSAGES].Size(); i++) {

            // Get error block information
            std::string nonTerminal = d[ERROR_MESSAGES][i][NON_TERMINAL].GetString();
            std::string terminal = d[ERROR_MESSAGES][i][TERMINAL].GetString();
            std::string message = d[ERROR_MESSAGES][i][MESSAGE].GetString();

            // Verify duplicates
            if(messages->m_errorMessages.find(nonTerminal) != messages->m_errorMessages.end() &&
                    messages->m_errorMessages[nonTerminal].find(terminal) != messages->m_errorMessages[nonTerminal].end()) {
                throw std::runtime_error("Message with non-terminal: " + nonTerminal +
                                         " and terminal: " + terminal + " is defined multiple times");
            }
            messages->m_errorMessages[nonTerminal][terminal] = message;
        }
        return messages;
    }

    std::string SyntaxMessages::getErrorMessage(std::string nonTerminal, std::string terminal) {

        // If non-terminal registered
        if(m_errorMessages.find(nonTerminal) != m_errorMessages.end()) {

            // If terminal registered in that non-terminal
            if(m_errorMessages[nonTerminal].find(terminal) != m_errorMessages[nonTerminal].end()) {
                return m_errorMessages[nonTerminal][terminal];

            } else if(m_errorMessages[nonTerminal].find(DEFAULT_TERMINAL_AND_NON_TERMINAL) !=
                        m_errorMessages[nonTerminal].end()) {
                return m_errorMessages[nonTerminal][DEFAULT_TERMINAL_AND_NON_TERMINAL];
            }
        } else if(m_errorMessages.find(DEFAULT_TERMINAL_AND_NON_TERMINAL) != m_errorMessages.end() &&
                m_errorMessages[DEFAULT_TERMINAL_AND_NON_TERMINAL].find(terminal) !=
                        m_errorMessages[DEFAULT_TERMINAL_AND_NON_TERMINAL].end()) {
            return m_errorMessages[DEFAULT_TERMINAL_AND_NON_TERMINAL][terminal];
        }
        return this->m_defaultMessage;
    }
}
