/* This file is part of the KDE libraries
    Copyright (C) 1997	Mark Donohoe <donohoe@kde.org>
						Nicolas Hadacek <hadacek@via.ecp.fr>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
    Boston, MA 02111-1307, USA.
*/

#ifndef _KACCEL_H
#define _KACCEL_H

#include <qdict.h>
#include <qaccel.h>

#include <kconfig.h>

#include "kckey.h"

/**
 * Returns the key code corresponding to the string sKey or zero if the string
 * is not recognized. The string must be something like "SHIFT+A",
 * "F1+CTRL+ALT" or "Backspace" for example. That is, a key plus a combination
 * of SHIFT, CTRL and ALT.
 */	
uint stringToKey( const char * sKey );

/** 
 * Returns a string corresponding to the key code keyCode, which is empty if
 * keyCode is not recognized or zero.
 */
const QString keyToString( uint keyCode );

struct KKeyEntry {
	uint aCurrentKeyCode, aDefaultKeyCode, aConfigKeyCode;
	bool bConfigurable;
	bool bEnabled;
	int aAccelId;
	const QObject *receiver;
	QString *member;
};

/** 
 * The KAccel class handles keyboard accelerators, allowing a user to configure
 * key bindings through application configuration files or through the
 * KKeyChooser GUI.
 *
 * A KAccel contains a list of accelerator items. Each accelerator item
 * consists of an action name and a keyboard code combined with modifiers
 * (SHIFT, CTRL and ALT.)
 *
 * For example, "CTRL+P" could be a shortcut for printing a document. The key
 * codes are listed in kckey.h. "Print" could be the action name for printing.
 * The action name indentifies the key binding in configuration files and the
 * KKeyChooser GUI.
 *
 * When pressed, an accelerator key calls the slot to which it has been
 * connected. Accelerator items can be connected so that a key will activate
 * two different slots.
 *
 * A KAccel object handles key events to its parent widget and all children
 * of this parent widget.
 *
 * Key binding configuration during run time can be prevented by specifying
 * that an accelerator item is not configurable when it is inserted. A special
 * group of non-configurable key bindings are known as the standard accelerators.
 *
 * The standard accelerators appear repeatedly in applications for
 * standard document actions like printing and saving. Convenience methods are
 * available to insert and connect these accelerators which are configurable on
 * a desktop-wide basis.
 *
 * It is possible for a user to choose to have no key associated with an action.
 *
 * KAccel *a = new KAccel( myWindow );
 * a->insertItem( i18n("Scroll up"), "Up" );
 * a->connectItem( i18n("Scroll up"), myWindow, SLOT( srollUp() ) );
 * a->insertStdItem( KAccel::Print );
 * a->connectItem( a->stdAction( KAccel::Print ), myWindow, SLOT( printDoc() ) );
 * 
 * a->readSettings();
 *
 */
class KAccel 
{ 
 public:
 	enum StdAccel { Open=1, New, Close, Save, Print, Quit, Cut, Copy,
		Paste, Undo, Find, Replace, Insert, Home, End, Prior, Next, Help };
	/** 
	 * Creates a KAccel object with a parent widget and a name.
	 */
	KAccel( QWidget * parent, const char * name = 0 );
			
	/** 
	 * Destroys the accelerator object. 
	 */
	~KAccel();
	
	/**
	 * Removes all accelerator items.
	 */
	void clear();
	
	/** 
	 * Connect an accelerator item to a slot/signal in another object.
	 *
	 * Arguments:
	 *
	 *	\begin{itemize}
	 *  \item action is the accelerator item action name.
	 *  \item receiver is the object to receive a signal
	 *  \item member is a slot or signal in the receiver
	 *  \item activate indicates whether the accelrator item should be
	 *  enabled immediately
	 * 	\end{itemize}
	 */
	void connectItem( const char * action,
						  const QObject* receiver, const char* member,
						  bool activate = TRUE );

	/** 
	* Returns the number of accelerator items.
	*/					  
	uint count() const;
	
	/** 
	* Returns the key code of the accelerator item with the action name
	* action, or zero if either the action name cannot be found or the current
	* key is set to no key.
	*/
	uint currentKey( const char * action );

	/** 
	* Returns the default key code of the accelerator item with the action name
	* action, or zero if the action name cannot be found.
	*/
	uint defaultKey( const char * action);
	
