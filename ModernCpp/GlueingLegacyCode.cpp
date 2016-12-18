#include <iostream>
#include <tuple>

// Legacy code that takes: int, char*, char*, char*
void printt(int x, const char *s1, const char* s2, const char* s3) {
    std::cout << x << ' ' << s1 << ' ' << s2 << ' ' << s3 << std::endl;
}


/*
 * Robast glue code that adapts Legacy code's signature change.
 * The only thing we need to change in our side is change the tuple providing the same number of params.
 *
 * In the Glue code: First we determine the number of parameters that the tuple contains
 * then we unpack the tuple and call "printt"
 */
template <typename ...Params, std::size_t ...I>
void print_tuple(std::tuple<Params...> &t, std::index_sequence<I...>) {
    printt(std::get<I>(t)...);
}

template <typename ...Params>
void magic_wand(std::tuple<Params...> &t) {
    static const std::size_t params_count = sizeof...(Params);
    print_tuple(t, std::make_index_sequence<params_count>());
}

int main() {
    auto x = std::make_tuple(12, "hello world", "2016", "!!!");
    magic_wand(x);

    return 0;
}
