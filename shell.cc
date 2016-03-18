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

#include <iostream>
#include <string>

#include "shell.h"
#include "shell_argument.h"
#include "command.h"
#include "escape_string.h"
#include "variable_evaluator.h"


namespace wish {

using std::string;

int Shell::run() {
    using std::cout;
    using std::cin;

    while (cin && !_exit) {
        string line;
        cout << "wish-1.0$ ";
        getline(cin, line);

        EscapeString escaped(line);
        VariableEvaluator evaluator(Environment::instance());
        EscapeString cmd = evaluator.evaluate(escaped);

        ShellArgument args(cmd.str());
        if (args.empty()) continue;
        Command::execute(args);
    }

    return 0;
}

/* static */
Shell& Shell::instance() {
    static Shell _instance;
    return _instance;
}

} /* wish */


int main(int argc, char *argv[]) {
    return wish::Shell::instance().run();
}
