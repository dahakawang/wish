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
#include <vector>
#include <memory>

namespace wish {

typedef std::string value_t;

class EnvObserver {
public:
    virtual void on_delete(const std::string& name, const value_t& value) = 0;
    virtual void on_assign(const std::string& name, const value_t& old_value, const value_t& new_value) = 0;
};


class Environment {
public:
    static Environment& instance();
    void set(const std::string& name, const value_t& value, bool exported = false);
    void erase(const std::string& name);
    value_t get(const std::string& name) const;
    bool contain(const std::string& name);
    std::vector<std::string> list_all();
    std::vector<char*> make_envp(std::vector<std::string>& holder) const;
    //this transfer ownership of the observer object
    void register_observer(std::unique_ptr<EnvObserver> observer);

private:
    Environment();
    size_t count_environ(char* env[]);
    void parse_envron(const std::string& line);
    void notify_delete(const std::string& name, const value_t& value);
    void notify_assign(const std::string& name, const value_t& old_value, const value_t& new_value);
    

    std::unordered_map<std::string, value_t> _global_envs;
    std::unordered_map<std::string, value_t> _envs;
    std::vector<std::unique_ptr<EnvObserver>> _observers;
};
} /* wish  */ 
