#include "Repository.h"

void Repository::add(std::shared_ptr<Transmission> t) {
    // for (const auto& transmission: transmissions)
    //     if (t->getID()==transmission->getID())
    //         throw std::runtime_error("There already is a transmission with ID = "+ std::to_string(t->getID()));
    if (find(t->getID()) != nullptr)
        throw std::runtime_error("There already is a transmission with ID = " + std::to_string(t->getID()));
    transmissions.push_back(t);
}

void Repository::remove(int id) {
    auto it = std::find_if(transmissions.begin(), transmissions.end(),
                           [id](const shared_ptr<Transmission> &crtT) {
                               return crtT->getID() == id;
                           });
    if (it == transmissions.end())
        throw std::runtime_error("There is no transmission with ID = " + std::to_string(id));
    transmissions.erase(it);
}

std::shared_ptr<Transmission> Repository::find(int id) {
    auto it = std::find_if(transmissions.begin(), transmissions.end(),
                           [id](const shared_ptr<Transmission> &crtT) {
                               return crtT->getID() == id;
                           });
    if (it != transmissions.end())
        return *it;
    return nullptr;
}

std::vector<std::shared_ptr<Transmission> > Repository::getAll() const {
    return transmissions;
}

unsigned long long Repository::getSize() {
    return transmissions.size();
}
