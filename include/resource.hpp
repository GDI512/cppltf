#ifndef VOID_TEST_RESOURCE_HPP
#define VOID_TEST_RESOURCE_HPP

namespace void_test {

    class resource {
      private:
        int value;
        resource* self;

      public:
        ~resource() noexcept;
        resource() noexcept;
        resource(resource&& other) noexcept;
        resource(const resource& other) noexcept;

      public:
        auto operator=(resource&& other) noexcept -> resource&;
        auto operator=(const resource& other) noexcept -> resource&;
    };

}

#endif
