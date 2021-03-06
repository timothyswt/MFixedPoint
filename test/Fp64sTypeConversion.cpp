//!
//! @file 				Fp64sTypeConversion.cpp
//! @author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @edited 			n/a
//! @created			2013-07-24
//! @last-modified		2017-06-27
//! @brief 				Performs type conversion tests on the slow 64-bit fixed point library.
//! @details
//!		See README.rst in root dir for more info.

// System includes
// none

// 3rd party includes
#include "MUnitTest/MUnitTestApi.hpp"

// User includes
#include "MFixedPoint/Fp64s.hpp"

using namespace mn::MFixedPoint;

MTEST_GROUP(Fp64sTypeConversionTests)
{
	// Check double->fixed conversion first as the
	// rest of the tests depend on it
	MTEST(PositiveDoubleToFixedConversionTest)
	{
		Fp64s fp1 = Fp64s(3.2, 8);

		// The closest fixed point number this can be represented
		// as is Math.Round(3.2*2^8) = 819 = 0b001100110011
		CHECK_EQUAL(fp1.rawVal, (int32_t)0b001100110011);
		CHECK_EQUAL(fp1.q, 8);
	}

	MTEST(NegativeDoubleToFixedConversionTest)
	{
		Fp64s fp1 = Fp64s(-3.2, 8);

		// The closest fixed point number this can be represented
		// as is Math.Round(-3.2*2^8) = -819 = 0b1111111111111111111111111111111111111111111111111111110011001101 (64-bit 2's compliment)
		CHECK_EQUAL(fp1.rawVal, (int64_t)0b1111111111111111111111111111111111111111111111111111110011001101);
		CHECK_EQUAL(fp1.q, 8);
	}

	MTEST(PosInt32CastTest)
	{
		Fp64s fp1 = Fp64s(12.8, 12);
		int32_t myInt32 = (int32_t)fp1;
		
		CHECK_EQUAL(myInt32, 12);
	}

	MTEST(NegInt32CastTest)
	{
		Fp64s fp1 = Fp64s(-22.3, 12);
		int32_t myInt32 = (int32_t)fp1;
		
		// Rounds down to nearest int
		CHECK_EQUAL(myInt32, -23);
	}
	
	MTEST(PosInt64CastTest)
	{
		Fp64s fp1 = Fp64s(5.6, 12);
		int64_t myInt64 = (int64_t)fp1;
		
		CHECK_EQUAL(myInt64, 5);
	}
	
	MTEST(NegInt64CastTest)
	{
		Fp64s fp1 = Fp64s(-43.2, 12);
		int64_t myInt64 = (int64_t)fp1;
		
		// Rounds down to nearest int
		CHECK_EQUAL(myInt64, -44);
	}

	MTEST(PosFloatCastTest)
	{
		Fp64s fp1 = Fp64s(5.6, 12);
		float flo1 = (float)fp1;
		
		CHECK_CLOSE(5.6, flo1, 0.05);
	}
	
	MTEST(NegFloatCastTest)
	{
		Fp64s fp1 = Fp64s(-2.2, 12);
		float flo1 = (float)fp1;
		
		CHECK_CLOSE(-2.2, flo1, 0.05);
	}
	
	MTEST(PosDoubleCastTest)
	{
		Fp64s fp1 = Fp64s(5.6, 12);
		double dbl1 = (double)fp1;
		
		CHECK_CLOSE(5.6, dbl1, 0.05);
	}
	
	MTEST(NegDoubleCastTest)
	{
		Fp64s fp1 = Fp64s(-25.6, 12);
		double dbl1 = (double)fp1;
		
		CHECK_CLOSE(-25.6, dbl1, 0.05);
	}
}
