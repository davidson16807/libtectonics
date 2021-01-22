
// 3rd party libraries
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch/catch.hpp>

// in house libraries
#include "si_test_utils.hpp"
#include "corresponding_states.hpp"


TEST_CASE( "Klincewicz method purity", "[properties]" ) {
	// properties of acetone
	si::molar_mass M = 58.080*si::gram/si::mole;
	si::temperature Tb = 329.20*si::kelvin;
	int A = 10;
    SECTION("Calling a function twice with the same arguments must produce the same results"){
    	CHECK(si::is_within_fraction( compound::property::estimate_critical_temperature_from_klincewicz(M, Tb), 
    		                      compound::property::estimate_critical_temperature_from_klincewicz(M, Tb), 1e-4));
    	CHECK(si::is_within_fraction( compound::property::estimate_critical_pressure_from_klincewicz(M, A), 
    		                      compound::property::estimate_critical_pressure_from_klincewicz(M, A), 1e-4));
    	CHECK(si::is_within_fraction( compound::property::estimate_critical_molar_volume_from_klincewicz(M, A), 
    		                      compound::property::estimate_critical_molar_volume_from_klincewicz(M, A), 1e-4));
    }
}
TEST_CASE( "Klincewicz method accuracy", "[properties]" ) {
	// properties of acetone
	si::molar_mass M = 58.080*si::gram/si::mole;
	si::temperature Tb = 329.20*si::kelvin;
	int A = 10;
	si::pressure pc = 47.0*si::bar;
	si::temperature Tc = 508.1*si::kelvin;
	si::molar_volume Vc = 209.0 * si::centimeter3/si::mole;

    SECTION("Klincewicz method must predict properties of acetone to within 30%"){
    	CHECK(si::is_within_fraction(compound::property::estimate_critical_temperature_from_klincewicz(M, Tb), Tc, 0.3));
    	CHECK(si::is_within_fraction(compound::property::estimate_critical_pressure_from_klincewicz(M, A), pc, 0.3));
    	CHECK(si::is_within_fraction(compound::property::estimate_critical_molar_volume_from_klincewicz(M, A), Vc, 0.3));
    }
}
TEST_CASE( "Ihmels method purity", "[properties]" ) {
	// properties of acetone
	si::pressure pc = 47.0*si::bar;
	si::temperature Tc = 508.1*si::kelvin;
	si::molar_volume Vc = 209.0 * si::centimeter3/si::mole;

    SECTION("Calling a function twice with the same arguments must produce the same results"){
    	CHECK(si::is_within_fraction(compound::property::estimate_critical_temperature_from_ihmels(pc, Vc), compound::property::estimate_critical_temperature_from_ihmels(pc, Vc), 1e-4));
    	CHECK(si::is_within_fraction(compound::property::estimate_critical_pressure_from_ihmels(Tc, Vc), compound::property::estimate_critical_pressure_from_ihmels(Tc, Vc), 1e-4));
    	CHECK(si::is_within_fraction(compound::property::estimate_critical_molar_volume_from_ihmels(Tc, pc), compound::property::estimate_critical_molar_volume_from_ihmels(Tc, pc), 1e-4));
    }
}
TEST_CASE( "Ihmels method accuracy", "[properties]" ) {
	// properties of acetone
	si::pressure pc = 47.0*si::bar;
	si::temperature Tc = 508.1*si::kelvin;
	si::molar_volume Vc = 209.0 * si::centimeter3/si::mole;

    SECTION("Ihmels method must predict properties of acetone to within 30%"){
    	CHECK(si::is_within_fraction(compound::property::estimate_critical_temperature_from_ihmels(pc, Vc), Tc, 0.3));
    	CHECK(si::is_within_fraction(compound::property::estimate_critical_pressure_from_ihmels(Tc, Vc), pc, 0.3));
    	CHECK(si::is_within_fraction(compound::property::estimate_critical_molar_volume_from_ihmels(Tc, pc), Vc, 0.3));
    }
}

TEST_CASE( "Klincewicz-Ihmels consistency", "[properties]" ) {
	// properties of acetone
	si::molar_mass M = 58.080*si::gram/si::mole;
	si::temperature Tb = 329.20*si::kelvin;
	int A = 10;
	si::pressure pc = 47.0*si::bar;
	si::temperature Tc = 508.1*si::kelvin;
	si::molar_volume Vc = 209.0 * si::centimeter3/si::mole;

    SECTION("Klincewicz method and Ihmels method must agree on predictions to within 30%"){
    	CHECK(si::is_within_fraction(compound::property::estimate_critical_temperature_from_ihmels(pc, Vc), compound::property::estimate_critical_temperature_from_klincewicz(M, Tb), 0.3));
    	CHECK(si::is_within_fraction(compound::property::estimate_critical_pressure_from_ihmels(Tc, Vc), compound::property::estimate_critical_pressure_from_klincewicz(M,A), 0.3));
    	CHECK(si::is_within_fraction(compound::property::estimate_critical_molar_volume_from_ihmels(Tc,pc), compound::property::estimate_critical_molar_volume_from_klincewicz(M,A), 0.3));
    }
}

