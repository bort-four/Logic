/* logic.y */

%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <ctype.h>
	#include "Parser.h"
	#include "Logic.h"
	int  yylex(Source* sourcePtr);
	void yyerror(Source* sourcePtr, ParserNode* parseTreePtr,
				Vector* errVectPtr, char const *msg);
	
	#define addErrorOnBegin(msg, loc)                                          \
	{                                                                          \
		Error error = createParserError((msg), sourcePtr,                      \
							(loc).first_line, (loc).first_column);             \
		addBack(*errVectPtr, Error, error);                                    \
	}

	#define addErrorOnEnd(msg, loc)                                            \
	{                                                                          \
		Error error = createParserError((msg), sourcePtr,                      \
							(loc).last_line, (loc).last_column);               \
		addBack(*errVectPtr, Error, error);                                    \
	}
	
	#define setNullNode(ndPtr, loc)                                            \
	{                                                                          \
		(ndPtr)                                                                \
			= createNode(ND_NULL, NULL, (loc).first_line, (loc).first_column); \
	}
	
%}

%param { Source* sourcePtr }
%parse-param { ParserNode* parseTreePtr }
%parse-param { Vector* errVectPtr }
%define api.value.type { ParserNode* }

%token NAME
%token DECLARATIONS_TITLE	FACTS_TITLE		RESTRICTIONS_TITLE
%token SINGLE_FACT	SINGLE_AXIOM	SINGLE_RESTRICTION	SINGLE_DECLARATION
%token ALL EXT
%token REAL INTEGER

%precedence QUANT
%token 	'='
%left 	ARROW		/* ->	*/
%left 	ARROW_IMP	/* =>	*/
%left 	ARROW_EQ	/* <=>	*/
%left 	LES_OR_EQ	/* <=	*/
%left 	MORE_OR_EQ	/* >=	*/
%left 	'|' '&'
%left 	'+' '-'
%left 	'*' '/' '%'
%right	'^'
%right 	'(' ')'
%precedence NEG
%precedence BRAC
%precedence FUNC
%precedence UNAR_MINUS

%glr-parser
%expect-rr 4


%%

input:
	program
	| single_decl
	| single_fact
	| single_axiom
	| single_restr
	| query
;


query:
	name '(' query_param_list ')' query_result ';'
	{
		setType(parseTreePtr, ND_QUERY);
		addParamToNode($1, $3);
		addNeighborToNode($1, $5);
		addParamToNode(parseTreePtr, $1);
	}
	| name error
	{
		setType(parseTreePtr, ND_QUERY);
		setNullNode($$, @2);
		addErrorOnBegin("expected \'(\' token after name", @2);
		freeNode($1);
	}
	| name '(' query_param_list ')' query_result error
	{
		setType(parseTreePtr, ND_QUERY);
		addParamToNode($1, $3);
		addNeighborToNode($1, $5);
		addParamToNode(parseTreePtr, $1);
		
		addErrorOnEnd("expected \';\' token after query", @4);
	}
;


query_param_list:
	query_param
	| query_param_list ',' query_param	{ $$ = addNeighborToNode($1, $3); }
;

query_param:
	%empty	{ $$ = createNode(ND_NAME, "", @0.first_line, @0.first_column); }
	| constant
;

query_result:
	%empty	{ $$ = createNode(ND_NAME, "", @0.first_line, @0.first_column); }
	| '=' constant	{ $$ = $2; }
;


single_decl:
	SINGLE_DECLARATION declaration ';'
	{
		setType(parseTreePtr, ND_S_DECL);
		addParamToNode(parseTreePtr, $2);
	}
	| SINGLE_DECLARATION error	{ addErrorOnBegin("invalid declaration", @2); }
	| SINGLE_DECLARATION declaration error
	{ addErrorOnEnd("expected ';' after declaration", @2); }

single_fact:
	SINGLE_FACT fact ';'
	{
		setType(parseTreePtr, ND_S_FACT);
		addParamToNode(parseTreePtr, $2);
	}
	| SINGLE_FACT error	{ addErrorOnBegin("invalid fact", @2); }
	| SINGLE_FACT fact error
	{ addErrorOnEnd("expected ';' after fact", @2); }

