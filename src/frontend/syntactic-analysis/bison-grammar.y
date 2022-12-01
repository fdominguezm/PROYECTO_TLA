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
	tProgram * program;

	tCredentialsSection * credentialsSection;
	tCredentialList * credentialList;
	tCredentialDefinition * credentialDefinition;

	tClassSection *classSection;
	tClassList *classList;
	tClassDeclaration *classDeclaration;
	tInstanceAtt * instanceAttribute;
	tClassMethod* classMethod;

	tAttrList * attrList;
	tAttrDeclaration * attrDeclaration;

	tVarDeclaration *varDeclaration;
	tVarEquals *varEquals;
	
	tDataType * dataType;
	tDataValue *dataValue;

	tCodeSection * codeSection;
	tCodeComponents *codeComponents;
	tCodeList *codeList;

	tIfStatement * ifStatement;
	tElseStatement * elseStatement;
	tWhileStatement *whileStatement;
	
	tParamList *paramList;

	tLogicalExpression *logicalExpression;
	// int expression;
	// int factor;
	// int constant;

	MethodType method;

	// Terminales.
	int token;
	char * stringToken;
	int integer;
	char * className;
	char * varName;
}

// IDs y tipos de los tokens terminales generados desde Flex.
%token <token> ADD
%token <token> SUB
%token <token> MUL
%token <token> DIV

%token <stringToken> EQ

%token <stringToken> EQEQ
%token <stringToken> GT
%token <stringToken> LT
%token <stringToken> GTEQ
%token <stringToken> LTEQ
%token <stringToken> NOTEQ

%token <stringToken> OPEN_PARENTHESIS
%token <stringToken> CLOSE_PARENTHESIS

%token <stringToken> OPEN_BRACKET
%token <stringToken> CLOSE_BRACKET
%token <stringToken> SEMI_COLON
%token <stringToken> DOT
%token <stringToken> COMMA
%token <stringToken> COLON

%token <stringToken> CLASS_SECTION 
%token <stringToken> CREDENTIALS_SECTION

%token <stringToken> NEW
%token <stringToken> RETURN

%token <stringToken> INTEGER
%token <stringToken> STRING
%token <stringToken> BOOLEAN
%token <token> INTEGER_VALUE
%token <stringToken> STRING_VALUE

%token <className> CAPITALIZED_NAME
%token <stringToken> ALPHANUMERIC_NAME

%token <stringToken> IF
%token <stringToken> ELSE
%token <stringToken> WHILE

%token <stringToken> AND
%token <stringToken> OR
%token <stringToken> TRUEE
%token <stringToken> FALSEE

%token <stringToken> MIN
%token <stringToken> MAX
%token <stringToken> AVG
%token <stringToken> DELETE

%token <stringToken> COMMENT

// Tipos de dato para los no-terminales generados desde Bison.
%type <program> program
// %type <expression> expression
// %type <factor> factor
// %type <constant> constant

%type <credentialsSection> credentialsSection
%type <credentialList> credentialList
%type <credentialDefinition> credentialDefinition

%type <classSection> classSection
%type <classList> classList
%type <classDeclaration> classDeclaration
%type <instanceAttribute> instanceAttribute
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
%type <method> method
%type <codeList> codeList
%type <attrList> attrList
%type <attrDeclaration> attrDeclaration



// Reglas de asociatividad y precedencia (de menor a mayor).
%left ADD SUB
%left MUL DIV
%left AND OR 
%left GTEQ LTEQ GT EQEQ NOTEQ LT

// El símbolo inicial de la gramatica.
%start program


%%

program: credentialsSection classSection codeSection															{ $$ = ProgramGrammarAction($1,$2,$3); }	
	;

credentialsSection: %empty	{$$ = NULL;}
	| CREDENTIALS_SECTION OPEN_BRACKET credentialList CLOSE_BRACKET { $$ = CredentialsSectionGrammarAction($3); }
	;

credentialList: credentialDefinition																					{ $$ = MultipleCredentialListGrammarAction($1, NULL); }
	| credentialDefinition credentialList																				{ $$ = MultipleCredentialListGrammarAction($1, $2); }

credentialDefinition: ALPHANUMERIC_NAME EQ dataValue SEMI_COLON						{ $$ = CredentialDefinitionGrammarAction($1, $3);}

classSection: CLASS_SECTION OPEN_BRACKET classList CLOSE_BRACKET							{ $$ = ClassListGrammarAction($3); }	 
	;

classList: classDeclaration																	{ $$ = ClassDeclarationGrammarAction($1); }
	| classDeclaration classList															{ $$ = MultipleClassDeclarationGrammarAction($1,$2);}									
	;

classDeclaration: CAPITALIZED_NAME OPEN_BRACKET attrList CLOSE_BRACKET								{ $$ = ClassAttrListGrammarAction($1,$3);}
	;


instanceAttribute: ALPHANUMERIC_NAME DOT ALPHANUMERIC_NAME													{ $$ = InstanceAttributeGrammarAction($1,$3);}
	;

classMethod: CAPITALIZED_NAME DOT method OPEN_PARENTHESIS ALPHANUMERIC_NAME CLOSE_PARENTHESIS				{ $$ = MethodsAndVarNameGrammarAction($1,$3,$5);}
	;

attrList: attrDeclaration																					{$$ = AttrDecGrammarAction($1);}
	| attrDeclaration attrList																				{$$ = MultipleAttrDecGrammarAction($1, $2);}
	;

attrDeclaration: dataType ALPHANUMERIC_NAME SEMI_COLON 														{$$ = ClassAttrDecGrammarAction($1, $2);}

