#include "generator.h"


FILE * fd;
FILE * fd_config;

/**
 * Implementación de "generator.h".
 */

void Generator(tProgram * node) {
	LogDebug("Generator\n");
	
	
	const char * file_name = "output.js";
	fd = fopen(file_name, "w+");

	if (node->credentialSection != NULL) {
		fd_config = fopen("configprueba.js", "w+");
		generateSetup(node->credentialSection);
		fclose(fd_config);
	} else {
		LogDebug("\t sin credenciales");
	}

	if (node->classSection != NULL) {
		generateClassSection(node->classSection);
	} else {
		LogDebug("no habia clases");
	}

	if (node->codeSection != NULL) {
		generateCodeSection(node->codeSection);
	} else {
		LogDebug("\t sin codigo");
	}

	generateExit();
	fclose(fd);
}

void generateExit() {
	LogDebug("\tgenerateExit()");
	fprintf(fd, "await sequelize.sync();\n");
	fprintf(fd, "await sequelize.close();\n");
}

void generateSetup(tCredentialsSection * credentials) {
	LogDebug("\tgenerateSetup()");

	generateConfig(credentials);
	fprintf(fd, "import { sequelize, DataTypes } from './config.js';\n");
}

void generateConfig(tCredentialsSection * credentials) {
	LogDebug("\tgenerateConfig");
	fprintf(fd_config, "import { Sequelize, DataTypes } from 'sequelize';\n");

	tCredentialList * list = credentials->credentialList;
	tCredentialDefinition * def = NULL;

	while (list) {
		def = list->credentialDefinition;

		if (def != NULL) {
			fprintf(fd_config, "const %s = ", def->campo);
			generateDataValue(def->dataValue, fd_config);
			fprintf(fd_config, ";\n");
		}

		list = list->next;
	}

	fprintf(fd_config, "const sequelize = new Sequelize(database, user, password,\n");
	fprintf(fd_config, "{host, port, dialect: 'postgres', logging: (...msg) => console.log(msg)})\n");
	fprintf(fd_config, "export { sequelize, DataTypes }");
}

void generateClassSection(tClassSection * node){
	LogDebug("\tgenerateClassSection()");
	generateClassList(node->classList);
}

void generateClassList(tClassList * node){
	LogDebug("\tgenerateClassList()");
	generateClassDeclaration(node->classDeclaration);
	if (node->type == MULTIPLE_CLASS_DECLARATION)
	{
		generateClassList(node->next);
	}
}

void generateClassDeclaration(tClassDeclaration * node) {
	LogDebug("\tgenerateClassDeclaration()");
	fprintf(fd,"const %s = sequelize.define( \"%s\", {", node->className,node->className);
	generateAttrList(node->attrList);
	fprintf(fd, "await sequelize.sync({force: true});\n");
}

void generateInstanceAttribute(tInstanceAtt * node){
	LogDebug("\tgenerateInstanceAttribute()");
	fprintf(fd, "%s.%s", node->instanceName, node->varName);
	if (node->varEq != NULL) {
		LogDebug("en el varequelas este");
		fprintf(fd, " = ");
		generateVarEquals(node->varEq);
	}
}

void generateAttrList(tAttrList * node) {
	LogDebug("\tgenerateAttrList()");
	if (node == NULL) {
		fprintf(fd,"}, {freezeTableName:true});\n");
		return;
	}
	generateAttrDeclaration(node->attrDeclaration);
	generateAttrList(node->next);
}

void generateAttrDeclaration(tAttrDeclaration * node) {
	LogDebug("\tgenerateAttrDeclaration()");	
	switch (node->dataType->type)
	{
		case BOOL_TYPE:
			fprintf(fd, "%s: DataTypes.BOOLEAN", node->varName);
			break;
		
		case STR_TYPE:
			fprintf(fd, "%s: DataTypes.STRING", node->varName);			
			break;

		case INT_TYPE:
			fprintf(fd, "%s: DataTypes.INTEGER", node->varName);			
			break;
	}
	fprintf(fd,",");
}

void generateClassMethod(tClassMethod * node){
	LogDebug("\tgenerateClassMethod()");	
	switch (node->method)
	{
	case MAX_METHOD:
		fprintf(fd, "await %s.max('%s')", node->className, node->arguments);
		break;
	
	case MIN_METHOD:
		fprintf(fd, "await %s.min('%s')", node->className, node->arguments);
		break;
	
	case AVG_METHOD:
		fprintf(fd, "await %s.sum('%s') / await %s.count('%s')", node->className, node->arguments, node->className, node->arguments);
		break;

	// case DELETE_METHOD:
	// 	//fprintf para eliminar node->arguments de la tabla node->className
	// 	break;

	default:
		break;
	}
}

