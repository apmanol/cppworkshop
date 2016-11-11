=====================
C++ WORKSHOP HANDS-ON
=====================

.. contents:: CONTENTS


Exercise 1: memerr.cpp (memory errors)
======================================

1. Execute the following:

   .. code:: bash

    make distclean
    make debug=1

	./bin/memerr

2. In src/memerr.cpp uncomment DO_ERROR_ADDRESS_SANITIZER, and repeat step 1.
   Explain the result.

   2.1 Comment out the buffer overflow case, build, run and explain
   the result.

   2.2 Comment out the use after free case, build, run and explain the
   result.

   2.3 Comment out the double free case, build, run and explain the
   result.

3. In src/memerr.cpp uncomment DO_ERROR_STACK_PROTECTOR, and repeat step 1.
   Explain the result.

4. In src/memerr.cpp uncomment DO_ERROR_FORTIFY_SOURCE, and repeat step 1.
   Explain the result.

   Related links:

   * AddressSanitizer_
   * FORTIFY_SOURCE_
   * fstack-protector_

.. _AddressSanitizer: https://github.com/google/sanitizers/wiki/AddressSanitizer
.. _FORTIFY_SOURCE: https://access.redhat.com/blogs/766093/posts/1976213
.. _fstack-protector: https://access.redhat.com/blogs/766093/posts/1976073

Exercise 2: auto.cpp (type deduction)
=====================================

1. Execute the following:

   .. code:: bash

    make distclean
    make debug=1

    ./bin/auto

   The unit tests should fail!

   Those test cases contain some example with type deduction. Study
   the examples and replace the ``void`` cases with the correct type
   in order to pass the unit test.

Exercise 3: stl.cpp (STL & algorithms)
======================================

1. Execute the following:

   .. code:: bash

    make distclean
    make

    ./bin/stl

   The unit tests should fail! This section is based on STL
   algorithms and sequences, so a very handy link is:
   http://en.cppreference.com/w/cpp/algorithm


2. Fix unit test ``geometric``

   Fill the function ``generate_geometric_samples`` in order to
   generate a ``vector``  with geometric sequences.
   Geometric sequence is a sequence of numbers where each term after
   the first is found by multiplying the previous one by a fixed,
   non-zero number called the common ratio. For example, the sequence
   2, 6, 18, 54, ... is a geometric progression with common ratio 3.

   Tip: use std::generate

   Then fill the function ``is_divisible_by`` in order to check if all
   elements of a ``vector`` are divisible by some number.

   Tip: use std::all_of

3. Fix unit test ``remove``

   Fill the remove criteria in ``remove_even_numbers``.

4. [optional] Fix unit test ``counting``

   Implement ``count_unique_words`` so as to keep a counter for every
   word met in the string. The function must use a generic map
   structure.

   Tip: check http://en.cppreference.com/w/cpp/container/unordered_map

5. [optional] Fix unit test ``timing``

   Implement the return value of ``time_find``.

   Tip: use http://en.cppreference.com/w/cpp/chrono/duration

Exercise 4: move.cpp (filesystem access with move semantics)
============================================================

1. Execute the following:

   .. code:: bash

    make distclean
    make

    ./bin/move ./src/move.cpp

   Why is the assertion failing? Correct the issue!

2. Execute the following:

   .. code:: bash

    ./bin/move /dev/urandom

   To debug the problem, you may use gdb_ (C-x o to change active `Text
   User Interface`__ window!):

   .. code:: bash

    gdb -tui ./bin/move
    (gdb) run /dev/urandom
    (gdb) bt
    (gdb) p *this
    (gdb) p size_
    (gdb) whatis buf_
    (gdb) cont
    (gdb) q

3. Before correcting the issue, use also AddressSanitizer_ to reproduce it:

   .. code:: bash

    make distclean
    make debug=1

    ./bin/move /dev/urandom

4. [optional] Implement the ability to print the contents of the file's
   buffer to std::cout, and test it!

.. _gdb: https://sourceware.org/gdb/
.. __: https://sourceware.org/gdb/onlinedocs/gdb/TUI.html

Exercise 5: raii.cpp (network port scanning with RAII)
======================================================

1. Execute the following:

   .. code:: bash

    make distclean
    make

    ./bin/raii

   Can you generate an assertion failure after a few executions? Where are
   the leaks in the program? For one of them, you can get more information
   with valgrind_:

   .. code:: bash

    valgrind ./bin/raii

2. Correct the leaks, and verify by a few normal/valgrind_ executions!

3. Can you refactor port_scan() into a new port_scan2(), that applies
   RAII to its resources? You should not change anything in namespace net!

.. _valgrind: http://valgrind.org/

Exercise 6: thread.cpp (apply multi-threading to a simple task)
===============================================================

1. Execute the following:

   .. code:: bash

    make distclean
    make

    ./bin/thread

   Note the duration output for the sorting of both containers.

2. Can you refactor task() into a new parallel_task(), that spawns two
   threads, each sorting one of the two containers? Execute the program a
   few times, and compare the execution times of task() and parallel_task().

   Tip: keep copies of vec & deq in main and invoke parallel_task()
   on these (unsorted) copies, in order to compare the execution times
   of both sorting tasks!