varDeclaration: dataType ALPHANUMERIC_NAME SEMI_COLON 															{ $$ = DataTypeAndVarNameGrammarAction($1,$2);}
	| dataType ALPHANUMERIC_NAME varEquals SEMI_COLON															{ $$ = DataTypeVarNameAndVarEqualsGrammarAction($1,$2,$3);}
	| CAPITALIZED_NAME ALPHANUMERIC_NAME EQ NEW CAPITALIZED_NAME OPEN_PARENTHESIS paramList CLOSE_PARENTHESIS SEMI_COLON	{ $$ = VarNameParamListGrammarAction($1,$2,$7);}
	;

dataValue: TRUEE																			{ $$ = TrueGrammarAction(); }
	| FALSEE																				{ $$ = FalseGrammarAction(); }
	| STRING_VALUE																			{ $$ = StringValueGrammarAction($1); }
	| INTEGER_VALUE																				{ $$ = IntegerValueGrammarAction($1); }
	;

paramList: ALPHANUMERIC_NAME COLON ALPHANUMERIC_NAME										{ $$ = ParamListVarGrammarAction($1, $3);}
	| ALPHANUMERIC_NAME COLON ALPHANUMERIC_NAME COMMA paramList						{ $$ = MultipleParamListVarGrammarAction($1, $3, $5);}
	| ALPHANUMERIC_NAME COLON dataValue																		{ $$ = ParamListValueGrammarAction($1,$3); }
	| ALPHANUMERIC_NAME COLON dataValue COMMA paramList																{ $$ = MultipleParamListValueGrammarAction($1,$3,$5); }
	;
	
varEquals:  EQ dataValue 														{ $$ = VarEqDataValueGrammarAction($2); }
	| EQ instanceAttribute 														{ $$ = VarEqInstanceAttributeGrammarAction($2); }
	| EQ ALPHANUMERIC_NAME 																	{ $$ = VarEqVarNameGrammarAction($2); }
	| EQ classMethod 																{ $$ = VarEqClassMethodGrammarAction($2); }
	;

dataType: INTEGER 																			{ $$ = IntTypeGrammarAction($1); }
	| STRING 																				{ $$ = StrTypeGrammarAction($1); }
	| BOOLEAN																				{ $$ = BoolTypeGrammarAction($1); }
	;

codeSection: %empty {$$ = NULL; }
	| codeList																		{ $$ = CodeListGrammarAction($1); }
	;

codeList: codeComponents 																	{ $$ = CodeComponentsGrammarAction($1); }
	| codeComponents codeList																{ $$ = MultipleCodeComponentsGrammarAction($1,$2);}
	;

codeComponents: ifStatement 																{ $$ = IfGrammarAction($1); }
	| whileStatement 																		{ $$ = WhileGrammarAction($1); }
	| varDeclaration 																		{ $$ = CodeVarDeclarationGrammarAction($1); }
	| ALPHANUMERIC_NAME varEquals SEMI_COLON 												{ $$ = VarNameEqualsVarGrammarAction($1,$2);}
	| instanceAttribute varEquals SEMI_COLON												{ $$ = InstanceAttributeEqualGrammarAction($1,$2);}
	| classMethod SEMI_COLON																{ $$ = ClassMethodGrammarAction($1); }
	| COMMENT																				{ $$ = CommentCodeGrammarAction($1); }
	;

ifStatement: IF OPEN_PARENTHESIS logicalExpression CLOSE_PARENTHESIS OPEN_BRACKET codeList CLOSE_BRACKET elseStatement			{$$ = IfInitializedGrammarAction($3, $6, $8);}
	;
	
elseStatement: %empty 																		{ $$ = EmptyGrammarAction();}
	| ELSE ifStatement																		{ $$ = ElseIfGrammarAction($2); }
	| ELSE OPEN_BRACKET codeList CLOSE_BRACKET												{ $$ = ElseCodeListGrammarAction($3); }
	;

whileStatement: WHILE OPEN_PARENTHESIS logicalExpression CLOSE_PARENTHESIS OPEN_BRACKET codeList CLOSE_BRACKET					{ $$ = WhileInitializedGrammarAction($3,$6);}
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
	// |  expression 																			{ $$ = ExpressionLogicalExpressionGrammarAction($1); }
	|  classMethod																			{ $$ = ClassMethodLogicalExpressionGrammarAction($1); }
	;


// expression: expression[left] ADD expression[right]											{ $$ = AdditionExpressionGrammarAction($left, $right); }
// 	| expression[left] SUB expression[right]												{ $$ = SubtractionExpressionGrammarAction($left, $right); }
// 	| expression[left] MUL expression[right]												{ $$ = MultiplicationExpressionGrammarAction($left, $right); }
// 	| expression[left] DIV expression[right]												{ $$ = DivisionExpressionGrammarAction($left, $right); }
// 	| factor																				{ $$ = FactorExpressionGrammarAction($1); }
// 	;

// factor: OPEN_PARENTHESIS expression CLOSE_PARENTHESIS										{ $$ = ExpressionFactorGrammarAction($2); }
// 	| constant																				{ $$ = ConstantFactorGrammarAction($1); }
// 	;

// constant: INTEGER_VALUE																			{ $$ = IntegerConstantGrammarAction($1); }
// 	;

method: MAX																				{ $$ = MaxGrammarAction(); }
	| MIN																					{ $$ = MinGrammarAction(); }
	| AVG																					{ $$ = AvgGrammarAction(); }
	| DELETE																				{ $$ = DeleteGrammarAction(); }
	;

%%