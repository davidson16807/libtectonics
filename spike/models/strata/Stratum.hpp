#pragma once

// C libraries
#include <cmath>
#include <cstdint>
#include <cstddef>

// std libraries
#include <algorithm>
#include <array>

// in-house libraries
#include "StratumMassPool.hpp"

namespace strata
{
    /*
    "Stratum" describes the composition and texuture of a single rock layer
    */
    template<int M>
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
        std::array<StratumMassPool, M>  mass_pools;
        float max_temperature_received;
        float max_pressure_received;
        float age_of_world_when_deposited;

        Stratum():
            max_temperature_received(0),
            max_pressure_received(0),
            age_of_world_when_deposited(0)
        {
            mass_pools.fill(StratumMassPool());
        }

        Stratum(
            const float max_temperature_received,
            const float max_pressure_received,
            const float age_of_world_when_deposited
        ):
            max_temperature_received(max_temperature_received),
            max_pressure_received(max_pressure_received),
            age_of_world_when_deposited(age_of_world_when_deposited)
        {
            mass_pools.fill(StratumMassPool());
        }

        // DERIVED ATTRIBUTES, regular functions of the form: Stratum -> T
        float mass() const 
        {
            float total_mass(0.0);
            for (std::size_t i=0; i<M; i++)
            {
                total_mass += mass_pools[i].mass;
            }
            return total_mass;
        }
        float age(const float age_of_world) const
        {
            return age_of_world - age_of_world_when_deposited;
        }
        float volume(const float age_of_world, const std::array<float, M>& mass_pool_densities) const 
        {
            float total_volume(0.0);
            for (std::size_t i=0; i<M; i++)
            {
                total_volume += mass_pools[i].mass / mass_pool_densities[i];
            }
            return total_volume;
        }
        float density(const float age_of_world, const std::array<float, M>& mass_pool_densities) const 
        {
            return mass() / volume(mass_pool_densities);
        }
        float thermal_conductivity(
            float age_of_world,
            const std::array<float, M>& mass_pool_densities,
            const std::array<float, M>& mass_pool_thermal_conductivities
        ) const 
        {
            // geometric mean weighted by fractional volume, see work by Fuchs (2013)
            float logK(0.0);
            float total_volume(volume(mass_pool_densities));
            float fractional_volume(0);
            for (std::size_t i=0; i<M; i++)
            {
                fractional_volume = mass_pools[i].mass / (mass_pool_densities[i] * total_volume);
                logK += fractional_volume * mass_pool_thermal_conductivities[i];
            }
            return exp(logK);
        }
    };

}
