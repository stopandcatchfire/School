package com.mycompany.a3;

import com.codename1.charts.util.ColorUtil;
import com.codename1.ui.Graphics;
import com.codename1.ui.geom.Point;

/*
 * The Astronaut class is the representation of the concrete object Astronaut.
 * It has unique attributes health and ability to change color.
 * Getters and setters as appropriate, updating color is giving me trouble at 
 * the moment.
 */

public class Astronaut extends Opponent implements ISelectable{

	private int health;
	private int constant = 1;
	private int xarr[] = new int[3];
	private int yarr[] = new int[3];
	private boolean isSelected = false;
	
	
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

	public void draw(Graphics g, Point pCmpRelPrnt){
		xarr[0] = this.getX()+pCmpRelPrnt.getX()-(getSize()/2);
		xarr[1] = this.getX()+pCmpRelPrnt.getX();
		xarr[2] = this.getX()+pCmpRelPrnt.getX()+(getSize()/2);
		yarr[0] = this.getY()+pCmpRelPrnt.getY()+(getSize()/2);
		yarr[1] = this.getY()+pCmpRelPrnt.getY()-(getSize()/2);
		yarr[2] = this.getY()+pCmpRelPrnt.getY()+(getSize()/2);
		g.setColor(this.getColor());
		if(isSelected){
			g.fillPolygon(xarr,yarr,3);
		}
		else{
			g.drawPolygon(xarr,yarr,3);
		}
	}
	
	public void setSelected(boolean b){
		isSelected = b;
	}
	
	public boolean getSelected(){
		return isSelected;
	}
	
	@Override
	public String toString(){
		System.out.println("Astronaut: loc=" +  Math.round(getX()*10.0)/10.0 + "," + Math.round(getY()*10.0)/10.0 + " color=[" + ColorUtil.red(getColor()) 
			+ "," + ColorUtil.green(getColor()) + "," + ColorUtil.blue(getColor()) + "] size=" + getSize() 
			+ " speed=" + getSpeed() + " dir=" + getDirection() + " health=" + health);
		return null;
	}

	public boolean checkCollisions(ICollider o) {
		// TODO Auto-generated method stub
		return false;
	}

	public void handleCollision(ICollider o) {
		// TODO Auto-generated method stub
		
	}

	public void handleCollision(Opponent o) {
		// TODO Auto-generated method stub
		
	}
	
	
}
