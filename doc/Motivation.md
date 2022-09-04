# Motivation

Why implement yet another system library when
[Boost](https://www.boost.org/), [Qt](https://www.qt.io/), and a [host
of others](https://en.cppreference.com/w/cpp/links/libs) already exist
and include much of the same, or more, functionality?

The goal of libunistdcpp is to provide simple abstractions and better
interaction with the C++ standard library when programming on POSIX
compatible operating systems.  The primary operating system targets
are GNU/Linux, FreeBSD, and OpenBSD on the x86_64 and ARM64
architectures.  (Patches for compatibility with similar operating
systems and other architectures are always welcome.)

Libunistdcpp does not aim to compete with larger frameworks, provide
general purpose programming abstractions, nor to offer wide
portability among operating systems.

In addition to implementing a software library that is potentially
useful, the author hopes to learn and to have fun along the way.
