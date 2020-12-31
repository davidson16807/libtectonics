#pragma once

// C libraries
#include <math.h>       // log10 

// in-house libraries
#include <units.hpp>      // mole
#include <physics/constants.hpp>  // boltzmann_constant
#include "compressibility.hpp"  // fast_approx_compressibility_factor

namespace compound{
    namespace property
    {

        /*
        NOTE: 
        The namespace here each serves as a "category of primitives" where objects are variables of primitive types.
        We may consider moving to the academic layer if we discover its implementation can be done in a general way.

        This namespace maps to and from critical point metrics: pressure, volume, temperature, compressibility, and acentricity



% https://tikzcd.yichuanshen.de/#N4Igdg9gJgpgziAXAbVABwnAlgFyxMJZARgBYAaABgF1yQA3AQwBsBXGJEAHS4CcALCAH0AMiAC+5dJlz5CKYgFYqtBi3aceA4QGUJUkBmx4CRYgHYVdJmw6JufQUIDi+6cblmKxVTY32ANVEAAgBZN0MZE3kSZR9rdTsQIJ0wiKNZUwVLeLVbTiDnNMl3TJilcgAmX0SCoT0SyI8s2PIAZhr8wPrggBUhHHSozwVyUk7-EABrUSHmmLaxiaSeCABbGABzRjmyomVxhK6QAAkhel3oogA2JaPJ-oAjS5HkS0O8yZ5sTbWdxoyVxQAE47p8VlwYDhGLMAcMWgAOMF+CHrLb-AyA17EYjI2r2VYbbYvFrESp444ABSEwHoInEJPKiw+KM0XB+f0ZXgpkyCYjh8zMB2WdREfQGXOyPKShUlJHIihF9n6AGMwn1xc8BXsUItFfckqqNYT0XKKPrwZwjb1gmcLtqgchlBbWcqhGrqWqbXa5bcXfiQEbPRqnnLLP7jkH3cFvlhfhjSo7QRGHtHg6FjZDobDMfCYkiU4a09GMzaTcSHdjcYWrcW1UEvTGuGiK7nBQpyTW3R7ow2NdT7W2dSRzUrA73owAtaO9OUWBVjqNq6eNylz8jXRfu0KhystRabg21lVhjdbnsnvflXGHy3d4LBhtzigI88PifL93Ps9H+99ldzpYt6uuOF7BABV5mOSwEBo+X6QQoepjn2sbxnOB7IfBQ6OriwJjqWQhath2Lknhv4gAAguECHIJQC7kTu-RrHOSK5CBGYAMLnE2UIwq4NHEEiNDkTM-HEaSoJsQGnHcaJc6gsJd4OLxLjoVYSnUrSOgMgJixSccZxwCGAzvoMAnkopIFcQ04nlOS+kPHKnZvjaXH8rZRDkiyAZuRIqgwFAmzwEQoAAGa8OsSB0SAOAQEguJ3mArDMMwdDMIwjwwMwlJ5pwzAwKFZkGOFkWIAlsVRb+SUpWlGVZTl7YgPlhUgHQcD8FgLWIAAtMQjQlcxiCLDFcWINFrrValTV1dluX2M1RVhRFg3DRVZVIolyVTelmWzY1C2tU1WBgEkUAQDgOABREA1IBQI1ILcm01dNu0NTqTUFYMaXHad52XVA13LbddBrQlE1bbVr1zR9LX9UDiDKPdiDkk920zW9QIw4tIA3QjIOjZU434pNkP1dDB3fSdnBnRdV1w6VlhI8QoKo6Te3vQd9ODYza2PeDz07WT+2fYDpUs6Dd382jUPCy1dD8DAjAA-YkBU5Tv2sI8+WHZlYDK20lBc-FKOg4zUtsxjIxY4dCtK5wqscOr1MQJr2t0Lr+uG8V8NkPj8WI+bL1CxzIvy4ryvgAQjtHVT9hna70ce0gBtG2VPOjYJVUQ0H7OYxTIDtZ1gxlanmdM2bAYAEI6CIlSHYLudW7wcb8NjuPM3761ZwL6Pk6HMe-bTAOl+Lo0V8czgQNAfyEBbfdywXHVdb1qeVOVo0bSBOiMLF3UAEowFgsDMPXvey19i9F0gK-e6Va+d20w2Bw3ltZNbTtx39dO34NlQm6NbRJbE2zi-eeF9mA-WdkPUWv9-5IEqE-WCuAABeMBeCnxliHWGP94FwMQCzZ+Z8sHgMgZ-aBq9VoExRoQzBed+6F2Xn1HByNKHJyAV0EmOdX7yHfgPKB-0YHwLumtBB3dpbBzoQvCBscQA0wEavYRACA7AJ7rQq2+dpGD3kcwyoij4pEw4SAohkiSEyLkd-Jad9EYiPYZMDiCtZ5cOhs3TYrdBHI2sUosRc9z711IbIr+w8dGePimDFR4jG5vw0f48xQTLG-0eqDah4SfHEL8WYwJ7jKiJK8azJxviP4BPITo9O8DN4BhEFCOALtuo6DwFlDBEj1H0KXsXG+8T4GlLKogwxqimlRP7po-hFicbw0qF0toyjekRO4XlQZMTMmrw2iI8e-hOGgN8Uszuvs8kbLSYU2JWTlm5Jof0nh0SMnFI6cjUeycDGTEqTAbqABpeAOB8roNSSYw6DC2lMOuZUW5Q0+YpPyfsvhZDtEAqBRUXZxjmlSIWVc0ZpUDYPxBdMr5CLTFaJGbjNFSNAXeLBd81OBLQYYrWUYtRAzEWXKhSila694rlOOHvRgKophQnAfCt+Li3FkuZUNVlVK+mRPOfM+leL4ZtDwYTYlezSXMNlQ-AhoLFXYvSbiuJjLk6sMQKQHpoqZlgK1cMnV+L9WAIVbyiVdLtXuOtUjR+NqaV2ovr86+-zdVDRCUNWxdh1m2rmfa81jq-VtEpUkAAkvwDYzAEBYr5S3NuMq-XZPIr0ZwOhiCNPFSGj1rSvVkpycnVZgbqVnILY60tBr7kVrFbM+akqHUloflM41Sb3VmshVdNqRaS7KomVGpAQa3XVoOZk-tV9B3XLaBMtVmKSWasndA92MA9aVUvowslEyRUNpNQUiFRSGX4uOWW11Vbm0L09T1b1+KgXzsvfm69F8k5jVTqQaKa1I3kVjfGxNy7k2uMLTO+98Mv2d1IGE441cRC5q7dWz937RqkGSUujVtKcVhs-UKyDcLx2vp+QO9pProNQfQ5MODCGgPds-Xg8jBGr28KGb2gG06d3MMNQ-I1SRnnSJVDAAA7lgFUyC81NpAPy0DXVwOlVIHout5F+PHUEyJsTEnnEpvcYx02q7T0+y6Yx29vVyJwbrgozulREa3rkwk7ZAarTZoszo-VxBoqsZPdK+Tfr92cB0ArUKoUACe3UABSEB+BgGqYQT9tbSCM084cz956DUsyS4srjqXSAjvsAAUVYJyjdOn4sbRM3ZpAighWKHrZwDi6U0AwGCxFWLzDFD6sUJRpIlI0G8GC0oXNq88GKEc-YPeEAhPSJi91HK0jNiacatJ9xI3O6KEUKnFbhKUa2fENQcQQA
\begin{tikzcd}
                                   &                                                                    &                                            &                                                                                                     &                                                                       &                                                                                              &                                                                       &                                                                                    &                                                                   &                                                                                                &  &                                                                                               & C_S                                                                            & P_{vS}                                                                & \rho_L \arrow[r]                                                                                        & \rho_S \arrow[l, shift left]                               &  & \rho_G                                      & k_G                                                  & \eta_G                                          \\
                                   &                                                                    &                                            &                                                                                                     &                                                                       &                                                                                              &                                                                       &                                                                                    &                                                                   &                                                                                                &  &                                                                                               & T \arrow[u, "Perry151"]                                                        & H_s T T_t P_t \arrow[u, "Clapeyron"]                                  & V_L M \arrow[u] \arrow[ddd, dotted]                                                                     & V_S M \arrow[d, dotted] \arrow[u]                          &  & V_G M \arrow[u] \arrow[ddd, dotted]         & M C_v \eta_G \arrow[u, dotted] \arrow[r, shift left] & M C_v k_G \arrow[u, dotted] \arrow[l, "Eucken"] \\
                                   &                                                                    &                                            &                                                                                                     &                                                                       &                                                                                              &                                                                       &                                                                                    &                                                                   &                                                                                                &  &                                                                                               &                                                                                &                                                                       &                                                                                                         & V_S                                                        &  &                                             &                                                      &                                                 \\
                                   &                                                                    &                                            &                                                                                                     &                                                                       &                                                                                              &                                                                       &                                                                                    &                                                                   &                                                                                                &  &                                                                                               &                                                                                &                                                                       &                                                                                                         & V_S T_t \arrow[d] \arrow[u]                                &  &                                             &                                                      &                                                 \\
                                   & k_L                                                                & C_L                                        & \omega \arrow[rrrrr, no head, Rightarrow, bend left]                                                &                                                                       & H_v                                                                                          & T_b                                                                   & \sigma \arrow[rrrrrr, no head, Rightarrow, bend left]                              & \omega \arrow[rrr, no head, Rightarrow, bend left]                & \eta_L                                                                                         &  & \omega                                                                                        & P_{vL}                                                                         & \sigma \arrow[r, shift right] \arrow[d, "BSL2", shift left]           & V_L \arrow[l, "BSL2"']                                                                                  & V_L T_t \arrow[l, dotted] \arrow[u, "Goodman", shift left] &  & V_G                                         &                                                      &                                                 \\
MTT_m \arrow[ru, "Sheffy-Johnson"] & T_c M T T_b \arrow[u, "Sato-Reidel", shift left] \arrow[d, dotted] & T_c T C_L \arrow[u] \arrow[r, shift right] & T_c T \omega \arrow[d, dotted] \arrow[r, "Pitzer"] \arrow[u, dotted] \arrow[l, "Rowlinson-Poling"'] & T_c T H_v \arrow[l, shift left] \arrow[ld, dotted] \arrow[ru, dotted] & T_c P_c T H_v \arrow[l, dotted] \arrow[rrd, dotted] \arrow[u, dotted] \arrow[r, shift right] & T_c P_c T T_b \arrow[l, "Chen"'] \arrow[rd, dotted] \arrow[u, dotted] & T_c P_c \sigma \arrow[u, dotted] \arrow[d, dotted] \arrow[ru, "TGS2"]              & T_c P_c M T \omega \arrow[r] \arrow[u, dotted] \arrow[ld, dotted] & T_c P_c M T \eta_L \arrow[l, "Letsou-Stiel", shift left] \arrow[u, dotted] \arrow[lld, dotted] &  & T_c P_c V_c T \omega \arrow[r, "Lee-Kestler", shift left] \arrow[d, dotted] \arrow[u, dotted] & T_c P_c V_c T P_v \arrow[ld, dotted] \arrow[l] \arrow[u, dotted]               & V_c \sigma \arrow[ld, shift left] \arrow[d, "BSL1"] \arrow[u, dotted] & T_c V_c Z_c T \arrow[u, "Rackett"'] \arrow[d, dotted]                                                   &                                                            &  & T_c P_c Z_c T P \arrow[u] \arrow[d, dotted] &                                                      &                                                 \\
                                   & T_cMT_b \arrow[ddd, dotted] \arrow[rr, dotted]                     &                                            & T_c \arrow[ll, shift left]                                                                          &                                                                       &                                                                                              &                                                                       & T_c P_c \arrow[llll, dotted] \arrow[rrrr, "Ihmels"'] \arrow[u, "TGS1", shift left] &                                                                   &                                                                                                &  & T_c P_c V_c \arrow[rrrdd] \arrow[r, dotted] \arrow[llll, dotted, shift right]                 & P_c V_c \arrow[l, "Ihmels"', shift right] \arrow[ru, "BSL1"] \arrow[r, dotted] & V_c \arrow[u, dotted, shift left]                                     & T_c V_c Z_c \arrow[dd, shift left]                                                                      &                                                            &  & T_c P_c Z_c \arrow[llldd]                   &                                                      &                                                 \\
                                   &                                                                    &                                            &                                                                                                     &                                                                       &                                                                                              &                                                                       &                                                                                    &                                                                   &                                                                                                &  &                                                                                               &                                                                                &                                                                       &                                                                                                         &                                                            &  &                                             &                                                      &                                                 \\
                                   &                                                                    &                                            &                                                                                                     &                                                                       &                                                                                              &                                                                       &                                                                                    &                                                                   &                                                                                                &  &                                                                                               &                                                                                &                                                                       & T_c P_c V_c Z_c \arrow[llluu, dotted, shift right] \arrow[rrruu, dotted, shift left] \arrow[uu, dotted] &                                                            &  &                                             &                                                      &                                                 \\
                                   & M T_b \arrow[uuu, "Klincewicz"', shift right]                      &                                            &                                                                                                     &                                                                       &                                                                                              &                                                                       &                                                                                    &                                                                   &                                                                                                &  &                                                                                               & AM \arrow[uuu, "Klincewicz"']                                                  &                                                                       &                                                                                                         &                                                            &  &                                             &                                                      &                                                
\end{tikzcd}



        ROADMAP: 
        Tested  Implemented Correlation                 Property
                X           Klincewicz                  critical properties
                X           Ihmels                      critical properties
                X           Sato Reidel                 liquid thermal conductivity, boiling point
                X           Pitzer                      heat of vaporization, accentric factor
                X           Chen                        heat of vaporization, boiling point
                X           Tee Gotoh Steward 1         molecular diameter, critical properties
                X           Tee Gotoh Steward 2         acentric factor, molecular diameter, critical properties
                X           Letsou-Stiel                liquid viscosity, accentric factor
                X           Lee-Kestler                 vapor pressure, accentric factor
                X           Bird Stewart Lightfoot 1    molecular diameter, critical volume
                X           Bird Stewart Lightfoot 2    molecular diameter, liquid volume
                X           Rackett                     liquid volume, critical properties
                X           Goodman                     liquid volume, solid volume
        */

