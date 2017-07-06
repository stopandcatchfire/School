package com.mycompany.a1;

/*
 * Rescuers are currently just the spaceship object.  But since all rescuers
 * are guided and in the same way, implemented a 10 pixel shift in given 
 * directions from input.
 */
public abstract class Rescuer extends GameObject implements IGuided{

	public void moveLeft(){
		float tempX = getX();
		if(tempX>0){
			tempX -= 10.0;
			setX(tempX);
		}
		updateLocation();
	}
	
	public void moveRight(){
		float tempX = getX();
		if(tempX<1240.0){	
			tempX += 10.0;
			setX(tempX);
		}
		updateLocation();
	}
	
	public void moveUp(){
		float tempY = getY();
		if(tempY<768.0){
			tempY += 10.0;
			setY(tempY);
		}
		updateLocation();
	}
	
	public void moveDown(){
		float tempY = getY();
		if(tempY>0){
			tempY -= 10.0;
			setY(tempY);
		}
		updateLocation();
	}
	
	public void widenDoor(){}
	
	public void shrinkDoor(){}
	
}
