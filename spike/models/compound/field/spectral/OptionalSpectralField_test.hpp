
// 3rd party libraries
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch/catch.hpp>

// in house libraries
#include <units/si.hpp>
#include "units/si_test_utils.hpp"

#include "OptionalSpectralField.hpp"

#include "OptionalSpectralField_test_utils.hpp"



TEST_CASE( "OptionalSpectralField value_or() purity", "[field]" ) {
    si::wavenumber nlo = 14286.0/si::centimeter;
    si::wavenumber nhi = 25000.0/si::centimeter;
    si::pressure p = si::standard_pressure;
    si::temperature T = si::standard_temperature;

	compound::field::OptionalSpectralField<double> unknown  = std::monostate();
	compound::field::OptionalSpectralField<double> constant  = 1.0;
	compound::field::OptionalSpectralField<double> sample  = compound::field::SpectralSample<double>(2.0, nlo, nhi, p, T);
	compound::field::OptionalSpectralField<double> relation  = compound::field::SpectralFunction<double>([](const si::wavenumber nlo, si::wavenumber nhi, const si::pressure p, const si::temperature T){ return test_OptionalSpectralField(nlo,nhi,p,T); });


	SECTION("Calling a function twice with the same arguments must produce the same results")
	{
    	CHECK(unknown.value_or(unknown ) 
    	   == unknown.value_or(unknown ));
    	CHECK(constant.value_or(constant) 
    	   == constant.value_or(constant));
    	CHECK(sample.value_or(sample  ) 
    	   == sample.value_or(sample  ));
    	CHECK(relation.value_or(relation) 
    	   == relation.value_or(relation));
    }
}

TEST_CASE( "OptionalSpectralField value_or() identity", "[field]" ) {
    si::wavenumber nlo = 14286.0/si::centimeter;
    si::wavenumber nhi = 25000.0/si::centimeter;
    si::pressure p = si::standard_pressure;
    si::temperature T = si::standard_temperature;

	compound::field::OptionalSpectralField<double> unknown  = std::monostate();
	compound::field::OptionalSpectralField<double> constant  = 1.0;
	compound::field::OptionalSpectralField<double> sample  = compound::field::SpectralSample<double>(2.0, nlo, nhi, p, T);
	compound::field::OptionalSpectralField<double> relation  = compound::field::SpectralFunction<double>([](const si::wavenumber nlo, si::wavenumber nhi, const si::pressure p, const si::temperature T){ return test_OptionalSpectralField(nlo,nhi,p,T); });


	SECTION("There exists a entry that when applied to a function returns the original entry")
	{
    	CHECK(unknown.value_or(unknown) == unknown);
    	CHECK(constant.value_or(unknown) == constant);
    	CHECK(sample.value_or(unknown) == sample);
    	CHECK(relation.value_or(unknown) == relation);
    }
}

TEST_CASE( "OptionalSpectralField value_or() associativity", "[field]" ) {
    si::wavenumber nlo = 14286.0/si::centimeter;
    si::wavenumber nhi = 25000.0/si::centimeter;
    si::pressure p = si::standard_pressure;
    si::temperature T = si::standard_temperature;

	compound::field::OptionalSpectralField<double> unknown  = std::monostate();
	compound::field::OptionalSpectralField<double> constant  = 1.0;
	compound::field::OptionalSpectralField<double> sample  = compound::field::SpectralSample<double>(2.0, nlo, nhi, p, T);

	SECTION("Functions can be applied in any order and still produce the same results")
	{
    	CHECK(unknown.value_or(constant.value_or(sample)) == 
    		  unknown.value_or(constant).value_or(sample));

    	CHECK(unknown.value_or(sample.value_or(constant)) == 
    		  unknown.value_or(sample).value_or(constant));


    	CHECK(unknown.value_or(constant.value_or(sample)) == 
    		  unknown.value_or(constant).value_or(sample));

    	CHECK(unknown.value_or(sample.value_or(constant)) == 
    		  unknown.value_or(sample).value_or(constant));





    	CHECK(constant.value_or(sample.value_or(unknown)) == 
    		  constant.value_or(sample).value_or(unknown));

    	CHECK(constant.value_or(unknown.value_or(sample)) == 
    		  constant.value_or(unknown).value_or(sample));


    	CHECK(constant.value_or(sample.value_or(unknown)) == 
    		  constant.value_or(sample).value_or(unknown));

    	CHECK(constant.value_or(unknown.value_or(sample)) == 
    		  constant.value_or(unknown).value_or(sample));

    }
}


