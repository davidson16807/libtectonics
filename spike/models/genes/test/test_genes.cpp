
#include <cstddef>

#include <array>

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch/catch.hpp>

#include <models/genes/constituents/Photopigment.hpp>
#include <models/genes/constituents/ClosedFluidSystemConstituent.hpp>

using namespace genes;


TEST_CASE( "fraction encode/decode invertibility", "[many]" ) {
    SECTION("decoding an array then reencoding it must reproduce the original array"){
        CHECK(encode_fraction(decode_fraction(0x0))==0x0);
        CHECK(encode_fraction(decode_fraction(0x1))==0x1);
        CHECK(encode_fraction(decode_fraction(0xD))==0xD);
        CHECK(encode_fraction(decode_fraction(0xF))==0xF);
    }
}

TEST_CASE( "portion encode/decode invertibility", "[many]" ) {
    SECTION("decoding an array then reencoding it must reproduce the original array"){
        CHECK(encode_portion(decode_portion(0x0))==0x0);
        CHECK(encode_portion(decode_portion(0x1))==0x1);
        CHECK(encode_portion(decode_portion(0xD))==0xD);
        CHECK(encode_portion(decode_portion(0xF))==0xF);
    }
}

TEST_CASE( "range encode/decode invertibility", "[many]" ) {
    const float lo = 1.6;
    const float hi = 80.7;
    SECTION("decoding an array then reencoding it must reproduce the original array"){
        CHECK(encode_ranged(decode_ranged(0x0, lo, hi), lo, hi)==0x0);
        CHECK(encode_ranged(decode_ranged(0x1, lo, hi), lo, hi)==0x1);
        CHECK(encode_ranged(decode_ranged(0xD, lo, hi), lo, hi)==0xD);
        CHECK(encode_ranged(decode_ranged(0xF, lo, hi), lo, hi)==0xF);
    }
}

TEST_CASE( "Photopigment encode/decode regularity", "[many]" ) {
    std::array<std::int16_t, Photopigment::bit_count/4> original;
    std::array<std::int16_t, Photopigment::bit_count/4> reconstituted1;
    std::array<std::int16_t, Photopigment::bit_count/4> reconstituted2;
    std::array<std::int16_t, Photopigment::bit_count/4> reconstituted3;
    int count = 0;  
    std::generate(original.begin(), original.end(), [&](){ return count=(count+1)%0xF; });
    Photopigment photopigment1;
    Photopigment photopigment2;

    SECTION("decode and encode must be called repeatedly without changing the value of output references"){
        photopigment1.decode(original.begin());
        photopigment1.encode(reconstituted1.begin());
        photopigment1.encode(reconstituted2.begin());
        CHECK(reconstituted1==reconstituted2);
        photopigment2.decode(original.begin());
        photopigment2.encode(reconstituted3.begin());
        CHECK(reconstituted1==reconstituted3);
    }
}

TEST_CASE( "Photopigment encode/decode invertibility", "[many]" ) {
    std::array<std::int16_t, Photopigment::bit_count/4> original;
    std::array<std::int16_t, Photopigment::bit_count/4> reconstituted;
    int count = 0;  
    std::generate(original.begin(), original.end(), [&](){ return count=(count+1)%0xF; });
    Photopigment photopigment;

    SECTION("decoding an array then reencoding it must reproduce the original array"){
        photopigment.decode(original.begin());
        photopigment.encode(reconstituted.begin());
        CHECK(original==reconstituted);
    }
}

TEST_CASE( "Photopigment static method consistency", "[many]" ) {
    std::array<std::uint8_t, Photopigment::bit_count/4+1> mutation_rates = {};
    std::array<std::uint8_t, Photopigment::bit_count/4+1> attribute_sizes = {};
    Photopigment::getMutationRates(mutation_rates.begin());
    Photopigment::getAttributeSizes(attribute_sizes.begin());
    SECTION("mutation rates and attribute sizes must have the same count"){
        CHECK(mutation_rates.end()[-2] != 0);
        CHECK(mutation_rates.end()[-1] == 0);
        CHECK(attribute_sizes.end()[-2] != 0);
        CHECK(attribute_sizes.end()[-1] == 0);
    }
}







TEST_CASE( "ClosedFluidSystemConstituent encode/decode regularity", "[many]" ) {
    std::array<std::int16_t, ClosedFluidSystemConstituent::bit_count/4> original;
    std::array<std::int16_t, ClosedFluidSystemConstituent::bit_count/4> reconstituted1;
    std::array<std::int16_t, ClosedFluidSystemConstituent::bit_count/4> reconstituted2;
    std::array<std::int16_t, ClosedFluidSystemConstituent::bit_count/4> reconstituted3;
    int count = 0;  
    std::generate(original.begin(), original.end(), [&](){ return count=(count+1)%0xF; });
    ClosedFluidSystemConstituent constituent1;
    ClosedFluidSystemConstituent constituent2;

    SECTION("decode and encode must be called repeatedly without changing the value of output references"){
        constituent1.decode(original.begin());
        constituent1.encode(reconstituted1.begin());
        constituent1.encode(reconstituted2.begin());
        CHECK(reconstituted1==reconstituted2);
        constituent2.decode(original.begin());
        constituent2.encode(reconstituted3.begin());
        CHECK(reconstituted1==reconstituted3);
    }
}

TEST_CASE( "ClosedFluidSystemConstituent encode/decode invertibility", "[many]" ) {
    std::array<std::int16_t, ClosedFluidSystemConstituent::bit_count/4> original;
    std::array<std::int16_t, ClosedFluidSystemConstituent::bit_count/4> reconstituted;
    int count = 0;  
    std::generate(original.begin(), original.end(), [&](){ return count=(count+1)%0xF; });
    ClosedFluidSystemConstituent constituent;
 
    SECTION("decoding an array then reencoding it must reproduce the original array"){
        constituent.decode(original.begin());
        constituent.encode(reconstituted.begin());
        CHECK(original==reconstituted);
    }
}

TEST_CASE( "ClosedFluidSystemConstituent static method consistency", "[many]" ) {
    std::array<std::uint8_t, ClosedFluidSystemConstituent::bit_count/4+1> mutation_rates = {};
    std::array<std::uint8_t, ClosedFluidSystemConstituent::bit_count/4+1> attribute_sizes = {};
    ClosedFluidSystemConstituent::getMutationRates(mutation_rates.begin());
    ClosedFluidSystemConstituent::getAttributeSizes(attribute_sizes.begin());
    SECTION("mutation rates and attribute sizes must have the same count"){
        CHECK(mutation_rates.end()[-2] != 0);
        CHECK(mutation_rates.end()[-1] == 0);
        CHECK(attribute_sizes.end()[-2] != 0);
        CHECK(attribute_sizes.end()[-1] == 0);
    }
}