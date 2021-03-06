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

#include <algorithm>
#include <string>
#include <sstream>

#include "shell_argument.h"

namespace wish {

using std::string;
using std::stringstream;
using std::vector;

ShellArgument::ShellArgument(int argc, char* argv[]) {
    std::copy(argv, argv + argc, back_inserter(_args));
}

ShellArgument::ShellArgument(const string& arg_str) {
    stringstream stream(arg_str);
    string arg_elem;

    while(stream >> arg_elem) {
        _args.push_back(arg_elem);
    }
}

vector<char*> ShellArgument::make_argv(vector<string>& holder) const {
    vector<char*> args;

    for (auto& str : _args) {
        holder.push_back(str);
    }

    for (string& str : holder) {
        args.push_back(const_cast<char*>(str.c_str()));
    }
    args.push_back(nullptr);

    return args;
}
} /* wish */ 
