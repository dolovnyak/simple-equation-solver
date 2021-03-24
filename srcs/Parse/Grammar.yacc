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
%type<Var>          LEFT_EXPRESSIONS
%type<Var>          RIGHT_EXPRESSIONS

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
                    {
                      //here we have 2 expressions lists to be simplified
                    }

LEFT_EXPRESSIONS:
                    EXPRESSION
                    {
                        std::cout << $1 << std::endl;
                        $$ = $1;
                    }
                    | EXPRESSION SES_PLUS LEFT_EXPRESSIONS
                    {
                        std::cout << "AA" << std::endl;
                        std::cout << $1 << " | " << $3 << std::endl;
                        solverData->AddToExpression($1);
                        solverData->AddToExpression($3);
                    }
                    | EXPRESSION SES_MINUS LEFT_EXPRESSIONS
                    {
                        std::cout << "BB" << std::endl;
                        std::cout << $1 << " | " << std::endl;
//                        $3 = $3 * SES_Variable(-1, 1);
                        solverData->AddToExpression($1);
//                        solverData->AddToExpression($3);
                    }

EXPRESSION_MINUS:
                    SES_MINUS EXPRESSION
                    {
                        std::cout << "gug" << std::endl;
                    }

RIGHT_EXPRESSIONS:
                    RIGHT_EXPRESSIONS SES_PLUS
                    {
                        std::cout << "R: AA" << std::endl;
                    }
                    | EXPRESSION
                    {
                        std::cout << "R: BB" << std::endl;
                    }

EXPRESSION:
                    SES_X SES_DEGREE SES_INTEGER_NUMBER
                    {
                        if ($3 < 0 || $3 > 2)
                            throw std::runtime_error("degree should be >= 0 and <= 2");
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
                        std::cout << "AAA" << std::endl;
                    }


%%