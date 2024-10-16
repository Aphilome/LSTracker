#ifndef COPTER_APP_HPP
#define COPTER_APP_HPP

#include "ArgumentsParser.hpp"

namespace copter::app
{

class CopterApp
{
public:
    int Run(int argc, char** argv);

private:
    Arguments ParseArguments(int argc, char** argv) const;
};

} // namespace copter::app

#endif