#include <QApplication>
#include <QPushButton>
#include "Service.h"
#include "RepositoryFactory.h"
#include "TransmissionsGUI.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    std::cout << Transmission::getMorseCode("This is an SOS.");
    string repoType, filename = "";
    // std::cout << "What type of repo? (memory/csv/json)";
    // getline(std::cin, repoType);
    // if (repoType == "csv" || repoType == "json") {
    //     std::cout << "Filename: ";
    //     getline(std::cin, filename);
    // }
    std::unique_ptr<Repository> repo = RepositoryFactory::create("json","../transmissions.json");
    // auto allT = repo->getAll();
    // qDebug() << repo->getAll().size();
    // for (int i = 0; i<repo->getAll().size(); i++) {
    //     qDebug() << allT.at(i)->getID();
    // }
    //RepositoryFileCSV repo("../transmissions.csv");
    Service srv(*repo);

    TransmissionsGUI ui(srv);
    ui.show();
    return QApplication::exec();
}
