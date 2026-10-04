# Municipal Financial Management System (MFMS)

**PAP521S — Programming in Practice · Project A**

Namibia University of Science and Technology

---

## Group Members

| # | Student Name | Student Number | Responsibility |
|---|---|---|---|
| 1 | Akim Kandal | 225008440 | Employee Management |
| 2 | ILUNGA BOTA | 226141772 | Supplier Management |
| 3 | Franz Moussiessi | 226141861 | About / Help module, Testing |
| 4 |  Namholo Markus| 224010646 |  Asset Management |
| 5 | Nakale T Willem | 225036630 | Integration and Validation|
| 6 | Christian Hatutale | 225006812 |  Budget Management |
| 7 | N.E David | 226100529 | Reports |

---

## Project Description

The Municipal Financial Management System is a menu-driven console application
written in ANSI C (C99). It supports the day-to-day financial administration of a
municipality: it records employees and calculates their salaries, tracks
departmental budgets against expenditure, maintains a supplier register and an
asset register, and produces summary reports across all of them.

Project A is the foundation version of the system. It applies the programming
concepts covered in Weeks 1–8 of the course: variables and data types, operators,
decision making with `if` / `else` and `switch`, loops, arrays, strings, and
functions with parameters and return values.

Data is held in memory using parallel arrays, one array per field, sharing a
common index. Each module owns its own data privately (`static` file-scope
arrays) and exposes it to the rest of the system only through getter functions
declared in its header file. This keeps the modules independent and allowed the
team to work on separate files in parallel.

---

## System Features

### 1. Employee Management
- Add an employee (ID, name, department, basic salary, housing and transport allowances)
- Display all employees with gross and net salary
- Search for an employee by name
- Salary summary: total payroll, average, highest and lowest salary

Gross salary = basic + housing + transport. Net salary = gross − 15% tax.

### 2. Budget Management
- Record a departmental budget (allocation and expenditure)
- Calculate the remaining budget
- Classify each department as WITHIN BUDGET or OVER BUDGET
- Display all budgets, search by department, and list departments that overspent

### 3. Supplier Management
- Register a supplier (ID, name, email, telephone, town)
- Display the supplier register
- Search for a supplier by name

### 4. Asset Management
- Register a municipal asset (ID, name, type, purchase value, department, condition)
- Display the asset register with a running total value
- Search by asset name
- Total and average asset value
- Filter assets by department, with a department sub-total

### 5. Reports
- Employee report — total employees, total payroll, average, highest and lowest salary
- Budget report — total allocated, total expenditure, remaining, departments over budget
- Supplier report — all registered suppliers
- Asset report — all registered assets with total value
- Full municipal report — all four in sequence

### 6. About / Help
System information, group details and a description of each module.

### Input Validation
All user input passes through the shared helpers in `utils.c`, so the system
rejects:
- menu choices outside the valid range
- text typed where a number is expected (without entering an infinite loop)
- negative salaries, budgets and asset values
- empty names and departments
- adding records beyond an array's capacity

---

## Repository Structure

```
Project--MFMS/
├── main.c          main menu and dispatch
├── utils.c/.h      shared input and validation helpers
├── employees.c/.h  Employee Management
├── budget.c/.h     Budget Management
├── suppliers.c/.h  Supplier Management
├── assets.c/.h     Asset Management
├── reports.c/.h    Reports
├── about.c/.h      About / Help
└── README.md
```

Every module is a `.c` and `.h` pair. The header declares what the module offers
to the rest of the program; the source file holds the implementation and keeps
its data private.

---

## Compilation Instructions

The project is split across several source files, so every `.c` file must be
listed on the command line. Header files are not listed — they are pulled in by
`#include`.

**Requirements:** GCC (MinGW-w64 / MSYS2 UCRT64 on Windows, or GCC on Linux/macOS)

```bash
gcc main.c utils.c employees.c budget.c suppliers.c assets.c reports.c about.c -o mfms
```

To compile with all warnings enabled (the project compiles with none):

```bash
gcc -Wall -Wextra -std=c99 main.c utils.c employees.c budget.c suppliers.c assets.c reports.c about.c -o mfms
```

---

## How to Run the System

**Windows:**
```bash
./mfms
```

**Linux / macOS:**
```bash
./mfms
```

The main menu appears:

```
========================================
 MUNICIPAL FINANCIAL MANAGEMENT SYSTEM
========================================

1. Employee Management
2. Budget Management
3. Supplier Management
4. Asset Management
5. Reports
6. About / Help
7. Exit

Enter your choice:
```

Enter the number of the module you want. Each module has its own sub-menu, and
option "Back to main menu" returns here. Option 7 exits the program.



---

## Individual Responsibilities

| Student | Files owned | Functions developed |
|---|---|---|
| Akim Kandal (225008440) | `employees.c/.h`, `main.c`, |
| ILUNGA BOTA (226141772) | `suppliers.c/.h` | `supplierMenu`, supplier add / display / search, `getSupplierCount`, `getSupplierName`, `getSupplierTown` |
| Franz Moussiessi | `about.c/.h` | `displayWelcome`, `displayAbout`, `displayExit` |
| Namholo Markus (224010646) | standalone billing prototype | `createNewAccount`, `processBilling`, `recordPayment`, `generateFinancialReport`, `searchAccount` |
|Christian Hatutale 225006812 -` Budget Management`|
|Ilunga Bota 226141772 -   `Supplier Management`|
|Namholo Markus 224010646 - `Asset Management`|
|N.E David 226100529 - Reports`|
|Nakale T willem 225036630 - `Integration and Validation`|
|Franz Moussiessi 226141861 - `About module, Testing and Git`|


> **Note on scope:** several modules originally assigned to other members were
> not delivered before the deadline. To produce a working system, Akim Kandal
> implemented the main menu, the shared validation helpers, and the Budget,
> Asset and Reports modules in addition to his own Employee Management module.
> This table reflects what each member actually wrote.

---

## Version Control

Each member worked on their own branch and merged into `main` through the
repository. Branches used: `employees`, `suppliers`, `docs`.

Repository: https://github.com/225008440-Kandal/Project--MFMS# Project--MFMS