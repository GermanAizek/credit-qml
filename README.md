
# Сredit Manager C++

[![Licence](https://img.shields.io/badge/license-GPL-blue.svg?style=flat)](LICENSE)

This repository is a simple example of developing an application for a credit institution.
Solution implemented with C++ QML.

## License

Сredit Manager is licensed under the ([GNU General Public License 3.0](https://www.gnu.org/licenses/gpl-3.0.html))

## Requirments

- CMake
- Qt libraries
- Supported compilers:
    - GCC 4.8 - 11.0 (and possibly later)
    - Clang 3.4 - 11.0 (and possibly later)
    - Microsoft Visual C++ 2019 (and possibly later)
    
## Dependencies

- [picojson](https://github.com/kazuho/picojson) (header-only JSON parser)
- [Qt5 QML](https://doc.qt.io/qt-5/qtqml-index.html)
- [Qt5 Quick](https://doc.qt.io/qt-5/qtquick-index.html)
- [Qt5 Widgets](https://doc.qt.io/qt-5/qtwidgets-index.html)

## Building on Linux

execute all commands in the terminal

### Required Packages

#### Debian/Ubuntu
```
sudo apt-get install qt5-default git
```

#### Arch Linux
```
sudo pacman -Ss qt5-base git
```

#### Gentoo
```
emerge -av @qt5-essentials @dev-vcs/git
```

### Configure and build
```
git clone https://github.com/GermanAizek/credit-qml.git
cd credit-qml
mkdir build
cmake ../sources
make
```
## Building on Windows
### Configure and build

1) download any Windows git client and clone repository with url ( https://github.com/GermanAizek/credit-qml.git )

- Example:
  - download git client [git-scm.com](https://github.com/git-for-windows/git/releases/download/v2.30.0.windows.2/Git-2.30.0.2-64-bit.exe)
  - execute in cmd or powershell
  ```
  git clone https://github.com/GermanAizek/credit-qml.git
  cd credit-qml
  ```

2) download Qt5 for Windows: [official site](https://download.qt.io/official_releases/qt/5.12/5.12.10/qt-opensource-windows-x86-5.12.10.exe)

3) during the installation stage, select an optional component for your version of Visual Studio (example below)
![Installing a Component](https://github.com/GermanAizek/credit-qml/blob/main/docs/screenshots/qt_install_msvc.jpg)

4) execute in cmd or powershell
   ```
   mkdir build
   cmake -DQt5_DIR="<path to Qt lib cmake>" ../sources
   # Example: cmake -DQt5_DIR="C:/Qt/5.6/msvc2013_64/lib/cmake/Qt5" ../sources
   ```

5) open *.sln solution with Visual Studio
6) build projects and run it
