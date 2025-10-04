Ailya (523506) Assignment01 Fall2025
================================

Approach
--------
This submission implements three tasks. Polynomial ADT, Text Editor Simulation, and UNO Card Game Simulation by using C++ with linked lists, aligning with "Assignment 1: Linked Lists". The headers are enhanced with virtual functions and abstract base classes per the  guidance on the "slight enhancement" involving the `virtual` keyword, with concrete implementations in .cpp files.

- **Polynomial ADT**: The `Polynomial` class is implemented as an abstract base class with virtual methods. A derived `ConcretePolynomial` class uses a singly linked list to store terms (coefficient, exponent), supporting `insertTerm`, `toString`, `add`, `multiply`, and `derivative` operations. The output follows the format "3x^4 + 2x^2 - x + 5", handling polynomial arithmetic and differentiation.

- **Text Editor Simulation**: The `TextEditor` class is an abstract base class with virtual methods. A derived `ConcreteTextEditor` class employs a doubly linked list to manage text and a cursor, implementing `insertChar`, `deleteChar`, `moveLeft`, `moveRight`, and `getTextWithCursor`. The output resembles "ab|c", indicating cursor position.

- **UNO Card Game Simulation**: The `UNOGame` class is an abstract base class with virtual methods. A derived `ConcreteUNOGame` class uses a singly linked list for the deck and discard pile, and a vector of `Node*` pointers for player hands, implementing `initialize`, `playTurn`, `isGameOver`, `getWinner`, and `getState`. The output matches "Player 0's turn, Direction: Clockwise, Top: Blue 3, Players cards: P0:7, P1:7" with a fixed seed (1234) for reproducibility.

Publicly Accessible GitHub Link
------------------------------
https://github.com/Ailya-Shah/DSA-assignment01-2025.git

Challenges Faced
----------------
Implementing this assignment presented several challenges, particularly in aligning with the  hint about a "slight enhancement" involving a C++ keyword. Initially, we assumed it might be `private` with linked list members, leading to non-compliant code due to the no-modification constraint on headers. After iterative attempts and clarification, we identified `virtual` as the intended keyword, requiring a shift to abstract base classes with virtual functions. This necessitated redesigning the headers to include pure virtual methods and implementing concrete derived classes, which was complex due to managing dynamic memory for linked lists (e.g., memory leaks in `UNOGame`). The lack of permission to enhance headers caused trial-and-error, and the deadline pressure. Test case compatibility was another hurdle, resolved by aligning with provided output formats. We request feedback to refine the virtual design and ensure test case success.

