Unix Crypt Native Bindings
============================

This repository provides native bindings to the `crypt` library that is usually included in UNIX/Linux distributions. This utility is used for hashing passwords in order to securely store information such as login credentials,...

It is used as a hashing mechanism for the `/etc/shadow` file, as well as in other software such as Dovecot.

## API

The API provides by this library consists of two functions: `crypt` and `gensalt`.
The former accepts two parameters: a phrase and a setting, which work as describe on the `crypt(3)` man-page.
The latter functions like `crypt_gensalt(3)`, but only requires two arguments: the hashing prefix and a difficulty(= count). See the relevant man-page for more information.

An example of the API usage can be found in the `test/` directory.

## Platform support

The library has been tested on an `ArchLinux x86_64` machine, and NodeJS version 16 (LTS).
Its entrypoint contains a hard-coded reference to a build of the library for that Node.js version. 
Contributions are welcome to automate the build process such that the library can be built from source regardless of the platform, or to support a larger number of pre-built Node version and architectures.
