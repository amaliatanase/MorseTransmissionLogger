
#include "TransmissionsGUI.h"
#include <QVBoxLayout>
#include <QKeySequence>
#include <QFormLayout>
#include <QMessageBox>
#include <QTimer>

QString TransmissionsGUI::priorityToQString(Priority p) {
    if (p == Priority::LOW) return QString{"LOW"};
    if (p == Priority::NORMAL) return QString{"NORMAL"};
    return QString{"IMPORTANT"};
}

void TransmissionsGUI::initGUI() {
    table = new QTableWidget;
    table->setColumnCount(6);
    table->setRowCount(srv.getAllTransmissions().size());
    table->setHorizontalHeaderLabels(QStringList{"ID", "Sender", "Receiver", "Content", "Morse Content", "Priority"});
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);


    idLbl = new QLabel("ID");
    senderLbl = new QLabel("Sender");
    receiverLbl = new QLabel("Receiver");
    contentLbl = new QLabel("Content");
    priorityLbl = new QLabel("Priority");

    idEdit = new QLineEdit;
    senderEdit = new QLineEdit;
    receiverEdit = new QLineEdit;
    contentEdit = new QPlainTextEdit;
    priorityCombo = new QComboBox;
    priorityCombo->addItem("LOW");
    priorityCombo->addItem("NORMAL");
    priorityCombo->addItem("IMPORTANT");

    addBtn = new QPushButton("Add");
    delBtn = new QPushButton("Delete");
    searchBtn = new QPushButton("Search");
    playBtn = new QPushButton("Play");
    stopBtn = new QPushButton("Stop");

    clearSearchBtn = new QPushButton("Clear search");

    searchEdit = new QLineEdit;
    torchOn.load("../torch_on.png");
    torchOff.load("../torch_off.png");

    imageLbl = new QLabel;
    //imageLbl->setPixmap(torchOff.scaled(200, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    setTorchImage(false);
    circleLbl = new QLabel;
    circleLbl->setFixedSize(70, 70);
    //circleLbl->setStyleSheet("background-color: white; border-radius: 35px");
    setCircle(false);

    playedLettersLbl = new QLabel("Played letters");
    playedLettersEdit = new QPlainTextEdit;

    playedSymbolsLbl = new QLabel("Played symbols");
    playedSymbolsEdit = new QPlainTextEdit;

    undoShortcut = new QShortcut(QKeySequence("CTRL+Z"), this);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    setLayout(mainLayout);
    QVBoxLayout *leftSideLayout = new QVBoxLayout;
    leftSideLayout->addWidget(table);
    QVBoxLayout *playMorseLayout = new QVBoxLayout;
    QHBoxLayout *displayLayout = new QHBoxLayout;
    displayLayout->addWidget(imageLbl);
    displayLayout->addWidget(circleLbl);
    playMorseLayout->addLayout(displayLayout);
    playMorseLayout->addWidget(playedLettersLbl);
    playMorseLayout->addWidget(playedLettersEdit);
    playMorseLayout->addWidget(playedSymbolsLbl);
    playMorseLayout->addWidget(playedSymbolsEdit);

    QHBoxLayout *playBtnsRow = new QHBoxLayout;
    playBtnsRow->addWidget(playBtn);
    playBtnsRow->addWidget(stopBtn);
    QVBoxLayout *rightSideLayout = new QVBoxLayout;
    QFormLayout *formLayout = new QFormLayout;

    playMorseLayout->addLayout(playBtnsRow);
    leftSideLayout->addLayout(playMorseLayout);

    mainLayout->addLayout(leftSideLayout);
    mainLayout->addLayout(rightSideLayout);

    formLayout->addRow(idLbl, idEdit);
    formLayout->addRow(senderLbl, senderEdit);
    formLayout->addRow(receiverLbl, receiverEdit);
    formLayout->addRow(contentLbl, contentEdit);
    formLayout->addRow(priorityLbl, priorityCombo);

    rightSideLayout->addLayout(formLayout);

    QHBoxLayout *btnRow = new QHBoxLayout;
    btnRow->addWidget(addBtn);
    btnRow->addWidget(delBtn);

    QHBoxLayout *searchRow = new QHBoxLayout;
    searchRow->addWidget(searchEdit);
    searchRow->addWidget(searchBtn);
    searchRow->addWidget(clearSearchBtn);

    rightSideLayout->addLayout(btnRow);
    rightSideLayout->addLayout(searchRow);
}

