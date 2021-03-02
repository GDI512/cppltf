#ifndef CPPLTF_TYPE_HPP
#define CPPLTF_TYPE_HPP

namespace test {

    class object {
      private:
        volatile int number;
        volatile int value;
        volatile object* self;

      public:
        ~object() noexcept;
        object(int number = 0) noexcept;
        object(object&& other) noexcept;
        object(const object& other) noexcept;

      public:
        operator int() const noexcept;
        auto operator=(object&& other) noexcept -> object&;
        auto operator=(const object& other) noexcept -> object&;

      private:
        auto is_self() const noexcept -> bool;
        auto is_initialized() const noexcept -> bool;
        auto is_uninitialized() const noexcept -> bool;
    };

    class counter {
      private:
        int number;

      public:
        ~counter() noexcept;
        counter(int number = 0) noexcept;
        counter(counter&& other) noexcept;
        counter(const counter& other) noexcept;

      public:
        operator int() const noexcept;
        auto operator=(counter&& other) noexcept -> counter&;
        auto operator=(const counter& other) noexcept -> counter&;
    };

}

#endif
