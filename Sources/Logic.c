// Logic.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Logic.h"
#include "Model.h"
#include "Parser.h"
#include "Interpretation.h"

#include "atl.h"



/* === MAIN === */

//~ int main(int argc, char** argv)
//~ {
	//~ ATL_init();
	//~ 
	//~ ATL_ModelId modelId = ATL_createModel();
	//~ ATL_setDebugStream(stdout, modelId);
	//~ ATL_setErrorStream(stdout, modelId);
	
	
	
	//~ ATL_inputFile("../example.sh", modelId);
	//~ ATL_inputString("fact Pred(1);", modelId);
	
	
	
	//~ ATL_run(modelId);
	//~ 
	//~ ATL_free();
	//~ return 0;
	
	//~ Model model;
	//~ initModel(&model);
	//~ model.debugStream = model.errorStream = stdout;
//~ 
	//~ parseFile("../example.sh", &model);
	//~ 
	//~ if (model.errors.len > 0) return 0;

	//~ printDeclarations(&model);
	//~ printRestrictions(&model);
	//~ printAxioms(&model);

	//~ work(&model);
	//~ check(&model);
	//~ 
	//~ freeModel(&model);
	//~ return 0;
	
	/////////////////
		//~ Query query = parseQuery("  P3(, , ) = False;", &model);
	//~ QueryIterator qiter = createQueryIterator(query);
	//~ 
	//~ printf("========\n");
	//~ for (; qiterIsValid(&qiter); moveQIterator(&qiter))
	//~ {
		//~ Fact fact = getFact(&qiter);
		//~ char* factStr = getFactStr(&fact, &model);
		//~ printf("%s\n", factStr);
		//~ 
		//~ freePtr(factStr);
		//~ freeFact(&fact);
	//~ }
	//~ freeQuery(&query);
	//~ printf("========\n");
	
	//~ parseString("declaration Pred:	(Integer) -> Boolean;", &model);
	//~ parseString("fact Pred(1);", &model);
	//~ parseString("axiom All x:Integer "
					//~ "Pred(x) & x < 5 => Pred(x + 1);", &model);
	//~ parseString("restriction 5 + 3 = 9;", &model);
//~ }


void expandVector(Vector* vectPtr, size_t needLen, Boolean extra)
{
	if (needLen <= vectPtr->maxLen)
		return;

	if (extra) needLen *= 2;
	
	vectPtr->addr = realloc(vectPtr->addr, needLen * vectPtr->itemSize);
	vectPtr->maxLen = needLen;
}

char* getDynamicStr(char str[])
{
	if (str == NULL) return NULL;
	
	char* strPtr = (char*) malloc(sizeof(char) * (strlen(str) + 1));
	strcpy(strPtr, str);
	strPtr[strlen(str)] = '\0';
	
	return strPtr;
}


/* for parse & error recovery */


Source createSource()
{
	Source source;
	source.file = NULL;
	source.fileName = NULL;
	source.strPtr = NULL;
	initVect(source.charVect, char);
	return source;
}

Source createFileSource(char fileName[])
{
	Source source = createSource();
	source.type = SRC_FILE;
	source.fileName = getDynamicStr(fileName);
	return source;
}

Source createStreamSource(FILE* stream)
{
	Source source = createSource();
	source.type = SRC_STREAM;
	source.file = stream;
	return source;
}

Source createStringSource(char string[])
{
	Source source = createSource();
	source.type = SRC_STRING;
	source.strPtr = string;
	return source;
}

int getChar(Source* sourcePtr)
{
	int ch;
	
	switch (sourcePtr->type)
	{
		case SRC_FILE:	
			if (sourcePtr->file == NULL)
				sourcePtr->file = fopen(sourcePtr->fileName, "r");
			
			ch = getc(sourcePtr->file);
			//~ if (ch == EOF)
			//~ {
				//~ fclose(sourcePtr->file);
				//~ sourcePtr->file = NULL;
			//~ }
			return ch;
		
		case SRC_STREAM:
			ch = getc(sourcePtr->file);
			addBack(sourcePtr->charVect, char, ch);
			return ch;
		
		case SRC_STRING:
			ch = *(sourcePtr->strPtr++);
			addBack(sourcePtr->charVect, char, ch);
			return ch;
	}
	
	return 0;
}


void comeBack(Source* sourcePtr)
{	
	switch (sourcePtr->type)
	{
		case SRC_FILE:
			if (sourcePtr->file != NULL)
				fseek(sourcePtr->file, -1, SEEK_CUR);
			break;
		
		case SRC_STREAM:
			ungetc(ptr(char, sourcePtr->charVect)[sourcePtr->charVect.len - 1],
				sourcePtr->file);
			delFrom(sourcePtr->charVect, char, sourcePtr->charVect.len - 1);
			break;
		
		case SRC_STRING:
			sourcePtr->strPtr--;
			delFrom(sourcePtr->charVect, char, sourcePtr->charVect.len - 1);
			break;
	}
}


