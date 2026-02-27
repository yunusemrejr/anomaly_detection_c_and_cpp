# Changelog

All notable changes to the Anomaly Detection Software are documented in this file.

## [2.0.0] - 2026-02-27

### 🎉 Major Release - Complete Modernization

This release represents a complete overhaul of the anomaly detection software, transforming it from a basic demonstration tool into a professional, production-ready application.

### ✨ Added

#### Detection Algorithms
- **IQR Method**: Interquartile Range-based detection for robust outlier identification
- **MAD Method**: Median Absolute Deviation for highly robust detection
- **Modified Z-Score**: Enhanced Z-score using MAD for better outlier resistance
- Configurable thresholds for all detection methods

#### CLI Features
- Complete command-line argument parsing system
- File input support (`-i, --input`)
- File output support (`-o, --output`)
- Method selection (`-m, --method`)
- Output format selection (`-f, --format`)
- Threshold configuration (`-t, --threshold`)
- Column selection (`-c, --columns`)
- Header row support (`--header`)
- Verbose mode (`-v, --verbose`)
- Help system (`-h, --help`)
- Version information (`--version`)

#### Output Formats
- **Terminal**: Colorized, formatted output with Unicode box drawing
- **JSON**: Machine-readable format with complete statistics
- **CSV**: Tabular format for spreadsheet import

#### Statistics
- Median calculation
- Quartiles (Q1, Q3)
- Interquartile Range (IQR)
- Median Absolute Deviation (MAD)
- Min/Max values
- Anomaly scores and confidence levels
- Detailed reasoning for each detection

#### Data Handling
- Professional CSV parser with quote support
- Column selection for multi-dimensional data
- Header row detection and skipping
- Graceful handling of invalid values
- Support for large datasets

#### Documentation
- Comprehensive README with examples
- Build instructions for multiple platforms
- Detailed improvements documentation
- Sample datasets (3 different use cases)
- Usage examples for common scenarios
- Architecture documentation

#### Development
- Modular code architecture
- Separate header files for each component
- C++17 modern features
- Enhanced Makefile with test targets
- Build script for systems without make
- Error handling throughout

### 🔧 Changed

#### Core Functionality
- Upgraded from C++11 to C++17
- Refactored main.cpp for better organization
- Improved memory management
- Enhanced error messages
- Better input validation

#### Build System
- Updated Makefile for new source files
- Added optimization flags (-O2)
- Improved build output
- Added test and help targets

#### User Interface
- Replaced asterisk borders with Unicode box drawing
- Added color-coded output
- Improved error messages
- Better progress indication

### 🐛 Fixed
- CSV parsing edge cases
- Memory leaks in feature extraction
- Input validation issues
- Error handling in file operations

### 📚 Documentation
- Complete rewrite of README.md
- Added BUILD_INSTRUCTIONS.md
- Added IMPROVEMENTS.md
- Added CHANGELOG.md
- Inline code documentation improvements

### 🎯 Backward Compatibility
- Maintained stdin input support
- Legacy functions preserved
- Original detection algorithm available as default
- Existing workflow compatibility

---

## [1.0.0] - Original Release

### Initial Features
- Basic Z-score anomaly detection
- CSV input via stdin
- Console output
- Mean and standard deviation calculation
- Simple preprocessing
- Feature extraction
- C/C++ mixed implementation

---

## Version Numbering

This project follows [Semantic Versioning](https://semver.org/):
- MAJOR version for incompatible API changes
- MINOR version for added functionality (backward compatible)
- PATCH version for backward compatible bug fixes

---

## Future Roadmap

### [2.1.0] - Planned
- [ ] Configuration file support (JSON/YAML)
- [ ] Real-time streaming data mode
- [ ] Additional statistical methods
- [ ] Performance benchmarks

### [2.2.0] - Planned
- [ ] Machine learning-based detection
- [ ] Visualization output (SVG/PNG charts)
- [ ] Multi-threaded processing
- [ ] Database connectivity

### [3.0.0] - Future
- [ ] REST API interface
- [ ] Web dashboard
- [ ] Plugin system for custom detectors
- [ ] Distributed processing support
