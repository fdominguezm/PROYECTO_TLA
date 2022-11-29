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

typedef enum DataType {
	BOOL_TYPE,
	STR_TYPE,
	INT_TYPE
} DataType;

typedef struct tDataType{
	char * text;
	DataType type;
}tDataType;

typedef enum DataValueType {
	BOOLEAN_VAL,
	STRING_VAL,
	INTEGER_VAL
} DataValueType;

typedef struct tDataValue{
	boolean boolVal;
	char * stringVal;
	int integerVal;
	DataValueType type;
} tDataValue;

typedef enum VarEqualsType {
	VAREQ_INSTANCE_ATT,
	VAREQ_VAR_NAME,
	VAREQ_CLASS_METHOD,
	VAREQ_DATA_VALUE
} VarEqualsType;

typedef struct tVarEquals{
	tDataValue * val;
	struct tInstanceAtt * instanceAtt;
	char * name;
	struct tClassMethod * method;
	VarEqualsType type;
} tVarEquals;

typedef struct tInstanceAtt
{
	char * instanceName;
	char * varName;
	tVarEquals * varEq;
}tInstanceAtt;

typedef enum MethodType {
	MAX_METHOD,
	MIN_METHOD,
	AVG_METHOD,
	DELETE_METHOD
} MethodType;

typedef struct tClassMethod
{
	char * className;
	MethodType method;
	char * arguments;
}tClassMethod;
typedef enum LogicalExpresionType{
	MULTIPLE_LOGEX,
	VAR_NAME_LOGEX,
	INSTANCE_ATT_LOGEX,
	DATA_VAL_LOGEX,
	EXP_LOGEX,
	CLASS_METHOD_LOGEX
}LogExType;

typedef struct tLogicalExpression{
	struct tLogicalExpression * right;
	struct tLogicalExpression * left;
	char * logicalConnector;
	char * varName;
	tInstanceAtt * instanceAtt;
	tDataValue * dataValue;
	int expression;
	tClassMethod * classMethod;
	LogExType type;
}tLogicalExpression;


typedef struct tIfStatement{
	tLogicalExpression * logicalExpression;
	struct tCodeList * codeList;
	struct tElseStatement * elseStatement;
} tIfStatement;


typedef struct tWhileStatement{
	tLogicalExpression * logicalExpression;
	struct tCodeList * codeList;
} tWhileStatement;

typedef enum CodeComponentType {
	WHILE_COMPONENT,
	IF_COMPONENT,
	VAR_DECLARATION_COMPONENT,
	VAR_EQUALS_COMPONENT,
	INSTANCE_ATTRIBUTE_COMPONENT,
	CLASS_METHOD_COMPONENT,
	COMMENT_COMPONENT
} CodeComponentType;

typedef struct tCodeComponents{
	tWhileStatement * whileStatement;
	tIfStatement * ifStatement;
	struct tVarDeclaration * varDeclaration;
	char * varName;
	tInstanceAtt * instanceAtt;
	struct tClassMethod * classMethod;
	char * comment;
	tVarEquals * varEq;
	CodeComponentType type;
} tCodeComponents;


typedef struct tCodeList{
	tCodeComponents * codeComponents;
	struct tCodeList * next;
} tCodeList;

typedef enum ElseStatementType {
	ELSE_EMPTY,
	ELSE_CODE_LIST,
	ELSE_IF
}ElseStatementType;

typedef struct tElseStatement{
	tIfStatement * ifStatement;
	tCodeList * codeList;
	ElseStatementType type;
} tElseStatement;

typedef struct tCodeSection{
	tCodeList * codeList;
} tCodeSection;


typedef struct tVar{
	char * name;
	tVarEquals varEq;
}tVar;

typedef struct tParamList{
	char * attrName;
	tDataValue * value;
	struct tParamList * next;
} tParamList;

typedef enum VarDeclarationType {
	VARDEC_DATATYPE_VARNAME_VAREQ,
	VARDEC_CLASSNAME_VARNAME_PARAMLIST,
	VARDEC_VARNAME_DATATYPE
}VarDeclarationType;

typedef struct tVarDeclaration{
	tDataType * dataType;
	char * varName;
	char * className;
	tVarEquals * varEq;
	tParamList * paramList;
	VarDeclarationType type;
}tVarDeclaration;

typedef struct tAttrDeclaration{
	tDataType * dataType;
	char * varName;
}tAttrDeclaration;

typedef struct tAttrList{
	tAttrDeclaration * attrDeclaration;
	struct tAttrList * next;
}tAttrList;

typedef struct tClassDeclaration
{
	char * className;
	tAttrList * attrList;
}tClassDeclaration;

typedef enum ClassListType {
	CLASS_DECLARATION,
	MULTIPLE_CLASS_DECLARATION
} ClassListType;

typedef struct tClassList
{
	tClassDeclaration * classDeclaration;
	struct tClassList * next;
	ClassListType type;
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
	tProgram * result;

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
