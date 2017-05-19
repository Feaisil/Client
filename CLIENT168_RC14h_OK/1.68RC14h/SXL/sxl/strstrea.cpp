#include <climits>
#include <cstdlib>
#include <cstring>
#include <strstream>
 #pragma warning(disable:4244 4097)
_STD_BEGIN

_CRTIMP2 istrstream::~istrstream()
	{	// destruct an istrstream
	}

_CRTIMP2 ostrstream::ostrstream(char *s, streamsize n,
	ios_base::openmode mode)
	: ostream(&_Sb),
	_Sb(s, n, s == 0 || (mode & app) == 0 ? s : s + strlen(s))
	{	// write at terminating null (if there)
	}

_CRTIMP2 ostrstream::~ostrstream()
	{	// destruct an ostrstream
	}

_CRTIMP2 strstream::strstream(char *s, streamsize n,
	ios_base::openmode mode)
	: iostream(&_Sb),
	_Sb(s, n, s == 0 || (mode & app) == 0 ? s : s + strlen(s))
	{	// write at terminating null (if there)
	}

_CRTIMP2 strstream::~strstream()
	{	// destruct a strstream
	}

_CRTIMP2 strstreambuf::~strstreambuf()
	{	// destruct a strstreambuf
	_Tidy();
	}

_CRTIMP2 void strstreambuf::freeze(bool freezeit)
	{	// freeze a dynamic string
	if (freezeit && !(_Strmode & _Frozen))
		{	// disable writing
		_Strmode |= _Frozen;
		_Pendsave = epptr();
		setp(pbase(), pptr(), eback());
		}
	else if (!freezeit && _Strmode & _Frozen)
		{	// re-enable writing
		_Strmode &= ~_Frozen;
		setp(pbase(), pptr(), _Pendsave);
		}
	}

_CRTIMP2 int strstreambuf::overflow(int ch)
	{	// try to extend write area
	if (ch == EOF)
		return (0);
	else if (pptr() != 0 && pptr() < epptr())
		return ((unsigned char)(*_Pninc() = ch));
	else if (!(_Strmode & _Dynamic)
		|| _Strmode & (_Constant | _Frozen))
		return (EOF);
	else
		{	// okay to extend
		int osize = gptr() == 0 ? 0 : epptr() - eback();
		int nsize = osize;
		int inc = nsize / 2 < _MINSIZE
			? _MINSIZE : nsize / 2;
		char *p = 0;
		while (0 < inc && INT_MAX - inc < nsize)
			inc /= 2;
		if (0 < inc)
			{	// room to grow
			nsize += inc;
			p = _Palloc != 0 ? (char *)(*_Palloc)(nsize)
				: new char[nsize];
			}
		if (p == 0)
			return (EOF);
		if (0 < osize)
			memcpy(p, eback(), osize);
		if (!(_Strmode & _Allocated))
			;
		else if (_Pfree != 0)
			(*_Pfree)(eback());
		else
			delete[] eback();
		_Strmode |= _Allocated;
		if (osize == 0)
			{	// setup new buffer
			_Seekhigh = p;
			setp(p, p + nsize);
			setg(p, p, p);
			}
		else
			{	// revise old pointers
			_Seekhigh = _Seekhigh - eback() + p;
			setp(pbase() - eback() + p, pptr() - eback() + p,
				p + nsize);
			setg(p, gptr() - eback() + p, pptr() + 1);
			}
		return ((unsigned char)(*_Pninc() = ch));
		}
	}

_CRTIMP2 int strstreambuf::pbackfail(int ch)
	{	// try to putback a character
	if (gptr() == 0 || gptr() <= eback()
		|| ch != EOF
			&& (unsigned char)ch != (unsigned char)gptr()[-1]
			&& _Strmode & _Constant)
		return (EOF);
	else
		{	// safe to back up
		gbump(-1);
		return (ch == EOF ? 0 : (unsigned char)(*gptr() = ch));
		}
	}

