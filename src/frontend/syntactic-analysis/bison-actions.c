#include "../../backend/domain-specific/calculator.h"
#include "../../backend/support/logger.h"
#include "bison-actions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BLOCK	1

/**
 * Implementación de "bison-grammar.h".
 */

/**
* Esta función se ejecuta cada vez que se emite un error de sintaxis.
*/
void yyerror(const char * string) {
	LogError("Mensaje: '%s' debido a '%s' (linea %d).", string, yytext, yylineno);
	LogError("En ASCII es:");
	LogErrorRaw("\t");
	const int length = strlen(yytext);
	for (int i = 0; i < length; ++i) {
		LogErrorRaw("[%d]", yytext[i]);
	}
	LogErrorRaw("\n\n");
}

/**
* Esta acción se corresponde con el no-terminal que representa el símbolo
* inicial de la gramática, y por ende, es el último en ser ejecutado, lo que
* indica que efectivamente el programa de entrada se pudo generar con esta
* gramática, o lo que es lo mismo, que el programa pertenece al lenguaje.
*/
tProgram * ProgramGrammarAction(tClassSection * claSection, tCodeSection * codeSection) {
	LogDebug("Reconozco patrón. ProgramGrammarAction()");
	tProgram * value = calloc(BLOCK, sizeof(tProgram));
	if (value == NULL)
	{
		return value;
	}
	value->classSection = claSection;
	value->codeSection = codeSection;
	
	/*
	* "state" es una variable global que almacena el estado del compilador,
	* cuyo campo "succeed" indica si la compilación fue o no exitosa, la cual
	* es utilizada en la función "main".
	*/
	state.succeed = true;
	/*
	* Por otro lado, "result" contiene el resultado de aplicar el análisis
	* sintáctico mediante Bison, y almacenar el nood raíz del AST construido
	* en esta variable. Para el ejemplo de la calculadora, no hay AST porque
	* la expresión se computa on-the-fly, y es la razón por la cual esta
	* variable es un simple entero, en lugar de un nodo.
	*/
	state.result = value;
	return value;
}

int AdditionExpressionGrammarAction(const int leftValue, const int rightValue) {
	LogDebug("\tAdditionExpressionGrammarAction(%d, %d)", leftValue, rightValue);
	return Add(leftValue, rightValue);
}

int SubtractionExpressionGrammarAction(const int leftValue, const int rightValue) {
	LogDebug("\tSubtractionExpressionGrammarAction(%d, %d)", leftValue, rightValue);
	return Subtract(leftValue, rightValue);
}

int MultiplicationExpressionGrammarAction(const int leftValue, const int rightValue) {
	LogDebug("\tMultiplicationExpressionGrammarAction(%d, %d)", leftValue, rightValue);
	return Multiply(leftValue, rightValue);
}

int DivisionExpressionGrammarAction(const int leftValue, const int rightValue) {
	LogDebug("\tDivisionExpressionGrammarAction(%d, %d)", leftValue, rightValue);
	return Divide(leftValue, rightValue);
}

int FactorExpressionGrammarAction(const int value) {
	LogDebug("\tFactorExpressionGrammarAction(%d)", value);
	return value;
}

int ExpressionFactorGrammarAction(const int value) {
	LogDebug("\tExpressionFactorGrammarAction(%d)", value);
	return value;
}

int ConstantFactorGrammarAction(const int value) {
	LogDebug("\tConstantFactorGrammarAction(%d)", value);
	return value;
}

int IntegerConstantGrammarAction(const int value) {
	LogDebug("\tIntegerConstantGrammarAction(%d)", value);
	return value;
}

tClassSection * ClassListGrammarAction(tClassList * classList) {
	LogDebug("\tClassListGrammarAction()");

	tClassSection * res = calloc(BLOCK, sizeof(tClassSection));
	if (res == NULL) {
		return NULL;
	}
	res->classList = classList;
	return res;
}

tClassList * ClassDeclarationGrammarAction(tClassDeclaration * classDeclaration){
	LogDebug("\tClassDeclarationGrammarAction()");
	tClassList * res = calloc(BLOCK, sizeof(tClassList));
	if (res == NULL) {
		return NULL;
	}
	res->classDeclaration = classDeclaration;
	res->next = NULL;
	res->type = CLASS_DECLARATION;
	return res;
}