single_axiom:
	  SINGLE_AXIOM axiom ';'
	{
		setType(parseTreePtr, ND_S_AXIOM);
		addParamToNode(parseTreePtr, $2);
	}
	| SINGLE_AXIOM error	{ addErrorOnBegin("invalid axiom", @2); }
	| SINGLE_AXIOM axiom error
	{ addErrorOnEnd("expected ';' after axiom", @2); }

single_restr:
	  SINGLE_RESTRICTION  ';'
	{
		setType(parseTreePtr, ND_S_RESTR);
		addParamToNode(parseTreePtr, $2);
	}
	| SINGLE_RESTRICTION error	{ addErrorOnBegin("invalid restriction", @2); }
	| SINGLE_RESTRICTION restriction error
	{ addErrorOnEnd("expected ';' after restriction", @2); }
;


program:
	declarations facts restrictions
	{
		setType(parseTreePtr, ND_PROG);
		addParamToNode(parseTreePtr, $1);
		addParamToNode(parseTreePtr, $2);
		addParamToNode(parseTreePtr, $3);
	}
	| error
	{
		setType(parseTreePtr, ND_PROG);
		addErrorOnBegin("Unknown programm segment. "
						"Start with one of follow keywords:\n"
						"    DECLARATIONS\n"
						"    FACTS\n"
						"    RESTRICTIONS\n", @1);
	}
;



/* === Declarations === */

declarations:
	%empty	{ $$ = createNode(ND_DECLS, NULL, @0.first_line, @0.first_column); }
	| DECLARATIONS_TITLE decls_list
	{
		$$ = addParamToNode(createNode(ND_DECLS, NULL,
							@1.first_line, @1.first_column), $2);
	}
;

decls_list:
	%empty							{ $$ = NULL; }
	| decls_list ';'
	| decls_list declaration		{ $$ = addNeighborToNode($1, $2); }
;


declaration:
	name ':' '(' name_list ')' ARROW name ';'
	{
		$1->type = ND_FUNC_DEC;
		$$ = $1;
		addParamToNode($$, $4);
		addParamToNode($$, $7);
	}
	| name ':' '(' name_list ')' ARROW name error
	{
		$1->type = ND_FUNC_DEC;
		$$ = $1;
		addParamToNode($$, $4);
		addParamToNode($$, $7);
		
		addErrorOnEnd("expexted \';\' after declaration", @7);
	}
	| name error ';'
	{
		addErrorOnBegin("expexted \':\' after name", @2);
		setNullNode($$, @2);
		freeNode($1);
	}
	| name ':' error ';'
	{
		addErrorOnBegin("expexted \'(\' after \':\' token", @3);
		setNullNode($$, @3);
		freeNode($1);
	}
	| name ':' '(' name_list error ';'
	{
		addErrorOnBegin("expexted \')\' after list of types", @5);
		setNullNode($$, @5);
		freeNode($1); freeNode($4);
	}
	| name ':' '(' name_list ')' error ';'
	{
		addErrorOnBegin("expexted \'->\' after list of types", @6);
		setNullNode($$, @6);
		freeNode($1); freeNode($4);
	}
;

name_list:
	name
	| name_list ',' name	{ $$ = addNeighborToNode($1, $3); }
	| name_list error
	{
		addErrorOnBegin("expected \',\' token after name", @2);
		$$ = $1;
	}
;

name:
	NAME
	| error { addErrorOnBegin("invalid name", @1); setNullNode($$, @1); }


/* === Facts === */

facts:
	%empty	{ $$ = createNode(ND_FACTS, NULL, @0.first_line, @0.first_column); }
	| FACTS_TITLE fact_list
	{
		$$ = addParamToNode(createNode(ND_FACTS, NULL,
							@1.first_line, @1.first_column), $2);
	}
;

fact_list:
	%empty							{ $$ = NULL; }
	| fact_list ';'
	| fact_list fact_or_axiom		{ $$ = addNeighborToNode($1, $2); }
