//
// Created by Anamaria Briciu on 18.05.2026.
//

#ifndef SEMINAR6_1012_REPOSITORYFILE_H
#define SEMINAR6_1012_REPOSITORYFILE_H

#include <string>

#include "Repository.h"

class RepositoryFile: public Repository{
protected:
    std::string filename;
    Priority stringToPriority(const string& p);
    string priorityToString(Priority p);
public:
    RepositoryFile(const string& file):filename(file) {};
    virtual void loadFromFile() = 0;
    virtual void saveToFile() = 0;
    void add(std::shared_ptr<Transmission> t) override;
    void remove(int id) override;

};

class RepositoryFileCSV:public RepositoryFile {
public:
    RepositoryFileCSV(const string& file):RepositoryFile(file)
    {
        loadFromFile();
    };
    void loadFromFile() override;
    void saveToFile() override;
};

class RepositoryFileJSON:public RepositoryFile {
public:
    RepositoryFileJSON(const string& file):RepositoryFile(file)
    {
        loadFromFile();
    };
    void loadFromFile() override;
    void saveToFile() override;
};

#endif //SEMINAR6_1012_REPOSITORYFILE_H