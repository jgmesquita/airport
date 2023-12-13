#include <string>

using namespace std;

class Flight{
private:
    string source;
    string target;
    string airline;
public:
    Flight(string source, string target, string airline) {
        this->source = source;
        this->target = target;
        this->airline = airline;
    }

    string getSource() {
        return this->source;
    }

    string getTarget() {
        return this->target;
    }

    string getAirline() {
        return this->airline;
    }
};
