#include <fstream>
#include "settings.h"

/**
 * Construct settings store
 * and load data from file (if exists)
 * \param filename Path to file with settings
 */
settings::settings(std::string const &filename) {

}

/**
 * Get setting value
 * \param name Setting unique identifier
 * \param def Default setting value
 * \return Stored value for given name or default value
 */
std::string const &settings::get(std::string const &name, std::string const &def) const {
    return "";
}

/**
 * Set or replace setting value and save changes to file
 * \param name Setting unique identifier
 * \param value New setting value
 */
void settings::set(std::string const &name, std::string const &value) {

}

/**
 * Reset all settings
 */
void settings::reset() {

}

/**
 * Reload all settings from file
 */
void settings::reload() {

}

/**
  * Get constant setting wrapper
  * \param name Setting unique identifier
  */
/*settings::param const settings::operator[](std::string const &name) const {

}*/

/**
  * Get constant setting wrapper
  * \param name Setting unique identifier
  */
/*settings::param settings::operator[](std::string const &name) {

}*/
