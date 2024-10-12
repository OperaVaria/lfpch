# Lightning-Fast Password Check

LFPCh is a small, cross-platform GUI application to check if your password is safe to use. The program conducts a two-step security check:
In step one, the password's quality is evaluated based on its length and character variety. In step two, the app checks whether
the password was part of an earlier data breach through the haveibeenpwned.com API. LFPCh provides an extra layer of security
compared to using the website directly, as the password data never actually leaves the computer. Implementing a k-Anonymity model,
only the first five characters of the password's sha1 hash is ever sent to the haveibeenpwned server, making its decoding impossible,
even if it is somehow intercepted. The application also includes a random password generator that creates a secure password, customizable
in accordance with the user's needs. The random generation is based on a "true" random seed provided by the x86 processor's DRNG unit.

LFCh was written entirely in C with speed and efficiency in mind. Its simple, GTK4 UI aims to provide a clean and easy-to-use interface.

The application utilizes the following libraries:

- Gtk4 for the user interface
- cURL for HTTP requests
- OpenSSL for hashing

Tested on: MX Linux 23.4 and Windows 11.

Important: the application's random generation depends on an x86 specific assembly instruction, therefore it will not work on a different architecture.

---

**[Contact](mailto:lcs_it@proton.me)**

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
