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

#include "working_directory.h"
#include "environment.h"
#include "path.h"

#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <iostream>
#include <string>
#include <cstring>

namespace wish {

using std::string;

int PWDCommand::exec(const ShellArgument& args) {
    char* buffer = getcwd(nullptr, 0);
    if (buffer == nullptr) {
        perror(nullptr);
        return -1;
    }

    std::cout << buffer << std::endl;
    free(buffer);
    return 0;
}
DECLARE_COMMAND("pwd", PWDCommand);


std::string CDCommand::trim(const std::string& str) {
    size_t first = 0, last = str.size() - 1;
    for(; first < str.size() && isspace(str[first]); ++first);
    for(; last >= first && isspace(str[last]); --last);

    return str.substr(first, last + 1 - first);
}

int CDCommand::exec(const ShellArgument& args) {
    string target;
    if (args.size() > 2) std::cerr << "too many arguments" << std::endl;
    if (args.size() == 2) target = trim(args[1]);
    else target = Environment::instance().get("HOME");
    if (target == "~") target = Environment::instance().get("HOME");


    try {
        string cwd = Environment::instance().get("PWD");
        string dir_name = Path(cwd, target).str();

        if (chdir(dir_name.c_str()) < 0) {
            perror(nullptr);
            return -1;
        }

        Environment::instance().set("PWD", dir_name);
        return 0;
    } catch (PathException e) {
        std::cerr << "invalid path specified" << std::endl;
    }

    return -1;
}
DECLARE_COMMAND("cd", CDCommand);


int LSCommand::exec(const ShellArgument& args) {
    if (args.size() > 1) {
        std::cerr << "too many arguments" << std::endl;
    }

    string cwd = Environment::instance().get("PWD");

    DIR* dir = opendir(cwd.c_str());
    if (dir == nullptr) {
        perror(nullptr);
        return -1;
    }

    dirent* entry = nullptr;
    while((entry = readdir(dir))) {
        if (strcmp(entry->d_name, ".") == 0 ||
                strcmp(entry->d_name, "..") == 0) continue;
        std::cout << entry->d_name << std::endl;
    }

    if (closedir(dir) < 0) {
        perror(nullptr);
        return -1;
    }

    return 0;
}
DECLARE_COMMAND("ls", LSCommand);

} /* wish */ 
