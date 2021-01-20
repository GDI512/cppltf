#include <output.hpp>
#include <cstdio>

namespace void_test::core {

    struct format {
        static constexpr auto space = "\040\040";
        static constexpr auto scope = "(\033[93munit\033[0m\040%s)\n";
        static constexpr auto error = "(\033[31merror\033[0m\040%s)\n";
        static constexpr auto success = "(\033[32mok\033[0m\040%s)\n";
        static constexpr auto exception = "(\033[31munhandled\040exception\033[0m\040%s)\n";
        static constexpr auto test_error = "(\033[31munit\040error\033[0m\040[%i/%i])\n";
        static constexpr auto test_success = "(\033[32munit\040ok\033[0m\040[%i/%i])\n";
        static constexpr auto resource_error = "(\033[31mresource\040error\033[0m\040[%i/%i]\040[%i/%i/%i])\n";
        static constexpr auto resource_success = "(\033[32mresource\040ok\033[0m\040[%i/%i]\040[%i/%i/%i])\n";
    };

    size_type output::indent_level = 0;

    output::~output() noexcept {
        indent_level--;
    }

    output::output() noexcept {
        indent_level++;
    }

    static auto repeat(string text, size_type count) noexcept -> void {
        while (count-- > 0) {
            fputs(text, stdout);
        }
    }

    auto output::on_scope(string name) noexcept -> void {
        repeat(format::space, indent_level);
        printf(format::scope, name);
    }

    auto output::on_error(string source) noexcept -> void {
        repeat(format::space, indent_level);
        printf(format::error, source);
    }

    auto output::on_success(string source) noexcept -> void {
        repeat(format::space, indent_level);
        printf(format::success, source);
    }

    auto output::on_exception(string source) noexcept -> void {
        repeat(format::space, indent_level);
        printf(format::exception, source);
    }

    auto output::on_test_error(registry::state data) noexcept -> void {
        repeat(format::space, indent_level);
        printf(format::test_error, data.error_count, data.success_count + data.error_count);
    }

    auto output::on_test_success(registry::state data) noexcept -> void {
        repeat(format::space, indent_level);
        printf(format::test_success, data.error_count, data.success_count + data.error_count);
    }

    auto output::on_resource_error(const verifier::state& data) noexcept -> void {
        repeat(format::space, indent_level);
        printf(format::resource_error, static_cast<int>(data.destroyed_count), static_cast<int>(data.constructed_count),
               static_cast<int>(data.destructor_error_count), static_cast<int>(data.constructor_error_count),
               static_cast<int>(data.operator_error_count));
    }

    auto output::on_resource_success(const verifier::state& data) noexcept -> void {
        repeat(format::space, indent_level);
        printf(format::resource_success, static_cast<int>(data.destroyed_count),
               static_cast<int>(data.constructed_count), static_cast<int>(data.destructor_error_count),
               static_cast<int>(data.constructor_error_count), static_cast<int>(data.operator_error_count));
    }

}