TEST_CASE( "OptionalSpectralField value_or() increasing", "[field]" ) {
    si::wavenumber nlo = 14286.0/si::centimeter;
    si::wavenumber nhi = 25000.0/si::centimeter;
    si::pressure p = si::standard_pressure;
    si::temperature T = si::standard_temperature;

	compound::field::OptionalSpectralField<double> unknown  = std::monostate();
	compound::field::OptionalSpectralField<double> constant  = 1.0;
	compound::field::OptionalSpectralField<double> sample  = compound::field::SpectralSample<double>(2.0, nlo, nhi, p, T);
	compound::field::OptionalSpectralField<double> relation  = compound::field::SpectralFunction<double>([](const si::wavenumber nlo, si::wavenumber nhi, const si::pressure p, const si::temperature T){ return test_OptionalSpectralField(nlo,nhi,p,T); });

	SECTION("An attribute of a function's return entry either increases or remains the same when compared to the same attribute of the input entry")
	{

    	CHECK(unknown.value_or(unknown).index() >= unknown.index());
    	CHECK(unknown.value_or(constant).index() >= unknown.index());
    	CHECK(unknown.value_or(sample).index() >= unknown.index());
    	CHECK(unknown.value_or(relation).index() >= unknown.index());


    	CHECK(constant.value_or(unknown).index() >= constant.index());
    	CHECK(constant.value_or(constant).index() >= constant.index());
    	CHECK(constant.value_or(sample).index() >= constant.index());
    	CHECK(constant.value_or(relation).index() >= constant.index());


    	CHECK(sample.value_or(unknown).index() >= sample.index());
    	CHECK(sample.value_or(constant).index() >= sample.index());
    	CHECK(sample.value_or(sample).index() >= sample.index());
    	CHECK(sample.value_or(relation).index() >= sample.index());


    	CHECK(relation.value_or(unknown).index() >= relation.index());
    	CHECK(relation.value_or(constant).index() >= relation.index());
    	CHECK(relation.value_or(sample).index() >= relation.index());
    	CHECK(relation.value_or(relation).index() >= relation.index());

    }
}








TEST_CASE( "OptionalSpectralField compare() purity", "[field]" ) {
    si::wavenumber nlo = 14286.0/si::centimeter;
    si::wavenumber nhi = 25000.0/si::centimeter;
    si::pressure p = si::standard_pressure;
    si::temperature T = si::standard_temperature;

	compound::field::OptionalSpectralField<double> unknown  = std::monostate();
	compound::field::OptionalSpectralField<double> constant  = 1.0;
	compound::field::OptionalSpectralField<double> sample  = compound::field::SpectralSample<double>(2.0, nlo, nhi, p, T);
	compound::field::OptionalSpectralField<double> relation  = compound::field::SpectralFunction<double>([](const si::wavenumber nlo, si::wavenumber nhi, const si::pressure p, const si::temperature T){ return test_OptionalSpectralField(nlo,nhi,p,T); });

	SECTION("Calling a function twice with the same arguments must produce the same results")
	{
    	CHECK(unknown.compare(unknown ) 
    	   == unknown.compare(unknown ));
    	CHECK(constant.compare(constant) 
    	   == constant.compare(constant));
    	CHECK(sample.compare(sample  ) 
    	   == sample.compare(sample  ));
    	CHECK(relation.compare(relation) 
    	   == relation.compare(relation));
    }
}

TEST_CASE( "OptionalSpectralField compare() identity", "[field]" ) {
    si::wavenumber nlo = 14286.0/si::centimeter;
    si::wavenumber nhi = 25000.0/si::centimeter;
    si::pressure p = si::standard_pressure;
    si::temperature T = si::standard_temperature;
    
	compound::field::OptionalSpectralField<double> unknown  = std::monostate();
	compound::field::OptionalSpectralField<double> constant  = 1.0;
	compound::field::OptionalSpectralField<double> sample  = compound::field::SpectralSample<double>(2.0, nlo, nhi, p, T);
	compound::field::OptionalSpectralField<double> relation  = compound::field::SpectralFunction<double>([](const si::wavenumber nlo, si::wavenumber nhi, const si::pressure p, const si::temperature T){ return test_OptionalSpectralField(nlo,nhi,p,T); });

	SECTION("There exists a entry that when applied to a function returns the original entry")
	{
    	CHECK(unknown.compare(unknown) == unknown);
    	CHECK(constant.compare(unknown) == constant);
    	CHECK(sample.compare(unknown) == sample);
    	CHECK(relation.compare(unknown) == relation);
    }
}

TEST_CASE( "OptionalSpectralField compare() associativity", "[field]" ) {
    si::wavenumber nlo = 14286.0/si::centimeter;
    si::wavenumber nhi = 25000.0/si::centimeter;
    si::pressure p = si::standard_pressure;
    si::temperature T = si::standard_temperature;
    
	compound::field::OptionalSpectralField<double> unknown  = std::monostate();
	compound::field::OptionalSpectralField<double> constant  = 1.0;
	compound::field::OptionalSpectralField<double> sample  = compound::field::SpectralSample<double>(2.0, nlo, nhi, p, T);

	SECTION("Functions can be applied in any order and still produce the same results")
	{
    	CHECK(unknown.compare(constant.compare(sample)) == 
    		  unknown.compare(constant).compare(sample));

    	CHECK(unknown.compare(sample.compare(constant)) == 
    		  unknown.compare(sample).compare(constant));


    	CHECK(unknown.compare(constant.compare(sample)) == 
    		  unknown.compare(constant).compare(sample));

    	CHECK(unknown.compare(sample.compare(constant)) == 
    		  unknown.compare(sample).compare(constant));





    	CHECK(constant.compare(sample.compare(unknown)) == 
    		  constant.compare(sample).compare(unknown));

    	CHECK(constant.compare(unknown.compare(sample)) == 
    		  constant.compare(unknown).compare(sample));


    	CHECK(constant.compare(sample.compare(unknown)) == 
    		  constant.compare(sample).compare(unknown));

    	CHECK(constant.compare(unknown.compare(sample)) == 
    		  constant.compare(unknown).compare(sample));

    }
}


