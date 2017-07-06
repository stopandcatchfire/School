package com.mycompany.a3;

import java.util.Vector;

import com.codename1.ui.geom.Dimension;
import com.codename1.ui.geom.Point;

/*
 * Opponent represents Aliens and Astronauts, handling what they do similarly
 * Speed and direction are unique to opponents.  The move method first checks if
 * an Opponent is on or past the game screen edge.  If it is, direction is inverted
 * and it will travel in the opposite direction.  The random changes in direction
 * will also assist in ensuring no getting stuck in corners etc...
 */

public abstract class Opponent extends GameObject implements IMovable,ICollider{
	private int speed;
	private int direction;
	private int incX;
	private int incY;
	private int newX;
	private int newY;
	private Point r1;
	private Point l1;
	private Point r2;
	private Point l2;
	private Vector<Opponent> collision;
	private Alien a;
	private Astronaut g;
	private boolean collided = false;
	private boolean newSpawn = false;
	
	//construct opponents with size between 20 and 50
	public Opponent(){
		setSize(rand.nextInt(30)+20);
		direction = rand.nextInt(359);
		collision = new Vector<Opponent>();
		r1 = new Point(getX()+getSize(),getY());
		r2 = new Point(getX()+getSize(),getY()+getSize());
		l1 = new Point(getX(),getY());
		l2 = new Point(getX(),getY()+getSize());
	}
	//all opponents move and in the same way
	public void move(Dimension d){
		incX = (int) ((Math.cos(direction - 90.0)*speed));
		incY = (int) ((Math.sin(direction - 90.0)*speed));
		
		if((getX()+getSize()>=d.getWidth()) || (getX()-getSize()<0)){
			incX = -incX;
			direction += 95;
		}
			
		else if((getY()-getSize()<0) || (getY()+getSize()>=d.getHeight())){
			incY = -incY;
			direction += 91;
		}
		
		newX = getX() + incX;
		newY = getY() + incY;
		
		
		Point p = new Point(newX,newY);
		
		//direction += (rand.nextInt(4)-2);	//adds or subtracts up to 5 degrees to ensure no sticking.
		
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
	
	public boolean checkCollisions(Opponent o){
		
		r1 = new Point(getX()+getSize(),getY());
		r2 = new Point(getX()+getSize(),getY()+getSize());
		l1 = new Point(getX(),getY());
		l2 = new Point(getX(),getY()+getSize());
		
		//System.out.println("checkCollision");
		if(((r1.getX()>=o.l2.getX())&&(r1.getY()<=o.l2.getY()))&&(((l1.getX()<=o.r2.getX())&&(l1.getY()<=o.r2.getY())))){
			System.out.println("foundCollision");
			
			return true;
		}
		//if collision has not taken place or if there is no longer a collision
		if(collision.contains(o) && this.getCollided() && !this.getNewSpawn()){
			setCollided(false);
			collision.remove(o);
		}
		
		return false;
		
		
	}
	
	public void handleCollision(Opponent o, GameWorld game){
		
		System.out.println("handling Collisions");
		
		if(this.collision.contains(o) || this.getCollided() || game.getAlOutside()>20){
			System.out.println("preventingSpawn");
			return;
		}
		else if(this instanceof Alien){
			if(o instanceof Astronaut){
				g = (Astronaut) o;
				g.updateHealth();
				g.updateColor();
				g.updateSpeed();
				this.setCollided(true);
				g.setCollided(true);
				game.playFightSound();
			}		
			else{
				a = game.spawnNewAlien(this.getX(),this.getY(), o, this);
				this.collision.add(a);
				this.setCollided(true);
				o.setCollided(true);
				o.collision.add(this);
				o.collision.add(a);
				a.setCollided(true);
				a.setNewSpawn();
			}
			
			this.collision.add(o);
				
		}
	}
	
	public boolean getCollided(){
		return collided;
	}
	
	public void setCollided(boolean b){
		collided = b;
	}
	
	public void setColls(Opponent o, Opponent sp){
		this.collision.add(o);
		this.collision.add(sp);
	}
	
	public void setNewSpawn(){
		newSpawn = true;
	}
	
	public boolean getNewSpawn(){
		return newSpawn;
	}
	
}
