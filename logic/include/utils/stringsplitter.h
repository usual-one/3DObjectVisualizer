#ifndef STRINGSEPARATOR_H
#define STRINGSEPARATOR_H

#include <string>
#include <vector>

class StringSplitter {
public:
    static std::vector<std::string> splitIntoStdString(const std::string &str, const std::string &sep);

    static std::vector<double> splitIntoDouble(const std::string &str, const std::string &sep);

private:
    static double convertToDouble(const std::string &str);

};

#endif // STRINGSEPARATOR_H
