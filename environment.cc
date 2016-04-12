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

#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <cassert>

#include "environment.h"
extern char **environ;
namespace wish {

using std::string;
using std::vector;

/* static */
Environment& Environment::instance() {
    static Environment _instance;

    return _instance;
}

namespace {

//make sure this instance is initialized during the dynamic initialization
//which is single threaded
Environment& _instance = Environment::instance();

}

Environment::Environment() {
    size_t length = count_environ(environ);

    for (size_t pos = 0; pos < length; ++pos) {
        parse_envron(environ[pos]);
    }
}

size_t Environment::count_environ(char* env[]) {
    size_t len = 0;
    for (; env[len] != nullptr; ++len);
    return len;
}

void Environment::parse_envron(const string& line) {
    size_t delim_pos = line.find('=');
    string key = line.substr(0, delim_pos);
    string value = line.substr(delim_pos + 1);

    if (!key.empty()) _global_envs[key] = value;
}



void Environment::set(const std::string& name, const value_t& value, bool exported) {
    value_t old_value = get(name);

    if (exported) {
        _global_envs[name] = value;
    } else {
        _envs[name] = value;
    }

    notify_assign(name, old_value, value);
}


void Environment::erase(const std::string& name) {
    value_t value = get(name);

    _global_envs.erase(name);
    _envs.erase(name);

    notify_delete(name, value);
}

value_t Environment::get(const std::string& name) const {
    auto it = _envs.find(name);
    if (it != _envs.end()) return it->second;

    it = _global_envs.find(name);
    if (it != _global_envs.end()) return it->second;

    return value_t();
}

std::vector<std::string> Environment::list_all() {
    vector<string> values;

    for(auto& kv : _global_envs) values.push_back(kv.first);
    for(auto& kv  : _envs) {
        if (_global_envs.count(kv.first)) values.push_back(kv.first);
    }

    return values;
}

vector<char*> Environment::make_envp(vector<string>& holder) const {
    vector<char*> envp;

    holder.clear();
    for (auto& kv : _global_envs) {
        holder.push_back(kv.first + "=" + kv.second);
    }

    for (string& str : holder) {
        envp.push_back(const_cast<char*>(str.c_str()));
    }
    envp.push_back(nullptr);

    return envp;
}


void Environment::register_observer(std::unique_ptr<EnvObserver> observer) {
    assert(observer != nullptr);

    _observers.push_back(std::move(observer));
}

void Environment::notify_delete(const std::string& name, const value_t& value) {
    for (auto& observer : _observers) {
        if (observer) observer->on_delete(name, value);
    }
}
void Environment::notify_assign(const std::string& name, const value_t& old_value, const value_t& new_value) {
    for (auto& observer : _observers) {
        if (observer) observer->on_assign(name, old_value, new_value);
    }
}
} /* wish  */ 
