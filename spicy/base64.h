#define BASE64_LENGTH(inlen) ((((inlen) + 2) / 3) * 4)

static unsigned char to_uchar(char ch)
{
	return ch;
}

static const char b64c[64] =
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static void base64_encode_fast(const char *in, size_t inlen, char *out)
{
	while (inlen) {
		*out++ = b64c[to_uchar (in[0]) >> 2];
		*out++ = b64c[((to_uchar (in[0]) << 4) + (to_uchar (in[1]) >> 4)) & 0x3f];
		*out++ = b64c[((to_uchar (in[1]) << 2) + (to_uchar (in[2]) >> 6)) & 0x3f];
		*out++ = b64c[to_uchar (in[2]) & 0x3f];
	
		inlen -= 3;
		in += 3;
	}
}

void base64_encode(const char *in, size_t inlen, char *out, size_t outlen)
{
	if (outlen % 4 == 0 && inlen == outlen / 4 * 3) {
		base64_encode_fast(in, inlen, out);
		return;
	}

	while (inlen && outlen) {
		*out++ = b64c[to_uchar (in[0]) >> 2];
		if (!--outlen)
			break;

		*out++ = b64c[((to_uchar (in[0]) << 4) +
			(--inlen ? to_uchar (in[1]) >> 4 : 0)) & 0x3f];
		if(!--outlen)
			break;

		*out++ = (
			inlen
			? b64c[((to_uchar (in[1]) << 2) +
				(--inlen ? to_uchar (in[2]) >> 6 : 0)) & 0x3f]
			: '=');
		if(!--outlen)
			break;

		*out++ = inlen ? b64c[to_uchar (in[2]) & 0x3f] : '=';
		if (!--outlen)
			break;

		if (inlen)
			inlen--;

		if (inlen)
			in += 3;
	}

	if (outlen)
		*out = '\0';
}

void base64_encode_alloc(const char *in, size_t inlen, char **out)
{
	size_t outlen = 1 + BASE64_LENGTH(inlen);
	if (inlen > outlen) {
		*out = NULL;
		return;
	}

	*out = malloc(outlen);
	if (!*out)
		return;

	base64_encode(in, inlen, *out, outlen);
}

#define ENC_BLOCKSIZE (1024*3*10)

#ifndef MIN
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#endif

static void wrap_write(const char *buffer, size_t len, unsigned wrap_column,
	size_t *current_column, FILE *out)
{
	size_t written;

	if (wrap_column == 0) {
		/* don't wrap */
		fwrite(buffer, 1, len, out);
	}
	else {
		for (written = 0; written < len; ) {
			unsigned cols_remaining = wrap_column - *current_column;
			if (cols_remaining == 0) {
				fputc('\n', out);
				*current_column = 0;
			} else {
				size_t to_write = MIN(
					cols_remaining, len - written);
				fwrite(buffer + written, 1, to_write, out);
				*current_column += to_write;
				written += to_write;
			}
		}
	}
}


void do_base64_encode(FILE *in, FILE *out, unsigned wrap_column)
{
	size_t current_column = 0;
	char inbuf[ENC_BLOCKSIZE];
	char outbuf[BASE64_LENGTH(ENC_BLOCKSIZE)];
	size_t sum;

	do {
		size_t n;

		sum = 0;
		do {
			n = fread(inbuf + sum, 1, ENC_BLOCKSIZE - sum, in);
			sum += n;
		} while (!feof(in) && !ferror(in) && sum < ENC_BLOCKSIZE);

		if (sum > 0) {
			base64_encode(inbuf, sum, outbuf, BASE64_LENGTH(sum));
			wrap_write(outbuf, BASE64_LENGTH(sum), wrap_column,
				&current_column, out);
		}
	} while (!feof(in) && !ferror(in) && sum == ENC_BLOCKSIZE);

	if (wrap_column && current_column)
		fputc('\n', out);
}

