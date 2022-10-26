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

"/*"										{ BEGIN(COMMENT); BeginCommentPatternAction(); }
<COMMENT>.							        { ; }
<COMMENT>{endline}			                { ; }
<COMMENT>"*/"					            { EndCommentPatternAction(); BEGIN(INITIAL); }

"\""                                        { BEGIN(STRING); BeginStringPatternAction(); }
<STRING>[^\"]*                              { return StringPatternAction(yytext, yyleng); }
<STRING>"\""                                { EndStringPatternAction(); BEGIN(INITIAL); }

"CLASSES"                                   { return ClassDefinitionsPatternAction(yytext); }

"int"|"string"|"bool"                       { return DataTypePatternAction(yytext); }
"new"                                       { return NewKeywordPatternAction(yytext); }
"return"                                    { return ReturnKeywordPatternAction(yytext);  }
"if"                                        { return IfKeywordPatternAction(yytext);  } 
"else"                                      { return ElseKeywordPatternAction(yytext);  }
"while"                                     { return WhileKeywordPatternAction(yytext);  }
"true"                                      { return TrueKeywordPatternAction(yytext);}
"false"                                     { return FalseKeywordPatternAction(yytext);}
"{"                                         { return OpenBracketPatternAction(yytext); }
"}"                                         { return CloseBracketPatternAction(yytext); }
";"                                         { return SemicolonPatternAction(yytext); }

"&&"                                        { return AndPatternAction(yytext); }
"||"                                        { return OrPatternAction(yytext); }
"."                                         { return DotPatternAction(yytext);  }
"=="                                        { return EqualEqualPatternAction(yytext); }
"<"                                         { return LessThanPatternAction(yytext); }
">"                                         { return GreaterThanPatternAction(yytext); }
"<="                                        { return LessEqualThanPatternAction(yytext); }
">="                                        { return GreaterEqualThanPatternAction(yytext); }
","                                         { return CommaPatternAction(yytext); }

"!="                                        { return NotEqualPatternAction(yytext); }
"="                                         { return EqualPatternAction(yytext); }
"+"											{ return AdditionOperatorPatternAction(yytext); }
"-"											{ return SubtractionOperatorPatternAction(yytext); }
"*"											{ return MultiplicationOperatorPatternAction(yytext); }
"/"											{ return DivisionOperatorPatternAction(yytext); }

"("											{ return OpenParenthesisPatternAction(yytext); }
")"											{ return CloseParenthesisPatternAction(yytext); }

"max"                                       { return MaxValuePatternAction(yytext); }
"min"                                       { return MinValuePatternAction(yytext); }
"avg"                                       { return AverageValuePatternAction(yytext); }
"delete"                                    { return DeletePatternAction(yytext);}

[A-Z][a-z]*                                 { return CapitalizedWordPatternAction(yytext); }
[a-zA-Z][a-zA-Z0-9_]*                       { return AlphanumericWordPatternAction(yytext); } 


[0-9]+                                      { return IntegerValuePatternAction(yytext); }

{whitespace}+					            { IgnoredPatternAction(yytext, yyleng); }
.											{ return UnknownPatternAction(yytext, yyleng); }

%%
