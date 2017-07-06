package com.mycompany.a1;

import java.util.Observable;
import java.util.Observer;

import com.codename1.ui.Container;
import com.codename1.ui.Label;
import com.codename1.ui.layouts.FlowLayout;
import com.codename1.ui.layouts.GridLayout;

public class ScoreView extends Container implements Observer {
	
	private String soundS = "On";
	private GameWorld gw;
	//private ComponentGroup cg;
	Label sc = new Label();
	Label scr = new Label();
	Label ar = new Label();
	Label asn = new Label();
	Label alr = new Label();
	Label asr = new Label();
	Label sound = new Label();
	
	
	
	public ScoreView(GameWorld gw){
		this.gw = gw;
		
		this.setLayout(new FlowLayout(CENTER));
		
		if(gw.getSound()){
			this.soundS = "On";
		}
		else
			this.soundS = "Off";
		
		this.sc.setText("Total Score: " + gw.getPoints());
		this.ar.setText("Astronauts Rescued: " + gw.getRescued());
		this.asn.setText("Aliens Sneaked In: " + gw.getSneakedIn());
		this.asr.setText("Astronauts Remaining: " + gw.getAstOutside());
		this.alr.setText("Aliens Remaining: " + gw.getAlOutside());
		this.sound.setText("Sound: " + soundS);
		
		sc.getAllStyles().setPadding(RIGHT, 2);
		ar.getAllStyles().setPadding(RIGHT, 2);
		asn.getAllStyles().setPadding(RIGHT, 2);
		asr.getAllStyles().setPadding(RIGHT, 2);
		alr.getAllStyles().setPadding(RIGHT, 2);
		sound.getAllStyles().setPadding(RIGHT, 2);
		
		this.add(sc);
		this.add(ar);
		this.add(asn);
		this.add(asr);
		this.add(alr);
		this.add(sound);
		
		
	}
	
	public void update(Observable o, Object arg){
		
		if(gw.getSound()){
			this.soundS = "On";
		}
		else
			this.soundS = "Off";
		
		this.sc.setText("Total Score: " + gw.getPoints());
		this.ar.setText("Astronauts Rescued: " + gw.getRescued());
		this.asn.setText("Aliens Sneaked In: " + gw.getSneakedIn());
		this.asr.setText("Astronauts Remaining: " + gw.getAstOutside());
		this.alr.setText("Aliens Remaining: " + gw.getAlOutside());
		this.sound.setText("Sound: " + soundS);
		
		this.repaint();
	}

}
