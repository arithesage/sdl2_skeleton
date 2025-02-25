#ifndef __RESOURCE_POOL__
#define __RESOURCE_POOL__

#include <String.hpp>
#include <Dictionary.hpp>


class Resource;


/**
 * A pool containing resources of type R
 */
template <typename R = Resource>
class Pool
{
    private:
        static Dictionary<const char*, R> pool;

    public:
        /**
         * Returns a resource by its name
         */
        R Get (const char* resourceName);

        /**
         * Returns if a resource with the given name exists
         */
        bool Has (const char* resourceName);

        /**
         * Stores a new resource
         */
        void Store (const char* resourceName, R resource);
};


template <typename R>
Dictionary<const char*, R> Pool<R>::pool;


template <typename R>
R Pool<R>::Get (const char* resourceName)
{
    return pool[resourceName];
}


template <typename R>
bool Pool<R>::Has (const char* resourceName)
{
    return (pool.find (resourceName) != pool.end());
}


template <typename R>
void Pool<R>::Store (const char* resourceName, R resource)
{
    if (resource.IsValid () && !Has (resourceName))
    {
        pool[resourceName] = resource;
    }
}
#endif