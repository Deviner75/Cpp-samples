#include "mymatrix.h"
#include <iostream>
#include <iomanip>

template <typename T>
std::ostream& operator<<(std::ostream& out, MyMatrix<T> const& mtx)
{
	std::size_t rows = mtx.rows();
	std::size_t cols = mtx.cols();

	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			out << std::setw(3) << mtx(i, j);
		}
		out << "\n";
	}
	return out;
}

int main()
{
	{
		// CONSTRUCTORS
		MyMatrix<float> fm{ 3, 3 };
		std::cout << "fill fm" << "\n";
		std::fill(fm.begin(), fm.end(), 3);
		std::cout << fm;

		// TO DO
		//std::cout << "MyMatrix<int> im(fm);" << "\n";
		//std::cout << im;

		std::cout << "iterator constructor im" << "\n";
		MyMatrix<std::string> sm{ 3, 2, { "one", "two", "three", "four", "five", "six" } };

		std::cout << "iterator constructor im" << "\n";
		std::vector<int> vec{0,1,0,3,0,5,6,5,7};
		MyMatrix<int> im(vec.begin(), vec.end(), 3, 3);
		std::cout << im;


		// Mathematical operations
		std::cout << "auto doppel = fm + im" << "\n";
		auto doppel = fm + im;
		// fm = im + fm; ??
		std::cout << doppel;

		std::cout << "auto doppel = im - fm" << "\n";
		auto doppel1 = im - fm;
		// fm = im - fm; ??
		std::cout << doppel1;

		std::cout << "auto doppel = fm * im" << "\n";
		doppel = fm * im;
		// fm = im - fm; ??
		std::cout << doppel;

		//std::cout << "-fm" << "\n";
		//std::cout << -fm;

		//std::cout << "+fm" << "\n";
		//std::cout << +fm;













		//std::cout << "a - b" << "\n";
		//a = a - b;
		//std::cout << a;

		//std::cout << "a = b" << "\n";
		//a = b;
		//std::cout << a;

		//// Multiplication
		//std::cout << "a(2, 3) * b(3, 2)" << "\n";
		//MyMatrix<float> mtx1(2, 3);
		//MyMatrix<float> mtx2(3, 2);
		//mtx1.fillRand();
		//mtx2.fillRand();
		//std::cout << mtx1;
		//std::cout << mtx2;

		//mtx1 = mtx1 * mtx2;
		//std::cout << mtx1;

		//// Element access
		//std::cout << "mtx2(2, 1)" << "\n";
		//std::cout << mtx2(2, 1) << "\n";
		//// mtx2(2, 2); // ASSERTION ERROR!

		//// Comparision
		//std::cout << "a==b" << "\n";
		//if (a == b) std::cout << "equal" << "\n";
		//std::cout << "mtx1!=mtx2" << "\n";
		//if (mtx1 != mtx2) std::cout << "not equal" << "\n";

		//// Transpose
		//std::cout << "mtx2 before transpose" << "\n";
		//std::cout << mtx2 << "\n";
		//std::cout << "mtx2 after transpose" << "\n";
		//mtx2 = transpose(mtx2);
		//std::cout << mtx2 << "\n";

		//std::cout << "matrix scalar operations" << "\n";
		//std::cout << "- + * /" << "\n";
		//mtx2 = mtx2 - 2;
		//std::cout << mtx2 << "\n";
		//mtx2 = mtx2 + 2;
		//std::cout << mtx2 << "\n";
		//mtx2 = mtx2 * 2;
		//std::cout << mtx2 << "\n";
		//mtx2 = mtx2 / 2;
		//std::cout << mtx2 << "\n";

		//std::cout << "mtx1 inverse" << "\n";
		//mtx2 = inverse(mtx2);
		//std::cout << mtx2 << "\n";

		//std::cout << "a diagonalizesymmetric" << "\n";
		//a.fillRand();
		//a = symmetric(a);
		//std::cout << a << "\n";

		//std::cout << "symmetric" << "\n";
		//std::vector<float> vec{0,1,0,3,0,5,6,5,7,0,0,0};
		//MyMatrix<float> mtx4(vec.begin(), vec.end(), 4, 3);
		//std::cout << mtx4;

		//std::cout << "ident fm" << "\n";
		//fm.ident();
		//std::cout << fm;
	}

	system("pause");



	return 0;
}