#include "mymatrix.h"
#include <iostream>
#include <iomanip>
#include <vector>

template <typename T>
std::ostream& operator<<(std::ostream& out, MyMatrix<T> const& mtx)
{
	std::size_t rows = mtx.rows();
	std::size_t cols = mtx.cols();

	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			out << std::setw(5) << mtx(i, j);
		}
		out << "\n";
	}
	return out;
}

int main()
{
	{
		// TO DO?
		// fm = im;
		// MyMatrix<int> im(fm);
		// fm==im

		// CONSTRUCTORS
		MyMatrix<float> fm;
		std::cout << "fill fm" << "\n";
		std::fill(fm.begin(), fm.end(), 3);
		std::cout << fm;

		std::cout << "iterator constructor sm" << "\n";
		MyMatrix<std::string> sm{ 3, 2, { "one", "two", "three", "four", "five", "six" } };
		std::cout << sm;

		std::cout << "iterator constructor im" << "\n";
		std::vector<int> vec{0,1,0,3,0,5,6,5,7};
		MyMatrix<int> im(vec.begin(), vec.end(), 3, 3);
		std::cout << im;

		// Mathematical operations
		std::cout << "auto doppel = fm + im" << "\n";
		auto doppel = fm + im;
		std::cout << doppel;

		std::cout << "auto doppel = im - fm" << "\n";
		auto doppel1 = im - fm;
		std::cout << doppel1;

		std::cout << "auto doppel = fm * im" << "\n";
		auto doppel2 = fm * im;
		std::cout << doppel2;

		// Access operators with validation
		std::cout << "im(1, 2): " << im(1, 2) << "\n"
			<< "im[5]: " << im[5] << "\n";
		// Exception case
		// std::cout << "fm(0,4): " << fm(0, 4) << "\n";
		//	<< "fm[3]: " << fm[3] << "\n";
		
		// Unary operators
		std::cout << "-fm" << "\n";
		std::cout << -fm;

		std::cout << "+fm" << "\n";
		std::cout << +fm;

		// Matrix scalar operations
		std::cout << "fm = fm+2" << "\n";
		fm = fm + 2.0f;
		std::cout << fm;

		std::cout << "fm = fm-2" << "\n";
		fm = fm - 2L;
		std::cout << fm;

		std::cout << "fm = fm*2" << "\n";
		fm = fm * 2;
		std::cout << fm;

		std::cout << "fm = fm/2" << "\n";
		fm = fm / 2u;
		std::cout << fm;

		// Comparision
		std::cout << "fm==fm" << "\n";
		if (fm == fm) std::cout << "equal" << "\n";
		std::cout << "fm!=fm" << "\n";
		if (fm != fm) std::cout << "not equal" << "\n";

		// Transpose
		std::cout << "mtx" << "\n";
		MyMatrix<float> mtx{ 2, 4, { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0} };
		std::cout << mtx << "\n";
		std::cout << "mtx transpose" << "\n";
		mtx = transpose(mtx);
		std::cout << mtx << "\n";

		std::cout << "mtx inverse" << "\n";
		mtx = inverse(mtx);
		std::cout << mtx << "\n";

		std::cout << "mtx diagonalizesymmetric" << "\n";
		im = symmetric(im);
		std::cout << im << "\n";

		std::cout << "ident fm" << "\n";
		fm.ident();
		std::cout << fm;

		MyMatrix<bool> b{ 5, 5 };
		std::cout << b << "\n";

	}

	system("pause");



	return 0;
}