	/** 
	 * Disconnects an accelerator item from a function in another object.
	 */
	void disconnectItem( const char * action,
							const QObject* receiver, const char* member );
	
	/** 
	 * Returns that identifier of the accelerator item with the keycode key,
	 * or zero if the item cannot be found.
	 */
	const char *findKey( int key ) const;
	
	/** 
	 * Inserts an accelerator item and returns -1 if the key code 
	 * 	defaultKeyCode is not valid.
	 *	
	 * Arguments:
	 *
	 *	\begin{itemize}
	 *  \item action is the accelerator item action name.
	 *  \item defaultKeyCode is a key code to be used as the default for the action.
	 *  \item configurable indicates whether a user can configure the key
	 *	binding using the KKeyChooser GUI and whether the key will be written
	 *	back to configuration files on calling writeSettings.
	 * 	\end{itemize} 	 
	 *
	 * If an action already exists the old association and connections will be
	 * removed..
	 * 	 
	 */
	bool insertItem( const char * action, uint defaultKeyCode,
				 bool configurable = TRUE );
	
	 /** 
	 * Inserts an accelerator item and returns -1 if the key code 
	 * 	defaultKeyCode is not valid.
	 *	
	 * Arguments:
	 *
	 *	\begin{itemize}
	 *  \item action is the accelerator item action name.
	 *  \item defaultKeyCode is a key plus a combination of SHIFT, CTRL
	 *	and ALT to be used as the default for the action.
	 *  \item configurable indicates whether a user can configure the key
	 *	binding using the KKeyChooser GUI and whether the key will be written
	 *	back to configuration files on calling writeSettings.
	 * 	\end{itemize} 	 
	 *
	 * If an action already exists the old association and connections will be
	 * removed..
	 * 	 
	 */
	bool insertItem( const char * action, const char * defaultKeyCode,
				 bool configurable = TRUE );
				 
	/** 
	 *	Inserts a standard accelerator item if id equal to Open, New,
	 *	Close, Save, Print, Quit, Cut, Copy, Paste, Undo, Find, Replace,
	 *	Insert, Home, End, Prior, Next, or Help.
	 *
	 * If an action already exists the old association and connections will be
	 * removed..
	 */
	const char *insertStdItem( StdAccel id );
				 
	bool isEnabled();
	bool isItemEnabled( const char *action );
				 
	/** 
	* Returns the dictionary of accelerator action names and KKeyEntry
	* objects. Note that only a shallow copy is returned so that items will be
	* lost when the KKeyEntry objects are deleted.
	*/	
	QDict<KKeyEntry> keyDict();
				 
	/** 
	 * Reads all key associations from the application's configuration files.
	 */	
	void readSettings();
		
 	/** 
	 * Removes the accelerator item with the action name action.
	 */
    void removeItem( const char * action );  
	
	void setConfigGroup( const char *group );
	void setConfigGlobal( bool global );
	
	const char * configGroup();
	bool configGlobal();
	
	/** 
	 * Enables the accelerator if activate is TRUE, or disables it if
	 * activate is FALSE..
	 *
	 * Individual keys can also be enabled or disabled.
	 */
	void setEnabled( bool activate );
	
	/** 
	 * Enables or disables an accelerator item.
	 *
	 * Arguments:
	 *
	 *	\begin{itemize}
	 *  \item action is the accelerator item action name.
	 *	\item activate specifies whether the item should be enabled or
	 *	disabled.
	 * 	\end{itemize} 
	 */
	void setItemEnabled( const char * action, bool activate );
	
	/** 
	* Sets the dictionary of accelerator action names and KKeyEntry
	* objects to nKeyDict.. Note that only a shallow copy is made so that items will be
	* lost when the KKeyEntry objects are deleted.
	*/	
	bool setKeyDict( QDict<KKeyEntry> nKeyDict );
	
	/** 
	 *	Returns a standard action name if id equal to Open, New,
	 *	Close, Save, Print, Quit, Cut, Copy, Paste, Undo, Find, Replace,
	 *	Insert, Home, End, Prior, Next, or Help and zero otherwise.
	 */
	const char *stdAction( StdAccel id );

	/** 
	 * Writes the current configurable associations to the application's
	 * configuration files
	 */	
	void writeSettings();
	 
protected:
 	QAccel *pAccel;
	int aAvailableId;
	QDict<KKeyEntry> aKeyDict;
	bool bEnabled;
	bool bGlobal;
	QString aGroup;
	
 
};
	
#endif
