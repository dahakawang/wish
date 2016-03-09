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

#pragma once

#include <string>
#include <vector>

namespace wish {

class ShellArgument {
public:
    ShellArgument(int argc, char* argv[]);
    ShellArgument(const std::string& arg_str);
    ShellArgument (const std::vector<std::string>& args) : _args(args) {}
    std::string cmd() const { return (_args.empty())? "" : _args.front(); }
    const std::string& operator[](size_t pos) const { return _args[pos]; }
    const std::string& at(size_t pos) const { return _args.at(pos); }
    size_t size() const { return _args.size();  }
    std::vector<const char*> make_execve() const;

private:
    std::vector<std::string> _args;
};

} /* wish */ 