tClassList * MultipleClassDeclarationGrammarAction(tClassDeclaration * classDeclaration,tClassList * next){
	LogDebug("\tMultipleClassDeclarationGrammarAction()");
	tClassList * res = calloc(BLOCK, sizeof(tClassList));
	if (res == NULL) {
		return NULL;
	}
	res->classDeclaration = classDeclaration;
	res->next = next;
	res->type = MULTIPLE_CLASS_DECLARATION;
	return res;
}

tClassDeclaration * VarListGrammarAction(char * className, tVarList * varList){
	LogDebug("\tVarListGrammarAction()");
	tClassDeclaration * res = calloc(BLOCK, sizeof(tClassDeclaration));
	if (res == NULL) {
		return NULL;
	}
	res->className = className;
	res->varList = varList;
	return res;
}

tInstanceAtt * InstanceAttributeGrammarAction(char * instanceName, char * varName){
	LogDebug("\tInstanceAttributeGrammarAction()");
	tInstanceAtt * res = calloc(BLOCK, sizeof(tInstanceAtt));
	if (res == NULL) {
		return NULL;
	}
	res->instanceName = instanceName;
	res->varName = varName;
	return res;
}

tClassMethod * MethodsAndVarNameGrammarAction(char * className, MethodType  method, char * arguments){
	LogDebug("\tMethodsAndVarNameGrammarAction()");
	tClassMethod * res = (tClassMethod *) calloc(BLOCK, sizeof(tClassMethod));
	if (res == NULL) {
		return NULL;
	}
	res->className = className;
	res->method = method;
	res->arguments = arguments;
	return res;
}

tVarList * VarDeclarationGrammarAction(tVarDeclaration * varDec){
	LogDebug("\tVarDeclarationGrammarAction()");
	tVarList * res = calloc(BLOCK, sizeof(tVarList));
	if (res == NULL) {
		return NULL;
	}
	res->varDeclaration = varDec;
	res->type = SINGLE_VAR_DECLARATION;
	return res;
}

tVarList * MultipleVarDeclarationGrammarAction(tVarDeclaration * varDec,tVarList * next){
	LogDebug("\tMultipleVarDeclarationGrammarAction()");
	tVarList * res = calloc(BLOCK, sizeof(tVarList));
	if (res == NULL) {
		return NULL;
	}
	res->varDeclaration = varDec;
	res->next = next;
	res->type = MULTIPLE_VAR_DECLARATION;
	return res;
}

tVarDeclaration * DataTypeVarNameAndVarEqualsGrammarAction(textNode * dataType, char * varName, tVarEquals * varEquals){
	LogDebug("\tDataTypeVarNameAndVarEqualsGrammarAction()");
	tVarDeclaration * res = calloc(BLOCK, sizeof(tVarDeclaration));
	if (res == NULL) {
		return NULL;
	}
	res->dataType = dataType;
	res->varName = varName;
	res->varEq = varEquals;
	res->type = VARDEC_DATATYPE_VARNAME_VAREQ;
	return res;
}

tVarDeclaration * VarNameParamListGrammarAction(char * className, char * varName, tParamList *paramList){
	LogDebug("\tVarNameParamListGrammarAction()");
	tVarDeclaration * res = calloc(BLOCK, sizeof(tVarDeclaration));
	if (res == NULL) {
		return NULL;
	}
	res->className = className;
	res->paramList = paramList;
	res->varName = varName;
	res->type = VARDEC_CLASSNAME_VARNAME_PARAMLIST;
	return res;
}

tVarDeclaration * DataTypeAndVarNameGrammarAction(textNode * dataType, char * varName){
	LogDebug("\tDataTypeAndVarNameGrammarAction()");
	tVarDeclaration * res = calloc(BLOCK, sizeof(tVarDeclaration));
	if (res == NULL) {
		return NULL;
	}
	res->varName = varName;
	res->dataType = dataType;
	res->type = VARDEC_VARNAME_DATATYPE;
	return res;
}

