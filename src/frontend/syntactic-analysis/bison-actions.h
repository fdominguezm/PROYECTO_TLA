#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../backend/support/shared.h"
#include "../../backend/semantic-analysis/abstract-syntax-tree.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Se definen las acciones a ejecutar sobre cada regla de producción de la
 * gramática. El objetivo de cada acción debe ser el de construir el nodo
 * adecuado que almacene la información requerida en el árbol de sintaxis
 * abstracta (i.e., el AST).
 */

// Programa.
tProgram * ProgramGrammarAction(tClassSection * claSection, tCodeSection *codeSection);

// Expresión.
int AdditionExpressionGrammarAction(const int leftValue, const int rightValue);
int SubtractionExpressionGrammarAction(const int leftValue, const int rightValue);
int MultiplicationExpressionGrammarAction(const int leftValue, const int rightValue);
int DivisionExpressionGrammarAction(const int leftValue, const int rightValue);
int FactorExpressionGrammarAction(const int value);

// Factores.
int ExpressionFactorGrammarAction(const int value);
int ConstantFactorGrammarAction(const int value);

// Constantes.
int IntegerConstantGrammarAction(const int value);

int CapitalizedWordGrammarAction(); 

int IntegerGrammarAction();

int StringGrammarAction();

int BooleanGrammarAction();



tClassSection * ClassListGrammarAction(tClassList *classList);


tClassList * ClassDeclarationGrammarAction(tClassDeclaration *classDeclaration);
tClassList * MultipleClassDeclarationGrammarAction(tClassDeclaration *classDeclaration,tClassList* next);


tClassDeclaration * ClassAttrListGrammarAction(char * className,tAttrList * attrList);


tInstanceAtt * InstanceAttributeGrammarAction(char * instanceName, char * varName);

tVarDeclaration * DataTypeVarNameAndVarEqualsGrammarAction(tDataType * dataType, char * varName, tVarEquals *varEquals);
tVarDeclaration * VarNameParamListGrammarAction(char * className,char * varName,tParamList * paramList);
tVarDeclaration * DataTypeAndVarNameGrammarAction(tDataType * dataType, char * varName);


tDataValue * TrueGrammarAction();
tDataValue * FalseGrammarAction();
tDataValue * StringValueGrammarAction(char * value);
tDataValue * IntegerValueGrammarAction(int value);


tVarEquals * VarEqDataValueGrammarAction(tDataValue * dataVal);
tVarEquals * VarEqInstanceAttributeGrammarAction(tInstanceAtt *instanceAtt);
tVarEquals * VarEqVarNameGrammarAction(char * varName);
tVarEquals *VarEqClassMethodGrammarAction(tClassMethod *classMethod); 

tDataType * IntTypeGrammarAction(char * type);
tDataType * StrTypeGrammarAction(char * type) ;
tDataType * BoolTypeGrammarAction(char * type);

tCodeSection * CodeListGrammarAction(tCodeList * codeList);

tCodeList * CodeComponentsGrammarAction(tCodeComponents * codeComponent);
tCodeList * MultipleCodeComponentsGrammarAction(tCodeComponents * codeComponent,tCodeList * next);


tCodeComponents * IfGrammarAction(tIfStatement * ifStatement);
tCodeComponents * WhileGrammarAction(tWhileStatement * whileStatement);
tCodeComponents * CodeVarDeclarationGrammarAction(tVarDeclaration *varDec);
tCodeComponents * VarNameEqualsVarGrammarAction(char * name, tVarEquals * varEq);
tCodeComponents * InstanceAttributeEqualGrammarAction(tInstanceAtt * instanceAtt, tVarEquals *varEq);
tCodeComponents * ClassMethodGrammarAction(tClassMethod * classMethod);
tCodeComponents * CommentCodeGrammarAction(char * comment);


tIfStatement * IfInitializedGrammarAction(tLogicalExpression * logExp, tCodeList * codeList, tElseStatement * elseStatement);


tElseStatement * EmptyGrammarAction();
tElseStatement * ElseIfGrammarAction(tIfStatement * ifStatement);
tElseStatement * ElseCodeListGrammarAction(tCodeList *codeList);


tWhileStatement * WhileInitializedGrammarAction(tLogicalExpression * logExp, tCodeList * codeList);


tLogicalExpression * MultipleLogicalExpressionGrammarAction(tLogicalExpression * left, char * logConnector, tLogicalExpression * right );
tLogicalExpression * VarNameLogicalExpressionGrammarAction(char * varName);
tLogicalExpression * InstanceAttLogicalExpressionGrammarAction(tInstanceAtt * instanceAtt);
tLogicalExpression * DataValueLogicalExpressionGrammarAction(tDataValue * value); 
tLogicalExpression * ExpressionLogicalExpressionGrammarAction(int expression);
tLogicalExpression * ClassMethodLogicalExpressionGrammarAction(tClassMethod * classMethod);

tParamList * ParamListValueGrammarAction(char * attrName, tDataValue * value);
tParamList * MultipleParamListValueGrammarAction(char * attrName, tDataValue * dataVal, tParamList * paramList);
tParamList * ParamListVarGrammarAction(char * attrName, char * varName);
tParamList * MultipleParamListVarGrammarAction(char * attrName, char * varName, tParamList * paramList);






tClassMethod * MethodsAndVarNameGrammarAction(char * className, MethodType method, char * varName);

MethodType DeleteGrammarAction();
MethodType AvgGrammarAction();
MethodType MinGrammarAction();
MethodType MaxGrammarAction();

tAttrDeclaration * ClassAttrDecGrammarAction(tDataType * dataType, char * varName);
tAttrList * MultipleAttrDecGrammarAction(tAttrDeclaration * attrDec, tAttrList *next);
tAttrList * AttrDecGrammarAction(tAttrDeclaration * attrDec);

#endif
