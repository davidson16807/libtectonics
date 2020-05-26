#include <cmath>
#include <cstdint>
#include <cstddef>

#include <algorithm>

#include <genes/coding.hpp>    // encode_*(), decode_*()

namespace genes
{
    // Most arthropods seem to have ~7 segments, but their common ancestor may have had up to 11 (Kukalova-Peck, 1992).
    // In the absence of a firm answer, we should probably set this number to something that helps us conserve memory and line up with cache sizes.
    // setting APPENDAGE_SEGMENT_COUNT = 8 allows us to easily reason with memory alignment and cache lines
    const int APPENDAGE_SEGMENT_COUNT = 8;

    // 120 bytes
ruct Appendage
    {
        /*
        BODY SCALING SYSTEM:
        total body length                       meters, log scale
        total body width                        max body segment width found within the body
        total body height                       max body segment height found within the body
        body segment length                     relative portion of total body length
        body segment height                     multiple of total body length, log scale
        body segment width                      multiple of total body length, log scale
        appendage length                        multiple of total body length, log scale
        appendage width                         max appendage segment width found within the appendage
        appendage height                        max appendage segment height found within the appendage
        appendage segment length                relative portion of appendage length
        appendage segment height                fraction of body segment height
        appendage segment width                 fraction of body segment length
        appendage segment insertion             fraction of parent appendage segment
        appendage segment thickness attributes  proportion of half the appendage segment width or height, whichever is smallest
        appendage segment vessel radius         proportion of half the appendage segment width or height, whichever is smallest
        appendage segment vessel thickness      fraction of corresponding vessel radius
        appendage segment coverage              fraction of appendage segment surface area
        */

        // appendage segments
        std::array<AppendageSegment, APPENDAGE_SEGMENT_COUNT> segments;

        // scaling, such as hair
        Scaling scaling;

        // pigmentation for intentional displays, such as startle or mating displays
        Pigmentation pigmentation;

        // mineralization for dermal bone, such as turtle shell, or the human skull
        Mineralization exterior_mineralization;

        // corneous structure, such as claws, talons, hooves, spikes, clubs
        CorneousStructure corneous_structure;

        // eyes, ranging from primitive photosensitive regions to human eyes
        PhotoreceptorStructure photoreceptor_structure;

        // ears, ranging from fine exposed hairs to multi component structures
        PressureSensingStructure pressure_sensing_structure;

        // basic dimensions
        float length;
        float width;
        float height;

        // miscellaneous
        // detects motion within appendages, notably including johnston's organ for detecting sound in insects
        float kinaesthetic_motion_detector;

        // chemical detection by touch or by air
        // more effective when exposed to a continuous resupply of air,
        // either by swishing the appendage (antenna) or by moving air or fluid across it,
        // such as by placing it near an intake for a pneumatic system (nose)
        float chemical_receptor_coverage; 

        float fused_segments_factor;

        template<typename TIterator>
        TIterator encode(TIterator output) const
        {
            for (auto segment = segments.begin(); 
                 segment != segments.end(); ++segment)
            {
                output = segment->encode(output);
            }
            output = Scaling                 ::encode(output);  
            output = Pigmentation            ::encode(output);
            output = Mineralization          ::encode(output);
            output = CorneousStructure       ::encode(output);
            output = PhotoreceptorStructure  ::encode(output);
            output = PressureSensingStructure::encode(output);
            *output++ = encode_fraction(length);
            *output++ = encode_fraction(width );
            *output++ = encode_fraction(height);
            *output++ = encode_fraction(kinaesthetic_motion_detector);
            *output++ = encode_fraction(chemical_receptor_coverage  );
            *output++ = encode_fraction(fused_segments_factor       );
            return output;
        }
        template<typename TIterator>
        TIterator decode(TIterator input)
        {
            for (auto segment = segments.begin(); 
                 segment != segments.end(); ++segment)
            {
                decode = segment::decode(decode);
            }
            input = Scaling                 ::decode(input);  
            input = Pigmentation            ::decode(input);
            input = Mineralization          ::decode(input);
            input = CorneousStructure       ::decode(input);
            input = PhotoreceptorStructure  ::decode(input);
            input = PressureSensingStructure::decode(input);
            length = decode_fraction(*output++);
            width  = decode_fraction(*output++);
            height = decode_fraction(*output++);
            kinaesthetic_motion_detector = decode_fraction(*output++);
            chemical_receptor_coverage   = decode_fraction(*output++);
            fused_segments_factor        = decode_fraction(*output++);
            return input;
        }
        template<typename TIterator>
        static TIterator getMutationRates(TIterator output)
        {
            for (auto segment = segments.begin(); 
                 segment != segments.end(); ++segment)
            {
                output = AppendageSegment::getMutationRates(output);
            }
            output = Scaling                 ::getMutationRates(output);  
            output = Pigmentation            ::getMutationRates(output);
            output = Mineralization          ::getMutationRates(output);
            output = CorneousStructure       ::getMutationRates(output);
            output = PhotoreceptorStructure  ::getMutationRates(output);
            output = PressureSensingStructure::getMutationRates(output);
            output = std::fill_n(output, 6, 1);
            return output;
        }
        template<typename TIterator>
        static TIterator getAttributeSizes(TIterator output)
        {
            for (auto segment = segments.begin(); 
                 segment != segments.end(); ++segment)
            {
                output = AppendageSegment::getAttributeSizes(output);
            }
            output = Scaling                 ::getAttributeSizes(output);  
            output = Pigmentation            ::getAttributeSizes(output);
            output = Mineralization          ::getAttributeSizes(output);
            output = CorneousStructure       ::getAttributeSizes(output);
            output = PhotoreceptorStructure  ::getAttributeSizes(output);
            output = PressureSensingStructure::getAttributeSizes(output);
            output = std::fill_n(output, 6, 4);
            return output;
        }
    };
}
