#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include "kfmipc.h"

void write_int( int _fd, int _value )
{
    char buffer[10];
    sprintf( buffer, "%i ", _value );
next:
    if ( write( _fd, (const char*)buffer, strlen(buffer) ) < 0 )
      if ( errno == EINTR )
	goto next;
}

void write_double( int _fd, double _value )
{
    char buffer[10];
    sprintf( buffer, "%f ", _value );
next:
    if ( write( _fd, (const char*)buffer, strlen(buffer) ) < 0 )
      if ( errno == EINTR )
	goto next;
}

void write_char( int _fd, char _value )
{
next:
  if ( write( _fd, (const char*)&_value, sizeof(char) ) < 0 )
    if ( errno == EINTR )
      goto next;
}

void write_string( int _fd, const char* _value )
{
    if ( _value == 0L )
    {
	write_int( _fd, -1 );
	return;
    }
    
    int len = strlen( _value );
    write_int( _fd, len );
next:
    if ( write( _fd, (const char*)_value, strlen(_value) ) < 0 )
      if ( errno == EINTR )
	goto next;
}

void write_mem( int _fd, IPCMemory _mem )
{
    if ( _mem.data == 0L )
    {
	write_int( _fd, -1 );
	return;
    }
    
    write_int( _fd, _mem.size );
next:
    if ( write( _fd, _mem.data, _mem.size ) < 0 )
      if ( errno == EINTR )
	goto next;
}

void write_intList( int _fd, intList* _list )
{
    int len = _list->elements * sizeof(int);
next1:
    if ( write( _fd, (const char*)&(_list->elements), sizeof(int) ) )
      if ( errno == EINTR )
	goto next1;
next2:
    if ( write( _fd, (const char*)(_list->list), len ) )
      if ( errno == EINTR )
	goto next2;
}

void write_doubleList( int _fd, doubleList* _list )
{
    int len = _list->elements * sizeof(double);
next1:
    if ( write( _fd, (const char*)&(_list->elements), sizeof(int) ) < 0 )
      if ( errno == EINTR )
	goto next1;
next2:
    if ( write( _fd, (const char*)(_list->list), len ) < 0 )
      if ( errno == EINTR )
	goto next2;
}

void write_charList( int _fd, charList* _list )
{
    int len = _list->elements * sizeof(char);
next1:
    if ( write( _fd, (const char*)&(_list->elements), sizeof(int) ) < 0 )
      if ( errno == EINTR )
	goto next1;
next2:
    if ( write( _fd, (const char*)(_list->list), len ) < 0 )
      if ( errno == EINTR )
	goto next2;
}

void write_stringList( int _fd, stringList* _list )
{
    // int len = _list->elements * sizeof(int);
next:
  if ( write( _fd, (const char*)&(_list->elements), sizeof(int) ) < 0 )
      if ( errno == EINTR )
	goto next;

    for( int i = 0; i < _list->elements; i++ )
    {
	write_string( _fd, _list->list[i] );
    }
}

char* read_string( char *_data, int &_pos, int _len )
{
    int tmp = read_int( _data, _pos, _len );
    if ( tmp == -1 )
	return 0L;
    
    char *str = (char*)malloc(tmp + 1);
    strncpy( str, _data + _pos, tmp);
    _pos += tmp;
    str[tmp] = 0;
    return str;
}

IPCMemory read_mem( char *_data, int &_pos, int _len )
{
    int tmp = read_int( _data, _pos, _len );
    if ( tmp == -1 )
	return IPCMemory( 0L, 0 );
    
    // Add one byte for the trailing 0.
    // Perhaps someone transfers ASCII and
    // does not want to be bothered with the 0.
    char *str = (char*)malloc(tmp + 1);
    memcpy( str, _data + _pos, tmp );
    str[ tmp ] = 0;
    _pos += tmp;
    return IPCMemory( str, tmp );
}

