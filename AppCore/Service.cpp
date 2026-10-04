#include "Service.h"

#include <csignal>

std::string Service::convertToLower(const std::string &s) {
    std::string copyS = s;
    //https://en.cppreference.com/cpp/algorithm/transform
    //transform: applies the given function to the elements of
    //the given input range(s),
    //and stores the result in an output range starting from d_first.
    std::transform(copyS.begin(), copyS.end(), copyS.begin(),
                   [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    //read here why we need casting for fns such as tolower/toupper:
    //https://stackoverflow.com/questions/21805674/do-i-need-to-cast-to-unsigned-char-before-calling-toupper-tolower-et-al
    return copyS;
}

bool Service::containsString(const std::string &text, const std::string &query) {
    std::string textCopy = convertToLower(text);
    std::string queryCopy = convertToLower(query);
    //https://cplusplus.com/reference/string/string/find/
    //find: Searches the string for the first occurrence of the sequence specified by its arguments.
    //returns: The position of the first character of the first match.
    //         If no matches were found, the function returns string::npos.
    return textCopy.find(queryCopy) != std::string::npos;
}

void Service::undo() {
    if (undoStack.empty())
        throw std::runtime_error("No more undos.");
    std::unique_ptr<Action> action = std::move(undoStack.back());
    undoStack.pop_back();
    action->undo();
    redoStack.push_back(std::move(action));
}

void Service::redo() {
    if (redoStack.empty())
        throw std::runtime_error("No more redos.");
    std::unique_ptr<Action> action = std::move(redoStack.back());
    redoStack.pop_back();
    action->redo();
    undoStack.push_back(std::move(action));
}

void Service::addTransmission(int id, const std::string &sender, const std::string &receiver,
                              const std::string &content, Priority priority) {
    //validate id, sender, receiver
    if (id < 0)
        throw std::invalid_argument("ID should be >0!");
    if (sender.empty() || receiver.empty())
        throw std::invalid_argument("Sender/receiver cannot be empty");

    shared_ptr<Transmission> t = std::make_shared<Transmission>(id, sender, receiver, content, priority);
    std::unique_ptr<Action> action = std::make_unique<AddAction>(t, repo);
    action->execute();
    undoStack.emplace_back(std::move(action));
    redoStack.clear();
}

void Service::deleteTransmission(int id) {
    shared_ptr<Transmission> t = repo.find(id);
    if (!t)
        throw std::invalid_argument("Cannot find transmission with the given ID");
    std::unique_ptr<Action> action = std::make_unique<RemoveAction>(t, repo);
    action->execute();
    undoStack.emplace_back(std::move(action));
    redoStack.clear();
}

std::vector<std::shared_ptr<Transmission> > Service::getAllTransmissions() const {
    return repo.getAll();
}

std::vector<std::shared_ptr<Transmission> > Service::search(const std::string &query) const {
    if (query.empty())
        throw std::invalid_argument("Query is empty!");
    std::vector<shared_ptr<Transmission> > filteredTransmissions;
    std::vector<shared_ptr<Transmission> > allTransmissions = repo.getAll();
    std::copy_if(allTransmissions.begin(), allTransmissions.end(),
                 std::back_inserter(filteredTransmissions),
                 [&query](const shared_ptr<Transmission> &t) {
                     return containsString(t->getContent(), query) || containsString(t->getContent(), query);
                 });
    return filteredTransmissions;
}

std::vector<std::shared_ptr<Transmission> > Service::filterBySender(const std::string &sender) const {
    if (sender.empty())
        throw std::invalid_argument("Sender is empty!");
    std::vector<shared_ptr<Transmission> > filteredTransmissions;
    std::vector<shared_ptr<Transmission> > allTransmissions = repo.getAll();
    std::copy_if(allTransmissions.begin(), allTransmissions.end(),
                 std::back_inserter(filteredTransmissions),
                 [&sender](const shared_ptr<Transmission> &t) {
                     return t->getSender() == sender;
                 });
    return filteredTransmissions;
}

std::vector<std::shared_ptr<Transmission> > Service::filterByPriority(Priority priority) const {

    std::vector<shared_ptr<Transmission> > filteredTransmissions;
    std::vector<shared_ptr<Transmission> > allTransmissions = repo.getAll();
    std::copy_if(allTransmissions.begin(), allTransmissions.end(),
                 std::back_inserter(filteredTransmissions),
                 [&priority](const shared_ptr<Transmission> &t) {
                     return t->getPriority() == priority;
                 });
    return filteredTransmissions;
}

std::vector<std::shared_ptr<Transmission> > Service::filterByReceiver(const std::string &receiver) const {
    if (receiver.empty())
        throw std::invalid_argument("Receiver is empty!");
    std::vector<shared_ptr<Transmission> > filteredTransmissions;
    std::vector<shared_ptr<Transmission> > allTransmissions = repo.getAll();
    std::copy_if(allTransmissions.begin(), allTransmissions.end(),
                 std::back_inserter(filteredTransmissions),
                 [&receiver](const shared_ptr<Transmission> &t) {
                     return t->getReceiver() == receiver;
                 });
    return filteredTransmissions;
}

