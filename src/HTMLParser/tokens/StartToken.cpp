#include "StartToken.hpp"

#include <iostream>

StartToken::StartToken()
{
    self_closing = false;
    attributes = {};
    tag_name = L"";
    current_attribute_name = L"";
    current_attribute_value = L"";
}

StartToken::StartToken(wchar_t token_name)
{
    self_closing = false;
    attributes = {};
    tag_name = tolower(token_name);
    current_attribute_name = L"";
    current_attribute_value = L"";
}

bool StartToken::is_self_closing() const
{
    return self_closing;
}

void StartToken::set_self_closing(bool closing)
{
    self_closing = closing;
}

std::map<std::wstring, std::wstring> StartToken::get_attributes() const
{
    return attributes;
}

void StartToken::add_to_current_attribute_name(wchar_t next_char)
{
    current_attribute_name.push_back(tolower(next_char));
    current_attribute_value = L"";
}

void StartToken::add_to_current_attribute_value(wchar_t next_char)
{
    current_attribute_value.push_back(tolower(next_char));
}

bool StartToken::contains_attribute(std::wstring attribute_name) const
{
    return (attributes.count(attribute_name) > 0);
}

std::wstring StartToken::get_attribute_value(std::wstring attribute_name) const
{
    try
    {
        if (contains_attribute(attribute_name) != 0)
            return attributes.at(attribute_name);
        else
            throw attribute_name;
    }
    catch (std::wstring illegal_name)
    {
        std::wcerr << "TOKENIZATION ERROR: Attempt to access unset "
            << " attribute name " << illegal_name << std::endl;
        return L"";
    }
}

void StartToken::process_current_attribute()
{
    if (contains_attribute(current_attribute_name))
        return;

    attributes.insert({current_attribute_name, current_attribute_value});

    current_attribute_name = L"";
    current_attribute_value = L"";
}

bool StartToken::is_start_token() const
{
    return true;
}