tDataValue * TrueGrammarAction(){
	LogDebug("\tTrueGrammarAction()");
	tDataValue * res = calloc(BLOCK, sizeof(tDataValue));
	res->boolVal = true;
	res->type = BOOLEAN_VAL;
	return res;
}

tDataValue * FalseGrammarAction(){
	LogDebug("\tFalseGrammarAction()");
	tDataValue * res = calloc(BLOCK, sizeof(tDataValue));
	res->boolVal = false;
	res->type = BOOLEAN_VAL;
	return res;
}

tDataValue * StringValueGrammarAction(char * value){
	LogDebug("\tStringValueGrammarAction()");
	tDataValue * res = calloc(BLOCK, sizeof(tDataValue));
	if (res == NULL) {
		return NULL;
	}
	res->stringVal = value;
	res->type = STRING_VAL;
	return res;
}

tDataValue * IntegerValueGrammarAction(int value){
	LogDebug("\tIntegerValueGrammarAction()");
	tDataValue * res = calloc(BLOCK, sizeof(tDataValue));
	if (res == NULL) {
		return NULL;
	}
	res->integerVal = value;
	res->type = INTEGER_VAL;
	return res;
}

tVarEquals * VarEqDataValueGrammarAction(tDataValue * dataVal){
	LogDebug("\tDataValueGrammarAction()");
	tVarEquals * res = calloc(BLOCK, sizeof(tVarEquals));
	if (res == NULL) {
		return NULL;
	}
	res->val = dataVal;
	res->type = VAREQ_DATA_VALUE;
	return res;
}

tLogicalExpression * ClassMethodLogicalExpressionGrammarAction(tClassMethod * classMethod){
	LogDebug("\tClassMethodLogicalExpressionGrammarAction()");
	tLogicalExpression * res = calloc(BLOCK, sizeof(tLogicalExpression));
	if (res == NULL) {
		return NULL;
	}
	res->classMethod = classMethod;
	res->type = CLASS_METHOD_LOGEX;

	return res;
}

tLogicalExpression * MultipleLogicalExpressionGrammarAction(tLogicalExpression * left, char * logConnector, tLogicalExpression * right ){
	LogDebug("\tMultipleLogicalExpressionGrammarAction()");
	tLogicalExpression * res = calloc(BLOCK, sizeof(tLogicalExpression));
	if (res == NULL) {
		return NULL;
	}
	res->left = left;
	res->right = right;
	res->logicalConnector = logConnector;
	res->type = MULTIPLE_LOGEX;

	return res;
}
tLogicalExpression * VarNameLogicalExpressionGrammarAction(char * varName){
	LogDebug("\tVarNameLogicalExpressionGrammarAction()");

	tLogicalExpression * res = calloc(BLOCK, sizeof(tLogicalExpression));
	if (res == NULL) {
		return NULL;
	} 

	res->varName = varName;
	res->type = VAR_NAME_LOGEX;

	return res;
}
tLogicalExpression * InstanceAttLogicalExpressionGrammarAction(tInstanceAtt * instanceAtt){
	LogDebug("\tInstanceAttLogicalExpressionGrammarAction()");

	tLogicalExpression * res = calloc(BLOCK, sizeof(tLogicalExpression));
	if (res == NULL) {
		return NULL;
	} 
	res->instanceAtt = instanceAtt;
	INSTANCE_ATT_LOGEX;
	return res;
}
tLogicalExpression * DataValueLogicalExpressionGrammarAction(tDataValue * value){
	LogDebug("\tDataValueLogicalExpressionGrammarAction()");

	tLogicalExpression * res = calloc(BLOCK, sizeof(tLogicalExpression));
	if (res == NULL) {
		return NULL;
	} 
	res->dataValue = value;
	res->type = DATA_VAL_LOGEX;
	return res;
}
tLogicalExpression * ExpressionLogicalExpressionGrammarAction(int expression){
	LogDebug("\tExpressionLogicalExpressionGrammarAction()");

	tLogicalExpression * res = calloc(BLOCK, sizeof(tLogicalExpression));
	if (res == NULL) {
		return NULL;
	} 
	res->expression = expression;
	res->type = EXP_LOGEX;

	return res;
}

