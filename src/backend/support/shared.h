#ifndef SHARED_HEADER
#define SHARED_HEADER

#include <stdio.h>
#include "../semantic-analysis/abstract-syntax-tree.h"

// Descriptor del archivo de entrada que utiliza Bison.
extern FILE * yyin;

// Descriptor del archivo de salida que utiliza Bison.
extern FILE * yyout;

// La cantidad de caracteres en el lexema "yytext". Se debe leer en las
// acciones de Flex, no en Bison.
extern int yyleng;

// Variable global que contiene el número de la línea analizada.
extern int yylineno;

// Token actual en el tope de la pila del analizador Bison.
extern char * yytext;

// Función global de manejo de errores en Bison.
extern void yyerror(const char * string);

// Función global del analizador léxico Flex.
extern int yylex(void);

// Función global del analizador sintáctico Bison.
extern int yyparse(void);

// Emular tipo "boolean".
typedef enum {

	false = 0,
	true = 1
} boolean;

// El tipo de los tokens emitidos por Flex.
typedef int token;



typedef enum {
	EXPRESSION,
	CONSTANT
} FactorType;

typedef enum {
	ADDITION,
	SUBTRACTION,
	MULTIPLICATION,
	DIVISION,
	FACTOR
} ExpressionType;

typedef struct tExpression{
	ExpressionType type;
	struct tExpression * leftExpression;
	struct tExpression * rightExpression;
}tExpression;

typedef struct Factor{
	FactorType type;
 	tExpression * expression;
} Factor;

typedef struct textNode{
	char * text;
}textNode;

typedef struct tDataValue{
	boolean boolVal;
	char * stringVal;
	int integerVal;
} tDataValue;


typedef struct tVarEquals{
	tDataValue * val;
	tInstanceAtt * instanceAtt;
	char * name;
	tClassMethod * method;
} tVarEquals;

typedef struct tInstanceAtt
{
	char * instanceName;
	char * varName;
	tVarEquals * varEq;
}tInstanceAtt;

typedef struct tLogicalExpression{
	struct tLogicalExpression * right;
	struct tLogicalExpression * left;
	char * logicalConnector;
	char * varName;
	tInstanceAtt * instanceAtt;
	tDataValue * dataValue;
	tExpression * expression;
}tLogicalExpression;


typedef struct tIfStatement{
	tLogicalExpression * logicalExpression;
	tCodeList * codeList;
	tElseStatement * elseStatement;
} tIfStatement;


typedef struct tWhileStatement{
	tLogicalExpression * logicalExpression;
	tCodeList * codeList;
} tWhileStatement;

typedef struct tCodeComponents{
	 tWhileStatement * whileStatement;
	 tIfStatement * ifStatement;
	 tVarDeclaration * varDeclaration;
	char * varName;
	tInstanceAtt * instanceAtt;
	 tClassMethod * classMethod;
	textNode * comment;
	tVarEquals * varEq;
} tCodeComponents;


typedef struct tCodeList{
	tCodeComponents * codeComponents;
	struct tCodeList * next;
} tCodeList;


typedef struct tElseStatement{
	tIfStatement * ifStatement;
	tCodeList * codeList;
} tElseStatement;

typedef struct tCodeSection{
	tCodeList * codeList;
} tCodeSection;


typedef struct tVar{
	char * name;
	tVarEquals varEq;
}tVar;

typedef struct tParamList{
	tDataValue * value;
	struct tParamList * next;
} tParamList;

typedef struct tVarDeclaration{
	textNode * dataType;
	char * varName;
	char * className;
	tVarEquals *varEq;
	tParamList * paramList;
}tVarDeclaration;

typedef struct tVarList{
	tVarDeclaration * varDeclaration;
	struct tVarList * next;
}tVarList;

typedef struct tClassMethod
{
	char * className;
	char * method;
	char * arguments;
}tClassMethod;

typedef struct tClassDeclaration
{
	char * className;
	tVarList * varList;
}tClassDeclaration;

typedef struct tClassList
{
	tClassDeclaration * classDeclaration;
	struct tClassList * next;
}tClassList;


typedef struct tClassSection{
	tClassList *classList;
} tClassSection;

typedef struct tProgram{
	tClassSection * classSection;
	tCodeSection * codeSection;
}tProgram;


// Estado global de toda la aplicación.
typedef struct {

	// Indica si la compilación tuvo problemas hasta el momento.
	boolean succeed;

	// Indica el resultado de la compilación (para la calculadora).
	int result;

	// El nodo raíz del AST (se usará cuando se implemente el backend).
	tProgram * program;

	// Agregar lo que sea necesario para el compilador.
	// Agregar una pila para manipular scopes.
	// Agregar una tabla de símbolos.
	// ...

} CompilerState;

// El estado se define e inicializa en el archivo "main.c".
extern CompilerState state;

#endif
