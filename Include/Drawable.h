

#pragma once

/*! Abstract class
	Allows an object to be drawn by render component
*/

class Drawable {
public:
	//!< Virtual function called when object is drawn
	virtual void draw() = 0;
};