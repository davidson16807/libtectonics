#pragma once

#include <initializer_list> // initializer_list
#include <memory>           // std::shared_ptr

#include <many/types.hpp> // floats, etc.

#include <rasters/Grid.hpp>    // Grid

#include <models/Crust.hpp>    // Crust

namespace crust
{
    using namespace rasters;

    class CrustProfile
    {
    public:
        CrustProfile();
        ~CrustProfile();
        
        float sediment;
        float sedimentary;
        float metamorphic;
        float felsic_plutonic;
        float felsic_volcanic;
        float mafic_volcanic;
        float mafic_plutonic;
        float age;
    };

    // A "Crust" is defined as a tuple of rasters that represent the solid chemical constituents of a planet
    // The Crust namespace provides functions that allow crust objects to be manipulated in the same way as rasters.
    // It also provides functions for modeling properties of Crust.
    //
    // Q: Why is Crust a structure of arrays? Why not make it an array of structures?
    // A: In keeping with data oriented design, we store data in whichever way is most performant. 
    //      This isn't to say data oriented design will always prefer a structure of arrays (SoA). 
    //      We ought to prefer an array of structures (AoS) if the members of a structure are always used together.
    //      For instance, a vector raster should definitely be an array of structures if
    //        we use dot products more than swizzles, because a dot product uses all the members of a vector, 
    //        whereas swizzles only use a single member.
    //      For Crust objects, the most common operations are:
    //        1.) adding up deltas
    //        2.) multiplying filters
    //        3.) summing up conserved mass to ensure conservation
    //        4.) calculating deltas such as erosion and lithification
    //        5.) calculating thickness and overburden pressure
    //      Of these operations, 1.) and 2.) will run well under both SoA and AoS.
    //      All other operations except for 5.) are more performant using SoA, so that's what we use. 
    //
    // TODO: implement stratigraphic model a la Rich's "Planet" project
    class Crust
    {
    public:
        std::shared_ptr<Grid> grid;

        // The following are the most fundamental fields to the tectonics model:
        //
        // "felsic" is the mass of the buoyant, unsubductable igneous component of the crust
        // AKA "sial", or "continental" crust
        // 
        // "sediment", "sedimentary", and "metamorphic" are forms of felsic rock 
        //    that have been converted by weathering, lithification, or metamorphosis.
        //   Together with felsic, they form a conserved quantity 
        //    - felsic type rock is never created or destroyed without our explicit say-so
        //   This is done to provide our model with a way to check for errors.
        //
        // "mafic" is the mass of the denser, subductable igneous component of the crust
        //    AKA "sima", or "oceanic" crust.
        //   Mafic never undergoes conversion to the other rock types, this is due to a few reasons:
        //    1.) it's not performant
        //    2.) mafic is not conserved, so it's not as important to get right
        //    3.) mafic remains underocean most of the time so it isn't very noticeable
        //
        // "volcanic" rock is rock that was created by volcanic resurfacing
        // "plutonic" rock is rock that was created by magma seeping into the cracks of existing rock
        // by tracking plutonic/volcanic rock, we can identify the specific kind of rock that's in a region:
        // 
        //             volcanic     plutonic
        //     felsic   rhyolite     granite
        //     mafic    basalt       gabbro
        //
        // "age" is the age of the subductable, mafic component of the crust
        // we don't track the age of unsubductable crust because it doesn't affect model behavior

        raster sediment;
        raster sedimentary;
        raster metamorphic;
        raster felsic_plutonic;
        raster felsic_volcanic;
        raster mafic_volcanic;
        raster mafic_plutonic;
        raster age;

        // destructor: delete pointer 
        ~Crust()
        {
        };

        // copy constructor
        Crust(const Crust& a)
            : grid            (a.grid            ),
              sediment        (a.sediment        ),
              sedimentary     (a.sedimentary     ),
              metamorphic     (a.metamorphic     ),
              felsic_plutonic (a.felsic_plutonic ),
              felsic_volcanic (a.felsic_volcanic ),
              mafic_volcanic  (a.mafic_volcanic  ),
              mafic_plutonic  (a.mafic_plutonic  ),
              age             (a.age             )
        {

        }

