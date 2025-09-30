# 📚 API Reference

## Overview

The EByte LoRa E220 Series Library provides a comprehensive interface for EByte LoRa E220 Series devices based on the LLCC68 chipset, offering long-range communication capabilities (5-10km range) for Arduino, ESP32, ESP8266, STM32, and Raspberry Pi Pico platforms.

**Version**: 1.1.6  
**Author**: Renzo Mischianti (Original), Alteriom (Fork maintainer with CI/CD enhancements)  
**License**: MIT

## 🏗️ Core Classes

### LoRa_E220 Class

Main LoRa E220 device interface class providing complete control over the module.

#### Constructors

##### Software Serial (Arduino Uno, Nano, Pro Mini)
```cpp
// Basic constructor with TX/RX pins
LoRa_E220(int txE220pin, int rxE220pin, int auxPin, int m0Pin, int m1Pin, UART_BPS_TYPE bpsRate);

// Constructor with custom baud rate
LoRa_E220(int txE220pin, int rxE220pin, int auxPin, int m0Pin, int m1Pin, UART_BPS_TYPE bpsRate);
```

**Parameters**:
- `txE220pin`: Digital pin number for TX to E220 (Arduino TX → E220 RX)
- `rxE220pin`: Digital pin number for RX from E220 (Arduino RX ← E220 TX)  
- `auxPin`: Digital pin connected to E220 AUX pin for status monitoring
- `m0Pin`: Digital pin connected to E220 M0 pin for mode control
- `m1Pin`: Digital pin connected to E220 M1 pin for mode control
- `bpsRate`: UART communication speed (UART_BPS_RATE_9600, UART_BPS_RATE_115200, etc.)

##### Hardware Serial (ESP32, STM32, Mega)
```cpp
// Constructor using hardware serial
LoRa_E220(HardwareSerial* serial, int auxPin, int m0Pin, int m1Pin);

// Constructor with selectable pins (ESP32 only)
LoRa_E220(HardwareSerial* serial, int auxPin, int m0Pin, int m1Pin, int txE220pin, int rxE220pin);
```

**Parameters**:
- `serial`: Pointer to hardware serial interface (Serial1, Serial2, etc.)
- `txE220pin`: (ESP32 only) Hardware serial TX pin assignment
- `rxE220pin`: (ESP32 only) Hardware serial RX pin assignment

#### Core Methods

##### Initialization
```cpp
bool begin();
```
Initialize the E220 module and establish communication.

**Returns**: `true` if initialization successful, `false` otherwise

##### Configuration Management
```cpp
ResponseStructContainer<Configuration> getConfiguration();
ResponseStatus setConfiguration(Configuration configuration, PROGRAM_COMMAND writeType);
```

**Get Configuration**:
- **Returns**: `ResponseStructContainer<Configuration>` containing current device configuration
- **Usage**: Always call `container.close()` after use to free memory

**Set Configuration**:
- **Parameters**:
  - `configuration`: Configuration structure with desired settings
  - `writeType`: 
    - `WRITE_CFG_PWR_DWN_SAVE`: Save to EEPROM (persistent)
    - `WRITE_CFG_PWR_DWN_LOSE`: Temporary (lost on power cycle)
- **Returns**: `ResponseStatus` indicating success/failure

##### Message Transmission

**Transparent Mode**:
```cpp
ResponseStatus sendMessage(String message);
ResponseStatus sendMessage(const void* message, uint8_t size);
```

**Fixed Mode**:
```cpp
ResponseStatus sendFixedMessage(uint8_t ADDH, uint8_t ADDL, uint8_t CHAN, String message);
ResponseStatus sendFixedMessage(uint8_t ADDH, uint8_t ADDL, uint8_t CHAN, const void* message, uint8_t size);
```

**Broadcast Mode**:
```cpp
ResponseStatus sendBroadcastFixedMessage(uint8_t CHAN, String message);
ResponseStatus sendBroadcastFixedMessage(uint8_t CHAN, const void* message, uint8_t size);
```

