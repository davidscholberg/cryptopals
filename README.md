# Cryptopals Crypto Challenges

These are my solutions to the [Cryptopals Crypto Challenges][cryptopals-site] (no, this is not some cryptocurrency nonsense). The solutions are written in [C][c-lang].

[cryptopals-site]: https://cryptopals.com/
[c-lang]: https://en.wikipedia.org/wiki/C_(programming_language)

### Development Setup

To build and run this project, you'll need a C compiler and [CMake][cmake]. For example, if you want to use [GCC][gcc] on [Fedora Linux][fedora], you would run the following:

```bash
sudo dnf install gcc cmake
```

Building the project will depend on how your development environment handles CMake. Refer to the relevant documentation for instructions.


[cmake]: https://cmake.org/
[gcc]: https://gcc.gnu.org/
[fedora]: https://fedoraproject.org/

### Running Solutions

You can run the solution for a particular challenge by passing the challenge number to the compiled binary:

```bash
./build/cryptopals 1
```
