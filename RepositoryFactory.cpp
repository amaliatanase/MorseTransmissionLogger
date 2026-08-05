//
// Created by Anamaria Briciu on 18.05.2026.
//

#include "RepositoryFactory.h"

#include "RepositoryFile.h"

std::unique_ptr<Repository> RepositoryFactory::create(const string &repoType, const string &filename) {
    if (repoType=="csv") {
        return std::make_unique<RepositoryFileCSV>(filename);
    }
    else if (repoType=="json") {
        return std::make_unique<RepositoryFileJSON>(filename);
    }
    return std::make_unique<Repository>();
}
