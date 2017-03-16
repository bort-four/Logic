/* interpretator.c */

/* conditional directives */

#define PLATFORM_WIDNOWS	1
#define PLATFORM_UNIX		2
//~ #define PLATFORM 			PLATFORM_WIDNOWS
#define PLATFORM 			PLATFORM_UNIX
#define USE_COLORS

/* include */

#if PLATFORM == PLATFORM_WIDNOWS
	#include <Windows.h>
#endif

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <atl.h>


/* functions */

void setErrorColor();
void setNormalColor();
void printErrors(long firstErrNum, long lastErrNum, ATL_ModelId modelId);
Boolean acceptCommand(char commandStr[], ATL_ModelId modelId);



/* MAIN */

int main(int argc, char** argv)
{
	printf("Logical interpretator version %s\n", ATL_VERSION_STR);
	printf("type 'help' to see command list\n");
	printf("type 'exit' to close interpretator\n\n");
	
	ATL_init();
	ATL_ModelId modelId = ATL_createModel();
	ATL_setDebugStream(stdout, modelId);
	//~ ATL_setErrorStream(stderr, modelId);
	
	/* input files */
	size_t fileNum;
	
	for (fileNum = 1; fileNum < argc; ++fileNum)
		ATL_inputFile(argv[fileNum], modelId);
	
	printErrors(0, ATL_getErrorCt(modelId) - 1, modelId);
	
	/* input commands */
	#define COMMAND_STR_LEN 150
	char commandStr[COMMAND_STR_LEN];
	char inWork = 1;
	
	while (inWork)
	{
		printf("> ");
		size_t pos = 0;
		
		for (; pos < COMMAND_STR_LEN - 1
				&& (commandStr[pos] = getc(stdin)) != '\n'; ++pos);
		commandStr[pos] = '\0';
		
		Boolean exit = acceptCommand(commandStr, modelId);
		if (exit) inWork = 0;
	}
	
	ATL_free();
	return 0;
}



/* implementation */

Boolean acceptCommand(char commandStr[], ATL_ModelId modelId)
{
	char commandName[50];
	char param[50];
	commandName[0]  = '\0';
		
	sscanf(commandStr, "%s", commandName);
	char* commandParams = commandStr + strlen(commandName);
	
	size_t oldErrCount = ATL_getErrorCt(modelId);
	
	if (strcmp(commandName, "exit") == 0)
		return true;
	else if (strcmp(commandName, "input_file") == 0)
	{
		sscanf(commandParams, "%s", param);
		ATL_inputFile(param, modelId);
	}
	else if (strcmp(commandName, "input") == 0)
	{
		ATL_inputString(commandParams, modelId);
	}
	else if (strcmp(commandName, "run") == 0)
	{
		ATL_run(modelId);
	}
	else if (strcmp(commandName, "print") == 0)
	{
		sscanf(commandParams, "%s", param);
		
		if (strcmp(param, "declarations") == 0)
			ATL_printDeclarations(modelId);
		else if (strcmp(param, "axioms") == 0)
			ATL_printAxioms(modelId);
		else if (strcmp(param, "restrictions") == 0)
			ATL_printRestrictions(modelId);
		else
			printf("unknown object \'%s\'\n", param);
	}
	else if (strcmp(commandName, "ask") == 0)
	{
		ATL_Query qiter = ATL_inputQuery(commandParams, modelId);
		
		for (; ATL_queryIsValid(&qiter); ATL_moveQuery(&qiter))
		{
			ATL_Fact fact = ATL_getFact(&qiter);
			char* factStr = ATL_getFactStr(&fact, modelId);
			printf("    %s\n", factStr);
			
			free(factStr);
			ATL_freeFact(&fact);
		}
	}
	else if (strcmp(commandName, "clear") == 0)
	{
		ATL_clear(modelId);
	}
	else if (strcmp(commandName, "help") == 0)
	{
		printf(
		"Commands:\n"
	"    input_file <file_name> - input logical specification from file\n"
	"    input declaration <declaration>; - input single declaration\n"
	"    input fact <fact>; - input single fact\n"
	"    input axiom <axiom>; - input single axiom\n"
	"    input restriction <restriction>; - input single restriction\n"
	"    run - start interpretation\n"
	"    ask <fact_patern>; - display all facts matches whith patern\n"
	"    clear - clear specification\n"
	"    print declarations - display all declarations\n"
	"    print axioms - display all axioms\n"
	"    print restrictions - display all restrictions\n"
	"    help - display this information\n"
	"    exit - close interpretator\n"
		);
	}
	else if (strlen(commandName) != 0)
	{
		printf("unknown command \'%s\'\n", commandName);
		printf("type 'help' to see command list\n");
	}
	
	printErrors(oldErrCount, ATL_getErrorCt(modelId) - 1, modelId);
	
	return false;
}


void printErrors(long firstErrNum, long lastErrNum, ATL_ModelId modelId)
{
	if (firstErrNum 	>= ATL_getErrorCt(modelId)
		|| lastErrNum 	>= ATL_getErrorCt(modelId))
		return;
	
	size_t errNum;
	setErrorColor();
		
	for (errNum = firstErrNum; errNum <= lastErrNum; ++errNum)
	{
		printf("\n");
		ATL_printError(errNum, stderr, modelId);
	}
	
	setNormalColor();
}


void setErrorColor()
{
    #ifdef USE_COLORS
        #if PLATFORM == PLATFORM_WIDNOWS
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 12));
        #elif PLATFORM == PLATFORM_UNIX
            printf("\033[31m");
        #endif
    #endif
}

void setNormalColor()
{
    #ifdef USE_COLORS
        #if PLATFORM == PLATFORM_WIDNOWS
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 7));
        #elif PLATFORM == PLATFORM_UNIX
            printf("\033[0m");
        #endif
    #endif
}
