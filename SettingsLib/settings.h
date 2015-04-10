#ifndef _SETTINGSLIB_SETTINGS_H_
#define _SETTINGSLIB_SETTINGS_H_

#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <stdexcept>

#include "util.h"

class settings {
public:
    class param {
        friend class settings;

    public:
        param() {
        }

        operator std::string() const {
            return _value;
        }

        operator int() const {
            return stringToInt(_value);
        }

        operator bool() const {
            return stringToBool(_value);
        }

        operator double() const {
            return stringToDouble(_value);
        }

        template<class T>
        param &operator=(const T &value) {
            return *this = param(value);
        }

        template<class T>
        param &operator+=(const T &value) {
            return *this = T(*this) + value;
        }

        template<class T>
        param &operator-=(const T &value) {
            return *this = T(*this) - value;
        }

        template<class T>
        param &operator*=(const T &value) {
            return *this = T(*this) * value;
        }

        template<class T>
        param &operator/=(const T &value) {
            return *this = T(*this) / value;
        }

        template<class T>
        param &operator|=(const T &value) {
            return *this = T(*this) | value;
        }

        template<class T>
        param &operator&=(const T &value) {
            return *this = T(*this) & value;
        }

        bool is_empty() const {
            return _value.empty();
        }

    private:
        std::string _value;

        param(const param &parameter) {
            _value = parameter._value;
        }

        param(const std::string &value) {
            _value = value;
        }

        param(const int &value) {
            _value = intToString(value);
        }

        param(const bool &value) {
            _value = boolToString(value);
        }

        param(const double &value) {
            _value = doubleToString(value);
        }
    };

    // Main functions

    /**
     * Construct settings store
     * and load data from file (if exists)
     * \param filename Path to file with settings
     */
    settings(const std::string &fileName) {
        _fileName = fileName;
        read();
    }

    virtual ~settings() {
        write();
    }

/**
     * Get setting value
     * \param name Setting unique identifier
     * \param def Default setting value
     * \return Stored value for given name or default value
     */
    const std::string &get(const std::string &name,
            const std::string &def = "") const {
        if (_table.find(name) != _table.end()) {
            return _table.at(name)._value;
        }
        return def;
    }

    /**
     * Set or replace setting value and save changes to file
     * \param name Setting unique identifier
     * \param value New setting value
     */
    void set(const std::string &name, const std::string &value) {
        _table[name] = value;
        write();
    }

    /**
     * Reset all settings
     */
    void reset() {
        _table.clear();
        write();
    }

    /**
     * Reload all settings from file
     */
    void reload() {
        read();
    }

    // Advanced funñtions

    /**
      * Get constant setting wrapper
      * \param name Setting unique identifier
      */
    const param operator[](const std::string &name) const {
        return _table.at(name);
    }

    /**
      * Get constant setting wrapper
      * \param name Setting unique identifier
      */
    param operator[](const std::string &name) {
        return _table.at(name);
    }

private:
    std::string _fileName;
    std::map<std::string, param> _table;

    void read() {
        std::ifstream stream(_fileName);
        if (!stream) {
            std::cout << "Settings file created.\n";
            return;
        }
        while (1) {
            std::string name;
            std::string value;
            stream >> name >> value;
            if (name == "") {
                break;
            }
            _table[name] = value;
        }
    }

    void write() {
        std::ofstream stream(_fileName);
        if (!stream) {
            std::cerr << "Can't safe settings to file.";
            return;
        }
        for (std::map<std::string, param>::const_iterator it = _table.begin(); it != _table.end(); it++) {
            stream << it->first << " " << std::string(it->second) << "\n";
        }
    }
};


#endif //_SETTINGSLIB_SETTINGS_H_
