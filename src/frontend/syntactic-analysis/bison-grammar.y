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
	int instanceAttribute;
	int classMethod;

	int varList;
	int varDeclaration;
	int varEquals;
	
	int dataType;
	int dataValue;

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

	int comment;

	tMethods * methods;

	// Terminales.
	int token;
	int integer;
	char * className;
	char * varName;
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
%token <integer> INTEGER_VALUE
%token <token> STRING_VALUE

%token <className> CAPITALIZED_NAME
%token <varName> ALPHANUMERIC_NAME

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
%type <instanceAttribute> instanceAttribute
%type <varList> varList
%type <paramList> paramList
%type <varDeclaration> varDeclaration
%type <varEquals> varEquals
%type <dataType> dataType
%type <codeSection> codeSection
%type <codeComponents> codeComponents
%type <ifStatement> ifStatement
%type <elseStatement> elseStatement
%type <whileStatement> whileStatement
%type <logicalExpression> logicalExpression
%type <classMethod> classMethod
%type <dataValue> dataValue
%type <methods> methods


// Reglas de asociatividad y precedencia (de menor a mayor).
%left ADD SUB
%left MUL DIV

// El símbolo inicial de la gramatica.
%start program


%%

program: classSection codeSection															{ $$ = ProgramGrammarAction($1,$2); }		
	;

classSection: CLASS_SECTION OPEN_BRACKET classList CLOSE_BRACKET							{ $$ = ClassListGrammarAction($3); }	 
	;

classList: classDeclaration																	{ $$ = ClassDeclarationGrammarAction($1); }
	| classDeclaration classList															{ $$ = MultipleClassDeclarationGrammarAction($1,$2);}									
	;

classDeclaration: CAPITALIZED_NAME OPEN_BRACKET varList CLOSE_BRACKET								{ $$ = VarListGrammarAction($1,$3);}
	;


instanceAttribute: ALPHANUMERIC_NAME DOT ALPHANUMERIC_NAME														{ $$ = InstanceAttributeGrammarAction($1,$3);}
	;

classMethod: CAPITALIZED_NAME DOT methods OPEN_PARENTHESIS ALPHANUMERIC_NAME CLOSE_PARENTHESIS				{ $$ = MethodsAndVarNameGrammarAction($1,$3,$5);}
	;

varList: varDeclaration 																	{ $$ = VarDeclarationGrammarAction($1); }
	| varDeclaration varList																{ $$ = MultipleVarDeclarationGrammarAction($1,$2);}
	;

varDeclaration: dataType ALPHANUMERIC_NAME SEMI_COLON 															{ $$ = DataTypeAndVarNameGrammarAction($1,$2);}
	| dataType ALPHANUMERIC_NAME varEquals SEMI_COLON															{ $$ = DataTypeVarNameAndVarEqualsGrammarAction($1,$2,$3);}
	| CAPITALIZED_NAME ALPHANUMERIC_NAME EQ NEW CAPITALIZED_NAME OPEN_PARENTHESIS paramList CLOSE_PARENTHESIS SEMI_COLON	{ $$ = VarNameParamListGrammarAction($1,$2,$7);}
	;

dataValue: TRUEE																			{ $$ = TrueGrammarAction(); }
	| FALSEE																				{ $$ = FalseGrammarAction(); }
	| STRING_VALUE																			{ $$ = StringValueGrammarAction($1); }
	| INTEGER_VALUE																			{ $$ = IntegerValueGrammarAction($1); }
	;

paramList: dataValue																		{ $$ = ParamListGrammarAction($1); }
	| dataValue COMMA paramList																{ $$ = MultipleParamListGrammarAction($1,$3); }
	;
	
varEquals:  EQ dataValue 														{ $$ = VarEqDataValueGrammarAction($2); }
	| EQ instanceAttribute 														{ $$ = VarEqInstanceAttributeGrammarAction($2); }
	| EQ ALPHANUMERIC_NAME 																	{ $$ = VarEqVarNameGrammarAction($2); }
	| EQ classMethod 																{ $$ = VarEqClassMethodGrammarAction($2); }
	;

dataType: INTEGER 																			{ $$ = TypeGrammarAction($1); }
	| STRING 																				{ $$ = TypeGrammarAction($1); }
	| BOOLEAN																				{ $$ = TypeGrammarAction($1); }
	;

codeSection: codeList																		{ $$ = CodeListGrammarAction($1); }
	;

