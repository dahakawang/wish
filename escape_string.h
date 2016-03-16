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

#include <vector>
#include <string>

namespace wish {

class EscapeString {
public:
    static const size_t npos = std::string::npos;

    EscapeString (const std::string& str, bool plain = false);
    size_t size() const { return _str.size();  }
    char operator[](size_t pos) const { return _str[pos]; }
    char& operator[](size_t pos) { return _str[pos]; }
    bool is_active(size_t pos) const { return _active[pos]; }
    void set_active(size_t pos, bool flag) { _active[pos] = flag; }
    size_t find(char c, size_t pos = 0) const { return _str.find(c, pos); }
    EscapeString substr(size_t pos, size_t count = npos) const;
    EscapeString& append(const EscapeString& other);
    EscapeString& operator+=(const EscapeString& other) { return append(other); }

private:
    std::string _str;
    std::vector<bool> _active;

    EscapeString() = default;

};
} /* wish */ 
