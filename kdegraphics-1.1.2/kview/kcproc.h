/*
* kcproc.h -- Declaration of class KColourProc.
* Generated by newclass on Thu Oct 15 13:51:46 EST 1998.
*/
#ifndef SSK_KCPROC_H
#define SSK_KCPROC_H

/**
* Provides methods to convert pixel colour spaces between
* HSV and RGB. Also provides gamma correction facilities.
*
* In the interest of performance, no error checking is
* done. Please call setGamma BEFORE attempting to call
* gammaCorrect.
*
* All HSV values are assumed to be in the range (0..1).
* All RGB values are assumed to be in the range (0..255).
*
* @author Sirtaj Singh Kang (taj@kde.org)
* @version $Id: kcproc.h,v 1.2 1998/10/26 06:22:39 ssk Exp $
* @short Colour space and gamma utilities.
*/
class KColourProc
{

private:

	double _gammav;
	double *_gammat;

public:
	/**
	* KColourProc Constructor
	*/
	KColourProc();

	/**
	* KColourProc Destructor
	*/
	virtual ~KColourProc();
	
	/**
	* Convert the RGB values (in range 0-255) to 
	* HSV values (range 0-1). The values are stored 
	* back in the RGB references passed as arguments.
	* @return false if conversion failed.
	*/
	static bool toHSV( double& r, double& g, double& b );

	/**
	* Convert the HSV values (in range 0-1) to 
	* RGB values (range 0-255). The values are stored 
	* back in the HSV references passed as arguments.
	* @return always true
	*/
	static bool toRGB( double& h, double& s, double& v );

	/**
	* Intialize gamma tables to the provided gamma value.
	* This is done to speed up gamma correction. All
	* following calls to the gammaCorrect methods will
	* correct the intensity to the given gamma.
	*/
	void setGamma( double gamma );

	/**
	* Return the gamma value last set with setGamma.
	* @see ::setGamma
	*/
	double gamma() const { return _gammav; }

	/**
	* Correct the intensity of the RGB values (in range
	* 0-255) to the gamma value last set with
	* @ref ::setGamma. Note that if you already have
	* the HSV values of the pixel, it will be faster
	* to call gammaCorrect( v ) instead, since this
	* step entails conversion to HSV and then back
	* to RGB.
	*/
	void gammaCorrect( int& r, int& g, int& b ) const;

	/**
	* Correct the intensity V to the gamma value last
	* set with @ref ::setGamma.
	*/
	void gammaCorrect( double& v ) const; 

private:
	KColourProc& operator=( const KColourProc& );
	KColourProc( const KColourProc& );
};

#endif // SSK_KCPROC_H
