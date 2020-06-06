#include <exception>

#include "logic/include/utils/stringsplitter.h"
#include "logic/include/utils/exception/stringsplitterexception.h"


std::vector<std::string> StringSplitter::splitIntoStdString(const std::string &str, const std::string &sep) {
    std::vector<std::string> arr;
    size_t prev = 0;
    size_t next;
    size_t delta = sep.length();
    while ((next = str.find(sep, prev)) != std::string::npos) {
        arr.push_back(str.substr(prev, next - prev));
        prev = next + delta;
    }
    arr.push_back(str.substr(prev));
    return arr;
}

std::vector<double> StringSplitter::splitIntoDouble(const std::string &str, const std::string &sep) {
    std::vector<double> arr;
    size_t prev = 0;
    size_t next;
    size_t delta = sep.length();
    while ((next = str.find(sep, prev)) != std::string::npos) {
        arr.push_back(convertToDouble(str.substr(prev, next - prev)));
        prev = next + delta;
    }
    arr.push_back(convertToDouble(str.substr(prev)));
    return arr;
}

double StringSplitter::convertToDouble(const std::string &str) {
    double result;
    try {
        result = std::stod(str);
    } catch (std::exception &err) {
        throw StringSplitterException("cannot convert \"" + str + "\" to double");
    }
    return result;
}