**Parameters**:
- `ADDH`: High address byte (0x00-0xFF)
- `ADDL`: Low address byte (0x00-0xFF)
- `CHAN`: Channel number (0-80)
- `message`: String or binary data to transmit
- `size`: Size of binary data (max 200 bytes)

##### Message Reception
```cpp
bool available();
String receiveMessage();
ResponseContainer receiveMessageComplete();
String receiveMessageRSSI();
```

**Methods**:
- `available()`: Check if message is available
- `receiveMessage()`: Get message content as String
- `receiveMessageComplete()`: Get message with metadata (RSSI, sender info)
- `receiveMessageRSSI()`: Get message with RSSI information

##### Device Information
```cpp
ResponseStructContainer<ModuleInformation> getModuleInformation();
ResponseStructContainer<String> getVersion();
ResponseStructContainer<int> getRSSI();
```

##### Mode Control
```cpp
ResponseStatus setMode(MODE_TYPE mode);
```

**Mode Types**:
- `MODE_0_TRANSMISSION`: Normal transmission mode
- `MODE_1_WOR_TRANSMITTER`: Wake-on-radio transmitter
- `MODE_2_WOR_RECEIVER`: Wake-on-radio receiver  
- `MODE_3_CONFIGURATION`: Configuration mode

## 📊 Data Structures

### Configuration Structure

Complete device configuration containing all operational parameters.

```cpp
struct Configuration {
    uint8_t ADDH;              // High address byte
    uint8_t ADDL;              // Low address byte  
    uint8_t CHAN;              // Channel (0-80)
    SPED SPED;                 // Speed configuration
    OPTION OPTION;             // Option configuration
    TRANSMISSION_MODE TRANSMISSION_MODE;  // Transmission mode
    Encryption ENCRYPTION;     // Encryption settings
    
    // Helper method
    String getChannelDescription();
};
```

### SPED (Speed Configuration)
```cpp
struct SPED {
    UART_PARITY uartParity;    // UART parity setting
    UART_BPS_TYPE uartBaudRate; // UART baud rate
    AIR_DATA_RATE airDataRate;  // Air interface data rate
    
    // Helper methods
    String getAirDataRateDescription();
    String getUARTParityDescription(); 
    String getUARTBaudRateDescription();
};
```

**UART Baud Rates**:
- `UART_BPS_1200`: 1200 bps
- `UART_BPS_2400`: 2400 bps
- `UART_BPS_4800`: 4800 bps
- `UART_BPS_9600`: 9600 bps (default)
- `UART_BPS_19200`: 19200 bps
- `UART_BPS_38400`: 38400 bps
- `UART_BPS_57600`: 57600 bps
- `UART_BPS_115200`: 115200 bps

**Air Data Rates**:
- `AIR_DATA_RATE_2_4`: 2.4 kbps
- `AIR_DATA_RATE_4_8`: 4.8 kbps
- `AIR_DATA_RATE_9_6`: 9.6 kbps
- `AIR_DATA_RATE_19_2`: 19.2 kbps
- `AIR_DATA_RATE_38_4`: 38.4 kbps
- `AIR_DATA_RATE_62_5`: 62.5 kbps

### TRANSMISSION_MODE (Transmission Configuration)
```cpp
struct TRANSMISSION_MODE {
    WOR_PERIOD WORPeriod;      // Wake-on-radio period
    LBT_ENABLE_BYTE enableLBT; // Listen-before-talk
    FIXED_TRANSMISSION fixedTransmission; // Fixed/transparent mode
    ENABLE_RSSI enableRSSI;    // RSSI output enable
    
    // Helper methods
    String getWORPeriodDescription();
    String getLBTEnableByteDescription();
    String getFixedTransmissionDescription();
    String getEnableRSSIDescription();
};
```

**WOR Periods**:
- `WOR_500_000`: 500ms
- `WOR_1000_000`: 1 second
- `WOR_1500_000`: 1.5 seconds
- `WOR_2000_000`: 2 seconds
- `WOR_2500_000`: 2.5 seconds
- `WOR_3000_000`: 3 seconds
- `WOR_3500_000`: 3.5 seconds
- `WOR_4000_000`: 4 seconds

