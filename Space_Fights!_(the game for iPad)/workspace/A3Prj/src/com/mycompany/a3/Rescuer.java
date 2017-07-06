package com.mycompany.a3;

/*
 * Rescuers are currently just the spaceship object.  But since all rescuers
 * are guided and in the same way, implemented a 10 pixel shift in given 
 * directions from input.
 */
public abstract class Rescuer extends GameObject implements IGuided{

	public void moveLeft(){
		int tempX = getX();
		if(tempX>0){
			tempX -= 30.0;
			setX(tempX);
		}
		updateLocation();
	}
	
	public void moveRight(){
		int tempX = getX();
		if(tempX<getWorldWidth()-getSize()){	
			tempX += 30.0;
			setX(tempX);
		}
		updateLocation();
	}
	
	public void moveUp(){
		int tempY = getY();
		if(tempY<getWorldHeight()-getSize()){
			tempY += 30.0;
			setY(tempY);
		}
		updateLocation();
	}
	
	public void moveDown(){
		int tempY = getY();
		if(tempY>0){
			tempY -= 30.0;
			setY(tempY);
		}
		updateLocation();
	}
	
	public void widenDoor(){}
	
	public void shrinkDoor(){}
	
}
