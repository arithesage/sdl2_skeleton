#ifndef __TYPES_DICTIONARY__
#define __TYPES_DICTIONARY__

#include <map>
#include <unordered_map>

template <typename Key, typename Value>
using Dictionary = std::unordered_map<Key,Value>;

template <typename Key, typename Value>
using Map = std::map<Key, Value>;

#endif