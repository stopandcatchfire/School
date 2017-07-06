/*
 * Alien is an extension of opponent, in the current moment it is pretty basic
 * it's movement and size are predetermined and is fully automated during play.
 */


package com.mycompany.a3;

import com.codename1.charts.util.ColorUtil;
import com.codename1.ui.Graphics;
import com.codename1.ui.geom.Point;

public class Alien extends Opponent{

	private int constant = 1;
	
	public Alien(){
		setColor(ColorUtil.rgb(0,255,0));
		setSpeed(5 * constant);
	}
	
	
	@Override
	public String toString(){
		System.out.println("Alien: loc=" +  Math.round(getX()*10.0)/10.0 + "," + (Math.round(getY()*10.0)/10.0) + " color=[" + ColorUtil.red(getColor()) 
			+ "," + ColorUtil.green(getColor()) + "," + ColorUtil.blue(getColor()) + "] size=" + getSize() 
			+ " speed=" + getSpeed() + " dir=" + getDirection());
		return null;
	}

	public void draw(Graphics g, Point pCmpRelPrnt) {
		g.setColor(this.getColor());
		g.drawArc(getX()+pCmpRelPrnt.getX(),getY()+pCmpRelPrnt.getY(), getSize(), getSize(), 0, 360);
		
	}


	
	
	public void setColls(Opponent o, Opponent sp){
		 super.setColls(o, sp);
	}
	
	
	
	
	public boolean checkCollisions(ICollider o) {
		// TODO Auto-generated method stub
		return false;
	}


	public void handleCollision(Opponent o) {
		// TODO Auto-generated method stub
		
	}
}
