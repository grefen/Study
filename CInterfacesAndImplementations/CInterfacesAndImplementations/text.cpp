#include "string.h"
#include "limits.h"
#include "assert.h"
#include "fmt.h"
#include "Text.h"
#include "mem.h"

#define T Text_T

#define idx(i, len) ( (i) <= 0? (i) + (len) : (i) - 1)

struct Text_save_T
{
	struct chunk* current;
	char* avail;
};

static char cset[256] = {0};

const T Text_cset = {256, cset};
const T Text_ascii= {127, cset};
const T Text_ucase= {26, cset + 'A'};
const T Text_lcase= {26, cset + 'a'};
const T Text_digits = {10, cset + '0'};
const T Text_null = {0, cset};

static struct chunk
{
	struct chunk* link;
	char* avail;
	char* limit;
}head = {NULL, NULL, NULL},*current = &head;


static char* alloc(int len)
{
	assert(len >= 0);

	if(current->avail + len > current->limit)
	{
		current = current->link = ALLOC(sizeof(*current) + 10*1024 + len);
		current->avail = (char*)(current + 1);
		current->limit = current->avail + 10*1024 + len;
		current->link  = NULL;
	}
	current->avail += len;
	return current->avail - len;
}

#define isatend(s, n) ((s).str + (s.len) == current->avail && current->avail + (n) <= current->limit)
#define equal(s, i, t) (memcmp(&(s).str[i], (t).str, (t).len) == 0)

int Text_pos(T s, int i)
{
	assert(s.len >= 0 && s.str);

	i = idx(i, s.len);

	assert(i >= 0 && i <= s.len);
	return i + 1;
}

T Text_box(const char* str, int len)
{
	T text;

	assert(str);
	assert(len >= 0);
	text.str = str;
	text.len = len;

	return text;
}

T Text_sub(T s, int i, int j)
{
	T text;

	assert(s.len >= 0 && s.str);
	i = idx(i, s.len);
	j = idx(j, s.len);

	if( i > j){int t = i; i = j; j = t;}

	assert(i >= 0 && j <= s.len);

	text.len = j - i;
	text.str = s.str + i;

	return text;
}

T Text_put(const char* str)
{
	T text;

	assert(str);
	text.len = strlen(str);
	text.str = memcpy(alloc(text.len), str, text.len);

	return text;
}

char* Text_get(char* str, int size, T s)
{
	assert(s.len >= 0 && s.str);

	if(str == NULL)
		str = ALLOC(s.len + 1);
	else
		assert(size >= s.len + 1);

	memcpy(str, s.str, s.len);

	str[s.len] = '\0';

	return str;
}

T Text_dup(T s, int n)
{
	assert(s.len >= 0 && s.str);
	assert(n >= 0);

	if(n == 0 || s.len == 0)
		return Text_null;
	if(n == 1)
		return s;
	{
		T text;
		char* p;

		text.len = n*s.len;

		if(isatend(s, text.len - s.len))
		{
			text.str = s.str;
			p = alloc(text.len - s.len);
			n--;
		}
		else
		{
			text.str = p = alloc(text.len);
		}

		for(; n-- > 0; p += s.len)
			memcpy(p, s.str, s.len);
		return text;
	}
}

T Text_cat(T s1, T s2)
{
	assert(s1.len >= 0 && s1.str);
	assert(s2.len >= 0 && s2.str);

	if(s1.len == 0)
		return s2;
	if(s1.len == 0)
		return s1;

	if(s1.str + s1.len == s2.str)
	{
		s1.len += s2.len;
		return s1;
	}

	{
		T text;

		text.len = s1.len + s2.len;

		if(isatend(s1, s2.len))
		{
			text.str = s1.str;
			memcpy(alloc(s2.len), s2.str,s2.len);
		}
		else
		{
			char* p;

			text.str = p = alloc(s1.len + s2.len);
			memcpy(p, s1.str, s1.len);
			memcpy(p + s1.len , s2.str, s2.len);
		}

		return text;
	}
}