        explicit Crust(const std::shared_ptr<Grid>& grid)
            : grid            (grid),
              sediment        (grid),
              sedimentary     (grid),
              metamorphic     (grid),
              felsic_plutonic (grid),
              felsic_volcanic (grid),
              mafic_volcanic  (grid),
              mafic_plutonic  (grid),
              age             (grid)
        {
        }

        inline unsigned int size() const
        {
            return grid->vertex_positions.size();
        }
    };

    //all_pools:
    //    sediment
    //    sedimentary
    //    metamorphic
    //    felsic_plutonic
    //    felsic_volcanic
    //    mafic_volcanic
    //    mafic_plutonic
    //    age
    //
    //mass_pools:
    //    sediment
    //    sedimentary
    //    metamorphic
    //    felsic_plutonic
    //    felsic_volcanic
    //    mafic_volcanic
    //    mafic_plutonic
    //
    //conserved_pools:
    //    sediment
    //    sedimentary
    //    metamorphic
    //    felsic_plutonic
    //    felsic_volcanic
    //
    //nonconserved_pools:
    //    mafic_volcanic
    //    mafic_plutonic
    //    age
    //

    template<typename F>
    inline void transform_all(const Crust& in, F f, Crust& out) {
        f(in.sediment,        out.sediment        );
        f(in.sedimentary,     out.sedimentary     );
        f(in.metamorphic,     out.metamorphic     );
        f(in.felsic_plutonic, out.felsic_plutonic );
        f(in.felsic_volcanic, out.felsic_volcanic );
        f(in.mafic_volcanic,  out.mafic_volcanic  );
        f(in.mafic_plutonic,  out.mafic_plutonic  );
        f(in.age,             out.age             );
    }
    template<typename F>
    inline void transform_all(const Crust& a, const Crust& b, F f, Crust& out) {
        f(a.sediment,        b.sediment,        out.sediment        );
        f(a.sedimentary,     b.sedimentary,     out.sedimentary     );
        f(a.metamorphic,     b.metamorphic,     out.metamorphic     );
        f(a.felsic_plutonic, b.felsic_plutonic, out.felsic_plutonic );
        f(a.felsic_volcanic, b.felsic_volcanic, out.felsic_volcanic );
        f(a.mafic_volcanic,  b.mafic_volcanic,  out.mafic_volcanic  );
        f(a.mafic_plutonic,  b.mafic_plutonic,  out.mafic_plutonic  );
        f(a.age,             b.age,             out.age             );
    }
    template<typename F, typename T>
    inline void transform_all(const Crust& a, const T b, F f, Crust& out) {
        f(a.sediment,        b, out.sediment        );
        f(a.sedimentary,     b, out.sedimentary     );
        f(a.metamorphic,     b, out.metamorphic     );
        f(a.felsic_plutonic, b, out.felsic_plutonic );
        f(a.felsic_volcanic, b, out.felsic_volcanic );
        f(a.mafic_volcanic,  b, out.mafic_volcanic  );
        f(a.mafic_plutonic,  b, out.mafic_plutonic  );
        f(a.age,             b, out.age             );
    }



