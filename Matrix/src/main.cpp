#include "mymatrix.h"
#include <iostream>

int main()
{
	{
		MyMatrix<float> fm{ 3, 3 };
		std::cout << "fill fm" << std::endl;
		std::fill(fm.begin(), fm.end(), 3);
		std::cout << fm;

		//std::cout << "ident fm" << std::endl;
		//fm.ident();
		//std::cout << fm;

		std::cout << "iterator constructor im" << std::endl;
		std::vector<int> vec{0,1,0,3,0,5,6,5,7};
		MyMatrix<int> im(vec.begin(), vec.end(), 3, 3);
		std::cout << im;

		std::cout << "fm += im" << std::endl;
		fm += im;
		std::cout << fm;

		std::cout << "im += fm" << std::endl;
		im += fm;
		std::cout << im;

		std::cout << "auto doppel = fm + im" << std::endl;
		auto doppel = fm + im;
		std::cout << doppel;

		//std::cout << "a - b" << std::endl;
		//a = a - b;
		//std::cout << a;

		//std::cout << "a = b" << std::endl;
		//a = b;
		//std::cout << a;

		//// Multiplication
		//std::cout << "a(2, 3) * b(3, 2)" << std::endl;
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
		//std::cout << mtx2(2, 1) << std::endl;
		//// mtx2(2, 2); // ASSERTION ERROR!

		//// Comparision
		//std::cout << "a==b" << std::endl;
		//if (a == b) std::cout << "equal" << std::endl;
		//std::cout << "mtx1!=mtx2" << std::endl;
		//if (mtx1 != mtx2) std::cout << "not equal" << std::endl;

		//// Transpose
		//std::cout << "mtx2 before transpose" << std::endl;
		//std::cout << mtx2 << "\n";
		//std::cout << "mtx2 after transpose" << std::endl;
		//mtx2 = transpose(mtx2);
		//std::cout << mtx2 << "\n";

		//std::cout << "matrix scalar operations" << std::endl;
		//std::cout << "- + * /" << std::endl;
		//mtx2 = mtx2 - 2;
		//std::cout << mtx2 << "\n";
		//mtx2 = mtx2 + 2;
		//std::cout << mtx2 << "\n";
		//mtx2 = mtx2 * 2;
		//std::cout << mtx2 << "\n";
		//mtx2 = mtx2 / 2;
		//std::cout << mtx2 << "\n";

		//std::cout << "mtx1 inverse" << std::endl;
		//mtx2 = inverse(mtx2);
		//std::cout << mtx2 << "\n";

		//std::cout << "a diagonalizesymmetric" << std::endl;
		//a.fillRand();
		//a = symmetric(a);
		//std::cout << a << "\n";

		//std::cout << "symmetric" << std::endl;
		//std::vector<float> vec{0,1,0,3,0,5,6,5,7,0,0,0};
		//MyMatrix<float> mtx4(vec.begin(), vec.end(), 4, 3);
		//std::cout << mtx4;
	}

	system("pause");



	return 0;
}