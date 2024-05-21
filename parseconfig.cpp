#include <string>
#include <map>
#include <sstream>
#include <stdexcept>
#include <cctype>

struct ConfigOptions {
    bool strict_mode = false;
};

std::map<std::string, std::string> ParseConfig(const std::string& data, const ConfigOptions& options) {
    std::map<std::string, std::string> config;
    std::istringstream stream(data);
    std::string line;

    while (getline(stream, line)) {
        // Trim leading and trailing whitespace
        line.erase(line.begin(), std::find_if(line.begin(), line.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        }));
        line.erase(std::find_if(line.rbegin(), line.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        }).base(), line.end());

        if (line.empty() || line[0] == '#') {
            continue;  // Skip empty lines and comments
        }

        size_t equals_pos = line.find('=');
        if (equals_pos == std::string::npos) {
            if (options.strict_mode) {
                throw std::invalid_argument("Line format error: missing '=' character.");
            }
            continue;  // Skip lines with format errors in non-strict mode
        }

        std::string key = line.substr(0, equals_pos);
        std::string value = line.substr(equals_pos + 1);

        // Trim spaces around key and value
        key.erase(key.find_last_not_of(" \t") + 1);
        key.erase(0, key.find_first_not_of(" \t"));
        value.erase(value.find_last_not_of(" \t") + 1);
        value.erase(0, value.find_first_not_of(" \t"));

        if (key.empty() || value.empty()) {
            if (options.strict_mode) {
                throw std::invalid_argument("Line format error: empty key or value.");
            }
            continue;  // Skip lines with incomplete key-value pairs in non-strict mode
        }

        config[key] = value;
    }

    return config;
}


#include <cassert>

int main() {
    ConfigOptions options;
    ConfigOptions strict_options;
    strict_options.strict_mode = true;

    // TEST
    std::map<std::string, std::string> result = ParseConfig("", options);
    assert(result.empty());
    // TEST_END
    
    // TEST
    result = ParseConfig("key1=value1\nkey2=value2", options);
    assert(result["key1"] == "value1" && result["key2"] == "value2");
    // TEST_END
    
    // TEST
    result = ParseConfig("   key1    =    value1    ", options);
    assert(result["key1"] == "value1");
    // TEST_END

    // TEST
    result = ParseConfig("# This is a comment\nkey=value", options);
    assert(result["key"] == "value");
    // TEST_END

    // TEST
    try {
        ParseConfig("invalid_line_without_equal_sign", strict_options);
        assert(false); // Should not reach this point, only tests the error type
    } catch (const std::invalid_argument&) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        ParseConfig("=value_without_key", strict_options);
        assert(false); // Should not reach this point, only tests the error type
    } catch (const std::invalid_argument&) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        ParseConfig("key_without_value=", strict_options);
        assert(false); // Should not reach this point, only tests the error type
    } catch (const std::invalid_argument&) {
        assert(true);
    }
    // TEST_END
}
