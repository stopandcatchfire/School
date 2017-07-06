package com.mycompany.a1;

import com.codename1.charts.util.ColorUtil;

/*
 * The Astronaut class is the representation of the concrete object Astronaut.
 * It has unique attributes health and ability to change color.
 * Getters and setters as appropriate, updating color is giving me trouble at 
 * the moment.
 */

public class Astronaut extends Opponent{

	private int health;
	private int constant = 1;
	
	
	public Astronaut() {
		setColor(ColorUtil.rgb(0,0,255));
		setHealth(5);
		updateSpeed();
	}

	/*
	 * Getters and Setters
	 */
	public void updateHealth(){
		if(health>0){
			setHealth(getHealth() - 1);
		}
	}
	
	public void setHealth(int i){
		health = i;
	}
	 
	public void updateColor(){
		if(health>0){
			int colorTmp = (int) (51*(5%health));
			setColor(ColorUtil.rgb(colorTmp,colorTmp,255));
		}
		else
			setColor(ColorUtil.rgb(250,250,255));
	}
	
	//speed is health * constant, will probably change once we have variable speeds
	public void updateSpeed(){
		setSpeed(health * constant);
	}

	public int getHealth(){
		return health;
	}

	@Override
	public String toString(){
		System.out.println("Astronaut: loc=" +  Math.round(getX()*10.0)/10.0 + "," + Math.round(getY()*10.0)/10.0 + " color=[" + ColorUtil.red(getColor()) 
			+ "," + ColorUtil.green(getColor()) + "," + ColorUtil.blue(getColor()) + "] size=" + getSize() 
			+ " speed=" + getSpeed() + " dir=" + getDirection() + " health=" + health);
		return null;
	}
}