codeList: codeComponents 																	{ $$ = CodeComponentsGrammarAction($1); }
	| codeComponents codeList																{ $$ = MultipleCodeComponentsGrammarAction($1,$2);}
	;

codeComponents: ifStatement 																{ $$ = IfGrammarAction($1); }
	| whileStatement 																		{ $$ = WhileGrammarAction($1); }
	| varDeclaration 																		{ $$ = CodeVarDeclarationGrammarAction($1); }
	| ALPHANUMERIC_NAME varEquals SEMI_COLON 												{ $$ = VarNameEqualsVarGrammarAction($1);}
	| instanceAttribute varEquals SEMI_COLON												{ $$ = InstanceAttributeEqualGrammarAction($1,$2);}
	| classMethod SEMI_COLON																{ $$ = ClassMethodGrammarAction($1); }
	| comment																				{ $$ = CommentCodeGrammarAction($1); }
	;

ifStatement: IF logicalExpression OPEN_BRACKET codeList CLOSE_BRACKET elseStatement			{$$ = IfInitializedGrammarAction($2, $4, $5);}
	;

elseStatement: %empty 																		{ $$ = EmptyGrammarAction();}
	| ELSE ifStatement																		{ $$ = ElseIfGrammarAction($2); }
	| ELSE OPEN_BRACKET codeList CLOSE_BRACKET												{ $$ = ElseCodeListGrammarAction($3); }
	;

whileStatement: WHILE logicalExpression OPEN_BRACKET codeList CLOSE_BRACKET					{ $$ = WhileInitializedGrammarAction($2,$4);}
	;

logicalExpression:  logicalExpression[left] AND logicalExpression[right] 					{ $$ = MultipleLogicalExpressionGrammarAction($left, $2,$right); }
	|  logicalExpression[left] OR logicalExpression[right] 									{ $$ = MultipleLogicalExpressionGrammarAction($left, $2,$right); }
	|  logicalExpression[left] EQEQ logicalExpression[right] 								{ $$ = MultipleLogicalExpressionGrammarAction($left, $2,$right); }
	|  logicalExpression[left] NOTEQ logicalExpression[right] 								{ $$ = MultipleLogicalExpressionGrammarAction($left, $2,$right); }
	|  logicalExpression[left] GT logicalExpression[right] 									{ $$ = MultipleLogicalExpressionGrammarAction($left, $2,$right); }
	|  logicalExpression[left] GTEQ logicalExpression[right] 								{ $$ = MultipleLogicalExpressionGrammarAction($left, $2,$right); }
	|  logicalExpression[left] LT logicalExpression[right] 									{ $$ = MultipleLogicalExpressionGrammarAction($left, $2,$right); }
	|  logicalExpression[left] LTEQ logicalExpression[right] 								{ $$ = MultipleLogicalExpressionGrammarAction($left, $2,$right); }
	|  ALPHANUMERIC_NAME 																	{ $$ = VarNameLogicalExpressionGrammarAction($1); }
	|  instanceAttribute 																	{ $$ = InstanceAttLogicalExpressionGrammarAction($1); }
	|  dataValue 																			{ $$ = DataValueLogicalExpressionGrammarAction($1); }
	|  expression 																			{ $$ = ExpressionLogicalExpressionGrammarAction($1); }
	;


expression: expression[left] ADD expression[right]											{ $$ = AdditionExpressionGrammarAction($left, $right); }
	| expression[left] SUB expression[right]												{ $$ = SubtractionExpressionGrammarAction($left, $right); }
	| expression[left] MUL expression[right]												{ $$ = MultiplicationExpressionGrammarAction($left, $right); }
	| expression[left] DIV expression[right]												{ $$ = DivisionExpressionGrammarAction($left, $right); }
	| factor																				{ $$ = FactorExpressionGrammarAction($1); }
	;

factor: OPEN_PARENTHESIS expression CLOSE_PARENTHESIS										{ $$ = ExpressionFactorGrammarAction($2); }
	| constant																				{ $$ = ConstantFactorGrammarAction($1); }
	;

constant: INTEGER																			{ $$ = IntegerConstantGrammarAction($1); }
	;

comment: COMMENT																			{ $$ = CommentGrammarAction($1); }
	;

methods: MAX																				{ $$ = MaxGrammarAction(); }
	| MIN																					{ $$ = MinGrammarAction(); }
	| AVG																					{ $$ = AvgGrammarAction(); }
	| DELETE																				{ $$ = DeleteGrammarAction(); }
	;

%%