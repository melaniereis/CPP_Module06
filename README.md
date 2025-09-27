# 🔄 CPP Module 06 - Casts

<div align="center">

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![42 School](https://img.shields.io/badge/42-School-000000?style=for-the-badge&logo=42&logoColor=white)
![Module](https://img.shields.io/badge/Module-06-blue?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)

*Mastering Type Conversions and Cast Operators*

</div>

## 📖 Overview

**CPP Module 06** explores the intricate world of **type conversions** and **cast operators** in C++. Through scalar conversions, serialization, and runtime type identification, you'll master the four fundamental C++ casts and understand when and how to safely convert between different data types while maintaining type safety.

### 🎯 Learning Objectives

- Master the four C++ cast operators and their appropriate usage
- Implement safe scalar type conversions with validation
- Understand pointer serialization and deserialization
- Learn runtime type identification with dynamic_cast
- Practice type safety and conversion error handling
- Explore reinterpret_cast for low-level memory operations
- Implement robust type checking and validation systems

## 💡 Key Concepts Introduced

- **Static Cast**: Safe conversions between related types
- **Dynamic Cast**: Runtime type checking for polymorphic types
- **Const Cast**: Adding or removing const qualifiers
- **Reinterpret Cast**: Low-level bit pattern reinterpretation
- **Type Safety**: Preventing dangerous type conversions
- **Serialization**: Converting objects to/from raw data
- **RTTI**: Runtime Type Information and identification

## 🎭 The Four Cast Operators

### `static_cast<T>()`
- **Purpose**: Safe, checked conversions between related types
- **Usage**: Numeric conversions, base-to-derived (when safe)
- **Check**: Compile-time validation

### `dynamic_cast<T>()`
- **Purpose**: Safe downcasting with runtime type checking
- **Usage**: Polymorphic type conversions
- **Check**: Runtime validation, returns nullptr on failure

### `const_cast<T>()`
- **Purpose**: Add or remove const/volatile qualifiers
- **Usage**: Interfacing with legacy code
- **Warning**: Use sparingly, can break const correctness

### `reinterpret_cast<T>()`
- **Purpose**: Low-level bit pattern reinterpretation
- **Usage**: Pointer-to-integer conversions, platform-specific code
- **Warning**: Dangerous, bypasses type system

## 🚀 Exercises

### 🔢 Exercise 00: Conversion of Scalar Types
**Files**: `ScalarConverter.cpp`, `ScalarConverter.hpp`, `main.cpp`

Comprehensive scalar type conversion system with validation, demonstrating:
- Static cast for safe numeric conversions
- Input validation and type detection
- Conversion between char, int, float, and double
- Special value handling (inf, nan, pseudo-literals)
- Error handling and impossible conversion detection

**ScalarConverter Class**:
```cpp
class ScalarConverter {
public:
    static void convert(const std::string &input);

private:
    ScalarConverter();                        // Static class - no instances
    ~ScalarConverter();
    ScalarConverter(const ScalarConverter &other);
    ScalarConverter &operator=(const ScalarConverter &other);

    // Type detection functions
    static bool isChar(const std::string &str);
    static bool isInt(const std::string &str);
    static bool isFloat(const std::string &str);
    static bool isDouble(const std::string &str);
    static bool isPseudoLiteral(const std::string &str);

    // Conversion functions
    static void convertFromChar(const std::string &str);
    static void convertFromInt(const std::string &str);
    static void convertFromFloat(const std::string &str);
    static void convertFromDouble(const std::string &str);
    static void convertPseudoLiteral(const std::string &str);

    // Output functions
    static void printChar(double value);
    static void printInt(double value);
    static void printFloat(double value);
    static void printDouble(double value);
};
```

**Type Detection Logic**:
```cpp
bool ScalarConverter::isChar(const std::string &str) {
    return (str.length() == 1 && isprint(str[0]) && !isdigit(str[0]));
}

bool ScalarConverter::isInt(const std::string &str) {
    if (str.empty()) return false;

    size_t start = (str[0] == '+' || str[0] == '-') ? 1 : 0;
    if (start >= str.length()) return false;

    for (size_t i = start; i < str.length(); i++) {
        if (!isdigit(str[i])) return false;
    }
    return true;
}

bool ScalarConverter::isFloat(const std::string &str) {
    if (str.length() < 2 || str[str.length() - 1] != 'f') return false;

    std::string without_f = str.substr(0, str.length() - 1);
    return isValidNumber(without_f);
}
```

**Conversion Implementation**:
```cpp
void ScalarConverter::convert(const std::string &input) {
    if (input.empty()) {
        std::cout << ERROR_EMPTY << std::endl;
        return;
    }

    // Type detection with function pointer array
    CheckFunc checkers[] = {
        &ScalarConverter::isChar,
        &ScalarConverter::isInt,
        &ScalarConverter::isFloat,
        &ScalarConverter::isDouble,
        &ScalarConverter::isPseudoLiteral
    };

    ConvertFunc converters[] = {
        &ScalarConverter::convertFromChar,
        &ScalarConverter::convertFromInt,
        &ScalarConverter::convertFromFloat,
        &ScalarConverter::convertFromDouble,
        &ScalarConverter::convertPseudoLiteral
    };

    for (int i = 0; i < 5; i++) {
        if (checkers[i](input)) {
            converters[i](input);
            return;
        }
    }

    std::cout << ERROR_INVALID_FORMAT << std::endl;
}
```

**Safe Static Cast Usage**:
```cpp
void ScalarConverter::convertFromInt(const std::string &str) {
    long long value = std::strtoll(str.c_str(), NULL, 10);

    // Check for overflow
    if (value > std::numeric_limits<int>::max() ||
        value < std::numeric_limits<int>::min()) {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: impossible" << std::endl;
        std::cout << "double: impossible" << std::endl;
        return;
    }

    int intValue = static_cast<int>(value);
    double doubleValue = static_cast<double>(intValue);

    printChar(doubleValue);
    std::cout << "int: " << intValue << std::endl;
    std::cout << "float: " << static_cast<float>(doubleValue) << "f" << std::endl;
    std::cout << "double: " << doubleValue << std::endl;
}
```

**Special Value Handling**:
```cpp
void ScalarConverter::convertPseudoLiteral(const std::string &str) {
    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;

    if (str == "inff" || str == "+inff") {
        std::cout << "float: +inff" << std::endl;
        std::cout << "double: +inf" << std::endl;
    } else if (str == "-inff") {
        std::cout << "float: -inff" << std::endl;
        std::cout << "double: -inf" << std::endl;
    } else if (str == "nanf") {
        std::cout << "float: nanf" << std::endl;
        std::cout << "double: nan" << std::endl;
    }
    // Handle double versions...
}
```

**Usage Examples**:
```bash
./scalar_converter "42"
# Output:
# char: '*'
# int: 42
# float: 42.0f
# double: 42.0

./scalar_converter "42.0f"
# Output:
# char: '*'
# int: 42
# float: 42.0f
# double: 42.0

./scalar_converter "inff"
# Output:
# char: impossible
# int: impossible
# float: +inff
# double: +inf
```

**Key Learning Points**:
- Static cast for safe numeric conversions
- Type detection and validation algorithms
- Special floating-point value handling
- Error reporting and impossible conversion detection
- Function pointer arrays for dispatch

---

### 🔐 Exercise 01: Serialization
**Files**: `Serializer.cpp`, `Serializer.hpp`, `Data.cpp`, `Data.hpp`, `main.cpp`

Pointer serialization and deserialization using reinterpret_cast, showcasing:
- Reinterpret cast for pointer-to-integer conversion
- Data integrity preservation across serialization
- Static utility class design
- Serialization round-trip testing

**Data Structure**:
```cpp
class Data {
public:
    Data();
    Data(const std::string &name, const std::string &profession, int id);
    Data(const Data &other);
    Data &operator=(const Data &other);
    ~Data();

    // Getters
    const std::string &getName() const;
    const std::string &getProfession() const;
    int getId() const;

    // Setters
    void setName(const std::string &name);
    void setProfession(const std::string &profession);
    void setId(int id);

    // Utility
    void display() const;
    bool operator==(const Data &other) const;

private:
    std::string _name;
    std::string _profession;
    int _id;
};
```

**Serializer Class** (Static Utility):
```cpp
class Serializer {
public:
    static uintptr_t serialize(Data *ptr);
    static Data *deserialize(uintptr_t raw);

private:
    Serializer();                             // Static class - no instances
    ~Serializer();
    Serializer(const Serializer &other);
    Serializer &operator=(const Serializer &other);
};
```

**Serialization Implementation**:
```cpp
uintptr_t Serializer::serialize(Data *ptr) {
    return reinterpret_cast<uintptr_t>(ptr);
}

Data *Serializer::deserialize(uintptr_t raw) {
    return reinterpret_cast<Data *>(raw);
}
```

**Comprehensive Testing**:
```cpp
void testSerialization() {
    // Create original data
    Data *original = new Data("Alice Johnson", "Software Engineer", 12345);
    std::cout << "Original Data:" << std::endl;
    original->display();

    // Serialize to integer
    uintptr_t serialized = Serializer::serialize(original);
    std::cout << "\nSerialized address: 0x" << std::hex << serialized << std::dec << std::endl;

    // Deserialize back to pointer
    Data *deserialized = Serializer::deserialize(serialized);
    std::cout << "\nDeserialized Data:" << std::endl;
    deserialized->display();

    // Verify integrity
    std::cout << "\nIntegrity Check:" << std::endl;
    std::cout << "Pointers equal: " << (original == deserialized) << std::endl;
    std::cout << "Data equal: " << (*original == *deserialized) << std::endl;
    std::cout << "Same memory address: " << (original == deserialized) << std::endl;

    // Cleanup
    delete original;  // Note: original and deserialized point to same memory
}
```

**Advanced Serialization Tests**:
```cpp
void testMultipleSerialization() {
    std::vector<Data*> dataVector;
    std::vector<uintptr_t> serializedVector;

    // Create multiple data objects
    dataVector.push_back(new Data("Bob Smith", "Designer", 67890));
    dataVector.push_back(new Data("Carol Wilson", "Manager", 11111));
    dataVector.push_back(new Data("Dave Brown", "Tester", 22222));

    // Serialize all
    for (size_t i = 0; i < dataVector.size(); i++) {
        serializedVector.push_back(Serializer::serialize(dataVector[i]));
    }

    // Deserialize and verify
    for (size_t i = 0; i < serializedVector.size(); i++) {
        Data *restored = Serializer::deserialize(serializedVector[i]);
        std::cout << "Object " << i << " integrity: "
                  << (dataVector[i] == restored) << std::endl;
    }

    // Cleanup
    for (size_t i = 0; i < dataVector.size(); i++) {
        delete dataVector[i];
    }
}
```

**Key Learning Points**:
- Reinterpret cast for pointer-to-integer conversions
- Data integrity preservation across serialization
- Static utility class design patterns
- Memory address preservation and validation
- Round-trip serialization testing

---

### 🎯 Exercise 02: Identify Real Type
**Files**: `Base.cpp`, `Base.hpp`, `main.cpp`

Runtime type identification using dynamic_cast, demonstrating:
- Dynamic cast for safe downcasting
- Runtime type information (RTTI)
- Polymorphic type identification
- Exception handling in type identification

**Polymorphic Class Hierarchy**:
```cpp
class Base {
public:
    virtual ~Base();                          // Virtual destructor for RTTI
};

class A : public Base {};
class B : public Base {};
class C : public Base {};
```

**Factory Function**:
```cpp
Base *generate(void) {
    static bool seeded = false;
    if (!seeded) {
        std::srand(std::time(NULL));
        seeded = true;
    }

    // Factory function pointer array
    Base* (*creators[])() = {
        []() -> Base* { return new A; },
        []() -> Base* { return new B; },
        []() -> Base* { return new C; }
    };

    int random = std::rand() % 3;
    std::cout << "Generated type: " << (char)('A' + random) << std::endl;
    return creators[random]();
}
```

**Type Identification Functions**:

#### By Pointer (Safe):
```cpp
void identify(Base* p) {
    if (p == NULL) {
        std::cout << "Error: Null pointer provided" << std::endl;
        return;
    }

    std::cout << "Identifying by pointer: ";

    // Try dynamic_cast to each derived type
    if (dynamic_cast<A*>(p)) {
        std::cout << "A" << std::endl;
    } else if (dynamic_cast<B*>(p)) {
        std::cout << "B" << std::endl;
    } else if (dynamic_cast<C*>(p)) {
        std::cout << "C" << std::endl;
    } else {
        std::cout << "Unknown type" << std::endl;
    }
}
```

#### By Reference (Exception-Based):
```cpp
void identify(Base& p) {
    std::cout << "Identifying by reference: ";

    // Try dynamic_cast with references - throws std::bad_cast on failure
    try {
        (void)dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
        return;
    } catch (const std::bad_cast&) {}

    try {
        (void)dynamic_cast<B&>(p);
        std::cout << "B" << std::endl;
        return;
    } catch (const std::bad_cast&) {}

    try {
        (void)dynamic_cast<C&>(p);
        std::cout << "C" << std::endl;
        return;
    } catch (const std::bad_cast&) {}

    std::cout << "Unknown type" << std::endl;
}
```

**Comprehensive Testing**:
```cpp
void testTypeIdentification() {
    std::cout << "=== Type Identification Tests ===" << std::endl;

    // Test multiple random generations
    for (int i = 0; i < 10; i++) {
        std::cout << "\nTest " << (i + 1) << ":" << std::endl;

        Base *obj = generate();

        // Test both identification methods
        identify(obj);      // By pointer
        identify(*obj);     // By reference

        delete obj;
    }
}
```

**Advanced Testing with Known Types**:
```cpp
void testKnownTypes() {
    std::cout << "\n=== Known Type Tests ===" << std::endl;

    Base *objects[] = {
        new A(),
        new B(),
        new C()
    };

    const char types[] = {'A', 'B', 'C'};

    for (int i = 0; i < 3; i++) {
        std::cout << "\nTesting known type " << types[i] << ":" << std::endl;
        identify(objects[i]);
        identify(*objects[i]);
        delete objects[i];
    }
}
```

**Edge Case Testing**:
```cpp
void testEdgeCases() {
    std::cout << "\n=== Edge Case Tests ===" << std::endl;

    // Test null pointer
    std::cout << "Testing null pointer:" << std::endl;
    Base *nullPtr = NULL;
    identify(nullPtr);

    // Test base class instance (if allowed)
    std::cout << "\nTesting base class:" << std::endl;
    Base *base = new Base();  // If concrete base allowed
    identify(base);
    identify(*base);
    delete base;
}
```

**Key Learning Points**:
- Dynamic cast for runtime type checking
- Difference between pointer and reference dynamic_cast
- Exception handling with std::bad_cast
- Runtime Type Information (RTTI) usage
- Safe downcasting techniques

## 🛠️ Compilation

Each exercise includes a Makefile with standard targets:

```bash
# Compile the program
make

# Clean object files
make clean

# Clean everything
make fclean

# Recompile
make re
```

**Compilation flags**:
```bash
c++ -Wall -Wextra -Werror -std=c++98
```

## 🎮 How to Run

### Exercise 00 - Conversion of Scalar Types
```bash
cd ex00
make
./scalar_converter "42"
./scalar_converter "42.0f"
./scalar_converter "'a'"
./scalar_converter "inff"
```

### Exercise 01 - Serialization
```bash
cd ex01
make
./serializer
```

### Exercise 02 - Identify Real Type
```bash
cd ex02
make
./identify
```

## 🧪 Testing Examples

### Scalar Conversion Test
```bash
# Test various input types
./scalar_converter "0"          # char: Non displayable, int: 0, float: 0.0f, double: 0.0
./scalar_converter "127"        # char: '\x7f', int: 127, float: 127.0f, double: 127.0
./scalar_converter "128"        # char: impossible, int: 128, float: 128.0f, double: 128.0
./scalar_converter "42.0f"      # char: '*', int: 42, float: 42.0f, double: 42.0
./scalar_converter "'z'"        # char: 'z', int: 122, float: 122.0f, double: 122.0
./scalar_converter "inff"       # char: impossible, int: impossible, float: +inff, double: +inf
```

### Serialization Integrity Test
```cpp
Data original("Test User", "Developer", 123);
uintptr_t serialized = Serializer::serialize(&original);
Data *restored = Serializer::deserialize(serialized);
assert(&original == restored);  // Same memory address
```

### Dynamic Cast Test
```cpp
Base *obj = generate();
A *a_ptr = dynamic_cast<A*>(obj);
if (a_ptr) {
    std::cout << "Successfully cast to A" << std::endl;
} else {
    std::cout << "Not an A object" << std::endl;
}
```

## 🏗️ Project Structure

```
CPP_Module06/
├── README.md
├── ex00/                    # Conversion of Scalar Types
│   ├── Makefile
│   ├── inc/
│   │   ├── ansi.h
│   │   └── ScalarConverter.hpp
│   └── src/
│       ├── ScalarConverter.cpp
│       └── main.cpp
├── ex01/                    # Serialization
│   ├── Makefile
│   ├── inc/
│   │   ├── ansi.h
│   │   ├── Serializer.hpp
│   │   └── Data.hpp
│   └── src/
│       ├── Serializer.cpp
│       ├── Data.cpp
│       └── main.cpp
└── ex02/                    # Identify Real Type
    ├── Makefile
    ├── inc/
    │   ├── ansi.h
    │   └── Base.hpp
    └── src/
        ├── Base.cpp
        └── main.cpp
```

## 💡 Key Takeaways

1. **Cast Safety**: Understanding when each cast operator is appropriate
2. **Type Safety**: Maintaining type safety while performing conversions
3. **Runtime Checking**: Using dynamic_cast for safe downcasting
4. **Serialization**: Converting objects to/from raw data safely
5. **RTTI**: Leveraging runtime type information effectively
6. **Error Handling**: Proper validation and error reporting in conversions
7. **Static Design**: Creating utility classes with static-only interfaces

## 🎯 Skills Developed

- ✅ Four C++ cast operators mastery
- ✅ Safe scalar type conversions
- ✅ Pointer serialization techniques
- ✅ Runtime type identification
- ✅ Dynamic cast exception handling
- ✅ Input validation and error handling
- ✅ Static utility class design
- ✅ Type safety preservation techniques

## ⚠️ Cast Usage Guidelines

### `static_cast<T>()`
- ✅ **Use for**: Numeric conversions, explicit type conversions
- ✅ **Safe when**: Types are related, conversion is well-defined
- ❌ **Avoid for**: Unrelated pointer types, const removal

### `dynamic_cast<T>()`
- ✅ **Use for**: Safe downcasting, type identification
- ✅ **Requires**: Virtual functions (RTTI enabled)
- ❌ **Avoid for**: Non-polymorphic types, performance-critical code

### `const_cast<T>()`
- ✅ **Use for**: Interfacing with legacy APIs
- ⚠️ **Caution**: Can break const correctness
- ❌ **Never**: Modify originally const objects

### `reinterpret_cast<T>()`
- ⚠️ **Use sparingly**: Platform-specific code, serialization
- ⚠️ **Dangerous**: Bypasses type system completely
- ❌ **Avoid**: Unless absolutely necessary and well-documented

## 🔗 Type Safety Best Practices

1. **Prefer static_cast**: Use for most conversions
2. **Validate inputs**: Check ranges and validity
3. **Handle failures**: dynamic_cast can return nullptr
4. **Document intent**: Explain why specific casts are used
5. **Test thoroughly**: Verify conversion accuracy
6. **Avoid C-style casts**: Use explicit C++ casts
7. **Consider alternatives**: Maybe redesign instead of casting

## 🔗 Common Pitfalls & Solutions

1. **Implicit Conversions**: Be explicit about type conversions
2. **Precision Loss**: Check numeric conversion ranges
3. **Null Pointers**: Always validate dynamic_cast results
4. **Const Violations**: Avoid const_cast unless absolutely necessary
5. **Platform Dependencies**: Document reinterpret_cast usage
6. **Performance**: dynamic_cast has runtime overhead
7. **Exception Safety**: Handle bad_cast exceptions properly

## 🔗 Next Steps

After mastering Module 06, you'll be ready to tackle:
- **Module 07**: Templates and generic programming
- **Module 08**: STL containers and iterators
- **Module 09**: Advanced STL algorithms and performance

---

<div align="center">

*"Type safety is not a restriction, it's a foundation for reliable software."*

**Module 06 Complete** ✨ | **Previous**: [← Module 05](https://github.com/melaniereis/CPP_Module05/) | **Next**: [Module 07 →](https://github.com/melaniereis/CPP_Module07/)

</div>
