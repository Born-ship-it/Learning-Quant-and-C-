# C++ Learning Worksheet

A practical, self-guided roadmap from core language fundamentals to design and library use. Each section contains tasks to complete, concepts to understand, and small projects to build.  
Check off items as you gain confidence.

---

## How to Use This Worksheet

- Move from concrete examples to abstract ideas: write small programs first, then generalize.
- Revisit earlier topics when you encounter them again in a more advanced context.
- For every concept, type the code, compile it, and experiment by breaking it deliberately.
- After each major section, build a mini-project that combines several of the covered ideas.

---

## 1. Foundation – Basic Types, Control Flow, and Program Structure

- [ ] Write programs using fundamental types (`int`, `double`, `char`, `bool`) and observe their limits.
- [ ] Practice expressions and operators: arithmetic, relational, logical, bitwise, and assignment.
- [ ] Implement branching with `if`, `else if`, `switch`, and the conditional operator.
- [ ] Write loops (`for`, `while`, `do-while`) and understand iteration vs recursion.
- [ ] Use arrays and pointers; manually traverse an array with pointer arithmetic.
- [ ] Understand C-style strings (`const char*`) and their relationship to pointers.
- [ ] Create simple `struct`s that group related data together.
- [ ] Write functions: pass by value, by pointer, and by reference; return values and references.
- [ ] Use function overloading and default arguments to create flexible interfaces.
- [ ] Explore scope, storage duration, and the `static` keyword.
- [ ] Organize code into namespaces to avoid name collisions.
- [ ] Handle errors with exceptions: `throw`, `try`, `catch`, and resource cleanup.
- [ ] Build a multi-file project: header files, include guards, separate compilation, and linking.
- [ ] **Mini-project**: A command-line calculator that parses expressions using recursive descent.

---

## 2. Abstraction Mechanisms – Classes, Inheritance, and Templates

### Concrete Types and Operator Overloading

- [ ] Design a class that encapsulates data and operations (e.g., `Date`, `Complex`).
- [ ] Implement constructors (including default, copy, and parameterized) and destructors.
- [ ] Use member initializer lists correctly.
- [ ] Differentiate between `public`, `private`, and `protected` access.
- [ ] Write `const` member functions and understand logical vs physical constness.
- [ ] Overload arithmetic and comparison operators as members or non-member functions.
- [ ] Overload `<<` and `>>` for custom I/O.
- [ ] Implement a resource-managing class (e.g., a dynamic array) following RAII.
- [ ] **Mini-project**: A `Rational` number class that supports addition, subtraction, multiplication, division, and reduction.

### Inheritance and Polymorphism

- [ ] Create a class hierarchy with a base class and several derived classes.
- [ ] Use `virtual` functions to enable runtime polymorphism.
- [ ] Define pure virtual functions (`=0`) to create abstract interfaces.
- [ ] Understand the role of virtual destructors.
- [ ] Implement a class that stores derived objects via base-class pointers and calls virtual functions.
- [ ] Investigate object slicing and how to avoid it.
- [ ] Use `dynamic_cast` and `typeid` where necessary, and understand their costs.
- [ ] Design a clone pattern using a virtual `clone()` function.
- [ ] **Mini-project**: A simple shape hierarchy (`Circle`, `Rectangle`, `Triangle`) that can be drawn (text output) and whose total area can be computed polymorphically.

### Templates and Generic Programming

- [ ] Write a function template for a generic algorithm (e.g., `max`, `swap`, `find`).
- [ ] Create a class template for a container (e.g., a dynamic array `Vector<T>`).
- [ ] Use non-type template parameters (e.g., a fixed-size `Array<T, N>`).
- [ ] Explicitly instantiate templates and understand implicit instantiation.
- [ ] Specialise a template for a particular type (full specialisation).
- [ ] Understand the difference between template arguments that are types vs. values.
- [ ] Use the `typename` and `class` keywords interchangeably in template parameters.
- [ ] Compose templates: build a `Stack<T>` that uses your custom `Vector<T>`.
- [ ] **Mini-project**: A generic `Matrix` class template with element access and basic arithmetic operations.

### Error Handling and Exception Safety

- [ ] Classify exception safety guarantees: basic, strong, no-throw.
- [ ] Apply the “resource acquisition is initialization” (RAII) idiom to guarantee cleanup.
- [ ] Write constructors that either fully succeed or leave no resources allocated.
- [ ] Use `try`/`catch` blocks strategically; do not overuse exceptions for normal control flow.
- [ ] Understand the stack unwinding process and its performance implications.
- [ ] **Mini-project**: Extend your `Vector<T>` to be exception-safe (copy-and-swap for assignment).

---

## 3. The Standard Library – Containers, Algorithms, I/O, and Numerics

### Containers and Iterators

- [ ] Use `std::vector` and `std::array` as default sequential containers.
- [ ] Work with `std::list` and `std::forward_list` for frequent insertions/deletions.
- [ ] Explore ordered associative containers: `std::set`, `std::map`, `std::multiset`, `std::multimap`.
- [ ] Use unordered containers (`std::unordered_map`, `std::unordered_set`) and understand hashing.
- [ ] Learn iterator categories: input, output, forward, bidirectional, random-access.
- [ ] Use iterators to traverse, insert, and erase elements.
- [ ] Employ range-based `for` loops with containers.
- [ ] Understand `std::string` as a container of characters; use its member functions.
- [ ] **Mini-project**: A word frequency counter that reads a text file, stores counts in `std::map<std::string, int>`, and prints the top N words.

### Algorithms and Function Objects

