package com.mycompany.a2;

import com.codename1.ui.Command;
import com.codename1.ui.events.ActionEvent;

public class AlienCollisionCommand extends Command{
	private GameWorld g;
	
	public AlienCollisionCommand(GameWorld gw){
		super("NewAlien");
		this.g = gw;
	}
	
	@Override
	public void actionPerformed(ActionEvent evt){
		g.alienCollisionCheck();
	}

}
