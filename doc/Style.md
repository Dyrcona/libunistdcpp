# Coding Style

The code in libunistdcpp follows the [C++ Core
Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines),
except as mentioned below.

## Naming Conventions

New class, struct, and enum names begin with a capital letter and are
written as a single word with subwords being capitalized.  Examples:
`SysName, Pipe, Pipe::Flags, Popen`.

New function, variable, and enum member names are composed of
lowercase letters with underscores separating words in keeping with
the Core Guidelines.  Simple wrappers for existing functions and
values use the same name as the wrapped function or value when there
is no conflict with override resolution.

## Plain Enumerations

Plain enumerations are used when the values are passed directly into C
functions of the POSIX library.  Plain enumerations readily decay to
int and many POSIX functions take int bitmasks as parameters.  Plain
enumerations should always be specified as a member type of an outher
class so that they are not globally accessible without specifying the
outer class name, example: `Pipe::Flags`.
