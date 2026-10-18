# Ciri
This is a C++ serialization libirary that uses a reflection system to serialize and deserialize objects.

## Supported types
- Primitive types (int, float, double, char, bool, etc.)
- std::string
- std::vector
- raw pointers (make sure you allocate memory before serialization/deserialization)
f your application logs during testing.


## Usage
I am goint to be honest here, there is no practical usage for this library yet.
The current status as i write this message C++26 feature are lacking support not only from compilers but also from build systems and other tools.
Maybe in year 2056 when support is available and AI will did not replace us, we might be able to use this library in production code.
Until then, this library is just playground for me and you to learn and experiment with C++26 features.
If you somehow find this library useful, please let me know, i would love to hear your feedback.

## Building
The Ciri library uses cmake to generate the config files needed and ninja (or you can use your preferred build system) to build it.

```
cmake -G Ninja -B build -S .
ninja -C build
```

## Docs (Not tested yet)
Use the doxygen tool to generate the code documentation.
```
doxygen docs/Doxyfile
```