### OPTION (Advanced Options)
```cpp
struct OPTION {
    TRANSMISSION_POWER transmissionPower; // TX power level
    ENABLE_RSSI_AMBIENT_NOISE_ENABLE rssiAmbientNoiseEnable; // Noise monitoring
    SUB_PACKET_SETTING subPacketSetting; // Packet size setting
    
    // Helper methods
    String getTransmissionPowerDescription();
    String getRSSIAmbientNoiseEnableDescription();
    String getSubPacketSettingDescription();
};
```

**Transmission Power Levels**:
- `POWER_22`: 22dBm (170mW)
- `POWER_17`: 17dBm (50mW)
- `POWER_13`: 13dBm (20mW)
- `POWER_10`: 10dBm (10mW)

### ModuleInformation Structure
```cpp
struct ModuleInformation {
    uint8_t HEAD;              // Response header
    uint8_t model;             // Module model
    uint8_t version;           // Firmware version
    uint8_t features;          // Feature flags
};
```

### ResponseStatus Structure
```cpp
struct ResponseStatus {
    STATUS_CODE code;          // Operation result code
    String data;               // Additional status information
    
    // Helper method
    String getResponseDescription();
};
```

**Status Codes**:
- `SUCCESS`: Operation completed successfully
- `ERR_E220_UNKNOWN_COMMAND`: Invalid command sent
- `ERR_E220_WRONG_PARAMETERS`: Invalid parameters
- `ERR_E220_PACKET_TOO_BIG`: Message exceeds 200 bytes
- `ERR_E220_BRO_WRONG_UART_CONFIG`: UART configuration error
- `ERR_E220_NOT_SUPPORT`: Feature not supported
- `ERR_E220_NOT_IMPLEMENT`: Feature not implemented
- `ERR_E220_NOT_INITIAL`: Module not initialized
- `ERR_E220_INVALID_PARAM`: Invalid parameter value
- `ERR_E220_DATA_SIZE_NOT_MATCH`: Data size mismatch
- `ERR_E220_BUF_TOO_SMALL`: Buffer too small
- `ERR_E220_TIMEOUT`: Operation timeout
- `ERR_E220_HARDWARE`: Hardware error
- `ERR_E220_HEAD_NOT_RECOGNIZED`: Invalid response header

### ResponseStructContainer<T>
```cpp
template<class T>
struct ResponseStructContainer {
    T data;                    // Response data
    ResponseStatus status;     // Operation status
    
    void close();              // Free allocated memory
};
```

**⚠️ Important**: Always call `container.close()` after using ResponseStructContainer to prevent memory leaks.

## 🔧 Constants and Enumerations

### Maximum Values
```cpp
#define MAX_SIZE_TX_PACKET 200  // Maximum transmission size in bytes
```

### Operating Modes
```cpp
enum MODE_TYPE {
    MODE_0_TRANSMISSION = 0,    // Normal transmission
    MODE_1_WOR_TRANSMITTER = 1, // WOR transmitter
    MODE_2_WOR_RECEIVER = 2,    // WOR receiver  
    MODE_3_CONFIGURATION = 3    // Configuration mode
};
```

### Programming Commands
```cpp
enum PROGRAM_COMMAND {
    WRITE_CFG_PWR_DWN_SAVE = 0xC0,    // Save configuration
    READ_CONFIGURATION = 0xC1,         // Read configuration
    WRITE_CFG_PWR_DWN_LOSE = 0xC2,     // Temporary configuration
    WRONG_FORMAT = 0xFF                // Invalid format
};
```

## 🚀 Usage Examples

### Basic Initialization
```cpp
#include "LoRa_E220.h"

// Software Serial (Arduino Uno)
LoRa_E220 e220ttl(2, 3, 4, 5, 6, UART_BPS_RATE_9600);

// Hardware Serial (ESP32)
LoRa_E220 e220ttl(&Serial2, 18, 19, 21);

void setup() {
    Serial.begin(9600);
    e220ttl.begin();
}
```

