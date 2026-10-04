#ifndef SEMINAR6_1012_REPOSITORYFACTORY_H
#define SEMINAR6_1012_REPOSITORYFACTORY_H
#include "Repository.h"

class RepositoryFactory {
public:
    static std::unique_ptr<Repository> create(const string& repoType, const string& filename);
};


#endif //SEMINAR6_1012_REPOSITORYFACTORY_H
