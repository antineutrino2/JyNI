/* This File is based on unicodectype.c from CPython 2.7.13.
 * It has been modified to suit JyNI needs.
 * Note that this file was generated by JyNIgate and its source is hosted in the
 * JyNIgate project. Modifying this generated file is not recommended.
 *
 *
 * Copyright of JyNI:
 * Copyright (c) 2013, 2014, 2015, 2016, 2017 Stefan Richthofer.
 * All rights reserved.
 *
 *
 * Copyright of Python and Jython:
 * Copyright (c) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008,
 * 2009, 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017
 * Python Software Foundation.
 * All rights reserved.
 *
 *
 * This file is part of JyNI.
 *
 * JyNI is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * JyNI is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with JyNI.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
   Unicode character type helpers.

   Written by Marc-Andre Lemburg (mal@lemburg.com).
   Modified for Python 2.0 by Fredrik Lundh (fredrik@pythonware.com)

   Copyright (c) Corporation for National Research Initiatives.

*/

#include "Python_JyNI.h"
#include "unicodeobject_JyNI.h"

#define ALPHA_MASK 0x01
#define DECIMAL_MASK 0x02
#define DIGIT_MASK 0x04
#define LOWER_MASK 0x08
#define LINEBREAK_MASK 0x10
#define SPACE_MASK 0x20
#define TITLE_MASK 0x40
#define UPPER_MASK 0x80
#define NODELTA_MASK 0x100
#define NUMERIC_MASK 0x200

typedef struct {
    const Py_UNICODE upper;
    const Py_UNICODE lower;
    const Py_UNICODE title;
    const unsigned char decimal;
    const unsigned char digit;
    const unsigned short flags;
} _PyUnicode_TypeRecord;

#include "unicodetype_db.h"

static const _PyUnicode_TypeRecord *
gettyperecord(Py_UNICODE code)
{
    int index;

#ifdef Py_UNICODE_WIDE
    if (code >= 0x110000)
        index = 0;
    else
#endif
    {
        index = index1[(code>>SHIFT)];
        index = index2[(index<<SHIFT)+(code&((1<<SHIFT)-1))];
    }

    return &_PyUnicode_TypeRecords[index];
}

/* Returns the titlecase Unicode characters corresponding to ch or just
   ch if no titlecase mapping is known. */

Py_UNICODE _PyUnicode_ToTitlecase(register Py_UNICODE ch)
{
    const _PyUnicode_TypeRecord *ctype = gettyperecord(ch);
    int delta = ctype->title;

    if (ctype->flags & NODELTA_MASK)
	return delta;

    if (delta >= 32768)
	    delta -= 65536;

    return ch + delta;
}

/* Returns 1 for Unicode characters having the category 'Lt', 0
   otherwise. */

int _PyUnicode_IsTitlecase(Py_UNICODE ch)
{
    const _PyUnicode_TypeRecord *ctype = gettyperecord(ch);

    return (ctype->flags & TITLE_MASK) != 0;
}

/* Returns the integer decimal (0-9) for Unicode characters having
   this property, -1 otherwise. */

int _PyUnicode_ToDecimalDigit(Py_UNICODE ch)
{
    const _PyUnicode_TypeRecord *ctype = gettyperecord(ch);

    return (ctype->flags & DECIMAL_MASK) ? ctype->decimal : -1;
}

int _PyUnicode_IsDecimalDigit(Py_UNICODE ch)
{
    if (_PyUnicode_ToDecimalDigit(ch) < 0)
	return 0;
    return 1;
}

/* Returns the integer digit (0-9) for Unicode characters having
   this property, -1 otherwise. */

int _PyUnicode_ToDigit(Py_UNICODE ch)
{
    const _PyUnicode_TypeRecord *ctype = gettyperecord(ch);

    return (ctype->flags & DIGIT_MASK) ? ctype->digit : -1;
}

int _PyUnicode_IsDigit(Py_UNICODE ch)
{
    if (_PyUnicode_ToDigit(ch) < 0)
	return 0;
    return 1;
}

/* Returns the numeric value as double for Unicode characters having
   this property, -1.0 otherwise. */

int _PyUnicode_IsNumeric(Py_UNICODE ch)
{
    const _PyUnicode_TypeRecord *ctype = gettyperecord(ch);

    return (ctype->flags & NUMERIC_MASK) != 0;
}

#ifndef WANT_WCTYPE_FUNCTIONS

/* Returns 1 for Unicode characters having the category 'Ll', 0
   otherwise. */

int _PyUnicode_IsLowercase(Py_UNICODE ch)
{
    const _PyUnicode_TypeRecord *ctype = gettyperecord(ch);

    return (ctype->flags & LOWER_MASK) != 0;
}

/* Returns 1 for Unicode characters having the category 'Lu', 0
   otherwise. */

int _PyUnicode_IsUppercase(Py_UNICODE ch)
{
    const _PyUnicode_TypeRecord *ctype = gettyperecord(ch);

    return (ctype->flags & UPPER_MASK) != 0;
}

/* Returns the uppercase Unicode characters corresponding to ch or just
   ch if no uppercase mapping is known. */

Py_UNICODE _PyUnicode_ToUppercase(Py_UNICODE ch)
{
    const _PyUnicode_TypeRecord *ctype = gettyperecord(ch);
    int delta = ctype->upper;
    if (ctype->flags & NODELTA_MASK)
	return delta;
    if (delta >= 32768)
	    delta -= 65536;
    return ch + delta;
}

/* Returns the lowercase Unicode characters corresponding to ch or just
   ch if no lowercase mapping is known. */

Py_UNICODE _PyUnicode_ToLowercase(Py_UNICODE ch)
{
    const _PyUnicode_TypeRecord *ctype = gettyperecord(ch);
    int delta = ctype->lower;
    if (ctype->flags & NODELTA_MASK)
	return delta;
    if (delta >= 32768)
	    delta -= 65536;
    return ch + delta;
}

/* Returns 1 for Unicode characters having the category 'Ll', 'Lu', 'Lt',
   'Lo' or 'Lm',  0 otherwise. */

int _PyUnicode_IsAlpha(Py_UNICODE ch)
{
    const _PyUnicode_TypeRecord *ctype = gettyperecord(ch);

    return (ctype->flags & ALPHA_MASK) != 0;
}

#else

/* Export the interfaces using the wchar_t type for portability
   reasons:  */

int _PyUnicode_IsLowercase(Py_UNICODE ch)
{
    return iswlower(ch);
}

int _PyUnicode_IsUppercase(Py_UNICODE ch)
{
    return iswupper(ch);
}

Py_UNICODE _PyUnicode_ToLowercase(Py_UNICODE ch)
{
    return towlower(ch);
}

Py_UNICODE _PyUnicode_ToUppercase(Py_UNICODE ch)
{
    return towupper(ch);
}

int _PyUnicode_IsAlpha(Py_UNICODE ch)
{
    return iswalpha(ch);
}

#endif