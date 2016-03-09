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
#include <unordered_map>

#include "environment.h"
#include "shell_argument.h"

namespace wish {
namespace Executable {

/*
int full_path(const std::string& cmd) {

}
*/


class ExecutableFinder;

class PathVariableObserver : public EnvObserver {
public:
    PathVariableObserver(ExecutableFinder& finder) : _finder(finder) {}
    void on_delete(const std::string& name, const value_t& value) override;
    void on_assign(const std::string& name, const value_t& old_value, const value_t& new_value) override;

private:
    ExecutableFinder& _finder;
};



class ExecutableFinder {
public:
    static ExecutableFinder& instance();
    std::string full_path(const std::string& cmd);
    std::string operator[](const std::string& cmd);

private:
    ExecutableFinder ();

    std::unordered_map<std::string, std::string> _uniformed_mapping;
    std::vector<std::string> _search_path;
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> _mapping;

    std::vector<std::string> parse_path_variable();
    bool is_executable(const std::string& file);
    void find_executable(const std::string& dir);
    void merge();
    void setup();
};


class Execute {
public:
    static int execute(const std::string& cmd, const ShellArgument& args);
};

} /* Executable */ 
} /* wish */ 
