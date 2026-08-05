//
// Created by Anamaria Briciu on 04.05.2026.
//

#ifndef SEMINAR5_1012_SERVICE_H
#define SEMINAR5_1012_SERVICE_H
#include "Action.h"
#include "Repository.h"


class Service {
private:
    Repository& repo;

    //methods to handle searching for strings in transmission text fields
    static std::string convertToLower(const std::string& s);
    static bool containsString(const std::string& text, const std::string& query);
    std::vector<std::unique_ptr<Action>> undoStack;
    std::vector<std::unique_ptr<Action>> redoStack;

public:
    void undo();
    void redo();
    Service(Repository& _repo):repo(_repo){};
    void addTransmission(int id, const std::string& sender, const std::string& receiver,  const std::string& content, Priority priority);
    shared_ptr<Transmission> find(int id) {
        return repo.find(id);
    }
    void deleteTransmission(int id);

std::vector<std::shared_ptr<Transmission>> getAllTransmissions() const;

std::vector<std::shared_ptr<Transmission>> search(const std::string& query) const;

std::vector<std::shared_ptr<Transmission>> filterBySender(const std::string& sender) const;

std::vector<std::shared_ptr<Transmission>> filterByPriority(Priority priority) const;

std::vector<std::shared_ptr<Transmission>> filterByReceiver(const std::string& receiver) const;
};




#endif //SEMINAR5_1012_SERVICE_H
