# Qt/QML Calculator

A modern, feature-rich calculator application built with Qt 6 and QML, featuring a sleek digital display and comprehensive arithmetic operations.

## 🌟 Features

- **Basic Operations**: Addition, subtraction, multiplication, and division
- **Advanced Operations**: 
  - Square root (√)
  - Square (x²)
  - Percentage (%)
- **Error Handling**: 
  - Division by zero protection
  - Negative square root detection
  - Overflow and infinity handling
- **User Experience**:
  - Digital font display (DS-DIGIB)
  - Intuitive button layout
  - Visual operator feedback
  - Backspace/delete functionality
  - Clear/reset functionality

## 🚀 Getting Started

### Prerequisites

- Qt 6.8.3 or later
- CMake 3.16 or later
- C++17 compatible compiler

### Building the Application

1. **Clone the repository:**
   ```bash
   git clone https://github.com/faelbluhm/SimpleQalculator
   cd SimpleQalculator
   ```

2. **Create build directory:**
   ```bash
   mkdir build && cd build
   ```

3. **Configure and build:**
   ```bash
   cmake ..
   make
   ```

4. **Run the application:**
   ```bash
   ./calculator
   ```

### Alternative: Using Qt Creator

1. Open `CMakeLists.txt` in Qt Creator
2. Configure the project with your Qt kit
3. Build and run (Ctrl+R)

## 🏗️ Architecture

The application follows a clean separation of concerns:

- **CalculatorLogic** (C++): Core calculation engine and business logic
- **Main.qml**: User interface and visual components
- **Signal/Slot Pattern**: Qt's signal-slot system for UI-logic communication

### Key Components

```
├── calculatorlogic.h/cpp    # Core calculator logic
├── main.cpp                 # Application entry point
├── Main.qml                 # QML user interface
├── fonts/DS-DIGIB.TTF      # Digital display font
└── CMakeLists.txt          # Build configuration
```

## 🎮 Usage

### Basic Operations
- Click number buttons (0-9) to input values
- Use +, -, ×, ÷ for basic arithmetic
- Press = to calculate results

### Advanced Operations
- **√**: Square root of current number
- **x²**: Square of current number
- **%**: Percentage calculation

### Controls
- **C**: Clear all and reset
- **⌫**: Delete last digit
- **.**: Decimal point

### Error Messages
- `Error: DIV 0`: Division by zero
- `Error: √-`: Square root of negative number
- `Error: OB`: Number too large for display
- `Error: Inf`: Result is infinity

## 🛠️ Development

### Code Structure

The calculator uses a state-machine approach with the following key states:
- Display text management
- Operator precedence handling
- Error state management
- Input validation

### Key Classes

**CalculatorLogic**
- Handles all mathematical operations
- Manages calculator state
- Provides Qt property bindings for QML
- Implements comprehensive error handling

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request. For major changes, please open an issue first to discuss what you would like to change.

### Development Guidelines
- Follow Qt coding conventions
- Ensure all operations have appropriate error handling
- Add unit tests for new functionality
- Update documentation as needed

## 📝 License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE](LICENSE) file for details.

### GPL v3 Summary
- ✅ Commercial use
- ✅ Modification
- ✅ Distribution
- ✅ Patent use
- ✅ Private use
- ❌ Liability
- ❌ Warranty
- 📋 License and copyright notice required
- 📋 State changes required
- 📋 Disclose source required
- 📋 Same license required

## 🙏 Acknowledgments

- Qt Framework for the excellent development platform
- DS-DIGIB font for the authentic digital calculator display
- The open-source community for inspiration and best practices

## 📞 Support

If you encounter any issues or have questions:
1. Check the issues page
2. Create a new issue with detailed information
3. Include your Qt version and operating system

---

**Made with ❤️ using Qt 6 and QML**
