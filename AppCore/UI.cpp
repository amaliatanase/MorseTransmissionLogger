//
// Created by Anamaria Briciu on 27.04.2026.
//

#include "UI.h"


#include <iostream>

void UI::addTransmission() {
    int id;
    string sender, receiver, content;
    string p;
    Priority priority;
    std::cout << "ID: ";
    std::cin >> id;

    std::cout << "Sender: ";
    std::cin >> sender;

    std::cout << "Receiver: ";
    std::cin >> receiver;

    std::cout << "Content: ";
    getchar();
    getline(std::cin, content);

    priority = readPriority();

    try {
        srv.addTransmission(id, sender, receiver, content, priority);
    } catch (std::runtime_error &e) {
        std::cout << e.what() << std::endl;
    }
}

void UI::displayAllTransmissions() {
    auto allTransmissions = srv.getAllTransmissions();
    printTransmissions(allTransmissions);
}

void UI::deleteTransmission() {
    int id;
    std::cout << "ID to delete:";
    std::cin >> id;
    srv.deleteTransmission(id);
}

void UI::searchTransmission() {
    string query;
    std::cout << "Query:";
    std::cin >> query;
    auto filteredT = srv.search(query);

    printTransmissions(filteredT);
}

void UI::filterTransmissions() {
    string byWhat;
    std::cout << "Filter criteria (sender/receiver/priority):";
    std::cin >> byWhat;
    std::vector<shared_ptr<Transmission> > filteredTransmissions;

    if (byWhat == "sender") {
        string sender;
        std::cout << "Sender: " << std::endl;
        std::cin >> sender;
        filteredTransmissions = srv.filterBySender(sender);
    } else if (byWhat == "receiver") {
        string receiver;
        std::cout << "Receiver: " << std::endl;
        std::cin >> receiver;
        filteredTransmissions = srv.filterByReceiver(receiver);
    } else if (byWhat == "priority") {
        Priority p = readPriority();
        filteredTransmissions = srv.filterByPriority(p);
    } else {
        std::cout << "Cannot filter by the given criteria. Please choose one of criteria: sender, receiver, priority."
                << std::endl;
        return;
    }

    printTransmissions(filteredTransmissions);
}

void UI::printMenu() {
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "TRANSMISSION LOGGER" << std::endl;
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "1. Add new transmission" << std::endl;
    std::cout << "2. Delete transmission" << std::endl;
    std::cout << "3. View all logs" << std::endl;
    std::cout << "4. Search (sender/content)" << std::endl;
    std::cout << "5. Filter (sender/receiver/priority)" << std::endl;
    std::cout << "6. Undo last action" << std::endl;
    std::cout << "7. Redo last action" << std::endl;
    std::cout << "8. Exit" << std::endl;
}

Priority UI::readPriority() {
    int p;
    std::cout << "Priority (1 = LOW/2 = NORMAL/3 = IMPORTANT): ";
    std::cin >> p;
    if (p == 1)
        return Priority::LOW;
    if (p == 2)
        return Priority::NORMAL;

    return Priority::IMPORTANT;
}

void UI::printTransmissions(const std::vector<std::shared_ptr<Transmission> > &transmissions) {
    if (transmissions.empty())
        std::cout << "No transmissions. " << std::endl;
    else {
        for (const auto &pt: transmissions) {
            std::cout << "[Transmission #" << pt->getID() << "]" << std::endl;
            std::cout << "Sender: " << pt->getSender() << std::endl;
            std::cout << "Receiver: " << pt->getReceiver() << std::endl;
            std::cout << "Content: " << pt->getContent() << std::endl;

            std::cout << Transmission::getMorseCode(pt->getContent()) << std::endl;
        }
    }
}

void UI::run() {
    while (true) {
        int cmd;
        printMenu();
        std::cout << ">>>";
        std::cin >> cmd;
        try {
            switch (cmd) {
                case 1:
                    addTransmission();
                    break;
                case 2:
                    deleteTransmission();
                    break;
                case 3:
                    displayAllTransmissions();
                    break;
                case 4:
                    searchTransmission();
                    break;
                case 5:
                    filterTransmissions();
                    break;
                case 6:
                    srv.undo();
                    break;
                case 7:
                    srv.redo();
                    break;
                case 8:
                    return;
                default:
                    std::cout << "Invalid command!";
            }
        } catch (std::exception &e) {
            std::cout << e.what()<<std::endl;
        }
    }
}
