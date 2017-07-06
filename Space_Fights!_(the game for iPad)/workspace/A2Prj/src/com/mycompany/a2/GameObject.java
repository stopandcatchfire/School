package com.mycompany.a2;

import java.util.Random;
import com.codename1.ui.Transform;
import com.codename1.ui.geom.PathIterator;
import com.codename1.ui.geom.Rectangle;
import com.codename1.ui.geom.Shape;
import com.codename1.charts.models.Point;


/*
 * Superclass of all objects in game.  Holds size, color, coordinators, and a hitbox to be utilized later.
 * I was trying to use the rectangle.contains(opponent.getX,Y) but it wasn't picking up the Point correctly.
 * I think it will work better when comparing two shapes instead of a shape and a Point.
 * Contains most getters and setters for objects.
 */
public abstract class GameObject implements Shape{
	private int size;
	private int color;
	private float x;
	private float y;
	private Point location = new Point();
	//private Shape shape;
	private Rectangle hitBox;
	Random rand = new Random();
	
	
	//GameObject constructor sets random location (x,y) and creates a new square
	//to act as the hit box. shape will be implemented when we do graphics I think.
	public GameObject() {
		x = rand.nextFloat()*1024;
		y = rand.nextFloat()*768;
		setLocation(x,y);
		hitBox = new Rectangle(Math.round(x),Math.round(y),size,size);
	}
	
	
	//Getters and setters
	public void setSize(int s){
		size = s;
	}
	
	public int getSize(){
		return size;
	}
	
	public void setColor(int c){
		color = c;
	}
	
	public int getColor(){
		return color;
	}
	
	public void setX(float pX){
		x = pX;
	}
	
	public float getX(){
		return x;
	}
	
	public int getIntX(){
		return Math.round(x);
	}
	
	public void setY(float pY){
		y = pY;
	}
	
	public float getY(){
		return y;
	}
	
	public int getIntY(){
		return Math.round(y);
	}
	// figure out if I want to pass point or coordinates. Why not BOTH?
	public void setLocation(float pX, float pY){
		location.setX(pX);
		location.setY(pY);
	}
	
	public void setLocation(Point p){
		location = p;
	}
	
	public Point getLocation(){
		return location;
	}
	
	public void updateLocation(){
		setLocation(x, y);
		updateHitBox();
	}
	
	//hitbox to be implemented later.
	public void updateHitBox(){
		hitBox.setX(getIntX());
		hitBox.setY(getIntY());
		hitBox.setHeight(size);
		hitBox.setWidth(size);
	}
	
	
	
	
	
	
	/*
	 * Need these to eliminate implementation issues with shape.
	 * 
	 */
	public PathIterator getPathIterator() {
		// TODO Auto-generated method stub
		return null;
	}

	public PathIterator getPathIterator(Transform transform) {
		// TODO Auto-generated method stub
		return null;
	}

	public Rectangle getBounds() {
		// TODO Auto-generated method stub
		return null;
	}

	public float[] getBounds2D() {
		// TODO Auto-generated method stub
		return null;
	}

	public boolean isRectangle() {
		// TODO Auto-generated method stub
		return false;
	}

	public boolean contains(int x, int y) {
		// TODO Auto-generated method stub
		return false;
	}

	public Shape intersection(Rectangle rect) {
		// TODO Auto-generated method stub
		return null;
	}
	
	
}