;


fact_or_axiom:
	fact
	| axiom
;


fact: positive_fact | negative_fact | function_fact;

positive_fact:
	name '(' const_list ')' ';'
	{
		$$ = addParamToNode(setType($1, ND_PRED), $3);
	}
	| name '(' const_list ')' error
	{
		$$ = addParamToNode(setType($1, ND_PRED), $3);
		addErrorOnEnd("expexted \';\' after fact expression", @4);
	}
	| name error
	{
		addErrorOnBegin("expexted \'(\' after name", @2);
		setNullNode($$, @2);
		freeNode($1);
	}
	| name '(' const_list error ';'
	{
		addErrorOnBegin("expexted \')\' after constants list", @4);
		setNullNode($$, @4);
		freeNode($1); freeNode($3);
	}
;


negative_fact:
	'!' name '(' const_list ')' ';'
	{
		$$ = createNode(ND_NOT, NULL, @1.first_line, @1.first_column);
		addParamToNode($2, $4);
		addParamToNode($$, setType($2, ND_PRED));
	}
	| '!' name '(' const_list ')' error
	{
		$$ = createNode(ND_NOT, NULL, @1.first_line, @1.first_column);
		addParamToNode($2, $4);
		addParamToNode($$, setType($2, ND_PRED));
		
		addErrorOnEnd("expexted \';\' after fact expression", @5);
	}
	| '!' name error
	{
		addErrorOnBegin("expexted \'(\' after name", @2);
		setNullNode($$, @3);
		freeNode($2);
	}
	| '!' name '(' const_list error ';'
	{
		addErrorOnBegin("expexted \')\' after constants list", @5);
		setNullNode($$, @5);
		freeNode($2); freeNode($4);
	}
;

function_fact:
	name '(' const_list ')' '=' constant ';'
	{
		$$ = createNode(ND_EQ, NULL, @1.first_line, @1.first_column);
		addParamToNode($1, $3);
		addParamToNode($$, setType($1, ND_FUNC));
		addParamToNode($$, $6);
	}
	| name '(' const_list ')' '=' constant error
	{
		$$ = createNode(ND_EQ, NULL, @1.first_line, @1.first_column);
		addParamToNode($1, $3);
		addParamToNode($$, setType($1, ND_FUNC));
		addParamToNode($$, $6);
		
		addErrorOnEnd("expexted \';\' after fact expression", @6);
	}
;


const_list:
	constant
	| const_list ',' constant	{ $$ = addNeighborToNode($1, $3); }
	| const_list error
	{
		addErrorOnEnd("expected \',\' token after constant", @1);
		$$ = $1;
	}
;

constant:
	NAME 		{ $$ = setType($1, ND_NAMED_CONST); }
	| INTEGER
	| REAL
	| error
	{
		addErrorOnEnd("invalid constant", @0);
		setNullNode($$, @1);
	}
;


/* === Axioms === */


axiom:
	axiom_vars premise ARROW_IMP result ';'
	{
		$$ = addParamToNode(createNode(ND_AXIOM, NULL,
							@1.first_line, @1.first_column), $1);
		addParamToNode($$, $2);
		addParamToNode($$, $4);
	}
	| axiom_vars premise ARROW_IMP result error
	{
		$$ = addParamToNode(createNode(ND_AXIOM, NULL,
							@1.first_line, @1.first_column), $1);
		addParamToNode($$, $2);
		addParamToNode($$, $4);
		
		addErrorOnEnd("expexted \';\' after axiom", @1);
	}
;

axiom_vars:
	ALL var_block_list
	{
		$$ = addParamToNode(createNode(ND_VARS, NULL,
										@1.first_line, @1.first_column), $2);
	}
	| axiom_vars ALL var_block_list	{ $$ = addParamToNode($1, $3); }
;


var_block_list:
	var_block
	| var_block_list ',' var_block
	{
		$$ = addNeighborToNode($1, $3);
	}
;

