#pragma once

// std libraries
#include <variant>          // variant

// in-house libraries
#include <si.hpp>

#include "StateSample.hpp"
#include "StateFunction.hpp"

#include "CompletedStateField.hpp"

namespace compound { 
namespace field {

    template<typename T1>
    class CompletedStateField
    {
    	template<typename T2>
	    using CompletedStateFieldVariant = std::variant<T2, StateSample<T2>, StateFunction<T2>>;

        class CompletedStateFieldValueVisitor
        {
            si::pressure p;
            si::temperature T;
        public:
            CompletedStateFieldValueVisitor(const si::pressure p, const si::temperature T)
            : p(p), T(T)
            {

            }
            T1 operator()(const T1 a                           ) const {
                return a;
            }
            T1 operator()(const StateSample<T1> a        ) const {
                return a.value;
            }
            T1 operator()(const StateFunction<T1> a ) const {
                return a(p,T);
            }
        };
        template<typename T2>
        class CompletedStateFieldMapVisitor
        {
        public:
            typedef std::function<T2(const T1)> F;
            F f;
            CompletedStateFieldMapVisitor(const F f)
            : f(f)
            {

            }
            CompletedStateFieldVariant<T2> operator()(const T1 a                           ) const {
                return f(a);
            }
            CompletedStateFieldVariant<T2> operator()(const StateSample<T1> a        ) const {
                return StateSample<T1>(f(a.value), a.pressure, a.temperature);
            }
            CompletedStateFieldVariant<T2> operator()(const StateFunction<T1> a ) const {
                // NOTE: capturing `this` results in a segfault when we call `this->f()`
                // This occurs even when we capture `this` by value.
                // I haven't clarified the reason, but it seems likely related to accessing 
                // the `f` attribute in a object that destructs after we exit out of the `map` function.
                auto fcopy = f; 
                return [fcopy, a](const si::pressure p, const si::temperature T){ return fcopy(a(p, T)); };
            }
        };
        class CompletedStateFieldFunctionVisitor
        {
        public:
            CompletedStateFieldFunctionVisitor()
            {

            }
            StateFunction<T1> operator()(const T1 a) const {
                return [a](const si::pressure p, const si::temperature T) { return a; };
            }
            StateFunction<T1> operator()(const StateSample<T1> a) const {
                T1 value = a.value;
                return [value](const si::pressure p, const si::temperature T) { return value; };
            }
            StateFunction<T1> operator()(const StateFunction<T1> a) const {
                // NOTE: capturing `this` results in a segfault when we call `this->f()`
                // This occurs even when we capture `this` by value.
                // I haven't clarified the reason, but it seems likely related to accessing 
                // the `f` attribute in a object that destructs after we exit out of the `map` function.
                return a;
            }
        };
        template<typename T2>
        class CompletedStateFieldMapToConstantVisitor
        {
            si::pressure default_p;
            si::temperature default_T;
            std::function<T2(T1, si::pressure, si::temperature)> f;
        public:
            CompletedStateFieldMapToConstantVisitor(
                const si::pressure default_p, 
                const si::temperature default_T,
                const std::function<T2(const T1, const si::pressure, const si::temperature)> f
            )
            : default_p(default_p), 
              default_T(default_T),
              f(f)
            {

            }
            T2 operator()( const T1 a                           ) const {
                return f(a, default_p, default_T);
            }
            T2 operator()( const StateSample<T1> a        ) const {
                return f(a.value, a.pressure, a.temperature);
            }
            T2 operator()( const StateFunction<T1> a ) const {
                return f(a(default_p, default_T), default_p, default_T);
            }
        };

        CompletedStateFieldVariant<T1> value;
    public:
        constexpr CompletedStateField(const CompletedStateFieldVariant<T1> value)
        : value(value)
        {

        }
        constexpr CompletedStateField(const T1 value)
        : value(value)
        {

        }
        constexpr CompletedStateField(const StateSample<T1> value)
        : value(value)
        {

        }
        constexpr CompletedStateField(const StateFunction<T1> value)
        : value(value)
        {

        }
    	template<typename T2>
        constexpr CompletedStateField<T1>& operator=(const T2& other)
        {
        	value = CompletedStateFieldVariant<T1>(other);
        	return *this;
        }
        constexpr T1 operator()(const si::pressure p, const si::temperature T) const
        {
            return std::visit(CompletedStateFieldValueVisitor(p, T), value);
        }
        /*
        Return whichever field provides more information, going by the following definition:
            std::monostate < T1 < StateFunction<T1> < std::pair<T1, StateFunction<T1>>
        If both provide the same amount of information, return `a` by default.
        */
        constexpr CompletedStateField<T1> compare(const CompletedStateField<T1> other) const
        {
            return value.index() >= other.value.index()? *this : other;
        }
        /*
		Return whether a value exists within the field
        */
        constexpr int index() const
        {
            return value.index();
        }
        /*
		Return whether a value exists within the field
        */
        constexpr bool has_value() const
        {
            return value.index() == 0;
        }
        constexpr StateFunction<T1> function() const
        {
            return std::visit(CompletedStateFieldFunctionVisitor(), value);
        }
        /*
        Return a CompletedStateField<T1> field representing `a` after applying the map `f`
        */
        template<typename T2>
        constexpr CompletedStateField<T2> map(const std::function<T2(const T1)> f) const
        {
            return CompletedStateField<T2>(std::visit(CompletedStateFieldMapVisitor<T2>(f), value));
        }
        /*
        Return a CompletedStateField<T1> field representing `a` after applying the map `f`
        */
        template<typename T2>
        constexpr T1 map_to_constant(
            const si::pressure default_p, 
            const si::temperature default_T, 
            const std::function<T2(const T1, const si::pressure, const si::temperature)> f
        ) const {
            return std::visit(CompletedStateFieldMapToConstantVisitor<T2>(default_p, default_T, f), value);
        }

        template<typename T2>
		friend class CompletedStateField;
    };
    
}}