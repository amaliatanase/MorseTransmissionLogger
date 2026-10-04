#ifndef SEMINAR6_1012_ACTION_H
#define SEMINAR6_1012_ACTION_H
#include <memory>

#include "Repository.h"
#include "Transmission.h"

//Command
//Action:

//Undo Stack: AddAction, RemoveAction
//.           Action*
class Action {
public:
    virtual void execute() = 0;

    virtual void undo() = 0;

    virtual void redo() = 0;

    virtual ~Action() = default;
};

class AddAction : public Action {
private:
    std::shared_ptr<Transmission> t;
    Repository &repo;

public:
    AddAction(shared_ptr<Transmission> _t, Repository &_r) : t{_t}, repo(_r) {
    };

    void execute() override {
        repo.add(t);
    }

    void undo() override {
        repo.remove(t->getID());
    };

    void redo() override {
        repo.add(t);
    }
};

class RemoveAction : public Action {
private:
    std::shared_ptr<Transmission> t;
    Repository &repo;

public:
    RemoveAction(shared_ptr<Transmission> _t, Repository &_r) : t{_t}, repo(_r) {
    };

    void execute() override {
        repo.remove(t->getID());
    }

    void undo() override {
        repo.add(t);
    };

    void redo() override {
        repo.remove(t->getID());
    }
};



#endif //SEMINAR6_1012_ACTION_H
