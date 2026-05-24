#pragma once
#include <concepts>
#include <cstddef>

template <typename C>
concept SequenceContainer = requires(C c, typename C::value_type v) {
    c.Append(v);                                        
    c.Prepend(v);                                      
    c.InsertAt(v, size_t{0});                           
    { c.GetLength() } -> std::convertible_to<size_t>;    
    { c[0] } -> std::same_as<typename C::reference>;      
    { c.Get(0) } -> std::same_as<typename C::value_type>;  
    { c.GetFirst() } -> std::same_as<typename C::value_type>;
    { c.GetLast() } -> std::same_as<typename C::value_type>;  
};