TEST_CASE( "OptionalSpectralField compare() increasing", "[field]" ) {
    si::wavenumber nlo = 14286.0/si::centimeter;
    si::wavenumber nhi = 25000.0/si::centimeter;
    si::pressure p = si::standard_pressure;
    si::temperature T = si::standard_temperature;
    
	compound::field::OptionalSpectralField<double> unknown  = std::monostate();
	compound::field::OptionalSpectralField<double> constant  = 1.0;
	compound::field::OptionalSpectralField<double> sample  = compound::field::SpectralSample<double>(2.0, nlo, nhi, p, T);
	compound::field::OptionalSpectralField<double> relation  = compound::field::SpectralFunction<double>([](const si::wavenumber nlo, si::wavenumber nhi, const si::pressure p, const si::temperature T){ return test_OptionalSpectralField(nlo,nhi,p,T); });

	SECTION("An attribute of a function's return entry either increases or remains the same when compared to the same attribute of the input entry")
	{

    	CHECK(unknown.compare(unknown).index() >= unknown.index());
    	CHECK(unknown.compare(constant).index() >= unknown.index());
    	CHECK(unknown.compare(sample).index() >= unknown.index());
    	CHECK(unknown.compare(relation).index() >= unknown.index());


    	CHECK(constant.compare(unknown).index() >= constant.index());
    	CHECK(constant.compare(constant).index() >= constant.index());
    	CHECK(constant.compare(sample).index() >= constant.index());
    	CHECK(constant.compare(relation).index() >= constant.index());


    	CHECK(sample.compare(unknown).index() >= sample.index());
    	CHECK(sample.compare(constant).index() >= sample.index());
    	CHECK(sample.compare(sample).index() >= sample.index());
    	CHECK(sample.compare(relation).index() >= sample.index());


    	CHECK(relation.compare(unknown).index() >= relation.index());
    	CHECK(relation.compare(constant).index() >= relation.index());
    	CHECK(relation.compare(sample).index() >= relation.index());
    	CHECK(relation.compare(relation).index() >= relation.index());

    }
}

TEST_CASE( "OptionalSpectralField compare() commutativity", "[field]" ) {
    si::wavenumber nlo = 14286.0/si::centimeter;
    si::wavenumber nhi = 25000.0/si::centimeter;
    si::pressure p = si::standard_pressure;
    si::temperature T = si::standard_temperature;
    
	compound::field::OptionalSpectralField<double> unknown  = std::monostate();
	compound::field::OptionalSpectralField<double> constant  = 1.0;
	compound::field::OptionalSpectralField<double> sample  = compound::field::SpectralSample<double>(2.0, nlo, nhi, p, T);
	compound::field::OptionalSpectralField<double> relation  = compound::field::SpectralFunction<double>([](const si::wavenumber nlo, si::wavenumber nhi, const si::pressure p, const si::temperature T){ return test_OptionalSpectralField(nlo,nhi,p,T); });

	SECTION("Arguments to a function can be swapped and still produce the same results")
	{

    	CHECK(unknown.compare(unknown) == unknown.compare(unknown));
    	CHECK(unknown.compare(constant) == constant.compare(unknown));
    	CHECK(unknown.compare(sample) == sample.compare(unknown));
    	CHECK(unknown.compare(relation) == relation.compare(unknown));


    	CHECK(constant.compare(unknown) == unknown.compare(constant));
    	CHECK(constant.compare(constant) == constant.compare(constant));
    	CHECK(constant.compare(sample) == sample.compare(constant));
    	CHECK(constant.compare(relation) == relation.compare(constant));


    	CHECK(sample.compare(unknown) == unknown.compare(sample));
    	CHECK(sample.compare(constant) == constant.compare(sample));
    	CHECK(sample.compare(sample) == sample.compare(sample));
    	CHECK(sample.compare(relation) == relation.compare(sample));


    	CHECK(relation.compare(unknown) == unknown.compare(relation));
    	CHECK(relation.compare(constant) == constant.compare(relation));
    	CHECK(relation.compare(sample) == sample.compare(relation));
    	CHECK(relation.compare(relation) == relation.compare(relation));

    }
}









