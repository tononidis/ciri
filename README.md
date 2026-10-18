# Ciri
This is a C++ serialization libirary that uses a reflection system to serialize and deserialize objects.

## Supported types
- Primitive types (int, float, double, char, bool, etc.)
- std::string
- std::vector
- raw pointers (make sure you allocate memory before serialization/deserialization)

## Usage
I am going to be honest here, there is no practical usage for this library yet.

The current support of C++26 features as I write this message is lacking behind.

Maybe in year 2056 when support is available and AI did not manage to replace us, we might find a use of this library in production code.

Until then, this library is just playground for me and you to learn and experiment with C++26 features.

If you somehow find this library useful, please let me know, i would love to hear your feedback.

## Building
Install gcc 16.1 or higher and set it to CXX environment variable.

The Ciri library uses cmake to generate the config files needed and ninja (or you can use your preferred build system) to build it.

```
cmake -G Ninja -B build -S .
ninja -C build
```

## Future Plans
If I wont get bored of this project fast, I will continue to work on it and add more features at a painfully slow pace.

- Add support to most if not all stl containers
- Support static member serialization for classes/structs
- Add testing

## Contributing
If you want to contribute to this project, read the CONTRIBUTING.md file and create a pull request.

## Docs (Not tested yet)
Use the doxygen tool to generate the code documentation.
```
doxygen docs/Doxyfile
```