#include <string>

using namespace std;

class Airport {
private:
    string code;
    string name;
    string city;
    string country;
    string latitude;
    string longitude;

public:
    Airport(string code, string name, string city, string country, string latitude, string longitude) {
        this->code = code;
        this->name = name;
        this->city = city;
        this->country = country;
        this->latitude = latitude;
        this->longitude = longitude;
    }
    Airport() {}

    string getCode() {
        return this->code;
    }

    string getName() {
        return this->name;

    }

    string getCity() {
        return this->city;
    }

    string getCountry() {
        return this->country;
    }

    string getLatitude() {
        return this->latitude;
    }

    string getLongitude() {
        return this->longitude;
    }

    bool operator == (const Airport &a2) const {
        return this->code == a2.code;
    }
    bool operator < (const Airport &a2) const {
        return this->code < a2.code;
    }
};
