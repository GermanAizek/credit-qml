
# Сredit Manager C++

[![Licence](https://img.shields.io/badge/license-GPL-blue.svg?style=flat)](LICENSE)

This repository is a simple example of developing an application for a credit institution.
Solution implemented with C++ QML.

## License

Сredit Manager is licensed under the ([GNU General Public License 3.0](https://www.gnu.org/licenses/gpl-3.0.html))

## Requirments

- CMake
- Supported compilers:
    - GCC 4.8 - 11.0 (and possibly later)
    - Clang 3.4 - 11.0 (and possibly later)
    - Microsoft Visual C++ 2019 (and possibly later)
- Lightweight dependencies:
    - [picojson](https://github.com/kazuho/picojson)
    - Qt libraries:
        - [Qt5 QML](https://doc.qt.io/qt-5/qtqml-index.html)
        - [Qt5 Quick](https://doc.qt.io/qt-5/qtquick-index.html)
        - [Qt5 Widgets](https://doc.qt.io/qt-5/qtwidgets-index.html)

## Building

```
git clone https://github.com/GermanAizek/credit-qml.git
cd credit-qml
```

### Build on Linux

```
mkdir build
cmake ../sources
make
```

### Build on Windows

```
mkdir build
cmake ../sources
# open *.sln solution with Visual Studio 2019 and build it
```
