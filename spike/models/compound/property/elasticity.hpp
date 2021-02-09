#pragma once

namespace compound
{
namespace property
{
/*
NOTE: 
The namespace here serves as a "category of primitives" where objects are variables of primitive types.
We may consider moving to the academic layer if we discover its implementation can be done in a general way.

This namespace maps to and from different elastic moduli.

it namely implements this table: https://en.wikipedia.org/wiki/Elastic_modulus
we may consider coupling it with data from http://dx.doi.org/10.5061/dryad.h505v in the future

The parameters are abbreviated as follows:

bulk     K    bulk modulus
tensile  E    tensile Modulus, Young's modulus, modulus of elasticity
lame     λ    Lamé's first parameter
shear    G,μ  shear modulus, dynamic viscosity, or modulus of rigidity
poisson  ν    Poisson's ratio
pwave    M    P-wave modulus
*/


// (K,E)->* 
constexpr si::pressure get_lame_from_bulk_and_tensile ( const si::pressure bulk, const si::pressure tensile) { return ( 3.0*bulk*(3.0*bulk-tensile) )/( 9.0*bulk-tensile )  ;}
constexpr si::pressure get_shear_from_bulk_and_tensile ( const si::pressure bulk, const si::pressure tensile) { return ( 3.0*bulk*tensile )/( 9.0*bulk-tensile )            ;}
constexpr double       get_poisson_from_bulk_and_tensile ( const si::pressure bulk, const si::pressure tensile) { return si::unitless(( 3.0*bulk-tensile )/( 6.0*bulk ))    ;}
constexpr si::pressure get_pwave_from_bulk_and_tensile ( const si::pressure bulk, const si::pressure tensile) { return ( 3.0*bulk*(3.0*bulk+tensile) )/( 9.0*bulk-tensile ) ;}

// (K,λ)->* 
constexpr si::pressure get_tensile_from_bulk_and_lame ( const si::pressure bulk, const si::pressure lame) { return ( 9.0*bulk*(bulk-lame) )/( 3.0*bulk-lame )               ;}
constexpr si::pressure get_shear_from_bulk_and_lame ( const si::pressure bulk, const si::pressure lame) { return ( 3.0*(bulk-lame) )/( 2.0 )                                ;}
constexpr double       get_poisson_from_bulk_and_lame ( const si::pressure bulk, const si::pressure lame) { return si::unitless(( lame )/( 3.0*bulk-lame ))                 ;}
constexpr si::pressure get_pwave_from_bulk_and_lame ( const si::pressure bulk, const si::pressure lame) { return 3.0*bulk-2.0*lame                                          ;}

// (K,G)->* 
constexpr si::pressure get_tensile_from_bulk_and_shear ( const si::pressure bulk, const si::pressure shear) { return ( 9.0*bulk*shear )/( 3.0*bulk+shear )                  ;}
constexpr si::pressure get_lame_from_bulk_and_shear ( const si::pressure bulk, const si::pressure shear) { return bulk - ( 2.0*shear )/( 3.0 )                              ;}
constexpr double       get_poisson_from_bulk_and_shear ( const si::pressure bulk, const si::pressure shear) { return si::unitless(( 3.0*bulk-2.0*shear )/( 2.0*(3.0*bulk+shear) ));}
constexpr si::pressure get_pwave_from_bulk_and_shear ( const si::pressure bulk, const si::pressure shear) { return bulk + ( 4.0*shear )/( 3.0 )                             ;}

// (K,ν)->* 
constexpr si::pressure get_tensile_from_bulk_and_poisson ( const si::pressure bulk, const double poisson) { return 3.0*bulk*(1.0-2.0*poisson)                               ;}
constexpr si::pressure get_lame_from_bulk_and_poisson ( const si::pressure bulk, const double poisson) { return ( 3.0*bulk*poisson )/( 1.0+poisson )                        ;}
constexpr si::pressure get_shear_from_bulk_and_poisson ( const si::pressure bulk, const double poisson) { return ( 3.0*bulk*(1.0-2.0*poisson) )/( 2.0*(1.0+poisson) )       ;}
constexpr si::pressure get_pwave_from_bulk_and_poisson ( const si::pressure bulk, const double poisson) { return ( 3.0*bulk*(1.0-poisson) )/( 1.0+poisson )                 ;}

// (K,M)->* 
constexpr si::pressure get_tensile_from_bulk_and_pwave ( const si::pressure bulk, const si::pressure pwave) { return ( 9.0*bulk*(pwave-bulk) )/( 3.0*bulk+pwave )           ;}
constexpr si::pressure get_lame_from_bulk_and_pwave ( const si::pressure bulk, const si::pressure pwave) { return ( 3.0*bulk-pwave )/( 2.0 )                                ;}
constexpr si::pressure get_shear_from_bulk_and_pwave ( const si::pressure bulk, const si::pressure pwave) { return ( 3.0*(pwave-bulk) )/( 4.0 )                             ;}
constexpr double       get_poisson_from_bulk_and_pwave ( const si::pressure bulk, const si::pressure pwave) { return si::unitless(( 3.0*bulk-pwave )/( 3.0*bulk+pwave ))    ;}

// (E,λ)->* 
// NOTE: these functions cannot be marked constexpr due to their use of `si::sqrt`, however we still want to convey they should be inlined
inline si::pressure get_bulk_from_tensile_and_lame ( const si::pressure tensile, const si::pressure lame) { si::pressure R = si::sqrt(tensile*tensile + 9.0*lame*lame + 2.0*tensile*lame ); return ( tensile + 3.0*lame + R )/( 6.0 )             ;}
inline si::pressure get_shear_from_tensile_and_lame ( const si::pressure tensile, const si::pressure lame) { si::pressure R = si::sqrt(tensile*tensile + 9.0*lame*lame + 2.0*tensile*lame ); return ( tensile-3.0*lame+R )/( 4.0 )                ;}
inline double       get_poisson_from_tensile_and_lame ( const si::pressure tensile, const si::pressure lame) { si::pressure R = si::sqrt(tensile*tensile + 9.0*lame*lame + 2.0*tensile*lame ); return si::unitless(( 2.0*lame )/( tensile+lame+R ));}
inline si::pressure get_pwave_from_tensile_and_lame ( const si::pressure tensile, const si::pressure lame) { si::pressure R = si::sqrt(tensile*tensile + 9.0*lame*lame + 2.0*tensile*lame ); return ( tensile-lame+R )/( 2.0 )                     ;}

// (E,G)->* 
constexpr si::pressure get_bulk_from_tensile_and_shear ( const si::pressure tensile, const si::pressure shear) { return ( tensile*shear )/( 3.0*(3.0*shear-tensile) )                                                             ;}
constexpr si::pressure get_lame_from_tensile_and_shear ( const si::pressure tensile, const si::pressure shear) { return ( shear*(tensile-2.0*shear) )/( 3.0*shear-tensile )                                                       ;}
constexpr double       get_poisson_from_tensile_and_shear ( const si::pressure tensile, const si::pressure shear) { return si::unitless(( tensile )/( 2.0*shear))-1.0                                                             ;}
constexpr si::pressure get_pwave_from_tensile_and_shear ( const si::pressure tensile, const si::pressure shear) { return ( shear*(4.0*shear-tensile) )/( 3.0*shear-tensile )                                                      ;}

// (E,ν)->* 
constexpr si::pressure get_bulk_from_tensile_and_poisson ( const si::pressure tensile, const double poisson) { return ( tensile )/( 3.0*(1.0-2.0*poisson) )                                                              ;}
constexpr si::pressure get_lame_from_tensile_and_poisson ( const si::pressure tensile, const double poisson) { return ( tensile*poisson )/( (1.0+poisson)*(1.0-2.0*poisson) )                                             ;}
constexpr si::pressure get_shear_from_tensile_and_poisson ( const si::pressure tensile, const double poisson) { return ( tensile )/( 2.0*(1.0+poisson) )                                                                  ;}
constexpr si::pressure get_pwave_from_tensile_and_poisson ( const si::pressure tensile, const double poisson) { return ( tensile*(1.0-poisson) )/( (1.0+poisson)*(1.0-2.0*poisson) )                                     ;}

// (E,M)->* 
// NOTE: There are two valid solutions, such that S can be positive or negative. To prevent introducing dependencies we represent them as separate functions
// NOTE: these functions cannot be marked constexpr due to their use of `si::sqrt`, however we still want to convey they should be inlined
inline si::pressure get_bulk1_from_tensile_and_pwave ( const si::pressure tensile, const si::pressure pwave) { si::pressure S = si::sqrt(tensile*tensile + 9.0*pwave*pwave - 10.0*tensile*pwave); return ( 3.0*pwave-tensile+S )/( 6.0 )        ;}
inline si::pressure get_lame1_from_tensile_and_pwave ( const si::pressure tensile, const si::pressure pwave) { si::pressure S = si::sqrt(tensile*tensile + 9.0*pwave*pwave - 10.0*tensile*pwave); return ( pwave-tensile+S )/( 4.0 )             ;}
inline si::pressure get_shear1_from_tensile_and_pwave ( const si::pressure tensile, const si::pressure pwave) { si::pressure S = si::sqrt(tensile*tensile + 9.0*pwave*pwave - 10.0*tensile*pwave); return ( 3.0*pwave+tensile-S )/( 8.0 )       ;}
inline double       get_poisson1_from_tensile_and_pwave ( const si::pressure tensile, const si::pressure pwave) { si::pressure S = si::sqrt(tensile*tensile + 9.0*pwave*pwave - 10.0*tensile*pwave); return si::unitless(( tensile-pwave+S )/( 4.0*pwave ))                    ;}
inline si::pressure get_bulk2_from_tensile_and_pwave ( const si::pressure tensile, const si::pressure pwave) { si::pressure S = -si::sqrt(tensile*tensile + 9.0*pwave*pwave - 10.0*tensile*pwave); return ( 3.0*pwave-tensile+S )/( 6.0 )        ;}
inline si::pressure get_lame2_from_tensile_and_pwave ( const si::pressure tensile, const si::pressure pwave) { si::pressure S = -si::sqrt(tensile*tensile + 9.0*pwave*pwave - 10.0*tensile*pwave); return ( pwave-tensile+S )/( 4.0 )             ;}
inline si::pressure get_shear2_from_tensile_and_pwave ( const si::pressure tensile, const si::pressure pwave) { si::pressure S = -si::sqrt(tensile*tensile + 9.0*pwave*pwave - 10.0*tensile*pwave); return ( 3.0*pwave+tensile-S )/( 8.0 )       ;}
inline double       get_poisson2_from_tensile_and_pwave ( const si::pressure tensile, const si::pressure pwave) { si::pressure S = -si::sqrt(tensile*tensile + 9.0*pwave*pwave - 10.0*tensile*pwave); return si::unitless(( tensile-pwave+S )/( 4.0*pwave ))                    ;}

// (λ,G)->* 
constexpr si::pressure get_bulk_from_lame_and_shear ( const si::pressure lame, const si::pressure shear) { return lame+ ( 2.0*shear )/( 3.0 )                                 ;}
constexpr si::pressure get_tensile_from_lame_and_shear ( const si::pressure lame, const si::pressure shear) { return ( shear*(3.0*lame + 2.0*shear) )/( lame + shear )        ;}
constexpr double       get_poisson_from_lame_and_shear ( const si::pressure lame, const si::pressure shear) { return si::unitless(( lame )/( 2.0*(lame + shear) ))            ;}
constexpr si::pressure get_pwave_from_lame_and_shear ( const si::pressure lame, const si::pressure shear) { return lame+2.0*shear                                             ;}

// (λ,ν)->* 
constexpr si::pressure get_bulk_from_lame_and_poisson ( const si::pressure lame, const double poisson) { return ( lame*(1.0+poisson) )/( 3.0*poisson )                        ;}
constexpr si::pressure get_tensile_from_lame_and_poisson ( const si::pressure lame, const double poisson) { return ( lame*(1.0+poisson)*(1.0-2.0*poisson) )/( poisson )       ;}
constexpr si::pressure get_shear_from_lame_and_poisson ( const si::pressure lame, const double poisson) { return ( lame*(1.0-2.0*poisson) )/( 2.0*poisson )                   ;}
constexpr si::pressure get_pwave_from_lame_and_poisson ( const si::pressure lame, const double poisson) { return ( lame*(1.0-poisson) )/( poisson )                           ;}

// (λ,M)->* 
constexpr si::pressure get_bulk_from_lame_and_pwave ( const si::pressure lame, const si::pressure pwave) { return ( pwave + 2.0*lame )/( 3.0 )                                ;}
constexpr si::pressure get_tensile_from_lame_and_pwave ( const si::pressure lame, const si::pressure pwave) { return ( (pwave-lame)*(pwave+2.0*lame) )/( pwave+lame )         ;}
constexpr si::pressure get_shear_from_lame_and_pwave ( const si::pressure lame, const si::pressure pwave) { return ( pwave-lame )/( 2.0 )                                     ;}
constexpr double       get_poisson_from_lame_and_pwave ( const si::pressure lame, const si::pressure pwave) { return si::unitless(( lame )/( pwave+lame ))                    ;}

// (G,ν)->* 
constexpr si::pressure get_bulk_from_shear_and_poisson ( const si::pressure shear, const double poisson) { return ( 2.0*shear*(1.0+poisson) )/( 3.0*(1.0-2.0*poisson) )       ;}
constexpr si::pressure get_tensile_from_shear_and_poisson ( const si::pressure shear, const double poisson) { return 2.0*shear*(1.0+poisson)                                  ;}
constexpr si::pressure get_lame_from_shear_and_poisson ( const si::pressure shear, const double poisson) { return ( 2.0* shear*poisson )/( 1.0-2.0*poisson )                  ;}
constexpr si::pressure get_pwave_from_shear_and_poisson ( const si::pressure shear, const double poisson) { return ( 2.0*shear*(1.0-poisson) )/( 1.0-2.0*poisson )            ;}

// (G,M)->* 
constexpr si::pressure get_bulk_from_shear_and_pwave ( const si::pressure shear, const si::pressure pwave) { return pwave - ( 4.0*shear )/( 3.0 )                             ;}
constexpr si::pressure get_tensile_from_shear_and_pwave ( const si::pressure shear, const si::pressure pwave) { return ( shear*(3.0*pwave-4.0*shear) )/( pwave-shear )        ;}
constexpr si::pressure get_lame_from_shear_and_pwave ( const si::pressure shear, const si::pressure pwave) { return pwave - 2.0*shear                                         ;}
constexpr double       get_poisson_from_shear_and_pwave ( const si::pressure shear, const si::pressure pwave) { return si::unitless(( pwave - 2.0*shear )/( 2.0*pwave - 2.0*shear )) ;}

// (ν,M)->* 
constexpr si::pressure get_bulk_from_poisson_and_pwave ( const double poisson, const si::pressure pwave) { return ( pwave*(1.0+poisson) )/( 3.0*(1.0-poisson) )               ;}
constexpr si::pressure get_tensile_from_poisson_and_pwave ( const double poisson, const si::pressure pwave) { return ( pwave*(1.0+poisson)*(1.0-2.0*poisson) )/( 1.0-poisson ) ;}
constexpr si::pressure get_lame_from_poisson_and_pwave ( const double poisson, const si::pressure pwave) { return ( pwave*poisson )/( 1.0-poisson )                           ;}
constexpr si::pressure get_shear_from_poisson_and_pwave ( const double poisson, const si::pressure pwave) { return ( pwave*(1.0-2.0*poisson) )/( 2.0*(1.0-poisson) )          ;}

    }
}