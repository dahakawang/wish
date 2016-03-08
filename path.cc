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

#include "path.h"

#include <vector>
#include <string>
#include <sstream>

namespace wish {

using std::stringstream;
using std::string;
using std::vector;


/*static*/
std::vector<std::string> Path::split(const string& path) {
    vector<string> elements;
    size_t pos = 0, found = 0;
    if (!path.empty() && path[0] == '/') pos = 1;

    while ((found = path.find('/', pos)) != string::npos) {
        string elem = path.substr(pos, found - pos);
        assert(elem.find(' ') == string::npos);
        assert(!elem.empty());
        elements.push_back(elem);

        pos = found + 1;
    }
    if (path.size() - pos > 0) elements.push_back(path.substr(pos, path.size() - pos));

    return elements;
}

/*static*/
void Path::append(std::vector<std::string>& path, const std::string& relative) {
    assert(!is_absolute(relative));

    auto elements = split(relative);

    for (string& elem : elements) {
        if (elem == "..") {
            if (!path.empty()) path.pop_back();
        } else if (elem != ".") {
            path.push_back(elem);
        }
    }
}


Path::Path (const std::string& cwd, const std::string& path_name) {
    if (is_absolute(path_name)) {
        _path = split(path_name);

    } else {
        assert(is_absolute(cwd));
        _path = split(cwd);
        append(_path, path_name);
    }
}


Path Path::parent() const {
    vector<string> pathes;
    if (!_path.empty()) {
        std::copy(_path.begin(), _path.end() - 1, back_inserter(pathes));
    }
    Path obj(pathes);

    return obj;
}

Path Path::append(const std::string& relative) const {
    vector<string> path(_path);
    append(path, relative);

    return Path(path);
}

std::string Path::name() const {
    if (is_root()) return "";
    return _path.back();
}

std::string Path::extension() const {
    string filename = name();
    size_t pos = filename.find('.');

    return filename.substr(pos + 1);
}

std::string Path::str() const {
    if (is_root()) return "/";
    stringstream stream;

    for (const string& elem : _path) {
        stream << '/' << elem;
    }

    return stream.str();
}

/*static*/
bool Path::is_absolute(const std::string& path_name) {
    if (path_name.empty()) return false;

    return path_name[0] == '/';
}

} /* wish */ 
