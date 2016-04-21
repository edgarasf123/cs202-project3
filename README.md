# CS202_Project3

--------------------
PROJECT INSTRUCTIONS
--------------------

You are to implement the bank account program from Project #1 as an object oriented C++ program.

The code you produce must compile with GNU g++ on the Linux machine.

----------
DISCUSSION
----------

You may implement a menu-driven program or you may implement a command line-driven program.

That is, either re-implement Part #1 of Project #1 or re-implement Part #2 of Project #1.

It's up to you.

--------------------
PROGRAM REQUIREMENTS
--------------------

- [x] You must use a hierarchical class [ meaning class inhertance ] design for this program.
- [ ] Your design must include at least one pure abstract base class.
- [ ] When you are finished developing the program, test it.
- [ ] Document your program and tests in a write-up for the program, make it an MS-Word document.
- [ ] Document your tests by taking screenshots (Ctrl PrintScreen) and paste those into the write-up MS-Word document.
- [ ] When making your Word doc, include a sentence for each screenshot that tells what is going on in it:  what the test was, what the result was, etc.
- [ ] Your Word doc should include screenshots for testing every function you implement, along with associated verbiage.
- [ ] Copy your MS-Word document and your Linux make file to the same folder that the .CPP source file resides in.
- [ ] When you are ready to submit to Canvas, you need to zip up the entire folder structure and upload the resulting .zip file to the drop box.

-----------------------------------
CODING CONVENTIONS and RESTRICTIONS
-----------------------------------

- [ ] Each file shall have a file header.
- [ ] Each function shall have a function header.
- [ ] Your code shall be properly indented and commented.
- [ ] Global variables cannot be used.
- [ ] Global constants can be used, and must be all-uppercase names, with words separated by underscores.
- [ ] The main() function must act as the executive for the program, no detailed logic can appear in main().
- [ ] The main() function cannot act as a "wrapper function" for a function that contains all or most of the program's detailed logic.  If you don't know what this means, ask your teacher to explain it.

Grading for submitted code will take into account violations of the above.

----------------------------
GENERAL PROJECT REQUIREMENTS
----------------------------

- [ ] The program must incorporate certain language features, as described below.
- [ ] The program you write must be an object-oriented program, using classes designed by you.
- [ ] The program must use three (3) of the following STL classes:
    linked list [ Chapter 17 ]
    queue       [ Chapter 18 ]
    stack       [ Chapter 18 ]
    vector      [ Chapter 7, Section 7.11 and Chapter 16, Section 16.5 ]
- [ ] Error detection and error recovery shall be a part of the program.  For example, if an output file cannot be opened, the user should be notified.
- [ ] You are required to use the try-catch error handling method of Chapter 16 in your program.
- [ ] Programs submitted as part of a project must build [ an executable ] on the Linux server.
- [ ] Programs submitted as part of a project must satisfy the requirments of the project.
- [ ] The student need not present the project to the class, but in the write-up the student must discuss the project's requirements and how the program satisfies them, giving sample runs for the program, discuss the project's makefile, and discuss the program's shortcomings and known bugs.

-------------------------
ZERO CREDIT FOR A PROJECT
-------------------------

In general, for this course, several things can cause a student to receive zero [ 0 ] credit for a submitted assignment.

    1.  a student submits a project late [ "late" means after the due date/time ]

    2.  a student submits code they did not write

    3.  a student submits a program that does not build

    4.  a student submits a program that builds and does not run [ it crashes ]

    5.  a student submits a program that builds and runs, but does not satisfy the project's requirements

-----------------------
SUBMISSION REQUIREMENTS
-----------------------

You need to submit a ZIP file that contains the entire project: source files, makefile, data files.

You need to upload the ZIP file to canvas.

Submission verification by you is possible because you are allowed to download files from your Canvas submissions.  This allows you to test your submission by performing the following procedure:

1.    download your ZIP file from the Canvas drop box
2.    unzip your ZIP file (extract its contents)
3.    transfer the source code, makefile, data file(s) to the server
4.    build the project
5.    run the resulting program

If steps 1-5 do not work for you, steps 1-5 will not work for your instructor either.

If steps 1-5 do not work for you, fix your project until steps 1-5 work for you.

Only when steps 1-5 work for you can you consider your submission complete.