TEST_CASE( "Klincewicz/Ihmels accuracy", "[properties]" ) {
	// properties of acetone
	si::molar_mass M = 58.080*si::gram/si::mole;
	int A = 10;
	si::temperature Tc = 508.1*si::kelvin;
	double Zc = 0.233f;
    SECTION("Combining Klincewicz and Ihmels must predict properties of acetone to within 30%"){
		si::pressure pc2 = compound::property::estimate_critical_pressure_from_klincewicz(M, A);
		si::molar_volume Vc2 = compound::property::estimate_critical_molar_volume_from_klincewicz(M, A);
		si::temperature Tc2 = compound::property::estimate_critical_temperature_from_ihmels(pc2, Vc2);
		double Zc2 = compound::property::get_critical_compressibility(pc2, Tc2, Vc2);
    	CHECK(si::is_within_fraction(Tc2, Tc, 0.3));
    	CHECK(si::is_within_fraction(Zc2, Zc, 0.3));
    }
}

TEST_CASE( "Sheffy-Johnson method purity", "[properties]" ) {
	// properties of acetone
	si::molar_mass M = 58.080*si::gram/si::mole;
	si::temperature Tm = 178.5 * si::kelvin;
	si::temperature T = si::standard_temperature;

    SECTION("Calling a function twiced with the same arguments must produce the same results"){
    	CHECK(compound::property::estimate_thermal_conductivity_as_liquid_from_sheffy_johnson(M,T,Tm) == compound::property::estimate_thermal_conductivity_as_liquid_from_sheffy_johnson(M,T,Tm));
    }
}

TEST_CASE( "Sheffy-Johnson method accuracy", "[properties]" ) {
	// properties of acetone
	si::molar_mass M = 58.080*si::gram/si::mole;
	si::temperature Tm = 178.5 * si::kelvin;
	si::temperature T = si::standard_temperature;
	si::thermal_conductivity kL = 0.161 * si::watt/(si::meter*si::kelvin);

    SECTION("Sheffy-Johnson method must predict properties of acetone to within 30%"){
    	CHECK(si::is_within_fraction(compound::property::estimate_thermal_conductivity_as_liquid_from_sheffy_johnson(M,T,Tm), kL, 0.3));
    }
}

TEST_CASE( "Sato-Riedel method purity", "[properties]" ) {
	// properties of acetone
	si::molar_mass M = 58.080*si::gram/si::mole;
	si::temperature Tc = 508.1*si::kelvin;
	si::temperature Tb = 329.20*si::kelvin;
	si::temperature T = si::standard_temperature;

	SECTION("Calling a function twiced with the same arguments must produce the same results"){
    	CHECK(compound::property::estimate_thermal_conductivity_as_liquid_from_sato_riedel(M,T,Tb,Tc) == compound::property::estimate_thermal_conductivity_as_liquid_from_sato_riedel(M,T,Tb,Tc));
    }
}

TEST_CASE( "Sato-Riedel method accuracy", "[properties]" ) {
	// properties of acetone
	si::molar_mass M = 58.080*si::gram/si::mole;
	si::temperature Tc = 508.1*si::kelvin;
	si::temperature Tb = 329.20*si::kelvin;
	si::temperature T = si::standard_temperature;
	si::thermal_conductivity kL = 0.161 * si::watt/(si::meter*si::kelvin);

    SECTION("Sato-Riedel method must predict properties of acetone to within 30%"){
    	CHECK(si::is_within_fraction(compound::property::estimate_thermal_conductivity_as_liquid_from_sato_riedel(M,T,Tb,Tc), kL, 0.3));
    }
}

TEST_CASE( "Sheffy-Johnson/Sato-Riedel consistency", "[properties]" ) {
	// properties of acetone
	si::molar_mass M = 58.080*si::gram/si::mole;
	si::temperature Tc = 508.1*si::kelvin;
	si::temperature Tb = 329.20*si::kelvin;
	si::temperature Tm = 178.5* si::kelvin;
	si::temperature T = si::standard_temperature;

    SECTION("Sheffy-Johnson method and Sato-Riedel method must agree on predictions to within 30%"){
    	CHECK(si::is_within_fraction(compound::property::estimate_thermal_conductivity_as_liquid_from_sato_riedel(M,T,Tb,Tc), compound::property::estimate_thermal_conductivity_as_liquid_from_sheffy_johnson(M,T,Tm), 0.3));
    }
}



