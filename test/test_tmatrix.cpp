#include "TMatrix.h"
#include "..\src\TMatrix.cpp"
#include "..\src\TVector.cpp"

#include <gtest.h>

using testing::Types;

template <class T>
class TDynamicMatrixTest : public testing::Test {};
typedef Types<int, double> Implementations;

TYPED_TEST_CASE(TDynamicMatrixTest, Implementations);

TYPED_TEST(TDynamicMatrixTest, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<TypeParam> mat(3));
}

TYPED_TEST(TDynamicMatrixTest, can_not_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<TypeParam> mat(-1));
}

TYPED_TEST(TDynamicMatrixTest, can_get_matrix_size)
{
  TDynamicMatrix<TypeParam> mat(3);

  EXPECT_EQ(3, mat.GetSize());
}

TYPED_TEST(TDynamicMatrixTest, can_compare_matrix_equivalence)
{
  TDynamicMatrix<TypeParam> mat1(2);
  TDynamicMatrix<TypeParam> mat2(2);
  mat1[0][0] = 0;
  mat1[1][0] = 1;
  mat1[1][1] = 2;
  mat2[0][0] = 0;
  mat2[1][0] = 1;
  mat2[1][1] = 2;
  EXPECT_EQ(mat1 == mat2, true);
}

TYPED_TEST(TDynamicMatrixTest, can_compare_matrix_nonequivalence)
{
  TDynamicMatrix<TypeParam> mat1(2);
  TDynamicMatrix<TypeParam> mat2(2);
  mat1[0][0] = 0;
  mat1[1][0] = 1;
  mat1[1][1] = 2;
  mat2[0][0] = 1;
  mat2[1][0] = 1;
  mat2[1][1] = 2;
  EXPECT_EQ(mat1 != mat2, true);
}

TYPED_TEST(TDynamicMatrixTest, can_not_compare_empty_matrix_equivalence)
{
  TDynamicMatrix<TypeParam> mat1;
  TDynamicMatrix<TypeParam> mat2;
  ASSERT_ANY_THROW(mat1 == mat2);
}

TYPED_TEST(TDynamicMatrixTest, can_not_compare_empty_matrix_nonequivalence)
{
  TDynamicMatrix<TypeParam> mat1;
  TDynamicMatrix<TypeParam> mat2;
  ASSERT_ANY_THROW(mat1 != mat2);
}

TYPED_TEST(TDynamicMatrixTest, can_sum_matrixes)
{
  TDynamicMatrix<TypeParam> mat1(2);
  TDynamicMatrix<TypeParam> mat2(2);
  mat1[0][0] = 0;
  mat1[1][0] = 1;
  mat1[1][1] = 2;
  mat2[0][0] = 1;
  mat2[1][0] = 1;
  mat2[1][1] = 2;
  TDynamicMatrix<TypeParam> mat3 = mat1 + mat2;
  EXPECT_EQ(mat3[0][0], 1);
  EXPECT_EQ(mat3[1][0], 2);
  EXPECT_EQ(mat3[1][1], 4);
}

TYPED_TEST(TDynamicMatrixTest, can_substract_matrixes)
{
  TDynamicMatrix<TypeParam> mat1(2);
  TDynamicMatrix<TypeParam> mat2(2);
  mat1[0][0] = 3;
  mat1[1][0] = 2;
  mat1[1][1] = 6;
  mat2[0][0] = 1;
  mat2[1][0] = 1;
  mat2[1][1] = 2;
  TDynamicMatrix<TypeParam> mat3 = mat1 - mat2;
  EXPECT_EQ(mat3[0][0], 2);
  EXPECT_EQ(mat3[1][0], 1);
  EXPECT_EQ(mat3[1][1], 4);
}

TYPED_TEST(TDynamicMatrixTest, can_not_sum_empty_matrixes)
{
  TDynamicMatrix<TypeParam> mat1;
  TDynamicMatrix<TypeParam> mat2;
  ASSERT_ANY_THROW(TDynamicMatrix<TypeParam> mat3 = mat1 + mat2);
}

TYPED_TEST(TDynamicMatrixTest, can_not_substract_empty_matrixes)
{
  TDynamicMatrix<TypeParam> mat1;
  TDynamicMatrix<TypeParam> mat2;
  ASSERT_ANY_THROW(TDynamicMatrix<TypeParam> mat3 = mat1 - mat2);
}

TYPED_TEST(TDynamicMatrixTest, can_not_sum_matrixes_differrent_sizes)
{
  TDynamicMatrix<TypeParam> mat1(1);
  TDynamicMatrix<TypeParam> mat2(2);
  ASSERT_ANY_THROW(TDynamicMatrix<TypeParam> mat3 = mat1 + mat2);
}

TYPED_TEST(TDynamicMatrixTest, can_not_substract_matrixes_differrent_sizes)
{
  TDynamicMatrix<TypeParam> mat1(1);
  TDynamicMatrix<TypeParam> mat2(2);
  ASSERT_ANY_THROW(TDynamicMatrix<TypeParam> mat3 = mat1 - mat2);
}

TYPED_TEST(TDynamicMatrixTest, can_mult_matrixes)
{
  TDynamicMatrix<TypeParam> mat1(2);
  TDynamicMatrix<TypeParam> mat2(2);
  mat1[0][0] = 4;
  mat1[1][0] = 5;
  mat1[1][1] = 6;
  mat2[0][0] = 1;
  mat2[1][0] = 2;
  mat2[1][1] = 3;
  TDynamicMatrix<TypeParam> mat3 = mat1 * mat2;
  EXPECT_EQ(mat3[0][0], 4);
  EXPECT_EQ(mat3[1][0], 23);
  EXPECT_EQ(mat3[1][1], 18);
}

TYPED_TEST(TDynamicMatrixTest, can_mult_matrix_on_vector)
{
  TDynamicMatrix<TypeParam> mat(2);
  TDynamicVector<TypeParam> vec1(2);
  mat[0][0] = 1;
  mat[1][0] = 2;
  mat[1][1] = 3;
  vec1[0] = 1;
  vec1[1] = 2;
  TDynamicVector<TypeParam> vec2 = mat * vec1;
  EXPECT_EQ(vec2[0], 5);
  EXPECT_EQ(vec2[1], 6);
}

TYPED_TEST(TDynamicMatrixTest, can_mult_matrix_on_scalar)
{
  TDynamicMatrix<TypeParam> mat(2);
  mat[0][0] = 1;
  mat[1][0] = 2;
  mat[1][1] = 3;
  TDynamicMatrix<TypeParam> res = mat * 2;
  EXPECT_EQ(res[0][0], 2);
  EXPECT_EQ(res[1][0], 4);
  EXPECT_EQ(res[1][1], 6);
}