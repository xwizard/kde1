/*
* gridbagl.h -- Declaration of class KBagLayout.
* Generated by newclass on Mon May  4 15:57:51 EST 1998.
*/
#ifndef SSK_GRIDBAGL_H
#define SSK_GRIDBAGL_H

#include<qwidget.h>
#include<qptrdict.h>
#include<bagconst.h>
#include<qlist.h>
#include<qsize.h>

class QFrame;

/**
* Similar to @ref QGridLayout but allows more refined control
* of each widget to 
* @author Sirtaj Singh Kang (taj@kde.org)
* @version $Id: baglayout.h,v 1.3 1999/01/10 18:17:03 ssk Exp $
* @short Allows finer-grained layout control similar to @ref QGridLayout
*/
class KBagLayout : public QObject
{
	Q_OBJECT

private:
	KBagLayout& operator=( const KBagLayout& );
	KBagLayout( const KBagLayout& );

	QWidget *_parent;

	QPtrDict<KBagConstraints> *_cstr;
	QList<QWidget>	*_widgets;

	/** 
	 * This is set if @ref ::setGridSize is called.
	 */
	bool _sizeSet;

	QSize	_grid;
	QSize	_min;
	QSize	_max;

	QRect	_contents;

	int _topSpace;
	int _bottomSpace;
	int _leftSpace;
	int _rightSpace;

	void arrangeWidget( QWidget *w, KBagConstraints *c );
	void calcGridExtent();
	void updateContentRect();
	void updateMinSize();
public:
	/**
	* Create a KBagLayout object with the given grid size.
	*/
	KBagLayout( QWidget *parent, int xsize=0, int ysize=0 );

	/**
	* KBagLayout Destructor
	*/
	virtual ~KBagLayout();
	
	KBagConstraints *addWidget( QWidget *widget );
	KBagConstraints *addWidget( QWidget *widget, KBagConstraints& constr );
	KBagConstraints *addWidget( QWidget *widget, int x, int y,
				 int xspan = 1, int yspan = 1 );

	/** 
	 * Find the constraints of a handled widgets.
	 * @return A non-const pointer to the widget, or 0 if
	 *	it is not being handled by this layout object.
	 */
	KBagConstraints *constraints( const QWidget *widget );

	/** 
	 * Recalculate and lay out handled widgets. This is also
	 * automatically called everytime the parent widget is
	 * resized.
	 */
	void activate();

	/** 
	 * Set the size of the logical layout grid. If this is
	 * never called, the default grid will be big enough to
	 * allow all added widgets to be contained.
	 */
	void setGridSize( int x, int y ) 
		{ _grid.setWidth( x ); _grid.setHeight( y ); _sizeSet = true; }

	/** 
	 * Event filter for parent widget. This implementation
	 * calls @ref ::activate on resize events.
	 */
	bool eventFilter( QObject *, QEvent * );

	/** 
	 * Set the blank vertical space which will be left between the
	 * parent widget's border and the laid-out widgets.
	 * @see ::setHSpace
	 */
	void setVSpace( int top, int bottom ) 
		{ _topSpace = top; _bottomSpace = bottom; updateContentRect(); }

	/** 
	 * Set the blank horizontal space which will be left between the
	 * parent widget's border and the laid-out widgets.
	 * @see ::setVSpace
	 */
	void setHSpace( int left, int right )
		{ _leftSpace = left; _rightSpace = right; updateContentRect(); }

	/**
	* Set the horizontal and vertical space to be the
	* contents rect of a frame.
	*/
	void setSpaceContents( QFrame *frame );
};


inline KBagConstraints *KBagLayout::constraints( const QWidget *widget )
{
	return _cstr->find( (void *) widget );
}

#endif // SSK_GRIDBAGL_H