TEST_CASE( "OptionalSpectralField value_or(f,a) purity", "[field]" ) {
    si::wavenumber nlo = 14286.0/si::centimeter;
    si::wavenumber nhi = 25000.0/si::centimeter;
    si::pressure p = si::standard_pressure;
    si::temperature T = si::standard_temperature;

    compound::field::OptionalSpectralField<double> unknown  = std::monostate();
    compound::field::OptionalSpectralField<double> constant  = 1.0;
    compound::field::OptionalSpectralField<double> sample  = compound::field::SpectralSample<double>(2.0, nlo, nhi, p, T);
    compound::field::OptionalSpectralField<double> relation  = compound::field::SpectralFunction<double>([](const si::wavenumber nlo, si::wavenumber nhi, const si::pressure p, const si::temperature T){ return test_OptionalSpectralField(nlo,nhi,p,T); });
    std::function<double(const double)> f  = [](const double entry){ return 1.0 - 2.0*entry; };

    SECTION("Calling a function twice with the same arguments must produce the same results")
    {
        CHECK(unknown.value_or(f,unknown) == unknown.value_or(f,unknown));
        CHECK(unknown.value_or(f,constant) == unknown.value_or(f,constant));
        CHECK(unknown.value_or(f,sample) == unknown.value_or(f,sample));
        CHECK(unknown.value_or(f,relation) == unknown.value_or(f,relation));

        CHECK(constant.value_or(f,unknown) == constant.value_or(f,unknown));
        CHECK(constant.value_or(f,constant) == constant.value_or(f,constant));
        CHECK(constant.value_or(f,sample) == constant.value_or(f,sample));
        CHECK(constant.value_or(f,relation) == constant.value_or(f,relation));

        CHECK(sample.value_or(f,unknown) == sample.value_or(f,unknown));
        CHECK(sample.value_or(f,constant) == sample.value_or(f,constant));
        CHECK(sample.value_or(f,sample) == sample.value_or(f,sample));
        CHECK(sample.value_or(f,relation) == sample.value_or(f,relation));
    }
}

TEST_CASE( "OptionalSpectralField value_or(f,a) identity", "[field]" ) {
    si::wavenumber nlo = 14286.0/si::centimeter;
    si::wavenumber nhi = 25000.0/si::centimeter;
    si::pressure p = si::standard_pressure;
    si::temperature T = si::standard_temperature;

    compound::field::OptionalSpectralField<double> unknown  = std::monostate();
    compound::field::OptionalSpectralField<double> constant  = 1.0;
    compound::field::OptionalSpectralField<double> sample  = compound::field::SpectralSample<double>(2.0, nlo, nhi, p, T);
    compound::field::OptionalSpectralField<double> relation  = compound::field::SpectralFunction<double>([](const si::wavenumber nlo, si::wavenumber nhi, const si::pressure p, const si::temperature T){ return test_OptionalSpectralField(nlo,nhi,p,T); });
    std::function<double(const double)> I  = [](const double entry){ return entry; };

    SECTION("There exists a entry that when applied to a function returns the original entry")
    {
        CHECK(unknown.value_or(I,unknown) == unknown);
        CHECK(unknown.value_or(I,constant) == constant);
        CHECK(unknown.value_or(I,sample) == sample);
        CHECK(unknown.value_or(I,relation) == relation);
    }
}










