#include "Commands.h"

template<typename Function>
std::pair<std::string, std::shared_ptr<Task>> makeTask(std::string name, Function func) {
    using namespace std;
    return make_pair(name, make_shared<Task>(func));
}

template<typename ...Commands>
std::pair<std::string, std::shared_ptr<CommandsTree>> makeCommandsTree(std::string name, Commands ...cmds) {
    using namespace std;
    return make_pair(name, make_shared<CommandsTree>(cmds...));
}

template<typename ExtensionType, typename ... Arguments>
std::shared_ptr<Extension> makeExtension(Arguments ... args) {
    return dynamic_pointer_cast<Extension>(make_shared<ExtensionType>(args...));
}