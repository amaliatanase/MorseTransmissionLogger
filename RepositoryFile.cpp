//
// Created by Anamaria Briciu on 18.05.2026.
//

#include "RepositoryFile.h"
#include <fstream>
#include <QApplication>
#include <sstream>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

Priority RepositoryFile::stringToPriority(const string &p) {
    if (p == "LOW") return Priority::LOW;
    if (p == "NORMAL") return Priority::NORMAL;
    return Priority::IMPORTANT;
}

string RepositoryFile::priorityToString(Priority p) {
    if (p == Priority::LOW) return "LOW";
    if (p == Priority::NORMAL) return "NORMAL";
    return "IMPORTANT";
}

void RepositoryFile::add(std::shared_ptr<Transmission> t) {
    Repository::add(t);
    saveToFile();
}

void RepositoryFile::remove(int id) {
    Repository::remove(id);
    saveToFile();
}

void RepositoryFileCSV::loadFromFile() {
    std::ifstream f(filename);
    if (!f.is_open())
        throw std::runtime_error("Cannot open file");
    string line;
    while (getline(f, line)) {
        string id;
        string sender, receiver, content, priority;
        std::stringstream lineS(line);
        getline(lineS, id, ',');
        getline(lineS, sender, ',');
        getline(lineS, receiver, ',');
        getline(lineS, content, ',');
        getline(lineS, priority, ',');

        int id_i = std::stoi(id);
        Priority p = stringToPriority(priority);
        shared_ptr<Transmission> t =
                std::make_shared<Transmission>(id_i, sender, receiver, content, p);
        RepositoryFile::add(t);
    }
}

void RepositoryFileCSV::saveToFile() {
    //to add
}

void RepositoryFileJSON::loadFromFile() {
    QFile file(QString::fromStdString(filename));
    if (!file.open(QIODevice::ReadOnly))
        throw std::runtime_error("Could not open file");

    QByteArray content = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(content);
    QJsonArray arr = doc.array();
    for (int i = 0; i < arr.size(); i++) {
        if (!arr[i].isObject())
            continue;
        QJsonObject obj = arr[i].toObject();
        //can access values in json multiple ways
        int id = obj["id"].toInt();
        string sender = obj.value("sender").toString().toStdString();
        string receiver = obj.value("receiver").toString().toStdString();
        string transmissionContent = obj.value("content").toString().toStdString();
        string priority = obj.value("priority").toString().toStdString();

        Priority p = stringToPriority(priority);
        shared_ptr<Transmission> t = std::make_shared<Transmission>(id, sender, receiver, transmissionContent, p);
        RepositoryFile::add(t);
    }
}

void RepositoryFileJSON::saveToFile() {
    QJsonArray arr;
    auto allT = getAll();
    for (std::size_t i = 0; i < allT.size(); ++i) {
        if (!allT[i]) continue;

        QJsonObject o;

        o["id"] = allT[i]->getID();
        o["sender"] = QString::fromStdString(allT[i]->getSender());
        o["receiver"] = QString::fromStdString(allT[i]->getReceiver());
        o["content"] = QString::fromStdString(allT[i]->getContent());
        o["priority"] = QString::fromStdString(priorityToString(allT[i]->getPriority()));

        arr.append(o);
    }

    QJsonDocument doc(arr);

    QFile file(QString::fromStdString(filename));
    if (!file.open(QIODevice::WriteOnly))
        return;

    file.write(doc.toJson());
    file.close();
}
