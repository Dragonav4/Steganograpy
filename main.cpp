#include <iostream>
#include <vector>
#include "exceptions/argument_count_exception.h"
#include "commandHandlers/CommandHandlersCollection.h"
#include "commandHandlers/HelpCommandHandler.h"

using namespace std;

auto print_invalid_parameters_count(const vector<string>& params, int expected_size) {
    cout<<"Invalid amount of parameters for command "<<params[0]
        <<". Receiving "<<params.size()<<" while expecting "<<expected_size<<" parameters"<<endl;
    CommandHandlersCollection::getDefaultCommandHandler()->handleWithoutParamsCheck(params);
}

auto main(int argc, char* argv[]) -> int {

    // Fill params collection from command line
    auto params = vector<string>();
    for(int i=1; i<argc; i++) // 0 for path
        params.emplace_back(argv[i]); //push_back

    try {
        for (auto commandHandler: CommandHandlersCollection::getCommandHandlers()) {
            if (commandHandler->canHandle(params)) { //pointer ->, ref .
                commandHandler->handleWithParamsCheck(params);
                return 0;
            }
        }
        CommandHandlersCollection::getDefaultCommandHandler()->handleWithoutParamsCheck(params);
    }
    catch(argument_count_exception& ace) {
        print_invalid_parameters_count(params, ace.get_expected_count());
    }
    catch(exception& e) {
        cout<<e.what(); // base function of exception which return message
    }
    return 0;
}
