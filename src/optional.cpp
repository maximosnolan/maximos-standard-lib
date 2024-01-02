/*
C++ 23 __Optional Type Library
Author: Maximos Nolan
Last Updated: Feb 14, 2023
License: MIT

Special shoutout to Jason Turner for inspiring a good portion of this code.
*/

#include <stdexcept>
#include <type_traits>
#include <string>

template <typename underlying_type>
struct nullopt_t {
    explicit constexpr nullopt_t(underlying_type) {}
};


template <typename underlying_type>
class __Optional {

    private:

    bool is_active = false;

    union Data {

        constexpr ~Data() requires std::is_trivially_destructible_v<underlying_type> = default;
        constexpr ~Data() {}

        constexpr Data() requires std::is_trivially_constructible<underlying_type>::value = default;
        constexpr Data() {};

        constexpr Data(Data & d) requires std::is_trivially_copy_assignable_v<underlying_type> = default;

        underlying_type datum;

    };

    Data datum{};

   public:

    constexpr __Optional() requires std::is_trivially_constructible<underlying_type>::value = default;
    constexpr __Optional() {}
    constexpr ~__Optional() requires std::is_trivially_destructible_v<underlying_type> = default;

    constexpr ~__Optional() {
        if (is_active) {
            std::destroy_at(&datum.datum);
        }
    }

    [[nodiscard]] constexpr const underlying_type &get() noexcept {
        return datum.datum;
    }

    constexpr __Optional &operator=(const underlying_type &obj) noexcept {
        if (is_active) {
            datum.datum = obj;
        } else {
            is_active = true;
            std::construct_at(&datum.datum, obj);
        }

        return *this;
    }

    constexpr __Optional &operator*() {
        return datum.datum;
    }

    [[nodiscard]] constexpr bool has_value() const noexcept {
        return is_active;
    }

    [[nodiscard]] constexpr underlying_type unwrap_optional([[maybe_unused]] std::string && panic_msg) const {
        if (is_active) {
            return datum.datum;
        }
        throw std::runtime_error(panic_msg);
    }


    void reset() noexcept {
        is_active = false;
    }

};
