// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Api.hpp"

#include <chrono>
#include <format>
#include <map>
#include <string>
#include <variant>

struct SqlConnectionString
{
    std::string value;

    LIGHTWEIGHT_API auto operator<=>(SqlConnectionString const&) const noexcept = default;
};

using SqlConnectionStringMap = std::map<std::string, std::string>;

LIGHTWEIGHT_API SqlConnectionStringMap ParseConnectionString(SqlConnectionString const& connectionString);
LIGHTWEIGHT_API SqlConnectionString BuildConnectionString(SqlConnectionStringMap const& map);

struct SqlConnectionDataSource
{
    std::string datasource;
    std::string username;
    std::string password;
    std::chrono::seconds timeout { 5 };

    LIGHTWEIGHT_API auto operator<=>(SqlConnectionDataSource const&) const noexcept = default;
};

using SqlConnectInfo = std::variant<SqlConnectionDataSource, SqlConnectionString>;

template <>
struct LIGHTWEIGHT_API std::formatter<SqlConnectInfo>: std::formatter<std::string>
{
    auto format(SqlConnectInfo const& info, format_context& ctx) const -> format_context::iterator
    {
        if (auto const* dsn = std::get_if<SqlConnectionDataSource>(&info))
        {
            return formatter<string>::format(std::format("DSN={};UID={};PWD={};TIMEOUT={}",
                                                         dsn->datasource,
                                                         dsn->username,
                                                         dsn->password,
                                                         dsn->timeout.count()),
                                             ctx);
        }
        else if (auto const* connectionString = std::get_if<SqlConnectionString>(&info))
        {
            return formatter<string>::format(connectionString->value, ctx);
        }
        else
        {
            return formatter<string>::format("Invalid connection info", ctx);
        }
    }
};