TEST_CASE( "OptionalSpectralField value_or(f,a,b) purity", "[field]" ) {
    si::wavenumber nlo = 14286.0/si::centimeter;
    si::wavenumber nhi = 25000.0/si::centimeter;
    si::pressure p = si::standard_pressure;
    si::temperature T = si::standard_temperature;

    compound::field::OptionalSpectralField<double> unknown  = std::monostate();
    compound::field::OptionalSpectralField<double> constant  = 1.0;
    compound::field::OptionalSpectralField<double> sample  = compound::field::SpectralSample<double>(2.0, nlo, nhi, p, T);
    compound::field::OptionalSpectralField<double> relation  = compound::field::SpectralFunction<double>([](const si::wavenumber nlo, si::wavenumber nhi, const si::pressure p, const si::temperature T){ return test_OptionalSpectralField(nlo,nhi,p,T); });
    std::function<double(const double, const double)> f  = [](const double first, const double second){ return 1.0 - 2.0*first + 3.0*second; };

    compound::field::OptionalSpectralField<int> unknown_i  = std::monostate();
    compound::field::OptionalSpectralField<int> constant_i  = 1.0;
    compound::field::OptionalSpectralField<int> sample_i  = compound::field::SpectralSample<int>(2.0, nlo, nhi, p, T);
    compound::field::OptionalSpectralField<int> relation_i  = compound::field::SpectralFunction<int>([](const si::wavenumber nlo, si::wavenumber nhi, const si::pressure p, const si::temperature T){ return test_OptionalSpectralField(nlo,nhi,p,T); });
    std::function<double(const int, const double)> f_id  = [](const int first, const double second){ return 1.0 - 2.0*first + 3.0*second; };
    std::function<double(const double, const int)> f_di  = [](const double first, const int second){ return 1.0 - 2.0*first + 3.0*second; };
    std::function<double(const int, const int)> f_ii  = [](const int first, const int second){ return 1.0 - 2.0*first + 3.0*second; };

    SECTION("Calling a function twice with the same arguments must produce the same results")
    {
        CHECK(unknown.value_or(f, unknown,  unknown) == unknown.value_or(f, unknown,  unknown));
        CHECK(unknown.value_or(f, constant, unknown) == unknown.value_or(f, constant, unknown));
        CHECK(unknown.value_or(f, sample,   unknown) == unknown.value_or(f, sample,   unknown));
        CHECK(unknown.value_or(f, relation, unknown) == unknown.value_or(f, relation, unknown));

        CHECK(unknown.value_or(f, unknown,  constant) == unknown.value_or(f, unknown,  constant));
        CHECK(unknown.value_or(f, constant, constant) == unknown.value_or(f, constant, constant));
        CHECK(unknown.value_or(f, sample,   constant) == unknown.value_or(f, sample,   constant));
        CHECK(unknown.value_or(f, relation, constant) == unknown.value_or(f, relation, constant));

        CHECK(unknown.value_or(f, unknown,  sample) == unknown.value_or(f, unknown,  sample));
        CHECK(unknown.value_or(f, constant, sample) == unknown.value_or(f, constant, sample));
        CHECK(unknown.value_or(f, sample,   sample) == unknown.value_or(f, sample,   sample));
        CHECK(unknown.value_or(f, relation, sample) == unknown.value_or(f, relation, sample));

        CHECK(unknown.value_or(f, unknown,  relation) == unknown.value_or(f, unknown,  relation));
        CHECK(unknown.value_or(f, constant, relation) == unknown.value_or(f, constant, relation));
        CHECK(unknown.value_or(f, sample,   relation) == unknown.value_or(f, sample,   relation));
        CHECK(unknown.value_or(f, relation, relation) == unknown.value_or(f, relation, relation));

        CHECK(constant.value_or(f, constant, constant) == constant.value_or(f, constant, constant));
        CHECK(sample  .value_or(f, constant, constant) == sample  .value_or(f, constant, constant));
        CHECK(relation.value_or(f, constant, constant) == relation.value_or(f, constant, constant));

        CHECK(constant.value_or(f, sample, sample) == constant.value_or(f, sample, sample));
        CHECK(sample  .value_or(f, sample, sample) == sample  .value_or(f, sample, sample));
        CHECK(relation.value_or(f, sample, sample) == relation.value_or(f, sample, sample));

        CHECK(constant.value_or(f, relation, relation) == constant.value_or(f, relation, relation));
        CHECK(sample  .value_or(f, relation, relation) == sample  .value_or(f, relation, relation));
        CHECK(relation.value_or(f, relation, relation) == relation.value_or(f, relation, relation));



        CHECK(unknown.value_or(f_ii, unknown_i,  unknown_i) == unknown.value_or(f_ii, unknown_i,  unknown_i));
        CHECK(unknown.value_or(f_ii, constant_i, unknown_i) == unknown.value_or(f_ii, constant_i, unknown_i));
        CHECK(unknown.value_or(f_ii, sample_i,   unknown_i) == unknown.value_or(f_ii, sample_i,   unknown_i));
        CHECK(unknown.value_or(f_ii, relation_i, unknown_i) == unknown.value_or(f_ii, relation_i, unknown_i));

        CHECK(unknown.value_or(f_ii, unknown_i,  constant_i) == unknown.value_or(f_ii, unknown_i,  constant_i));
        CHECK(unknown.value_or(f_ii, constant_i, constant_i) == unknown.value_or(f_ii, constant_i, constant_i));
        CHECK(unknown.value_or(f_ii, sample_i,   constant_i) == unknown.value_or(f_ii, sample_i,   constant_i));
        CHECK(unknown.value_or(f_ii, relation_i, constant_i) == unknown.value_or(f_ii, relation_i, constant_i));

        CHECK(unknown.value_or(f_ii, unknown_i,  sample_i) == unknown.value_or(f_ii, unknown_i,  sample_i));
        CHECK(unknown.value_or(f_ii, constant_i, sample_i) == unknown.value_or(f_ii, constant_i, sample_i));
        CHECK(unknown.value_or(f_ii, sample_i,   sample_i) == unknown.value_or(f_ii, sample_i,   sample_i));
        CHECK(unknown.value_or(f_ii, relation_i, sample_i) == unknown.value_or(f_ii, relation_i, sample_i));

        CHECK(unknown.value_or(f_ii, unknown_i,  relation_i) == unknown.value_or(f_ii, unknown_i,  relation_i));
        CHECK(unknown.value_or(f_ii, constant_i, relation_i) == unknown.value_or(f_ii, constant_i, relation_i));
        CHECK(unknown.value_or(f_ii, sample_i,   relation_i) == unknown.value_or(f_ii, sample_i,   relation_i));
        CHECK(unknown.value_or(f_ii, relation_i, relation_i) == unknown.value_or(f_ii, relation_i, relation_i));

        CHECK(constant.value_or(f_ii, constant_i, constant_i) == constant.value_or(f_ii, constant_i, constant_i));
        CHECK(sample  .value_or(f_ii, constant_i, constant_i) == sample  .value_or(f_ii, constant_i, constant_i));
        CHECK(relation.value_or(f_ii, constant_i, constant_i) == relation.value_or(f_ii, constant_i, constant_i));

        CHECK(constant.value_or(f_ii, sample_i, sample_i) == constant.value_or(f_ii, sample_i, sample_i));
        CHECK(sample  .value_or(f_ii, sample_i, sample_i) == sample  .value_or(f_ii, sample_i, sample_i));
        CHECK(relation.value_or(f_ii, sample_i, sample_i) == relation.value_or(f_ii, sample_i, sample_i));

        CHECK(constant.value_or(f_ii, relation_i, relation_i) == constant.value_or(f_ii, relation_i, relation_i));
        CHECK(sample  .value_or(f_ii, relation_i, relation_i) == sample  .value_or(f_ii, relation_i, relation_i));
        CHECK(relation.value_or(f_ii, relation_i, relation_i) == relation.value_or(f_ii, relation_i, relation_i));



        CHECK(unknown.value_or(f_id, unknown_i,  unknown) == unknown.value_or(f_id, unknown_i,  unknown));
        CHECK(unknown.value_or(f_id, constant_i, unknown) == unknown.value_or(f_id, constant_i, unknown));
        CHECK(unknown.value_or(f_id, sample_i,   unknown) == unknown.value_or(f_id, sample_i,   unknown));
        // CHECK(unknown.value_or(f_id, relation_i, unknown) == unknown.value_or(f_id, relation_i, unknown));

        CHECK(unknown.value_or(f_id, unknown_i,  constant) == unknown.value_or(f_id, unknown_i,  constant));
        CHECK(unknown.value_or(f_id, constant_i, constant) == unknown.value_or(f_id, constant_i, constant));
        CHECK(unknown.value_or(f_id, sample_i,   constant) == unknown.value_or(f_id, sample_i,   constant));
        // CHECK(unknown.value_or(f_id, relation_i, constant) == unknown.value_or(f_id, relation_i, constant));

        CHECK(unknown.value_or(f_id, unknown_i,  sample) == unknown.value_or(f_id, unknown_i,  sample));
        CHECK(unknown.value_or(f_id, constant_i, sample) == unknown.value_or(f_id, constant_i, sample));
        CHECK(unknown.value_or(f_id, sample_i,   sample) == unknown.value_or(f_id, sample_i,   sample));
        // CHECK(unknown.value_or(f_id, relation_i, sample) == unknown.value_or(f_id, relation_i, sample));

        // CHECK(unknown.value_or(f_id, unknown_i,  relation) == unknown.value_or(f_id, unknown_i,  relation));
        // CHECK(unknown.value_or(f_id, constant_i, relation) == unknown.value_or(f_id, constant_i, relation));
        // CHECK(unknown.value_or(f_id, sample_i,   relation) == unknown.value_or(f_id, sample_i,   relation));
        // CHECK(unknown.value_or(f_id, relation_i, relation) == unknown.value_or(f_id, relation_i, relation));

        CHECK(constant.value_or(f_id, constant_i, constant) == constant.value_or(f_id, constant_i, constant));
        CHECK(sample  .value_or(f_id, constant_i, constant) == sample  .value_or(f_id, constant_i, constant));
        // CHECK(relation.value_or(f_id, constant_i, constant) == relation.value_or(f_id, constant_i, constant));

        CHECK(constant.value_or(f_id, sample_i, sample) == constant.value_or(f_id, sample_i, sample));
        CHECK(sample  .value_or(f_id, sample_i, sample) == sample  .value_or(f_id, sample_i, sample));
        // CHECK(relation.value_or(f_id, sample_i, sample) == relation.value_or(f_id, sample_i, sample));

        // CHECK(constant.value_or(f_id, relation_i, relation) == constant.value_or(f_id, relation_i, relation));
        // CHECK(sample  .value_or(f_id, relation_i, relation) == sample  .value_or(f_id, relation_i, relation));
        // CHECK(relation.value_or(f_id, relation_i, relation) == relation.value_or(f_id, relation_i, relation));



        CHECK(unknown.value_or(f_di, unknown,  unknown_i) == unknown.value_or(f_di, unknown,  unknown_i));
        CHECK(unknown.value_or(f_di, constant, unknown_i) == unknown.value_or(f_di, constant, unknown_i));
        CHECK(unknown.value_or(f_di, sample,   unknown_i) == unknown.value_or(f_di, sample,   unknown_i));
        // CHECK(unknown.value_or(f_di, relation, unknown_i) == unknown.value_or(f_di, relation, unknown_i));

        CHECK(unknown.value_or(f_di, unknown,  constant_i) == unknown.value_or(f_di, unknown,  constant_i));
        CHECK(unknown.value_or(f_di, constant, constant_i) == unknown.value_or(f_di, constant, constant_i));
        CHECK(unknown.value_or(f_di, sample,   constant_i) == unknown.value_or(f_di, sample,   constant_i));
        // CHECK(unknown.value_or(f_di, relation, constant_i) == unknown.value_or(f_di, relation, constant_i));

        CHECK(unknown.value_or(f_di, unknown,  sample_i) == unknown.value_or(f_di, unknown,  sample_i));
        CHECK(unknown.value_or(f_di, constant, sample_i) == unknown.value_or(f_di, constant, sample_i));
        CHECK(unknown.value_or(f_di, sample,   sample_i) == unknown.value_or(f_di, sample,   sample_i));
        // CHECK(unknown.value_or(f_di, relation, sample_i) == unknown.value_or(f_di, relation, sample_i));

        // CHECK(unknown.value_or(f_di, unknown,  relation_i) == unknown.value_or(f_di, unknown,  relation_i));
        // CHECK(unknown.value_or(f_di, constant, relation_i) == unknown.value_or(f_di, constant, relation_i));
        // CHECK(unknown.value_or(f_di, sample,   relation_i) == unknown.value_or(f_di, sample,   relation_i));
        // CHECK(unknown.value_or(f_di, relation, relation_i) == unknown.value_or(f_di, relation, relation_i));

        CHECK(constant.value_or(f_di, constant, constant_i) == constant.value_or(f_di, constant, constant_i));
        CHECK(sample  .value_or(f_di, constant, constant_i) == sample  .value_or(f_di, constant, constant_i));
        // CHECK(relation.value_or(f_di, constant, constant_i) == relation.value_or(f_di, constant, constant_i));

        CHECK(constant.value_or(f_di, sample, sample_i) == constant.value_or(f_di, sample, sample_i));
        CHECK(sample  .value_or(f_di, sample, sample_i) == sample  .value_or(f_di, sample, sample_i));
        // CHECK(relation.value_or(f_di, sample, sample_i) == relation.value_or(f_di, sample, sample_i));

        // CHECK(constant.value_or(f_di, relation, relation_i) == constant.value_or(f_di, relation, relation_i));
        // CHECK(sample  .value_or(f_di, relation, relation_i) == sample  .value_or(f_di, relation, relation_i));
        // CHECK(relation.value_or(f_di, relation, relation_i) == relation.value_or(f_di, relation, relation_i));
    }
}

