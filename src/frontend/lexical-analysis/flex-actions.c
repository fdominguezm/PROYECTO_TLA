#include "../../backend/support/logger.h"
#include "flex-actions.h"
#include <stdlib.h>
#include <string.h>

#ifndef YYUNDEF
#define YYUNDEF 2
#endif

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

void BeginStringPatternAction() {
	LogDebug("BeginStringPatternAction.");
}

void EndStringPatternAction() {
	LogDebug("EndStringPatternAction.");
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

token CapitalizedWordPatternAction(const char * lexeme, int length) {
	LogDebug("CapitalizedWordPatternAction: '%s'.", lexeme);
	// Reservar memoria para el lexema identificado y el \0 final:
	char * text = (char *) calloc(length + 1, sizeof(char));
	// Copiar el lexema y \0 para evitar segmentation-faults:
	strncpy(text, lexeme, len);
	yylval.className = text;
	return CAPITALIZED_NAME;
}

token AlphanumericWordPatternAction(const char * lexeme, int length) {
	LogDebug("AlphanumericWordPatternAction: '%s'.", lexeme);
	// Reservar memoria para el lexema identificado y el \0 final:
	char * text = (char *) calloc(length + 1, sizeof(char));
	// Copiar el lexema y \0 para evitar segmentation-faults:
	strncpy(text, lexeme, length);
	yylval.varName = text;
	return ALPHANUMERIC_NAME;
}

token ClassDefinitionsPatternAction(const char * lexeme) {
	LogDebug("ClassDefinitionsPatternAction: '%s'.", lexeme);
	yylval.token = CLASS_SECTION;
	return CLASS_SECTION;
}

token DataTypePatternAction(const char * lexeme) {
	LogDebug("DataTypePatternAction: '%s'.", lexeme);
	
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


token GreaterEqualThanPatternAction(const char * lexeme) {
	LogDebug("GreaterEqualThanPatternAction: '%s'.", lexeme);
	yylval.token = GTEQ;
	return GTEQ;
}

token LessEqualThanPatternAction(const char * lexeme) {
	LogDebug("LessEqualThanPatternAction: '%s'.", lexeme);
	yylval.token = LTEQ;
	return LTEQ;
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

token EqualPatternAction(const char * lexeme) {
	LogDebug("EqualPatternAction: '%s'.", lexeme);
	yylval.token = EQ;
	return EQ;	
}

token NotEqualPatternAction(const char * lexeme) {
	LogDebug("NotEqualPatternAction: '%s'.", lexeme);
	yylval.token = NOTEQ;
	return NOTEQ;	
}

token AndPatternAction(const char * lexeme) {
	LogDebug("AndPatternAction: '%s'.", lexeme);
	yylval.token = AND;
	return AND;
}

token OrPatternAction(const char * lexeme) {
	LogDebug("OrPatternAction: '%s'.", lexeme);
	yylval.token = OR;
	return OR;
}

token StringPatternAction(const char * lexeme, const int length) {
	LogDebug("StringPatternAction: '%s'.", lexeme);
	yylval.token = STRING_VALUE;
	return STRING_VALUE;
}

token StringValuePatternAction(const char * lexeme){
	LogDebug("StringValuePatternAction: '%s'.", lexeme);
	yylval.token = STRING_VALUE;
	return STRING_VALUE;	
}

token CommaPatternAction(const char * lexeme) {
	LogDebug("CommaValuePatternAction: '%s'.", lexeme);
	yylval.token = COMMA;
	return COMMA;
}

token IntegerValuePatternAction(const char * lexeme, int length) {
	LogDebug("IntegerValuePatternAction: '%s'.", lexeme);
	  // Reservar memoria para el lexema identificado y el \0 final:
    char * text = (char *) calloc(length + 1, sizeof(char));
    // Copiar el lexema y \0 para evitar segmentation-faults:
    strncpy(text, lexeme, length);
    // Convertir el lexema en un entero de verdad:
    yylval.integer = atoi(text);
    // Liberar la memoria, ya que solo nos interesa el resultado de atoi(.)
    // (no debería llamar a free(.), si “text” debe ser utilizado en Bison):
    free(text);
    // Indicarle a Bison de qué terminal se trata:
	return INTEGER_VALUE;	
}

token MinValuePatternAction(const char * lexeme) {
	LogDebug("MinValuePatternAction: '%s'.", lexeme);
	yylval.token = MIN;
	return MIN;	
}

token MaxValuePatternAction(const char * lexeme) {
	LogDebug("MaxValuePatternAction: '%s'.", lexeme);
	yylval.token = MAX;
	return MAX;	
}

token AverageValuePatternAction(const char * lexeme) {
	LogDebug("AverageValuePatternAction: '%s'.", lexeme);
	yylval.token = AVG;
	return AVG;	
}

token DeletePatternAction(const char * lexeme) {
	LogDebug("DeletePatternAction: '%s'.", lexeme);
	yylval.token = DELETE;
	return DELETE;	
}