        // taken from https://eng.libretexts.org/Bookshelves/Chemical_Engineering/Book%3A_Distillation_Science_(Coleman)/03%3A_Critical_Properties_and_Acentric_Factor
        constexpr float get_critical_compressibility(const float critical_pressure, const float critical_temperature, const float critical_molecular_volume)
        {
            return critical_pressure * critical_molecular_volume / (physics::boltzmann_constant * critical_temperature);
        }
        
        // Klincewicz method (1982): https://en.wikipedia.org/wiki/Klincewicz_method
        constexpr float approx_critical_temperature_from_klincewicz(const float molecular_mass, const float standard_boiling_point)
        {
            float molar_mass_in_grams_per_mole = molecular_mass / (units::gram / units::mole);
            float temperature_in_kelvin = 50.2f - 0.16f * molar_mass_in_grams_per_mole + 1.41f * standard_boiling_point;
            return temperature_in_kelvin * units::kelvin; 
        }
        // Klincewicz method (1982): https://en.wikipedia.org/wiki/Klincewicz_method
        constexpr float approx_critical_pressure_from_klincewicz(const float molecular_mass, const int atom_count)
        {
            float molar_mass_in_grams_per_mole = molecular_mass / (units::gram / units::mole);
            float Y = 0.335f + 0.009f * molar_mass_in_grams_per_mole + 0.019f * atom_count;
            float critical_pressure_in_bars = molar_mass_in_grams_per_mole/Y;
            return critical_pressure_in_bars * units::bar;
        }
        // Klincewicz method (1982): https://en.wikipedia.org/wiki/Klincewicz_method
        constexpr float approx_critical_molecular_volume_from_klincewicz(const float molecular_mass, const int atom_count)
        {
            float molar_mass_in_grams_per_mole = molecular_mass / (units::gram / units::mole);
            float critical_molar_volume_in_cm3 = 20.1f + 0.88f * molar_mass_in_grams_per_mole + 13.4f * atom_count;
            return critical_molar_volume_in_cm3 * (units::centimeter3/units::mole);
        }

