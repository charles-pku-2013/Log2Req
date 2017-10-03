#ifndef _COMM_DEF_H_
#define _COMM_DEF_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <stdexcept>


#define SPACES                " \t\f\r\v\n"

#define THROW_RUNTIME_ERROR(args) \
    do { \
        std::ostringstream __err_stream; \
        __err_stream << args << std::flush; \
        throw std::runtime_error( __err_stream.str() ); \
    } while (0)

#define THROW_RUNTIME_ERROR_IF(cond, args) \
    do { \
        if (cond) THROW_RUNTIME_ERROR(args); \
    } while (0)

#define RET_MSG(args) \
    do { \
        std::ostringstream __err_stream; \
        __err_stream << args << std::flush; \
        std::cerr << __err_stream.str() << std::endl; \
        return; \
    } while (0)

#define RET_MSG_IF(cond, args) \
    do { \
        if (cond) RET_MSG(args); \
    } while (0)

#define RET_MSG_VAL(val, args) \
    do { \
        std::ostringstream __err_stream; \
        __err_stream << args << std::flush; \
        std::cerr << __err_stream.str() << std::endl; \
        return val; \
    } while (0)

#define RET_MSG_VAL_IF(cond, val, args) \
    do { \
        if (cond) RET_MSG_VAL(val, args); \
    } while (0)


inline
std::shared_ptr<std::istream>
open_istream(const std::string &fname, std::ios_base::openmode mode = std::ios_base::in)
{
    std::shared_ptr<std::istream> ret;

    if (fname.empty() || fname == "-")
        ret.reset(&std::cin, [](std::istream*){});
    else
        ret.reset(new std::ifstream(fname, mode));

    return ret;
}

inline
std::shared_ptr<std::ostream>
open_ostream(const std::string &fname, std::ios_base::openmode mode = std::ios_base::out)
{
    std::shared_ptr<std::ostream> ret;

    if (fname.empty() || fname == "-")
        ret.reset(&std::cout, [](std::ostream*){});
    else
        ret.reset(new std::ofstream(fname, mode));

    return ret;
}

#endif /* ifndef _COMM_DEF_H_ */

