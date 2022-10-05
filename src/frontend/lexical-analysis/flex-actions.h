#ifndef FLEX_ACTIONS_HEADER
#define FLEX_ACTIONS_HEADER

#include "../../backend/support/shared.h"
#include "../syntactic-analysis/bison-parser.h"

/**
 * Se definen las acciones a ejecutar sobre cada patrón hallado mediante el
 * analizador léxico Flex. Este analizador solo puede identificar
 * construcciones regulares, ya que utiliza un autómata finito determinístico
 * (a.k.a. DFA), como mecanismo de escaneo y reconocimiento.
 *
 * Debería existir una acción por cada patrón disponible en Flex (es decir,
 * por cada regla).
 *
 * Solo aquellas acciones que tengan interés en conocer el largo del lexema
 * emplean el parámetro adicional "length". Esto es útil cuando se desea
 * asignar memoria dinámica, y por lo tanto, se debe saber exactamente el
 * largo de aquello que se va a almacenar.
 */

// Bloque de comentarios multilínea.
void BeginCommentPatternAction();
void EndCommentPatternAction();

// Patrones terminales del lenguaje diseñado.
token AdditionOperatorPatternAction(const char * lexeme);
token CloseParenthesisPatternAction(const char * lexeme);
token DivisionOperatorPatternAction(const char * lexeme);
token MultiplicationOperatorPatternAction(const char * lexeme);
token OpenParenthesisPatternAction(const char * lexeme);
token SubtractionOperatorPatternAction(const char * lexeme);
token BeginStringPatternAction(const char * lexeme);

token CapitalizedWordPatternAction(const char * lexeme);

token AlphanumericWordPatternAction(const char * lexeme);

token ClassDefinitionsPatternAction(const char * lexeme);
token DataTypePatternAction(const char * lexeme);

token GreaterThanPatternAction(const char * lexeme);

token LessThanPatternAction(const char * lexeme);

token OpenBracketPatternAction(const char * lexeme);
token CloseBracketPatternAction(const char * lexeme);

token DotPatternAction(const char * lexeme);
token SemicolonPatternAction(const char * lexeme);

token ReturnKeywordPatternAction(const char * lexeme);

token NewKeywordPatternAction(const char * lexeme);

token IfKeywordPatternAction(const char * lexeme);

token WhileKeywordPatternAction(const char * lexeme);

token ElseKeywordPatternAction(const char * lexeme);

token TrueKeywordPatternAction(const char * lexeme);

token FalseKeywordPatternAction(const char * lexeme);

token EqualEqualPatternAction(const char * lexeme); 

// Patrón desconocido, permite abortar debido a un error de sintaxis.
token UnknownPatternAction(const char * lexeme, const int length);

// Regla que no hace nada, permite ignorar parte de la entrada.
void IgnoredPatternAction(const char * lexeme, const int length);

#endif
