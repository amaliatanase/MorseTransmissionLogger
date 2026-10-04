
#ifndef SEMINAR5_1012_REPOSITORY_H
#define SEMINAR5_1012_REPOSITORY_H
#include <vector>
#include <memory>
using std::shared_ptr;
#include "Transmission.h"
class Repository {
private:
    std::vector<shared_ptr<Transmission>> transmissions;
public:
    Repository()=default;
    virtual void add(std::shared_ptr<Transmission> t);
    virtual void remove(int id);
    virtual std::shared_ptr<Transmission> find(int id);
    virtual std::vector<std::shared_ptr<Transmission>> getAll() const;
    virtual unsigned long long getSize();
    virtual ~Repository() = default;
};


#endif //SEMINAR5_1012_REPOSITORY_H
