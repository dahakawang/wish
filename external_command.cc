/**
 *    The MIT License (MIT)
 *
 *    Copyright (c) 2016 Kaiqiang Wang
 *
 *    Permission is hereby granted, free of charge, to any person obtaining a copy
 *    of this software and associated documentation files (the "Software"), to deal
 *    in the Software without restriction, including without limitation the rights
 *    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *    copies of the Software, and to permit persons to whom the Software is
 *    furnished to do so, subject to the following conditions:
 *
 *    The above copyright notice and this permission notice shall be included in all
 *    copies or substantial portions of the Software.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *    SOFTWARE.
 */

#include <string>
#include <iostream>

#include "external_command.h"
#include "executable.h"
#include "command.h"

namespace wish {
    
using std::string;

int TYPECommand::exec(const ShellArgument& args) {
    if (args.size() == 1) return 0;

    for (size_t pos = 1; pos < args.size(); ++pos) {
        string full_path = Executable::ExecutableFinder::instance().full_path(args[pos]);
        if (full_path.empty()) {
            std::cout << args[pos] << " not found"  << std::endl;
        } else {
            std::cout << args[pos] << " is " << full_path << std::endl;
        }
    }

    return 0;
}
DECLARE_COMMAND("type", TYPECommand);

} /* wish */ 
