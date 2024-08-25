#ifndef SIMD_UTIL_H
#define SIMD_UTIL_H

#include <immintrin.h>

// A non extensive compile-time redefinition of SIMD functions for AVX
// I did not like the naming of things so I changed it to be much more legible

namespace simd
{
    using floatAVX256 = __m256;      // Can hold up to 8 floats in each vector
    using doubleAVX256 = __m256d;    // Can hold up to 4 doubles in each vector.

    /*  Can hold up to:
        - 32 chars (8 bit)
        - 16 shorts (16 bit)
        - 8 ints (32 bit)
        - 4 long long (64 bit)
    */
    using intAVX256 = __m256i;

    using SetFloatAVX256 = floatAVX256(*)(float);                         // Create a vector of floats with a set value.
    using LoadFloatAVX256 = floatAVX256(*)(float const*);                // Move array of floats into AVX vector.
    using StoreFloatAVX256 = void (*)(float*, floatAVX256);               // Return AVX vector as array of floats.
    using ArithFloatAVX256 = floatAVX256(*)(floatAVX256, floatAVX256);    // AVX arithmetic definition.
    using SqrtFloatAVX256 = floatAVX256(*)(floatAVX256);                  // Take the sqaure-root of each element in AVX vector.
    using RecpSqrtFloatAVX256 = floatAVX256(*)(floatAVX256);              // Recipricol of sqaure roots of floats.
    using RecpFloatAVX256 = floatAVX256(*)(floatAVX256);                  // Recipricol of floats.
    //using cmpFloatAVX256 = floatAVX256(*)(floatAVX256, floatAVX256);

    using SetDoubleAVX256 = doubleAVX256(*)(double);                      //
    using LoadDoubleAVX256 = doubleAVX256(*)(double const*);             //
    using StoreDoubleAVX256 = void (*)(double*, doubleAVX256);            //
    using ArithDoubleAVX256 = doubleAVX256(*)(doubleAVX256, doubleAVX256);//
    using SqrtDoubleAVX256 = doubleAVX256(*)(doubleAVX256);               //
    //using cmpDoubleAVX256 = doubleAVX256(*)(doubleAVX256, doubleAVX256);

    using SetInt8AVX256 = intAVX256(*)(char);                             //
    using LoadInt8AVX256 = intAVX256(*)(intAVX256 const*);                //
    using StoreInt8AVX256 = void (*)(intAVX256*, intAVX256);              //
    using ArithInt8AVX256 = intAVX256(*)(intAVX256, intAVX256);           //
    //using SqrtInt8AVX256 = intAVX256(*)(intAVX256);                       //
    //using cmpInt8AVX256 = intAVX256(*)(intAVX256, intAVX256);              

    using SetInt16AVX256 = intAVX256(*)(short);                           //
    using LoadInt16AVX256 = intAVX256(*)(intAVX256 const*);               //
    using StoreInt16AVX256 = void (*)(intAVX256*, intAVX256);             //
    using ArithInt16AVX256 = intAVX256(*)(intAVX256, intAVX256);          //
    //using SqrtInt16AVX256 = intAVX256(*)(intAVX256);                      //
    //using cmpInt16AVX256 = intAVX256(*)(intAVX256, intAVX256);            

    using SetInt32AVX256 = intAVX256(*)(int);                             //
    using LoadInt32AVX256 = intAVX256(*)(intAVX256 const*);               //
    using StoreInt32AVX256 = void (*)(intAVX256*, intAVX256);             //
    using ArithInt32AVX256 = intAVX256(*)(intAVX256, intAVX256);          //
    //using SqrtInt32AVX256 = intAVX256(*)(intAVX256);                      //
    //using cmpInt32AVX256 = intAVX256(*)(intAVX256, intAVX256);            

    using SetInt64AVX256 = intAVX256(*)(long long);                       //
    using LoadInt64AVX256 = intAVX256(*)(intAVX256 const*);               //
    using StoreInt64AVX256 = void (*)(intAVX256*, intAVX256);             //
    using ArithInt64AVX256 = intAVX256(*)(intAVX256, intAVX256);          //
    //using SqrtInt64AVX256 = intAVX256(*)(intAVX256);                      //
    //using cmpInt64AVX256 = intAVX256(*)(intAVX256, intAVX256);            

