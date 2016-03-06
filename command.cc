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
#include <cassert>
#include <iostream>
#include <unordered_map>

#include "command.h"

namespace wish {

using std::string;
using std::vector;
using std::unordered_map;

/* static */ 
int Command::execute(const ShellArgument& args) {
    Command* cmd = getCommand(args);

    return cmd->exec(args);
}

/* static */
Command* Command::getCommand(const ShellArgument& args) {
    if (InternalCommand::is_internal(args.cmd())) return InternalCommand::getCommand(args);

    return ExternalCommand::getCommand(args);
}



/* static */
Command* InternalCommand::getCommand(const ShellArgument& args) {
    return _internal_cmds[args.cmd()];
}

unordered_map<string, InternalCommand*> InternalCommand::_internal_cmds;



/*static*/ 
Command* ExternalCommand::getCommand(const ShellArgument& args) {
    static ExternalCommand instance;
    return &instance;
}

int ExternalCommand::exec(const ShellArgument& args) {
    std::cout << "invoked executable " << args.cmd() << std::endl;
    return 0;
}
} /* wish */ 
