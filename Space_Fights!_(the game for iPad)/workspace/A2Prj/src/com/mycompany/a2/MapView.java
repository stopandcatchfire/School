package com.mycompany.a2;

import java.util.Observable;
import java.util.Observer;

import com.codename1.ui.Container;

public class MapView extends Container implements Observer {

	private GameWorld g;
	
	public MapView(GameWorld g){
		this.g = g;
		g.printMap();
	}
	
	//@Override
	public void update(Observable observable, Object data){
		this.g.printMap();
	}
}