void TransmissionsGUI::connectSignalsSlots() {
    //connect elements (buttons, shortcut, selection in table)
    connect(table, &QTableWidget::itemSelectionChanged, this, &TransmissionsGUI::handleTableSelectionChanged);
    //left to connect: add, filter
    connect(delBtn, &QPushButton::clicked, this, &TransmissionsGUI::handleDelete);
    connect(undoShortcut, &QShortcut::activated, this, &TransmissionsGUI::handleUndo);
    connect(playBtn, &QPushButton::clicked, this, &TransmissionsGUI::handlePlay);
    connect(stopBtn, &QPushButton::clicked, this, &TransmissionsGUI::handleStop);

}

void TransmissionsGUI::reloadData(const std::vector<std::shared_ptr<Transmission> > &transmissions) {
    table->clearContents();
    table->setRowCount(transmissions.size());
    for (int i = 0; i < transmissions.size(); i++) {
        auto t = transmissions.at(i);
        if (!t) {
            continue;
        }
        table->setItem(i, 0, new QTableWidgetItem(QString::number(t->getID())));
        table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(t->getSender())));
        table->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(t->getReceiver())));
        table->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(t->getContent())));
        table->setItem(i, 4, new QTableWidgetItem(priorityToQString(t->getPriority())));
        table->setItem(i, 5, new QTableWidgetItem(QString::fromStdString(Transmission::getMorseCode(t->getContent()))));
    }
}

int TransmissionsGUI::getSelectedID() {
    auto selectedItems = table->selectedItems();
    if (selectedItems.empty())
        return -1;
    auto item = selectedItems.at(0);
    int row = item->row();
    int id = table->item(row, 0)->text().toInt();
    return id;
}

void TransmissionsGUI::setCircle(bool on) {
    if (on) {
        circleLbl->setStyleSheet("background-color: white; border-radius: 35px");
    } else
        circleLbl->setStyleSheet("background-color: black; border-radius: 35px");
}

