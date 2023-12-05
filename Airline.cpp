#include <string>

using namespace std;

class Airline {
private:
    string code;
    string name;
    string callsign;
    string country;

public:
    Airline(string code, string name, string callsign, string country) {
        this->code = code;
        this->name = name;
        this->callsign = callsign;
        this->country = country;
    }

    Airline() {}

    string getCode() {
        return this->code;
    }

    string getName() {
        return this->name;
    }

    string getCallSign() {
        return this->callsign;
    }

    string getCountry() {
        return this->country;
    }
};