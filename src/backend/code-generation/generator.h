#ifndef GENERATOR_HEADER
#define GENERATOR_HEADER

#include "../support/logger.h"
#include "../../backend/support/shared.h"
#include <stdio.h>


void Generator(tProgram *  result);
void generateClassSection(tClassSection * node);
void generateClassList(tClassList * node);
void generateClassDeclaration(tClassDeclaration * node) ;
void generateInstanceAttribute(tInstanceAtt * node);
void generateAttrList(tAttrList * node) ;
void generateAttrDeclaration(tAttrDeclaration * node);
void generateClassMethod(tClassMethod * node);
void generateVarList(tVarList * node);
void generateVarDeclaration(tVarDeclaration * node);
void generateParamList(tParamList * node);
void generateVarEquals(tVarEquals * node);
void generateCodeSection(tCodeSection * node);
void generateCodeList(tCodeList * node);
void generateCodeComponents(tCodeComponents * node);
void generateWhileStatement(tWhileStatement * node);
void generateIfStatement(tIfStatement * node);
void generateElseStatement(tElseStatement * node);
void generateLogicalExpression(tLogicalExpression * node);
void generateDataValue(tDataValue * node);


#endif