void TransmissionsGUI::setTorchImage(bool on) {
    if (!on)
        imageLbl->setPixmap(torchOff.scaled(200, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    else
        imageLbl->setPixmap(torchOn.scaled(200, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

QChar TransmissionsGUI::nextLetterFromStr(const QString &s, int &index) {
    while (index < s.size() && s.at(index) == ' ')
        index++;
    if (index >= s.size())
        return QChar();
    QChar charToReturn = s.at(index);
    index++;
    return charToReturn;
}

void TransmissionsGUI::processMorseCode(QString content, QString morseCode) {
    steps.clear();
    QStringList tokens = morseCode.split(" ", Qt::SkipEmptyParts);
    int indexInContentString = 0;
    qDebug() << content.size();
    for (int i = 0; i < tokens.size(); i++) {
        qDebug() << tokens[i];
        QString crtToken = tokens[i];
        if (crtToken == "/") {
            //spatiu intre cuvinte
            Step offStep;
            offStep.torchOn = false;
            offStep.delayMs = 7 * unitMs;
            offStep.letter = " ";
            offStep.symbol = " / ";
            steps.push_back(offStep);
            continue;
        }
        QChar letter = nextLetterFromStr(content, indexInContentString);
        qDebug() << "Letter: " << letter;
        if (letter.isNull())
            letter = '?';
        qDebug() << "i = " << i;
        for (int j = 0; j < crtToken.size(); j++) {
            QChar crtSymbol = crtToken[j];
            int howManyUnits = 0;
            if (crtSymbol == '.')
                howManyUnits = 1;
            else if (crtSymbol == '-')
                howManyUnits = 3;


            Step onStep;
            onStep.torchOn = true;
            onStep.delayMs = howManyUnits * unitMs;
            if (j == 0)
                //only if it's the first symbol in group
                //should we print the associated letter
                onStep.letter = letter;
            else
                onStep.letter = "";
            onStep.symbol = crtSymbol;
            steps.push_back(onStep);

            Step betweenSymGapStep;
            betweenSymGapStep.torchOn = false;
            betweenSymGapStep.delayMs = 1 * unitMs;
            //to modify to get actual current letter
            betweenSymGapStep.letter = "";
            betweenSymGapStep.symbol = "";
            steps.push_back(betweenSymGapStep);
        }

        //gap intre litere
        if (i + 1 < tokens.size() && tokens[i + 1] != "/") {
            Step offLetterStep;
            offLetterStep.torchOn = false;
            offLetterStep.delayMs = 2 * unitMs;
            offLetterStep.letter = "";
            offLetterStep.symbol = " ";
            steps.push_back(offLetterStep);
        }
    }
    qDebug() << "Finished processing morse code";
}

void TransmissionsGUI::play() {
    playedLettersEdit->clear();
    playedSymbolsEdit->clear();
    crtStepIndex = 0;
    setCircle(false);
    setTorchImage(false);
    playStep();

    //this looks intuitive, but doesn't work
    //int totalDelay = 0;
    // for (int i = 0; i < steps.size(); i++) {
    //
    //     QTimer::singleShot(totalDelay, this, [this, i, &totalDelay]() {
    //         Step s = steps[i];
    //         setCircle(s.torchOn);
    //         setTorchImage(s.torchOn);
    //         playedSymbolsEdit->moveCursor(QTextCursor::End);
    //         playedSymbolsEdit->insertPlainText(s.symbol);
    //         playedSymbolsEdit->moveCursor(QTextCursor::End);
    //         totalDelay+=steps[i].delayMs;
    //     });
    // }
}

void TransmissionsGUI::stop() {
    steps.clear();
    crtStepIndex = 0;

    setCircle(false);
    setTorchImage(false);

    playedLettersEdit->clear();
    playedSymbolsEdit->clear();

}

void TransmissionsGUI::playStep() {
    if (crtStepIndex >= steps.size()) {
        stop();
        return;
    }

    Step s = steps.at(crtStepIndex);

    setCircle(s.torchOn);
    setTorchImage(s.torchOn);
    if (!s.symbol.isEmpty()) {
        playedSymbolsEdit->moveCursor(QTextCursor::End);
        playedSymbolsEdit->insertPlainText(s.symbol);
        playedSymbolsEdit->moveCursor(QTextCursor::End);
    }
    if (!s.letter.isEmpty()) {
        playedLettersEdit->moveCursor(QTextCursor::End);
        playedLettersEdit->insertPlainText(s.letter);
        playedLettersEdit->moveCursor(QTextCursor::End);
    }
    crtStepIndex++;
    QTimer::singleShot(s.delayMs, this, [this]() {
        playStep();
    });
}

void TransmissionsGUI::handleTableSelectionChanged() {
    int id = getSelectedID();
    if (id == -1)
        return;
    auto transmission = srv.find(id);
    if (!transmission)
        return;
    idEdit->setText(QString::number(transmission->getID()));
    senderEdit->setText(QString::fromStdString(transmission->getSender()));
    receiverEdit->setText(QString::fromStdString(transmission->getReceiver()));
    contentEdit->setPlainText(QString::fromStdString(transmission->getContent()));
    priorityCombo->setCurrentText(priorityToQString(transmission->getPriority()));
}

void TransmissionsGUI::handleDelete() {
    int id = idEdit->text().toInt();
    try {
        srv.deleteTransmission(id);
        qDebug() << "in delete";
        reloadData(srv.getAllTransmissions());
    } catch (std::invalid_argument &e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void TransmissionsGUI::handleUndo() {
    try {
        srv.undo();
        reloadData(srv.getAllTransmissions());
    } catch (std::exception &e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void TransmissionsGUI::handlePlay() {
    int id = getSelectedID();
    auto transmission = srv.find(id);
    if (!transmission)
        QMessageBox::warning(this, "Error", "Cannot find transmission with given ID.");
    QString morseCode = QString::fromStdString(Transmission::getMorseCode(transmission->getContent()));

    //also need the string content for the letters
    QString content = QString::fromStdString(transmission->getContent());
    qDebug() << "This is the current Morse Code we are playing: " << morseCode;
    //ensure that previous playback is stopped
    stop();
    //create the necessary steps for current transmission
    processMorseCode(content, morseCode);
    //start playing code
    play();
}

void TransmissionsGUI::handleStop() {
    stop();
}
