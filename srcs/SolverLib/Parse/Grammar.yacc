%{
#include <iostream>
#include "Grammar.yy.hpp"

extern int yychar;
extern int yylex();

void yyerror(std::shared_ptr<SES_SolverData> solverData, const char *msg)
{
    throw std::runtime_error("YACC EXCEPTION: " + std::string(msg) +
        ", lookahead token number " + std::to_string(yychar) +
        ", current parse state: \"" + solverData->ToString() + "\"");
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


%type<Var>          EXPR_X
%type<Var>          EXPRESSION
%type<Var>          SIGNED_EXPRESSION
%type<IntNumber>    SIGN

%left               SES_PLUS SES_MINUS
%left               SES_MULT SES_DIV

%%

LINE:
                    EQUATION

EQUATION:
                    LEFT_EXPRESSIONS SES_EQUALLY RIGHT_EXPRESSIONS


LEFT_EXPRESSIONS:
                    FIRST_EXPR_TO_BE_ADDED EXPRESSIONS_TO_BE_ADDED
                    | FIRST_EXPR_TO_BE_ADDED

FIRST_EXPR_TO_BE_ADDED:
                    SIGNED_EXPRESSION                                   { solverData->AddExpression($1); }
                    | EXPRESSION                                        { solverData->AddExpression($1); }

EXPRESSIONS_TO_BE_ADDED:
                    EXPRESSIONS_TO_BE_ADDED SIGNED_EXPRESSION           { solverData->AddExpression($2); }
                    | SIGNED_EXPRESSION                                 { solverData->AddExpression($1); }


RIGHT_EXPRESSIONS:
                    FIRST_EXPR_TO_BE_SUB EXPRESSIONS_TO_BE_SUB
                    | FIRST_EXPR_TO_BE_SUB

FIRST_EXPR_TO_BE_SUB:
                    SIGNED_EXPRESSION                                   { solverData->SubExpression($1); }
                    | EXPRESSION                                        { solverData->SubExpression($1); }

EXPRESSIONS_TO_BE_SUB:
                    EXPRESSIONS_TO_BE_SUB SIGNED_EXPRESSION             { solverData->SubExpression($2); }
                    | SIGNED_EXPRESSION                                 { solverData->SubExpression($1); }


SIGNED_EXPRESSION:
                    SIGN EXPRESSION                                     { $$ = SES_Variable($1, 0) * $2; }

SIGN:
                    SES_MINUS SIGN                                      { $$ = -1 * $2; }
                    | SES_MINUS                                         { $$ = -1; }
                    | SES_PLUS SIGN                                     { $$ = $2; }
                    | SES_PLUS                                          { $$ = 1; }

EXPRESSION:
                    SES_NUMBER EXPR_X                                   { $$ = SES_Variable($1, 0) * $2; }
                    | SES_INTEGER_NUMBER EXPR_X                         { $$ = SES_Variable($1, 0) * $2; }
                    | SES_NUMBER                                        { $$ = SES_Variable($1, 0); }
                    | SES_INTEGER_NUMBER                                { $$ = SES_Variable($1, 0); }
                    | EXPR_X                                            { $$ = $1; }
                    | EXPRESSION SES_MULT EXPRESSION                    { $$ = $1 * $3; }
                    | EXPRESSION SES_DIV EXPRESSION                     { $$ = $1 / $3; }

EXPR_X:
                    SES_X SES_DEGREE SIGN SES_INTEGER_NUMBER            { $$ = SES_Variable(1, $3 * $4); }
                    | SES_X SES_DEGREE SES_INTEGER_NUMBER               { $$ = SES_Variable(1, $3); }
                    | SES_X                                             { $$ = SES_Variable(1, 1); }

%%