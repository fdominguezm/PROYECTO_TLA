%{

#include "flex-actions.h"
#include <stdio.h>

%}

/* Obliga a crear una regla explícita para manejar lexemas desconocidos. */
%option nodefault

/* Escanea un único archivo y se detiene. */
%option noyywrap

/* Dispone una variable global "yylineno" con el número de línea actual. */
%option yylineno

/* Contextos de Flex. */
%x COMMENT
%x STRING

/* Patrones reutilizables. */
digit			    [0-9]
endline			  [\n]
whitespace		[ \f\n\r\t\v]

%%

"CLASSES"               { return ClassDefinitionsPatternAction(yytext); }

"int"|"string"|"bool"   { return DataTypePatternAction(yytext); }
"new"                   { return NewKeywordPatternAction(yytext); }
"return"                { return ReturnKeywordPatternAction(yytext);  }
"if"                    { return IfKeywordPatternAction(yytext);  } 
"else"                  { return ElseKeywordPatternAction(yytext);  }
"while"                 { return WhileKeywordPatternAction(yytext);  }
"true"                  { return TrueKeywordPatternAction(yytext);}
"false"                 { return FalseKeywordPatternAction(yytext);}
"{"                     { return OpenBracketPatternAction(yytext); }
"}"                     { return CloseBracketPatternAction(yytext); }
";"                     { return SemicolonPatternAction(yytext); }

"."                     { return DotPatternAction(yytext);  }
"=="                    { return EqualEqualPatternAction(yytext); }
"<"                     { return LessThanPatternAction(yytext); }
">"                     { return GreaterThanPatternAction(yytext); }

"+"											{ return AdditionOperatorPatternAction(yytext); }
"-"											{ return SubtractionOperatorPatternAction(yytext); }
"*"											{ return MultiplicationOperatorPatternAction(yytext); }
"/"											{ return DivisionOperatorPatternAction(yytext); }

"("											{ return OpenParenthesisPatternAction(yytext); }
")"											{ return CloseParenthesisPatternAction(yytext); }

[A-Z][a-z]*             { return CapitalizedWordPatternAction(yytext); }
[a-zA-Z][a-zA-Z0-9_]*   { return AlphanumericWordPatternAction(yytext); }  
{whitespace}+					{ IgnoredPatternAction(yytext, yyleng); }
.											  { return UnknownPatternAction(yytext, yyleng); }

%%