- [ ] Apply non-modifying algorithms: `std::find`, `std::count`, `std::equal`, `std::search`.
- [ ] Use modifying algorithms: `std::copy`, `std::transform`, `std::fill`, `std::replace`.
- [ ] Sort and partition with `std::sort`, `std::stable_sort`, `std::partition`.
- [ ] Remove elements with the erase–remove idiom (`vec.erase(remove(...), vec.end())`).
- [ ] Write custom function objects (functors) with `operator()`.
- [ ] Use lambdas to create inline predicates and operations.
- [ ] Bind arguments with `std::bind` and placeholders (or prefer lambdas in modern practice).
- [ ] **Mini-project**: A program that reads a list of numbers, filters out odd ones, squares the remaining, and prints the sorted result using a combination of standard algorithms.

### Input/Output Streams

- [ ] Format output with manipulators (`std::setw`, `std::setprecision`, `std::fixed`, etc.).
- [ ] Read formatted input using `>>` and handle errors with stream state bits.
- [ ] Perform unformatted I/O with `get()`, `getline()`, `read()`, `write()`.
- [ ] Work with file streams: `std::ifstream`, `std::ofstream`, `std::fstream`.
- [ ] Use string streams (`std::istringstream`, `std::ostringstream`) for in-memory formatting.
- [ ] Create custom stream operators for your own types.
- [ ] **Mini-project**: A simple CSV parser that reads rows and columns into a vector of vectors of strings.

### Numerics and String Processing

- [ ] Use `std::complex`, `std::valarray`, and `std::numeric_limits`.
- [ ] Generate random numbers with `<random>` (engines, distributions).
- [ ] Perform advanced string operations: substrings, find, replace, comparison, and conversion.
- [ ] Use `std::to_string` and `std::stoi`/`std::stod` family for numeric conversion.
- [ ] **Mini-project**: A polynomial class that uses `std::valarray<double>` for coefficients, with evaluation and addition.

---

## 4. Design and Software Development

- [ ] Understand the distinction between interface and implementation; minimize compilation dependencies.
- [ ] Apply the Pimpl idiom (pointer to implementation) to hide details.
- [ ] Use forward declarations and avoid unnecessary `#include` in headers.
- [ ] Identify when to use inheritance versus composition (“is-a” vs “has-a”).
- [ ] Recognize the role of concrete types (value-like), abstract interfaces, and node classes.
- [ ] Factor shared interfaces into abstract base classes, and shared implementations into base classes.
- [ ] Design for testability: decouple components using interfaces.
- [ ] Practice reading and refactoring existing code to improve structure.
- [ ] **Capstone project**: A simple address book application that uses:
  - A custom contact class with validation.
  - A polymorphic storage interface (in-memory vs. file-backed).
  - A generic search/filter function using templates and algorithms.
  - Proper error handling and a cleanly separated UI layer.

---

## 5. Language-Technical Details (Optional but Deepening)

- [ ] Browse the formal grammar to understand expression precedence and declarator rules.
- [ ] Differentiate C++ from C: stronger type checking, function overloading, references, and `new`/`delete`.
- [ ] Learn about locales and internationalization: `std::locale`, facets for date/time/money formatting.
- [ ] Examine the exception-safety guarantees of standard library containers and algorithms.
- [ ] Explore move semantics and rvalue references (introduced later, but can be studied here).

---

## Programming Heuristics – Rules of Thumb While You Learn

These are not absolute laws; apply them where reasonable and let experience refine them.

### Express Ideas Directly in Code
- **If you can think of “it” as a separate idea, make it a class.**  
  *A “separate idea” is a concept from your problem domain (e.g., `Account`, `Texture`, `Timer`). A class binds its data and behaviour together.*
- **If you can think of “it” as a separate entity, make it an object of some class.**  
  *An entity is a concrete instance (a specific account, a particular timer). Each entity deserves its own object.*
- **If two classes share a common interface, make that interface an abstract class.**  
  *Define the operations they have in common as pure virtual functions in an abstract base class. This allows polymorphic use without depending on concrete types.*
- **If two classes have significant implementation in common, factor that commonality into a base class.**  
  *Avoid duplicate code by pulling shared data and function implementations into a common base class.*

### Write Generic Code Where Appropriate
- **If a class is a container of objects, make it a template.**  
  *A container’s logic is independent of the element type. A class template lets you write it once for any type while preserving type safety.*
- **If a function implements an algorithm for a container, make it a template function that works for a family of containers.**  
  *Write algorithms in terms of iterator ranges, not specific container types. This makes them usable with arrays, vectors, lists, etc.*

### Organize Logically
- **If a set of classes, templates, and functions are logically related, place them in a common namespace.**  
  *Use namespaces to group your library or module and to prevent name collisions with other code.*

### Practical Class Design (for typical application classes)
- **Don’t use global data; use member data instead.**  
  *Global variables make programs hard to reason about and test. Encapsulate state inside objects.*
- **Don’t use global functions; prefer member functions or namespace-scoped functions.**  
  *Keep functions close to the data they operate on, either as members or in the same namespace.*
- **Don’t use public data members; use private data with accessor functions.**  
  *Hiding data behind functions allows you to change the internal representation without breaking client code.*
- **Don’t use `friend` unless it avoids a worse problem (global data or a type field).**  
  *Friendship breaks encapsulation; use it sparingly, typically for tightly coupled non-member operators or implementation details where making everything public would be worse.*
- **Don’t put a “type field” in a class; use virtual functions.**  
  *Instead of an enum tag and a switch statement, rely on polymorphism. Virtual functions dispatch to the correct behaviour automatically, making extensions easier.*
- **Don’t use inline functions except as a significant optimization.**  
  *Trust the compiler’s own inlining decisions unless profiling proves otherwise. Over-inlining can bloat code and increase compile-time coupling.*

Finally, remember: *“To write a good program takes intelligence, taste, and patience. You are not going to get it right the first time. Experiment!”*