    template<typename F>
    inline void transform_mass(const Crust& in, F f, Crust& out) {
        f(in.sediment,        out.sediment        );
        f(in.sedimentary,     out.sedimentary     );
        f(in.metamorphic,     out.metamorphic     );
        f(in.felsic_plutonic, out.felsic_plutonic );
        f(in.felsic_volcanic, out.felsic_volcanic );
        f(in.mafic_volcanic,  out.mafic_volcanic  );
        f(in.mafic_plutonic,  out.mafic_plutonic  );
        // f(in.age,             out.age             );
    }
    template<typename F>
    inline void transform_mass(const Crust& a, const Crust& b, F f, Crust& out) {
        f(a.sediment,        b.sediment,        out.sediment        );
        f(a.sedimentary,     b.sedimentary,     out.sedimentary     );
        f(a.metamorphic,     b.metamorphic,     out.metamorphic     );
        f(a.felsic_plutonic, b.felsic_plutonic, out.felsic_plutonic );
        f(a.felsic_volcanic, b.felsic_volcanic, out.felsic_volcanic );
        f(a.mafic_volcanic,  b.mafic_volcanic,  out.mafic_volcanic  );
        f(a.mafic_plutonic,  b.mafic_plutonic,  out.mafic_plutonic  );
        // f(a.age,             b.age,             out.age             );
    }
    template<typename F, typename T>
    inline void transform_mass(const Crust& a, const T b, F f, Crust& out) {
        f(a.sediment,        b, out.sediment        );
        f(a.sedimentary,     b, out.sedimentary     );
        f(a.metamorphic,     b, out.metamorphic     );
        f(a.felsic_plutonic, b, out.felsic_plutonic );
        f(a.felsic_volcanic, b, out.felsic_volcanic );
        f(a.mafic_volcanic,  b, out.mafic_volcanic  );
        f(a.mafic_plutonic,  b, out.mafic_plutonic  );
        // f(a.age,             b, out.age             );
    }



    template<typename F>
    inline void transform_conserved(const Crust& in, F f, Crust& out) {
        f(in.sediment,        out.sediment        );
        f(in.sedimentary,     out.sedimentary     );
        f(in.metamorphic,     out.metamorphic     );
        f(in.felsic_plutonic, out.felsic_plutonic );
        f(in.felsic_volcanic, out.felsic_volcanic );
        // f(in.mafic_volcanic,  out.mafic_volcanic  );
        // f(in.mafic_plutonic,  out.mafic_plutonic  );
        // f(in.age,             out.age             );
    }
    template<typename F>
    inline void transform_conserved(const Crust& a, const Crust& b, F f, Crust& out) {
        f(a.sediment,        b.sediment,        out.sediment        );
        f(a.sedimentary,     b.sedimentary,     out.sedimentary     );
        f(a.metamorphic,     b.metamorphic,     out.metamorphic     );
        f(a.felsic_plutonic, b.felsic_plutonic, out.felsic_plutonic );
        f(a.felsic_volcanic, b.felsic_volcanic, out.felsic_volcanic );
        // f(a.mafic_volcanic,  b.mafic_volcanic,  out.mafic_volcanic  );
        // f(a.mafic_plutonic,  b.mafic_plutonic,  out.mafic_plutonic  );
        // f(a.age,             b.age,             out.age             );
    }
    template<typename F, typename T>
    inline void transform_conserved(const Crust& a, const T b, F f, Crust& out) {
        f(a.sediment,        b, out.sediment        );
        f(a.sedimentary,     b, out.sedimentary     );
        f(a.metamorphic,     b, out.metamorphic     );
        f(a.felsic_plutonic, b, out.felsic_plutonic );
        f(a.felsic_volcanic, b, out.felsic_volcanic );
        // f(a.mafic_volcanic,  b, out.mafic_volcanic  );
        // f(a.mafic_plutonic,  b, out.mafic_plutonic  );
        // f(a.age,             b, out.age             );
    }

    void copy(Crust& out, const Crust& source) {
        transform_all(source, copy, out);
    }
    void reset(Crust& crust) {
        transform_all(source, 0.f, fill, out);
    }
    void mult(const Crust& crust, raster& field, Crust& result) {
        transform_all(source, field, mult, out);
    }
    void add(const Crust& crust, const Crust& delta, Crust& result) {
        transform_all(source, delta, add, out);
    }

    Crust& operator+=(Crust& crust, const Crust& delta) 
    {
        crust.sediment        += delta.sediment;        
        crust.sedimentary     += delta.sedimentary;     
        crust.metamorphic     += delta.metamorphic;     
        crust.felsic_plutonic += delta.felsic_plutonic; 
        crust.felsic_volcanic += delta.felsic_volcanic; 
        crust.mafic_volcanic  += delta.mafic_volcanic;  
        crust.mafic_plutonic  += delta.mafic_plutonic;  
        crust.age             += delta.age;             
        return crust;
    }
    Crust& operator*=(Crust& crust, const Crust& delta) 
    {
        crust.sediment        *= delta.sediment;        
        crust.sedimentary     *= delta.sedimentary;     
        crust.metamorphic     *= delta.metamorphic;     
        crust.felsic_plutonic *= delta.felsic_plutonic; 
        crust.felsic_volcanic *= delta.felsic_volcanic; 
        crust.mafic_volcanic  *= delta.mafic_volcanic;  
        crust.mafic_plutonic  *= delta.mafic_plutonic;  
        crust.age             *= delta.age;             
        return crust;
    }

