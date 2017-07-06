package com.mycompany.a3;




import com.codename1.charts.util.ColorUtil;
import com.codename1.ui.Graphics;
import com.codename1.ui.geom.Point;


/*
 * Spaceship is a guided rescuer.  Has unique size setter, in that it has bounds.
 * Also the ability to jump to a location, which gets passed by random opponent location.
 * Door size controls are also implemented here +/- 10 pixels per change.
 */
public class Spaceship extends Rescuer{

	private static Spaceship spaceship;
	
	private Spaceship(){}
	
	public static Spaceship getSpaceship(){
		if(spaceship == null)
			spaceship = new Spaceship();
			spaceship.setSize(100);
			spaceship.setColor(ColorUtil.GRAY);
		return spaceship;
	}
	@Override
	public void setSize(int s){
		if(s > 49 && s < 1025)
			super.setSize(s);
	}

	public void jumpToLocation(Point p){
		setX(p.getX());
		setY(p.getY());
		setLocation(p);
		updateLocation();
	}
	
	public void widenDoor(){
		if(getSize()<1014){
			setSize(getSize()+10);
		}
		else if(getSize()<1024){
			setSize(1024);
		}
		//updateHitBox();
	}
	
	public void shrinkDoor(){
		if(getSize()>60){
			setSize(getSize()-40);
		}
		else if(getSize()>50){
			setSize(50);
		}
		//updateHitBox();
	}
	
	@Override
	public String toString(){
		System.out.println("Spaceship: loc=" + Math.round(getX()*10.0)/10.0 + "," + Math.round(getY()*10.0)/10.0 + " color=[" + ColorUtil.red(getColor()) 
			+ "," + ColorUtil.green(getColor()) + "," + ColorUtil.blue(getColor()) + "] size=" + getSize());
		return null;
	}



	public void draw(Graphics g, Point pCmpRelPrnt) {
		g.setColor(this.getColor());
		g.drawRect((getX()+pCmpRelPrnt.getX())-(getSize()/2), (getY()+pCmpRelPrnt.getY())-(getSize()/2), getSize(), getSize());
		
	}

}
