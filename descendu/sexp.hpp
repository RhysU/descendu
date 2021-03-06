/*
 * Copyright (C) 2017 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DESCENDU_SEXP_HPP
#define DESCENDU_SEXP_HPP

#include <cctype>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace descendu {

namespace sexp {

// TODO Track line/column as input processed
// TODO Record line/column within each node
// Such tracking most useful within stateful parser

enum struct node_type { list=1, symbol, string };

template<class OutputStream>
auto& operator<<(OutputStream& os, node_type type) {
    switch (type) {
        case node_type::list:   os << "list";   break;
        case node_type::symbol: os << "symbol"; break;
        case node_type::string: os << "string"; break;
        default:                throw std::logic_error("unimplemented");
    }
    return os;
}

std::string to_string(const node_type& node) {
    std::ostringstream oss;
    oss << node;
    return oss.str();
}

// Forward to permit use during error handling
class node;
std::string to_string(const node& sexp);

// switch (node.type) {
//     case node_type::list:    /* Use list-like methods */ break;
//     case node_type::symbol:  /* Use node.string */       break;
//     case node_type::string:  /* Use node.string */       break;
// }
class node : std::vector<node>
{
    typedef std::vector<node> base_type;

public:

    // Discern which type of data is contained.
    node_type type;

    // For string node access
    std::string string;

    // For list node access
    using base_type::at;
    using base_type::back;
    using base_type::begin;
    using base_type::cbegin;
    using base_type::cend;
    using base_type::emplace_back;
    using base_type::end;
    using base_type::front;
    using base_type::pop_back;
    using base_type::size;

    // Construct a string node
    explicit node(const std::string& s, const bool is_symbol = true)
        : base_type(0)
        , type(is_symbol ? node_type::symbol : node_type::string)
        , string(s)
    {};

    // Move into a string node
    explicit node(std::string&& s, const bool is_symbol = true)
        : base_type(0)
        , type(is_symbol ? node_type::symbol : node_type::string)
        , string(s)
    {};

    // Construct an empty list node
    node()
        : base_type()
        , type(node_type::list)
        , string()
    {};

    bool operator==(const node& other) const {
        if (type != other.type) return false;
        switch (type) {
        case node_type::symbol:
        case node_type::string:
            return string == other.string;
        case node_type::list:
            return static_cast<const base_type&>(*this) == other;
        default:
            throw std::logic_error("Unimplemented case");
        }
    }

    bool operator!=(const node& other) const {
        return !(*this == other);
    }

    // TODO Cleaner way to detect entire string consumed?
    // Permits directly casting a symbol node to any numeric type
    template<class T, typename = std::enable_if_t<std::is_arithmetic<T>::value>>
    explicit operator T() const {
        if (this->type != node_type::symbol) {
            throw std::logic_error(to_string(*this));       // Caller misused
        }
        T retval;
        std::istringstream iss(this->string);
        iss >> std::noskipws >> retval;
        if (!iss) {
            throw std::domain_error(to_string(*this));      // Malformed input
        }
        iss.get();
        if (!iss.eof()) {
            throw std::invalid_argument(to_string(*this));  // Extraneous input
        }
        return retval;
    }
};

namespace impl {

// Helper to process C99 and S-expression escapes for parse(...) just below
template<typename InputIt>
std::string& append_maybe_escaped(
    const char c,
    std::string &acc,  // Reference!
    InputIt& next,     // Reference!
    InputIt end,
    const bool quoted)
{
    if (c != '\\') return acc += c;
    if (next == end) throw std::invalid_argument("backslash precedes EOF");
    const char q = *next++;
    switch (q) {
    case 'a': return acc += '\a';
    case 'b': return acc += '\b';
    case 'f': return acc += '\f';
    case 'n': return acc += '\n';
    case 'r': return acc += '\r';
    case 't': return acc += '\t';
    case 'v': return acc += '\v';
    case '\'':
    case '\\':
    case '"':
    case '?': return acc += q;
    case 'x':
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
        throw new std::logic_error("Escaping via numeric codes unimplemented");
    case '(': case ')': if (!quoted) return acc += q;  // Possibly fall through
    }
    throw new std::invalid_argument(std::string("Improper escape \\") + q);
}

} // namespace impl