Boolean isEmpty(Source* sourcePtr)
{
	if (sourcePtr->type == SRC_STRING)
		return ptr(char, sourcePtr->charVect)[sourcePtr->charVect.len - 1] == 0;
	else
		return feof(sourcePtr->file);
}

void freeSource(Source* sourcePtr)
{
	freePtr(sourcePtr->fileName);
	freeVect(sourcePtr->charVect);
}




Error createParserError(char msg[], Source* sourcePtr,
						size_t lineNum, size_t columnNum)
{
	Error error;
	error.type = PARSER_ERROR;
	error.location.sourcePtr = sourcePtr;
	error.location.lineNum = lineNum;
	error.location.columnNum = columnNum;
	error.message = getDynamicStr(msg);
	
	return error;
}


Error createInterpretationError(char msg[])
{
	Error error;
	error.type = INTERPRETATION_ERROR;
	error.location.sourcePtr = NULL;
	error.location.lineNum = 0;
	error.location.columnNum = 0;
	error.message = getDynamicStr(msg);
	
	return error;
}


Error createInnerError(char msg[])
{
	Error error;
	error.type = INNER_ERROR;
	error.location.sourcePtr = NULL;
	error.location.lineNum = 0;
	error.location.columnNum = 0;
	error.message = getDynamicStr(msg);
	
	return error;
}


void addTextToError(Error* errorPtr, char msg[])
{
	size_t oldLen = strlen(errorPtr->message);
	errorPtr->message = (char*)realloc(errorPtr->message,
						oldLen + strlen(msg) + 2);
	strcpy(errorPtr->message + oldLen, msg);
}


void printError(Error* errorPtr, FILE* stream)
{
	if (stream == NULL) return;
	
	Source* sourcePtr = errorPtr->location.sourcePtr;
	
	/* print location */
	if (sourcePtr != NULL)
	{
		if (sourcePtr->type == SRC_FILE)
			fprintf(stream, "%s:", sourcePtr->fileName);
		fprintf(stream, "%ld:%ld: ",
				errorPtr->location.lineNum, errorPtr->location.columnNum);
	}
	
	switch (errorPtr->type)
	{
		case PARSER_ERROR:
			fprintf(stream, "error: ");			break;
		case INTERPRETATION_ERROR:
			fprintf(stream, "interpretation error: ");	break;	
		case INNER_ERROR:
			fprintf(stream, "inner error: ");			break;	
	}
	
	fprintf(stream, "%s\n", errorPtr->message);
	
	/* print error line */
	if (sourcePtr != NULL)
	{	
		size_t colNum, lineNum = 1;
		
		if (sourcePtr->type == SRC_FILE) /* from file */
		{
			FILE* file = fopen(sourcePtr->fileName, "r");
			
			while (!feof(file) && lineNum < errorPtr->location.lineNum)
				if (getc(file) == '\n') lineNum++;
			
			int ch;
			
			while (!feof(file) && (ch = getc(file)) != '\n')
				if (ch == '\t')	fprintf(stream, " ");
				else			fprintf(stream, "%c", ch);
			
			fclose(file);
		}
		else	/* from saved string */
		{
			char* str = ptr(char, sourcePtr->charVect);
			
			while (*str != 0 && lineNum < errorPtr->location.lineNum)
				if (*(str++) == '\n') lineNum++;
			
			while (*str != 0 && *str != '\n')
			{
				if (*str == '\t')	fprintf(stream, " ");
				else				fprintf(stream, "%c", *str);
				str++;
			}
		}
		
		fprintf(stream, "\n");
		for (colNum = 1; colNum < errorPtr->location.columnNum; ++colNum)
			fprintf(stream, " ");
		fprintf(stream, "^\n");
	}
}

void freeError(Error* errorPtr)
{
	freePtr(errorPtr->message);
}


/* garbage */

/*void swapVectors(Vector* vec1, Vector* vec2)
{
    Vector vec0 = *vec1;
    *vec1 = *vec2;
    *vec2 = vec0;
}*/

/*
Vector createVector(int itemSize, int initLen)
{
    Vector vec = {0, 0, 0, 0};
    vec.itemSize = itemSize;
    expandVector(&vec, initLen, false);
    return vec;
}
*/

//~ Name makeName(char str[])
//~ {
    //~ Name name;
    //~ strcpy(name.n, str);
    //~ return name;
//~ }
//~ 
//~ void freeMem()
//~ {
//~ }


/*void printFactMaps(int axNum, _p)
{
	Axiom* ax = &ptr(Axiom, axioms_g)[axNum];
	AxiomData* data = &ptr(AxiomData, axData_g)[axNum];
	Vector* axMaps = data->facts;
	
	int it, mi, vi;
	for (it = 0; it < ax->premCt; it++)
	{
		FactMap* itMaps = ptr(FactMap, axMaps[it]);
		for (mi = 0; mi < axMaps[it].len; mi++)
		{
			for (vi = 0; vi < ax->varNames.len; vi++)
				if (itMaps[mi][vi] != IDC)
					printf("%s,", ptr(Name, cons_g)[itMaps[mi][vi]].n);
				else printf("_,");
			printf(" ");
		}
		printf("\n");
	}
}
*/


