        // Ihmels (2010)
        constexpr float approx_critical_temperature_from_ihmels(const float critical_pressure, const float critical_molecular_volume)
        {
            float critical_volume_in_m3_per_mole = critical_molecular_volume / (units::meter3/units::mole);
            float critical_pressure_in_pascal = critical_pressure / units::pascal;
            float critical_temperature_in_kelvin = (critical_pressure_in_pascal + 0.025f) * critical_volume_in_m3_per_mole / 2.215f;
            return critical_temperature_in_kelvin * units::kelvin;
        }
        // Ihmels (2010)
        constexpr float approx_critical_molecular_volume_from_ihmels(const float critical_temperature, const float critical_pressure)
        {
            float critical_pressure_in_pascal = critical_pressure / units::pascal;
            float critical_temperature_in_kelvin = critical_temperature / units::kelvin;
            float critical_volume_in_m3_per_mole = critical_temperature_in_kelvin * 2.215f / (critical_pressure_in_pascal + 0.025f);
            return critical_volume_in_m3_per_mole * (units::meter3/units::mole);
        }
        // Ihmels (2010)
        constexpr float approx_critical_pressure_from_ihmels(const float critical_temperature, const float critical_molecular_volume)
        {
            float critical_temperature_in_kelvin = critical_temperature / units::kelvin;
            float critical_volume_in_m3_per_mole = critical_molecular_volume / (units::meter3/units::mole);
            float critical_pressure_in_pascal = 2.215f * critical_temperature_in_kelvin / critical_volume_in_m3_per_mole - 0.025f;
            return critical_pressure_in_pascal * units::pascal;
        }

    }
}