//Comment out if strip or ring is being used
#define strip

#ifndef strip
    #define ring
#endif

//Comment out depening on large or small ring
//Large ring is only used on the horizontial blowers
#ifdef ring
    #define large
    //#define small
#endif

//Comment out if you are not using the pot
#define controlledSpeed

//comment out if not using stop button - used to set pinMode
#define hasStop
