C++ Version
Currently, code should target C++17, i.e., should not use C++2x features. The C++ version targeted by this guide will advance (aggressively) over time.

Do not use non-standard extensions.

Consider portability to other environments before using features from C++14 and C++17 in your project.
Header Files
In general, every .cc file should have an associated .h file. There are some common exceptions, such as unittests and small .cc files containing just a main() function.

Correct use of header files can make a huge difference to the readability, size and performance of your code.

The following rules will guide you through the various pitfalls of using header files.

Self-contained Headers
Header files should be self-contained (compile on their own) and end in .h. Non-header files that are meant for inclusion should end in .inc and be used sparingly.

All header files should be self-contained. Users and refactoring tools should not have to adhere to special conditions to include the header. Specifically, a header should have header guards and include all other headers it needs.

Prefer placing the definitions for template and inline functions in the same file as their declarations. The definitions of these constructs must be included into every .cc file that uses them, or the program may fail to link in some build configurations. If declarations and definitions are in different files, including the former should transitively include the latter. Do not move these definitions to separately included header files (-inl.h); this practice was common in the past, but is no longer allowed.

As an exception, a template that is explicitly instantiated for all relevant sets of template arguments, or that is a private implementation detail of a class, is allowed to be defined in the one and only .cc file that instantiates the template.

There are rare cases where a file designed to be included is not self-contained. These are typically intended to be included at unusual locations, such as the middle of another file. They might not use header guards, and might not include their prerequisites. Name such files with the .inc extension. Use sparingly, and prefer self-contained headers when possible.

The #define Guard
All header files should have #define guards to prevent multiple inclusion. The format of the symbol name should be <PROJECT>_<PATH>_<FILE>_H_.

To guarantee uniqueness, they should be based on the full path in a project's source tree. For example, the file foo/src/bar/baz.h in project foo should have the following guard:

#ifndef FOO_BAR_BAZ_H_
#define FOO_BAR_BAZ_H_

...

#endif  // FOO_BAR_BAZ_H_
Forward Declarations
Avoid using forward declarations where possible. Instead, #include the headers you need.

A "forward declaration" is a declaration of a class, function, or template without an associated definition.

Forward declarations can save compile time, as #includes force the compiler to open more files and process more input.
Forward declarations can save on unnecessary recompilation. #includes can force your code to be recompiled more often, due to unrelated changes in the header.
Forward declarations can hide a dependency, allowing user code to skip necessary recompilation when headers change.
A forward declaration may be broken by subsequent changes to the library. Forward declarations of functions and templates can prevent the header owners from making otherwise-compatible changes to their APIs, such as widening a parameter type, adding a template parameter with a default value, or migrating to a new namespace.
Forward declaring symbols from namespace std:: yields undefined behavior.
It can be difficult to determine whether a forward declaration or a full #include is needed. Replacing an #include with a forward declaration can silently change the meaning of code:
      // b.h:
      struct B {};
      struct D : B {};

      // good_user.cc:
      #include "b.h"
      void f(B*);
      void f(void*);
      void test(D* x) { f(x); }  // calls f(B*)
      
If the #include was replaced with forward decls for B and D, test() would call f(void*).
Forward declaring multiple symbols from a header can be more verbose than simply #includeing the header.
Structuring code to enable forward declarations (e.g. using pointer members instead of object members) can make the code slower and more complex.
Try to avoid forward declarations of entities defined in another project.
When using a function declared in a header file, always #include that header.
When using a class template, prefer to #include its header file.
Please see Names and Order of Includes for rules about when to #include a header.

Inline Functions
Define functions inline only when they are small, say, 10 lines or fewer.

You can declare functions in a way that allows the compiler to expand them inline rather than calling them through the usual function call mechanism.

Inlining a function can generate more efficient object code, as long as the inlined function is small. Feel free to inline accessors and mutators, and other short, performance-critical functions.

Overuse of inlining can actually make programs slower. Depending on a function's size, inlining it can cause the code size to increase or decrease. Inlining a very small accessor function will usually decrease code size while inlining a very large function can dramatically increase code size. On modern processors smaller code usually runs faster due to better use of the instruction cache.

A decent rule of thumb is to not inline a function if it is more than 10 lines long. Beware of destructors, which are often longer than they appear because of implicit member- and base-destructor calls!

Another useful rule of thumb: it's typically not cost effective to inline functions with loops or switch statements (unless, in the common case, the loop or switch statement is never executed).

It is important to know that functions are not always inlined even if they are declared as such; for example, virtual and recursive functions are not normally inlined. Usually recursive functions should not be inline. The main reason for making a virtual function inline is to place its definition in the class, either for convenience or to document its behavior, e.g., for accessors and mutators.
