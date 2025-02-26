#pragma once

#include <hex.hpp>

#include <functional>
#include <optional>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>

namespace hex::pl {

    class Preprocessor {
    public:
        Preprocessor();

        std::optional<std::string> preprocess(const std::string& code, bool initialRun = true);

        void addPragmaHandler(const std::string &pragmaType, const std::function<bool(const std::string&)> &function);
        void addDefaultPragmaHandlers();

        const std::pair<u32, std::string>& getError() { return this->m_error; }

    private:
        using PreprocessorError = std::pair<u32, std::string>;

        [[noreturn]] void throwPreprocessorError(const std::string &error, u32 lineNumber) const {
            throw PreprocessorError(lineNumber, "Preprocessor: " + error);
        }

        std::unordered_map<std::string, std::function<bool(std::string)>> m_pragmaHandlers;

        std::set<std::tuple<std::string, std::string, u32>> m_defines;
        std::set<std::tuple<std::string, std::string, u32>> m_pragmas;

        std::pair<u32, std::string> m_error;
    };

}