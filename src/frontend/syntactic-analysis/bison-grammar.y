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
	int instanceAttribute;
	int classMethod;

	int varList;
	int varDeclaration;
	int varName;
	int varEquals;
	
	int dataType;

	int codeSection;
	int codeComponents;

	int ifStatement;
	int elseStatement;
	int whileStatement;


	int variableDefinition;
	
	int paramList;

	int logicalExpression;
	int expression;
	int factor;
	int constant;

	int openBra;
	int closeBra;
	int openPar;
	int closePar;
	int semiColon;

	int boolVal;
	int comment;

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
%token <token> GTEQ
%token <token> LTEQ
%token <token> NOTEQ

%token <token> OPEN_PARENTHESIS
%token <token> CLOSE_PARENTHESIS

%token <token> OPEN_BRACKET
%token <token> CLOSE_BRACKET
%token <token> SEMI_COLON
%token <token> DOT
%token <token> COMMA

%token <token> CLASS_SECTION 
%token <token> NEW
%token <token> RETURN

%token <token> INTEGER
%token <token> STRING
%token <token> BOOLEAN
%token <token> INTEGER_VALUE
%token <token> STRING_VALUE

%token <token> CAPITALIZED_NAME
%token <token> ALPHANUMERIC_NAME

%token <token> IF
%token <token> ELSE
%token <token> WHILE

%token <token> AND
%token <token> OR
%token <token> TRUEE
%token <token> FALSEE

%token <token> MIN
%token <token> MAX
%token <token> AVG
%token <token> DELETE

%token <token> COMMENT

// Tipos de dato para los no-terminales generados desde Bison.
%type <program> program
%type <expression> expression
%type <factor> factor
%type <constant> constant
%type <classSection> classSection
%type <classList> classList
%type <classDeclaration> classDeclaration
%type <className> className
%type <instanceAttribute> instanceAttribute
%type <varList> varList
%type <paramList> paramList
%type <varDeclaration> varDeclaration
%type <varName> varName
%type <varEquals> varEquals
%type <dataType> dataType
%type <codeSection> codeSection
%type <codeComponents> codeComponents
%type <ifStatement> ifStatement
%type <elseStatement> elseStatement
%type <whileStatement> whileStatement
%type <logicalExpression> logicalExpression
%type <boolVal> boolVal
%type <openBra> openBra
%type <closeBra> closeBra
%type <openPar> openPar
%type <closePar> closePar
%type <semiColon> semiColon
%type <classMethod> classMethod


// Reglas de asociatividad y precedencia (de menor a mayor).
%left ADD SUB
%left MUL DIV

// El símbolo inicial de la gramatica.
%start program


%%

program: classSection codeSection									{ $$ = ProgramGrammarAction($1); }
	;

classSection: CLASS_SECTION openBra classList closeBra		{ $$ = ClassDefinitionsGrammarAction(); }		
	;

classList: classDeclaration
	| classDeclaration classList
	;

classDeclaration: className openBra varList closeBra			
	;

className: CAPITALIZED_NAME												{ $$ = CapitalizedWordGrammarAction(); }
	;

instanceAttribute: varName DOT varName
	;

classMethod: className DOT methods openPar varName closePar
	;

varList: varDeclaration 
	| varDeclaration varList
	;

varName: ALPHANUMERIC_NAME
	;												//{ $$ = AlphanumericWordGrammarAction() }

varDeclaration: dataType varName semiColon 
	| dataType varName varEquals
	| className varName EQ NEW className OPEN_PARENTHESIS paramList CLOSE_PARENTHESIS semiColon;
	;

dataValue: boolVal
	| STRING_VALUE
	| INTEGER_VALUE
	;

paramList: dataValue
	| dataValue COMMA paramList
	;
	
varEquals:  EQ dataValue semiColon 
	|  EQ instanceAttribute semiColon
	| EQ classMethod semiColon
	;

dataType: INTEGER 														//{ $$ = In}
	| STRING 
	| BOOLEAN
	;

codeSection: codeList
	;

codeList: codeComponents 
	| codeComponents codeList
	;

codeComponents: ifStatement 
	| whileStatement 
	| varList 
	| varName varEquals 
	| instanceAttribute varEquals
	| instanceAttribute EQ varName semiColon
	| instanceAttribute EQ dataValue semiColon
	| classMethod semiColon
	| comment
	;

ifStatement: IF logicalExpression openBra codeList closeBra elseStatement
	;

elseStatement: %empty 
	| ELSE ifStatement
	| ELSE openBra codeList closeBra
	;

whileStatement: WHILE logicalExpression openBra codeList closeBra
	;

logicalExpression: openPar logicalExpression[left] AND logicalExpression[right] closePar
	| openPar logicalExpression[left] OR logicalExpression[right] closePar
	| openPar logicalExpression[left] EQEQ logicalExpression[right] closePar
	| openPar logicalExpression[left] NOTEQ logicalExpression[right] closePar
	| openPar logicalExpression[left] GT logicalExpression[right] closePar
	| openPar logicalExpression[left] GTEQ logicalExpression[right] closePar
	| openPar logicalExpression[left] LT logicalExpression[right] closePar
	| openPar logicalExpression[left] LTEQ logicalExpression[right] closePar
	| openPar varName closePar
	| openPar instanceAttribute closePar
	| openPar dataValue closePar
	;


expression: expression[left] ADD expression[right]					{ $$ = AdditionExpressionGrammarAction($left, $right); }
	| expression[left] SUB expression[right]						{ $$ = SubtractionExpressionGrammarAction($left, $right); }
	| expression[left] MUL expression[right]						{ $$ = MultiplicationExpressionGrammarAction($left, $right); }
	| expression[left] DIV expression[right]						{ $$ = DivisionExpressionGrammarAction($left, $right); }
	| factor														{ $$ = FactorExpressionGrammarAction($1); }
	;

factor: openPar expression closePar									{ $$ = ExpressionFactorGrammarAction($2); }
	| constant														{ $$ = ConstantFactorGrammarAction($1); }
	;

constant: INTEGER													{ $$ = IntegerConstantGrammarAction($1); }
	;

boolVal: TRUEE
	| FALSEE
	;

openBra: OPEN_BRACKET
	;

closeBra: CLOSE_BRACKET
	;

openPar: OPEN_PARENTHESIS
	;

closePar: CLOSE_PARENTHESIS
	;

semiColon: SEMI_COLON
	;

comment: COMMENT
	;

methods: MAX
	| MIN
	| AVG
	| DELETE
	;

%%