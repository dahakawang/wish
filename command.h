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

#include <unordered_map>
#include <string>
#include <memory>

#include "shell_argument.h"

namespace wish {

class Command {
public:
    virtual int exec(const ShellArgument& args) = 0;
    static int execute(const ShellArgument& args);

private:
    static Command* getCommand(const ShellArgument& args);
};


class InternalCommand : public Command {
public:
    static bool is_internal(const std::string& cmd) { return _internal_cmds.count(cmd) != 0;  }
    static Command* getCommand(const ShellArgument& args);

private:
    static std::unordered_map<std::string, InternalCommand*> _internal_cmds;
};

class ExternalCommand : public Command {
public:
    int exec(const ShellArgument& args) override;
    static Command* getCommand(const ShellArgument& args);
};

} /* wish */ 
