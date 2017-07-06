package com.mycompany.a3;

import com.codename1.ui.geom.Point;

/*
 * IGuided is an interface for guided objects ie Rescuers.
 */


public interface IGuided {

	public void moveLeft();

	public void moveRight();
	
	public void moveUp();
	
	public void moveDown();
	
	public void jumpToLocation(Point point);
}
