#include "Postfix.h"

#include <gtest.h>

TEST(Postfix, can_parse_string)//можем разобрать строку
{
	string t = "a+b*c";
	Par parse(t);
	parse._Postfix();
	ASSERT_NO_THROW(parse._Postfix());
}

TEST(Postfix, throw_when_parse_empty_string)//бросить при разборе пустую строку
{
	string t;
	ASSERT_ANY_THROW(Par parse(t););
}

TEST(Postfix, throw_with_an_unequal_number_of_brackets)//бросить при неравном колличестве скобок
{
	string t = "((a+b)";
	ASSERT_ANY_THROW(Par parse(t));
	t = "(a+b))";
	ASSERT_ANY_THROW(Par parse(t));
}

TEST(Postfix, throw_when_parsing_a_string_with_missing_brackets)//бросить при разборе строки с недостающими скобками
{
	string t = "(a+b";
	ASSERT_ANY_THROW(Par parse(t));
	t= "a+b)";
	ASSERT_ANY_THROW(Par parse(t));
}

TEST(Postfix, throw_when_string_contain_error_symbols)//бросить, когда строка содержит символы ошибки
{
	string t = "@1+2";
	ASSERT_ANY_THROW(Par parse(t));
}