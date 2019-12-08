cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(chapter_three)

set(CMAKE_CXX_STANDARD 11)

# add_executable(director
# 	"director.cpp"
# 	"array.cpp"
# 	"lattice.cpp"
# 	"arraymechanisms.cpp"
# 	"arraystructure.cpp"
# 	"binomiallatticestrategy.cpp"
# 	"binomialmethod.cpp"
# 	"europeanoptionfactory.hpp"
# 	"fullarray.cpp"
# 	"fullmatrix.cpp"
# 	"latticemechanisms.cpp"
# 	"matrix.cpp"
# 	"matrixmechanisms.cpp"
# 	"matrixstructure.cpp"
# 	"numericmatrix.cpp"
# 	"option.hpp"
# 	"property.cpp"
# 	"propertything.cpp"
# 	"range.cpp"
# 	"set.cpp"
# 	"simplepropertyset.cpp"
# 	"tensor.cpp"
# 	"vector.cpp"
# )

add_executable(testBinomialMethod
	"testBinomialMethod.cpp"
	"binomialmethod.cpp"
	"lattice.cpp"
	"arraymechanisms.cpp"
	"arraystructure.cpp"
	"binomiallatticestrategy.cpp"
	"binomialmethod.cpp"
	"europeanoptionfactory.hpp"
	"fullarray.cpp"
	"fullmatrix.cpp"
	"latticemechanisms.cpp"
	"matrix.cpp"
	"matrixmechanisms.cpp"
	"matrixstructure.cpp"
	"numericmatrix.cpp"
	"option.hpp"
	"property.cpp"
	"propertything.cpp"
	"range.cpp"
	"set.cpp"
	"simplepropertyset.cpp"
	"tensor.cpp"
	"vector.cpp"
	"PayoffNamespace.cpp"
)