### Configuration Management
```cpp
void configureDevice() {
    ResponseStructContainer<Configuration> c = e220ttl.getConfiguration();
    if (c.status.code == 1) {
        Configuration config = c.data;
        
        // Modify settings
        config.ADDH = 0x00;
        config.ADDL = 0x01;
        config.CHAN = 23;
        config.SPED.airDataRate = AIR_DATA_RATE_19_2;
        config.OPTION.transmissionPower = POWER_22;
        
        // Save configuration
        ResponseStatus rs = e220ttl.setConfiguration(config, WRITE_CFG_PWR_DWN_SAVE);
        if (rs.code == 1) {
            Serial.println("✅ Configuration saved");
        }
    }
    c.close(); // Important: free memory
}
```

### Message Transmission
```cpp
void sendMessages() {
    // Transparent mode
    e220ttl.sendMessage("Hello World!");
    
    // Fixed mode with addressing
    e220ttl.sendFixedMessage(0x00, 0x02, 23, "Hello Device 2!");
    
    // Broadcast message
    e220ttl.sendBroadcastFixedMessage(23, "Hello Everyone!");
    
    // Binary data
    uint8_t data[] = {0x01, 0x02, 0x03, 0x04};
    e220ttl.sendMessage(data, sizeof(data));
}
```

### Message Reception
```cpp
void receiveMessages() {
    if (e220ttl.available()) {
        // Simple message
        String message = e220ttl.receiveMessage();
        Serial.println("Received: " + message);
        
        // Complete message with metadata
        ResponseContainer rc = e220ttl.receiveMessageComplete();
        Serial.println("Message: " + rc.data);
        Serial.println("RSSI: " + String(rc.rssi));
        rc.close();
    }
}
```

### Error Handling
```cpp
void handleErrors() {
    ResponseStructContainer<Configuration> c = e220ttl.getConfiguration();
    
    if (c.status.code == 1) {
        // Success - use c.data
        Configuration config = c.data;
        Serial.println("Channel: " + String(config.CHAN));
    } else {
        // Error - handle appropriately
        Serial.println("Error: " + c.status.getResponseDescription());
        
        switch (c.status.code) {
            case ERR_E220_TIMEOUT:
                Serial.println("Check wiring and power");
                break;
            case ERR_E220_WRONG_UART_CONFIG:
                Serial.println("Check baud rate settings");
                break;
            default:
                Serial.println("Unknown error occurred");
        }
    }
    
    c.close(); // Always close containers
}
```

## 💡 Best Practices

### Memory Management
- Always call `container.close()` on ResponseStructContainer objects
- Use binary transmission for large data to reduce memory usage
- Monitor free memory on constrained platforms (Arduino Uno)

### Error Handling
- Check ResponseStatus.code before using data
- Implement timeouts for blocking operations
- Use appropriate error recovery strategies

### Performance Optimization
- Match UART baud rate to air data rate for optimal performance
- Use hardware serial when available (ESP32, STM32, Mega)
- Implement proper buffering for high-frequency messaging

### Power Management
- Use WOR mode for battery-powered applications
- Configure appropriate WOR periods based on application needs
- Monitor AUX pin for transmission completion before sleep

## 🔗 Platform-Specific Notes

### Arduino (Software Serial)
- Limited to 9600-57600 baud for reliable operation
- May have timing issues with other interrupts
- Use AUX pin monitoring for better reliability

### ESP32 (Hardware Serial)
- Supports full speed operation up to 115200 baud
- Can use configurable pins for UART
- Excellent for WiFi + LoRa gateway applications

### ESP8266 (Software Serial)
- Similar limitations to Arduino
- Must use `yield()` in loops for stability
- Good for simple IoT sensor nodes

### STM32 (Hardware Serial)
- High performance with multiple UART options
- Supports all library features at full speed
- Excellent for industrial applications

For complete examples and platform-specific code, see the [Examples Library](examples.md).

## 📖 Related Documentation

- [Quick Start Guide](quickstart.md) - Get started quickly
- [Configuration Guide](configuration.md) - Detailed configuration options
- [Examples Library](examples.md) - Complete code examples
- [Troubleshooting](troubleshooting.md) - Common issues and solutions