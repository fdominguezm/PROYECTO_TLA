#include "../../backend/support/logger.h"
#include "flex-actions.h"
#include <stdlib.h>
#include <string.h>

/**
 * Implementación de "flex-actions.h".
 *
 * Cada función debe realizar 2 operaciones básicas para lograr el streaming
 * de tokens hacia Bison:
 *
 *	1) Computar los atributos del token y almacenarlos donde sea conveniente
 *		(en la tabla de símbolos, en "yylval", o en ambos).
 *	2) Retornar el token que identifica el terminal identificado.
 *
 * Bison utilizará el token retornado en el punto (2) para matchear dicho
 * terminal en la gramática. Por otro lado, el valor almacenado en "yylval" es
 * el que Bison proveerá como valor semántico al realizar una reducción
 * (mediante $1, $2, $3, etc.).
 */

void BeginCommentPatternAction() {
	LogDebug("BeginCommentPatternAction.");
}

void EndCommentPatternAction() {
	LogDebug("EndCommentPatternAction.");
}

token AdditionOperatorPatternAction(const char * lexeme) {
	LogDebug("AdditionOperatorPatternAction: '%s'.", lexeme);
	yylval.token = ADD;
	return ADD;
}

token CloseParenthesisPatternAction(const char * lexeme) {
	LogDebug("CloseParenthesisPatternAction: '%s'.", lexeme);
	yylval.token = CLOSE_PARENTHESIS;
	return CLOSE_PARENTHESIS;
}

token DivisionOperatorPatternAction(const char * lexeme) {
	LogDebug("DivisionOperatorPatternAction: '%s'.", lexeme);
	yylval.token = DIV;
	return DIV;
}

token MultiplicationOperatorPatternAction(const char * lexeme) {
	LogDebug("MultiplicationOperatorPatternAction: '%s'.", lexeme);
	yylval.token = MUL;
	return MUL;
}

token OpenParenthesisPatternAction(const char * lexeme) {
	LogDebug("OpenParenthesisPatternAction: '%s'.", lexeme);
	yylval.token = OPEN_PARENTHESIS;
	return OPEN_PARENTHESIS;
}

token SubtractionOperatorPatternAction(const char * lexeme) {
	LogDebug("SubtractionOperatorPatternAction: '%s'.", lexeme);
	yylval.token = SUB;
	return SUB;
}

token UnknownPatternAction(const char * lexeme, const int length) {
	LogDebug("UnknownPatternAction: '%s' (length = %d).", lexeme, length);
	yylval.token = YYUNDEF;
	// Al emitir este token, el compilador aborta la ejecución.
	return YYUNDEF;
}

void IgnoredPatternAction(const char * lexeme, const int length) {
	LogDebug("IgnoredPatternAction: '%s' (length = %d).", lexeme, length);
	// Como no debe hacer nada con el patrón, solo se loguea en consola.
}

token CapitalizedWordPatternAction(const char * lexeme) {
	LogDebug("CapitalizedWordPatternAction: '%s'.", lexeme);
	yylval.token = CAPITALIZED_NAME;
	return CAPITALIZED_NAME;
}

token AlphanumericWordPatternAction(const char * lexeme) {
	LogDebug("AlphanumericWordPatternAction: '%s'.", lexeme);
	yylval.token = ALPHANUMERIC_NAME;
	return ALPHANUMERIC_NAME;
}

token ClassDefinitionsPatternAction(const char * lexeme) {
	LogDebug("ClassDefinitionsPatternAction: '%s'.", lexeme);
	yylval.token = CLASS_SECTION;
	return CLASS_SECTION;
}

token DataTypePatternAction(const char * lexeme) {
	LogDebug("GreaterThanPatternAction: '%s'.", lexeme);
	
	if(strcmp(lexeme, "string") == 0) {
 		yylval.token = STRING;
		return STRING;
	}
	else if(strcmp(lexeme, "int") == 0) {
 		yylval.token = INTEGER;
		return INTEGER;
	}
	else {
 		yylval.token = BOOLEAN;
		return BOOLEAN;
	}
}

token GreaterThanPatternAction(const char * lexeme) {
	LogDebug("GreaterThanPatternAction: '%s'.", lexeme);
	yylval.token = GT;
	return GT;
}

token LessThanPatternAction(const char * lexeme) {
	LogDebug("LessThanPatternAction: '%s'.", lexeme);
	yylval.token = LT;
	return LT;
}

token OpenBracketPatternAction(const char * lexeme) {
	LogDebug("OpenBracketPatternAction: '%s'.", lexeme);
	yylval.token = OPEN_BRACKET;
	return OPEN_BRACKET;
}

token CloseBracketPatternAction(const char * lexeme) {
	LogDebug("CloseBracketPatternAction: '%s'.", lexeme);
	yylval.token = CLOSE_BRACKET;
	return CLOSE_BRACKET;
}

token DotPatternAction(const char * lexeme) {
	LogDebug("DotPatternAction: '%s'.", lexeme);
	yylval.token = DOT;
	return DOT;
}

token SemicolonPatternAction(const char * lexeme) {
	LogDebug("SemicolonPatternAction: '%s'.", lexeme);
	yylval.token = SEMI_COLON;
	return SEMI_COLON;
}

token ReturnKeywordPatternAction(const char * lexeme) {
	LogDebug("ReturnKeywordPatternAction: '%s'.", lexeme);
	yylval.token = RETURN;
	return RETURN;
}

token NewKeywordPatternAction(const char * lexeme) {
	LogDebug("NewKeywordPatternAction: '%s'.", lexeme);
	yylval.token = NEW;
	return NEW;
}

token IfKeywordPatternAction(const char * lexeme) {
	LogDebug("IfKeywordPatternAction: '%s'.", lexeme);
	yylval.token = IF;
	return IF;
}

token WhileKeywordPatternAction(const char * lexeme) {
	LogDebug("WhileKeywordPatternAction: '%s'.", lexeme);
	yylval.token = WHILE;
	return WHILE;
}

token ElseKeywordPatternAction(const char * lexeme) {
	LogDebug("ElseKeywordPatternAction: '%s'.", lexeme);
	yylval.token = ELSE;
	return ELSE;
}

token TrueKeywordPatternAction(const char * lexeme) {
	LogDebug("NewKeywordPatternAction: '%s'.", lexeme);
	yylval.token = TRUEE;
	return TRUEE;
}

token FalseKeywordPatternAction(const char * lexeme) {
	LogDebug("FalseKeywordPatternAction: '%s'.", lexeme);
	yylval.token = FALSEE;
	return FALSEE;
}

token EqualEqualPatternAction(const char * lexeme) {
	LogDebug("EqualEqualPatternAction: '%s'.", lexeme);
	yylval.token = EQEQ;
	return EQEQ;	
}