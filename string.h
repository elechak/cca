/*
The blue programming language ("blue")
Copyright (C) 2007  Erik R Lechak

email: erik@lechak.info
web: www.lechak.info

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/
#ifndef _STRING_
#define _STRING_
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>

struct string_header{
    size_t length;
    char data[];
};

typedef struct string_header  *string_t;

string_t string_new(const char * cstring);
string_t string_new_ls(size_t length, const char * cstring);
string_t string_new_quoted(const char * cstring, char ** pcstring);
string_t string_new_formatted(const char * format, ...);
string_t string_new_add(string_t a, string_t b);
string_t string_new_merge(string_t a, string_t b, int keep_a, int keep_b);
string_t string_substr(const string_t s, size_t start, size_t end);
string_t string_dup(const string_t s);
void string_fprint(const string_t self ,FILE * stream);
size_t string_sizeof(const string_t self);
size_t string_length(const string_t self);

int string_compare(string_t a, string_t b);
int string_compare_cstring(string_t a, char * cstring);

size_t string_find(string_t big, string_t little);

size_t string_save( string_t self, char * filename);
string_t string_load( char * filename);

#endif

