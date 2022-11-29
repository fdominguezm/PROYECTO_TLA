#include "generator.h"



/**
 * Implementación de "generator.h".
 */

void Generator(tProgram * node) {

	generateClassSection(node->classSection);
	generateCodeSection(node->codeSection);
}

void generateClassSection(tClassSection * node){
	generateClassList(node->classList);
}

void generateClassList(tClassList * node){
	generateClassDeclaration(node->classDeclaration);
	if (node->type == MULTIPLE_CLASS_DECLARATION)
	{
		generateClassList(node->next);
	}
}

void generateClassDeclaration(tClassDeclaration * node) {
	fprintf("../../../index.js","createTable(\'%s\', ", node->className);
	generateVarList(node->varList);
}

void generateInstanceAttribute(tInstanceAtt * node){
	if (node->varEq != NULL)
	{
		//frprintf para cambiar el valor de un atributo de una tabla
		generateVarEquals(node->varEq);
		return;
	}
	
	// Aca hago un fprintf para hacer un get del atributo node->varName en la tabla node->instanceName
}

void generateClassMethod(tClassMethod * node){
	switch (node->method)
	{
	case MAX_METHOD:
		//fprintf para obtener el max node->arguments de la tabla node->className
		break;
	
	case MIN_METHOD:
		//fprintf para obtener el min node->arguments de la tabla node->className
		break;
	
	case AVG_METHOD:
		//fprintf para hacer n avg node->arguments de la tabla node->className
		break;

	case DELETE_METHOD:
		//fprintf para eliminar node->arguments de la tabla node->className
		break;

	default:
		break;
	}
}

void generateVarList(tVarList * node) {
	fprintf("../../../index.js","{");
	generateVarDeclaration(node->varDeclaration);
	if (node->type == MULTIPLE_VAR_DECLARATION) {
		fprintf("../../../index.js",",");
		generateVarList(node->next);
	} else {
		fprintf("../../../index.js","});\n");
	}
}

void generateVarDeclaration(tVarDeclaration * node) {
	if (node->type == VARDEC_VARNAME_DATATYPE)
	{
		fprintf("../../../index.js","%s: \'%s\'", node->varName, node->dataType);
	}else if(node->type == VARDEC_CLASSNAME_VARNAME_PARAMLIST){
		//ACA INICIALIZAMOS LOS ATRIBUTOS DE LA CLASE
	}else if(node->type = VARDEC_DATATYPE_VARNAME_VAREQ){
		//ACA CREO UNA VARIABLE Y LA INICIALIZO
	}
}


void generateParamList(tParamList * node){
	generateDataValue(node->value); //Esto esta bien? hay que pasarle el nombre del parametro?
	if (node->next == NULL)
	{
		return;
	}
	generateParamList(node->next);
}

void generateVarEquals(tVarEquals * node){
	switch (node->type)
	{
	case VAREQ_INSTANCE_ATT:
		generateInstanceAttribute(node->instanceAtt); //Lo llamo asi no? no tengo que meter un fprontf aca creo
		break;

	case VAREQ_VAR_NAME:
		//fprintf de un get del atributo node->name de la tabla de variables
		break;

	case VAREQ_CLASS_METHOD:
		//fprintf de un get del atributo node->method
		break;

	case VAREQ_DATA_VALUE:
		//fprintf del atributo node->val
		break;		

	default:
		break;
	}
}

void generateCodeSection(tCodeSection * node) {
	generateCodeList(node->codeList);
}

void generateCodeList(tCodeList * node) {
	if (node == NULL) {
		return;
	}
	generateCodeComponents(node->codeComponents);
	generateCodeList(node->next);
}

void generateCodeComponents(tCodeComponents * node) {
	switch (node->type)
	{
	case WHILE_COMPONENT:
		generateWhileStatement(node->whileStatement);
		break;
	
	case IF_COMPONENT:
		generateIfStatement(node->ifStatement);
		break;
	
	case VAR_DECLARATION_COMPONENT:
		generateVarDeclaration(node->varDeclaration);
		break;
	
	case VAR_EQUALS_COMPONENT:
		/*accedo a la tabla de varibles, acceso a la variable*/
		generateVarEquals(node->varEq);
		break;
	
	case INSTANCE_ATTRIBUTE_COMPONENT:
		generateInstanceAttribute(node->instanceAtt);
		break;
	
	case CLASS_METHOD_COMPONENT:
		generateClassMethod(node->classMethod);
		break;
	
	case COMMENT_COMPONENT:
		/*comentario*/
		break;

	default:
		break;
	}
}

void generateWhileStatement(tWhileStatement * node) {
	generateLogicalExpression(node->logicalExpression);
	generateCodeList(node->codeList);
}

void generateIfStatement(tIfStatement * node) {
	generateLogicalExpression(node->logicalExpression);
	generateCodeList(node->codeList);
	generateElseStatement(node->elseStatement);
}

void generateElseStatement(tElseStatement * node) {
	if (node == NULL) {
		return;
	}
	switch (node->type)
	{
		case ELSE_CODE_LIST:
			generateCodeList(node->codeList);
			break;
		case ELSE_IF:
			generateIfStatement(node->ifStatement);
			break;
		default:
			break;
	}
	
}

void generateLogicalExpression(tLogicalExpression * node) {
	switch (node->type)
	{
		case MULTIPLE_LOGEX:
			generateLogicalExpression(node->left);
			generateLogicalExpression(node->right);
			break;
		
		case VAR_NAME_LOGEX:
			/*llamo la variable */
			break;
		
		case INSTANCE_ATT_LOGEX:
			generateInstanceAttribute(node->instanceAtt);
			break;
		
		case DATA_VAL_LOGEX:
			generateDataValue(node->dataValue); 
			break;

		case CLASS_METHOD_LOGEX:
			generateClassMethod(node->classMethod);
			break;
		
		default:
			break;
	}
}

void generateDataValue(tDataValue * node){
	switch (node->type)
	{
		case BOOLEAN_VAL:
			fprintf("../../../index.js","%d", node->boolVal);
			break;

		case STRING_VAL:
			fprintf("../../../index.js","%s", node->stringVal);
			break;

		case INTEGER_VAL:
			fprintf("../../../index.js","%d", node->integerVal);
			break;

		default:
			break;
	}
}
/*

	createTable('House', {price:'int', street:'string});
	insertIntoTable('House', {price:2000, street:'lm campos'})
*/


// {price: "int",street: "string"}