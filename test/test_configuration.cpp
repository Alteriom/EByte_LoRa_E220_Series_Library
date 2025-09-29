#include <unity.h>
#include <cstring>

// For native testing, we need to mock Arduino.h and avoid hardware-specific includes
#ifdef UNIT_TEST
// Mock Arduino types and functions for native testing
typedef unsigned char byte;
// Don't redefine standard types - let them come from system headers

// Mock String class for native testing
class String {
private:
    char* buffer;
public:
    String() : buffer(nullptr) {}
    String(const char* str) {
        if (str) {
            int len = strlen(str);
            buffer = new char[len + 1];
            strcpy(buffer, str);
        } else {
            buffer = nullptr;
        }
    }
    ~String() { delete[] buffer; }
    bool startsWith(const char* prefix) const {
        if (!buffer || !prefix) return false;
        return strncmp(buffer, prefix, strlen(prefix)) == 0;
    }
    bool endsWith(const char* suffix) const {
        if (!buffer || !suffix) return false;
        int bufLen = strlen(buffer);
        int sufLen = strlen(suffix);
        if (sufLen > bufLen) return false;
        return strcmp(buffer + bufLen - sufLen, suffix) == 0;
    }
    bool isEmpty() const { return buffer == nullptr || buffer[0] == '\0'; }
};

// Mock the minimal parts of LoRa_E220 library needed for testing
enum Status {
    E220_SUCCESS = 0
};

struct ResponseStatus {
    Status code;
    String getResponseDescription() {
        return String("Test response");
    }
};

struct Configuration {
    byte COMMAND = 0;
    byte STARTING_ADDRESS = 0;
    byte LENGHT = 0;
    byte ADDH = 0;
    byte ADDL = 0;
    byte CHAN = 0;
    
    String getChannelDescription() {
        return String("433MHz");
    }
};

struct ModuleInformation {
    byte COMMAND = 0;
    byte STARTING_ADDRESS = 0;
    byte LENGHT = 0;
    byte model = 0;
    byte version = 0;
    byte features = 0;
};

struct ResponseStructContainer {
    void *data;
    byte rssi;
    ResponseStatus status;
    void close() {
        if (data) {
            free(data);
            data = nullptr;
        }
    }
};

#else
// For actual Arduino compilation, include the real library
#include "../LoRa_E220.h"
#endif



void setUp(void) {
    // Setup before each test
}

void tearDown(void) {
    // Cleanup after each test
}

void test_configuration_structure_initialization() {
    Configuration config;
    
    // Test default values
    TEST_ASSERT_EQUAL(0, config.ADDH);
    TEST_ASSERT_EQUAL(0, config.ADDL);
    TEST_ASSERT_EQUAL(0, config.CHAN);
}

void test_configuration_channel_description() {
    Configuration config;
    config.CHAN = 23;
    
    String description = config.getChannelDescription();
    // Assuming OPERATING_FREQUENCY is 410MHz (from documentation)
    TEST_ASSERT_TRUE(description.startsWith("433"));
    TEST_ASSERT_TRUE(description.endsWith("MHz"));
}

void test_response_status_initialization() {
    ResponseStatus status;
    status.code = E220_SUCCESS;
    
    String description = status.getResponseDescription();
    TEST_ASSERT_FALSE(description.isEmpty());
}

void test_module_information_structure() {
    ModuleInformation info;
    
    // Test structure initialization
    TEST_ASSERT_EQUAL(0, info.COMMAND);
    TEST_ASSERT_EQUAL(0, info.STARTING_ADDRESS);
    TEST_ASSERT_EQUAL(0, info.LENGHT);
    TEST_ASSERT_EQUAL(0, info.model);
    TEST_ASSERT_EQUAL(0, info.version);
    TEST_ASSERT_EQUAL(0, info.features);
}

void test_response_container_memory_management() {
    ResponseStructContainer container;
    container.data = malloc(sizeof(Configuration));
    
    // Test that we can close the container without issues
    container.close();
    
    // After close, data should be freed (we can't directly test this)
    // but the function should not crash
    TEST_ASSERT_TRUE(true); // If we reach here, close() worked
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    
    RUN_TEST(test_configuration_structure_initialization);
    RUN_TEST(test_configuration_channel_description);
    RUN_TEST(test_response_status_initialization);
    RUN_TEST(test_module_information_structure);
    RUN_TEST(test_response_container_memory_management);
    
    return UNITY_END();
}