T Text_reverse(T s)
{
	assert(s.len >= 0 && s.str);

	if(s.len == 0)
		return Text_null;
	else if(s.len == 1)
	{
		return s;
	}
	else
	{
		T text;

		char* p;

		int i = s.len;
		text.len = s.len;
		text.str = p = alloc(s.len);

		while(--i >= 0)
			*p++ = s.str[i];
		return text;
	}

}

T Text_map(T s, const T* from, const T* to)
{
	static char map[256];
	static int  inited = 0;

	assert(s.len >= 0 && s.str);
	if(from && to)
	{
		int k;
		for(k = 0; k < (int)sizeof map; k++)
			map[k] = k;
		assert(from->len == to->len);
		for(k = 0; k < from->len; k++)
			map[from->str[k]] = to->str[k];

		inited = 1;
	}
	else
	{
		assert(from == NULL && to == NULL);
		assert(inited);
	}

	if(s.len == 0)
		return Text_null;
	else{
		T text;

		int i;
		char* p;
		text.len = s.len;
		text.str = p = alloc(s.len);
		for(i = 0; i < s.len; i++)
		{
			*p++ = map[s.str[i]];
		}

		return text;
	}
}

int Text_cmp(T s1, T s2)
{
	assert(s1.len >= 0 && s1.str);
	assert(s2.len >= 0 && s2.str);

	if(s1.str == s2.str)
		return s1.len - s2.len;
	else if(s1.len < s2.len)
	{
		int cond = memcmp(s1.str,s2.str, s1.len);
		return cond == 0 ? -1: cond;
	}
	else if(s1.len > s2.len)
	{
		int cond = memcmp(s1.str,s2.str, s2.len);
		return cond == 0 ? +1 : cond;
	}
	else
	{
		return memcmp(s1.str, s2.str, s1.len);
	}
}

Text_save_T Text_save(void)
{
	Text_save_T save;
	NEW(save);

	save->current = current;
	save->avail   = current->avail;

	alloc(1);

	return save;
}

void Text_restore(Text_save_T* save)
{
	struct chunk *p, *q;

	assert(save && &save);
	current = (*save)->current;
	current->avail = (*save)->avail;

	FREE(*save);
	for(p = current->link; p; p = q)
	{
		q= q->link;
		FREE(p);
	}

	current->link = NULL;
}

int Text_chr(T s, int i, int j, int c)
{
	assert(s.len >= 0 && s.str);
	i = idx(i, s.len);
	j = idx(j, s.len);

	if(i > j){int t = i; i = j; j = t;}
	assert(i >= 0 && j <= s.len);

	for(; i < j; i++)
	{
		if(s.str[i] == c)
			return i + 1;
	}

	return 0;
}

int Text_rchr(T s, int i, int j, int c)
{
   	assert(s.len >= 0 && s.str);
	i = idx(i, s.len);
	j = idx(j, s.len);

	if(i > j){int t = i; i = j; j = t;}
	assert(i >= 0 && j <= s.len);

	while(j >  i)
	{
		if(s.str[--j] == c)
		{
			return j + 1;
		}
	}

	return 0;
}

int Text_upto(T s, int i, int j, T set)
{
	assert(set.len >= 0 && set.str);
    assert(s.len >= 0 && s.str);
	i = idx(i, s.len);
	j = idx(j, s.len);

	if(i > j){int t = i; i = j; j = t;}
	assert(i >= 0 && j <= s.len);

	for(; i < j; i++)
	{
		if(memchr(set.str, s.str[i],set.len))
			return i + 1;
	}

	return 0;
}

int Text_rupto(T s, int i, int j, T set)
{
	assert(set.len >= 0 && set.str);
	assert(s.len >= 0 && s.str);
	i = idx(i, s.len);
	j = idx(j, s.len);

	if(i > j){int t = i; i = j; j = t;}
	assert(i >= 0 && j <= s.len);

	while(j > i)
	{
		if(memchr(set.str, s.str[--j], set.len))
			return j + 1;
	}

	return 0;
}



