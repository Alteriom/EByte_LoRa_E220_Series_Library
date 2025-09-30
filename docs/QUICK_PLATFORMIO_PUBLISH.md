# 🚀 Quick PlatformIO Publishing Guide

## ⚡ **Fastest Path to Publishing**

### **Prerequisites**
```bash
pip install platformio
```

### **Step 1: Authenticate**
```bash
# Login to PlatformIO
pio account login

# Get your auth token (save this for GitHub Secrets)
pio account token
```

### **Step 2: Validate Library**
```bash
# From your library root directory
cd /path/to/EByte_LoRa_E220_Series_Library

# Validate library structure and configuration
pio pkg validate

# Create package (optional - for testing)
pio pkg pack --output ./dist
```

### **Step 3: Publish**
```bash
# Publish to PlatformIO Registry
pio pkg publish

# Or publish with force flag if needed
pio pkg publish --force
```

## 🔧 **Troubleshooting**

### **Common Fixes**

#### **Authentication Issues**
```bash
pio account logout
pio account login
pio account show  # Verify login
```

#### **Version Already Exists**
Update version in `library.json`:
```json
{
  "version": "1.1.7"  // Increment version
}
```

#### **Package Validation Errors**
Check library.json format:
```bash
python -c "import json; json.load(open('library.json'))"
```

### **Quick Test**
```bash
# Test if library can be found after publishing
pio lib search "Alteriom_EByte_LoRa_E220"

# Install test
mkdir test_install && cd test_install
pio project init --board esp32
echo "lib_deps = alteriom/Alteriom_EByte_LoRa_E220" >> platformio.ini
pio lib install
```

## 📋 **Manual Workflow**

If automated publishing doesn't work:

1. **Test compilation locally** (recommended):
   ```bash
   # Run the test workflow manually
   git push  # Triggers test-platformio.yml workflow
   ```

2. **Check GitHub Actions** for any compilation issues

3. **Fix any errors** found in testing

4. **Publish manually**:
   ```bash
   pio pkg validate
   pio pkg publish
   ```

## 🎯 **Success Verification**

After publishing:
```bash
# Verify library is available
pio lib search "Alteriom_EByte_LoRa_E220"

# Check registry page
open https://registry.platformio.org/libraries/alteriom/Alteriom_EByte_LoRa_E220
```

## 📦 **Installation for Users**

Once published, users can install via:

**platformio.ini:**
```ini
lib_deps = alteriom/Alteriom_EByte_LoRa_E220@^1.1.6
```

**CLI:**
```bash
pio lib install "alteriom/Alteriom_EByte_LoRa_E220"
```

---

💡 **Tip**: Run the test workflow first to catch any issues before publishing!