//
// Created by hu on 17/10/18.
//

#ifndef QUESERA_CALPARSER_H
#define QUESERA_CALPARSER_H

#include <string>
#include <ctime>

template<class T> class CalParser
{
    public:
        virtual T parse(const std::string &input);
};

template<class T>
T CalParser<T>::parse(const std::string &input)
{
    return nullptr;
}


class DtStartParser : CalParser<time_t>
{
    public:
        time_t parse(const std::string &input) override;
};

class DtEndParser : CalParser<time_t>
{
    public:
        time_t parse(const std::string &input) override;
};

class SummaryParser : CalParser<std::string>
{
    public:
        std::string parse(const std::string &input) override;
};

#endif //QUESERA_CALPARSER_H
