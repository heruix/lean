/*
Copyright (c) 2014 Microsoft Corporation. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.

Author: Leonardo de Moura
*/
#include "util/sexpr/option_declarations.h"
#include "util/sexpr/format.h"

namespace lean {
void option_declaration::display_value(std::ostream & out, options const & o) const {
    bool contains = false;
    if (o.contains(get_name())) {
        sexpr s = o.get_sexpr(get_name());
        switch (kind()) {
        case BoolOption:
            if (!is_nil(s) && is_bool(s)) {
                out << (to_bool(s) ? "true" : "false");
                contains = true;
            }
            break;
        case IntOption:
            if (!is_nil(s) && is_int(s)) {
                out << to_int(s);
                contains = true;
            }
            break;
        case UnsignedOption:
            if (!is_nil(s) && is_int(s)) {
                out << static_cast<unsigned>(to_int(s));
                contains = true;
            }
            break;
        case DoubleOption:
            if (!is_nil(s) && is_double(s)) {
                out << to_double(s);
                contains = true;
            }
            break;
        case StringOption:
            if (!is_nil(s) && is_string(s)) {
                out << to_string(s);
                contains = true;
            }
            break;
        case SExprOption:
            out << mk_pair(flatten(pp(s)), o);
            contains = true;
        }
    }
    if (!contains)
        out << get_default_value();
}
}