_CRTIMP2 int strstreambuf::underflow()
	{	// read only if read position available
	if (gptr() == 0)
		return (EOF);
	else if (gptr() < egptr())
		return ((unsigned char)*gptr());
	else if (pptr() == 0
		|| pptr() <= gptr() && _Seekhigh <= gptr())
		return (EOF);
	else
		{	// update _Seekhigh and expand read region
		if (_Seekhigh < pptr())
			_Seekhigh = pptr();
		setg(eback(), gptr(), _Seekhigh);
		return ((unsigned char)*gptr());
		}
	}

_CRTIMP2 streampos strstreambuf::seekoff(streamoff off,
	ios_base::seekdir way, ios_base::openmode which)
	{	// seek by specified offset
	if (pptr() != 0 && _Seekhigh < pptr())
		_Seekhigh = pptr();
	if (which & ios_base::in && gptr() != 0)
		{	// set input (and maybe output) pointer
		if (way == ios_base::end)
			off += _Seekhigh - eback();
		else if (way == ios_base::cur
			&& !(which & ios_base::out))
			off += gptr() - eback();
		else if (way != ios_base::beg || off == _BADOFF)
			off = _BADOFF;
		if (0 <= off && off <= _Seekhigh - eback())
			{	// set one or two pointers
			gbump(eback() - gptr() + off);
			if (which & ios_base::out && pptr() != 0)
				setp(pbase(), gptr(), epptr());
			}
		else
			off = _BADOFF;
		}
	else if (which & ios_base::out && pptr() != 0)
		{	// set only output pointer
		if (way == ios_base::end)
			off += _Seekhigh - eback();
		else if (way == ios_base::cur)
			off += pptr() - eback();
		else if (way != ios_base::beg || off == _BADOFF)
			off = _BADOFF;
		if (0 <= off && off <= _Seekhigh - eback())
			pbump(eback() - pptr() + off);
		else
			off = _BADOFF;
		}
	else	// nothing to set
		off = _BADOFF;
	return (streampos(off));
	}

_CRTIMP2 streampos strstreambuf::seekpos(streampos sp,
		ios_base::openmode which)
	{	// seek to memorized position
	streamoff off = (streamoff)sp;
	if (pptr() != 0 && _Seekhigh < pptr())
		_Seekhigh = pptr();
	if (off == _BADOFF)
		;
	else if (which & ios_base::in && gptr() != 0)
		{	// set input (and maybe output) pointer
		if (0 <= off && off <= _Seekhigh - eback())
			{	// set valid offset
			gbump(eback() - gptr() + off);
			if (which & ios_base::out && pptr() != 0)
				setp(pbase(), gptr(), epptr());
			}
		else
			off = _BADOFF;
		}
	else if (which & ios_base::out && pptr() != 0)
		{	// set output pointer
		if (0 <= off && off <= _Seekhigh - eback())
			pbump(eback() - pptr() + off);
		else
			off = _BADOFF;
		}
	else	// nothing to set
		off = _BADOFF;
	return (streampos(off));
	}

_CRTIMP2 void strstreambuf::_Init(int n, char *gp, char *pp,
	_Strstate mode)
	{	// initialize with possibly static buffer
	streambuf::_Init();
	_Pendsave = 0;
	_Seekhigh = 0;
	_Palloc = 0;
	_Pfree = 0;
	_Strmode = mode;
	if (gp == 0)
		_Strmode |= _Dynamic;	// make dynamic
	else
		{	// make static
		int size = n < 0 ? INT_MAX : n == 0 ? strlen(gp) : n;
		_Seekhigh = gp + size;
		if (pp == 0)
			setg(gp, gp, gp + size);
		else
			{	// make writable too
			if (pp < gp)
				pp = gp;
			else if (gp + size < pp)
				pp = gp + size;
			setp(pp, gp + size);
			setg(gp, gp, pp);
			}
		}
	}

_CRTIMP2 void strstreambuf::_Tidy()
	{	// discard any allocated storage
	if ((_Strmode & (_Allocated | _Frozen)) != _Allocated)
		;
	else if (_Pfree != 0)
		(*_Pfree)(eback());
	else
		delete[] eback();
	_Seekhigh = 0;
	_Strmode &= ~(_Allocated | _Frozen);
	}
_STD_END

/*
 * Copyright (c) 1994-1999 by P.J. Plauger.  ALL RIGHTS RESERVED. 
 * Consult your license regarding permissions and restrictions.
 V2.33:099I */
