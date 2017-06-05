#ifndef SIMPLE_VIDEO_FRAMEWORK_H_
#define SIMPLE_VIDEO_FRAMEWORK_H_

/*
 * developed by: Kuksov Pavel
 * e-mail: aimed.fire@gmail.com
 */

#include <exception>
#include <string>

namespace svf {

class Error {
public:
    Error(const std::string& error_message): error_message_(error_message) {}


    const char* what() const noexcept { return error_message_.c_str(); }

private:
    std::string error_message_;
};//end of declaration class Error

} /* svf */

#endif /* end of include guard: SIMPLE_VIDEO_FRAMEWORK_H_ */
