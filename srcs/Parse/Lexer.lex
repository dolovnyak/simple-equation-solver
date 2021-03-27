%{
#include "Grammar.yy.hpp"
#include <iostream>
%}

%option nounput
%option noinput

%%

"="                 {return SES_EQUALLY;}
"X"                 {return SES_X;}
"x"                 {return SES_X;}
"^"                 {return SES_DEGREE;}
[0-9]+"."[0-9]+     {yylval.Number = std::stod(yytext); return SES_NUMBER;}
[0-9]+              {yylval.IntNumber = std::stoi(yytext); return SES_INTEGER_NUMBER;}
"*"                 {return SES_MULT;}
"/"                 {return SES_DIV;}
"+"                 {return SES_PLUS;}
"-"                 {return SES_MINUS;}

[\t\v\r\f ]+        {;}
.                   {throw std::runtime_error("LEX EXCEPTION: lexeme \"" + std::string(yytext) + "\" doesn't correct");}

%%

int yywrap (void)
{
	return 1;
}