    constexpr SetFloatAVX256 setFloatAVX256 = _mm256_set1_ps;
    constexpr LoadFloatAVX256 loadFloatAVX256 = _mm256_loadu_ps;
    constexpr StoreFloatAVX256 storeFloatAVX256 = _mm256_storeu_ps;
    constexpr ArithFloatAVX256 addFloatAVX256 = _mm256_add_ps;
    constexpr ArithFloatAVX256 subFloatAVX256 = _mm256_sub_ps;
    constexpr ArithFloatAVX256 mulFloatAVX256 = _mm256_mul_ps;
    constexpr ArithFloatAVX256 divFloatAVX256 = _mm256_div_ps;
    constexpr SqrtFloatAVX256 sqrtFloatAVX256 = _mm256_sqrt_ps;
    constexpr RecpSqrtFloatAVX256 recpSqrtFloatAVX256 = _mm256_rsqrt_ps;
    constexpr RecpFloatAVX256 recpFloatAVX256 = _mm256_rcp_ps;

    constexpr SetDoubleAVX256 setDoubleAVX256 = _mm256_set1_pd;
    constexpr LoadDoubleAVX256 loadDoubleAVX256 = _mm256_loadu_pd;
    constexpr StoreDoubleAVX256 storeDoubleAVX256 = _mm256_storeu_pd;
    constexpr ArithDoubleAVX256 addDoubleAVX256 = _mm256_add_pd;
    constexpr ArithDoubleAVX256 subDoubleAVX256 = _mm256_sub_pd;
    constexpr ArithDoubleAVX256 mulDoubleAVX256 = _mm256_mul_pd;
    constexpr ArithDoubleAVX256 divDoubleAVX256 = _mm256_div_pd;
    constexpr SqrtDoubleAVX256 sqrtDoubleAVX256 = _mm256_sqrt_pd;

    //constexpr SetInt8AVX256 setInt8AVX256 = _mm256_set1_epi8;
    //constexpr LoadInt8AVX256 loadInt8AVX256 = _mm256_loadu_si256;
    //constexpr StoreInt8AVX256 storeInt8AVX256 = _mm256_storeu_si256;
    //constexpr ArithInt8AVX256 addInt8AVX256 = _mm256_add_epi8;
    //constexpr ArithInt8AVX256 subInt8AVX256 = _mm256_sub_epi8;

    //constexpr SetInt16AVX256 setInt16AVX256 = _mm256_set1_epi16;
    //constexpr LoadInt16AVX256 loadInt16AVX256 = _mm256_loadu_si256;
    //constexpr StoreInt16AVX256 storeInt16AVX256 = _mm256_storeu_si256;
    //constexpr ArithInt16AVX256 addInt16AVX256 = _mm256_add_epi16;
    //constexpr ArithInt16AVX256 subInt16AVX256 = _mm256_sub_epi16;

    //constexpr SetInt32AVX256 setInt32AVX256 = _mm256_set1_epi32;
    //constexpr LoadInt32AVX256 loadInt32AVX256 = _mm256_loadu_si256;
    //constexpr StoreInt32AVX256 storeInt32AVX256 = _mm256_storeu_si256;
    //constexpr ArithInt32AVX256 addInt32AVX256 = _mm256_add_epi32;
    //constexpr ArithInt32AVX256 subInt32AVX256 = _mm256_sub_epi32;
    //constexpr ArithInt32AVX256 mulInt32AVX256 = _mm256_mullo_epi32;  // Corrected to _mm256_mullo_epi32

    //constexpr SetInt64AVX256 setInt64AVX256 = _mm256_set1_epi64x;
    //constexpr LoadInt64AVX256 loadInt64AVX256 = _mm256_loadu_si256;
    //constexpr StoreInt64AVX256 storeInt64AVX256 = _mm256_storeu_si256;
    //constexpr ArithInt64AVX256 addInt64AVX256 = _mm256_add_epi64;
    //constexpr ArithInt64AVX256 subInt64AVX256 = _mm256_sub_epi64;
}

#endif
