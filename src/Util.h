using byte = unsigned char;
using word = unsigned short;
using uint = unsigned int;

#ifndef asm
#define asm __asm__ volatile
#endif

template<typename T>
inline void Copy(const T *from, T *to, uint count)
{
	const T *read = from;
	T *write = to;

	while (count--)
		*write++ = *read++;
}