    float get_average_conserved_per_cell(const Crust& crust) {  
        float conserved;
        conserved += sum(crust.sediment        );
        conserved += sum(crust.sedimentary     );
        conserved += sum(crust.metamorphic     );
        conserved += sum(crust.felsic_plutonic );
        conserved += sum(crust.felsic_volcanic );
        // conserved += sum(crust.mafic_volcanic  );
        // conserved += sum(crust.mafic_plutonic  );
        // conserved += sum(crust.age             );
        return conserved / crust.size();
    }
    void get_conserved_mass(const Crust& crust, raster& conserved) {
        fill(conserved, 0.f);
        conserved += crust.sediment;        
        conserved += crust.sedimentary;     
        conserved += crust.metamorphic;     
        conserved += crust.felsic_plutonic; 
        conserved += crust.felsic_volcanic; 
        // conserved += crust.mafic_volcanic;  
        // conserved += crust.mafic_plutonic;  
        // conserved += crust.age;             
    }
    void get_total_mass(const Crust& crust, raster& total) {  
        fill(total, 0.f);
        total += crust.sediment;        
        total += crust.sedimentary;     
        total += crust.metamorphic;     
        total += crust.felsic_plutonic; 
        total += crust.felsic_volcanic; 
        total += crust.mafic_volcanic;  
        total += crust.mafic_plutonic;  
        // total += crust.age;         
    }
    void get_density(const raster& mass, const raster& thickness, float default_density, raster& density) {
        copy(density, mass);
        for (unsigned int i = 0; i < density.size(); i++) { 
            density[i] = thickness[i] > 0? density[i] / thickness[i] : default_density; 
        }
    }



    void get(const Crust& crust, const uint_raster& id_raster, Crust& result) {
        transform_all(crust, id_raster, get, result);
    }
    void fill(Crust& crust, const CrustProfile& rock_profile) {
        transform_all(crust, rock_profile, fill, crust);
    }
    void fill(Crust& crust, const bool_raster& selection_raster, const CrustProfile& rock_profile) {
        fill(crust.sediment,        selection_raster, rock_profile.sediment        );
        fill(crust.sedimentary,     selection_raster, rock_profile.sedimentary     );
        fill(crust.metamorphic,     selection_raster, rock_profile.metamorphic     );
        fill(crust.felsic_plutonic, selection_raster, rock_profile.felsic_plutonic );
        fill(crust.felsic_volcanic, selection_raster, rock_profile.felsic_volcanic );
        fill(crust.mafic_volcanic,  selection_raster, rock_profile.mafic_volcanic  );
        fill(crust.mafic_plutonic,  selection_raster, rock_profile.mafic_plutonic  );
        fill(crust.age,             selection_raster, rock_profile.age             );
    }
    void copy(Crust& crust1, const bool_raster& selection_raster, const Crust& crust2) {
        copy(crust1.sediment,        selection_raster, crust2.sediment        );
        copy(crust1.sedimentary,     selection_raster, crust2.sedimentary     );
        copy(crust1.metamorphic,     selection_raster, crust2.metamorphic     );
        copy(crust1.felsic_plutonic, selection_raster, crust2.felsic_plutonic );
        copy(crust1.felsic_volcanic, selection_raster, crust2.felsic_volcanic );
        copy(crust1.mafic_volcanic,  selection_raster, crust2.mafic_volcanic  );
        copy(crust1.mafic_plutonic,  selection_raster, crust2.mafic_plutonic  );
        copy(crust1.age,             selection_raster, crust2.age             );
    }