TEST_CASE( "OptionalSpectralField value_or(f,a,b) free theorem identity", "[field]" ) {
    si::wavenumber nlo = 14286.0/si::centimeter;
    si::wavenumber nhi = 25000.0/si::centimeter;
    si::pressure p = si::standard_pressure;
    si::temperature T = si::standard_temperature;

    compound::field::OptionalSpectralField<double> unknown  = std::monostate();
    compound::field::OptionalSpectralField<double> constant  = 1.0;
    compound::field::OptionalSpectralField<double> sample  = compound::field::SpectralSample<double>(2.0, nlo, nhi, p, T);
    compound::field::OptionalSpectralField<double> relation  = compound::field::SpectralFunction<double>([](const si::wavenumber nlo, si::wavenumber nhi, const si::pressure p, const si::temperature T){ return test_OptionalSpectralField(nlo,nhi,p,T); });
    std::function<double(const double, const double)> f  = [](const double first, const double second){ return first + second; };
    compound::field::OptionalSpectralField<double> I  = 0.0;

    SECTION("A function will have the identity property if it is passed a function that itself has the identity property (this presumes for our case that the function is invoked)")
    {
        CHECK(unknown.value_or(f, unknown,  I) == unknown );
        CHECK(unknown.value_or(f, constant, I) == constant);
        CHECK(unknown.value_or(f, sample,   I) == sample  );
        CHECK(unknown.value_or(f, relation, I) == relation);
    }
}

