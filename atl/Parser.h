/* Parser.h */

#ifndef PARSER_NODE_HEADER
#define PARSER_NODE_HEADER

#include "Logic.h"
#include "Model.h"


/* === additional types === */

typedef enum {
	ND_PROG, 		ND_DECLS,	ND_FACTS,	ND_RESTRS, 	ND_FUNC_DEC,ND_VAR,
	ND_NAMED_CONST,	ND_PRED, 	ND_FUNC,	ND_AXIOM,	ND_CONJ,	ND_RES_CONJ,
	ND_ALL,			ND_EXT,		ND_AND,		ND_OR,		ND_IMP, 	ND_EQ,
	ND_LEQ,			ND_NOT,		ND_NAME,	ND_VARS,	ND_PREM,	ND_RES,
	ND_INTEGER,		ND_REAL,	ND_S_DECL,	ND_S_FACT,	ND_S_AXIOM,	ND_S_RESTR,
	ND_QUERY,		ND_NULL
} ParserNodeType;


//~ typedef enum {
	//~ AF_ABS,		AF_MAX,		AF_MIN,		AF_SIN,		AF_COS,		AF_TAN,
	//~ AF_ASIN,	AF_ACOS,	AF_ATAN,	AF_LN,
	//~ AF_UMINUS,	AF_PLUS,	AF_MINUS,	AF_MULT,	AF_DIV,		AF_MOD,
	//~ AF_POW
//~ } ArithmeticFunctionId;

static const char ARITH_FUNCTION_NAMES[][5] = {
	"abs",		"max",		"min",		"sin",		"cos",		"tan",
	"asin",		"acos",		"atan",		"log",
	"-1",		"+",		"-",		"*",		"/",		"%",
	"^"
};

static const char ARITH_RELATION_NAMES[][3] = {
	"<",	">",	"<=",	">=",
};

static const int ARITH_FUNCTION_PAR_COUNTS[] = {
	1,			2,			2,			1,			1,			1,
	1,			1,			1,			1,
	1,			2,			2,			2,			2,			2,
	2
};

static const int ARITH_RELATION_PAR_COUNTS[] = {
	2,		2,		2,		2
};


//~ typedef struct YYLTYPE
	//~ {
		//~ int first_line;
		//~ int first_column;
		//~ int last_line;
		//~ int last_column;
	//~ } YYLTYPE;
	//~ 
	//~ #define YYLTYPE_IS_DECLARED

/* node of parse tree */
struct ParserNode {
	ParserNodeType type;
	char* name;
	size_t lineNum, columnNum;

	struct ParserNode *params, *next;
};

typedef struct ParserNode ParserNode;



/* === functions === */

/* work with ParserNode */
Boolean hasNodeName(ParserNodeType type);
void initNode(ParserNode* nodePtr, ParserNodeType type, char name[],
				int lineNum, int columnNum);
void freeNode(ParserNode* nodePtr);

ParserNode* setType(ParserNode* nodePtr, ParserNodeType type);
ParserNode* addParamToNode(ParserNode* nodePtr, ParserNode* paramPtr);
ParserNode* addNeighborToNode(ParserNode* nodePtr, ParserNode* neigPtr);
ParserNode* createNode(ParserNodeType type, char name[],
						int lineNum, int columnNum);

/* parsing */
void parseFile(char fileName[], _md);
void parseString(char string[], _md);
Query parseQuery(char string[], _md);


#endif /* PARSER_NODE_HEADER */
