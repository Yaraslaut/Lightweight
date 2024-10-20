# Lightweight, SQL and ORM data mapper API for C++23

**Lightweight** is a thin and modern C++ ODBC wrapper for **easy** and **fast** raw database access.

## Features

- **Easy to use** - simple, expressive and intuitive API
- **Performance** - do as little as possible, and as much as necessary - efficiency is key
- **Extensible** - support for custom data types for writing to and reading from columns
- **Exception safe** - no need to worry about resource management
- **Open Collaboration** - code directly integrated into the main project

## Non-Goals

- Feature creeping (ODBC is a huge API, we are not going to wrap everything)
- No intend to support non-ODBC connectors directly, in order to keep the codebase simple and focused

## Query builder examples

```cpp
auto sqlStatement = SqlStatement();
auto const& queryFormatter = sqlStatemnt.Connection().QueryFormatter();

// SELECT "employee_id", "first_name", "last_name"
// FROM "employees"
// WHERE "employee_id" = 100
// ORDER BY "last_name" ASC LIMIT 5 OFFSET 10
SqlQueryBuilder::FromTable("employees")
                .Select()
                .Fields("employee_id", "first_name", "last_name")
                .Where("employee_id", "=", 100)
                .OrderBy("last_name", SqlQueryBuilder::Ascending)
                .Range(5, 10)
                .ToSql(queryFormatter);

// UPDATE "employees"
// SET "first_name" = 'John', "last_name" = 'Doe'
// WHERE "employee_id" = 100
SqlQueryBuilder::FromTable("employees")
                .Update()
                .Set("first_name", "John")
                .Set("last_name", "Doe")
                .Where("employee_id", "=", 100)
                .ToSql(queryFormatter);

// INSERT INTO "employees" ("employee_id", "first_name", "last_name")
// VALUES (100, 'John', 'Doe')
SqlQueryBuilder::FromTable("employees")
                .Insert()
                .Set("employee_id", 100)
                .Set("first_name", "John")
                .Set("last_name", "Doe")
                .ToSql(queryFormatter);

// DELETE FROM "employees"
// WHERE "employee_id" = 100
SqlQueryBuilder::FromTable("employees")
                .Delete()
                .Where("employee_id", "=", 100)
                .ToSql(queryFormatter);
```

## C++ Language requirements

This library a little bit of more modern C++ language and library features in order to be more expressive and efficient.

- C++23 (`std::expected`, `std::stacktrace`, lambda templates expressions)
- C++20 (`std::source_location`, `std::error_code`, `operator<=>`, `std::format()`, designated initializers, concepts, ranges)
- C++17 (fold expressions, `std::string_view`, `std::optional`, `std::variant`, `std::apply`)

## Supported Databases

- Microsoft SQL
- PostgreSQL
- SQLite
- Oracle database (untested)

## Using SQLite for testing on Windows operating system

You need to have the SQLite3 ODBC driver for SQLite installed.

- ODBC driver download URL: http://www.ch-werner.de/sqliteodbc/
- Example connection string: `DRIVER={SQLite3 ODBC Driver};Database=file::memory:`

### SQLite ODBC driver installation on other operating systems

```sh
# Fedora Linux
sudo dnf install sqliteodbc

# Ubuntu Linux
sudo apt install sqliteodbc

# macOS
arch -arm64 brew install sqliteodbc
```

- sqliteODBC Documentation: http://www.ch-werner.de/sqliteodbc/html/index.html
- Example connection string: `DRIVER=SQLite3;Database=file::memory:`
