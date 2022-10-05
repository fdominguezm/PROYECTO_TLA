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
	int classDeclaration;
	int className;
	int classAttribute;

	int varList;
	int varDeclaration;
	int varName;
	int varEquals;

	int attrList;
	int attrDeclaration;
	int dataType;
	int attrName;

	int codeSection;
	int codeComponents;

	int ifStatement;
	int elseStatement;
	int whileStatement;

	int variableList;
	int variableDefinition;

	int condition;
	int logicalExpression;
	int expression;
	int factor;
	int constant;

	// Terminales.
	int token;

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
%token <token> NOTEQ

%token <token> OPEN_PARENTHESIS
%token <token> CLOSE_PARENTHESIS

%token <token> OPEN_BRACKET
%token <token> CLOSE_BRACKET
%token <token> SEMI_COLON
%token <token> DOT


%token <token> CLASS_SECTION 
%token <token> NEW
%token <token> RETURN

%token <token> INTEGER
%token <token> STRING
%token <token> BOOLEAN

%token <token> CAPITALIZED_NAME
%token <token> ALPHANUMERIC_NAME

%token <token> IF
%token <token> ELSE
%token <token> WHILE

%token <token> AND
%token <token> OR
%token <token> TRUEE
%token <token> FALSEE

// Tipos de dato para los no-terminales generados desde Bison.
%type <program> program
%type <expression> expression
%type <factor> factor
%type <constant> constant
%type <classSection> classSection;
%type <classList> classList;
%type <classDeclaration> classDeclaration;
%type <className> className;
%type <classAttribute> classAttribute;
%type <varList> varList;
%type <varDeclaration> varDeclaration;
%type <varName> varName;
%type <varEquals> varEquals;
%type <attrList> attrList;
%type <attrDeclaration> attrDeclaration;
%type <dataType> dataType;
%type <attrName> attrName;
%type <codeSection> codeSection;
%type <codeComponents> codeComponents;
%type <ifStatement> ifStatement;
%type <elseStatement> elseStatement;
%type <whileStatement> whileStatement;
%type <variableList> variableList;
%type <variableDefinition> variableDefinition;
%type <condition> condition;
%type <logicalExpression> logicalExpression;


// Reglas de asociatividad y precedencia (de menor a mayor).
%left ADD SUB
%left MUL DIV

// El símbolo inicial de la gramatica.
%start program


%%

program: classSection /*codeSection*/									{ $$ = ProgramGrammarAction($1); }
	;

classSection: CLASS_SECTION OPEN_BRACKET classList CLOSE_BRACKET		//{ $$ = ClassDefinitionsGrammarAction(); }							{ $$ = ClassDefinitionsPatternAction($1);}
	;

classList: classDeclaration
	| classDeclaration classList
	;

classDeclaration: className OPEN_BRACKET attrList CLOSE_BRACKET			
	;

attrList: varDeclaration | varDeclaration attrList
    ;

className: CAPITALIZED_NAME
	;

classAttribute: className DOT varName
	;

varList: varDeclaration 
	| varDeclaration varList
	;

varName: ALPHANUMERIC_NAME

varDeclaration: dataType varName SEMI_COLON | dataType varEquals
	;

varEquals: varName EQ ALPHANUMERIC_NAME SEMI_COLON

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
	| varList 
	| varEquals 
	| classAttribute EQ varName SEMI_COLON
	| classAttribute EQ /*VALUES*/ SEMI_COLON
	;

ifStatement: IF logicalExpression OPEN_BRACKET codeList CLOSE_BRACKET elseStatement
	;

elseStatement: %empty 
	| ELSE ifStatement
	| ELSE OPEN_BRACKET codeList CLOSE_BRACKET
	;

whileStatement: WHILE logicalExpression OPEN_BRACKET codeList CLOSE_BRACKET
	;

logicalExpression: OPEN_PARENTHESIS logicalExpression[left] AND logicalExpression[right] CLOSE_PARENTHESIS
	| OPEN_PARENTHESIS logicalExpression[left] OR logicalExpression[right] CLOSE_PARENTHESIS
	| OPEN_PARENTHESIS logicalExpression[left] EQEQ logicalExpression[right] CLOSE_PARENTHESIS
	| OPEN_PARENTHESIS logicalExpression[left] NOTEQ logicalExpression[right] CLOSE_PARENTHESIS
	| varName
	| classAttribute
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