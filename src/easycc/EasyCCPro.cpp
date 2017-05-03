#include <easycc/EasyCCPro.h>
#include <boost/move/utility_core.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <easycc/generated/StaticGrammar.h>
//#include <easycc/generated/StaticSyntaxConfig.h>
//#include <easycc/generated/StaticSyntaxMessages.h>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace keywords = boost::log::keywords;
namespace sinks = boost::log::sinks;

BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(ecc_logger, src::logger_mt)

namespace ecc{
    EasyCC::EasyCC() {
        StaticGrammar staticGrammar;
        for(std::string nonTerminal : staticGrammar.getNonTerminals()) {
            std::cout << nonTerminal << std::endl;
        }
    }
}

