# Usage Example: GitHub Copilot with MCP Server

This document demonstrates how to use the newly configured GitHub Copilot instructions and MCP server with the EByte LoRa E220 library.

## Setting up MCP Server

### 1. Configure your development environment

Add the MCP server configuration to your Copilot settings:

```json
{
  "github.copilot.mcp.servers": {
    "arduino-ebyte": {
      "configFile": ".github/mcp-server-config.json"
    }
  }
}
```

### 2. Available MCP Commands

With the configured MCP servers, you can now use:

#### Arduino CLI Commands
- `arduino-cli compile --fqbn esp32:esp32:esp32 examples/01_getConfiguration/`
- `arduino-cli lib install "EByte LoRa E220 library"`
- `arduino-cli board list`

#### PlatformIO Commands
- `pio run -e esp32dev`
- `pio test -e native`
- `pio device list`

## Example Development Session

### Creating a New LoRa Example

**Prompt to Copilot:**
```
Create a new Arduino example that demonstrates sending sensor data via LoRa E220 with JSON payload. The example should:
1. Read temperature from a DHT22 sensor
2. Package the data in JSON format  
3. Send via LoRa with fixed transmission
4. Handle response status appropriately
```

**Copilot Response:** 
With the custom instructions, Copilot will:
- Understand the LoRa E220 library structure
- Use appropriate Configuration structs
- Implement proper error handling with ResponseStatus
- Follow the existing code patterns from other examples
- Include proper pin configurations for different platforms

### Debugging Compilation Issues

**Prompt to Copilot:**
```
The example won't compile for ESP32. Fix the platform-specific issues.
```

**Copilot Response:**
With MCP server integration, Copilot can:
- Check the actual compilation errors from Arduino CLI
- Reference the platformio.ini configuration
- Apply ESP32-specific build flags
- Suggest platform-appropriate serial configurations

### Testing Across Platforms

**Prompt to Copilot:**
```
Test this code across all supported platforms and fix any compatibility issues.
```

**Copilot Response:**
The MCP server enables Copilot to:
- Compile for multiple platforms automatically
- Identify platform-specific compilation errors
- Suggest appropriate conditional compilation directives
- Validate library dependencies for each platform

## Example Code Generation

### Before Custom Instructions
Copilot might generate generic Arduino code:
```cpp
#include <SoftwareSerial.h>

SoftwareSerial loraSerial(2, 3);

void setup() {
  Serial.begin(9600);
  loraSerial.begin(9600);
}

void loop() {
  loraSerial.println("Hello");
  delay(1000);
}
```

### After Custom Instructions
Copilot generates LoRa E220-specific code:
```cpp
#include "LoRa_E220.h"

// Configure for ESP32
LoRa_E220 e220ttl(&Serial2, 22, 4, 18, 21, 19, UART_BPS_RATE_9600);

void setup() {
  Serial.begin(9600);
  
  // Initialize LoRa module
  e220ttl.begin();
  
  // Get and display configuration
  ResponseStructContainer c = e220ttl.getConfiguration();
  Configuration configuration = *(Configuration*)c.data;
  
  Serial.println(c.status.getResponseDescription());
  Serial.println(configuration.getChannelDescription());
  
  c.close();
}

void loop() {
  ResponseStatus rs = e220ttl.sendMessage("Hello LoRa!");
  Serial.println(rs.getResponseDescription());
  delay(5000);
}
```

## Advanced Features

### Automated Testing
```bash
# MCP server can run these automatically
pio test -e native
arduino-cli compile --fqbn arduino:avr:uno examples/
```

### Multi-Platform Validation
```bash
# Test compilation across all platforms
for platform in uno esp32dev nodemcuv2; do
    pio run -e $platform
done
```

### Documentation Generation
With file system MCP access, Copilot can:
- Generate API documentation from code comments
- Update README with new examples
- Create platform-specific setup guides

## Benefits

1. **Context Awareness**: Copilot understands LoRa E220 specifics
2. **Build Integration**: Real-time compilation feedback
3. **Multi-Platform Support**: Automatic platform-specific code generation
4. **Error Resolution**: Intelligent debugging assistance
5. **Testing Automation**: Comprehensive test coverage

This integration transforms development from manual, error-prone processes to AI-assisted, automated workflows with comprehensive validation.