tParamList * ParamListGrammarAction(tDataValue * value){
	LogDebug("\tParamListGrammarAction()");

	tParamList * res = calloc(BLOCK, sizeof(tParamList));
	if (res == NULL) {
		return NULL;
	} 

	res->value = value;
	res->next = NULL;

	return res;	
}


tParamList * MultipleParamListGrammarAction(tDataValue * dataVal, tParamList * paramList){
	LogDebug("\tMultipleParamListGrammarAction()");

	tParamList * res = calloc(BLOCK, sizeof(tParamList));
	if (res == NULL) {
		return NULL;
	} 

	res->value = dataVal;
	res->next = paramList;

	return res;
}


textNode * TypeGrammarAction(char * type) {
	LogDebug("\tTypeGrammarAction()");
	textNode * res = calloc(BLOCK, sizeof(textNode));
	if (res == NULL) {
		return NULL;
	}
	res->text = type;
	return res;
}

tCodeSection * CodeListGrammarAction(tCodeList * codeList) {
	LogDebug("\tCodeListGrammarAction()");
	tCodeSection * res = calloc(BLOCK, sizeof(tCodeSection));
	if (res == NULL) {
		return NULL;
	}
	res->codeList = codeList;
	return res;
}

tCodeList * CodeComponentsGrammarAction(tCodeComponents * codeComponent) {
	LogDebug("\tCodeComponentsGrammarAction()");
	tCodeList * res = calloc(BLOCK, sizeof(tCodeList));
	if (res == NULL) {
		return NULL;
	}
	res->codeComponents = codeComponent;
	res->next = NULL;
	return res;
}
tCodeList * MultipleCodeComponentsGrammarAction(tCodeComponents * codeComponent,tCodeList * next) {
	LogDebug("\tMultipleCodeComponentsGrammarAction()");
	tCodeList * res = calloc(BLOCK, sizeof(tCodeList));
	if (res == NULL) {
		return NULL;
	}
	res->codeComponents = codeComponent;
	res->next = next;
	return res;
}


tCodeComponents * IfGrammarAction(tIfStatement * ifStatement) {
	LogDebug("\tIfGrammarAction()");
	tCodeComponents * res = calloc(BLOCK, sizeof(tCodeComponents));
	if (res == NULL) {
		return NULL;
	}
	res->type = IF_COMPONENT;
	res->ifStatement = ifStatement;
	return res;
}
tCodeComponents * WhileGrammarAction(tWhileStatement * whileStatement) {
	LogDebug("\tWhileGrammarAction()");
	tCodeComponents * res = calloc(BLOCK, sizeof(tCodeComponents));
	if (res == NULL) {
		return NULL;
	}
	res->whileStatement = whileStatement;
	return res;
}

tCodeComponents * CodeVarDeclarationGrammarAction(tVarDeclaration * varDec) {
	LogDebug("\tCodeVarDeclarationGrammarAction()");
	tCodeComponents * res = calloc(BLOCK, sizeof(tCodeComponents));
	if (res == NULL) {
		return NULL;
	}
	res->type = VAR_DECLARATION_COMPONENT;
	res->varDeclaration = varDec;
	return res;
}
tCodeComponents * VarNameEqualsVarGrammarAction(char * name, tVarEquals * varEq) {
	LogDebug("\tVarNameEqualsVarGrammarAction()");
	tCodeComponents * res = calloc(BLOCK, sizeof(tCodeComponents));
	if (res == NULL) {
		return NULL;
	}
	res->type = VAR_EQUALS_COMPONENT;
	res->varName = name;
	res->varEq = varEq;
	return res;
}
tCodeComponents * InstanceAttributeEqualGrammarAction(tInstanceAtt * instanceAtt, tVarEquals * varEq) {
	LogDebug("\tInstanceAttributeEqualGrammarAction()");
	tCodeComponents * res = calloc(BLOCK, sizeof(tCodeComponents));
	if (res == NULL) {
		return NULL;
	}
	res->type = INSTANCE_ATTRIBUTE_COMPONENT;
	res->instanceAtt = instanceAtt;
	res->varEq = varEq;
	return res;
}
tCodeComponents * ClassMethodGrammarAction(tClassMethod * classMethod) {
		LogDebug("\tClassMethodGrammarAction()");
	tCodeComponents * res = calloc(BLOCK, sizeof(tCodeComponents));
	if (res == NULL) {
		return NULL;
	}
	res->type = CLASS_METHOD_COMPONENT;
	res->classMethod = classMethod;
	return res;
}
tCodeComponents * CommentCodeGrammarAction(char * comment) {
		LogDebug("\tCommentGrammarAction()");
	tCodeComponents * res = calloc(BLOCK, sizeof(tCodeComponents));
	if (res == NULL) {
		return NULL;
	}
	res->type = COMMENT_COMPONENT;
	res->comment = comment;
	return res;
}


