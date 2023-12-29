#include <string>

using namespace std;

class Airline {
private:
    string code;
    string name;
    string callsign;
    string country;

public:
    /**
     * @brief Constructor for the Airline Class.
     * @param code Code of the airline.
     * @param name Name of the airline.
     * @param callsign Call sign of the airline.
     * @param country Country of the airline.
     */
    Airline(string code, string name, string callsign, string country) {
        this->code = code;
        this->name = name;
        this->callsign = callsign;
        this->country = country;
    }
    /**
     * @brief Default constructor.
     */
    Airline() {}
    /**
     * @brief Get the code of the airline.
     * @return Code of the airline.
     */
    string getCode() {
        return this->code;
    }
    /**
     * @brief Get the name of the airline.
     * @return Name of the airline.
     */
    string getName() {
        return this->name;
    }
    /**
     * @brief Get call sign of the airline.
     * @return call sign of the airline.
     */
    string getCallSign() {
        return this->callsign;
    }
    /**
     * @brief Get the country of the airline.
     * @return Country of the airline.
     */
    string getCountry() {
        return this->country;
    }
};