#pragma once

// C libraries
#include <cmath>
#include <cstdint>
#include <cstddef>

// std libraries
#include <algorithm>
#include <array>

// in-house libraries
#include <units/si.hpp>
#include <models/mineral/Mineral.hpp>

namespace stratum
{
    /*
    "Stratum" describes the composition and texture of a single rock layer
    */
    template<std::size_t M>
    struct Stratum
    {
        /*
        "particle_size_bin_relative_volume" describes a set of bins.
        Each bin tracks the relative volume occupied by particles that fall within a certain range of diameters.
        Each bin corresponds to 3 gradations of the the Krumbein phi classification to a good approximation, 
        and describes anything from 1m boulders to colloids.
        Particle size is distinct from a mass pool's grain size.
        Grain size is primarily used to indicate distinctions between extrusive and intrusive rocks, like basalt and gabbro.
        Particle size is primarily used to indicate distinctions between things like boulders vs. pebbles vs sand vs. clay
        */
        std::array<mineral::Mineral, M>  minerals;
        si::temperature max_temperature_received;
        si::pressure max_pressure_received;
        si::time age_of_world_when_deposited;

        Stratum():
            max_temperature_received(0*si::kelvin),
            max_pressure_received(0*si::pascal),
            age_of_world_when_deposited(0*si::megayear)
        {
            minerals.fill(mineral::Mineral());
        }

        Stratum(
            const si::temperature max_temperature_received,
            const si::pressure max_pressure_received,
            const si::time age_of_world_when_deposited
        ):
            max_temperature_received(max_temperature_received),
            max_pressure_received(max_pressure_received),
            age_of_world_when_deposited(age_of_world_when_deposited)
        {
            minerals.fill(mineral::Mineral());
        }

        Stratum(
            const si::temperature max_temperature_received,
            const si::pressure max_pressure_received,
            const si::time age_of_world_when_deposited,
            const std::initializer_list<mineral::Mineral>& vector
        ): 
            max_temperature_received(max_temperature_received),
            max_pressure_received(max_pressure_received),
            age_of_world_when_deposited(age_of_world_when_deposited)
        {
            assert(vector.size() == M);
            int j(0);
            for (auto i = vector.begin(); i != vector.end(); ++i)
            {
                minerals[j] = *i;
                ++j;
            }
        }

        // DERIVED ATTRIBUTES, regular functions of the form: Stratum -> T
        si::mass mass() const 
        {
            si::mass total_mass(0.0);
            for (std::size_t i=0; i<M; i++)
            {
                total_mass += minerals[i].mass;
            }
            return total_mass;
        }
        si::time age(const si::time age_of_world) const
        {
            return age_of_world - age_of_world_when_deposited;
        }
        si::volume volume(const si::time age_of_world, const std::array<si::density, M>& mineral_densities) const 
        {
            si::volume total_volume(0.0);
            for (std::size_t i=0; i<M; i++)
            {
                total_volume += minerals[i].mass / mineral_densities[i];
            }
            return total_volume;
        }
        si::density density(const si::time age_of_world, const std::array<si::density, M>& mineral_densities) const 
        {
            return mass() / volume(age_of_world, mineral_densities);
        }
        // si::thermal_conductivity thermal_conductivity(
        //     si::time age_of_world,
        //     const std::array<si::density, M>& mineral_densities,
        //     const std::array<si::thermal_conductivity, M>& mineral_thermal_conductivities
        // ) const 
        // {
        //     // geometric mean weighted by fractional volume, see work by Fuchs (2013)
        //     float logK(0.0);
        //     si::volume total_volume(volume(mineral_densities));
        //     float fractional_volume(0);
        //     for (std::size_t i=0; i<M; i++)
        //     {
        //         fractional_volume = minerals[i].mass / (mineral_densities[i] * total_volume);
        //         logK += fractional_volume * mineral_thermal_conductivities[i];
        //     }
        //     return exp(logK);
        // }
    };

}
