#ifndef SEMINAR5_1012_TRANSMISSION_H
#define SEMINAR5_1012_TRANSMISSION_H

#include <string>
#include <map>
#include <iostream>
using std::string;
using std::map;
enum class Priority {
    LOW,
    NORMAL,
    IMPORTANT
};

class Transmission {
private:
    int id;
    string sender;
    string receiver;
    string content;
    Priority priority;
    static map<char, string> getMorseMap();
public:
    Transmission(int _id, const string &_sender, const string &_receiver, const string &_content,
                 Priority _priority) : id(_id), sender(_sender), receiver(_receiver), content(_content),
                                       priority(_priority) {
    };


     int getID() const;
    const string& getSender() const;
    const string& getReceiver() const;
    const string& getContent() const;
   Priority getPriority() const;

    ~Transmission() = default;
    static string getMorseCode(const string& content);
};


#endif //SEMINAR5_1012_TRANSMISSION_H
