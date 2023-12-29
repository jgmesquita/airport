#include <string>

using namespace std;

class Flight{
private:
    string source;
    string target;
    string airline;
public:
    /**
     * @brief Constructor for the Flight Class.
     * @param source Source airport.
     * @param target Target airport.
     * @param airline Airline
     */
    Flight(string source, string target, string airline) {
        this->source = source;
        this->target = target;
        this->airline = airline;
    }
    /**
     * @brief Get source airport.
     * @return Source airport.
     */
    string getSource() {
        return this->source;
    }
    /**
     * @brief Get target airport.
     * @return Target airport.
     */
    string getTarget() {
        return this->target;
    }
    /**
     * @brief Get airline.
     * @return Airline.
     */
    string getAirline() {
        return this->airline;
    }
};
