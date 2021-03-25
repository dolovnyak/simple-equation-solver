%{
#include <iostream>
#include "Grammar.yy.hpp"

extern int yychar;
extern int yylex();

void yyerror(std::shared_ptr<SES_SolverData> SES_SolverData, const char *msg)
{
    (void)SES_SolverData;
    throw std::runtime_error("YACC EXCEPTION: " + std::string(msg) + ", lookahead token number " + std::to_string(yychar));
}

%}

%union              Transmitter {
                        SES_Variable Var;
                        double Number;
                        int IntNumber;

                        Transmitter(double number, int degree) : Var(number, degree) {}
                        Transmitter(double number) : Number(number) {}
                        Transmitter(int intNumber) : IntNumber(intNumber) {}
                        Transmitter() {}
                    }

%parse-param        {std::shared_ptr<SES_SolverData> solverData}

%token              SES_SEPARATOR
%token              SES_EQUALLY
%token<Number>      SES_NUMBER
%token<IntNumber>   SES_INTEGER_NUMBER
%token              SES_MULT
%token              SES_DIV
%token              SES_PLUS
%token              SES_MINUS
%token              SES_DEGREE
%token              SES_X


%type<Var>          EXPRESSION
%type<Var>          EXPRESSION_PLUS
%type<Var>          EXPRESSION_MINUS

%left               SES_PLUS SES_MINUS
%left               SES_MULT SES_DIV

%%

LINE:
                    EQUATION
                    | EQUATION SEPARATORS

SEPARATORS:
                    SES_SEPARATOR
                    | SES_SEPARATOR SEPARATORS

EQUATION:
                    LEFT_EXPRESSIONS SES_EQUALLY RIGHT_EXPRESSIONS

LEFT_EXPRESSIONS:
                    ADD_FIRST_EXPR ADD_OTHER_EXPRS
                    | ADD_FIRST_EXPR

RIGHT_EXPRESSIONS:
                    SUB_FIRST_EXPR SUB_OTHER_EXPRS
                    | SUB_FIRST_EXPR

ADD_FIRST_EXPR:
                    EXPRESSION
                    {
                        solverData->AddExpression($1);
                    }

SUB_FIRST_EXPR:
                    EXPRESSION
                    {
                        solverData->AddExpression($1 * SES_Variable(-1, 0));
                    }

ADD_OTHER_EXPRS:
                    ADD_OTHER_EXPRS EXPRESSION_MINUS
                    {
                        solverData->AddExpression($2);
                    }
                    | EXPRESSION_MINUS
                    {
                        solverData->AddExpression($1);
                    }
                    | ADD_OTHER_EXPRS EXPRESSION_PLUS
                    {
                        solverData->AddExpression($2);
                    }
                    | EXPRESSION_PLUS
                    {
                        solverData->AddExpression($1);
                    }

SUB_OTHER_EXPRS:
                    SUB_OTHER_EXPRS EXPRESSION_MINUS
                    {
                        solverData->AddExpression($2 * SES_Variable(-1, 0));
                    }
                    | EXPRESSION_MINUS
                    {
                        solverData->AddExpression($1 * SES_Variable(-1, 0));
                    }
                    | SUB_OTHER_EXPRS EXPRESSION_PLUS
                    {
                        solverData->AddExpression($2 * SES_Variable(-1, 0));
                    }
                    | EXPRESSION_PLUS
                    {
                        solverData->AddExpression($1 * SES_Variable(-1, 0));
                    }

EXPRESSION_MINUS:
                    SES_MINUS EXPRESSION
                    {
                        $$ = $2 * SES_Variable(-1, 0);
                    }

EXPRESSION_PLUS:
                    SES_PLUS EXPRESSION
                    {
                        $$ = $2;
                    }

EXPRESSION:
                    SES_X SES_DEGREE SES_INTEGER_NUMBER
                    {
                        $$ = SES_Variable(1, $3);
                    }
                    | SES_X
                    {
                        $$ = SES_Variable(1, 1);
                    }
                    | SES_NUMBER
                    {
                        $$ = SES_Variable($1, 0);
                    }
                    | SES_INTEGER_NUMBER
                    {
                        $$ = SES_Variable($1, 0);
                    }
                    | EXPRESSION SES_MULT EXPRESSION
                    {
                        $$ = $1 * $3;
                    }
                    | EXPRESSION SES_DIV EXPRESSION
                    {
                        $$ = $1 / $3;
                    }

%%