    void add_values_to_ids(const Crust& crust, const uint_raster& id_raster, const raster& value_crust, Crust& result) {
        add_values_to_ids(crust.sediment,        id_raster, value_crust.sediment,        result.sediment        );
        add_values_to_ids(crust.sedimentary,     id_raster, value_crust.sedimentary,     result.sedimentary     );
        add_values_to_ids(crust.metamorphic,     id_raster, value_crust.metamorphic,     result.metamorphic     );
        add_values_to_ids(crust.felsic_plutonic, id_raster, value_crust.felsic_plutonic, result.felsic_plutonic );
        add_values_to_ids(crust.felsic_volcanic, id_raster, value_crust.felsic_volcanic, result.felsic_volcanic );
        add_values_to_ids(crust.mafic_volcanic,  id_raster, value_crust.mafic_volcanic,  result.mafic_volcanic  );
        add_values_to_ids(crust.mafic_plutonic,  id_raster, value_crust.mafic_plutonic,  result.mafic_plutonic  );
        add_values_to_ids(crust.age,             id_raster, value_crust.age,             result.age             );
    }
    void fix_delta(Crust& delta, const Crust& crust, raster& scratch) {
        fix_nonnegative_conserved_quantity_delta(delta.sediment,        crust.sediment,        scratch);
        fix_nonnegative_conserved_quantity_delta(delta.sedimentary,     crust.sedimentary,     scratch);
        fix_nonnegative_conserved_quantity_delta(delta.metamorphic,     crust.metamorphic,     scratch);
        fix_nonnegative_conserved_quantity_delta(delta.felsic_plutonic, crust.felsic_plutonic, scratch);
        fix_nonnegative_conserved_quantity_delta(delta.felsic_volcanic, crust.felsic_volcanic, scratch);
        // fix_nonnegative_conserved_quantity_delta(delta.mafic_volcanic,  crust.mafic_volcanic,  scratch);
        // fix_nonnegative_conserved_quantity_delta(delta.mafic_plutonic,  crust.mafic_plutonic,  scratch);
        // fix_nonnegative_conserved_quantity_delta(delta.age,             crust.age,             scratch);
    }
    bool is_conserved_delta(Crust& delta, float threshold) {
        return get_average_conserved_per_cell(delta) < threshold; 
    }
    // a "transport delta" represents the spatial transport of mass within a pool, e.g. erosion
    // it does not represent the mass transferring between pools
    bool is_conserved_transport_delta(Crust& delta, float threshold) {
        bool is_conserved = true;
        is_conserved |= is_conserved_quantity_delta(delta.sediment,        threshold);
        is_conserved |= is_conserved_quantity_delta(delta.sedimentary,     threshold);
        is_conserved |= is_conserved_quantity_delta(delta.metamorphic,     threshold);
        is_conserved |= is_conserved_quantity_delta(delta.felsic_plutonic, threshold);
        is_conserved |= is_conserved_quantity_delta(delta.felsic_volcanic, threshold);
        // is_conserved |= is_conserved_quantity_delta(delta.mafic_volcanic,  threshold);
        // is_conserved |= is_conserved_quantity_delta(delta.mafic_plutonic,  threshold);
        // is_conserved |= is_conserved_quantity_delta(delta.age,             threshold);
        return is_conserved;
    }
    // a "reaction delta" represents the transfer of mass between pools, e.g. weathering
    // it does not represent the spatial transport of mass within a pool
    bool is_conserved_reaction_delta(Crust& delta, float threshold, raster& scratch) {
        // "scratch" represents the sum of masses between pools
        fill(scratch, 0.f);
        scratch += delta.sediment;        
        scratch += delta.sedimentary;     
        scratch += delta.metamorphic;     
        scratch += delta.felsic_plutonic; 
        scratch += delta.felsic_volcanic; 
        // scratch += delta.mafic_volcanic;  
        // scratch += delta.mafic_plutonic;  
        // scratch += delta.age;             
        scratch *= scratch;
        return sum(scratch > threshold * threshold) == 0;
    }



    



    
}


