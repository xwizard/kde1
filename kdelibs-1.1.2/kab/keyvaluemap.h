/* -*- C++ -*-
 * The class KeyValueMap is used for managing key-value-pairs
 * WITHOUT any hierarchical structure.   Objects of it can be
 * used as they are or in conjunction with the  configuration
 * database class.
 *
 * Capabilities of the class are:
 * - storing of any key-value-pair that is storable in 
 *   std::string values,
 * - key-value-pairs are saved in human-readable text files
 *   when saving to disk,
 * - the values may contain newline and tabulator characters
 *   which will still be there after saving and rereading,
 * - supports the following datatypes:
 *   - std::strings (of course),
 *   - integers,
 *   - floating point values and
 *   - boolean states
 * - supports storing and retrieving lists of values of the 
 *   following datatypes:
 *   - std::strings,
 *   - integers and
 *   - floating point values
 *   (bools possibly supported in future)
 * - easy syntax of files, in general it is supposed to be a 
 *   kind of guarantee  ( you know that free software  never 
 *   guarantess anything, don't you?)  that every value that 
 *   has been  stored  by one of the member functions of the 
 *   class like 
 *      insert(const std::string& key, [value&]);
 *   can also be retrieved using 
 *      get(const std::string& key, [value&]);
 *   without being modified.
 *   (Please report anything that does not do so!)
 *
 * the Configuration Database library
 * copyright:  (C) Mirko Sucker, 1998
 * license:    GNU Public License, Version 2
 * mail to:    Mirko Sucker <mirko.sucker@hamburg.netsurf.de>
 *                          <mirko.sucker@unibw-hamburg.de>
 * requires:   C++-compiler, STL, std::string class
 *             Nana (only for debugging)
 * $Revision: 1.5 $
 */
#ifndef KEYVALUEMAP_H
#define KEYVALUEMAP_H

#pragma interface

#include "stl_headers.h"
#include <fstream>
#include <string>

using namespace std;

// forward declaration needed to avoid duplicate declaration 
// of global specifiers "red" and "black" in
// * map.h and
// * qcolor.h (Qt-library)

class StringStringMap;

// ########################################################

class KeyValueMap {
protected:
  StringStringMap* data;
  // helper for file handling:
  // bool isComment(const std::string&);
  // WORK_TO_DO: this is alpha, remove comment after testing
  /// returns true if a "complex std::string" was found
  bool parseComplexString(const std::string& orig, 
			  std::string::size_type index,
			  std::string& result,
			  int& noOfChars) const;
  /// codes a normal std::string into a complex std::string:
  std::string makeComplexString(const std::string& orig);
  /** Inserts a std::string (it must be an already coded one)
    * without coding it.
    */
  bool insertRaw(const std::string& key, 
		 const std::string& value, 
		 bool force=false);
  /** Retrieves the undecoded value of the given key.
    */
  bool getRaw(const std::string& key, std::string& value) const;
  // -------------------------
public:
  KeyValueMap();
  KeyValueMap(const KeyValueMap&); // copy constructor
  virtual ~KeyValueMap();
  /// returns true if object is OK 
  bool invariant();
  /// returns the number of key-value-pairs in the map
  unsigned int size() const; 
  /// deletes all entries
  void clear(); 
  /** Fills the database from the file. If the parameter 
    * force is true, it overrides keys that are already declared in
    * the database and are declared again in the file.
    * params: ° filename 
    *         ° wether to override existing keys or not
    *         ° wether values may be empty
    */
  bool fill(const std::string&, bool force=false, bool relax=false);
  /** Saves the database to a file. Only overrides existing 
    * files if force is true.
    * params: filename and wether to override existing files or not
    */
  bool save(const std::string&, bool force=false);
  /** Saves contents to an already open stream,
    * placing "count" spaces before each line. This method is 
    * called to save fierarchical databases.
    */
  bool save(std::ofstream& file, int count);
  /* The following pairs of get(..) and insert(..) member functions
   * can be used to store single objects and lists of the 
   * respective data types.
   * The std::string-insert- and -get-methods are somewhat basic since
   * they are used by all other insert functions, the others 
   * create a std::string from the respective data and insert this 
   * std::string.
   */
  // params of get: key, reference to value storage
  // params of insert: key, value and wether  to 
  // override existing keys or not
  // std::string values:
  bool get(const std::string&, std::string&) const;
  bool insert(const std::string&, const std::string&, 
	      bool force=false);
  // dummy function to explicitly catch char* as std::strings
  // (pgcc treats them as bool objects!)
  inline bool insert(const std::string& key, const char* value,
		     bool force=false);
  // additional insert method for lines
  // params: "<key>=<value>",
  // wether  to override existing keys or not and
  // wether values my be empty std::strings or not and
  // wether to code the value or not (INTERNAL)
  bool insertLine(std::string, 
		  bool force=false, 
		  bool relax=false, 
		  bool encode=true);
  // ---------------
  // integer values:
  bool get(const std::string&, int&) const;
  bool insert(const std::string&, const int&, bool force=false);
  // ---------------
  // double values:
  bool get(const std::string&, double&) const;
  bool insert(const std::string&, const double&, bool force=false);
  // ---------------
  // boolean values:
  bool get(const std::string&, bool&) const;
  bool insert(const std::string&, const bool&, bool force=false);
  // ---------------
  // the following methods try to parten the values into lists of values
  // std::string lists:
  bool get(const std::string&, list<std::string>&) const;
  bool insert(const std::string&, const list<std::string>&, bool force=false);
  // --------------
  // integer lists:
  bool get(const std::string&, list<int>&) const;
  bool insert(const std::string&, const list<int>&, bool force=false);
  // --------------
  // double lists:
  bool get(const std::string&, list<double>&) const;
  bool insert(const std::string&, const list<double>&, bool force=false);
  // --------------
  // end of corresponding get-insert-pairs
  // -------------------------
  /// Returns true if there are no keys declared in this map.
  bool empty();
  /** Erases all key-value-pairs in the map, 
    * the map is empty after it.
    */ 
  bool erase(const std::string& key);
};

// ----- inline functions:
bool KeyValueMap::insert
(const std::string& key, const char* value,
 bool force)
{ 
  std::string temp(value); 
  return insert(key, temp, force); 
}
// -----

#endif // KEYVALUEMAP_H