tIfStatement * IfInitializedGrammarAction(tLogicalExpression * logExp, tCodeList * codeList, tElseStatement * elseStatement) {
	LogDebug("\tIfInitializedGrammarAction()");
	tIfStatement * res = calloc(BLOCK, sizeof(tIfStatement));
	if (res == NULL) {
		return NULL;
	}
	res->logicalExpression = logExp;
	res->codeList = codeList;
	res->elseStatement = elseStatement;
	return res;
}


tElseStatement * EmptyGrammarAction(){
	LogDebug("\tEmptyGrammarAction()");
	tElseStatement * res = calloc(BLOCK, sizeof(tElseStatement));
	if (res == NULL) {
		return NULL;
	}
	res->type = ELSE_EMPTY;
	return NULL;
}
tElseStatement * ElseIfGrammarAction(tIfStatement * ifStatement) {
	LogDebug("\tElseIfGrammarAction()");
	tElseStatement * res = calloc(BLOCK, sizeof(tElseStatement));
	if (res == NULL) {
		return NULL;
	}
	res->ifStatement = ifStatement;
	res->type = ELSE_IF;
	return res;
}
tElseStatement * ElseCodeListGrammarAction(tCodeList * codeList){
	LogDebug("\tElseCodeListGrammarAction()");
	tElseStatement * res = calloc(BLOCK, sizeof(tElseStatement));
	if (res == NULL) {
		return NULL;
	}
	res->codeList = codeList;
	res->type = ELSE_CODE_LIST;
	return res;	
}


tWhileStatement * WhileInitializedGrammarAction(tLogicalExpression * logExp, tCodeList * codeList){
	LogDebug("\tWhileInitializedGrammarAction()");
	tWhileStatement * res = calloc(BLOCK, sizeof(tWhileStatement));
	if (res == NULL) {
		return NULL;
	}
	res->logicalExpression = logExp;
	res->codeList = codeList;
	return res;		
}



tVarEquals * VarEqInstanceAttributeGrammarAction(tInstanceAtt *instanceAtt){
	LogDebug("\tVarEqInstanceAttributeGrammarAction()");
	tVarEquals * res = calloc(BLOCK, sizeof(tVarEquals));
	if (res == NULL) {
		return NULL;
	}
	res->instanceAtt = instanceAtt;
	res->type = VAREQ_INSTANCE_ATT;
	return res;			
}

tVarEquals * VarEqVarNameGrammarAction(char * varName){
	LogDebug("\tVarEqVarNameGrammarAction()");
	tVarEquals * res = calloc(BLOCK, sizeof(tVarEquals));
	if (res == NULL) {
		return NULL;
	}
	res->name = varName;
	res->type = VAREQ_VAR_NAME;
	return res;		
}
tVarEquals *VarEqClassMethodGrammarAction(tClassMethod *classMethod){
	LogDebug("\tVarEqClassMethodGrammarAction()");
	tVarEquals * res = calloc(BLOCK, sizeof(tVarEquals));
	if (res == NULL) {
		return NULL;
	}
	res->method = classMethod;
	res->type = VAREQ_CLASS_METHOD;
	return res;	
}

MethodType DeleteGrammarAction() {
	return DELETE_METHOD;
}
MethodType AvgGrammarAction() {
	return AVG_METHOD;
}
MethodType MinGrammarAction() {
	return MIN_METHOD;
}
MethodType MaxGrammarAction() {
	return MAX_METHOD;
}