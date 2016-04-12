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

#include "escape_string.h"
#include "environment.h"

namespace wish {

class VariableEvaluator {
public:
    static constexpr const char* VALID_VARNAME_CHARSET = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";

    VariableEvaluator (Environment& env) : _env(env) {}
    EscapeString evaluate(const EscapeString& str) const;

private:
    Environment& _env;

    bool parse(const EscapeString& str, size_t pos, EscapeString& target, size_t& next) const;
    bool parse_with_brace(const EscapeString& str, size_t pos, EscapeString& target, size_t& next) const;
    bool parse_no_brace(const EscapeString& str, size_t pos, EscapeString& target, size_t& next) const;

};
} /* wish */ 
