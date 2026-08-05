//
// Created by Anamaria Briciu on 27.04.2026.
//

#ifndef SEMINAR5_1012_UI_H
#define SEMINAR5_1012_UI_H
#include "Service.h"


class UI {
private:
    Service &srv;

    void addTransmission();

    void displayAllTransmissions();

    void deleteTransmission();

    void searchTransmission();

    void filterTransmissions();

    void printMenu();
    Priority readPriority();
    void printTransmissions(const std::vector<std::shared_ptr<Transmission>>& transmissions);

public:
    UI(Service &_srv) : srv(_srv) {
    };

    void run();

};


#endif //SEMINAR5_1011_UI_H