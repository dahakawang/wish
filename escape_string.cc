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

#include "escape_string.h"

#include <string>
#include <vector>

namespace wish {

using std::vector;
using std::string;

EscapeString::EscapeString(const string& str, bool plain) {
    // if it's plain text, all the magic has gone (escape, special characters etc..)
    if (plain) {
        _str = str;
        _active = vector<bool>(str.size(), false);
        return;
    }


    _str.reserve(str.size());
    _active = vector<bool>(str.size(), true);
    size_t pos = 0, found = 0;

    while((found = str.find('\\', pos)) != string::npos) {
        _str += str.substr(pos, found - pos);

        pos = found + 1;
        if (pos >= str.size()) break;
        _str.push_back(str[pos]);
        _active[_str.size() - 1] = false;
        pos = found + 2;
    }
    if (pos < str.size()) _str += str.substr(pos, str.size() - pos);
    _active.resize(_str.size());
}

EscapeString EscapeString::substr(size_t pos, size_t count) const {
    EscapeString ret;

    ret._str = _str.substr(pos, count);
    ret._active = vector<bool>(_active.begin() + pos, _active.begin() + pos + ret._str.size());

    return ret;
}

EscapeString& EscapeString::append(const EscapeString& other) {
    _str.reserve(_str.size() + other.size());
    _active.reserve(_str.size() + other.size());

    _str += other._str;
    std::copy(other._active.begin(), other._active.end(), back_inserter(_active));

    return *this;
}

} /* wish */ 
