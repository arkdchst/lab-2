#include "base.h"
#include "sequence.h"
#include "matrix.h"

#define BOOST_TEST_MODULE tests
#include <boost/test/included/unit_test.hpp>

BOOST_TEST_DONT_PRINT_LOG_VALUE( DynamicArray<int> )
BOOST_TEST_DONT_PRINT_LOG_VALUE( LinkedList<int> )
BOOST_TEST_DONT_PRINT_LOG_VALUE( ArraySequence<int> )
BOOST_TEST_DONT_PRINT_LOG_VALUE( ListSequence<int> )



BOOST_AUTO_TEST_CASE(dynamic_array){
	int initArr1[] = {1,2,3,4,5};
	int initArr2[] = {0,2,3,4,5,6};
	int initArr3[] = {0,2,3,4};

	DynamicArray<int> arr1(initArr1, 5);

		BOOST_CHECK_THROW(DynamicArray<int>(-1), std::exception);
		BOOST_CHECK_THROW(arr1.get(-1), std::exception);
		BOOST_CHECK_THROW(arr1.get(5), std::exception);

		BOOST_TEST(arr1 == DynamicArray<int>(arr1));
		BOOST_TEST(arr1 == DynamicArray<int>(arr1, 5));
		BOOST_TEST(DynamicArray<int>() == DynamicArray<int>((int*)0, 0));
		BOOST_TEST(arr1.get(0) == 1);
		BOOST_TEST(arr1.get(3) == 4);
		BOOST_TEST(arr1.get(4) == 5);
		BOOST_TEST(arr1.getSize() == 5);


		BOOST_REQUIRE_THROW(arr1.set(5, 5), std::exception);
		BOOST_REQUIRE_THROW(arr1.resize(-6), std::exception);

	arr1.resize(6);
	arr1.set(0, 0);
	arr1.set(6, 5);
		BOOST_TEST(arr1 == DynamicArray<int>(initArr2, 6));
	arr1.resize(4);
		BOOST_TEST(arr1 == DynamicArray<int>(initArr3, 4));
}

BOOST_AUTO_TEST_CASE(linked_list){
	int initArr1[] = {1,2,3,5};
	int initArr2[] = {-1,0,1,2,3,4,5,6,7};
	int initArr3[] = {-1};
	int initArr35[] = {-2,0,1,2,3,4,5,0,8};
	int initArr4[] = {0,1,2,3,5,0};
	int initArr5[] = {0,1,2,3,5,0,-1};
	int initArr6[] = {0,1,2,3,5,0,1,2,3,5};

	LinkedList<int> list1(initArr1, 4);	

		BOOST_CHECK_THROW(LinkedList<int>(-1), std::exception);
		BOOST_CHECK_THROW(LinkedList<int>(initArr1, -1), std::exception);

		BOOST_CHECK_THROW(list1.get(-1), std::exception);
		BOOST_CHECK_THROW(list1.get(4), std::exception);
		BOOST_CHECK_THROW(LinkedList<int>().getFirst(), std::exception);
		BOOST_CHECK_THROW(LinkedList<int>().getLast(), std::exception);

		BOOST_TEST(list1 == LinkedList<int>(list1));
		BOOST_TEST(LinkedList<int>() == LinkedList<int>((int*)0, 0));
		BOOST_TEST(list1.get(0) == 1);
		BOOST_TEST(list1.getFirst() == 1);
		BOOST_TEST(list1.get(2) == 3);
		BOOST_TEST(list1.get(3) == 5);
		BOOST_TEST(list1.getLast() == 5);
		BOOST_TEST(list1.getSize() == 4);

		BOOST_REQUIRE_THROW(list1.insertAt(4, 5), std::exception);

	list1.prepend(0);
	list1.append(6);
	list1.insertAt(-1,0);
	list1.insertAt(7,7);
	list1.insertAt(4,5);
		BOOST_TEST(list1 == LinkedList<int>(initArr2,9));

		BOOST_CHECK_THROW(list1.getSublist(3, 1), std::exception);
		BOOST_CHECK_THROW(list1.getSublist(1, 10), std::exception);
		BOOST_CHECK_THROW(list1.getSublist(-1, 3), std::exception);

	LinkedList<int> *list2 = list1.getSublist(0,0);
	LinkedList<int> *list3 = list1.getSublist(0,1);
	LinkedList<int> *list4 = list1.getSublist(0,9);
		BOOST_TEST(*list2 == LinkedList<int>());
		BOOST_TEST(*list3 == LinkedList<int>(initArr3,1));
		BOOST_TEST(*list4 == list1);

		BOOST_REQUIRE_THROW(list1.set(4, 10), std::exception);

	list1.set(-2,0);
	list1.set(8,8);
	list1.set(0,7);
		BOOST_TEST(list1 == LinkedList<int>(initArr35,9));

		BOOST_REQUIRE_THROW(list1.removeAt(-1), std::exception);
		BOOST_REQUIRE_THROW(list1.removeAt(10), std::exception);

	list1.removeAt(0);
	list1.removeAt(7);
	list1.removeAt(4);
		BOOST_TEST(list1 == LinkedList<int>(initArr4,6));

	LinkedList<int> *list5 = list1.concat(LinkedList<int>());
	LinkedList<int> *list6 = list1.concat(LinkedList<int>(initArr3, 1));
	LinkedList<int> *list7 = list1.concat(LinkedList<int>(initArr1, 4));
		BOOST_TEST(*list5 == list1);
		BOOST_TEST(*list6 == LinkedList<int>(initArr5,7));
		BOOST_TEST(*list7 == LinkedList<int>(initArr6,10));

	delete list2;
	delete list3;
	delete list4;
	delete list5;
	delete list6;
	delete list7;
}


