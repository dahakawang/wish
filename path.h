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
#include <stdexcept>

namespace wish {

class PathException : public std::runtime_error {

};

class Path {
public:
    Path (const std::string& cwd, const std::string& path_name);
    Path parent() const;
    Path append(const std::string& relative) const;
    std::string name() const;
    std::string extension() const;
    std::string str() const;
    bool is_root() const { return _path.empty(); }

    static bool is_absolute(const std::string& path_name);

private:
    Path (std::vector<std::string>& v) : _path(v) {}
    static void append(std::vector<std::string>& _path, const std::string& relative);
    static std::vector<std::string> split(const std::string& path);

    std::vector<std::string> _path;
};
} /* wish */ 
