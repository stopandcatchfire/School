package com.mycompany.a1;

import com.codename1.charts.models.Point;

/*
 * Opponent represents Aliens and Astronauts, handling what they do similarly
 * Speed and direction are unique to opponents.  The move method first checks if
 * an Opponent is on or past the game screen edge.  If it is, direction is inverted
 * and it will travel in the opposite direction.  The random changes in direction
 * will also assist in ensuring no getting stuck in corners etc...
 */

public abstract class Opponent extends GameObject implements IMovable{
	private int speed;
	private int direction;
	
	//construct opponents with size between 20 and 50
	public Opponent(){
		setSize(rand.nextInt(30)+20);
		direction = rand.nextInt(359);
	}
	//all opponents move and in the same way
	public void move(){
		if(getX()<0.1 || getX()>1023.9 || getY()<0.1 || getY()>785.9){
			direction = (direction + 180)%359;
		}
		
		
		float newX = (float) (getX() + (Math.cos(direction - 90.0)*speed));
		float newY = (float) (getY() + (Math.sin(direction - 90.0)*speed));
		Point p = new Point(newX,newY);
		
		direction += (rand.nextInt(10)-5);	//adds or subtracts up to 5 degrees to ensure no sticking.
		
		//updates X Y and location on move
		setX(newX);							
		setY(newY);
		setLocation(p);
	}
	
	/*
	 * Getters/setters
	 */
	public void setSpeed(int s){
		speed = s;
	}
	
	public int getSpeed(){
		return speed;
	}
	
	public void setDirection(int d){
		direction = d;
	}
	
	public int getDirection(){
		return direction;
	}
	
}