BOOST_AUTO_TEST_CASE(array_sequence){
	int initArr1[] = {1,2,3,5};
	int initArr2[] = {-1,0,1,2,3,4,5,6,7};
	int initArr3[] = {-1};
	int initArr35[] = {-2,0,1,2,3,4,5,0,8};
	int initArr4[] = {0,1,2,3,5,6};
	int initArr5[] = {-2,0,1,2,3,4,5,0,8,-1};
	int initArr6[] = {-2,0,1,2,3,4,5,0,8,1,2,3,5};

	ArraySequence<int> seq1(initArr1, 4);	

		BOOST_CHECK_THROW(ArraySequence<int>(initArr1, -1), std::exception);

		BOOST_CHECK_THROW(ArraySequence<int>(0).getFirst(), std::exception);
		BOOST_CHECK_THROW(ArraySequence<int>(0).getLast(), std::exception);
		BOOST_CHECK_THROW(seq1.get(-1), std::exception);
		BOOST_CHECK_THROW(seq1.get(10), std::exception);

		BOOST_TEST(seq1 == ArraySequence<int>(seq1));
		BOOST_TEST(ArraySequence<int>() == ArraySequence<int>((int*)0, 0));
		BOOST_TEST(seq1.get(0) == 1);
		BOOST_TEST(seq1.getFirst() == 1);
		BOOST_TEST(seq1.get(2) == 3);
		BOOST_TEST(seq1.get(3) == 5);
		BOOST_TEST(seq1.getLast() == 5);
		BOOST_TEST(seq1.getSize() == 4);

		BOOST_REQUIRE_THROW(seq1.insertAt(0, -1), std::exception);
		BOOST_REQUIRE_THROW(seq1.insertAt(0, 5), std::exception);

	seq1.prepend(0);
	seq1.append(6);
	seq1.insertAt(-1,0);
	seq1.insertAt(7,7);
	seq1.insertAt(4,5);
		BOOST_TEST(seq1 == ArraySequence<int>(initArr2,9));
	
		BOOST_CHECK_THROW(seq1.getSubsequence(3, 1), std::exception);
		BOOST_CHECK_THROW(seq1.getSubsequence(1, 10), std::exception);
		BOOST_CHECK_THROW(seq1.getSubsequence(-1, 3), std::exception);


	ArraySequence<int> *seq2 = seq1.getSubsequence(0,0);
	ArraySequence<int> *seq3 = seq1.getSubsequence(0,1);
	ArraySequence<int> *seq4 = seq1.getSubsequence(0,9);
		
		BOOST_TEST(*seq2 == ArraySequence<int>());
		BOOST_TEST(*seq3 == ArraySequence<int>(initArr3,1));
		BOOST_TEST(*seq4 == seq1);


		BOOST_REQUIRE_THROW(seq1.set(0, -1), std::exception);
		BOOST_REQUIRE_THROW(seq1.set(0, 10), std::exception);


	seq1.set(-2,0);
	seq1.set(8,8);
	seq1.set(0,7);
		BOOST_TEST(seq1 == ArraySequence<int>(initArr35,9));

	ArraySequence<int> *seq5 = seq1.concat(ArraySequence<int>());
	ArraySequence<int> *seq6 = seq1.concat(ArraySequence<int>(initArr3, 1));
	ArraySequence<int> *seq7 = seq1.concat(ArraySequence<int>(initArr1, 4));
		BOOST_TEST(*seq5 == seq1);
		BOOST_TEST(*seq6 == ArraySequence<int>(initArr5,10));
		BOOST_TEST(*seq7 == ArraySequence<int>(initArr6,13));

	delete seq2;
	delete seq3;
	delete seq4;
	delete seq5;
	delete seq6;
	delete seq7;
}