void generateVarDeclaration(tVarDeclaration * node) {
	LogDebug("\tgenerateVarDeclaration()");	

	fprintf(fd,"let %s", node->varName);

	switch (node->type) {
		case VARDEC_CLASSNAME_VARNAME_PARAMLIST:
			fprintf(fd," = %s.create({", node->className);
			generateParamList(node->paramList);
			fprintf(fd, "});\n");
			fprintf(fd, "await %s.sync();\n", node->className); 
			break;
		case VARDEC_DATATYPE_VARNAME_VAREQ:
			fprintf(fd, " = ");
			generateVarEquals(node->varEq);
			break;
		case VARDEC_VARNAME_DATATYPE:
			break;
		default:
			break;
	}
}


void generateParamList(tParamList * node){
	LogDebug("\tgenerateParamList()");	
	fprintf(fd,"%s: ", node->attrName);
	switch (node->type)
	{
	case PARAM_VALUE:
		generateDataValue(node->value, fd);
		break;
	case PARAM_VAR:
		fprintf(fd, "%s", node->varName);
	default:
		break;
	}
	if (node->next != NULL) {
		fprintf(fd, ", ");
		generateParamList(node->next);
	}
}

void generateVarEquals(tVarEquals * node){
	LogDebug("\tgenerateVarEquals()");	
	switch (node->type)
	{
	case VAREQ_INSTANCE_ATT:
		generateInstanceAttribute(node->instanceAtt); 
		break;

	case VAREQ_VAR_NAME:
		fprintf(fd,"%s;\n", node->name);
		break;

	case VAREQ_CLASS_METHOD:
		generateClassMethod(node->method);
		break;

	case VAREQ_DATA_VALUE:
		generateDataValue(node->val, fd);
		break;		

	default:
		break;
	}
	fprintf(fd, ";\n");
}

void generateCodeSection(tCodeSection * node) {
	LogDebug("\tgenerateCodeSection()");	
	generateCodeList(node->codeList);
}

void generateCodeList(tCodeList * node) {
	LogDebug("\tgenerateCodeList()");	
	if (node == NULL) {
		return;
	}
	generateCodeComponents(node->codeComponents);
	generateCodeList(node->next);
}

void generateCodeComponents(tCodeComponents * node) {
	LogDebug("\tgenerateCodeComponents()");	
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
		fprintf(fd, "%s", node->varName);
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
	LogDebug("\tgenerateWhileStatement()");	
	fprintf(fd,"while (" );
	generateLogicalExpression(node->logicalExpression);
	fprintf(fd,"){\n" );
	generateCodeList(node->codeList);
	fprintf(fd,"}\n" );
}

void generateIfStatement(tIfStatement * node) {
	LogDebug("\tgenerateIfStatement()");	
	fprintf(fd,"if (" );
	generateLogicalExpression(node->logicalExpression);
	fprintf(fd,"){\n" );
	generateCodeList(node->codeList);
	fprintf(fd,"}\n" );
	if (node->elseStatement != NULL) {
		generateElseStatement(node->elseStatement);
	}
}

void generateElseStatement(tElseStatement * node) {
	LogDebug("\tgenerateElseStatement()");
	if (node == NULL) {
		return;
	}
	fprintf(fd,"else " );
	switch (node->type)
	{
		case ELSE_CODE_LIST:
			fprintf(fd, "{\n");
			generateCodeList(node->codeList);
			fprintf(fd,"}\n" );
			break;
		case ELSE_IF:
			generateIfStatement(node->ifStatement);
			break;
		default:
			break;
	}
	
}

void generateLogicalExpression(tLogicalExpression * node) {
	LogDebug("\tgenerateLogicalExpression()");
	switch(node->type) {
		case MULTIPLE_LOGEX:
			generateLogicalExpression(node->left);
			fprintf(fd, " %s ", node->logicalConnector);
			generateLogicalExpression(node->right);
			break;
		case VAR_NAME_LOGEX:
			fprintf(fd, "%s", node->varName);
			break;
		
		case INSTANCE_ATT_LOGEX:
			generateInstanceAttribute(node->instanceAtt);
			break;
		
		case DATA_VAL_LOGEX:
			generateDataValue(node->dataValue, fd); 
			break;

		case CLASS_METHOD_LOGEX:
			generateClassMethod(node->classMethod);
			break;
		
		default:
			break;
	}
}

void generateDataValue(tDataValue * node, FILE * file){
	LogDebug("\tgenerateDataValue()");
	if (node == NULL)
	{
		return;
	}
		
	switch (node->type)
	{
		case BOOLEAN_VAL:
			fprintf(file,"%s", node->boolVal == true ? "true" : "false");
			break;

		case STRING_VAL:
			fprintf(file,"'%s'", node->stringVal);
			break;

		case INTEGER_VAL:
			fprintf(file,"%d", node->integerVal);
			break;

		default:
			break;
	}
}