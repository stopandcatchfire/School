package com.mycompany.a3;

import java.util.Random;

import com.codename1.ui.Graphics;
import com.codename1.ui.Transform;
import com.codename1.ui.geom.PathIterator;
import com.codename1.ui.geom.Point;
import com.codename1.ui.geom.Rectangle;
import com.codename1.ui.geom.Shape;



/*
 * Superclass of all objects in game.  Holds size, color, coordinators, and a hitbox to be utilized later.
 * I was trying to use the rectangle.contains(opponent.getX,Y) but it wasn't picking up the Point correctly.
 * I think it will work better when comparing two shapes instead of a shape and a Point.
 * Contains most getters and setters for objects.
 */
public abstract class GameObject implements Shape, IDrawable{
	private int size;
	private int color;
	private int x;
	private int y;
	private int worldWidth;
	private int worldHeight;
	private int worldX;
	private int worldY;
	private Point location = new Point(0,0);
	private Shape shape;
	private Rectangle hitBox;
	Random rand = new Random();
	
	
	//GameObject constructor sets random location (x,y) and creates a new square
	//to act as the hit box. shape will be implemented when we do graphics I think.
	public GameObject() {
		x = 0;
		y = 0;
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
	
	public void setX(int pX){
		x = pX;
	}
	
	public int getX(){
		return x;
	}
	
	public void setY(int pY){
		y = pY;
	}
	
	public int getY(){
		return y;
	}
	
	// figure out if I want to pass point or coordinates. Why not BOTH?
	public void setLocation(int pX, int pY){
		location.setX(pX);
		location.setY(pY);
		setX(pX);
		setY(pY);
	}
	
	public void setLocation(Point p){
		location = p;
		setX(p.getX());
		setY(p.getY());
	}
	
	public Point getLocation(){
		return location;
	}
	
	public void updateLocation(){
		setLocation(x, y);
		//updateHitBox();
	}
	
	//hitbox to be implemented later.
	public void updateHitBox(){
		hitBox.setX(getX());
		hitBox.setY(getY());
		hitBox.setHeight(size);
		hitBox.setWidth(size);
	}
	
	public void setWorld(int w, int h, int wx, int wy){
		worldWidth = w;
		worldHeight = h;
		worldX = wx;
		worldY = wy;
	}
	
	public int getWorldHeight(){
		return worldHeight;
	}
	
	public int getWorldWidth(){
		return worldWidth;
	}
	
	public int getWorldX(){
		return worldX;
	}
	
	public int getWorldY(){
		return worldY;
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