BOOST_AUTO_TEST_CASE(list_sequence){
	int initArr1[] = {1,2,3,5};
	int initArr2[] = {-1,0,1,2,3,4,5,6,7};
	int initArr3[] = {-1};
	int initArr35[] = {-2,0,1,2,3,4,5,0,8};
	int initArr4[] = {0,1,2,3,5,6};
	int initArr5[] = {-2,0,1,2,3,4,5,0,8,-1};
	int initArr6[] = {-2,0,1,2,3,4,5,0,8,1,2,3,5};

	ListSequence<int> seq1(initArr1, 4);	

		BOOST_CHECK_THROW(ListSequence<int>(initArr1, -1), std::exception);
		BOOST_CHECK_THROW(ListSequence<int>(0).getFirst(), std::exception);
		BOOST_CHECK_THROW(ListSequence<int>(0).getLast(), std::exception);
		BOOST_CHECK_THROW(seq1.get(-1), std::exception);
		BOOST_CHECK_THROW(seq1.get(10), std::exception);

		BOOST_TEST(seq1 == ListSequence<int>(seq1));
		BOOST_TEST(ListSequence<int>() == ListSequence<int>((int*)0, 0));
		BOOST_TEST(seq1.get(0) == 1);
		BOOST_TEST(seq1.getFirst() == 1);
		BOOST_TEST(seq1.get(2) == 3);
		BOOST_TEST(seq1.get(3) == 5);
		BOOST_TEST(seq1.getLast() == 5);
		BOOST_TEST(seq1.getSize() == 4);

		BOOST_REQUIRE_THROW(seq1.insertAt(0, -1), std::exception);
		BOOST_REQUIRE_THROW(seq1.insertAt(0, 5), std::exception);

	seq1.prepend(0);
	seq1.append(6);
	seq1.insertAt(-1,0);
	seq1.insertAt(7,7);
	seq1.insertAt(4,5);
		BOOST_TEST(seq1 == ListSequence<int>(initArr2,9));
	
		BOOST_CHECK_THROW(seq1.getSubsequence(3, 1), std::exception);
		BOOST_CHECK_THROW(seq1.getSubsequence(1, 10), std::exception);
		BOOST_CHECK_THROW(seq1.getSubsequence(-1, 3), std::exception);

	ListSequence<int> *seq2 = seq1.getSubsequence(0,0);
	ListSequence<int> *seq3 = seq1.getSubsequence(0,1);
	ListSequence<int> *seq4 = seq1.getSubsequence(0,9);
		BOOST_TEST(*seq2 == ListSequence<int>());
		BOOST_TEST(*seq3 == ListSequence<int>(initArr3,1));
		BOOST_TEST(*seq4 == seq1);

		BOOST_REQUIRE_THROW(seq1.set(0, -1), std::exception);
		BOOST_REQUIRE_THROW(seq1.set(0, 10), std::exception);

	seq1.set(-2,0);
	seq1.set(8,8);
	seq1.set(0,7);
		BOOST_TEST(seq1 == ListSequence<int>(initArr35,9));

	ListSequence<int> *seq5 = seq1.concat(ListSequence<int>());
	ListSequence<int> *seq6 = seq1.concat(ListSequence<int>(initArr3, 1));
	ListSequence<int> *seq7 = seq1.concat(ListSequence<int>(initArr1, 4));
		BOOST_TEST(*seq5 == seq1);
		BOOST_TEST(*seq6 == ListSequence<int>(initArr5,10));
		BOOST_TEST(*seq7 == ListSequence<int>(initArr6,13));

	delete seq2;
	delete seq3;
	delete seq4;
	delete seq5;
	delete seq6;
	delete seq7;

}


BOOST_AUTO_TEST_CASE(diagonal_matrix){
	DiagonalMatrix<int> mat1(5, 3, 5);
	mat1.set(1, 0, 0);
	mat1.set(2, 1, 0);
	mat1.set(3, 2, 0);
	mat1.set(4, 0, 1);
	mat1.set(5, 1, 1);
	mat1.set(6, 2, 1);
	mat1.set(7, 3, 1);
	mat1.set(8, 0, 2);
	mat1.set(9, 1, 2);
	mat1.set(10, 2, 2);
	mat1.set(11, 3, 2);
	mat1.set(12, 4, 2);

	DiagonalMatrix<int> mat2(5, 3, 1);
	mat2.set(1, 0, 0);
	mat2.set(2, 1, 1);
	mat2.set(3, 2, 2);

	DiagonalMatrix<int> *mat3 = mat1 + mat2;
	DiagonalMatrix<int> *mat4 = *mat3 * 2;

		BOOST_CHECK_THROW(mat4->get(0, -1), std::exception);
		BOOST_CHECK_THROW(mat4->get(-1, 0), std::exception);
		BOOST_CHECK_THROW(mat4->get(10, 0), std::exception);
		BOOST_CHECK_THROW(mat4->get(0, 10), std::exception);
		BOOST_CHECK_THROW(mat4->set(0, 10, 0), std::exception);
		BOOST_CHECK_THROW(mat4->set(0, 0, 10), std::exception);
		BOOST_CHECK_NO_THROW(mat4->get(0, 0));

		BOOST_TEST(mat4->getWidth() == 5);
		BOOST_TEST(mat4->getHeight() == 3);
		BOOST_TEST(mat4->getDiag() == 5);
		BOOST_TEST(mat4->get(0, 0) == 4);
		BOOST_TEST(mat4->get(1, 2) == 18);
		BOOST_TEST(mat4->get(0, 2) == 16);
		BOOST_TEST(mat4->get(4, 0) == 0);
		BOOST_TEST(mat4->get(2, 2) == 26);

		BOOST_TEST(mat4->getNorm<float>() == 54.6, boost::test_tools::tolerance(0.1));

	delete mat3;
	delete mat4;
}