int Text_find(T s, int i, int j, T str)
{
	assert(str.len >= 0 && str.str);

	assert(s.len >= 0 && s.str);
	i = idx(i, s.len);
	j = idx(j, s.len);

	if(i > j){int t = i; i = j; j = t;}
	assert(i >= 0 && j <= s.len);

	if(str.len == 0)
		return i+ 1;
	else if(str.len == 1)
	{	
		for(; i < j; i++)
			if(s.str[i] == *str.str)
				return i + 1;
	}
	else
	{
		for(; i + str.len <= j; i++)
		{
			if(equal(s, i, str))
			{
				return i+ 1;
			}
		}
	}

	return 0;
			
}

int Text_rfind(T s, int i, int j, T str)
{
	assert(str.len >= 0 && str.str);
	assert(s.len >= 0 && s.str);
	i = idx(i, s.len);
	j = idx(j, s.len);

	if(i > j){int t = i; i = j; j = t;}
	assert(i >= 0 && j <= s.len);

	if(str.len == 0)
	{
		return j + 1;
	}
	else if(str.len == 1)
	{
		while(j > i)
		{
			if(s.str[--j] == *str.str)
				return j + 1;
		}
	}
	else
	{
		for(; j - str.len >= i; j--)
		{
			if(equal(s, j - str.len,str))
				return j - str.len + 1;
		}
	}

	return 0;
}

int Text_any(T s, int i, T set)
{
	assert(s.len >= 0 && s.str);
	assert(set.len >= 0 && set.str);

	i = idx(i, s.len);
	assert(i >= 0 && i <= s.len);

	if(i < s.len && memchr(set.str, s.str[i],set.len))
		return i + 1;
	return 0;
}

int Text_many(T s, int i, int j, T set)
{
	assert(set.len >= 0 && set.str);
	assert(s.len >= 0 && s.str);
	i = idx(i, s.len);
	j = idx(j, s.len);

	if(i > j){int t = i; i = j; j = t;}
	assert(i >= 0 && j <= s.len);

	if(i < j && memchr(set.str,s.str[i],set.len))
	{
		do
		{
			i++;
		}while(i<j &&memchr(set.str, s.str[i],set.len));

		return i+ 1;
	}

	return 0;
}

int Text_rmany(T s, int i, int j, T set)
{
	assert(set.len >= 0 && set.str);
	assert(s.len >= 0 && s.str);
	i = idx(i, s.len);
	j = idx(j, s.len);

	if(i > j){int t = i; i = j; j = t;}
	assert(i >= 0 && j <= s.len);

	if(j > i && memchr(set.str, s.str[j - 1], set.len))
	{
		do{
			--j;

		}while(j >= i && memchr(set.str, s.str[j],set.len));

		return j + 2;
	}

	return 0;
}

int Text_match(T s, int i, int j, T str)
{
	assert(str.len >= 0 && str.str);
	assert(s.len >= 0 && s.str);
	i = idx(i, s.len);
	j = idx(j, s.len);

	if(i > j){int t = i; i = j; j = t;}
	assert(i >= 0 && j <= s.len);

	if(str.len == 0)
		return i + 1;
	else if(str.len == 1)
	{
		if(i < j && s.str[i] == *str.str)
			return j + 2;
	}
	else if(i + str.len <= j && equal(s, i, str))
	{
		return i + str.len + 1;
	}

	return 0;

}

int Text_rmatch(T s, int i, int j, T str)
{
	assert(str.len >= 0 &&str.str);
	assert(s.len >= 0 && s.str);
	i = idx(i, s.len);
	j = idx(j, s.len);

	if(i > j){int t = i; i = j; j = t;}
	assert(i >= 0 && j <= s.len);

	if(str.len == 0)
		return j + 1;
	else if(str.len == 1)
	{
		if(j > i && s.str[j - 1] == *str.str)
			return j;
	}
	else if(j - str.len >= i && equal(s, j - str.len,str))
	{
		return j - str.len + 1;

	}

	return 0;
}

void Text_fmt(int code, va_list *app, int put(int c, void* cl), void* cl, unsigned char flags[], int width, int precision)
{
	T *s;

	assert(app && flags);
	s = va_arg(*app, T*);
	assert(s && s->len >= 0&&s->str);
	Fmt_puts(s->str, s->len, put, cl, flags, width, precision);
}

