#include <type_traits>
#include <utility>
#include <cstddef>

template <std::size_t _idx, typename T>
class __tuple_impl {
    private:
        T datum;

    public:
        constexpr __tuple_impl(T const & datum) : datum(datum) {};
        constexpr __tuple_impl(T && datum) {
            datum = std::move(datum);
        }
        [[nodiscard]] constexpr inline T & get() noexcept {
            return datum;
        }

};

template<std::size_t _idx, typename... types>
class __tuple_base {};

template <std::size_t _idx, typename Curr, typename... types>
class __tuple_base<_idx, Curr, types...> : public __tuple_impl<
    _idx,
    typename std::remove_reference<Curr>::type>,
    public __tuple_base<
        _idx + 1,
        types...>
{
    public:
    template<typename C, typename... CArgs>
        constexpr __tuple_base(C && arg, CArgs &&... args) : __tuple_impl<
                                                _idx, typename std::remove_reference<C>::type>(std::forward<C>(arg)),
                                                __tuple_base<
                                                    _idx + 1,
                                                    types...>(std::forward<CArgs>(args)...){}
};


template <typename L, typename... types>
class tuple : public __tuple_base<0, L, types...> {

    public:
        template <typename... CArgs>
        constexpr tuple(CArgs && ... args) : __tuple_base<0, L, types...>(std::forward<CArgs>(args)...) {}

        template <typename ... Args>
        friend bool operator==(tuple<Args...> &tuple1, tuple<Args...> &tuple2);
};

template <typename ... CArgs>
tuple(CArgs ... args)->tuple<CArgs...>;

template <std::size_t _idx, typename L, typename ... Args>
struct extract_type {
    using type = typename extract_type<_idx - 1, Args...>::type;
};

template<typename L, typename ... Args>
struct extract_type<0, L, Args...>  {
    using type = L;
};

template <std::size_t _idx, typename... Args>
[[nodiscard]] inline constexpr auto &get(tuple<Args...> & tuple) {
    return (static_cast<__tuple_impl<_idx, typename extract_type<_idx, Args...>::type> &>(tuple)).get();
}

template <std::size_t _idx, typename... Args>
[[nodiscard]] inline bool cmp(tuple<Args...> &tuple1, tuple<Args...> &tuple2) {
    if constexpr (_idx != 0) {
        return get<_idx>(tuple1) == get<_idx>(tuple2) && cmp<_idx - 1>(tuple1, tuple2);
    } else {
        return get<_idx>(tuple1) == get<_idx>(tuple2);
    }
}

template <typename... Args>
[[nodiscard]] inline bool operator==(tuple<Args...> &tuple1, tuple<Args...> &tuple2) {
    return cmp<sizeof...(Args) - 1>(tuple1, tuple2);
}