TEST_CASE( "OptionalSpectralField value_or(f,a,b) free theorem commutativity", "[field]" ) {
    si::wavenumber nlo = 14286.0/si::centimeter;
    si::wavenumber nhi = 25000.0/si::centimeter;
    si::pressure p = si::standard_pressure;
    si::temperature T = si::standard_temperature;

    compound::field::OptionalSpectralField<double> unknown  = std::monostate();
    compound::field::OptionalSpectralField<double> constant  = 1.0;
    compound::field::OptionalSpectralField<double> sample  = compound::field::SpectralSample<double>(2.0, nlo, nhi, p, T);
    compound::field::OptionalSpectralField<double> relation  = compound::field::SpectralFunction<double>([](const si::wavenumber nlo, si::wavenumber nhi, const si::pressure p, const si::temperature T){ return test_OptionalSpectralField(nlo,nhi,p,T); });
    std::function<double(const double, const double)> f  = [](const double first, const double second){ return first + second; };

    SECTION("A function will have the commutativity property if it is passed a function that itself has the commutativity property (this presumes for our case that the function is invoked)")
    {
        CHECK(unknown.value_or(f, unknown,  unknown) == unknown.value_or(f, unknown, unknown  ));
        CHECK(unknown.value_or(f, constant, unknown) == unknown.value_or(f, unknown, constant ));
        CHECK(unknown.value_or(f, sample,   unknown) == unknown.value_or(f, unknown, sample   ));
        CHECK(unknown.value_or(f, relation, unknown) == unknown.value_or(f, unknown, relation ));

        CHECK(unknown.value_or(f, unknown,  constant) == unknown.value_or(f, constant, unknown  ));
        CHECK(unknown.value_or(f, constant, constant) == unknown.value_or(f, constant, constant ));
        CHECK(unknown.value_or(f, sample,   constant) == unknown.value_or(f, constant, sample   ));
        CHECK(unknown.value_or(f, relation, constant) == unknown.value_or(f, constant, relation ));

        CHECK(unknown.value_or(f, unknown,  sample) == unknown.value_or(f, sample, unknown  ));
        CHECK(unknown.value_or(f, constant, sample) == unknown.value_or(f, sample, constant ));
        CHECK(unknown.value_or(f, sample,   sample) == unknown.value_or(f, sample, sample   ));
        CHECK(unknown.value_or(f, relation, sample) == unknown.value_or(f, sample, relation ));

        CHECK(unknown.value_or(f, unknown,  relation) == unknown.value_or(f, relation, unknown  ));
        CHECK(unknown.value_or(f, constant, relation) == unknown.value_or(f, relation, constant ));
        CHECK(unknown.value_or(f, sample,   relation) == unknown.value_or(f, relation, sample   ));
        CHECK(unknown.value_or(f, relation, relation) == unknown.value_or(f, relation, relation ));
    }
}











