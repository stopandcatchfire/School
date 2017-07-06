/*
 * Alien is an extension of opponent, in the current moment it is pretty basic
 * it's movement and size are predetermined and is fully automated during play.
 */


package com.mycompany.a2;

import com.codename1.charts.util.ColorUtil;

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
}
