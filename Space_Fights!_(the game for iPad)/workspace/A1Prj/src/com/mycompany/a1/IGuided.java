package com.mycompany.a1;

import com.codename1.charts.models.Point;

/*
 * IGuided is an interface for guided objects ie Rescuers.
 */


public interface IGuided {

	public void moveLeft();

	public void moveRight();
	
	public void moveUp();
	
	public void moveDown();
	
	public void jumpToLocation(Point p);
}
