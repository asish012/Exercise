#include <iostream>

/**
 * Factorial
 *
 * */
template <int N>
struct Factorial {
	static const int result = N * Factorial<N -1>::result;
};

template <>
struct Factorial<1>{
	static const int result = 1;
};

/**
 * Fraction
 *
 * */
template <int N, int D>
struct Fraction {
	static const int Num = N;
	static const int Den = D;
};

template <int N, typename F>
struct ScalerMultiplication {
	typedef Fraction<F::Num * N, F::Den * N> result;
};


int main() {
//	std::cout << "Factorial of 5: " << Factorial<5>::result << '\n';

//	typedef ScalerMultiplication<3, Fraction<2, 4>>::result result;
//	std::cout << "ScalerMultiplication of 3 * 2/4: " << result::Num << "/" << result::Den << '\n';
}
