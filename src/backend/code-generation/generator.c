#include "../support/logger.h"
#include "generator.h"
#include "shared.h"
#include <stdio.h>

/**
 * Implementación de "generator.h".
 */

void Generator(tProgram * node) {

	generateClassSection(node->classSection);
	generateCodeSection(node->codeSection);
}

generateClassDeclaration(tClassDeclaration * node) {
	fprintf("createTable(\'%s\', ", node->className);
	generateVarList(node->varList);
}

generateVarList(tVarList * node) {
	fprintf("{");
		generateVarDeclaration(node->varDeclaration);
	if (node->type == MULTIPLE_VAR_DECLARATION) {
		fprintf(",");
		generateVarList(node->next);
	} else {
		generateVarDeclaration(node->varDeclaration);
	}
}

generateVarDeclaration(tVarDeclaration * node) {
	fprintf("%s: \'%s\'", node->varName, node->dataType);
}

/*

	createTable('House', {price:'int', street:'string});
	insertIntoTable('House', {price:2000, street:'lm campos'})
*/


{price: "int",street: "string"}