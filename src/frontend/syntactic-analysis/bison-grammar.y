%{

#include "bison-actions.h"

%}

// Tipos de dato utilizados en las variables semánticas ($$, $1, $2, etc.).
%union {
	// No-terminales (backend).
	/*
	Program program;
	Expression expression;
	Factor factor;
	Constant constant;
	...
	*/

	// No-terminales (frontend).
	int program;
	int classSection;
	int classList;
	int classDeclaration
	int className;
	int attrList;
	int attrDeclaration;
	int dataType;
	int attrName;

	int codeSection;
	int codeComponents;
	int ifStatement;
	int elseStatement
	int whileStatement;

	int variableList;
	int variableDefinition;

	int condition;
	int logicalExpression;
	int expression;
	int factor;
	int constant;

	// Terminales.
	token token;
	int integer;
	int string;
	int bool;
}

// IDs y tipos de los tokens terminales generados desde Flex.
%token <token> ADD
%token <token> SUB
%token <token> MUL
%token <token> DIV

%token <token> EQ

%token <token> EQEQ
%token <token> GT
%token <token> LT

%token <token> OPEN_PARENTHESIS
%token <token> CLOSE_PARENTHESIS

%token <token> OPEN_BRACKET
%token <token> CLOSE_BRACKET
%token <token> SEMI_COLON
%token <token> DOT

%token <token> CLASS_SECTION 
%token <token> NEW
%token <token> RETURN

%token <integer> INTEGER
%token <string> STRING
%token <bool> BOOLEAN

%token <token> CAPITALIZED_NAME
%token <token> ALPHANUMERIC_NAME

%token <token> IF
%token <token> ELSE
%token <token> WHILE

// Tipos de dato para los no-terminales generados desde Bison.
%type <program> program
%type <expression> expression
%type <factor> factor
%type <constant> constant

// Reglas de asociatividad y precedencia (de menor a mayor).
%left ADD SUB
%left MUL DIV

// El símbolo inicial de la gramatica.
%start program


%%

program: classSection codeSection									{ $$ = ProgramGrammarAction($1); }
	;

classSection: CLASS_SECTION OPEN_BRACKET classList CLOSE_BRACKET										{ $$ = ClassDefinitionsPatternAction($1);}
	;

classList: classDeclaration
	| classDeclaration classList
	;

classDeclaration: className OPEN_BRACKET attrList CLOSE_BRACKET
	;

className: CAPITALIZED_NAME
	;

attrList: attrDeclaration 
	| attrDeclaration attrList
	;

attrDeclaration: dataType attrName SEMI_COLON
	;

dataType: INTEGER 
	| STRING 
	| BOOLEAN
	;

attrName: ALPHANUMERIC_NAME
	;

codeSection: codeList
	;

codeList: codeComponents 
	| codeComponents codeList
	;

codeComponents: ifStatement 
	| whileStatement 
	| variableList 
	| variableDefinition
	;

ifStatement: IF condition OPEN_BRACKET codeList CLOSE_BRACKET elseStatement
	;

elseStatement: %empty 
	| ELSE OPEN_BRACKET codeList CLOSE_BRACKET
	;

whileStatement: WHILE condition OPEN_BRACKET codeList CLOSE_BRACKET
	;

condition: OPEN_PARENTHESIS logicalExpression CLOSE_PARENTHESIS
	;

variableInitialized: ALPHANUMERIC_NAME EQ 
	;

logicalExpression: logicalExpression AND logicalExpression
	| logicalExpression OR logicalExpression
	| 
	;


expression: expression[left] ADD expression[right]					{ $$ = AdditionExpressionGrammarAction($left, $right); }
	| expression[left] SUB expression[right]						{ $$ = SubtractionExpressionGrammarAction($left, $right); }
	| expression[left] MUL expression[right]						{ $$ = MultiplicationExpressionGrammarAction($left, $right); }
	| expression[left] DIV expression[right]						{ $$ = DivisionExpressionGrammarAction($left, $right); }
	| factor														{ $$ = FactorExpressionGrammarAction($1); }
	;

factor: OPEN_PARENTHESIS expression CLOSE_PARENTHESIS				{ $$ = ExpressionFactorGrammarAction($2); }
	| constant														{ $$ = ConstantFactorGrammarAction($1); }
	;

constant: INTEGER													{ $$ = IntegerConstantGrammarAction($1); }
	;

%%