var_block:
	name_list ':' name
	{
		ParserNode* pnVarPtr = $1;
		for (; pnVarPtr != NULL; pnVarPtr = pnVarPtr->next)
		{
			pnVarPtr->type = ND_VAR;
			addParamToNode(pnVarPtr,
				createNode(ND_NAME, $3->name, @3.first_line, @3.first_column));
		}
		
		$$ = $1;
		freeNode($3);
	}
;



premise:
	conjunct
	{
		$$ = addParamToNode(createNode(ND_PREM, NULL,
							@1.first_line, @1.first_column), $1);
	}
	| premise '&' conjunct	{ $$ = addParamToNode($1, $3); }
	//~ | error				{ addErrorOnBegin("invalid conjunct", @1); $$ = NULL; }
	//~ | premise '&' error	{ addErrorOnBegin("invalid conjunct", @3); }
;

result:
	res_conjunct
	{
		$$ = addParamToNode(createNode(ND_RES, NULL,
										@1.first_line, @1.first_column), $1);
	}
	| result '&' res_conjunct	{ $$ = addParamToNode($1, $3); }
	//~ | error				{ addErrorOnBegin("invalid conjunct", @1); $$ = NULL; }
	//~ | result '&' error	{ addErrorOnBegin("invalid conjunct", @3); }
;


conjunct:
		  predicate
	| '!' predicate
	{
		$$ = addParamToNode(createNode(ND_NOT, NULL,
										@1.first_line, @1.first_column), $2);
	}
	| term '=' term
	{
		$$ = createNode(ND_EQ, NULL, @1.first_line, @1.first_column);
		addParamToNode($$, $1);
		addParamToNode($$, $3);
	}
;

res_conjunct:
	  predicate
	| function '=' term
	{
		$$ = createNode(ND_EQ, NULL, @1.first_line, @1.first_column);
		addParamToNode($$, $1);
		addParamToNode($$, $3);
	}
;


predicate:
	function	{ $$ = setType($1, ND_PRED); }
	| term '<' term
	{
		$$ = createNode(ND_PRED, (char*)ARITH_RELATION_NAMES[AR_LESS],
						@1.first_line, @1.first_column);
		addParamToNode($$, $1);
		addParamToNode($$, $3);
	}
	| term '>' term
	{
		$$ = createNode(ND_PRED, (char*)ARITH_RELATION_NAMES[AR_MORE],
						@1.first_line, @1.first_column);
		addParamToNode($$, $1);
		addParamToNode($$, $3);
	}
	| term LES_OR_EQ term
	{
		$$ = createNode(ND_PRED, (char*)ARITH_RELATION_NAMES[AR_LESS_EQ],
						@1.first_line, @1.first_column);
		addParamToNode($$, $1);
		addParamToNode($$, $3);
	}
	| term MORE_OR_EQ term
	{
		$$ = createNode(ND_PRED, (char*)ARITH_RELATION_NAMES[AR_MORE_EQ],
						@1.first_line, @1.first_column);
		addParamToNode($$, $1);
		addParamToNode($$, $3);
	}
	| error
	{
		addErrorOnBegin("invalid predicate expression", @1);
		setNullNode($$, @1);
	}
;

function:
	name '(' term_list ')'	{ $$ = addParamToNode(setType($1, ND_FUNC), $3); }
	| name '(' term_list error
	{
		addErrorOnBegin("expexted \')\' after parametrs", @4);
		setNullNode($$, @4);
		freeNode($1); freeNode($3);
	}
;

term_list:
	term
	| term_list ',' term	{ $$ = addNeighborToNode($1, $3); }
;


