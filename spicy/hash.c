#include <string.h>

unsigned csharp_hashcode(const char *s)
{
	int hash1 = (5381 << 16) + 5381;
    int hash2 = hash1;

	const char *p = s;
    int len = strlen(s);
    while (len > 2)
    {
        hash1 = ((hash1 << 5) + hash1 + (hash1 >> 27)) ^ (p[0] + (p[1] << 16));
        hash2 = ((hash2 << 5) + hash2 + (hash2 >> 27)) ^ (p[2] + (p[3] << 16));
        p += 4;
        len -= 4;
    }

    if (len > 0)
    {
        hash1 = ((hash1 << 5) + hash1 + (hash1 >> 27)) ^ (p[0] + (p[1] << 16));
    }

    return hash1 + (hash2 * 1566083941);
}