int read_int( char *_data, int &_pos, int _len )
{
    int i = _pos;
    while ( _data[ _pos ] != ' ' )
    {
	_pos++;
	if ( _pos == _len )
	    return 0;
    }
    _pos++;
    
    return atoi( _data + i );
}

char read_char( char *_data, int &_pos, int )
{
    char tmp = *((char*)_data + _pos);
    _pos += sizeof(char);
    return tmp;
}

double read_double( char *_data, int &_pos, int _len )
{
    int i = _pos;
    while ( _data[ _pos ] != ' ' )
    {
	_pos++;
	if ( _pos == _len )
	    return 0;
    }
    _pos++;
    
    return atof( _data + i );
}

void read_stringList( char *_data, int &_pos, int _len, stringList *_list )
{
    int tmp = *((int*)_data + _pos);
    _list->elements = tmp;
    _pos += sizeof(int);
    _list->list = (char**)malloc( tmp * sizeof(char*) );
    for( int i = 0; i < tmp; i++ )
    {
	_list->list[i] = read_string( _data, _pos, _len );
    }
}

void read_intList( char *_data, int &_pos, int _len, intList *_list )
{
    int tmp = *((int*)_data + _pos);
    _list->elements = tmp;
    _pos += sizeof(int);
    _list->list = (int*)malloc( tmp * sizeof(int) );
    for( int i = 0; i < tmp; i++ )
    {
	_list->list[i] = read_int( _data, _pos, _len );
    }
}

void read_doubleList( char *_data, int &_pos, int _len, doubleList *_list )
{
    int tmp = *((int*)_data + _pos);
    _list->elements = tmp;
    _pos += sizeof(int);
    _list->list = (double*)malloc( tmp * sizeof(double) );
    for( int i = 0; i < tmp; i++ )
    {
	_list->list[i] = read_double( _data, _pos, _len );
    }
}

void read_charList( char *_data, int &_pos, int _len, charList *_list )
{
    int tmp = *((int*)_data + _pos);
    _list->elements = tmp;
    _pos += sizeof(int);
    _list->list = (char*)malloc( tmp * sizeof(char) );
    for( int i = 0; i < tmp; i++ )
    {
	_list->list[i] = read_char( _data, _pos, _len );
    }
}

void free_string( char *_str )
{
    if ( _str != 0L )
	free( _str );
}

void free_stringList( stringList *_list )
{
    for( int i = 0; i < _list->elements; i++ )
    {
	free ( _list->list[i] );
    }
    free ( _list->list );
}

void free_intList( intList *_list )
{
    free ( _list->list );
}

void free_doubleList( doubleList *_list )
{
    free ( _list->list );
}

void free_charList( charList *_list )
{
    free ( _list->list );
}

int len_int( int _value )
{
    char buffer[ 20 ];
    sprintf( buffer, "%i", _value );
    return strlen(buffer) + 1;
}

int len_double( double _value )
{
    char buffer[ 20 ];
    sprintf( buffer, "%f", _value );
    return strlen(buffer) + 1;
}

int len_char( char )
{
    return 1;
}

int len_string( const char *_str )
{
    if ( _str == 0L )
	// The '-1' takes 2 characters + 1 space
	return 3;
    int len = strlen( _str );
    return len + len_int( len );
}

int len_mem( IPCMemory _mem )
{
    if ( _mem.data == 0L )
	// The '-1' takes 2 characters + 1 space
	return 3;
    return _mem.size + len_int( _mem.size );
}

int len_stringList( stringList *_list )
{
    int len = sizeof(int);
    for( int i = 0; i < _list->elements; i++ )
    {
	len += len_string( _list->list[i] );
    }
    return len;
}

int len_intList( intList *_list )
{
    return ( sizeof(int) + _list->elements * sizeof(int) );
}

int len_doubleList( doubleList *_list )
{
    return ( sizeof(int) + _list->elements * sizeof(double) );
}

int len_charList( charList *_list )
{
    return ( sizeof(int) + _list->elements * sizeof(char) );
}
