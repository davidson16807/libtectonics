
// 3rd party libraries
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch/catch.hpp>

// in house libraries
#include <si.hpp>
#include <si_test_utils.hpp>

#include "OptionalSpectralField.hpp"

double test_OptionalSpectralField(const si::wavenumber nlo, const si::wavenumber nhi, si::pressure p, const si::temperature T)
{
	return si::unitless(si::mole*si::universal_gas_constant*T/p/si::liter);
}

TEST_CASE( "OptionalSpectralField substitute() purity", "[field]" ) {
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
    	CHECK(unknown.substitute(unknown )(nlo, nhi, p, T) 
    	   == unknown.substitute(unknown )(nlo, nhi, p, T));
    	CHECK(constant.substitute(constant)(nlo, nhi, p, T) 
    	   == constant.substitute(constant)(nlo, nhi, p, T));
    	CHECK(sample.substitute(sample  )(nlo, nhi, p, T) 
    	   == sample.substitute(sample  )(nlo, nhi, p, T));
    	CHECK(relation.substitute(relation)(nlo, nhi, p, T) 
    	   == relation.substitute(relation)(nlo, nhi, p, T));
    }
}

TEST_CASE( "OptionalSpectralField substitute() identity", "[field]" ) {
    si::wavenumber nlo = 14286.0/si::centimeter;
    si::wavenumber nhi = 25000.0/si::centimeter;
    si::pressure p = si::standard_pressure;
    si::temperature T = si::standard_temperature;

	compound::field::OptionalSpectralField<double> unknown  = std::monostate();
	compound::field::OptionalSpectralField<double> constant  = 1.0;
	compound::field::OptionalSpectralField<double> sample  = compound::field::SpectralSample<double>(2.0, nlo, nhi, p, T);
	compound::field::OptionalSpectralField<double> relation  = compound::field::SpectralFunction<double>([](const si::wavenumber nlo, si::wavenumber nhi, const si::pressure p, const si::temperature T){ return test_OptionalSpectralField(nlo,nhi,p,T); });


	SECTION("There exists a value that when applied to a function returns the original value")
	{
    	CHECK(unknown.substitute(unknown)(nlo, nhi, p, T) == unknown(nlo, nhi, p, T));
    	CHECK(constant.substitute(unknown)(nlo, nhi, p, T) == constant(nlo, nhi, p, T));
    	CHECK(sample.substitute(unknown)(nlo, nhi, p, T) == sample(nlo, nhi, p, T));
    	CHECK(relation.substitute(unknown)(nlo, nhi, p, T) == relation(nlo, nhi, p, T));
    }
}

TEST_CASE( "OptionalSpectralField substitute() associativity", "[field]" ) {
    si::wavenumber nlo = 14286.0/si::centimeter;
    si::wavenumber nhi = 25000.0/si::centimeter;
    si::pressure p = si::standard_pressure;
    si::temperature T = si::standard_temperature;

	compound::field::OptionalSpectralField<double> unknown  = std::monostate();
	compound::field::OptionalSpectralField<double> constant  = 1.0;
	compound::field::OptionalSpectralField<double> sample  = compound::field::SpectralSample<double>(2.0, nlo, nhi, p, T);

	SECTION("Functions can be applied in any order and still produce the same results")
	{
    	CHECK(unknown.substitute(constant.substitute(sample))(nlo, nhi, p, T) == 
    		  unknown.substitute(constant).substitute(sample)(nlo, nhi, p, T));

    	CHECK(unknown.substitute(sample.substitute(constant))(nlo, nhi, p, T) == 
    		  unknown.substitute(sample).substitute(constant)(nlo, nhi, p, T));


    	CHECK(unknown.substitute(constant.substitute(sample))(nlo, nhi, p, T) == 
    		  unknown.substitute(constant).substitute(sample)(nlo, nhi, p, T));

    	CHECK(unknown.substitute(sample.substitute(constant))(nlo, nhi, p, T) == 
    		  unknown.substitute(sample).substitute(constant)(nlo, nhi, p, T));





    	CHECK(constant.substitute(sample.substitute(unknown))(nlo, nhi, p, T) == 
    		  constant.substitute(sample).substitute(unknown)(nlo, nhi, p, T));

    	CHECK(constant.substitute(unknown.substitute(sample))(nlo, nhi, p, T) == 
    		  constant.substitute(unknown).substitute(sample)(nlo, nhi, p, T));


    	CHECK(constant.substitute(sample.substitute(unknown))(nlo, nhi, p, T) == 
    		  constant.substitute(sample).substitute(unknown)(nlo, nhi, p, T));

    	CHECK(constant.substitute(unknown.substitute(sample))(nlo, nhi, p, T) == 
    		  constant.substitute(unknown).substitute(sample)(nlo, nhi, p, T));

    }
}


