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

#include "variable_evaluator.h"

#include <string>

namespace wish {

using std::string;

EscapeString VariableEvaluator::evaluate(const EscapeString& str) const {
    EscapeString expanded;
    size_t pos = 0, found = 0;

    while( (found = str.find('$', pos)) != EscapeString::npos ) {
        if (!str.is_active(pos)) { 
            expanded += str.substr(pos, found + 1 - pos);
            pos = found + 1; 
            continue; 
        }

        expanded += str.substr(pos, found - pos);
        EscapeString tmp;
        if (parse(str, found, tmp, pos)) {
            expanded += tmp;
        } else {
            pos = found + 1;
        }
    }
    if (pos < str.size()) expanded += str.substr(pos, str.size() - pos);

    return expanded;
}

bool VariableEvaluator::parse(const EscapeString& str, size_t pos, EscapeString& target, size_t& next) const {
    if (pos + 1 >= str.size()) return false;
    if (str[pos + 1] == '{') {
        return parse_with_brace(str, pos + 1, target, next);
    } else {
        return parse_no_brace(str, pos + 1, target, next);
    }
}

bool VariableEvaluator::parse_with_brace(const EscapeString& str, size_t pos, EscapeString& target, size_t& next) const {
    size_t ending = str.find('}', pos);
    if (ending == EscapeString::npos) return false;
    EscapeString variable_name = str.substr(pos + 1, ending - pos - 1);

    string variable = _env.get(variable_name.str());
    target = EscapeString(variable, false);
    next = ending + 1;
    return true;
}

bool VariableEvaluator::parse_no_brace(const EscapeString& str, size_t pos, EscapeString& target, size_t& next) const {
    size_t ending = str.find_first_not_of(VALID_VARNAME_CHARSET, pos);
    if (ending == EscapeString::npos) ending = str.size();

    EscapeString variable_name = str.substr(pos, ending - pos);

    string variable = _env.get(variable_name.str());
    target = EscapeString(variable, false);
    next = ending;
    return true;
}

} /* wish */ 
