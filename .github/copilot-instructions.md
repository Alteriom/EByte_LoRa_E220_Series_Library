# GitHub Copilot Instructions for EByte LoRa E220 Series Library

This repository contains an Arduino library for EByte LoRa E220 Series devices (LLCC68 chipset) designed for long-range communication (5-10km range).

## Project Context

### Library Overview
- **Purpose**: Arduino library for EByte LoRa E220 LLCC68 devices
- **Platforms**: Arduino, ESP32, ESP8266, STM32, Raspberry Pi Pico, SAMD
- **Range**: 5-10km long-range communication
- **Version**: 1.0.8
- **License**: MIT

### Key Files Structure
- `LoRa_E220.h` - Main library header with class definitions and enums
- `LoRa_E220.cpp` - Core implementation
- `EByte_LoRa_E220_library.h` - Simple include wrapper
- `examples/` - Arduino sketches demonstrating library usage
- `includes/statesNaming.h` - State definitions and constants
- `library.properties` - Arduino library metadata
- `library.json` - PlatformIO library metadata

### Core Functionality
- **Configuration Management**: Read/write device configuration (address, channel, speed, power)
- **Message Transmission**: Transparent, fixed, and broadcast messaging
- **WOR (Wake On Radio)**: Power-saving mode support
- **RSSI Monitoring**: Signal strength measurement
- **Multi-platform UART**: Hardware and software serial support

## Development Guidelines

### Code Style
- Follow Arduino library conventions
- Use descriptive struct and enum names (e.g., `Configuration`, `ModuleInformation`)
- Implement getter methods for human-readable descriptions
- Use consistent debug output with `DEBUG_PRINT` macros
- Memory management with `ResponseStructContainer.close()` pattern

### Key Data Structures
- `Configuration` - Device settings (address, channel, speed, options)
- `ModuleInformation` - Device identification and capabilities
- `ResponseStructContainer` - Generic response wrapper with status
- `ResponseStatus` - Operation result with descriptive messages

### Hardware Abstraction
- Support both hardware and software serial interfaces
- Handle platform-specific pin configurations (M0, M1, AUX pins)
- Voltage divider considerations for 3.3V/5V compatibility
- Platform detection via compiler macros

### Testing and Examples
- Each major feature has a corresponding example sketch
- Examples follow naming pattern: `##_featureName/##_featureName.ino`
- Include both basic usage and advanced configuration examples
- Test across multiple Arduino-compatible platforms

### Alteriom-Specific Considerations
When working on Alteriom-specific enhancements:
- Maintain backward compatibility with existing API
- Consider industrial/commercial use cases
- Focus on reliability and error handling
- Document any proprietary extensions clearly
- Follow existing code patterns and naming conventions

### Build and Test Process
- Arduino IDE: Use library manager or manual installation
- PlatformIO: Library available in registry
- No complex build system - standard Arduino library structure
- Test compilation across supported platforms
- Validate examples compile and upload successfully

### Common Operations
- Device initialization: `e220ttl.begin()`
- Configuration read: `e220ttl.getConfiguration()`
- Message sending: `e220ttl.sendMessage()` variants
- Status checking: `ResponseStatus.getResponseDescription()`
- Memory cleanup: `ResponseStructContainer.close()`

## MCP Server Context
This library requires Arduino-compatible build tools and testing across multiple embedded platforms. The MCP server should provide capabilities for:
- Arduino library compilation and validation
- Multi-platform build testing (ESP32, ESP8266, STM32, etc.)
- Serial communication simulation for testing
- Hardware abstraction layer validation