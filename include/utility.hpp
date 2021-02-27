#ifndef CPPLTF_UTILITY_HPP
#define CPPLTF_UTILITY_HPP

namespace test::aux {

    struct true_type {
        static constexpr auto value = true;
    };

    struct false_type {
        static constexpr auto value = false;
    };

    template <typename T>
    struct remove_reference {
        using type = T;
    };

    template <typename T>
    struct remove_reference<T&> {
        using type = T;
    };

    template <typename T>
    struct remove_reference<T&&> {
        using type = T;
    };

    template <typename T, typename U>
    struct is_same : false_type {};

    template <typename T>
    struct is_same<T, T> : true_type {};

    template <typename T>
    struct is_lvalue_reference : false_type {};

    template <typename T>
    struct is_lvalue_reference<T&> : true_type {};

    using size_type = decltype(sizeof(int));
    using difference_type = decltype(static_cast<int*>(0) - static_cast<int*>(0));

    template <typename T, auto N>
    constexpr auto begin(T (&array)[N]) {
        return static_cast<T*>(array);
    }

    template <typename T, auto N>
    constexpr auto begin(const T (&array)[N]) {
        return static_cast<const T*>(array);
    }

    template <typename T>
    constexpr decltype(auto) begin(T& container) {
        return container.begin();
    }

    template <typename T>
    constexpr decltype(auto) begin(const T& container) {
        return container.begin();
    }

    template <typename T, auto N>
    constexpr auto end(T (&array)[N]) {
        return array + N;
    }

    template <typename T, auto N>
    constexpr auto end(const T (&array)[N]) {
        return array + N;
    }

    template <typename T>
    constexpr decltype(auto) end(T& container) {
        return container.end();
    }

    template <typename T>
    constexpr decltype(auto) end(const T& container) {
        return container.end();
    }

    template <typename T>
    constexpr decltype(auto) move(T&& value) noexcept {
        return static_cast<typename remove_reference<T>::type&&>(value);
    }

    template <typename T>
    constexpr decltype(auto) forward(typename remove_reference<T>::type& value) noexcept {
        return static_cast<T&&>(value);
    }

    template <typename T>
    constexpr decltype(auto) forward(typename remove_reference<T>::type&& value) noexcept {
        static_assert(!is_lvalue_reference<T>::value);
        return static_cast<T&&>(value);
    }

    template <typename T, typename U>
    constexpr auto exchange(T& value, U&& new_value) {
        auto old = aux::move(value);
        value = aux::forward<U>(new_value);
        return old;
    }

    template <typename I, typename F>
    constexpr auto is_sorted(I first, I last, F&& comparison) {
        if (first != last) {
            auto next = first;
            while (++next != last) {
                if (!comparison(*first, *next))
                    return false;
                first = next;
            }
        }
        return true;
    }

    template <typename I, typename F>
    constexpr auto all_of(I first, I last, F&& predicate) {
        for (; first != last; ++first)
            if (!predicate(*first))
                return false;
        return true;
    }

    template <typename I, typename O>
    constexpr auto equal(I first, I last, O other) {
        for (; first != last; ++first, ++other)
            if (*first != *other)
                return false;
        return true;
    }

    template <typename I, typename T>
    constexpr auto find(I first, I last, const T& value) {
        for (; first != last; ++first)
            if (*first == value)
                return first;
        return last;
    }

}

#endif
