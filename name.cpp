#include "name.h"
#include "table.h"

const std::string& Name::get_str() const {
    return m_str;
}

const NameType& Name::get_type() const {
    return m_type;
}

/*void Name::set_value(const Value& value) {
    m_value.val = value.val;
    m_value.type = value.type;
}*/

void Name::set_value(const double& num) {
    m_value.val = num;
    m_value.type = ValueType::NUM;
}

void Name::set_value(const std::string& str) {
    m_value.val = str;
    m_value.type = ValueType::STR;
}

void Name::set_value(const bool& b) {
    m_value.val = b;
    m_value.type = ValueType::BOOL;
}

const Value Name::get_value() const {
    switch (m_type)
    {
    case NameType::IDENT:
        if (m_str == "t")
            return Value(true);
        else if (m_str == "nil")
            return Value(false);
        else
            return m_value;
        break;
    case NameType::NUM:
        return Value(std::stod(m_str));
        break;
    case NameType::STR:
        return Value(m_str);
        break;
    default:
        return m_value;
        break;
    }
}