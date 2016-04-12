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

#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <dirent.h>
#include <cstring>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

#include "executable.h"
#include "environment.h"
#include "path.h"

namespace wish {
namespace Executable {

using std::string;
using std::vector;
using std::unordered_map;


void PathVariableObserver::on_delete(const std::string& name, const value_t& value) {

}

void PathVariableObserver::on_assign(const std::string& name, const value_t& old_value, const value_t& new_value) {

}


inline void error(const string& str, bool mandatory = false) {
    if (!mandatory && Environment::instance().get("WDEBUG") != "y") return;
    char buffer[1024];
    std::cerr << str << " ("<< strerror_r(errno, buffer, sizeof(buffer)) << ")" << std::endl;
}

/* static */
ExecutableFinder& ExecutableFinder::instance() {
    static ExecutableFinder _instance;

    return _instance;
}

bool ExecutableFinder::is_executable(const string& file) {
    struct stat status;
    if (stat(file.c_str(), &status) < 0) {
        error(string("can't open: ") + file);
        return false;
    }

    return S_ISREG(status.st_mode) && ((status.st_mode & S_IXUSR) || (status.st_mode & S_IXGRP) || (status.st_mode & S_IXOTH));
}

void ExecutableFinder::find_executable(const std::string& dir) {
    unordered_map<string, string> mapping;

    DIR* directory = opendir(dir.c_str());
    if (directory == nullptr) {
        error("can't open directory: " + dir);
        return;
    }

    struct dirent *entry;
    while((entry = readdir(directory))) {
        Path path(dir, entry->d_name);

        if (is_executable(path.str())) {
            mapping[path.name()] = path.str();
            //std::cout << path.name()<< std::endl;
        }
    }

    _mapping[dir] = mapping;
}

void ExecutableFinder::merge() {
    for (string& path : _search_path) {
        auto& mapping = _mapping[path];
        for(auto& p : mapping) {
            if (_uniformed_mapping.count(p.first) == 0) {
                _uniformed_mapping.insert(p);
            }
        }
    }
}

void ExecutableFinder::setup() {
    _search_path = parse_path_variable();

    for (string path : _search_path) {
        find_executable(path);
    }

    merge();
}

ExecutableFinder::ExecutableFinder() {
    setup();

    std::unique_ptr<EnvObserver> observer(new PathVariableObserver(*this));
    Environment::instance().register_observer(std::move(observer));
}

vector<string> ExecutableFinder::parse_path_variable() {
    vector<string> result;
    string pathes = Environment::instance().get("PATH");

    size_t pos = 0, found = 0;

    while((found = pathes.find(':', pos)) != string::npos) {
        string path = pathes.substr(pos, found - pos);
        if (!path.empty()) result.push_back(path);
        pos = found + 1;
    }
    if (pathes.size() - pos > 0) result.push_back(pathes.substr(pos, pathes.size() - pos));

    return result;
}

string ExecutableFinder::full_path(const std::string& cmd) {
    if (_uniformed_mapping.count(cmd) == 0) return "";
    return _uniformed_mapping[cmd];
}

string ExecutableFinder::operator[](const std::string& cmd) {
    return full_path(cmd);
}

namespace {
ExecutableFinder& _p = ExecutableFinder::instance();
}


/* static */
int Execute::execute(const string& cmd, const ShellArgument& args) {
    pid_t pid = fork();
    if (pid > 0) {
        int status;
        if (waitpid(pid, &status, 0) < 0) {
            error("error wait for process", true);
            return -1;
        }
        return WEXITSTATUS(status);

    } else if (pid == 0) {
        vector<string> env_holder, arg_holder;
        auto env_list = Environment::instance().make_envp(env_holder);

        auto arg_list = args.make_execve();
        if (execve(cmd.c_str(), const_cast<char* const*>(arg_list.data()), const_cast<char* const*>(env_list.data())) < 0) {
            error("failed to execute ", true);
            exit(-1);
        }

        assert(false); // never reached
    } else { //pid < 0
        error("failed to fork ", true);
        return -1;
    }
}

} /* Executable */ 
} /* with */ 