term:
	constant
	| function
	| term '+' term
	{
		$$ = createNode(ND_FUNC, (char*)ARITH_FUNCTION_NAMES[AF_PLUS],
						@1.first_line, @1.first_column);
		addParamToNode($$, $1);
		addParamToNode($$, $3);
	}
	| term '*' term
	{
		$$ = createNode(ND_FUNC, (char*)ARITH_FUNCTION_NAMES[AF_MULT],
						@1.first_line, @1.first_column);
		addParamToNode($$, $1);
		addParamToNode($$, $3);
	}
	| term '-' term
	{
		$$ = createNode(ND_FUNC, (char*)ARITH_FUNCTION_NAMES[AF_MINUS],
						@1.first_line, @1.first_column);
		addParamToNode($$, $1);
		addParamToNode($$, $3);
	}
	| term '/' term
	{
		$$ = createNode(ND_FUNC, (char*)ARITH_FUNCTION_NAMES[AF_DIV],
						@1.first_line, @1.first_column);
		addParamToNode($$, $1);
		addParamToNode($$, $3);
	}
	| term '^' term
	{
		$$ = createNode(ND_FUNC, (char*)ARITH_FUNCTION_NAMES[AF_POW],
						@1.first_line, @1.first_column);
		addParamToNode($$, $1);
		addParamToNode($$, $3);
	}
	| term '%' term
	{
		$$ = createNode(ND_FUNC, (char*)ARITH_FUNCTION_NAMES[AF_MOD],
						@1.first_line, @1.first_column);
		addParamToNode($$, $1);
		addParamToNode($$, $3);
	}
	| '-' term	%prec UNAR_MINUS
	{
		$$ = addParamToNode(createNode(ND_FUNC, "-1",
										@1.first_line, @1.first_column), $2);
	}
	| '(' term ')'	{ $$ = $2; }
	| '(' term error
	{
		setNullNode($$, @3);
		addErrorOnBegin("expected \')\' token", @3);
		freeNode($2);
	}
;



all_quant:
	ALL var_block_list
	{
		ParserNode* pnVarPtr = $2;
		ParserNode* pnQuanPtr = $$
			= createNode(ND_ALL, NULL, @1.first_line, @1.first_column);
		addParamToNode(pnQuanPtr, pnVarPtr);
		pnVarPtr = pnVarPtr->next;
		pnQuanPtr->params->next = NULL;
		
		for (; pnVarPtr != NULL; )
		{
			addParamToNode(pnQuanPtr,
					createNode(ND_ALL, NULL, @1.first_line, @1.first_column));
			pnQuanPtr = pnQuanPtr->params->next;
			addParamToNode(pnQuanPtr, pnVarPtr);
			pnVarPtr = pnVarPtr->next;
			pnQuanPtr->params->next = NULL;
		}
	}
;


ext_quant:
	EXT var_block_list
	{
		ParserNode* pnVarPtr = $2;
		ParserNode* pnQuanPtr = $$
			= createNode(ND_EXT, NULL, @1.first_line, @1.first_column);
		addParamToNode(pnQuanPtr, pnVarPtr);
		pnVarPtr = pnVarPtr->next;
		pnQuanPtr->params->next = NULL;
		
		for (; pnVarPtr != NULL; )
		{
			addParamToNode(pnQuanPtr,
					createNode(ND_EXT, NULL, @1.first_line, @1.first_column));
			pnQuanPtr = pnQuanPtr->params->next;
			addParamToNode(pnQuanPtr, pnVarPtr);
			pnVarPtr = pnVarPtr->next;
			pnQuanPtr->params->next = NULL;
		}
	}
;



/* === Restrictions === */

restrictions:
	%empty
	{
		$$ = createNode(ND_RESTRS, NULL, @0.first_line, @0.first_column);
	}
	| RESTRICTIONS_TITLE restr_list
	{
		$$ = addParamToNode(createNode(ND_RESTRS, NULL,
							@1.first_line, @1.first_column), $2);
	}
;


restr_list:
	%empty							{ $$ = NULL; }
	| restr_list ';'
	| restr_list restriction ';'	{ $$ = addNeighborToNode($1, $2); }
	| restr_list restriction error
	{
		$$ = addNeighborToNode($1, $2);
		addErrorOnEnd("expected ';' after restriction", @2);
	}
;

restriction:
	formula
;