// Parse zero or more S-expressions in the input returning a list.
// Notice parsed input is wrapped in one additional list.  That is,
//     1) "(foo)(bar)" returned as ((foo)(bar))
//     2) "(foo)"      returned as ((foo))
//     3) "foo"        returned as (foo)
//     4) ""           returned as ()
// as otherwise non-list or trivial inputs problematic.
// Based upon https://en.wikipedia.org/wiki/S-expression#Parsing
// and grotesquely extended to handle different input with checking.
template<typename InputIt>
node parse(InputIt next, InputIt end) {

    node sexp;
    sexp.emplace_back();
    std::string word;
    int level = 0;
    bool in_string = 0;

    while (next != end) {
        const char c = *next++;
        if (std::isspace(c)) {
            if (in_string) {
                sexp.back().emplace_back(std::move(word));
                word.clear();
            }
            in_string = false;
        } else if (c == '(') {
            ++level;
            sexp.emplace_back();
        } else if (c == ')') {
            if (level == 0) {
                throw std::invalid_argument("unopened right parenthesis");
            }
            if (in_string) {
                sexp.back().emplace_back(std::move(word));
                word.clear();
            }
            in_string = false;
            node temp(std::move(sexp.back()));
            sexp.pop_back();
            sexp.back().emplace_back(std::move(temp));
            --level;
        } else if (c == '"') {
            if (in_string) {
                sexp.back().emplace_back(std::move(word));
                word.clear();
            }
            in_string = false;
            for (;;) {
                if (next == end) throw std::invalid_argument("unclosed quote");
                const char q = *next++;
                if (q == '"') break;
                impl::append_maybe_escaped(q, word, next, end, /*quoted*/true);
            }
            sexp.back().emplace_back(std::move(word), /*string*/false);
            word.clear();
        } else {
            impl::append_maybe_escaped(c, word, next, end, /*quoted*/false);
            in_string = true;
        }
    }

    if (level != 0) {
        throw std::invalid_argument("unclosed left parenthesis");
    }
    if (in_string) { // Required for final top-level string
        sexp.back().emplace_back(word);
    }
    if (!sexp.size()) {
        throw std::logic_error("sanity failure on size");
    }
    if (sexp.front().type != node_type::list) {
        throw std::logic_error("sanity failure on type");
    }

    return sexp.front();
}

node parse(const std::string& in) {
    return parse(in.cbegin(), in.cend());
}

node parse(std::istream& is) {
    return parse(
        std::istream_iterator<char>(is),
        std::istream_iterator<char>());
}

template<typename OutputIterator>
void copy(const node& sexp, OutputIterator out) {
    switch (sexp.type) {
    case node_type::list:
        {
            *out++ = '(';
            std::size_t count = 0;
            for (const auto& term : sexp) {
                if (count++) {
                    *out++ = ' ';
                }
                copy(term, out);
            }
            *out++ = ')';
        }
        break;
    case node_type::symbol:
        for (const char c : sexp.string) {
            switch (c) {
            case '\a': *out++ = '\\'; *out++ = 'a';  break;
            case '\b': *out++ = '\\'; *out++ = 'b';  break;
            case '\f': *out++ = '\\'; *out++ = 'f';  break;
            case '\n': *out++ = '\\'; *out++ = 'n';  break;
            case ' ':  *out++ = '\\'; *out++ = ' ';  break;
            case '?':  *out++ = '\\'; *out++ = '?';  break;
            case '"':  *out++ = '\\'; *out++ = '"';  break;
            case '(':  *out++ = '\\'; *out++ = '(';  break;
            case ')':  *out++ = '\\'; *out++ = ')';  break;
            case '\'': *out++ = '\\'; *out++ = '\''; break;
            case '\\': *out++ = '\\'; *out++ = '\\'; break;
            case '\r': *out++ = '\\'; *out++ = 'r';  break;
            case '\t': *out++ = '\\'; *out++ = 't';  break;
            case '\v': *out++ = '\\'; *out++ = 'v';  break;
            default:
                *out++ = c;
            }
        }
        break;
    case node_type::string:
        *out++ = '"';
        for (const char c : sexp.string) {
            switch (c) {
            case '\a': *out++ = '\\'; *out++ = 'a';  break;
            case '\b': *out++ = '\\'; *out++ = 'b';  break;
            case '\f': *out++ = '\\'; *out++ = 'f';  break;
            case '"':  *out++ = '\\'; *out++ = '"';  break;
            case '\\': *out++ = '\\'; *out++ = '\\'; break;
            default:
                *out++ = c;
            }
        }
        *out++ = '"';
        break;
    default:
        throw std::logic_error("Unimplemented case");
    }
}

void copy(const node& sexp, std::ostream& os) {
    return copy(sexp, std::ostream_iterator<char>(os));
}

std::string to_string(const node& sexp) {
    std::ostringstream oss;
    std::ostream_iterator<char> it(oss);
    copy(sexp, it);
    return oss.str();
}

} // namespace

} // namespace

#endif
