#ifndef CPPLTF_ASSERT_HPP
#define CPPLTF_ASSERT_HPP

#include "state.hpp"
#include "utility.hpp"

#define scope __func__

namespace test {

    inline auto check(bool value) noexcept -> bool {
        if (value) {
            return core::registry::on_success(scope);
        } else {
            return core::registry::on_error(scope);
        }
    }

    template <typename T, typename U>
    auto check(T first, T last, U&& function) noexcept -> bool {
        for (; first != last; ++first) {
            if (!function(*first)) {
                return core::registry::on_error(scope);
            }
        }
        return core::registry::on_success(scope);
    }

    template <typename T, typename U, auto N>
    auto check(T (&array)[N], U&& function) noexcept -> bool {
        auto first = core::begin(array);
        const auto last = core::end(array);
        for (; first != last; ++first) {
            if (!function(*first)) {
                return core::registry::on_error(scope);
            }
        }
        return core::registry::on_success(scope);
    }

    template <typename T, typename U>
    auto check_equal(const T& left, const U& right) noexcept -> bool {
        if (left == right) {
            return core::registry::on_success(scope);
        } else {
            return core::registry::on_error(scope);
        }
    }

    template <typename T, typename U>
    auto check_equal(T first, T last, U other) noexcept -> bool {
        for (; first != last; ++first, ++other) {
            if (*first != *other) {
                return core::registry::on_error(scope);
            }
        }
        return core::registry::on_success(scope);
    }

    template <typename T, typename U, auto N>
    auto check_equal(const T (&array)[N], const U (&other)[N]) noexcept -> bool {
        for (auto i = 0; i < N; i++) {
            if (array[i] != other[i]) {
                return core::registry::on_error(scope);
            }
        }
        return core::registry::on_success(scope);
    }

    template <typename T, typename U>
    auto check_not_equal(const T& left, const U& right) noexcept -> bool {
        if (left != right) {
            return core::registry::on_success(scope);
        } else {
            return core::registry::on_error(scope);
        }
    }

    template <typename T, typename U>
    auto check_not_equal(T first, T last, U other) noexcept -> bool {
        for (; first != last; ++first, ++other) {
            if (*first != *other) {
                return core::registry::on_success(scope);
            }
        }
        return core::registry::on_error(scope);
    }

    template <typename T, typename U, auto N>
    auto check_not_equal(const T (&array)[N], const U (&other)[N]) noexcept -> bool {
        for (auto i = 0; i < N; i++) {
            if (array[i] != other[i]) {
                return core::registry::on_success(scope);
            }
        }
        return core::registry::on_error(scope);
    }

    template <typename T, typename U>
    auto check_less(const T& left, const U& right) noexcept -> bool {
        if (left < right) {
            return core::registry::on_success(scope);
        } else {
            return core::registry::on_error(scope);
        }
    }

    template <typename T, typename U>
    auto check_not_less(const T& left, const U& right) noexcept -> bool {
        if (left >= right) {
            return core::registry::on_success(scope);
        } else {
            return core::registry::on_error(scope);
        }
    }

    template <typename T, typename U>
    auto check_greater(const T& left, const U& right) noexcept -> bool {
        if (left > right) {
            return core::registry::on_success(scope);
        } else {
            return core::registry::on_error(scope);
        }
    }

    template <typename T, typename U>
    auto check_not_greater(const T& left, const U& right) noexcept -> bool {
        if (left <= right) {
            return core::registry::on_success(scope);
        } else {
            return core::registry::on_error(scope);
        }
    }

    template <typename T, typename... U>
    auto check_throws(T&& function, U&&... args) noexcept -> bool {
        try {
            function(core::forward<U>(args)...);
            return core::registry::on_error(scope);
        } catch (...) {
            return core::registry::on_success(scope);
        }
    }

    template <typename T, typename... U>
    auto check_nothrows(T&& function, U&&... args) noexcept -> bool {
        try {
            function(core::forward<U>(args)...);
            return core::registry::on_success(scope);
        } catch (...) {
            return core::registry::on_error(scope);
        }
    }

    template <typename T, typename U>
    auto check_sorted(T first, T last, U&& compare) noexcept -> bool {
        if (first == last) {
            return core::registry::on_success(scope);
        } else {
            auto previous = first;
            if (++first == last) {
                return core::registry::on_success(scope);
            } else {
                for (; first != last; ++first, ++previous) {
                    if (!compare(*previous, *first)) {
                        return core::registry::on_error(scope);
                    }
                }
                return core::registry::on_success(scope);
            }
        }
    }

    template <typename T, typename U, auto N>
    auto check_sorted(const T (&array)[N], U&& compare) noexcept -> bool {
        auto first = core::begin(array);
        const auto last = core::end(array);
        if (N <= 1) {
            return core::registry::on_success(scope);
        } else {
            for (; first != last - 1; ++first) {
                if (!compare(*first, *(first + 1))) {
                    return core::registry::on_error(scope);
                }
            }
            return core::registry::on_success(scope);
        }
    }

}

#undef scope

#endif