formula:
	predicate
	| '!' formula					%prec NEG
	{
		$$ = addParamToNode(createNode(ND_NOT, NULL,
							@1.first_line, @1.first_column), $2);
	}
	| term '=' term
	{
		$$ = createNode(ND_EQ, NULL, @1.first_line, @1.first_column);
		addParamToNode($$, $1);
		addParamToNode($$, $3);
	}
	| formula ARROW_EQ formula
	{
		$$ = createNode(ND_LEQ, NULL, @1.first_line, @1.first_column);
		addParamToNode($$, $1);
		addParamToNode($$, $3);
	}
	| formula '|' formula
	{
		$$ = createNode(ND_OR, NULL, @1.first_line, @1.first_column);
		addParamToNode($$, $1);
		addParamToNode($$, $3);
	}
	| formula '&' formula
	{
		$$ = createNode(ND_AND, NULL, @1.first_line, @1.first_column);
		addParamToNode($$, $1);
		addParamToNode($$, $3);
	}
	| formula ARROW_IMP formula
	{
		$$ = createNode(ND_IMP, NULL, @1.first_line, @1.first_column);
		addParamToNode($$, $1);
		addParamToNode($$, $3);
	}
	| all_quant formula	%prec QUANT
	{
		ParserNode* pnQuanPtr = $$ = $1;
		for (; pnQuanPtr->params->next != NULL;
			pnQuanPtr = pnQuanPtr->params->next);
		addParamToNode(pnQuanPtr, $2);
	}
	| ext_quant formula	%prec QUANT
	{
		ParserNode* pnQuanPtr = $$ = $1;
		for (; pnQuanPtr->params->next != NULL;
			pnQuanPtr = pnQuanPtr->params->next);
		addParamToNode(pnQuanPtr, $2);
	}
	| '(' formula ')'	{ $$ = $2; }
;


%%



void yyerror(Source* sourcePtr, ParserNode* programPtr, Vector* errVectPtr,
			char const *msg)
{
	/* Empty */
}


/* LEXER */


typedef struct {
	char* word;
	int code;
} Keyword;

static const Keyword keywords_g[] = {
	{"DECLARATIONS",	DECLARATIONS_TITLE},
	{"FACTS", 			FACTS_TITLE},
	{"RESTRICTIONS",	RESTRICTIONS_TITLE},
	{"All",				ALL},
	{"Ext", 			EXT},
	{"declaration", 	SINGLE_DECLARATION},
	{"fact", 			SINGLE_FACT},
	{"axiom", 			SINGLE_AXIOM},
	{"restriction", 	SINGLE_RESTRICTION},
	//~ {"abs",				TOKEN_ABS},
	//~ {"max",				TOKEN_MAX},
	//~ {"min",				TOKEN_MIN},
	//~ {"sin",				SIN},
	//~ {"cos",				COS},
	//~ {"tan",				TAN},
	//~ {"asin",			ASIN},
	//~ {"acos",			ACOS},
	//~ {"atan",			ATAN},
	//~ {"log",				LOG}
};


int getKeywordCode(char word[])
{
	size_t wordCt = sizeof(keywords_g) / sizeof(Keyword);
	size_t wordNum;
	
	for (wordNum = 0; wordNum < wordCt; wordNum++)
		if (strcmp(word, keywords_g[wordNum].word) == 0)
			return keywords_g[wordNum].code;
	
	return 0;
}


const size_t maxStrLen_g = 256;
size_t strLen_g = 0;
char* str_g = NULL;

//~ #define _MAX(x, y) (x < y) ? (y) : (x)
//~ #define _MIN(x, y) (x < y) ? (x) : (y)


