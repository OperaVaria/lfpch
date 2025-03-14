# Lightning-Fast Password Check

LFPCh is a small, cross-platform GUI application to check if your password is safe to use. The program conducts a two-step security check:
In step one, the password's quality is evaluated based on its length and character variety. In step two, the app checks whether
the password was part of an earlier data breach through the haveibeenpwned.com API. LFPCh provides an extra layer of security
compared to using the website directly, as the password data never actually leaves the computer. Implementing a k-Anonymity model,
only the first five characters of the password's SHA1 hash is ever sent to the haveibeenpwned server, making its decoding impossible,
even if it is somehow intercepted. The application also includes a random password generator that creates a secure password, customizable
in accordance with the user's needs. The random generation is based on a "true" random seed provided by the x86 processor's DRNG unit.

LFPCh was written entirely in C with speed and efficiency in mind. Its simple, GTK4 UI aims to provide a clean and easy-to-use interface.

## Screenshots

<p align="center">
  <img src="./assets/screenshots/lnx_screen.jpg" alt="Linux Screenshot" height=auto width="700">
  <img src="./assets/screenshots/win_screen.jpg" alt="Windows Screenshot" height=auto width="700">
</p>

## Installation

The easiest and cleanest way to install LFPCh is via the binary packages located in the repository's ['bin/' directory](https://github.com/OperaVaria/lfpch/tree/main/bin).
These are set up to download and install the required dependencies automatically.

### Linux (Debian-based)

Download the latest version of the .deb package from ['/bin/Linux'](https://github.com/OperaVaria/lfpch/tree/main/bin/Linux), and use you distribution's GUI package installer
(e.g. GDebi, Deb Installer etc.), or run the following commands in the terminal:

```bash
cd /location/of/deb_file
sudo dpkg -i packagename.deb
```

The app can now be launched form the OS's application menu or by typing the "lfpch" command into the terminal.

### Windows

The Windows installation uses the [MSYS2](https://www.msys2.org/) platform with the UCRT64 environment to get the required dependencies.
Download the latest version of the .pkg.tar.zst package from ['/bin/Windows'](https://github.com/OperaVaria/lfpch/tree/main/bin/Windows) and run the following commands in the MYSYS shell:

```bash
cd /location/of/pkg_file
pacman -U packagename.pkg.tar.zst
```

The app can now be launched form the newly created desktop shortcut.

## Building

The building (and optional installation) process is done via the [Meson build system](https://mesonbuild.com/index.html),
version 1.5.0 is required. Meson does include a built-in pseudo-package manager called [WrapDB](https://mesonbuild.com/Wrapdb-projects.html)
to download and compile dependencies, but this takes a very long time to complete. **We recommend these steps instead:**

### Dependencies

The application depends on the following shared libraries:

- glib-2.0
- gtk4
- libcrypto
- libcurl

A faster and easier way to procure these libraries is to install the packages containing them through a package manager.

On Linux (Debian-based), run the following commands in the terminal:

  ```bash
  sudo apt update
  sudo apt install -y libglib2.0-dev libgtk-4-dev libssl-dev libcurl4-openssl-dev
  ```

On Windows, you can use [MSYS2](https://www.msys2.org/) to get the packages. This example is for the UCRT64 environment:

```bash
pacman -S mingw-w64-ucrt-x86_64-glib2 mingw-w64-ucrt-x86_64-gtk4 mingw-w64-ucrt-x86_64-openssl mingw-w64-ucrt-x86_64-curl
```

### Compilation

LFPCh can be built and installed on both OS families with Meson. After downloading and unpacking the source directory,
enter the following into the terminal:

```bash
cd /project/source/directory
meson setup builddir
meson install -C builddir
```

With the Meson install method, on Linux, the app installs to the conventional Unix filesystem locations
('/usr/bin' and '/usr/share'), and can be run with the "lfpch" command.
On Windows, the target directory for all files is 'C:\Tools\lfpch'.

## Other

**Tested on:** Ubuntu 24.04, MX Linux 23.4, and Windows 11.

**Note:** The application's random generator depends on an x86 specific assembly instruction, therefore it will not work on different architectures.

App icon from ["Internet & Security icon pack"](https://www.iconfinder.com/iconsets/internet-security-flat-2) by [Kmg Design](https://www.iconfinder.com/kmgdesignid)

**[Contact](mailto:lcs_it@proton.me)**

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
