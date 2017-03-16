// interpretator.cpp

#include <iostream>
#include <string>
#include <sstream>
#include <functional>
#include <vector>
#include <algorithm>

extern "C"
{
    #include <atl.h>
}



int main(int argc, char** argv)
{
    if (argc == 1)
    {
        std::cout << "No input files specified." << std::endl;
        return 0;
    }

    ATL_init();
    ATL_ModelId modelId = ATL_createModel();
    ATL_setDebugStream(stdout, modelId);
    ATL_setErrorStream(stderr, modelId);

    // input files
    for (int fileNum = 1; fileNum < argc && ATL_getErrorCt(modelId) == 0; ++fileNum)
    {
        ATL_inputFile(argv[fileNum], modelId);
    }

    // check errors
    if (ATL_getErrorCt(modelId) > 0)
    {
        ATL_free();
        return 1;
    }

    // start interpretation
    ATL_run(modelId);

    // check errors
    if (ATL_getErrorCt(modelId) > 0)
    {
        ATL_free();
        return 1;
    }

    ATL_free();
    return 0;
}




/*
void processErrors(size_t firstErrNum, size_t lastErrNum, ATL_ModelId modelId);
void inputFile(const std::string &filename, ATL_ModelId modelId);


int main(int argc, char** argv)
{
    std::cout << "Logical interpretator" << std::endl;
    std::cout << "type 'help' to see command list" << std::endl;
    std::cout << "type 'exit' to close interpretator" << std::endl;

    ATL_init();
    ATL_ModelId modelId = ATL_createModel();
    ATL_setDebugStream(stdout, modelId);
    ATL_setErrorStream(stderr, modelId);

    bool inWork = true;

    // input files
    for (int fileNum = 1; fileNum < argc; ++fileNum)
        inputFile(argv[fileNum], modelId);

    // create commands
    struct Command
    {
        using Action = std::function<void(const std::string &)>;

        Command(std::string name, std::string describtion,
                Action action)
            : _name(name), _describtion(describtion), _action(action)
        {
        }

        std::string _name, _describtion;
        Action _action;
    };

    std::vector<Command> commands;
    commands.push_back(Command("help", "show this help",
                               [&commands](const std::string &)
    {
        std::cout << "Commnds: " << std::endl;
        for (const Command &command : commands)
            std::cout << "    " << command._name << "  " << command._describtion << std::endl;
    }));

    commands.push_back(Command("exit", "exit interpretator",
                               [&inWork](const std::string &)
    {
        inWork = false;
    }));


    // process command
    for ( ; inWork; )
    {
        std::cout << "> ";

        // input command
        std::string commandText, commandName, parameters;
        inWork = std::getline(std::cin, commandText);
        std::istringstream stream(commandText);
        stream >> commandName;
        std::getline(stream, parameters);

        if (commandName == "")
        {
        }
        else
        {
            auto it = std::find_if(commands.begin(), commands.end(),
                                   [&commandName](const Command &command)
            {
                return command._name == commandName;
            });

            if (it == commands.end())
                std::cout << "unknown command '" << commandName << "'" << std::endl;
            else
            {
                it->_action(parameters);
            }
        }
    }

    ATL_free();
    return 0;
}



void inputFile(const std::string &filename, ATL_ModelId modelId)
{
    ATL_inputFile(const_cast<char *>(filename.c_str()), modelId);
    processErrors(0, ATL_getErrorCt(modelId) - 1, modelId);
}


void processErrors(size_t firstErrNum, size_t lastErrNum, ATL_ModelId modelId)
{
    if (firstErrNum 	>= ATL_getErrorCt(modelId)
        || lastErrNum 	>= ATL_getErrorCt(modelId))
        return;

    for (size_t errNum = firstErrNum; errNum <= lastErrNum; ++errNum)
    {
        printf("\n");
        ATL_printError(errNum, stderr, modelId);
    }
}
*/
