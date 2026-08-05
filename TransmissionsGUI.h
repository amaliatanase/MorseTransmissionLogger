//
// Created by Anamaria Briciu on 25.05.2026.
//

#ifndef SEMINAR7_1011_TRANSMISSIONSGUI_H
#define SEMINAR7_1011_TRANSMISSIONSGUI_H
#include <qwidget.h>
#include <QTableWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QComboBox>
#include <QPushButton>
#include <QShortcut>
#include "Service.h"
#include "Transmission.h"

class TransmissionsGUI : public QWidget {
private:
    Service &srv;
    QTableWidget *table;
    QLabel *idLbl;
    QLabel *senderLbl;
    QLabel *receiverLbl;
    QLabel *contentLbl;
    QLabel *priorityLbl;

    QLineEdit *idEdit;
    QLineEdit *senderEdit;
    QLineEdit *receiverEdit;
    QPlainTextEdit *contentEdit;
    QComboBox *priorityCombo;

    QPushButton *addBtn;
    QPushButton *delBtn;
    QLineEdit *searchEdit;
    QPushButton *searchBtn;
    QPushButton *clearSearchBtn;

    QPushButton *playBtn;
    QPushButton *stopBtn;

    QLabel *imageLbl;
    QLabel *circleLbl;
    QShortcut *undoShortcut;
    QPixmap torchOn;
    QPixmap torchOff;

    QLabel *playedLettersLbl;
    QPlainTextEdit *playedLettersEdit;
    QLabel *playedSymbolsLbl;
    QPlainTextEdit *playedSymbolsEdit;

    QString priorityToQString(Priority p);

    void initGUI();

    void connectSignalsSlots();

    void reloadData(const std::vector<std::shared_ptr<Transmission> > &transmissions);

    int getSelectedID();

    //Morse playing elements
    //function that sets the circle background to white (on) or black (off)
    void setCircle(bool on);

    //function that sets the image in imageLbl to torchOn img (on) or torchOff img (off)
    void setTorchImage(bool on);

    int unitMs = 200;

    struct Step {
        //in this step, should torch be on? Y/N
        bool torchOn;
        //how much should this particular step last? after how much time to start the next one?
        int delayMs;
        //letter to display for current step
        QString letter;
        //symbol to display for current step
        QString symbol;
    };

    std::vector<Step> steps;
    int crtStepIndex = 0;

    //we need to associate each token (group of symbols) to a letter
    //this function helps us do that
    QChar nextLetterFromStr(const QString & s, int& index);

    //populate the vector of steps
    void processMorseCode(QString content, QString morseCode);


    void play();
    void stop();
    void playStep();

private slots:
    void handleTableSelectionChanged();

    void handleDelete();

    void handleUndo();

    void handlePlay();
    void handleStop();

public:
    TransmissionsGUI(Service &srv) : srv(srv) {
        initGUI();
        connectSignalsSlots();
        reloadData(srv.getAllTransmissions());
    }
};


#endif //SEMINAR7_1011_TRANSMISSIONSGUI_H
