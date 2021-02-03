#pragma once

// std libraries
#include <variant>          // variant

// in-house libraries
#include <si.hpp>

#include "StateSample.hpp"
#include "StateFunction.hpp"

#include "OptionalStateField.hpp"

namespace compound { 
namespace field {

    template<typename T1>
    class OptionalStateField
    {
    	template<typename T2>
        using OptionalStateFieldVariant = std::variant<std::monostate, T2, StateSample<T2>, StateFunction<T2>>;
        template<typename T2>
	    using CompletedStateFieldVariant = std::variant<T2, StateSample<T2>, StateFunction<T2>>;

        class OptionalStateFieldValueVisitor
        {
            si::pressure p;
            si::temperature T;
        public:
            OptionalStateFieldValueVisitor(const si::pressure p, const si::temperature T)
            : p(p), T(T)
            {

            }
            std::optional<T1> operator()(const std::monostate a               ) const {
                return std::optional<T1>();
            }
            std::optional<T1> operator()(const T1 a                           ) const {
                return a;
            }
            std::optional<T1> operator()(const StateSample<T1> a        ) const {
                return a.entry;
            }
            std::optional<T1> operator()(const StateFunction<T1> a ) const {
                return a(p,T);
            }
        };
        template<typename T2>
        class OptionalStateFieldMapVisitor
        {
        public:
            typedef std::function<T2(const T1)> F;
            F f;
            OptionalStateFieldMapVisitor(const F f)
            : f(f)
            {

            }
            OptionalStateFieldVariant<T2> operator()(const std::monostate a               ) const {
                return std::monostate();
            }
            OptionalStateFieldVariant<T2> operator()(const T1 a                           ) const {
                return f(a);
            }
            OptionalStateFieldVariant<T2> operator()(const StateSample<T1> a        ) const {
                return StateSample<T1>(f(a.entry), a.pressure, a.temperature);
            }
            OptionalStateFieldVariant<T2> operator()(const StateFunction<T1> a ) const {
                // NOTE: capturing `this` results in a segfault when we call `this->f()`
                // This occurs even when we capture `this` by entry.
                // I haven't clarified the reason, but it seems likely related to accessing 
                // the `f` attribute in a object that destructs after we exit out of the `map` function.
                auto fcopy = f; 
                return [fcopy, a](const si::pressure p, const si::temperature T){ return fcopy(a(p, T)); };
            }
        };
        template<typename T2>
        class OptionalStateFieldMapToConstantVisitor
        {
            si::pressure default_p;
            si::temperature default_T;
            std::function<T2(T1, si::pressure, si::temperature)> f;
        public:
            OptionalStateFieldMapToConstantVisitor(
                const si::pressure default_p, 
                const si::temperature default_T,
                const std::function<T2(const T1, const si::pressure, const si::temperature)> f
            )
            : default_p(default_p), 
              default_T(default_T),
              f(f)
            {

            }
            std::optional<T2> operator()( const std::monostate a               ) const {
                return std::optional<T2>();
            }
            std::optional<T2> operator()( const T1 a                           ) const {
                return f(a, default_p, default_T);
            }
            std::optional<T2> operator()( const StateSample<T1> a        ) const {
                return f(a.entry, a.pressure, a.temperature);
            }
            std::optional<T2> operator()( const StateFunction<T1> a ) const {
                return f(a(default_p, default_T), default_p, default_T);
            }
        };
        class OptionalStateFieldCompletionVisitor
        {
            CompletedStateFieldVariant<T1> fallback;
        public:
            OptionalStateFieldCompletionVisitor(CompletedStateFieldVariant<T1> fallback) : fallback(fallback)
            {

            }
            CompletedStateFieldVariant<T1> operator()(const std::monostate a               ) const {
                return fallback;
            }
            CompletedStateFieldVariant<T1> operator()(const T1 a                           ) const {
                return a;
            }
            CompletedStateFieldVariant<T1> operator()(const StateSample<T1> a        ) const {
                return a;
            }
            CompletedStateFieldVariant<T1> operator()(const StateFunction<T1> a ) const {
                return a;
            }
        };

        OptionalStateFieldVariant<T1> entry;
    public:
        constexpr OptionalStateField(const OptionalStateFieldVariant<T1> entry)
        : entry(entry)
        {

        }
        constexpr OptionalStateField(const std::monostate entry)
        : entry(entry)
        {

        }
        constexpr OptionalStateField(const T1 entry)
        : entry(entry)
        {

        }
        constexpr OptionalStateField(const StateSample<T1> entry)
        : entry(entry)
        {

        }
        constexpr OptionalStateField(const StateFunction<T1> entry)
        : entry(entry)
        {

        }
    	template<typename T2>
        constexpr OptionalStateField<T1>& operator=(const T2& other)
        {
            entry = OptionalStateFieldVariant<T1>(other);
            return *this;
        }
        constexpr bool operator==(const OptionalStateField<T1> other) const
        {
            return entry == other.entry;
        }
        constexpr std::optional<T1> operator()(const si::pressure p, const si::temperature T) const
        {
            return std::visit(OptionalStateFieldValueVisitor(p, T), entry);
        }
        /*
        Return whichever field provides more information, going by the following definition:
            std::monostate < T1 < StateFunction<T1> < std::pair<T1, StateFunction<T1>>
        If both provide the same amount of information, return `a` by default.
        */
        constexpr OptionalStateField<T1> compare(const OptionalStateField<T1> other) const
        {
            return entry.index() >= other.entry.index()? *this : other;
        }
        /*
        Return `a` if available, otherwise return `b` as a substitute.
        */
        constexpr OptionalStateField<T1> value_or(const OptionalStateField<T1> other) const
        {
            return entry.index() > 0? *this : other;
        }
        constexpr CompletedStateFieldVariant<T1> value_or(CompletedStateFieldVariant<T1> fallback) const 
        {
            return std::visit(OptionalStateFieldCompletionVisitor(fallback), entry);
        }
        /*
		Return whether a entry exists within the field
        */
        constexpr bool has_entry() const
        {
            return entry.index() == 0;
        }
        /*
		Return whether a entry exists within the field
        */
        constexpr int index() const
        {
            return entry.index();
        }
        /*
        Return a OptionalStateField<T1> field representing `a` after applying the map `f`
        */
        template<typename T2>
        constexpr OptionalStateField<T2> map(const std::function<T2(const T1)> f) const
        {
            return OptionalStateField<T2>(std::visit(OptionalStateFieldMapVisitor<T2>(f), entry));
        }
        /*
        Return a OptionalStateField<T1> field representing `a` after applying the map `f`
        */
        template<typename T2>
        constexpr std::optional<T1> map_to_constant(
            const si::pressure default_p, 
            const si::temperature default_T, 
            const std::function<T2(const T1, const si::pressure, const si::temperature)> f
        ) const {
            return std::visit(OptionalStateFieldMapToConstantVisitor<T2>(default_p, default_T, f), entry);
        }

        template<typename T2>
		friend class OptionalStateField;
    };
    
}}