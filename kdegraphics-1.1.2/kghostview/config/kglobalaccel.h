/* This file is part of the KDE libraries
	Copyright (C) 1998	Mark Donohoe <donohoe@kde.org>
						Jani Jaakkola <jjaakkol@cs.helsinki.fi>

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

#ifndef _KGLOBALACCEL_H_
#define _KGLOBALACCEL_H_

#include <kapp.h>
#include <qobject.h>
#include "kaccel.h"

/** 
 * Returns the X key modifier for the key code keyCode.
 */	
uint keyToXMod( uint keyCode );

/** 
 * Returns the X key sym for the key code keyCode.
 */	
uint keyToXSym( uint keyCode );

/** 
 * The KGlobalAccel class handles global keyboard accelerators, allowing a
 * user to configure key bindings through application configuration files or
 * through the KKeyChooser GUI.
 *
 * A KGlobalAccel contains a list of accelerator items. Each accelerator item
 * consists of an action name and a keyboard code combined with modifiers
 * (SHIFT, CTRL and ALT.)
 *
 * For example, "CTRL+SHIFT+M" could be a shortcut for popping-up a menu of
 * monitor setting choices anywhere on the desktop. The key codes are listed
 * in kckey.h. "Monitor settings" could be the action name for this
 * accelerator. The action name indentifies the key binding in configuration
 * files and the KKeyChooser GUI.
 *
 * When pressed,an accelerator key calls the slot to which it has been
 * connected. Accelerator items can be connected so that a key will activate
 * two different slots. 
 *
 * KApplication::x11EventFilter must be re-implemented to call
 * KAccel::x11EventFilter so that a KAccel object can handle all key events.
 *
 * Key binding configuration during run time can be prevented by specifying
 * that an accelerator item is not configurable when it is inserted.
 *
 * It is possible for a user to choose to have no key associated with an action.
 *
 * MyApp::x11EventFilter( XEvent *ev ) {
 * if ( myObject->ga->x11EventFilter( ev ) ) 
 *		return true;
 * }
 *
 * ...
 *
 * ga = new KGlobalAccel();
 * ga->insertItem( i18n("Monitor settings"), "CTRL+SHIFT+M" );
 * ga->connectItem( i18n("Monitor settings"), myObject, SLOT( popupMenu() ) );
 *
 * ga->readSettings();
 *
 */
class KGlobalAccel : public QObject
{
	Q_OBJECT
	
 public:
	/** 
	 * Creates a KGlobalAccel object. 
	 */
	KGlobalAccel( );
			
	/** 
	 * Destroys the accelerator object.and ungrabs any allocated key bindings.
	 */
	~KGlobalAccel();
	
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
	 * Attempts to make a passive X server grab of the key specified by key symbol
	 * keysym and modifier mod. Returns false if unsuccessful.
	 *
	 * Modifications with num lock and caps lock are also grabbed.
	 *
	 */
	bool grabKey(uint keysym, uint mod);
	
	/** 
	 * Inserts an accelerator item and returns false if the key code 
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
	 * Inserts an accelerator item and returns false if the key code 
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
	 * Ungrabs the key specified by key symbol
	 * keysym and modifier mod. Returns false if unsuccessful.
	 *
	 * Modifications with num lock and caps lock are also ungrabbed.
	 *
	 */
	bool ungrabKey(uint keysym, uint mod);

	/** 
	 * Writes the current configurable associations to the application's
	 * configuration files
	 */	
	void writeSettings();
	
	/**
	 * Filters X11 events ev for key bindings in the accelerator dictionary.
	 * If a match is found the activated activated is emitted and the function
	 * returns true. Return false if the event is not processed.
	 */ 
	bool x11EventFilter(const XEvent *);
	
signals:
	void activated();	

protected:
	int aAvailableId;
	QDict<KKeyEntry> aKeyDict;
	bool bEnabled;
	bool bGlobal;
	QString aGroup;

 protected:
};

#endif _KGLOBALACCEL_H_