TEST_CASE( "OptionalSpectralField map_to_constant() purity", "[field]" ) {
    si::wavenumber nlo = 14286.0/si::centimeter;
    si::wavenumber nhi = 25000.0/si::centimeter;
    si::pressure p = si::standard_pressure;
    si::temperature T = si::standard_temperature;
    
	compound::field::OptionalSpectralField<double> unknown  = std::monostate();
	compound::field::OptionalSpectralField<double> constant  = 1.0;
	compound::field::OptionalSpectralField<double> sample  = compound::field::SpectralSample<double>(2.0, nlo, nhi, p, T);
	compound::field::OptionalSpectralField<double> relation  = compound::field::SpectralFunction<double>([](const si::wavenumber nlo, si::wavenumber nhi, const si::pressure p, const si::temperature T){ return test_OptionalSpectralField(nlo,nhi,p,T); });
	std::function<double(const double, const si::wavenumber nlo, const si::wavenumber nhi, const si::pressure, const si::temperature)> f  = 
		[](const double entry, const si::wavenumber nlo, const si::wavenumber nhi, const si::pressure p, const si::temperature T){ return 1.0 - 2.0*entry; };

	SECTION("Calling a function twice with the same arguments must produce the same results")
	{
    	CHECK(unknown.map_to_constant(nlo,nhi,p,T,f) == unknown.map_to_constant(nlo,nhi,p,T,f));
    	CHECK(constant.map_to_constant(nlo,nhi,p,T,f) == constant.map_to_constant(nlo,nhi,p,T,f));
    	CHECK(sample.map_to_constant(nlo,nhi,p,T,f) == sample.map_to_constant(nlo,nhi,p,T,f));
    	CHECK(relation.map_to_constant(nlo,nhi,p,T,f) == relation.map_to_constant(nlo,nhi,p,T,f));
    }
}

TEST_CASE( "OptionalSpectralField map_to_constant() identity", "[field]" ) {
    si::wavenumber nlo = 14286.0/si::centimeter;
    si::wavenumber nhi = 25000.0/si::centimeter;
    si::pressure p = si::standard_pressure;
    si::temperature T = si::standard_temperature;
    
	compound::field::OptionalSpectralField<double> unknown  = std::monostate();
	compound::field::OptionalSpectralField<double> constant  = 1.0;
	compound::field::OptionalSpectralField<double> sample  = compound::field::SpectralSample<double>(2.0, nlo, nhi, p, T);
	compound::field::OptionalSpectralField<double> relation  = compound::field::SpectralFunction<double>([](const si::wavenumber nlo, si::wavenumber nhi, const si::pressure p, const si::temperature T){ return test_OptionalSpectralField(nlo,nhi,p,T); });
	std::function<double(const double, const si::wavenumber nlo, const si::wavenumber nhi, const si::pressure, const si::temperature)> I  = 
		[](const double entry, const si::wavenumber nlo, const si::wavenumber nhi, const si::pressure p, const si::temperature T){ return entry; };

	SECTION("There exists a entry that when applied to a function returns the original entry")
	{
    	CHECK(unknown.map_to_constant(nlo,nhi,p,T,I)  == unknown(nlo,nhi,p,T) );
    	CHECK(constant.map_to_constant(nlo,nhi,p,T,I)  == constant(nlo,nhi,p,T) );
    	CHECK(sample.map_to_constant(nlo,nhi,p,T,I)  == sample(nlo,nhi,p,T) );
    	CHECK(relation.map_to_constant(nlo,nhi,p,T,I)  == relation(nlo,nhi,p,T) );
    }
}