TEST_CASE( "OptionalSpectralField substitute() increasing", "[field]" ) {
    si::wavenumber nlo = 14286.0/si::centimeter;
    si::wavenumber nhi = 25000.0/si::centimeter;
    si::pressure p = si::standard_pressure;
    si::temperature T = si::standard_temperature;

	compound::field::OptionalSpectralField<double> unknown  = std::monostate();
	compound::field::OptionalSpectralField<double> constant  = 1.0;
	compound::field::OptionalSpectralField<double> sample  = compound::field::SpectralSample<double>(2.0, nlo, nhi, p, T);
	compound::field::OptionalSpectralField<double> relation  = compound::field::SpectralFunction<double>([](const si::wavenumber nlo, si::wavenumber nhi, const si::pressure p, const si::temperature T){ return test_OptionalSpectralField(nlo,nhi,p,T); });

	SECTION("An attribute of a function's return value either increases or remains the same when compared to the same attribute of the input value")
	{

    	CHECK(unknown.substitute(unknown).index() >= unknown.index());
    	CHECK(unknown.substitute(constant).index() >= unknown.index());
    	CHECK(unknown.substitute(sample).index() >= unknown.index());
    	CHECK(unknown.substitute(relation).index() >= unknown.index());


    	CHECK(constant.substitute(unknown).index() >= constant.index());
    	CHECK(constant.substitute(constant).index() >= constant.index());
    	CHECK(constant.substitute(sample).index() >= constant.index());
    	CHECK(constant.substitute(relation).index() >= constant.index());


    	CHECK(sample.substitute(unknown).index() >= sample.index());
    	CHECK(sample.substitute(constant).index() >= sample.index());
    	CHECK(sample.substitute(sample).index() >= sample.index());
    	CHECK(sample.substitute(relation).index() >= sample.index());


    	CHECK(relation.substitute(unknown).index() >= relation.index());
    	CHECK(relation.substitute(constant).index() >= relation.index());
    	CHECK(relation.substitute(sample).index() >= relation.index());
    	CHECK(relation.substitute(relation).index() >= relation.index());

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
    	CHECK(unknown.compare(unknown )(nlo, nhi, p, T) 
    	   == unknown.compare(unknown )(nlo, nhi, p, T));
    	CHECK(constant.compare(constant)(nlo, nhi, p, T) 
    	   == constant.compare(constant)(nlo, nhi, p, T));
    	CHECK(sample.compare(sample  )(nlo, nhi, p, T) 
    	   == sample.compare(sample  )(nlo, nhi, p, T));
    	CHECK(relation.compare(relation)(nlo, nhi, p, T) 
    	   == relation.compare(relation)(nlo, nhi, p, T));
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

	SECTION("There exists a value that when applied to a function returns the original value")
	{
    	CHECK(unknown.compare(unknown)(nlo, nhi, p, T) == unknown(nlo, nhi, p, T));
    	CHECK(constant.compare(unknown)(nlo, nhi, p, T) == constant(nlo, nhi, p, T));
    	CHECK(sample.compare(unknown)(nlo, nhi, p, T) == sample(nlo, nhi, p, T));
    	CHECK(relation.compare(unknown)(nlo, nhi, p, T) == relation(nlo, nhi, p, T));
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
    	CHECK(unknown.compare(constant.compare(sample))(nlo, nhi, p, T) == 
    		  unknown.compare(constant).compare(sample)(nlo, nhi, p, T));

    	CHECK(unknown.compare(sample.compare(constant))(nlo, nhi, p, T) == 
    		  unknown.compare(sample).compare(constant)(nlo, nhi, p, T));


    	CHECK(unknown.compare(constant.compare(sample))(nlo, nhi, p, T) == 
    		  unknown.compare(constant).compare(sample)(nlo, nhi, p, T));

    	CHECK(unknown.compare(sample.compare(constant))(nlo, nhi, p, T) == 
    		  unknown.compare(sample).compare(constant)(nlo, nhi, p, T));





    	CHECK(constant.compare(sample.compare(unknown))(nlo, nhi, p, T) == 
    		  constant.compare(sample).compare(unknown)(nlo, nhi, p, T));

    	CHECK(constant.compare(unknown.compare(sample))(nlo, nhi, p, T) == 
    		  constant.compare(unknown).compare(sample)(nlo, nhi, p, T));


    	CHECK(constant.compare(sample.compare(unknown))(nlo, nhi, p, T) == 
    		  constant.compare(sample).compare(unknown)(nlo, nhi, p, T));

    	CHECK(constant.compare(unknown.compare(sample))(nlo, nhi, p, T) == 
    		  constant.compare(unknown).compare(sample)(nlo, nhi, p, T));

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

	SECTION("An attribute of a function's return value either increases or remains the same when compared to the same attribute of the input value")
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

TEST_CASE( "OptionalSpectralField best() commutativity", "[field]" ) {
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

    	CHECK(unknown.compare(unknown)(nlo, nhi, p, T) == unknown.compare(unknown)(nlo, nhi, p, T));
    	CHECK(unknown.compare(constant)(nlo, nhi, p, T) == constant.compare(unknown)(nlo, nhi, p, T));
    	CHECK(unknown.compare(sample)(nlo, nhi, p, T) == sample.compare(unknown)(nlo, nhi, p, T));
    	CHECK(unknown.compare(relation)(nlo, nhi, p, T) == relation.compare(unknown)(nlo, nhi, p, T));


    	CHECK(constant.compare(unknown)(nlo, nhi, p, T) == unknown.compare(constant)(nlo, nhi, p, T));
    	CHECK(constant.compare(constant)(nlo, nhi, p, T) == constant.compare(constant)(nlo, nhi, p, T));
    	CHECK(constant.compare(sample)(nlo, nhi, p, T) == sample.compare(constant)(nlo, nhi, p, T));
    	CHECK(constant.compare(relation)(nlo, nhi, p, T) == relation.compare(constant)(nlo, nhi, p, T));


    	CHECK(sample.compare(unknown)(nlo, nhi, p, T) == unknown.compare(sample)(nlo, nhi, p, T));
    	CHECK(sample.compare(constant)(nlo, nhi, p, T) == constant.compare(sample)(nlo, nhi, p, T));
    	CHECK(sample.compare(sample)(nlo, nhi, p, T) == sample.compare(sample)(nlo, nhi, p, T));
    	CHECK(sample.compare(relation)(nlo, nhi, p, T) == relation.compare(sample)(nlo, nhi, p, T));


    	CHECK(relation.compare(unknown)(nlo, nhi, p, T) == unknown.compare(relation)(nlo, nhi, p, T));
    	CHECK(relation.compare(constant)(nlo, nhi, p, T) == constant.compare(relation)(nlo, nhi, p, T));
    	CHECK(relation.compare(sample)(nlo, nhi, p, T) == sample.compare(relation)(nlo, nhi, p, T));
    	CHECK(relation.compare(relation)(nlo, nhi, p, T) == relation.compare(relation)(nlo, nhi, p, T));

    }
}









TEST_CASE( "OptionalSpectralField map() purity", "[field]" ) {
    si::wavenumber nlo = 14286.0/si::centimeter;
    si::wavenumber nhi = 25000.0/si::centimeter;
    si::pressure p = si::standard_pressure;
    si::temperature T = si::standard_temperature;
    
	compound::field::OptionalSpectralField<double> unknown  = std::monostate();
	compound::field::OptionalSpectralField<double> constant  = 1.0;
	compound::field::OptionalSpectralField<double> sample  = compound::field::SpectralSample<double>(2.0, nlo, nhi, p, T);
	compound::field::OptionalSpectralField<double> relation  = compound::field::SpectralFunction<double>([](const si::wavenumber nlo, si::wavenumber nhi, const si::pressure p, const si::temperature T){ return test_OptionalSpectralField(nlo,nhi,p,T); });
	std::function<double(const double)> f  = [](const double value){ return 1.0 - 2.0*value; };

	SECTION("Calling a function twice with the same arguments must produce the same results")
	{
    	CHECK(unknown.map(f)(nlo, nhi, p, T) == unknown.map(f)(nlo, nhi, p, T));
    	CHECK(constant.map(f)(nlo, nhi, p, T) == constant.map(f)(nlo, nhi, p, T));
    	CHECK(sample.map(f)(nlo, nhi, p, T) == sample.map(f)(nlo, nhi, p, T));
    	CHECK(relation.map(f)(nlo, nhi, p, T) == relation.map(f)(nlo, nhi, p, T));
    }
}

TEST_CASE( "OptionalSpectralField map() identity", "[field]" ) {
    si::wavenumber nlo = 14286.0/si::centimeter;
    si::wavenumber nhi = 25000.0/si::centimeter;
    si::pressure p = si::standard_pressure;
    si::temperature T = si::standard_temperature;
    
	compound::field::OptionalSpectralField<double> unknown  = std::monostate();
	compound::field::OptionalSpectralField<double> constant  = 1.0;
	compound::field::OptionalSpectralField<double> sample  = compound::field::SpectralSample<double>(2.0, nlo, nhi, p, T);
	compound::field::OptionalSpectralField<double> relation  = compound::field::SpectralFunction<double>([](const si::wavenumber nlo, si::wavenumber nhi, const si::pressure p, const si::temperature T){ return test_OptionalSpectralField(nlo,nhi,p,T); });
	std::function<double(const double)> I  = [](const double value){ return value; };

	SECTION("There exists a value that when applied to a function returns the original value")
	{
    	CHECK(unknown.map(I)(nlo, nhi, p, T) == unknown(nlo, nhi, p, T));
    	CHECK(constant.map(I)(nlo, nhi, p, T) == constant(nlo, nhi, p, T));
    	CHECK(sample.map(I)(nlo, nhi, p, T) == sample(nlo, nhi, p, T));
    	CHECK(relation.map(I)(nlo, nhi, p, T) == relation(nlo, nhi, p, T));
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
		[](const double value, const si::wavenumber nlo, const si::wavenumber nhi, const si::pressure p, const si::temperature T){ return 1.0 - 2.0*value; };

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
		[](const double value, const si::wavenumber nlo, const si::wavenumber nhi, const si::pressure p, const si::temperature T){ return value; };

	SECTION("There exists a value that when applied to a function returns the original value")
	{
    	CHECK(unknown.map_to_constant(nlo,nhi,p,T,I)  == unknown(nlo,nhi,p,T) );
    	CHECK(constant.map_to_constant(nlo,nhi,p,T,I)  == constant(nlo,nhi,p,T) );
    	CHECK(sample.map_to_constant(nlo,nhi,p,T,I)  == sample(nlo,nhi,p,T) );
    	CHECK(relation.map_to_constant(nlo,nhi,p,T,I)  == relation(nlo,nhi,p,T) );
    }
}