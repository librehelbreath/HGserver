
#define DEF_UPPERVERSION		"2"

#if		defined(DEF_INTERSERVER)

	#define DEF_LOWERVERSION 		"20"
	#define DEF_BUILDDATE			306

#elif		defined(DEF_USA)

	#define DEF_LOWERVERSION 		"20"
	#define DEF_BUILDDATE			222

#elif		defined(DEF_KOREA)

	#define DEF_LOWERVERSION 		"20"
	#define DEF_BUILDDATE			207

#elif		defined(DEF_CHINESE)

	#define DEF_LOWERVERSION 		"19"
	#define DEF_BUILDDATE			429		// 310


#else	// 다른 국가들

	#define DEF_LOWERVERSION 		"19"
	#define DEF_BUILDDATE			213


#endif