package com.mycompany.a3;

import java.util.Observable;
import java.util.Observer;

import com.codename1.ui.Container;
import com.codename1.ui.Graphics;
import com.codename1.ui.geom.Point;

public class MapView extends Container implements Observer {

	private GameWorld g;
	private IIterator it;
	private GameObject o;
	
	public MapView(GameWorld g){
		this.g = g;
	}
	
	//@Override
	public void update(Observable observable, Object data){
		this.g.printMap();
		this.repaint();
	}
	
	@Override
	public void paint(Graphics graph){
		
		it = g.getIterator(true);
		super.paint(graph);
		
		
		Point pCmpRelPrnt = new Point(this.getX(),this.getY());
		
		while(it.hasNext()){
			o = it.getNext();
			o.draw(graph, pCmpRelPrnt);
		}
	}
	
	@Override
	public void pointerPressed(int x, int y){
		x = x-this.getX();
		y = y-this.getAbsoluteY();
		it = g.getIterator(true);
		System.out.println("pointerPressed"+x+", "+y);
		while(it.hasNext()){
			o = it.getNext();
			if(o instanceof Astronaut){
				if(((o.getX()-o.getSize())<x) && ((o.getY()-o.getSize())<y) && ((o.getX()+o.getSize())>x) && ((o.getY()+o.getSize())>y)){
					Astronaut a = (Astronaut) o;
					if(a.getSelected()){
						a.setSelected(false);
					}
					else{
						a.setSelected(true);
					}
					this.repaint();
				}	
				else{
					Astronaut a = (Astronaut) o;
					a.setSelected(false);
				}
					
			}
		}
	}
}