int yylex(Source* sourcePtr)
{
	if (str_g == NULL)
	{
		strLen_g = 10;
		str_g = (char*)malloc(strLen_g * sizeof(char));
	}
	
	yylval = NULL;
	int ch = getChar(sourcePtr);

	/* ignore spaces and comments */
	while (!isEmpty(sourcePtr) && (isspace(ch) || ch == '#'))
	{
		while (!isEmpty(sourcePtr) && isspace(ch))
		{
			if (ch == '\n')
			{
				yylloc.last_line++;
				yylloc.last_column = 1;
			}
			else
				yylloc.last_column++;
				
			ch = getChar(sourcePtr);
		}
		
		if (ch == '#')
			while (!isEmpty(sourcePtr) && (ch = getChar(sourcePtr)) != '\n')
				yylloc.last_column++;
	}
	
	if (isEmpty(sourcePtr)) return 0;
	
	yylloc.first_line = yylloc.last_line;
	yylloc.first_column = yylloc.last_column;
	
	/* get cpecial character */
	if (ch == '-')	/* -> */
	{
		if (getChar(sourcePtr) == '>') return yylloc.last_column += 2, ARROW;
		else comeBack(sourcePtr);
	}
	if (ch == '=')	/* => */
	{
		if (getChar(sourcePtr) == '>')
			return yylloc.last_column += 2, ARROW_IMP;
		else comeBack(sourcePtr);
	}
	if (ch == '<')	/* <=> */
	{
		int ch1 = getChar(sourcePtr);
		int ch2 = getChar(sourcePtr);
		
		if (ch1 == '=' && ch2 == '>') return yylloc.last_column += 3, ARROW_EQ;
		else { comeBack(sourcePtr); comeBack(sourcePtr); }
	}
	if (ch == '<')	/* <= */
	{
		if (getChar(sourcePtr) == '=')
			return yylloc.last_column += 2, LES_OR_EQ;
		else comeBack(sourcePtr);
	}
	if (ch == '>')	/* <= */
	{
		if (getChar(sourcePtr) == '=')
			return yylloc.last_column += 2, MORE_OR_EQ;
		else comeBack(sourcePtr);
	}
	
	/* get number */
	if (ch == '-' || ch == '.' || isdigit(ch))
	{
		size_t pos = 0;
		Boolean hasPoint = false;
		
		while (isdigit(ch) || (ch == '.' && !hasPoint)
			|| (ch == '-' && pos == 0))
		{
			hasPoint |= (ch == '.');
			
			/* If buffer is full, make it bigger. */
			if (pos >= (ssize_t)strLen_g - 1)
			{
				strLen_g = _MIN(strLen_g + 10, maxStrLen_g);
				str_g = (char*) realloc(str_g, strLen_g);
			}

			if (pos < maxStrLen_g)
			{
				/* Add this character to the buffer. */
				str_g[pos++] = ch;
				ch = getChar(sourcePtr);
			}
		}

		comeBack(sourcePtr);

		if (pos == 1 && str_g[0] == '-')
		{
			ch = '-';
		}
		else
		{
			str_g[_MIN(pos, maxStrLen_g - 1)] = '\0';
			yylloc.last_column += pos;
			
			if (hasPoint)
			{
				yylval = createNode(ND_REAL, str_g,
					yylloc.first_line, yylloc.first_column);
				return REAL;
			}
			else
			{
				yylval = createNode(ND_INTEGER, str_g,
					yylloc.first_line, yylloc.first_column);
				return INTEGER;
			}
		}
	}

	/* get name or keyword */
	if (isalpha(ch) || ch == '_')
	{
		size_t pos = 0;
		
		while (isalnum(ch) || ch == '_')
		{
			/* If buffer is full, make it bigger. */
			if (pos >= (ssize_t)strLen_g - 1)
			{
				strLen_g = _MIN(strLen_g + 10, maxStrLen_g);
				str_g = (char*) realloc(str_g, strLen_g);
			}

			/* Add this character to the buffer. */
			if (pos < maxStrLen_g)
			{
				/* Add this character to the buffer. */
				str_g[pos++] = ch;
				ch = getChar(sourcePtr);
			}
		}

		comeBack(sourcePtr);
		str_g[_MIN(pos, maxStrLen_g - 1)] = '\0';
		yylloc.last_column += pos;
		
		/* check for keywords */
		int keywordCode = getKeywordCode(str_g);

		if (keywordCode > 0)
		{
			return keywordCode;
		}
		else
		{
			yylval = createNode(ND_NAME, str_g,
				yylloc.first_line, yylloc.first_column);
			return NAME;
		}
    }
	
	yylloc.last_column++;
	return ch;
}
